#include "scene.h"
#include "obj_parser.h"
#include <stdexcept>

namespace s21 {

Scene::Scene() {
  DirectionalLight dl;
  dl.position = {5, 10, 10};
  dl.intensity = 1.0f;
  light_manager_.SetDirectional(dl);
  AmbientLight al;
  al.intensity = 0.2f;
  light_manager_.SetAmbient(al);
}

bool Scene::LoadObjModel(const std::string& path) {
  if (static_cast<int>(models_.size()) >= kMaxModels) return false;
  ObjParser parser;
  try {
    ModelData data = parser.Parse(path);
    SceneModel sm;
    sm.data = std::move(data);
    sm.shape_type = "obj";
    models_.push_back(std::move(sm));
    active_model_index_ = static_cast<int>(models_.size()) - 1;
    NotifyObservers();
    return true;
  } catch (...) {
    return false;
  }
}

bool Scene::AddPrimitive(const std::string& type, Vec3 pos,
                          double radius, double height) {
  if (static_cast<int>(models_.size()) >= kMaxModels) return false;
  SceneModel sm;
  sm.shape_type = type;

  if (type == "Sphere")        sm.data = MakeSphereModel(16, 32);
  else if (type == "Cylinder") sm.data = MakeCylinderModel(32, radius, height);
  else if (type == "Cone")     sm.data = MakeConeModel(32, radius, height);
  else if (type == "Cube")     sm.data = MakeCubeModel(radius * 2);
  else if (type == "Pyramid")  sm.data = MakePyramidModel(4, radius, height);
  else return false;

  sm.analytic_shape = MakeAnalyticShape(type, pos, radius, height);
  models_.push_back(std::move(sm));
  active_model_index_ = static_cast<int>(models_.size()) - 1;
  RebuildAnalyticCache();
  NotifyObservers();
  return true;
}

bool Scene::RemoveModel(int index) {
  if (index < 0 || index >= static_cast<int>(models_.size())) return false;
  models_.erase(models_.begin() + index);
  active_model_index_ = std::max(0, index - 1);
  RebuildAnalyticCache();
  NotifyObservers();
  return true;
}

void Scene::SetActiveModel(int index) {
  if (index >= 0 && index < static_cast<int>(models_.size()))
    active_model_index_ = index;
}

void Scene::ApplyTransformToModel(int index, const Matrix4x4& m) {
  auto& sm = models_[index];
  sm.transform = AffineTransform::Multiply(m, sm.transform);
  AffineTransform::ApplyToVertices(m, sm.data.vertices);
  if (!sm.data.normals.empty())
    AffineTransform::ApplyToNormals(m, sm.data.normals);
}

void Scene::TranslateModel(int idx, double tx, double ty, double tz) {
  if (idx < 0 || idx >= static_cast<int>(models_.size())) return;
  ApplyTransformToModel(idx, AffineTransform::Translation(tx, ty, tz));
  NotifyObservers();
}

void Scene::RotateModel(int idx, double rx, double ry, double rz) {
  if (idx < 0 || idx >= static_cast<int>(models_.size())) return;
  auto m = AffineTransform::Multiply(
      AffineTransform::RotationZ(rz),
      AffineTransform::Multiply(AffineTransform::RotationY(ry),
                                AffineTransform::RotationX(rx)));
  ApplyTransformToModel(idx, m);
  NotifyObservers();
}

void Scene::ScaleModel(int idx, double sx, double sy, double sz) {
  if (idx < 0 || idx >= static_cast<int>(models_.size())) return;
  ApplyTransformToModel(idx, AffineTransform::Scale(sx, sy, sz));
  NotifyObservers();
}

void Scene::TranslateScene(double tx, double ty, double tz) {
  auto m = AffineTransform::Translation(tx, ty, tz);
  for (int i = 0; i < static_cast<int>(models_.size()); ++i)
    ApplyTransformToModel(i, m);
  NotifyObservers();
}

void Scene::RotateScene(double rx, double ry, double rz) {
  auto m = AffineTransform::Multiply(
      AffineTransform::RotationZ(rz),
      AffineTransform::Multiply(AffineTransform::RotationY(ry),
                                AffineTransform::RotationX(rx)));
  for (int i = 0; i < static_cast<int>(models_.size()); ++i)
    ApplyTransformToModel(i, m);
  NotifyObservers();
}

void Scene::ScaleScene(double sx, double sy, double sz) {
  auto m = AffineTransform::Scale(sx, sy, sz);
  for (int i = 0; i < static_cast<int>(models_.size()); ++i)
    ApplyTransformToModel(i, m);
  NotifyObservers();
}

void Scene::NotifyObservers() {
  for (auto* obs : observers_) obs->OnSceneChanged();
}

std::vector<ModelData> Scene::GetAllModelData() const {
  std::vector<ModelData> out;
  for (const auto& sm : models_) out.push_back(sm.data);
  return out;
}

std::vector<MaterialProperties> Scene::GetAllMaterials() const {
  std::vector<MaterialProperties> out;
  for (const auto& sm : models_) out.push_back(sm.material);
  return out;
}

void Scene::RebuildAnalyticCache() {
  analytic_cache_.clear();
  for (const auto& sm : models_) {
    if (sm.analytic_shape) {
      // clone by re-creating from type
      analytic_cache_.push_back(
          MakeAnalyticShape(sm.shape_type, {0,0,0}, 1.0, 2.0));
    }
  }
}

}  // namespace s21
