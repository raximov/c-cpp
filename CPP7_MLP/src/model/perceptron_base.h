#ifndef SRC_MODEL_PERCEPTRON_BASE_H_
#define SRC_MODEL_PERCEPTRON_BASE_H_

#include <cstddef>
#include <functional>
#include <string>
#include <vector>

namespace s21 {

constexpr std::size_t kInputSize = 28 * 28;  // EMNIST-letters image is 28x28
constexpr std::size_t kOutputSize = 26;      // 26 latin letters

struct Sample {
  std::vector<double> input;  // normalized [0, 1], size kInputSize
  int label = 0;              // 0..25 (A..Z)
};

struct TrainingReport {
  std::vector<double> epoch_errors;  // mean error on test set per epoch
};

struct ExperimentResult {
  double accuracy = 0.0;
  double precision = 0.0;
  double recall = 0.0;
  double f_measure = 0.0;
  double total_time_seconds = 0.0;
};

// Common interface implemented both by the matrix-based and the
// graph-based perceptron so the Controller can use either one
// interchangeably (Strategy pattern).
class IPerceptron {
 public:
  virtual ~IPerceptron() = default;

  // hidden_layer_sizes.size() must be in [2, 5]
  virtual void Configure(const std::vector<std::size_t> &hidden_layer_sizes) = 0;

  // Runs one full training pass (all epochs) over train_set, evaluating
  // the mean error on test_set after every epoch. Reports progress via
  // the optional callback (epoch index, mean error) so the GUI can plot it.
  virtual TrainingReport Train(const std::vector<Sample> &train_set,
                                const std::vector<Sample> &test_set, int epochs,
                                double learning_rate,
                                const std::function<void(int, double)> &on_epoch = nullptr) = 0;

  // k-fold cross-validation training over the whole dataset.
  virtual TrainingReport TrainCrossValidation(const std::vector<Sample> &dataset, int k,
                                               int epochs_per_fold, double learning_rate) = 0;

  // Returns predicted label (0..25) for one normalized input image.
  virtual int Predict(const std::vector<double> &input) const = 0;

  // Runs the experiment on `fraction` (0..1) of test_set.
  virtual ExperimentResult RunExperiment(const std::vector<Sample> &test_set, double fraction) const = 0;

  virtual void SaveWeights(const std::string &path) const = 0;
  virtual void LoadWeights(const std::string &path) = 0;

  virtual std::string Name() const = 0;
};

}  // namespace s21

#endif  // SRC_MODEL_PERCEPTRON_BASE_H_
