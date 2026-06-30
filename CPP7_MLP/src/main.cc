#include <gtk/gtk.h>

#include "controller/controller.h"
#include "view/main_window.h"

int main(int argc, char **argv) {
  gtk_init(&argc, &argv);

  s21::Controller controller;
  s21::MainWindow window(&controller);
  window.Show();

  return 0;
}
