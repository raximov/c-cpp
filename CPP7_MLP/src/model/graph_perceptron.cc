#include "graph_perceptron.h"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <numeric>
#include <random>
#include <stdexcept>

#include "activation.h"

namespace s21 {

Neuron::Neuron(std::size_t num_inputs) : weights_(num_inputs) {
  static thread_local std::mt19937 gen(std::random_device{}());
  std::uniform_real_distribution<double> dist(-0.5, 0.5);
  for (auto &w : weights_) w = dist(gen);
  bias_ = dist(gen);
}

double Neuron::Activate(const std::vector<double> &inputs) {
  double z = bias_;
  for (std::size_t i = 0; i < weights_.size(); ++i) z += weights_[i] * inputs[i];
  output_ = Sigmoid(z);
  return output_;
}

void GraphPerceptron::Configure(const std::vector<std::size_t> &hidden_layer_sizes) {
  if (hidden_layer_sizes.size() < 2 || hidden_layer_sizes.size() > 5)
    throw std::invalid_argument("GraphPerceptron: hidden layers count must be in [2, 5]");

  layer_sizes_.clear();
  layer_sizes_.push_back(kInputSize);
  for (auto s : hidden_layer_sizes) layer_sizes_.push_back(s);
  layer_sizes_.push_back(kOutputSize);

  layers_.clear();
  for (std::size_t l = 1; l < layer_sizes_.size(); ++l) {
    std::vector<Neuron> layer;
    layer.reserve(layer_sizes_[l]);
    for (std::size_t n = 0; n < layer_sizes_[l]; ++n) layer.emplace_back(layer_sizes_[l - 1]);
    layers_.push_back(std::move(layer));
  }
}

std::vector<double> GraphPerceptron::Forward(const std::vector<double> &input) const {
  std::vector<double> current = input;
  for (auto &layer : const_cast<std::vector<std::vector<Neuron>> &>(layers_)) {
    std::vector<double> next;
    next.reserve(layer.size());
    for (auto &neuron : layer) next.push_back(neuron.Activate(current));
    current = std::move(next);
  }
  return current;
}

double GraphPerceptron::TrainOneEpoch(const std::vector<Sample> &train_set, double learning_rate) {
  double total_error = 0.0;

  for (const auto &sample : train_set) {
    // Forward pass, keeping per-layer activations (including the input).
    std::vector<std::vector<double>> activations;
    activations.push_back(sample.input);
    std::vector<double> current = sample.input;
    for (auto &layer : layers_) {
      std::vector<double> next;
      next.reserve(layer.size());
      for (auto &neuron : layer) next.push_back(neuron.Activate(current));
      activations.push_back(next);
      current = next;
    }

    std::vector<double> target(kOutputSize, 0.0);
    target[sample.label] = 1.0;

    // Output layer deltas.
    auto &output_layer = layers_.back();
    for (std::size_t i = 0; i < output_layer.size(); ++i) {
      double out = output_layer[i].output();
      double diff = out - target[i];
      total_error += diff * diff;
      output_layer[i].set_delta(diff * SigmoidDerivativeFromOutput(out));
    }

    // Backpropagate hidden layers.
    for (std::size_t l = layers_.size() - 1; l-- > 0;) {
      auto &layer = layers_[l];
      auto &next_layer = layers_[l + 1];
      for (std::size_t i = 0; i < layer.size(); ++i) {
        double sum = 0.0;
        for (std::size_t j = 0; j < next_layer.size(); ++j)
          sum += next_layer[j].weights()[i] * next_layer[j].delta();
        layer[i].set_delta(sum * SigmoidDerivativeFromOutput(layer[i].output()));
      }
    }

    // Update weights using the activations recorded during the forward pass.
    for (std::size_t l = 0; l < layers_.size(); ++l) {
      const std::vector<double> &prev_activation = activations[l];
      for (auto &neuron : layers_[l]) {
        for (std::size_t w = 0; w < neuron.weights().size(); ++w)
          neuron.weights()[w] -= learning_rate * neuron.delta() * prev_activation[w];
        neuron.bias() -= learning_rate * neuron.delta();
      }
    }
  }
  return train_set.empty() ? 0.0 : total_error / train_set.size();
}

double GraphPerceptron::EvaluateMeanError(const std::vector<Sample> &test_set) const {
  if (test_set.empty()) return 0.0;
  double total_error = 0.0;
  for (const auto &sample : test_set) {
    std::vector<double> output = Forward(sample.input);
    for (std::size_t i = 0; i < output.size(); ++i) {
      double target = (static_cast<int>(i) == sample.label) ? 1.0 : 0.0;
      double diff = output[i] - target;
      total_error += diff * diff;
    }
  }
  return total_error / test_set.size();
}

TrainingReport GraphPerceptron::Train(const std::vector<Sample> &train_set,
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

TrainingReport GraphPerceptron::TrainCrossValidation(const std::vector<Sample> &dataset, int k,
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

int GraphPerceptron::Predict(const std::vector<double> &input) const {
  std::vector<double> output = Forward(input);
  int best = 0;
  double best_val = output[0];
  for (std::size_t i = 1; i < output.size(); ++i) {
    if (output[i] > best_val) {
      best_val = output[i];
      best = static_cast<int>(i);
    }
  }
  return best;
}

ExperimentResult GraphPerceptron::RunExperiment(const std::vector<Sample> &test_set,
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

void GraphPerceptron::SaveWeights(const std::string &path) const {
  std::ofstream out(path, std::ios::binary);
  if (!out) throw std::runtime_error("GraphPerceptron::SaveWeights: cannot open file " + path);

  std::size_t num_layers = layer_sizes_.size();
  out.write(reinterpret_cast<const char *>(&num_layers), sizeof(num_layers));
  for (auto s : layer_sizes_) out.write(reinterpret_cast<const char *>(&s), sizeof(s));

  for (const auto &layer : layers_) {
    for (const auto &neuron : layer) {
      out.write(reinterpret_cast<const char *>(neuron.weights().data()),
                neuron.weights().size() * sizeof(double));
      double b = neuron.bias();
      out.write(reinterpret_cast<const char *>(&b), sizeof(b));
    }
  }
}

void GraphPerceptron::LoadWeights(const std::string &path) {
  std::ifstream in(path, std::ios::binary);
  if (!in) throw std::runtime_error("GraphPerceptron::LoadWeights: cannot open file " + path);

  std::size_t num_layers = 0;
  in.read(reinterpret_cast<char *>(&num_layers), sizeof(num_layers));
  std::vector<std::size_t> sizes(num_layers);
  for (auto &s : sizes) in.read(reinterpret_cast<char *>(&s), sizeof(s));
  layer_sizes_ = sizes;

  layers_.clear();
  for (std::size_t l = 1; l < layer_sizes_.size(); ++l) {
    std::vector<Neuron> layer;
    layer.reserve(layer_sizes_[l]);
    for (std::size_t n = 0; n < layer_sizes_[l]; ++n) layer.emplace_back(layer_sizes_[l - 1]);
    layers_.push_back(std::move(layer));
  }

  for (auto &layer : layers_) {
    for (auto &neuron : layer) {
      in.read(reinterpret_cast<char *>(neuron.weights().data()),
              neuron.weights().size() * sizeof(double));
      double b = 0.0;
      in.read(reinterpret_cast<char *>(&b), sizeof(b));
      neuron.bias() = b;
    }
  }
}

}  // namespace s21
