#pragma once
#include <QWidget>
#include <QComboBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include "../../controller/scene_controller.h"

namespace s21 {

class SettingsPanel : public QWidget {
  Q_OBJECT
 public:
  explicit SettingsPanel(SceneController& ctrl, QWidget* parent = nullptr);

  void LoadFromScene();

 signals:
  void SettingsChanged();

 private slots:
  void OnRenderModeChanged(int idx);
  void OnProjectionChanged(int idx);
  void OnPickEdgeColor();
  void OnPickVertexColor();
  void OnPickObjectColor();
  void OnPickBgColor();
  void OnLightColorPick();

 private:
  SceneController& ctrl_;

  QComboBox* render_combo_{};
  QComboBox* proj_combo_{};
  QCheckBox* dashed_cb_{};
  QDoubleSpinBox* edge_width_{};
  QComboBox* vertex_display_{};
  QDoubleSpinBox* vertex_size_{};
  // Light
  QDoubleSpinBox* light_x_{}, *light_y_{}, *light_z_{};
  QDoubleSpinBox* ambient_{}, *specular_{};
  QSpinBox* shininess_{};

  float edge_r_{1}, edge_g_{1}, edge_b_{1};
  float vertex_r_{1}, vertex_g_{0}, vertex_b_{0};
  float obj_r_{0.6f}, obj_g_{0.6f}, obj_b_{0.9f};
  float bg_r_{0.1f}, bg_g_{0.1f}, bg_b_{0.15f};
  float light_r_{1}, light_g_{1}, light_b_{1};

  void PushAll();
};

}  // namespace s21
