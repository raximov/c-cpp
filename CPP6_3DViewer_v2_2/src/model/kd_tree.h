#pragma once
#include "model_data.h"
#include "camera.h"
#include "geometric_objects.h"
#include <memory>
#include <vector>
#include <optional>

namespace s21 {

struct AABB {
  Vec3 min_pt{1e9, 1e9, 1e9};
  Vec3 max_pt{-1e9, -1e9, -1e9};

  void Expand(const Vec3& p);
  void Expand(const AABB& other);
  bool Intersect(const Ray& ray, double t_min, double t_max) const;
  Vec3 Center() const;
};

struct TrianglePrimitive {
  Vec3 v0, v1, v2;
  Vec3 n0, n1, n2;  // vertex normals for smooth shading
  int model_index = 0;

  AABB BoundingBox() const;
  std::optional<HitRecord> Intersect(const Ray& ray, double t_min, double t_max) const;
};

class KDNode {
 public:
  AABB bbox;
  std::unique_ptr<KDNode> left;
  std::unique_ptr<KDNode> right;
  std::vector<TrianglePrimitive> primitives;  // leaf only
  bool is_leaf = false;
};

class KDTree {
 public:
  static constexpr int kMaxLeafPrimitives = 8;
  static constexpr int kMaxDepth = 20;

  void Build(std::vector<TrianglePrimitive> prims);
  std::optional<HitRecord> Intersect(const Ray& ray,
                                     double t_min,
                                     double t_max) const;

 private:
  std::unique_ptr<KDNode> root_;

  std::unique_ptr<KDNode> BuildNode(std::vector<TrianglePrimitive>& prims,
                                    int depth);
  std::optional<HitRecord> IntersectNode(const KDNode* node,
                                          const Ray& ray,
                                          double t_min,
                                          double t_max) const;
};

}  // namespace s21
