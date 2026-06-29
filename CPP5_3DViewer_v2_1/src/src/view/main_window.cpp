#include "main_window.h"
#include <QFileDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QMenuBar>
#include <QStatusBar>
#include <QApplication>
#include <QMessageBox>
#include <QImageWriter>

namespace s21 {

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), controller_(scene_) {
  controller_.LoadSettings();
  SetupUi();
  settings_panel_->LoadFromScene();
  setWindowTitle("3DViewer v2.1");
  resize(1280, 800);
}

MainWindow::~MainWindow() {
  controller_.SaveSettings();
}

void MainWindow::SetupUi() {
  auto* central = new QWidget(this);
  setCentralWidget(central);
  auto* main_hl = new QHBoxLayout(central);

  // Left: GL viewport
  gl_widget_ = new GlWidget(scene_, this);
  main_hl->addWidget(gl_widget_, 1);

  // Right: side panel in a scroll area
  auto* right_panel = new QWidget;
  right_panel->setFixedWidth(310);
  auto* right_vl = new QVBoxLayout(right_panel);

  // File selection
  auto* file_row = new QHBoxLayout;
  auto* open_btn = new QPushButton("Open .obj");
  file_label_ = new QLabel("No file loaded");
  file_label_->setWordWrap(true);
  file_row->addWidget(open_btn);
  right_vl->addLayout(file_row);
  right_vl->addWidget(file_label_);

  info_label_ = new QLabel;
  info_label_->setWordWrap(true);
  right_vl->addWidget(info_label_);

  // Tab widget for Transform / Settings
  auto* tabs = new QTabWidget;
  transform_panel_ = new TransformPanel(controller_, this);
  settings_panel_ = new SettingsPanel(controller_, this);

  auto* t_scroll = new QScrollArea;
  t_scroll->setWidget(transform_panel_);
  t_scroll->setWidgetResizable(true);

  auto* s_scroll = new QScrollArea;
  s_scroll->setWidget(settings_panel_);
  s_scroll->setWidgetResizable(true);

  tabs->addTab(t_scroll, "Transform");
  tabs->addTab(s_scroll, "Settings");
  right_vl->addWidget(tabs, 1);

  // Save image button
  auto* save_btn = new QPushButton("Save Image (BMP/JPEG)");
  right_vl->addWidget(save_btn);

  main_hl->addWidget(right_panel);

  // Menu
  auto* file_menu = menuBar()->addMenu("&File");
  file_menu->addAction("Open .obj", this, &MainWindow::OnOpenFile, QKeySequence::Open);
  file_menu->addAction("Save Image", this, &MainWindow::OnSaveImage);
  file_menu->addSeparator();
  file_menu->addAction("Quit", qApp, &QApplication::quit, QKeySequence::Quit);

  // Connections
  connect(open_btn, &QPushButton::clicked, this, &MainWindow::OnOpenFile);
  connect(save_btn, &QPushButton::clicked, this, &MainWindow::OnSaveImage);
  connect(transform_panel_, &TransformPanel::TransformChanged,
          this, &MainWindow::OnTransformChanged);
  connect(settings_panel_, &SettingsPanel::SettingsChanged,
          this, &MainWindow::OnSettingsChanged);
}

void MainWindow::OnOpenFile() {
  QString path = QFileDialog::getOpenFileName(
      this, "Open OBJ file", "", "OBJ Files (*.obj);;All Files (*)");
  if (path.isEmpty()) return;

  if (!controller_.LoadModel(path.toStdString())) {
    QMessageBox::critical(this, "Error", QString::fromStdString(scene_.GetLastError()));
    return;
  }

  file_label_->setText(QFileInfo(path).fileName());
  UpdateInfoLabel();
  gl_widget_->ReloadMesh();
}

void MainWindow::OnSaveImage() {
  QString path = QFileDialog::getSaveFileName(
      this, "Save Image", "", "BMP (*.bmp);;JPEG (*.jpg *.jpeg)");
  if (path.isEmpty()) return;
  QImage img = gl_widget_->grabFramebuffer();
  if (!img.save(path)) {
    QMessageBox::warning(this, "Error", "Failed to save image.");
  }
}

void MainWindow::OnTransformChanged() {
  gl_widget_->update();
}

void MainWindow::OnSettingsChanged() {
  gl_widget_->ReloadMesh();
}

void MainWindow::UpdateInfoLabel() {
  const auto& mesh = scene_.GetMesh();
  info_label_->setText(
    QString("Vertices: %1  |  Edges: %2")
      .arg(mesh.GetVertexCount())
      .arg(mesh.GetEdgeCount()));
}

}  // namespace s21
