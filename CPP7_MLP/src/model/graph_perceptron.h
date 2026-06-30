#ifndef SRC_MODEL_GRAPH_PERCEPTRON_H_
#define SRC_MODEL_GRAPH_PERCEPTRON_H_

#include <memory>
#include <string>
#include <vector>

#include "perceptron_base.h"

namespace s21 {

// Each neuron is an explicit node object holding references (indices) to
// the neurons of the previous layer together with the weight of each
// connection. This is the "graph form" required by the project, as
// opposed to MatrixPerceptron which stores whole layers as matrices.
class Neuron {
 public:
  Neuron() = default;
  explicit Neuron(std::size_t num_inputs);

  double Activate(const std::vector<double> &inputs);  // returns sigmoid output, caches it
  double output() const { return output_; }
  double delta() const { return delta_; }
  void set_delta(double d) { delta_ = d; }

  std::vector<double> &weights() { return weights_; }
  const std::vector<double> &weights() const { return weights_; }
  double &bias() { return bias_; }
  double bias() const { return bias_; }

 private:
  std::vector<double> weights_;  // one weight per incoming connection
  double bias_ = 0.0;
  double output_ = 0.0;
  double delta_ = 0.0;  // error term used during backpropagation
};

class GraphPerceptron : public IPerceptron {
 public:
  GraphPerceptron() = default;

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

  std::string Name() const override { return "Graph perceptron"; }

 private:
  std::vector<double> Forward(const std::vector<double> &input) const;
  double TrainOneEpoch(const std::vector<Sample> &train_set, double learning_rate);
  double EvaluateMeanError(const std::vector<Sample> &test_set) const;

  std::vector<std::size_t> layer_sizes_;
  // layers_[l] = neurons of layer l+1 (layers_[0] is the first hidden layer)
  std::vector<std::vector<Neuron>> layers_;
};

}  // namespace s21

#endif  // SRC_MODEL_GRAPH_PERCEPTRON_H_
