#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include "../model/scene.h"

namespace s21 {

class GlWidget : public QOpenGLWidget,
                 protected QOpenGLFunctions,
                 public SceneObserver {
  Q_OBJECT
 public:
  explicit GlWidget(Scene* scene, QWidget* parent = nullptr);

  // SceneObserver
  void OnSceneChanged() override;

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void wheelEvent(QWheelEvent* event) override;

 private:
  void DrawModel(const SceneModel& sm);
  void DrawFloor();
  void SetupLights();
  void SetupProjection(int w, int h);

  Scene* scene_;
  QPoint last_mouse_pos_;
  float cam_yaw_   = 0.0f;
  float cam_pitch_ = 20.0f;
  float cam_dist_  = 5.0f;
};

}  // namespace s21
