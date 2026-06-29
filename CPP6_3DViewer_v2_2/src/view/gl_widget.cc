#include "gl_widget.h"
#include <QMouseEvent>
#include <QWheelEvent>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>

namespace s21 {

GlWidget::GlWidget(Scene* scene, QWidget* parent)
    : QOpenGLWidget(parent), scene_(scene) {
  scene_->AddObserver(this);
}

void GlWidget::OnSceneChanged() {
  update();
}

void GlWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glShadeModel(GL_SMOOTH);
}

void GlWidget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  SetupProjection(w, h);
}

void GlWidget::SetupProjection(int w, int h) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  double aspect = (h > 0) ? static_cast<double>(w) / h : 1.0;
  if (scene_->GetCamera().GetProjection() == ProjectionType::kCentral) {
    gluPerspective(60.0, aspect, 0.01, 1000.0);
  } else {
    double s = cam_dist_;
    glOrtho(-s*aspect, s*aspect, -s, s, -1000, 1000);
  }
  glMatrixMode(GL_MODELVIEW);
}

void GlWidget::paintGL() {
  const auto& bg = scene_->GetSettings().background_color;
  glClearColor(bg.r, bg.g, bg.b, bg.a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();

  // Orbit camera
  double rad_pitch = cam_pitch_ * M_PI / 180.0;
  double rad_yaw   = cam_yaw_   * M_PI / 180.0;
  double cx = cam_dist_ * std::cos(rad_pitch) * std::sin(rad_yaw);
  double cy = cam_dist_ * std::sin(rad_pitch);
  double cz = cam_dist_ * std::cos(rad_pitch) * std::cos(rad_yaw);
  gluLookAt(cx, cy, cz, 0, 0, 0, 0, 1, 0);

  SetupLights();

  // Draw floor
  if (scene_->GetSettings().show_floor) DrawFloor();

  // Draw models
  for (int i = 0; i < scene_->GetModelCount(); ++i) {
    DrawModel(scene_->GetModel(i));
  }
}

void GlWidget::SetupLights() {
  const auto& dl = scene_->GetLightManager().GetDirectional();
  GLfloat pos[] = {static_cast<float>(dl.position.x),
                   static_cast<float>(dl.position.y),
                   static_cast<float>(dl.position.z), 0.0f};
  GLfloat diff[] = {dl.color.r * dl.intensity,
                    dl.color.g * dl.intensity,
                    dl.color.b * dl.intensity, 1.0f};
  glLightfv(GL_LIGHT0, GL_POSITION, pos);
  glLightfv(GL_LIGHT0, GL_DIFFUSE,  diff);

  const auto& amb = scene_->GetLightManager().GetAmbient();
  GLfloat ambc[] = {amb.color.r * amb.intensity,
                    amb.color.g * amb.intensity,
                    amb.color.b * amb.intensity, 1.0f};
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambc);

  // Point lights (GL_LIGHT1 .. GL_LIGHT5)
  const auto& pts = scene_->GetLightManager().GetPointLights();
  for (int i = 0; i < static_cast<int>(pts.size()) && i < 5; ++i) {
    GLenum light = GL_LIGHT1 + i;
    glEnable(light);
    GLfloat ppos[] = {static_cast<float>(pts[i].position.x),
                      static_cast<float>(pts[i].position.y),
                      static_cast<float>(pts[i].position.z), 1.0f};
    GLfloat pdiff[] = {pts[i].color.r * pts[i].intensity,
                       pts[i].color.g * pts[i].intensity,
                       pts[i].color.b * pts[i].intensity, 1.0f};
    glLightfv(light, GL_POSITION, ppos);
    glLightfv(light, GL_DIFFUSE,  pdiff);
  }
}

void GlWidget::DrawModel(const SceneModel& sm) {
  const auto& mat = sm.material;
  glColor4f(mat.base_color.r, mat.base_color.g,
            mat.base_color.b, mat.base_color.a);

  if (sm.display_mode == DisplayMode::kWireframe) {
    glDisable(GL_LIGHTING);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  } else {
    glEnable(GL_LIGHTING);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if (sm.display_mode == DisplayMode::kGouraudShading ||
        sm.display_mode == DisplayMode::kPhongShading) {
      glShadeModel(GL_SMOOTH);
    } else {
      glShadeModel(GL_FLAT);
    }
  }

  const auto& data = sm.data;
  for (const auto& face : data.faces) {
    int n = static_cast<int>(face.vertex_indices.size());
    if (n < 3) continue;
    glBegin((n == 3) ? GL_TRIANGLES : (n == 4) ? GL_QUADS : GL_POLYGON);
    for (int i = 0; i < n; ++i) {
      int vi = face.vertex_indices[i];
      if (!face.normal_indices.empty() &&
          i < static_cast<int>(face.normal_indices.size())) {
        int ni = face.normal_indices[i];
        if (ni >= 0 && ni < static_cast<int>(data.normals.size())) {
          const auto& nrm = data.normals[ni];
          glNormal3d(nrm.x, nrm.y, nrm.z);
        }
      }
      if (vi >= 0 && vi < static_cast<int>(data.vertices.size())) {
        const auto& v = data.vertices[vi];
        glVertex3d(v.x, v.y, v.z);
      }
    }
    glEnd();
  }

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glEnable(GL_LIGHTING);
}

void GlWidget::DrawFloor() {
  glDisable(GL_LIGHTING);
  glColor3f(0.3f, 0.3f, 0.3f);
  float s = 10.0f;
  glBegin(GL_LINES);
  for (float i = -s; i <= s; i += 1.0f) {
    glVertex3f(i, -0.01f, -s); glVertex3f(i, -0.01f,  s);
    glVertex3f(-s, -0.01f, i); glVertex3f( s, -0.01f, i);
  }
  glEnd();
  glEnable(GL_LIGHTING);
}

void GlWidget::mousePressEvent(QMouseEvent* event) {
  last_mouse_pos_ = event->pos();
}

void GlWidget::mouseMoveEvent(QMouseEvent* event) {
  auto delta = event->pos() - last_mouse_pos_;
  last_mouse_pos_ = event->pos();
  cam_yaw_   += delta.x() * 0.5f;
  cam_pitch_ += delta.y() * 0.5f;
  cam_pitch_ = std::clamp(cam_pitch_, -89.0f, 89.0f);
  update();
}

void GlWidget::wheelEvent(QWheelEvent* event) {
  cam_dist_ -= event->angleDelta().y() * 0.01f;
  cam_dist_ = std::clamp(cam_dist_, 0.5f, 100.0f);
  update();
}

}  // namespace s21
