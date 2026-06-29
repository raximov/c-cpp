#include "kd_tree.h"
#include <algorithm>
#include <cmath>
#include <numeric>

namespace s21 {

// ---- AABB ------------------------------------------------------------------

void AABB::Expand(const Vec3& p) {
  min_pt.x = std::min(min_pt.x, p.x);
  min_pt.y = std::min(min_pt.y, p.y);
  min_pt.z = std::min(min_pt.z, p.z);
  max_pt.x = std::max(max_pt.x, p.x);
  max_pt.y = std::max(max_pt.y, p.y);
  max_pt.z = std::max(max_pt.z, p.z);
}

void AABB::Expand(const AABB& o) {
  Expand(o.min_pt);
  Expand(o.max_pt);
}

bool AABB::Intersect(const Ray& ray, double t_min, double t_max) const {
  for (int a = 0; a < 3; ++a) {
    double inv = 1.0 / ((a==0)?ray.direction.x:(a==1)?ray.direction.y:ray.direction.z);
    double o   = (a==0)?ray.origin.x:(a==1)?ray.origin.y:ray.origin.z;
    double lo  = (a==0)?min_pt.x:(a==1)?min_pt.y:min_pt.z;
    double hi  = (a==0)?max_pt.x:(a==1)?max_pt.y:max_pt.z;
    double t0  = (lo - o) * inv;
    double t1  = (hi - o) * inv;
    if (t0 > t1) std::swap(t0, t1);
    t_min = std::max(t_min, t0);
    t_max = std::min(t_max, t1);
    if (t_max <= t_min) return false;
  }
  return true;
}

Vec3 AABB::Center() const {
  return Vec3{(min_pt.x+max_pt.x)*0.5,
              (min_pt.y+max_pt.y)*0.5,
              (min_pt.z+max_pt.z)*0.5};
}

// ---- TrianglePrimitive -----------------------------------------------------

AABB TrianglePrimitive::BoundingBox() const {
  AABB bb;
  bb.Expand(v0); bb.Expand(v1); bb.Expand(v2);
  return bb;
}

std::optional<HitRecord> TrianglePrimitive::Intersect(
    const Ray& ray, double t_min, double t_max) const {
  // Möller–Trumbore
  constexpr double kEps = 1e-8;
  Vec3 e1 = v1 - v0, e2 = v2 - v0;
  Vec3 h = ray.direction.cross(e2);
  double a = e1.dot(h);
  if (std::abs(a) < kEps) return std::nullopt;
  double f = 1.0 / a;
  Vec3 s = ray.origin - v0;
  double u = f * s.dot(h);
  if (u < 0 || u > 1) return std::nullopt;
  Vec3 q = s.cross(e1);
  double v = f * ray.direction.dot(q);
  if (v < 0 || u + v > 1) return std::nullopt;
  double t = f * e2.dot(q);
  if (t < t_min || t > t_max) return std::nullopt;

  HitRecord rec;
  rec.t = t;
  rec.point = ray.origin + ray.direction * t;
  // Interpolate smooth normal
  double w = 1.0 - u - v;
  Vec3 smooth_n = (n0 * w + n1 * u + n2 * v).normalized();
  rec.front_face = ray.direction.dot(smooth_n) < 0;
  rec.normal = rec.front_face ? smooth_n : smooth_n * -1.0;
  return rec;
}

// ---- KDTree ----------------------------------------------------------------

void KDTree::Build(std::vector<TrianglePrimitive> prims) {
  root_ = BuildNode(prims, 0);
}

std::unique_ptr<KDNode> KDTree::BuildNode(std::vector<TrianglePrimitive>& prims,
                                           int depth) {
  auto node = std::make_unique<KDNode>();

  // Compute bounding box
  for (const auto& p : prims) node->bbox.Expand(p.BoundingBox());

  if (static_cast<int>(prims.size()) <= kMaxLeafPrimitives || depth >= kMaxDepth) {
    node->is_leaf = true;
    node->primitives = prims;
    return node;
  }

  // Choose longest axis
  Vec3 ext = Vec3{node->bbox.max_pt.x - node->bbox.min_pt.x,
                   node->bbox.max_pt.y - node->bbox.min_pt.y,
                   node->bbox.max_pt.z - node->bbox.min_pt.z};
  int axis = 0;
  if (ext.y > ext.x) axis = 1;
  if ((axis==0?ext.z:ext.y) > (axis==0?ext.x:ext.y)) axis = 2;

  // Sort by centroid along axis
  std::sort(prims.begin(), prims.end(), [axis](const auto& a, const auto& b) {
    auto ca = a.BoundingBox().Center();
    auto cb = b.BoundingBox().Center();
    return (axis==0?ca.x:(axis==1?ca.y:ca.z)) < (axis==0?cb.x:(axis==1?cb.y:cb.z));
  });

  size_t mid = prims.size() / 2;
  std::vector<TrianglePrimitive> left_prims(prims.begin(), prims.begin() + mid);
  std::vector<TrianglePrimitive> right_prims(prims.begin() + mid, prims.end());

  node->left  = BuildNode(left_prims, depth + 1);
  node->right = BuildNode(right_prims, depth + 1);
  return node;
}

std::optional<HitRecord> KDTree::Intersect(const Ray& ray,
                                            double t_min,
                                            double t_max) const {
  if (!root_) return std::nullopt;
  return IntersectNode(root_.get(), ray, t_min, t_max);
}

std::optional<HitRecord> KDTree::IntersectNode(const KDNode* node,
                                                 const Ray& ray,
                                                 double t_min,
                                                 double t_max) const {
  if (!node->bbox.Intersect(ray, t_min, t_max)) return std::nullopt;

  if (node->is_leaf) {
    std::optional<HitRecord> closest;
    for (const auto& prim : node->primitives) {
      auto hit = prim.Intersect(ray, t_min, t_max);
      if (hit && (!closest || hit->t < closest->t)) {
        closest = hit;
        t_max = hit->t;
      }
    }
    return closest;
  }

  auto left_hit  = IntersectNode(node->left.get(), ray, t_min, t_max);
  double t_right = left_hit ? left_hit->t : t_max;
  auto right_hit = IntersectNode(node->right.get(), ray, t_min, t_right);
  return right_hit ? right_hit : left_hit;
}

}  // namespace s21
