#include "main_window.h"

#include <algorithm>
#include <sstream>

namespace s21 {

MainWindow::MainWindow(Controller *controller) : controller_(controller) {
  canvas_pixels_.assign(kCanvasGrid * kCanvasGrid, 0);

  window_ = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window_), "MultilayerPerceptron - s21");
  gtk_window_set_default_size(GTK_WINDOW(window_), 1000, 700);
  g_signal_connect(window_, "destroy", G_CALLBACK(gtk_main_quit), nullptr);

  gtk_container_add(GTK_CONTAINER(window_), BuildRootLayout());
}

MainWindow::~MainWindow() = default;

void MainWindow::Show() {
  gtk_widget_show_all(window_);
  gtk_main();
}

GtkWidget *MainWindow::BuildRootLayout() {
  GtkWidget *root = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 12);
  gtk_container_set_border_width(GTK_CONTAINER(root), 12);

  GtkWidget *left_col = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
  gtk_box_pack_start(GTK_BOX(left_col), BuildConfigPanel(), FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(left_col), BuildTrainingPanel(), FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(left_col), BuildExperimentPanel(), FALSE, FALSE, 0);

  GtkWidget *right_col = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
  gtk_box_pack_start(GTK_BOX(right_col), BuildDrawPanel(), FALSE, FALSE, 0);

  log_view_ = gtk_text_view_new();
  gtk_text_view_set_editable(GTK_TEXT_VIEW(log_view_), FALSE);
  GtkWidget *scroll = gtk_scrolled_window_new(nullptr, nullptr);
  gtk_widget_set_size_request(scroll, -1, 200);
  gtk_container_add(GTK_CONTAINER(scroll), log_view_);
  gtk_box_pack_start(GTK_BOX(right_col), scroll, TRUE, TRUE, 0);

  gtk_box_pack_start(GTK_BOX(root), left_col, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(root), right_col, TRUE, TRUE, 0);
  return root;
}

GtkWidget *MainWindow::BuildConfigPanel() {
  GtkWidget *frame = gtk_frame_new("Configuration");
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
  gtk_container_set_border_width(GTK_CONTAINER(box), 8);

  GtkWidget *impl_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);
  radio_matrix_ = gtk_radio_button_new_with_label(nullptr, "Matrix");
  radio_graph_ =
      gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio_matrix_), "Graph");
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_matrix_), TRUE);
  g_signal_connect(radio_matrix_, "toggled", G_CALLBACK(OnImplementationToggled), this);
  gtk_box_pack_start(GTK_BOX(impl_box), radio_matrix_, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(impl_box), radio_graph_, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), impl_box, FALSE, FALSE, 0);

  GtkWidget *layers_label = gtk_label_new("Hidden layers (2-5):");
  gtk_box_pack_start(GTK_BOX(box), layers_label, FALSE, FALSE, 0);

  spin_hidden_layers_ = gtk_spin_button_new_with_range(2, 5, 1);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_hidden_layers_), 2);
  g_signal_connect(spin_hidden_layers_, "value-changed", G_CALLBACK(OnHiddenLayersChanged), this);
  gtk_box_pack_start(GTK_BOX(box), spin_hidden_layers_, FALSE, FALSE, 0);

  hidden_layer_box_ = gtk_box_new(GTK_ORIENTATION_VERTICAL, 4);
  gtk_box_pack_start(GTK_BOX(box), hidden_layer_box_, FALSE, FALSE, 0);
  // Trigger initial population of per-layer size spinners.
  OnHiddenLayersChanged(GTK_SPIN_BUTTON(spin_hidden_layers_), this);

  gtk_container_add(GTK_CONTAINER(frame), box);
  return frame;
}

GtkWidget *MainWindow::BuildTrainingPanel() {
  GtkWidget *frame = gtk_frame_new("Dataset & Training");
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
  gtk_container_set_border_width(GTK_CONTAINER(box), 8);

  GtkWidget *dataset_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4);
  entry_dataset_path_ = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry_dataset_path_), "path/to/emnist-letters.csv");
  GtkWidget *load_btn = gtk_button_new_with_label("Load dataset");
  g_signal_connect(load_btn, "clicked", G_CALLBACK(OnLoadDatasetClicked), this);
  gtk_box_pack_start(GTK_BOX(dataset_box), entry_dataset_path_, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(dataset_box), load_btn, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), dataset_box, FALSE, FALSE, 0);

  gtk_box_pack_start(GTK_BOX(box), gtk_label_new("Test ratio (<= 0.2):"), FALSE, FALSE, 0);
  spin_test_ratio_ = gtk_spin_button_new_with_range(0.0, 0.2, 0.01);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_test_ratio_), 0.2);
  gtk_box_pack_start(GTK_BOX(box), spin_test_ratio_, FALSE, FALSE, 0);

  gtk_box_pack_start(GTK_BOX(box), gtk_label_new("Epochs:"), FALSE, FALSE, 0);
  spin_epochs_ = gtk_spin_button_new_with_range(1, 1000, 1);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_epochs_), 10);
  gtk_box_pack_start(GTK_BOX(box), spin_epochs_, FALSE, FALSE, 0);

  gtk_box_pack_start(GTK_BOX(box), gtk_label_new("Learning rate:"), FALSE, FALSE, 0);
  spin_learning_rate_ = gtk_spin_button_new_with_range(0.001, 1.0, 0.001);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_learning_rate_), 0.1);
  gtk_box_pack_start(GTK_BOX(box), spin_learning_rate_, FALSE, FALSE, 0);

  GtkWidget *train_btn = gtk_button_new_with_label("Start training");
  g_signal_connect(train_btn, "clicked", G_CALLBACK(OnStartTrainingClicked), this);
  gtk_box_pack_start(GTK_BOX(box), train_btn, FALSE, FALSE, 0);

  GtkWidget *cv_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4);
  gtk_box_pack_start(GTK_BOX(cv_box), gtk_label_new("k-folds:"), FALSE, FALSE, 0);
  spin_k_folds_ = gtk_spin_button_new_with_range(2, 20, 1);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_k_folds_), 5);
  gtk_box_pack_start(GTK_BOX(cv_box), spin_k_folds_, FALSE, FALSE, 0);
  GtkWidget *cv_btn = gtk_button_new_with_label("Run cross-validation");
  g_signal_connect(cv_btn, "clicked", G_CALLBACK(OnCrossValidationClicked), this);
  gtk_box_pack_start(GTK_BOX(cv_box), cv_btn, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), cv_box, FALSE, FALSE, 0);

  drawing_area_graph_ = gtk_drawing_area_new();
  gtk_widget_set_size_request(drawing_area_graph_, 280, 140);
  g_signal_connect(drawing_area_graph_, "draw", G_CALLBACK(+[](GtkWidget *, cairo_t *cr,
                                                                gpointer user_data) -> gboolean {
                     auto *self = static_cast<MainWindow *>(user_data);
                     self->RedrawErrorGraph(self->last_epoch_errors_);
                     (void)cr;
                     return FALSE;
                   }),
                   this);
  gtk_box_pack_start(GTK_BOX(box), drawing_area_graph_, FALSE, FALSE, 0);

  GtkWidget *weights_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4);
  GtkWidget *save_btn = gtk_button_new_with_label("Save weights");
  GtkWidget *load_w_btn = gtk_button_new_with_label("Load weights");
  g_signal_connect(save_btn, "clicked", G_CALLBACK(OnSaveWeightsClicked), this);
  g_signal_connect(load_w_btn, "clicked", G_CALLBACK(OnLoadWeightsClicked), this);
  gtk_box_pack_start(GTK_BOX(weights_box), save_btn, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(weights_box), load_w_btn, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), weights_box, FALSE, FALSE, 0);

  gtk_container_add(GTK_CONTAINER(frame), box);
  return frame;
}

GtkWidget *MainWindow::BuildExperimentPanel() {
  GtkWidget *frame = gtk_frame_new("Experiment");
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
  gtk_container_set_border_width(GTK_CONTAINER(box), 8);

  gtk_box_pack_start(GTK_BOX(box), gtk_label_new("Test sample fraction (0-1):"), FALSE, FALSE, 0);
  spin_experiment_fraction_ = gtk_spin_button_new_with_range(0.0, 1.0, 0.05);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_experiment_fraction_), 1.0);
  gtk_box_pack_start(GTK_BOX(box), spin_experiment_fraction_, FALSE, FALSE, 0);

  GtkWidget *run_btn = gtk_button_new_with_label("Run experiment");
  g_signal_connect(run_btn, "clicked", G_CALLBACK(OnRunExperimentClicked), this);
  gtk_box_pack_start(GTK_BOX(box), run_btn, FALSE, FALSE, 0);

  gtk_container_add(GTK_CONTAINER(frame), box);
  return frame;
}

GtkWidget *MainWindow::BuildDrawPanel() {
  GtkWidget *frame = gtk_frame_new("Draw / Load BMP & Classify");
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
  gtk_container_set_border_width(GTK_CONTAINER(box), 8);

  drawing_area_ = gtk_drawing_area_new();
  gtk_widget_set_size_request(drawing_area_, kCanvasGrid * kCanvasCell, kCanvasGrid * kCanvasCell);
  gtk_widget_add_events(drawing_area_, GDK_BUTTON_PRESS_MASK | GDK_POINTER_MOTION_MASK |
                                            GDK_BUTTON1_MOTION_MASK);
  g_signal_connect(drawing_area_, "draw", G_CALLBACK(OnCanvasDraw), this);
  g_signal_connect(drawing_area_, "motion-notify-event", G_CALLBACK(OnCanvasMotion), this);
  g_signal_connect(drawing_area_, "button-press-event", G_CALLBACK(OnCanvasButtonPress), this);
  gtk_box_pack_start(GTK_BOX(box), drawing_area_, FALSE, FALSE, 0);

  GtkWidget *btn_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4);
  GtkWidget *clear_btn = gtk_button_new_with_label("Clear");
  GtkWidget *classify_btn = gtk_button_new_with_label("Classify drawing");
  GtkWidget *load_bmp_btn = gtk_button_new_with_label("Load BMP...");
  g_signal_connect(clear_btn, "clicked", G_CALLBACK(OnClearDrawingClicked), this);
  g_signal_connect(classify_btn, "clicked", G_CALLBACK(OnClassifyDrawingClicked), this);
  g_signal_connect(load_bmp_btn, "clicked", G_CALLBACK(OnLoadBmpClicked), this);
  gtk_box_pack_start(GTK_BOX(btn_box), clear_btn, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(btn_box), classify_btn, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(btn_box), load_bmp_btn, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), btn_box, FALSE, FALSE, 0);

  gtk_container_add(GTK_CONTAINER(frame), box);
  return frame;
}

void MainWindow::AppendLog(const std::string &text) {
  GtkTextBuffer *buf = gtk_text_view_get_buffer(GTK_TEXT_VIEW(log_view_));
  GtkTextIter end;
  gtk_text_buffer_get_end_iter(buf, &end);
  std::string line = text + "\n";
  gtk_text_buffer_insert(buf, &end, line.c_str(), -1);
}

void MainWindow::RedrawErrorGraph(const std::vector<double> &errors) {
  if (!drawing_area_graph_ || errors.empty()) return;
  cairo_t *cr = gdk_cairo_create(gtk_widget_get_window(drawing_area_graph_));
  GtkAllocation alloc;
  gtk_widget_get_allocation(drawing_area_graph_, &alloc);

  cairo_set_source_rgb(cr, 1, 1, 1);
  cairo_paint(cr);
  cairo_set_source_rgb(cr, 0.1, 0.4, 0.9);
  cairo_set_line_width(cr, 2.0);

  double max_err = *std::max_element(errors.begin(), errors.end());
  if (max_err <= 0.0) max_err = 1.0;
  for (std::size_t i = 0; i < errors.size(); ++i) {
    double x = alloc.width * static_cast<double>(i) / std::max<std::size_t>(1, errors.size() - 1);
    double y = alloc.height - (errors[i] / max_err) * alloc.height;
    if (i == 0)
      cairo_move_to(cr, x, y);
    else
      cairo_line_to(cr, x, y);
  }
  cairo_stroke(cr);
  cairo_destroy(cr);
}

// ---- signal handlers ----

void MainWindow::OnImplementationToggled(GtkToggleButton *, gpointer user_data) {
  auto *self = static_cast<MainWindow *>(user_data);
  bool matrix_selected = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(self->radio_matrix_));
  self->controller_->SwitchImplementation(matrix_selected ? PerceptronKind::kMatrix
                                                            : PerceptronKind::kGraph);
  self->AppendLog(std::string("Switched to ") + self->controller_->CurrentImplementationName());
}

void MainWindow::OnHiddenLayersChanged(GtkSpinButton *btn, gpointer user_data) {
  auto *self = static_cast<MainWindow *>(user_data);
  int count = gtk_spin_button_get_value_as_int(btn);

  // Rebuild the per-layer size spin buttons.
  GList *children = gtk_container_get_children(GTK_CONTAINER(self->hidden_layer_box_));
  for (GList *it = children; it != nullptr; it = it->next) gtk_widget_destroy(GTK_WIDGET(it->data));
  g_list_free(children);
  self->hidden_layer_spins_.clear();

  for (int i = 0; i < count; ++i) {
    GtkWidget *row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4);
    std::ostringstream label_text;
    label_text << "Layer " << (i + 1) << " size:";
    gtk_box_pack_start(GTK_BOX(row), gtk_label_new(label_text.str().c_str()), FALSE, FALSE, 0);
    GtkWidget *spin = gtk_spin_button_new_with_range(1, 512, 1);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin), 32);
    gtk_box_pack_start(GTK_BOX(row), spin, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(self->hidden_layer_box_), row, FALSE, FALSE, 0);
    self->hidden_layer_spins_.push_back(spin);
  }
  gtk_widget_show_all(self->hidden_layer_box_);

  std::vector<std::size_t> sizes;
  for (auto *spin : self->hidden_layer_spins_)
    sizes.push_back(static_cast<std::size_t>(gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin))));
  if (sizes.size() >= 2) self->controller_->Configure(sizes);
}

void MainWindow::OnLoadBmpClicked(GtkButton *, gpointer user_data) {
  auto *self = static_cast<MainWindow *>(user_data);
  GtkWidget *dialog =
      gtk_file_chooser_dialog_new("Open BMP image", GTK_WINDOW(self->window_), GTK_FILE_CHOOSER_ACTION_OPEN,
                                   "_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, nullptr);
  if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
    char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
    try {
      int label = self->controller_->ClassifyBmp(filename);
      std::ostringstream out;
      out << "BMP classified as: " << static_cast<char>('A' + label);
      self->AppendLog(out.str());
    } catch (const std::exception &e) {
      self->AppendLog(std::string("Error: ") + e.what());
    }
    g_free(filename);
  }
  gtk_widget_destroy(dialog);
}

void MainWindow::OnClassifyDrawingClicked(GtkButton *, gpointer user_data) {
  auto *self = static_cast<MainWindow *>(user_data);
  try {
    int label = self->controller_->ClassifyDrawnImage(self->canvas_pixels_);
    std::ostringstream out;
    out << "Drawing classified as: " << static_cast<char>('A' + label);
    self->AppendLog(out.str());
  } catch (const std::exception &e) {
    self->AppendLog(std::string("Error: ") + e.what());
  }
}

void MainWindow::OnClearDrawingClicked(GtkButton *, gpointer user_data) {
  auto *self = static_cast<MainWindow *>(user_data);
  std::fill(self->canvas_pixels_.begin(), self->canvas_pixels_.end(), 0);
  gtk_widget_queue_draw(self->drawing_area_);
}

gboolean MainWindow::OnCanvasDraw(GtkWidget *, cairo_t *cr, gpointer user_data) {
  auto *self = static_cast<MainWindow *>(user_data);
  cairo_set_source_rgb(cr, 1, 1, 1);
  cairo_paint(cr);
  for (int y = 0; y < kCanvasGrid; ++y) {
    for (int x = 0; x < kCanvasGrid; ++x) {
      double v = self->canvas_pixels_[y * kCanvasGrid + x] / 255.0;
      cairo_set_source_rgb(cr, 1 - v, 1 - v, 1 - v);
      cairo_rectangle(cr, x * kCanvasCell, y * kCanvasCell, kCanvasCell, kCanvasCell);
      cairo_fill(cr);
    }
  }
  return FALSE;
}

namespace {
void PaintAt(MainWindow *self, std::vector<unsigned char> *pixels, double px, double py) {
  int cell_x = static_cast<int>(px) / MainWindow::kCanvasCell;
  int cell_y = static_cast<int>(py) / MainWindow::kCanvasCell;
  for (int dy = -1; dy <= 1; ++dy) {
    for (int dx = -1; dx <= 1; ++dx) {
      int x = cell_x + dx, y = cell_y + dy;
      if (x < 0 || x >= MainWindow::kCanvasGrid || y < 0 || y >= MainWindow::kCanvasGrid) continue;
      (*pixels)[y * MainWindow::kCanvasGrid + x] = 255;
    }
  }
  (void)self;
}
}  // namespace

gboolean MainWindow::OnCanvasMotion(GtkWidget *widget, GdkEventMotion *event, gpointer user_data) {
  auto *self = static_cast<MainWindow *>(user_data);
  if (event->state & GDK_BUTTON1_MASK) {
    PaintAt(self, &self->canvas_pixels_, event->x, event->y);
    gtk_widget_queue_draw(widget);
  }
  return TRUE;
}

gboolean MainWindow::OnCanvasButtonPress(GtkWidget *widget, GdkEventButton *event, gpointer user_data) {
  auto *self = static_cast<MainWindow *>(user_data);
  PaintAt(self, &self->canvas_pixels_, event->x, event->y);
  gtk_widget_queue_draw(widget);
  return TRUE;
}

void MainWindow::OnLoadDatasetClicked(GtkButton *, gpointer user_data) {
  auto *self = static_cast<MainWindow *>(user_data);
  const char *path = gtk_entry_get_text(GTK_ENTRY(self->entry_dataset_path_));
  double ratio = gtk_spin_button_get_value(GTK_SPIN_BUTTON(self->spin_test_ratio_));
  try {
    self->controller_->LoadDataset(path, ratio);
    std::ostringstream out;
    out << "Dataset loaded: train=" << self->controller_->train_size()
        << " test=" << self->controller_->test_size();
    self->AppendLog(out.str());
  } catch (const std::exception &e) {
    self->AppendLog(std::string("Error: ") + e.what());
  }
}

void MainWindow::OnRunExperimentClicked(GtkButton *, gpointer user_data) {
  auto *self = static_cast<MainWindow *>(user_data);
  double fraction = gtk_spin_button_get_value(GTK_SPIN_BUTTON(self->spin_experiment_fraction_));
  try {
    ExperimentResult r = self->controller_->RunExperiment(fraction);
    std::ostringstream out;
    out << "Experiment: accuracy=" << r.accuracy << " precision=" << r.precision
        << " recall=" << r.recall << " f-measure=" << r.f_measure
        << " time=" << r.total_time_seconds << "s";
    self->AppendLog(out.str());
  } catch (const std::exception &e) {
    self->AppendLog(std::string("Error: ") + e.what());
  }
}

void MainWindow::OnStartTrainingClicked(GtkButton *, gpointer user_data) {
  auto *self = static_cast<MainWindow *>(user_data);
  int epochs = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(self->spin_epochs_));
  double lr = gtk_spin_button_get_value(GTK_SPIN_BUTTON(self->spin_learning_rate_));
  try {
    self->last_epoch_errors_.clear();
    auto report = self->controller_->Train(epochs, lr, [self](int epoch, double err) {
      std::ostringstream out;
      out << "Epoch " << epoch + 1 << ": error=" << err;
      self->AppendLog(out.str());
      self->last_epoch_errors_.push_back(err);
      gtk_widget_queue_draw(self->drawing_area_graph_);
      while (gtk_events_pending()) gtk_main_iteration();
    });
    self->AppendLog("Training finished.");
    (void)report;
  } catch (const std::exception &e) {
    self->AppendLog(std::string("Error: ") + e.what());
  }
}

void MainWindow::OnCrossValidationClicked(GtkButton *, gpointer user_data) {
  auto *self = static_cast<MainWindow *>(user_data);
  int k = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(self->spin_k_folds_));
  int epochs = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(self->spin_epochs_));
  double lr = gtk_spin_button_get_value(GTK_SPIN_BUTTON(self->spin_learning_rate_));
  try {
    auto report = self->controller_->TrainCrossValidation(k, epochs, lr);
    self->last_epoch_errors_ = report.epoch_errors;
    gtk_widget_queue_draw(self->drawing_area_graph_);
    self->AppendLog("Cross-validation finished.");
  } catch (const std::exception &e) {
    self->AppendLog(std::string("Error: ") + e.what());
  }
}

void MainWindow::OnSaveWeightsClicked(GtkButton *, gpointer user_data) {
  auto *self = static_cast<MainWindow *>(user_data);
  GtkWidget *dialog =
      gtk_file_chooser_dialog_new("Save weights", GTK_WINDOW(self->window_), GTK_FILE_CHOOSER_ACTION_SAVE,
                                   "_Cancel", GTK_RESPONSE_CANCEL, "_Save", GTK_RESPONSE_ACCEPT, nullptr);
  if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
    char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
    try {
      self->controller_->SaveWeights(filename);
      self->AppendLog(std::string("Weights saved to ") + filename);
    } catch (const std::exception &e) {
      self->AppendLog(std::string("Error: ") + e.what());
    }
    g_free(filename);
  }
  gtk_widget_destroy(dialog);
}

void MainWindow::OnLoadWeightsClicked(GtkButton *, gpointer user_data) {
  auto *self = static_cast<MainWindow *>(user_data);
  GtkWidget *dialog =
      gtk_file_chooser_dialog_new("Load weights", GTK_WINDOW(self->window_), GTK_FILE_CHOOSER_ACTION_OPEN,
                                   "_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, nullptr);
  if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
    char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
    try {
      self->controller_->LoadWeights(filename);
      self->AppendLog(std::string("Weights loaded from ") + filename);
    } catch (const std::exception &e) {
      self->AppendLog(std::string("Error: ") + e.what());
    }
    g_free(filename);
  }
  gtk_widget_destroy(dialog);
}

}  // namespace s21
