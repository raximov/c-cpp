#include "render_preview.h"
#include <QVBoxLayout>
#include <QPixmap>

namespace s21 {

RenderPreviewWindow::RenderPreviewWindow(QWidget* parent)
    : QDialog(parent) {
  setWindowTitle("Ray Trace Preview");
  resize(800, 600);

  auto* layout = new QVBoxLayout(this);

  progress_bar_ = new QProgressBar(this);
  progress_bar_->setRange(0, 100);
  layout->addWidget(progress_bar_);

  image_label_ = new QLabel(this);
  image_label_->setAlignment(Qt::AlignCenter);
  image_label_->setText("Rendering...");
  layout->addWidget(image_label_);
}

void RenderPreviewWindow::SetProgress(int percent) {
  progress_bar_->setValue(percent);
}

void RenderPreviewWindow::ShowImage(const QString& path) {
  if (path.isEmpty()) {
    image_label_->setText("Render failed.");
    return;
  }
  QPixmap pix(path);
  if (pix.isNull()) {
    image_label_->setText("Could not load image: " + path);
    return;
  }
  image_label_->setPixmap(
      pix.scaled(image_label_->size(), Qt::KeepAspectRatio,
                 Qt::SmoothTransformation));
  progress_bar_->setValue(100);
}

}  // namespace s21
