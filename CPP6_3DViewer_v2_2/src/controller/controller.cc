#include "controller.h"
#include <thread>
#include <filesystem>

namespace s21 {

// ---- RayTraceStrategy ------------------------------------------------------

PixelBuffer RayTraceStrategy::Render(Scene& scene,
                                      const RenderSettings& settings,
                                      std::function<void(int)> progress_cb) {
  RayTracer tracer;
  auto models    = scene.GetAllModelData();
  auto materials = scene.GetAllMaterials();
  // analytic shapes
  std::vector<std::unique_ptr<AnalyticShape>> analytic;
  for (int i = 0; i < scene.GetModelCount(); ++i) {
    const auto& sm = scene.GetModel(i);
    if (!sm.shape_type.empty() && sm.shape_type != "obj") {
      analytic.push_back(
          MakeAnalyticShape(sm.shape_type, {0, 0, 0}, 1.0, 2.0));
    }
  }
  return tracer.Render(models, materials, analytic,
                        scene.GetLightManager(), scene.GetCamera(),
                        settings, progress_cb);
}

// ---- Controller ------------------------------------------------------------

Controller::Controller(Scene* scene)
    : scene_(scene),
      render_strategy_(std::make_unique<RayTraceStrategy>()) {}

bool Controller::LoadModel(const std::string& path) {
  return scene_->LoadObjModel(path);
}

bool Controller::AddPrimitive(const std::string& type, Vec3 position,
                               double radius, double height) {
  return scene_->AddPrimitive(type, position, radius, height);
}

bool Controller::RemoveModel(int index) {
  return scene_->RemoveModel(index);
}

void Controller::SetActiveModel(int index) {
  scene_->SetActiveModel(index);
}

void Controller::TranslateActiveModel(double tx, double ty, double tz) {
  scene_->TranslateModel(scene_->GetActiveModel(), tx, ty, tz);
}

void Controller::RotateActiveModel(double rx, double ry, double rz) {
  scene_->RotateModel(scene_->GetActiveModel(),
                       rx * kDegToRad, ry * kDegToRad, rz * kDegToRad);
}

void Controller::ScaleActiveModel(double s) {
  scene_->ScaleModel(scene_->GetActiveModel(), s, s, s);
}

void Controller::TranslateScene(double tx, double ty, double tz) {
  scene_->TranslateScene(tx, ty, tz);
}

void Controller::RotateScene(double rx, double ry, double rz) {
  scene_->RotateScene(rx * kDegToRad, ry * kDegToRad, rz * kDegToRad);
}

void Controller::ScaleScene(double s) {
  scene_->ScaleScene(s, s, s);
}

void Controller::SetRenderStrategy(std::unique_ptr<IRenderStrategy> strategy) {
  render_strategy_ = std::move(strategy);
}

void Controller::RenderToFile(const std::string& output_path,
                               const RenderSettings& settings,
                               std::function<void(int)> progress_cb,
                               std::function<void(const std::string&)> done_cb) {
  // Run in background thread so GUI stays responsive
  std::thread([this, output_path, settings, progress_cb, done_cb]() {
    PixelBuffer buf = render_strategy_->Render(*scene_, settings, progress_cb);
    bool ok = SaveImage(buf, settings.width, settings.height, output_path);
    if (done_cb) done_cb(ok ? output_path : "");
  }).detach();
}

void Controller::SetDisplayMode(DisplayMode mode) {
  int idx = scene_->GetActiveModel();
  if (idx >= 0 && idx < scene_->GetModelCount())
    scene_->GetModelMutable(idx).display_mode = mode;
  scene_->NotifyObservers();
}

void Controller::SetProjectionType(ProjectionType type) {
  scene_->GetCamera().SetProjection(type);
  scene_->NotifyObservers();
}

void Controller::SetShowFloor(bool show) {
  scene_->GetSettings().show_floor = show;
  scene_->NotifyObservers();
}

void Controller::SetModelMaterial(const MaterialProperties& mat) {
  int idx = scene_->GetActiveModel();
  if (idx >= 0 && idx < scene_->GetModelCount())
    scene_->GetModelMutable(idx).material = mat;
  scene_->NotifyObservers();
}

void Controller::SetSceneBackground(const Color& color) {
  scene_->GetSettings().background_color = color;
  scene_->NotifyObservers();
}

void Controller::SetDirectionalLight(const DirectionalLight& light) {
  scene_->GetLightManager().SetDirectional(light);
  scene_->NotifyObservers();
}

void Controller::SetAmbientLight(const AmbientLight& ambient) {
  scene_->GetLightManager().SetAmbient(ambient);
  scene_->NotifyObservers();
}

bool Controller::AddPointLight(const PointLight& light) {
  bool ok = scene_->GetLightManager().AddPointLight(light);
  if (ok) scene_->NotifyObservers();
  return ok;
}

bool Controller::RemovePointLight(int index) {
  bool ok = scene_->GetLightManager().RemovePointLight(index);
  if (ok) scene_->NotifyObservers();
  return ok;
}

}  // namespace s21
