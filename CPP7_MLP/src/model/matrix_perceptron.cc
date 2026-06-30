#include "matrix_perceptron.h"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <numeric>
#include <random>
#include <stdexcept>

#include "activation.h"

namespace s21 {

void MatrixPerceptron::Configure(const std::vector<std::size_t> &hidden_layer_sizes) {
  if (hidden_layer_sizes.size() < 2 || hidden_layer_sizes.size() > 5)
    throw std::invalid_argument("MatrixPerceptron: hidden layers count must be in [2, 5]");

  layer_sizes_.clear();
  layer_sizes_.push_back(kInputSize);
  for (auto s : hidden_layer_sizes) layer_sizes_.push_back(s);
  layer_sizes_.push_back(kOutputSize);

  weights_.clear();
  biases_.clear();
  for (std::size_t l = 0; l + 1 < layer_sizes_.size(); ++l) {
    weights_.push_back(Matrix::Random(layer_sizes_[l + 1], layer_sizes_[l]));
    biases_.push_back(Matrix::Random(layer_sizes_[l + 1], 1));
  }
}

MatrixPerceptron::ForwardCache MatrixPerceptron::Forward(const std::vector<double> &input) const {
  ForwardCache cache;
  Matrix a(input.size(), 1);
  for (std::size_t i = 0; i < input.size(); ++i) a.at(i, 0) = input[i];
  cache.activations.push_back(a);

  for (std::size_t l = 0; l < weights_.size(); ++l) {
    Matrix z = weights_[l].Multiply(a).Add(biases_[l]);
    a = z.Apply(Sigmoid);
    cache.activations.push_back(a);
  }
  return cache;
}

double MatrixPerceptron::TrainOneEpoch(const std::vector<Sample> &train_set, double learning_rate) {
  double total_error = 0.0;
  for (const auto &sample : train_set) {
    ForwardCache cache = Forward(sample.input);

    Matrix target(kOutputSize, 1);
    target.at(sample.label, 0) = 1.0;

    // Output layer error (dC/dz for sigmoid + MSE-like loss).
    Matrix output = cache.activations.back();
    Matrix delta = output.Subtract(target).HadamardProduct(output.Apply(SigmoidDerivativeFromOutput));

    for (std::size_t i = 0; i < output.rows(); ++i) {
      double diff = output.at(i, 0) - target.at(i, 0);
      total_error += diff * diff;
    }

    // Backpropagate through layers, last to first.
    for (std::size_t li = weights_.size(); li-- > 0;) {
      const Matrix &prev_activation = cache.activations[li];
      Matrix grad_w = delta.Multiply(prev_activation.Transpose());
      weights_[li] = weights_[li].Subtract(grad_w.ScalarMultiply(learning_rate));
      biases_[li] = biases_[li].Subtract(delta.ScalarMultiply(learning_rate));

      if (li > 0) {
        Matrix wt = weights_[li].Transpose();
        Matrix propagated = wt.Multiply(delta);
        Matrix act = cache.activations[li];
        delta = propagated.HadamardProduct(act.Apply(SigmoidDerivativeFromOutput));
      }
    }
  }
  return train_set.empty() ? 0.0 : total_error / train_set.size();
}

double MatrixPerceptron::EvaluateMeanError(const std::vector<Sample> &test_set) const {
  if (test_set.empty()) return 0.0;
  double total_error = 0.0;
  for (const auto &sample : test_set) {
    ForwardCache cache = Forward(sample.input);
    const Matrix &output = cache.activations.back();
    for (std::size_t i = 0; i < output.rows(); ++i) {
      double target = (static_cast<int>(i) == sample.label) ? 1.0 : 0.0;
      double diff = output.at(i, 0) - target;
      total_error += diff * diff;
    }
  }
  return total_error / test_set.size();
}

TrainingReport MatrixPerceptron::Train(const std::vector<Sample> &train_set,
                                        const std::vector<Sample> &test_set, int epochs,
                                        double learning_rate,
                                        const std::function<void(int, double)> &on_epoch) {
  TrainingReport report;
  for (int e = 0; e < epochs; ++e) {
    TrainOneEpoch(train_set, learning_rate);
    double mean_error = EvaluateMeanError(test_set);
    report.epoch_errors.push_back(mean_error);
    if (on_epoch) on_epoch(e, mean_error);
  }
  return report;
}

TrainingReport MatrixPerceptron::TrainCrossValidation(const std::vector<Sample> &dataset, int k,
                                                        int epochs_per_fold, double learning_rate) {
  if (k < 2) throw std::invalid_argument("TrainCrossValidation: k must be >= 2");
  TrainingReport report;
  std::size_t fold_size = dataset.size() / k;

  for (int fold = 0; fold < k; ++fold) {
    std::vector<Sample> test_fold, train_fold;
    std::size_t start = fold * fold_size;
    std::size_t end = (fold == k - 1) ? dataset.size() : start + fold_size;
    for (std::size_t i = 0; i < dataset.size(); ++i) {
      if (i >= start && i < end)
        test_fold.push_back(dataset[i]);
      else
        train_fold.push_back(dataset[i]);
    }
    for (int e = 0; e < epochs_per_fold; ++e) {
      TrainOneEpoch(train_fold, learning_rate);
      report.epoch_errors.push_back(EvaluateMeanError(test_fold));
    }
  }
  return report;
}

int MatrixPerceptron::Predict(const std::vector<double> &input) const {
  ForwardCache cache = Forward(input);
  const Matrix &output = cache.activations.back();
  int best = 0;
  double best_val = output.at(0, 0);
  for (std::size_t i = 1; i < output.rows(); ++i) {
    if (output.at(i, 0) > best_val) {
      best_val = output.at(i, 0);
      best = static_cast<int>(i);
    }
  }
  return best;
}

ExperimentResult MatrixPerceptron::RunExperiment(const std::vector<Sample> &test_set,
                                                   double fraction) const {
  fraction = std::clamp(fraction, 0.0, 1.0);
  std::size_t n = static_cast<std::size_t>(test_set.size() * fraction);

  std::vector<int> predicted, actual;
  predicted.reserve(n);
  actual.reserve(n);

  auto start = std::chrono::steady_clock::now();
  for (std::size_t i = 0; i < n; ++i) {
    predicted.push_back(Predict(test_set[i].input));
    actual.push_back(test_set[i].label);
  }
  auto end = std::chrono::steady_clock::now();

  ExperimentResult result;
  result.total_time_seconds = std::chrono::duration<double>(end - start).count();
  ComputeClassificationMetrics(predicted, actual, &result.accuracy, &result.precision, &result.recall,
                                &result.f_measure);
  return result;
}

void MatrixPerceptron::SaveWeights(const std::string &path) const {
  std::ofstream out(path, std::ios::binary);
  if (!out) throw std::runtime_error("MatrixPerceptron::SaveWeights: cannot open file " + path);

  std::size_t num_layers = layer_sizes_.size();
  out.write(reinterpret_cast<const char *>(&num_layers), sizeof(num_layers));
  for (auto s : layer_sizes_) out.write(reinterpret_cast<const char *>(&s), sizeof(s));

  for (const auto &w : weights_) out.write(reinterpret_cast<const char *>(w.raw().data()),
                                            w.raw().size() * sizeof(double));
  for (const auto &b : biases_) out.write(reinterpret_cast<const char *>(b.raw().data()),
                                           b.raw().size() * sizeof(double));
}

void MatrixPerceptron::LoadWeights(const std::string &path) {
  std::ifstream in(path, std::ios::binary);
  if (!in) throw std::runtime_error("MatrixPerceptron::LoadWeights: cannot open file " + path);

  std::size_t num_layers = 0;
  in.read(reinterpret_cast<char *>(&num_layers), sizeof(num_layers));
  std::vector<std::size_t> sizes(num_layers);
  for (auto &s : sizes) in.read(reinterpret_cast<char *>(&s), sizeof(s));

  layer_sizes_ = sizes;
  weights_.clear();
  biases_.clear();
  for (std::size_t l = 0; l + 1 < layer_sizes_.size(); ++l) {
    weights_.push_back(Matrix(layer_sizes_[l + 1], layer_sizes_[l]));
    biases_.push_back(Matrix(layer_sizes_[l + 1], 1));
  }
  for (auto &w : weights_) in.read(reinterpret_cast<char *>(w.raw().data()),
                                    w.raw().size() * sizeof(double));
  for (auto &b : biases_) in.read(reinterpret_cast<char *>(b.raw().data()),
                                   b.raw().size() * sizeof(double));
}

}  // namespace s21
