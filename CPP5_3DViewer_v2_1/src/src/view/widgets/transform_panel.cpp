#include "transform_panel.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGroupBox>

namespace s21 {

static QDoubleSpinBox* MakeSpin(double min, double max, double step = 0.1) {
  auto* s = new QDoubleSpinBox;
  s->setRange(min, max);
  s->setSingleStep(step);
  s->setDecimals(3);
  return s;
}

TransformPanel::TransformPanel(SceneController& ctrl, QWidget* parent)
    : QWidget(parent), ctrl_(ctrl) {
  auto* layout = new QVBoxLayout(this);

  // Translation
  auto* tbox = new QGroupBox("Translate (X / Y / Z)");
  auto* trow = new QHBoxLayout(tbox);
  tx_ = MakeSpin(-100, 100); ty_ = MakeSpin(-100, 100); tz_ = MakeSpin(-100, 100);
  trow->addWidget(tx_); trow->addWidget(ty_); trow->addWidget(tz_);
  layout->addWidget(tbox);

  // Rotation
  auto* rbox = new QGroupBox("Rotate (X / Y / Z)°");
  auto* rrow = new QHBoxLayout(rbox);
  rx_ = MakeSpin(-360, 360, 1.0); ry_ = MakeSpin(-360, 360, 1.0); rz_ = MakeSpin(-360, 360, 1.0);
  rrow->addWidget(rx_); rrow->addWidget(ry_); rrow->addWidget(rz_);
  layout->addWidget(rbox);

  // Scale
  auto* sbox = new QGroupBox("Scale");
  auto* srow = new QHBoxLayout(sbox);
  scale_ = MakeSpin(0.001, 1000, 0.1);
  scale_->setValue(1.0);
  srow->addWidget(scale_);
  layout->addWidget(sbox);

  // Buttons
  auto* btnrow = new QHBoxLayout;
  auto* apply_btn = new QPushButton("Apply");
  auto* reset_btn = new QPushButton("Reset");
  btnrow->addWidget(apply_btn);
  btnrow->addWidget(reset_btn);
  layout->addLayout(btnrow);

  connect(apply_btn, &QPushButton::clicked, this, &TransformPanel::OnApply);
  connect(reset_btn, &QPushButton::clicked, this, &TransformPanel::OnReset);

  // Live update on spin change
  auto notify = [this](double) { OnApply(); };
  connect(tx_, &QDoubleSpinBox::valueChanged, notify);
  connect(ty_, &QDoubleSpinBox::valueChanged, notify);
  connect(tz_, &QDoubleSpinBox::valueChanged, notify);
  connect(rx_, &QDoubleSpinBox::valueChanged, notify);
  connect(ry_, &QDoubleSpinBox::valueChanged, notify);
  connect(rz_, &QDoubleSpinBox::valueChanged, notify);
  connect(scale_, &QDoubleSpinBox::valueChanged, notify);
}

void TransformPanel::OnApply() {
  ctrl_.Translate(tx_->value(), ty_->value(), tz_->value());
  ctrl_.Rotate(rx_->value(), ry_->value(), rz_->value());
  ctrl_.Scale(scale_->value());
  emit TransformChanged();
}

void TransformPanel::OnReset() {
  QSignalBlocker b1(tx_), b2(ty_), b3(tz_);
  QSignalBlocker b4(rx_), b5(ry_), b6(rz_), b7(scale_);
  tx_->setValue(0); ty_->setValue(0); tz_->setValue(0);
  rx_->setValue(0); ry_->setValue(0); rz_->setValue(0);
  scale_->setValue(1.0);
  ctrl_.ResetTransform();
  emit TransformChanged();
}

}  // namespace s21
