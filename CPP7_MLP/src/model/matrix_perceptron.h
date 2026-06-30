#ifndef SRC_MODEL_MATRIX_PERCEPTRON_H_
#define SRC_MODEL_MATRIX_PERCEPTRON_H_

#include <string>
#include <vector>

#include "matrix.h"
#include "perceptron_base.h"

namespace s21 {

// Multilayer perceptron where every layer is represented by a weight
// matrix and a bias matrix (column vector). All hidden layers and the
// output layer use the sigmoid activation function.
class MatrixPerceptron : public IPerceptron {
 public:
  MatrixPerceptron() = default;

  void Configure(const std::vector<std::size_t> &hidden_layer_sizes) override;

  TrainingReport Train(const std::vector<Sample> &train_set, const std::vector<Sample> &test_set,
                        int epochs, double learning_rate,
                        const std::function<void(int, double)> &on_epoch) override;

  TrainingReport TrainCrossValidation(const std::vector<Sample> &dataset, int k,
                                       int epochs_per_fold, double learning_rate) override;

  int Predict(const std::vector<double> &input) const override;

  ExperimentResult RunExperiment(const std::vector<Sample> &test_set, double fraction) const override;

  void SaveWeights(const std::string &path) const override;
  void LoadWeights(const std::string &path) override;

  std::string Name() const override { return "Matrix perceptron"; }

 private:
  struct ForwardCache {
    std::vector<Matrix> activations;  // activations[0] = input, last = output
  };

  ForwardCache Forward(const std::vector<double> &input) const;
  double TrainOneEpoch(const std::vector<Sample> &train_set, double learning_rate);
  double EvaluateMeanError(const std::vector<Sample> &test_set) const;

  std::vector<std::size_t> layer_sizes_;  // [input, hidden..., output]
  std::vector<Matrix> weights_;           // weights_[l]: layer l -> l+1
  std::vector<Matrix> biases_;            // biases_[l]: bias for layer l+1, shape (size, 1)
};

}  // namespace s21

#endif  // SRC_MODEL_MATRIX_PERCEPTRON_H_
