#ifndef SRC_VIEW_MAIN_WINDOW_H_
#define SRC_VIEW_MAIN_WINDOW_H_

#include <gtk/gtk.h>

#include <memory>
#include <vector>

#include "../controller/controller.h"

namespace s21 {

// GTK+3 view. Contains no business logic: every action delegates to the
// Controller. Keeps only widget references and presentation state
// (e.g. the in-memory drawing canvas bitmap).
class MainWindow {
 public:
  explicit MainWindow(Controller *controller);
  ~MainWindow();

  void Show();

  static constexpr int kCanvasGrid = 28;
  static constexpr int kCanvasCell = 12;  // pixel size per cell on screen

 private:
  // -- widget builders --
  GtkWidget *BuildRootLayout();
  GtkWidget *BuildConfigPanel();
  GtkWidget *BuildDrawPanel();
  GtkWidget *BuildExperimentPanel();
  GtkWidget *BuildTrainingPanel();

  // -- signal handlers (static trampolines required by GTK's C API) --
  static void OnImplementationToggled(GtkToggleButton *btn, gpointer user_data);
  static void OnHiddenLayersChanged(GtkSpinButton *btn, gpointer user_data);
  static void OnLoadBmpClicked(GtkButton *btn, gpointer user_data);
  static void OnClassifyDrawingClicked(GtkButton *btn, gpointer user_data);
  static void OnClearDrawingClicked(GtkButton *btn, gpointer user_data);
  static gboolean OnCanvasDraw(GtkWidget *widget, cairo_t *cr, gpointer user_data);
  static gboolean OnCanvasMotion(GtkWidget *widget, GdkEventMotion *event, gpointer user_data);
  static gboolean OnCanvasButtonPress(GtkWidget *widget, GdkEventButton *event, gpointer user_data);
  static void OnLoadDatasetClicked(GtkButton *btn, gpointer user_data);
  static void OnRunExperimentClicked(GtkButton *btn, gpointer user_data);
  static void OnStartTrainingClicked(GtkButton *btn, gpointer user_data);
  static void OnCrossValidationClicked(GtkButton *btn, gpointer user_data);
  static void OnSaveWeightsClicked(GtkButton *btn, gpointer user_data);
  static void OnLoadWeightsClicked(GtkButton *btn, gpointer user_data);

  void AppendLog(const std::string &text);
  void RedrawErrorGraph(const std::vector<double> &errors);

  Controller *controller_;  // not owned

  GtkWidget *window_ = nullptr;
  GtkWidget *radio_matrix_ = nullptr;
  GtkWidget *radio_graph_ = nullptr;
  GtkWidget *spin_hidden_layers_ = nullptr;
  std::vector<GtkWidget *> hidden_layer_spins_;
  GtkWidget *hidden_layer_box_ = nullptr;

  GtkWidget *drawing_area_ = nullptr;
  std::vector<unsigned char> canvas_pixels_;  // 28x28 grayscale, drawing buffer

  GtkWidget *entry_dataset_path_ = nullptr;
  GtkWidget *spin_test_ratio_ = nullptr;
  GtkWidget *spin_experiment_fraction_ = nullptr;
  GtkWidget *spin_epochs_ = nullptr;
  GtkWidget *spin_learning_rate_ = nullptr;
  GtkWidget *spin_k_folds_ = nullptr;
  GtkWidget *drawing_area_graph_ = nullptr;
  std::vector<double> last_epoch_errors_;

  GtkWidget *log_view_ = nullptr;
};

}  // namespace s21

#endif  // SRC_VIEW_MAIN_WINDOW_H_
