#pragma once
#include <QMainWindow>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>
#include <QGroupBox>
#include <QListWidget>
#include <QSettings>
#include "../model/scene.h"
#include "../controller/controller.h"
#include "gl_widget.h"
#include "render_preview.h"

namespace s21 {

class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow() override;

 private slots:
  void OnLoadModel();
  void OnAddPrimitive();
  void OnRemoveModel();
  void OnModelSelected(int index);
  void OnTranslate();
  void OnRotate();
  void OnScale();
  void OnTranslateScene();
  void OnRotateScene();
  void OnScaleScene();
  void OnRender();
  void OnToggleFloor(bool checked);
  void OnDisplayModeChanged(int index);
  void OnProjectionChanged(int index);
  void OnBackgroundColorPick();
  void OnModelColorPick();
  void OnDirectionalLightChanged();
  void OnAddPointLight();
  void OnRemovePointLight();
  void OnMaterialChanged();

 private:
  void BuildUI();
  QWidget* BuildModelPanel();
  QWidget* BuildTransformPanel();
  QWidget* BuildRenderPanel();
  QWidget* BuildLightPanel();
  QWidget* BuildMaterialPanel();
  QWidget* BuildSettingsPanel();
  void UpdateModelInfo();
  void SaveSettings();
  void LoadSettings();

  Scene scene_;
  Controller controller_;
  GlWidget* gl_widget_ = nullptr;
  RenderPreviewWindow* preview_ = nullptr;
  QSettings* settings_ = nullptr;

  // Model list
  QListWidget* model_list_ = nullptr;
  QLabel* model_info_label_ = nullptr;

  // Transform inputs
  QDoubleSpinBox* tx_ = nullptr, *ty_ = nullptr, *tz_ = nullptr;
  QDoubleSpinBox* rx_ = nullptr, *ry_ = nullptr, *rz_ = nullptr;
  QDoubleSpinBox* scale_val_ = nullptr;

  QDoubleSpinBox* stx_ = nullptr, *sty_ = nullptr, *stz_ = nullptr;
  QDoubleSpinBox* srx_ = nullptr, *sry_ = nullptr, *srz_ = nullptr;
  QDoubleSpinBox* s_scale_ = nullptr;

  // Render
  QDoubleSpinBox* render_w_ = nullptr, *render_h_ = nullptr;
  QComboBox* display_mode_cb_ = nullptr;
  QComboBox* projection_cb_ = nullptr;
  QCheckBox* floor_cb_ = nullptr;

  // Lights
  QDoubleSpinBox* dl_x_ = nullptr, *dl_y_ = nullptr, *dl_z_ = nullptr;
  QDoubleSpinBox* dl_intensity_ = nullptr;
  QDoubleSpinBox* amb_intensity_ = nullptr;

  // Material
  QDoubleSpinBox* mat_transp_  = nullptr;
  QDoubleSpinBox* mat_refr_    = nullptr;
  QDoubleSpinBox* mat_refl_    = nullptr;
  QDoubleSpinBox* mat_rough_   = nullptr;
};

}  // namespace s21
