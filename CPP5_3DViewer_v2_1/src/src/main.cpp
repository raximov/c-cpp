#include <QApplication>
#include <QDir>
#include <QStandardPaths>
#include "view/main_window.h"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  app.setOrganizationName("s21");
  app.setApplicationName("3DViewer");
  app.setApplicationVersion("2.1");

  // Ensure app data directory exists
  QString data_dir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
  QDir().mkpath(data_dir);

  s21::MainWindow window;
  window.show();

  return app.exec();
}
