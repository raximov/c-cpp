#include "gl_widget.h"
#include <QOpenGLFunctions_3_3_Core>
#include <cmath>

namespace s21 {

GlWidget::GlWidget(Scene& scene, QWidget* parent)
    : QOpenGLWidget(parent), scene_(scene) {
  setMinimumSize(400, 400);
}

GlWidget::~GlWidget() {
  makeCurrent();
  if (vao_) glDeleteVertexArrays(1, &vao_);
  if (vbo_) glDeleteBuffers(1, &vbo_);
  if (wire_vao_) glDeleteVertexArrays(1, &wire_vao_);
  if (wire_vbo_) glDeleteBuffers(1, &wire_vbo_);
  if (wire_ebo_) glDeleteBuffers(1, &wire_ebo_);
  doneCurrent();
}

void GlWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_PROGRAM_POINT_SIZE);
  BuildShaders(RenderMode::kWireframe);
}

void GlWidget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
}

void GlWidget::ReloadMesh() {
  makeCurrent();
  UploadMeshData();
  BuildShaders(scene_.GetShadingModel().GetStrategy()->GetMode());
  doneCurrent();
  update();
}

void GlWidget::BuildShaders(RenderMode mode) {
  auto* strategy = scene_.GetShadingModel().GetStrategy();
  current_built_mode_ = mode;

  prog_solid_ = std::make_unique<QOpenGLShaderProgram>();
  prog_solid_->addShaderFromSourceCode(QOpenGLShader::Vertex,
                                       strategy->GetVertexShader());
  prog_solid_->addShaderFromSourceCode(QOpenGLShader::Fragment,
                                       strategy->GetFragmentShader());
  prog_solid_->link();

  // Wireframe always needed for overlay / wireframe mode
  WireframeStrategy ws;
  prog_wire_ = std::make_unique<QOpenGLShaderProgram>();
  prog_wire_->addShaderFromSourceCode(QOpenGLShader::Vertex, ws.GetVertexShader());
  prog_wire_->addShaderFromSourceCode(QOpenGLShader::Fragment, ws.GetFragmentShader());
  prog_wire_->link();
}

void GlWidget::UploadMeshData() {
  const Mesh& mesh = scene_.GetMesh();

  // --- Solid buffer (interleaved: pos(3)+normal(3)+uv(2)) ---
  std::vector<float> solid_buf = mesh.BuildVertexBuffer();
  solid_vertex_count_ = solid_buf.size() / 8;

  if (!vao_) glGenVertexArrays(1, &vao_);
  if (!vbo_) glGenBuffers(1, &vbo_);
  glBindVertexArray(vao_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, solid_buf.size() * sizeof(float),
               solid_buf.data(), GL_STATIC_DRAW);
  // pos
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // normal
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  // uv
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);
  glBindVertexArray(0);

  // --- Wireframe buffer (raw vertex positions + line indices) ---
  std::vector<float> pos_buf;
  pos_buf.reserve(mesh.GetVertexCount() * 3);
  for (const auto& v : mesh.GetVertices()) {
    pos_buf.push_back(v.x);
    pos_buf.push_back(v.y);
    pos_buf.push_back(v.z);
  }
  raw_vertex_count_ = mesh.GetVertexCount();

  auto wire_idx = mesh.BuildWireframeIndexBuffer();
  wire_index_count_ = wire_idx.size();

  if (!wire_vao_) glGenVertexArrays(1, &wire_vao_);
  if (!wire_vbo_) glGenBuffers(1, &wire_vbo_);
  if (!wire_ebo_) glGenBuffers(1, &wire_ebo_);
  glBindVertexArray(wire_vao_);
  glBindBuffer(GL_ARRAY_BUFFER, wire_vbo_);
  glBufferData(GL_ARRAY_BUFFER, pos_buf.size() * sizeof(float),
               pos_buf.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, wire_ebo_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, wire_idx.size() * sizeof(unsigned int),
               wire_idx.data(), GL_STATIC_DRAW);
  glBindVertexArray(0);
}

QMatrix4x4 GlWidget::GetMVP() const {
  const auto& t = scene_.GetTransform();
  const auto& s = scene_.GetSettings();
  float aspect = width() / (float)std::max(height(), 1);

  // model matrix from transform
  Mat4 model_m = t.GetModelMatrix();
  QMatrix4x4 model(model_m.data());
  model = model.transposed();

  // view matrix (orbit camera)
  float az = cam_azimuth_ * M_PI / 180.f;
  float el = cam_elevation_ * M_PI / 180.f;
  Vec3 eye = {cam_distance_ * cos(el) * sin(az),
              cam_distance_ * sin(el),
              cam_distance_ * cos(el) * cos(az)};
  Mat4 view_m = MathUtils::LookAt(eye, {0,0,0}, {0,1,0});
  QMatrix4x4 view(view_m.data());
  view = view.transposed();

  QMatrix4x4 proj;
  if (s.projection == ProjectionType::kPerspective) {
    proj.perspective(45.0f, aspect, 0.01f, 100.f);
  } else {
    float half = cam_distance_ * 0.5f;
    proj.ortho(-half * aspect, half * aspect, -half, half, 0.01f, 100.f);
  }

  return proj * view * model;
}

void GlWidget::paintGL() {
  const auto& s = scene_.GetSettings();
  glClearColor(s.bg_r, s.bg_g, s.bg_b, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (!scene_.HasModel()) return;

  // Rebuild shaders if mode changed
  RenderMode cur_mode = scene_.GetShadingModel().GetStrategy()->GetMode();
  if (cur_mode != current_built_mode_) {
    BuildShaders(cur_mode);
  }

  if (cur_mode == RenderMode::kWireframe) {
    DrawWireframe();
  } else {
    DrawShaded();
    // Optional wireframe overlay could go here
  }
}

void GlWidget::DrawWireframe() {
  if (wire_index_count_ == 0) return;
  const auto& s = scene_.GetSettings();
  QMatrix4x4 mvp = GetMVP();

  prog_wire_->bind();
  prog_wire_->setUniformValue("uMVP", mvp);
  prog_wire_->setUniformValue("uColor",
    QVector4D(s.edge_r, s.edge_g, s.edge_b, 1.0f));

  glLineWidth(s.edge_width);
  if (s.dashed_edges) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0xAAAA);
  }

  glBindVertexArray(wire_vao_);
  glDrawElements(GL_LINES, static_cast<GLsizei>(wire_index_count_),
                 GL_UNSIGNED_INT, nullptr);
  glBindVertexArray(0);

  if (s.dashed_edges) glDisable(GL_LINE_STIPPLE);
  prog_wire_->release();

  // Vertex display
  if (s.vertex_display > 0 && solid_vertex_count_ > 0) {
    prog_wire_->bind();
    prog_wire_->setUniformValue("uMVP", mvp);
    prog_wire_->setUniformValue("uColor",
      QVector4D(s.vertex_r, s.vertex_g, s.vertex_b, 1.0f));
    glPointSize(s.vertex_size);
    glBindVertexArray(wire_vao_);
    glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(raw_vertex_count_));
    glBindVertexArray(0);
    prog_wire_->release();
  }
}

void GlWidget::DrawShaded() {
  if (solid_vertex_count_ == 0) return;
  const auto& s = scene_.GetSettings();
  const auto& l = scene_.GetLight();
  const auto& t = scene_.GetTransform();

  QMatrix4x4 mvp = GetMVP();
  Mat4 model_m = t.GetModelMatrix();
  QMatrix4x4 model(model_m.data());
  model = model.transposed();

  float az = cam_azimuth_ * M_PI / 180.f;
  float el = cam_elevation_ * M_PI / 180.f;
  QVector3D eye_pos(cam_distance_ * cos(el) * sin(az),
                    cam_distance_ * sin(el),
                    cam_distance_ * cos(el) * cos(az));

  prog_solid_->bind();
  prog_solid_->setUniformValue("uMVP", mvp);
  prog_solid_->setUniformValue("uModel", model);
  prog_solid_->setUniformValue("uLightPos", QVector3D(l.position[0], l.position[1], l.position[2]));
  prog_solid_->setUniformValue("uLightColor", QVector3D(l.r, l.g, l.b));
  prog_solid_->setUniformValue("uObjectColor", QVector3D(s.obj_r, s.obj_g, s.obj_b));
  prog_solid_->setUniformValue("uViewPos", eye_pos);
  prog_solid_->setUniformValue("uAmbient", l.ambient_strength);
  prog_solid_->setUniformValue("uSpecular", l.specular_strength);
  prog_solid_->setUniformValue("uShininess", l.shininess);

  glBindVertexArray(vao_);
  glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(solid_vertex_count_));
  glBindVertexArray(0);
  prog_solid_->release();
}

void GlWidget::mousePressEvent(QMouseEvent* e) {
  last_mouse_pos_ = e->pos();
}

void GlWidget::mouseMoveEvent(QMouseEvent* e) {
  if (e->buttons() & Qt::LeftButton) {
    QPoint delta = e->pos() - last_mouse_pos_;
    cam_azimuth_ += delta.x() * 0.5f;
    cam_elevation_ += delta.y() * 0.5f;
    cam_elevation_ = std::clamp(cam_elevation_, -89.0f, 89.0f);
    last_mouse_pos_ = e->pos();
    update();
  }
}

void GlWidget::wheelEvent(QWheelEvent* e) {
  cam_distance_ -= e->angleDelta().y() * 0.01f;
  cam_distance_ = std::clamp(cam_distance_, 0.1f, 100.0f);
  update();
}

}  // namespace s21
