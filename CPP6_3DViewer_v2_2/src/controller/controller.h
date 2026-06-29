#pragma once
#include "../model/scene.h"
#include "../model/ray_tracer.h"
#include <cmath>
#include <string>
#include <functional>

namespace s21 {

// Design pattern: Strategy – render strategy can be swapped
class IRenderStrategy {
 public:
  virtual ~IRenderStrategy() = default;
  virtual PixelBuffer Render(
      Scene& scene,
      const RenderSettings& settings,
      std::function<void(int)> progress_cb) = 0;
};

class RayTraceStrategy : public IRenderStrategy {
 public:
  PixelBuffer Render(Scene& scene, const RenderSettings& settings,
                     std::function<void(int)> progress_cb) override;
};

// Controller – thin; delegates all logic to Scene/RayTracer
class Controller {
 public:
  explicit Controller(Scene* scene);

  // Model management
  bool LoadModel(const std::string& path);
  bool AddPrimitive(const std::string& type, Vec3 position,
                    double radius = 1.0, double height = 2.0);
  bool RemoveModel(int index);
  void SetActiveModel(int index);

  // Transforms on active model
  void TranslateActiveModel(double tx, double ty, double tz);
  void RotateActiveModel(double rx_deg, double ry_deg, double rz_deg);
  void ScaleActiveModel(double s);

  // Transforms on whole scene
  void TranslateScene(double tx, double ty, double tz);
  void RotateScene(double rx_deg, double ry_deg, double rz_deg);
  void ScaleScene(double s);

  // Rendering
  void SetRenderStrategy(std::unique_ptr<IRenderStrategy> strategy);
  void RenderToFile(const std::string& output_path,
                    const RenderSettings& settings,
                    std::function<void(int)> progress_cb,
                    std::function<void(const std::string&)> done_cb);

  // Settings
  void SetDisplayMode(DisplayMode mode);
  void SetProjectionType(ProjectionType type);
  void SetShowFloor(bool show);
  void SetModelMaterial(const MaterialProperties& mat);
  void SetSceneBackground(const Color& color);

  // Light setters
  void SetDirectionalLight(const DirectionalLight& light);
  void SetAmbientLight(const AmbientLight& ambient);
  bool AddPointLight(const PointLight& light);
  bool RemovePointLight(int index);

  Scene* GetScene() const { return scene_; }

 private:
  Scene* scene_;
  std::unique_ptr<IRenderStrategy> render_strategy_;

  static constexpr double kDegToRad = M_PI / 180.0;
};

}  // namespace s21
