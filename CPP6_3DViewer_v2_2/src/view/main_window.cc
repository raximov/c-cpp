#include "main_window.h"
#include <QFileDialog>
#include <QInputDialog>
#include <QColorDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QSplitter>
#include <QTabWidget>
#include <QMessageBox>
#include <QStatusBar>
#include <QMenuBar>
#include <QAction>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QFormLayout>

namespace s21 {

static QDoubleSpinBox* MakeSpin(double min, double max, double step,
                                 double val = 0.0) {
  auto* sb = new QDoubleSpinBox();
  sb->setRange(min, max);
  sb->setSingleStep(step);
  sb->setValue(val);
  return sb;
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), controller_(&scene_) {
  settings_ = new QSettings("s21", "3DViewer22", this);
  setWindowTitle("3DViewer v2.2");
  resize(1280, 800);
  BuildUI();
  LoadSettings();
}

MainWindow::~MainWindow() {
  SaveSettings();
}

void MainWindow::BuildUI() {
  auto* central = new QWidget(this);
  setCentralWidget(central);
  auto* main_layout = new QHBoxLayout(central);

  // Left panel (controls)
  auto* tabs = new QTabWidget();
  tabs->setFixedWidth(340);
  tabs->addTab(BuildModelPanel(),     "Models");
  tabs->addTab(BuildTransformPanel(), "Transform");
  tabs->addTab(BuildLightPanel(),     "Lights");
  tabs->addTab(BuildMaterialPanel(),  "Material");
  tabs->addTab(BuildRenderPanel(),    "Render");
  tabs->addTab(BuildSettingsPanel(),  "Settings");

  // GL widget (right)
  gl_widget_ = new GlWidget(&scene_, this);

  auto* splitter = new QSplitter(Qt::Horizontal);
  splitter->addWidget(tabs);
  splitter->addWidget(gl_widget_);
  splitter->setStretchFactor(1, 3);
  main_layout->addWidget(splitter);

  statusBar()->showMessage("Ready");
}

// ---- Model panel -----------------------------------------------------------

QWidget* MainWindow::BuildModelPanel() {
  auto* w = new QWidget();
  auto* layout = new QVBoxLayout(w);

  auto* load_btn = new QPushButton("Load OBJ File…");
  connect(load_btn, &QPushButton::clicked, this, &MainWindow::OnLoadModel);
  layout->addWidget(load_btn);

  // Primitive selector
  auto* prim_group = new QGroupBox("Add Primitive");
  auto* prim_layout = new QHBoxLayout(prim_group);
  auto* prim_cb = new QComboBox();
  prim_cb->addItems({"Sphere", "Cylinder", "Cone", "Cube", "Pyramid"});
  prim_layout->addWidget(prim_cb);
  auto* add_prim = new QPushButton("Add");
  connect(add_prim, &QPushButton::clicked, [this, prim_cb]() {
    controller_.AddPrimitive(prim_cb->currentText().toStdString(), {0,0,0});
    UpdateModelInfo();
  });
  prim_layout->addWidget(add_prim);
  layout->addWidget(prim_group);

  // Model list
  model_list_ = new QListWidget();
  connect(model_list_, &QListWidget::currentRowChanged,
          this, &MainWindow::OnModelSelected);
  layout->addWidget(model_list_);

  auto* remove_btn = new QPushButton("Remove Selected");
  connect(remove_btn, &QPushButton::clicked, this, &MainWindow::OnRemoveModel);
  layout->addWidget(remove_btn);

  model_info_label_ = new QLabel("No model loaded");
  model_info_label_->setWordWrap(true);
  layout->addWidget(model_info_label_);
  layout->addStretch();
  return w;
}

// ---- Transform panel -------------------------------------------------------

QWidget* MainWindow::BuildTransformPanel() {
  auto* w = new QWidget();
  auto* layout = new QVBoxLayout(w);

  auto MakeXYZ = [&](const QString& label,
                      QDoubleSpinBox*& x, QDoubleSpinBox*& y,
                      QDoubleSpinBox*& z, double rng, double step) {
    auto* g = new QGroupBox(label);
    auto* fl = new QFormLayout(g);
    x = MakeSpin(-rng, rng, step);
    y = MakeSpin(-rng, rng, step);
    z = MakeSpin(-rng, rng, step);
    fl->addRow("X:", x); fl->addRow("Y:", y); fl->addRow("Z:", z);
    return g;
  };

  layout->addWidget(new QLabel("<b>Active Model</b>"));
  layout->addWidget(MakeXYZ("Translate", tx_, ty_, tz_, 100, 0.1));
  auto* t_btn = new QPushButton("Apply Translate");
  connect(t_btn, &QPushButton::clicked, this, &MainWindow::OnTranslate);
  layout->addWidget(t_btn);

  layout->addWidget(MakeXYZ("Rotate (°)", rx_, ry_, rz_, 360, 1.0));
  auto* r_btn = new QPushButton("Apply Rotate");
  connect(r_btn, &QPushButton::clicked, this, &MainWindow::OnRotate);
  layout->addWidget(r_btn);

  auto* sg = new QGroupBox("Scale");
  auto* sf = new QFormLayout(sg);
  scale_val_ = MakeSpin(0.001, 1000, 0.1, 1.0);
  sf->addRow("Scale:", scale_val_);
  layout->addWidget(sg);
  auto* sc_btn = new QPushButton("Apply Scale");
  connect(sc_btn, &QPushButton::clicked, this, &MainWindow::OnScale);
  layout->addWidget(sc_btn);

  layout->addWidget(new QLabel("<b>Whole Scene</b>"));
  layout->addWidget(MakeXYZ("Scene Translate", stx_, sty_, stz_, 100, 0.1));
  auto* st_btn = new QPushButton("Apply Scene Translate");
  connect(st_btn, &QPushButton::clicked, this, &MainWindow::OnTranslateScene);
  layout->addWidget(st_btn);

  layout->addWidget(MakeXYZ("Scene Rotate (°)", srx_, sry_, srz_, 360, 1.0));
  auto* sr_btn = new QPushButton("Apply Scene Rotate");
  connect(sr_btn, &QPushButton::clicked, this, &MainWindow::OnRotateScene);
  layout->addWidget(sr_btn);

  auto* ssg = new QGroupBox("Scene Scale");
  auto* ssf = new QFormLayout(ssg);
  s_scale_ = MakeSpin(0.001, 1000, 0.1, 1.0);
  ssf->addRow("Scale:", s_scale_);
  layout->addWidget(ssg);
  auto* ssc_btn = new QPushButton("Apply Scene Scale");
  connect(ssc_btn, &QPushButton::clicked, this, &MainWindow::OnScaleScene);
  layout->addWidget(ssc_btn);

  layout->addStretch();
  auto* scroll = new QScrollArea();
  scroll->setWidget(w);
  scroll->setWidgetResizable(true);
  return scroll;
}

// ---- Light panel -----------------------------------------------------------

QWidget* MainWindow::BuildLightPanel() {
  auto* w = new QWidget();
  auto* layout = new QVBoxLayout(w);

  auto* dg = new QGroupBox("Directional Light");
  auto* df = new QFormLayout(dg);
  dl_x_ = MakeSpin(-100, 100, 0.5, 5);
  dl_y_ = MakeSpin(-100, 100, 0.5, 10);
  dl_z_ = MakeSpin(-100, 100, 0.5, 10);
  dl_intensity_ = MakeSpin(0, 10, 0.1, 1.0);
  df->addRow("X:", dl_x_); df->addRow("Y:", dl_y_); df->addRow("Z:", dl_z_);
  df->addRow("Intensity:", dl_intensity_);
  auto* dl_btn = new QPushButton("Apply Directional");
  connect(dl_btn, &QPushButton::clicked, this, &MainWindow::OnDirectionalLightChanged);
  df->addRow(dl_btn);
  layout->addWidget(dg);

  auto* ag = new QGroupBox("Ambient Light");
  auto* af = new QFormLayout(ag);
  amb_intensity_ = MakeSpin(0, 2, 0.05, 0.2);
  af->addRow("Intensity:", amb_intensity_);
  auto* amb_btn = new QPushButton("Apply Ambient");
  connect(amb_btn, &QPushButton::clicked, [this]() {
    AmbientLight a;
    a.intensity = static_cast<float>(amb_intensity_->value());
    controller_.SetAmbientLight(a);
  });
  af->addRow(amb_btn);
  layout->addWidget(ag);

  auto* pg = new QGroupBox("Point Lights (max 5)");
  auto* pf = new QVBoxLayout(pg);
  auto* add_pt = new QPushButton("Add Point Light at (0,3,3)");
  connect(add_pt, &QPushButton::clicked, this, &MainWindow::OnAddPointLight);
  auto* rem_pt = new QPushButton("Remove Last Point Light");
  connect(rem_pt, &QPushButton::clicked, this, &MainWindow::OnRemovePointLight);
  pf->addWidget(add_pt); pf->addWidget(rem_pt);
  layout->addWidget(pg);

  layout->addStretch();
  return w;
}

// ---- Material panel --------------------------------------------------------

QWidget* MainWindow::BuildMaterialPanel() {
  auto* w = new QWidget();
  auto* layout = new QVBoxLayout(w);

  auto* g = new QGroupBox("Material Properties");
  auto* f = new QFormLayout(g);
  mat_transp_ = MakeSpin(0, 1, 0.05);
  mat_refr_   = MakeSpin(1, 3, 0.05, 1.0);
  mat_refl_   = MakeSpin(0, 1, 0.05);
  mat_rough_  = MakeSpin(0, 1, 0.05, 0.5);
  f->addRow("Transparency:", mat_transp_);
  f->addRow("Refraction Index:", mat_refr_);
  f->addRow("Reflectivity:", mat_refl_);
  f->addRow("Roughness:", mat_rough_);

  auto* color_btn = new QPushButton("Model Color…");
  connect(color_btn, &QPushButton::clicked, this, &MainWindow::OnModelColorPick);
  f->addRow(color_btn);

  auto* apply_btn = new QPushButton("Apply Material");
  connect(apply_btn, &QPushButton::clicked, this, &MainWindow::OnMaterialChanged);
  f->addRow(apply_btn);
  layout->addWidget(g);

  layout->addStretch();
  return w;
}

// ---- Render panel ----------------------------------------------------------

QWidget* MainWindow::BuildRenderPanel() {
  auto* w = new QWidget();
  auto* layout = new QVBoxLayout(w);

  auto* rg = new QGroupBox("Ray Trace Render");
  auto* rf = new QFormLayout(rg);
  render_w_ = MakeSpin(64, 1920, 1, 1280);
  render_h_ = MakeSpin(64, 1440, 1, 720);
  rf->addRow("Width:", render_w_);
  rf->addRow("Height:", render_h_);

  auto* render_btn = new QPushButton("Render to File…");
  connect(render_btn, &QPushButton::clicked, this, &MainWindow::OnRender);
  rf->addRow(render_btn);
  layout->addWidget(rg);

  layout->addStretch();
  return w;
}

// ---- Settings panel --------------------------------------------------------

QWidget* MainWindow::BuildSettingsPanel() {
  auto* w = new QWidget();
  auto* layout = new QVBoxLayout(w);

  display_mode_cb_ = new QComboBox();
  display_mode_cb_->addItems({"Wireframe", "Flat Shading",
                               "Gouraud Shading", "Phong Shading"});
  connect(display_mode_cb_, qOverload<int>(&QComboBox::currentIndexChanged),
          this, &MainWindow::OnDisplayModeChanged);
  layout->addWidget(new QLabel("Display Mode:"));
  layout->addWidget(display_mode_cb_);

  projection_cb_ = new QComboBox();
  projection_cb_->addItems({"Central (Perspective)", "Parallel (Ortho)"});
  connect(projection_cb_, qOverload<int>(&QComboBox::currentIndexChanged),
          this, &MainWindow::OnProjectionChanged);
  layout->addWidget(new QLabel("Projection:"));
  layout->addWidget(projection_cb_);

  floor_cb_ = new QCheckBox("Show Floor");
  floor_cb_->setChecked(true);
  connect(floor_cb_, &QCheckBox::toggled, this, &MainWindow::OnToggleFloor);
  layout->addWidget(floor_cb_);

  auto* bg_btn = new QPushButton("Background Color…");
  connect(bg_btn, &QPushButton::clicked, this, &MainWindow::OnBackgroundColorPick);
  layout->addWidget(bg_btn);

  layout->addStretch();
  return w;
}

// ---- Slot implementations --------------------------------------------------

void MainWindow::OnLoadModel() {
  QString path = QFileDialog::getOpenFileName(
      this, "Open OBJ", "", "OBJ Files (*.obj);;All Files (*)");
  if (path.isEmpty()) return;
  if (!controller_.LoadModel(path.toStdString())) {
    QMessageBox::warning(this, "Error",
        "Failed to load model (max 6 models or file error).");
    return;
  }
  UpdateModelInfo();
}

void MainWindow::OnAddPrimitive() {}  // handled via lambda in BuildModelPanel

void MainWindow::OnRemoveModel() {
  int idx = model_list_->currentRow();
  if (idx < 0) return;
  controller_.RemoveModel(idx);
  UpdateModelInfo();
}

void MainWindow::OnModelSelected(int index) {
  controller_.SetActiveModel(index);
}

void MainWindow::UpdateModelInfo() {
  model_list_->clear();
  for (int i = 0; i < scene_.GetModelCount(); ++i) {
    const auto& sm = scene_.GetModel(i);
    model_list_->addItem(QString::fromStdString(sm.data.file_name));
  }
  int idx = scene_.GetActiveModel();
  if (idx >= 0 && idx < scene_.GetModelCount()) {
    const auto& sm = scene_.GetModel(idx);
    model_info_label_->setText(
        QString("File: %1\nVertices: %2\nEdges: %3")
            .arg(QString::fromStdString(sm.data.file_name))
            .arg(sm.data.vertex_count)
            .arg(sm.data.edge_count));
    model_list_->setCurrentRow(idx);
  } else {
    model_info_label_->setText("No model loaded");
  }
}

void MainWindow::OnTranslate() {
  controller_.TranslateActiveModel(tx_->value(), ty_->value(), tz_->value());
}

void MainWindow::OnRotate() {
  controller_.RotateActiveModel(rx_->value(), ry_->value(), rz_->value());
}

void MainWindow::OnScale() {
  controller_.ScaleActiveModel(scale_val_->value());
}

void MainWindow::OnTranslateScene() {
  controller_.TranslateScene(stx_->value(), sty_->value(), stz_->value());
}

void MainWindow::OnRotateScene() {
  controller_.RotateScene(srx_->value(), sry_->value(), srz_->value());
}

void MainWindow::OnScaleScene() {
  controller_.ScaleScene(s_scale_->value());
}

void MainWindow::OnRender() {
  QString out_path = QFileDialog::getSaveFileName(
      this, "Save Render", "render.png",
      "PNG (*.png);;JPEG (*.jpg);;BMP (*.bmp)");
  if (out_path.isEmpty()) return;

  if (!preview_) preview_ = new RenderPreviewWindow(this);
  preview_->show();
  preview_->SetProgress(0);

  RenderSettings settings;
  settings.width  = static_cast<int>(render_w_->value());
  settings.height = static_cast<int>(render_h_->value());

  std::string path = out_path.toStdString();
  controller_.RenderToFile(
      path, settings,
      [this](int pct) {
        QMetaObject::invokeMethod(preview_, [this, pct]() {
          preview_->SetProgress(pct);
        }, Qt::QueuedConnection);
      },
      [this, out_path](const std::string& result) {
        QMetaObject::invokeMethod(preview_, [this, out_path, result]() {
          preview_->ShowImage(result.empty() ? "" : out_path);
        }, Qt::QueuedConnection);
      });
}

void MainWindow::OnToggleFloor(bool checked) {
  controller_.SetShowFloor(checked);
}

void MainWindow::OnDisplayModeChanged(int index) {
  controller_.SetDisplayMode(static_cast<DisplayMode>(index));
}

void MainWindow::OnProjectionChanged(int index) {
  controller_.SetProjectionType(
      index == 0 ? ProjectionType::kCentral : ProjectionType::kParallel);
}

void MainWindow::OnBackgroundColorPick() {
  QColor c = QColorDialog::getColor(Qt::black, this, "Background Color");
  if (!c.isValid()) return;
  Color col{static_cast<float>(c.redF()), static_cast<float>(c.greenF()),
            static_cast<float>(c.blueF()), 1.0f};
  controller_.SetSceneBackground(col);
}

void MainWindow::OnModelColorPick() {
  QColor c = QColorDialog::getColor(Qt::white, this, "Model Color");
  if (!c.isValid()) return;
  int idx = scene_.GetActiveModel();
  if (idx < 0 || idx >= scene_.GetModelCount()) return;
  auto mat = scene_.GetModel(idx).material;
  mat.base_color = {static_cast<float>(c.redF()),
                    static_cast<float>(c.greenF()),
                    static_cast<float>(c.blueF()), 1.0f};
  controller_.SetModelMaterial(mat);
}

void MainWindow::OnDirectionalLightChanged() {
  DirectionalLight dl;
  dl.position = {dl_x_->value(), dl_y_->value(), dl_z_->value()};
  dl.intensity = static_cast<float>(dl_intensity_->value());
  controller_.SetDirectionalLight(dl);
}

void MainWindow::OnAddPointLight() {
  PointLight pt;
  pt.position = {0, 3, 3};
  pt.intensity = 1.0f;
  if (!controller_.AddPointLight(pt))
    QMessageBox::information(this, "Lights", "Maximum 5 point lights reached.");
}

void MainWindow::OnRemovePointLight() {
  int n = static_cast<int>(scene_.GetLightManager().GetPointLights().size());
  if (n > 0) controller_.RemovePointLight(n - 1);
}

void MainWindow::OnMaterialChanged() {
  MaterialProperties mat;
  mat.transparency     = static_cast<float>(mat_transp_->value());
  mat.refraction_index = static_cast<float>(mat_refr_->value());
  mat.reflectivity     = static_cast<float>(mat_refl_->value());
  mat.roughness        = static_cast<float>(mat_rough_->value());
  controller_.SetModelMaterial(mat);
}

void MainWindow::SaveSettings() {
  settings_->setValue("projection", projection_cb_->currentIndex());
  settings_->setValue("display_mode", display_mode_cb_->currentIndex());
  settings_->setValue("show_floor", floor_cb_->isChecked());
  const auto& bg = scene_.GetSettings().background_color;
  settings_->setValue("bg_r", bg.r);
  settings_->setValue("bg_g", bg.g);
  settings_->setValue("bg_b", bg.b);
}

void MainWindow::LoadSettings() {
  if (settings_->contains("projection"))
    projection_cb_->setCurrentIndex(settings_->value("projection").toInt());
  if (settings_->contains("display_mode"))
    display_mode_cb_->setCurrentIndex(settings_->value("display_mode").toInt());
  if (settings_->contains("show_floor"))
    floor_cb_->setChecked(settings_->value("show_floor").toBool());
}

}  // namespace s21
