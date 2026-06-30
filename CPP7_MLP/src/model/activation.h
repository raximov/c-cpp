#ifndef SRC_MODEL_ACTIVATION_H_
#define SRC_MODEL_ACTIVATION_H_

#include <cmath>
#include <numeric>
#include <vector>

#include "perceptron_base.h"

namespace s21 {

inline double Sigmoid(double x) { return 1.0 / (1.0 + std::exp(-x)); }

// Derivative expressed in terms of the already-computed sigmoid output y.
inline double SigmoidDerivativeFromOutput(double y) { return y * (1.0 - y); }

// Computes accuracy / precision / recall / f-measure (macro-averaged over
// the 26 classes) from parallel vectors of predicted and true labels.
inline void ComputeClassificationMetrics(const std::vector<int> &predicted,
                                          const std::vector<int> &actual, double *accuracy,
                                          double *precision, double *recall, double *f_measure) {
  const int kClasses = static_cast<int>(kOutputSize);
  std::vector<int> tp(kClasses, 0), fp(kClasses, 0), fn(kClasses, 0);
  std::size_t correct = 0;
  for (std::size_t i = 0; i < predicted.size(); ++i) {
    if (predicted[i] == actual[i]) {
      ++correct;
      ++tp[actual[i]];
    } else {
      ++fp[predicted[i]];
      ++fn[actual[i]];
    }
  }
  *accuracy = predicted.empty() ? 0.0 : static_cast<double>(correct) / predicted.size();

  double precision_sum = 0.0, recall_sum = 0.0;
  int classes_seen = 0;
  for (int c = 0; c < kClasses; ++c) {
    if (tp[c] + fp[c] + fn[c] == 0) continue;
    double p = (tp[c] + fp[c] > 0) ? static_cast<double>(tp[c]) / (tp[c] + fp[c]) : 0.0;
    double r = (tp[c] + fn[c] > 0) ? static_cast<double>(tp[c]) / (tp[c] + fn[c]) : 0.0;
    precision_sum += p;
    recall_sum += r;
    ++classes_seen;
  }
  *precision = classes_seen ? precision_sum / classes_seen : 0.0;
  *recall = classes_seen ? recall_sum / classes_seen : 0.0;
  *f_measure = (*precision + *recall > 0.0) ? 2 * (*precision) * (*recall) / (*precision + *recall) : 0.0;
}

}  // namespace s21

#endif  // SRC_MODEL_ACTIVATION_H_
