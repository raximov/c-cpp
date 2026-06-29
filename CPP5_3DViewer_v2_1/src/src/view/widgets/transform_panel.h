#pragma once
#include <QWidget>
#include <QDoubleSpinBox>
#include <QPushButton>
#include "../../controller/scene_controller.h"

namespace s21 {

class TransformPanel : public QWidget {
  Q_OBJECT
 public:
  explicit TransformPanel(SceneController& ctrl, QWidget* parent = nullptr);

 signals:
  void TransformChanged();

 private slots:
  void OnApply();
  void OnReset();

 private:
  SceneController& ctrl_;

  QDoubleSpinBox* tx_{}, *ty_{}, *tz_{};
  QDoubleSpinBox* rx_{}, *ry_{}, *rz_{};
  QDoubleSpinBox* scale_{};
};

}  // namespace s21
