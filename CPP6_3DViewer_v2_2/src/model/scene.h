#pragma once
#include "model_data.h"
#include "light.h"
#include "camera.h"
#include "geometric_objects.h"
#include "affine_transform.h"
#include <vector>
#include <memory>
#include <string>

namespace s21 {

constexpr int kMaxModels = 6;  // 1 base + 5 additional

// Design pattern: Command
class Command {
 public:
  virtual ~Command() = default;
  virtual void Execute() = 0;
  virtual void Undo() = 0;
};

struct SceneModel {
  ModelData data;
  MaterialProperties material;
  DisplayMode display_mode = DisplayMode::kFlatShading;
  Matrix4x4 transform = AffineTransform::Identity();
  std::unique_ptr<AnalyticShape> analytic_shape;  // set for primitives
  std::string shape_type;  // "obj", "sphere", "cylinder", etc.
};

// Design pattern: Observer (for MVC notification)
class SceneObserver {
 public:
  virtual ~SceneObserver() = default;
  virtual void OnSceneChanged() = 0;
};

// Design pattern: Facade
class Scene {
 public:
  Scene();

  // Model management
  bool LoadObjModel(const std::string& path);
  bool AddPrimitive(const std::string& type, Vec3 position,
                    double radius = 1.0, double height = 2.0);
  bool RemoveModel(int index);
  void SetActiveModel(int index);
  int  GetActiveModel() const { return active_model_index_; }
  int  GetModelCount() const { return static_cast<int>(models_.size()); }
  const SceneModel& GetModel(int index) const { return models_[index]; }
  SceneModel& GetModelMutable(int index) { return models_[index]; }

  // Affine transforms on a single model
  void TranslateModel(int index, double tx, double ty, double tz);
  void RotateModel(int index, double rx, double ry, double rz);
  void ScaleModel(int index, double sx, double sy, double sz);

  // Affine transforms on the whole scene (around origin)
  void TranslateScene(double tx, double ty, double tz);
  void RotateScene(double rx, double ry, double rz);
  void ScaleScene(double sx, double sy, double sz);

  // Lights
  LightManager& GetLightManager() { return light_manager_; }
  const LightManager& GetLightManager() const { return light_manager_; }

  // Camera
  Camera& GetCamera() { return camera_; }
  const Camera& GetCamera() const { return camera_; }

  // Settings
  SceneSettings& GetSettings() { return settings_; }
  const SceneSettings& GetSettings() const { return settings_; }

  // Observer
  void AddObserver(SceneObserver* obs) { observers_.push_back(obs); }
  void NotifyObservers();

  // All raw models for rendering
  std::vector<ModelData> GetAllModelData() const;
  std::vector<MaterialProperties> GetAllMaterials() const;
  std::vector<std::unique_ptr<AnalyticShape>>* GetAnalyticShapes() {
    return &analytic_cache_;
  }

 private:
  std::vector<SceneModel> models_;
  int active_model_index_ = 0;
  LightManager light_manager_;
  Camera camera_;
  SceneSettings settings_;
  std::vector<SceneObserver*> observers_;
  std::vector<std::unique_ptr<AnalyticShape>> analytic_cache_;

  void RebuildAnalyticCache();
  void ApplyTransformToModel(int index, const Matrix4x4& m);
};

}  // namespace s21
