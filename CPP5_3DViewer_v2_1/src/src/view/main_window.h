#pragma once
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QTabWidget>
#include "../model/scene.h"
#include "../controller/scene_controller.h"
#include "opengl/gl_widget.h"
#include "widgets/transform_panel.h"
#include "widgets/settings_panel.h"

namespace s21 {

class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow() override;

 private slots:
  void OnOpenFile();
  void OnSaveImage();
  void OnTransformChanged();
  void OnSettingsChanged();

 private:
  void SetupUi();
  void UpdateInfoLabel();

  Scene scene_;
  SceneController controller_;

  GlWidget* gl_widget_{};
  TransformPanel* transform_panel_{};
  SettingsPanel* settings_panel_{};

  QLabel* info_label_{};
  QLabel* file_label_{};
};

}  // namespace s21
