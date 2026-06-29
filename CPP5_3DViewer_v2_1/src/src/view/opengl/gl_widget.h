#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QWheelEvent>
#include <memory>
#include "../../model/scene.h"

namespace s21 {

class GlWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core {
  Q_OBJECT
 public:
  explicit GlWidget(Scene& scene, QWidget* parent = nullptr);
  ~GlWidget() override;

  void ReloadMesh();

 protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;
  void mousePressEvent(QMouseEvent* e) override;
  void mouseMoveEvent(QMouseEvent* e) override;
  void wheelEvent(QWheelEvent* e) override;

 private:
  void BuildShaders(RenderMode mode);
  void UploadMeshData();
  void DrawWireframe();
  void DrawShaded();
  void SetLightUniforms(QOpenGLShaderProgram* prog);
  QMatrix4x4 GetMVP() const;

  Scene& scene_;

  GLuint vao_{0}, vbo_{0};
  GLuint wire_vao_{0}, wire_vbo_{0}, wire_ebo_{0};

  std::unique_ptr<QOpenGLShaderProgram> prog_solid_;
  std::unique_ptr<QOpenGLShaderProgram> prog_wire_;

  RenderMode current_built_mode_{RenderMode::kWireframe};
  size_t solid_vertex_count_{0};
  size_t wire_index_count_{0};
  size_t raw_vertex_count_{0};

  // Camera
  float cam_distance_{5.0f};
  float cam_azimuth_{0.0f};
  float cam_elevation_{20.0f};
  QPoint last_mouse_pos_;
};

}  // namespace s21
