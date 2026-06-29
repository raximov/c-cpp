#include <QApplication>
#include "view/main_window.h"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  app.setApplicationName("3DViewer");
  app.setOrganizationName("s21");
  app.setApplicationVersion("2.2");

  s21::MainWindow window;
  window.show();

  return app.exec();
}
