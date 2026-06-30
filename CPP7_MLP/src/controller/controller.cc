#include "controller.h"

#include <stdexcept>

#include "../model/data_loader.h"

namespace s21 {

Controller::Controller() {
  matrix_model_ = std::make_unique<MatrixPerceptron>();
  graph_model_ = std::make_unique<GraphPerceptron>();
  matrix_model_->Configure(hidden_layer_sizes_);
  graph_model_->Configure(hidden_layer_sizes_);
}

IPerceptron *Controller::Active() {
  return kind_ == PerceptronKind::kMatrix
             ? static_cast<IPerceptron *>(matrix_model_.get())
             : static_cast<IPerceptron *>(graph_model_.get());
}

const IPerceptron *Controller::Active() const {
  return kind_ == PerceptronKind::kMatrix
             ? static_cast<const IPerceptron *>(matrix_model_.get())
             : static_cast<const IPerceptron *>(graph_model_.get());
}

void Controller::SwitchImplementation(PerceptronKind kind) { kind_ = kind; }

void Controller::Configure(const std::vector<std::size_t> &hidden_layer_sizes) {
  if (hidden_layer_sizes.size() < 2 || hidden_layer_sizes.size() > 5)
    throw std::invalid_argument("Controller::Configure: hidden layers count must be in [2, 5]");
  hidden_layer_sizes_ = hidden_layer_sizes;
  matrix_model_->Configure(hidden_layer_sizes_);
  graph_model_->Configure(hidden_layer_sizes_);
}

void Controller::LoadDataset(const std::string &csv_path, double test_ratio) {
  std::vector<Sample> dataset = DataLoader::LoadCsv(csv_path);
  DataLoader::SplitTrainTest(dataset, test_ratio, &train_set_, &test_set_);
}

TrainingReport Controller::Train(int epochs, double learning_rate,
                                  const std::function<void(int, double)> &on_epoch) {
  return Active()->Train(train_set_, test_set_, epochs, learning_rate, on_epoch);
}

TrainingReport Controller::TrainCrossValidation(int k, int epochs_per_fold, double learning_rate) {
  std::vector<Sample> full;
  full.reserve(train_set_.size() + test_set_.size());
  full.insert(full.end(), train_set_.begin(), train_set_.end());
  full.insert(full.end(), test_set_.begin(), test_set_.end());
  return Active()->TrainCrossValidation(full, k, epochs_per_fold, learning_rate);
}

ExperimentResult Controller::RunExperiment(double fraction) const {
  return Active()->RunExperiment(test_set_, fraction);
}

int Controller::ClassifyBmp(const std::string &bmp_path) const {
  std::vector<double> input = DataLoader::LoadAndNormalizeBmp(bmp_path);
  return Active()->Predict(input);
}

int Controller::ClassifyDrawnImage(const std::vector<unsigned char> &grayscale_28x28) const {
  std::vector<double> input = DataLoader::NormalizeRaw28x28(grayscale_28x28);
  return Active()->Predict(input);
}

void Controller::SaveWeights(const std::string &path) const { Active()->SaveWeights(path); }

void Controller::LoadWeights(const std::string &path) { Active()->LoadWeights(path); }

}  // namespace s21
