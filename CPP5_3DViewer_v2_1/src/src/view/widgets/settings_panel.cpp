#include "settings_panel.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QColorDialog>

namespace s21 {

static QPushButton* ColorButton(const QString& label) {
  auto* btn = new QPushButton(label);
  btn->setFixedWidth(100);
  return btn;
}

SettingsPanel::SettingsPanel(SceneController& ctrl, QWidget* parent)
    : QWidget(parent), ctrl_(ctrl) {
  auto* vl = new QVBoxLayout(this);

  // Render mode
  auto* rbox = new QGroupBox("Rendering");
  auto* rfl = new QFormLayout(rbox);
  render_combo_ = new QComboBox;
  render_combo_->addItems({"Wireframe", "Flat Shading", "Gouraud", "Phong"});
  proj_combo_ = new QComboBox;
  proj_combo_->addItems({"Perspective", "Orthographic"});
  rfl->addRow("Mode:", render_combo_);
  rfl->addRow("Projection:", proj_combo_);
  vl->addWidget(rbox);

  // Edge settings
  auto* ebox = new QGroupBox("Edges");
  auto* efl = new QFormLayout(ebox);
  dashed_cb_ = new QCheckBox("Dashed");
  edge_width_ = new QDoubleSpinBox;
  edge_width_->setRange(0.5, 10); edge_width_->setValue(1.0); edge_width_->setSingleStep(0.5);
  auto* edge_col_btn = ColorButton("Edge Color");
  efl->addRow(dashed_cb_);
  efl->addRow("Width:", edge_width_);
  efl->addRow("Color:", edge_col_btn);
  vl->addWidget(ebox);

  // Vertex settings
  auto* vbox = new QGroupBox("Vertices");
  auto* vfl = new QFormLayout(vbox);
  vertex_display_ = new QComboBox;
  vertex_display_->addItems({"None", "Circle", "Square"});
  vertex_size_ = new QDoubleSpinBox;
  vertex_size_->setRange(1, 20); vertex_size_->setValue(5);
  auto* vtx_col_btn = ColorButton("Vertex Color");
  vfl->addRow("Display:", vertex_display_);
  vfl->addRow("Size:", vertex_size_);
  vfl->addRow("Color:", vtx_col_btn);
  vl->addWidget(vbox);

  // Colors
  auto* cbox = new QGroupBox("Colors");
  auto* cfl = new QFormLayout(cbox);
  auto* obj_col_btn = ColorButton("Object Color");
  auto* bg_col_btn  = ColorButton("Background");
  cfl->addRow("Object:", obj_col_btn);
  cfl->addRow("Background:", bg_col_btn);
  vl->addWidget(cbox);

  // Light
  auto* lbox = new QGroupBox("Light Source");
  auto* lfl = new QFormLayout(lbox);
  light_x_ = new QDoubleSpinBox; light_x_->setRange(-50,50); light_x_->setValue(0);
  light_y_ = new QDoubleSpinBox; light_y_->setRange(-50,50); light_y_->setValue(5);
  light_z_ = new QDoubleSpinBox; light_z_->setRange(-50,50); light_z_->setValue(5);
  ambient_  = new QDoubleSpinBox; ambient_->setRange(0,1); ambient_->setValue(0.2); ambient_->setSingleStep(0.05);
  specular_ = new QDoubleSpinBox; specular_->setRange(0,1); specular_->setValue(0.5); specular_->setSingleStep(0.05);
  shininess_ = new QSpinBox; shininess_->setRange(1, 256); shininess_->setValue(32);
  auto* lc_btn = ColorButton("Light Color");
  auto* lpos_row = new QHBoxLayout;
  lpos_row->addWidget(light_x_); lpos_row->addWidget(light_y_); lpos_row->addWidget(light_z_);
  lfl->addRow("Position:", lpos_row);
  lfl->addRow("Ambient:", ambient_);
  lfl->addRow("Specular:", specular_);
  lfl->addRow("Shininess:", shininess_);
  lfl->addRow("Color:", lc_btn);
  vl->addWidget(lbox);

  vl->addStretch();

  // Connections
  connect(render_combo_, &QComboBox::currentIndexChanged, this, &SettingsPanel::OnRenderModeChanged);
  connect(proj_combo_, &QComboBox::currentIndexChanged, this, &SettingsPanel::OnProjectionChanged);

  auto push = [this](auto) { PushAll(); emit SettingsChanged(); };
  connect(dashed_cb_, &QCheckBox::toggled, push);
  connect(edge_width_, &QDoubleSpinBox::valueChanged, push);
  connect(vertex_display_, &QComboBox::currentIndexChanged, push);
  connect(vertex_size_, &QDoubleSpinBox::valueChanged, push);
  connect(light_x_, &QDoubleSpinBox::valueChanged, push);
  connect(light_y_, &QDoubleSpinBox::valueChanged, push);
  connect(light_z_, &QDoubleSpinBox::valueChanged, push);
  connect(ambient_, &QDoubleSpinBox::valueChanged, push);
  connect(specular_, &QDoubleSpinBox::valueChanged, push);
  connect(shininess_, &QSpinBox::valueChanged, push);

  connect(edge_col_btn,  &QPushButton::clicked, this, &SettingsPanel::OnPickEdgeColor);
  connect(vtx_col_btn,   &QPushButton::clicked, this, &SettingsPanel::OnPickVertexColor);
  connect(obj_col_btn,   &QPushButton::clicked, this, &SettingsPanel::OnPickObjectColor);
  connect(bg_col_btn,    &QPushButton::clicked, this, &SettingsPanel::OnPickBgColor);
  connect(lc_btn,        &QPushButton::clicked, this, &SettingsPanel::OnLightColorPick);
}

void SettingsPanel::LoadFromScene() {
  const auto& s = ctrl_.GetScene().GetSettings();
  QSignalBlocker b1(render_combo_), b2(proj_combo_);
  render_combo_->setCurrentIndex(static_cast<int>(s.render_mode));
  proj_combo_->setCurrentIndex(static_cast<int>(s.projection));
  dashed_cb_->setChecked(s.dashed_edges);
  edge_width_->setValue(s.edge_width);
  vertex_display_->setCurrentIndex(s.vertex_display);
  vertex_size_->setValue(s.vertex_size);
  edge_r_ = s.edge_r; edge_g_ = s.edge_g; edge_b_ = s.edge_b;
  vertex_r_ = s.vertex_r; vertex_g_ = s.vertex_g; vertex_b_ = s.vertex_b;
  obj_r_ = s.obj_r; obj_g_ = s.obj_g; obj_b_ = s.obj_b;
  bg_r_ = s.bg_r; bg_g_ = s.bg_g; bg_b_ = s.bg_b;
  const auto& l = ctrl_.GetScene().GetLight();
  light_x_->setValue(l.position[0]);
  light_y_->setValue(l.position[1]);
  light_z_->setValue(l.position[2]);
  ambient_->setValue(l.ambient_strength);
  specular_->setValue(l.specular_strength);
  shininess_->setValue(l.shininess);
  light_r_ = l.r; light_g_ = l.g; light_b_ = l.b;
}

void SettingsPanel::PushAll() {
  ctrl_.SetEdgeSettings(dashed_cb_->isChecked(), edge_r_, edge_g_, edge_b_,
                        edge_width_->value());
  ctrl_.SetVertexSettings(vertex_display_->currentIndex(),
                          vertex_r_, vertex_g_, vertex_b_, vertex_size_->value());
  ctrl_.SetObjectColor(obj_r_, obj_g_, obj_b_);
  ctrl_.SetBackgroundColor(bg_r_, bg_g_, bg_b_);
  ctrl_.SetLightPosition(light_x_->value(), light_y_->value(), light_z_->value());
  ctrl_.SetAmbientStrength(ambient_->value());
  ctrl_.SetSpecularStrength(specular_->value());
  ctrl_.SetShininess(shininess_->value());
  ctrl_.SetLightColor(light_r_, light_g_, light_b_);
  ctrl_.SaveSettings();
}

void SettingsPanel::OnRenderModeChanged(int idx) {
  ctrl_.SetRenderMode(static_cast<RenderMode>(idx));
  emit SettingsChanged();
}

void SettingsPanel::OnProjectionChanged(int idx) {
  ctrl_.SetProjection(static_cast<ProjectionType>(idx));
  emit SettingsChanged();
}

static void PickColor(float& r, float& g, float& b, QWidget* parent) {
  QColor c = QColorDialog::getColor(
    QColor::fromRgbF(r, g, b), parent);
  if (c.isValid()) { r = c.redF(); g = c.greenF(); b = c.blueF(); }
}

void SettingsPanel::OnPickEdgeColor() {
  PickColor(edge_r_, edge_g_, edge_b_, this);
  PushAll(); emit SettingsChanged();
}
void SettingsPanel::OnPickVertexColor() {
  PickColor(vertex_r_, vertex_g_, vertex_b_, this);
  PushAll(); emit SettingsChanged();
}
void SettingsPanel::OnPickObjectColor() {
  PickColor(obj_r_, obj_g_, obj_b_, this);
  PushAll(); emit SettingsChanged();
}
void SettingsPanel::OnPickBgColor() {
  PickColor(bg_r_, bg_g_, bg_b_, this);
  PushAll(); emit SettingsChanged();
}
void SettingsPanel::OnLightColorPick() {
  PickColor(light_r_, light_g_, light_b_, this);
  PushAll(); emit SettingsChanged();
}

}  // namespace s21
