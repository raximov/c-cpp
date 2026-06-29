#pragma once
#include <QDialog>
#include <QLabel>
#include <QProgressBar>

namespace s21 {

class RenderPreviewWindow : public QDialog {
  Q_OBJECT
 public:
  explicit RenderPreviewWindow(QWidget* parent = nullptr);
  void SetProgress(int percent);
  void ShowImage(const QString& path);

 private:
  QLabel* image_label_;
  QProgressBar* progress_bar_;
};

}  // namespace s21
