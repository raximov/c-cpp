#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "../model/graph_perceptron.h"
#include "../model/matrix_perceptron.h"
#include "../model/perceptron_base.h"

namespace s21 {

enum class PerceptronKind { kMatrix, kGraph };

// Thin controller: forwards calls from the View to the Model and back.
// Contains no business logic of its own beyond simple delegation and
// dataset bookkeeping (train/test split, current implementation choice).
class Controller {
 public:
  Controller();

  void SwitchImplementation(PerceptronKind kind);
  PerceptronKind current_kind() const { return kind_; }

  void Configure(const std::vector<std::size_t> &hidden_layer_sizes);

  void LoadDataset(const std::string &csv_path, double test_ratio);

  TrainingReport Train(int epochs, double learning_rate,
                        const std::function<void(int, double)> &on_epoch = nullptr);

  TrainingReport TrainCrossValidation(int k, int epochs_per_fold, double learning_rate);

  ExperimentResult RunExperiment(double fraction) const;

  int ClassifyBmp(const std::string &bmp_path) const;
  int ClassifyDrawnImage(const std::vector<unsigned char> &grayscale_28x28) const;

  void SaveWeights(const std::string &path) const;
  void LoadWeights(const std::string &path);

  std::string CurrentImplementationName() const { return Active()->Name(); }
  std::size_t train_size() const { return train_set_.size(); }
  std::size_t test_size() const { return test_set_.size(); }

 private:
  IPerceptron *Active();
  const IPerceptron *Active() const;

  PerceptronKind kind_ = PerceptronKind::kMatrix;
  std::unique_ptr<MatrixPerceptron> matrix_model_;
  std::unique_ptr<GraphPerceptron> graph_model_;

  std::vector<Sample> train_set_;
  std::vector<Sample> test_set_;
  std::vector<std::size_t> hidden_layer_sizes_ = {64, 32};  // default configuration
};

}  // namespace s21

#endif  // SRC_CONTROLLER_CONTROLLER_H_
