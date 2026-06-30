// Standalone smoke test: exercises the model layer (MatrixPerceptron,
// GraphPerceptron, save/load weights, RunExperiment) WITHOUT any GTK or
// GoogleTest dependency, so it can be compiled with just a plain g++.
//
// Build (run from inside the src/ directory):
//   g++ -std=c++20 -O2 -Wall -I. -o /tmp/smoke model/matrix_perceptron.cc
//       model/graph_perceptron.cc model/data_loader.cc controller/controller.cc
//       tests/smoke_test.cc
//
// Run:
//   /tmp/smoke

#include <iostream>
#include <vector>

#include "../controller/controller.h"
#include "../model/perceptron_base.h"

int main() {
  using namespace s21;

  // Build a tiny synthetic in-memory dataset (no CSV file needed).
  std::vector<Sample> train, test;
  for (int i = 0; i < 50; ++i) {
    Sample s;
    s.input.assign(kInputSize, (i % 26) / 26.0);
    s.label = i % 26;
    train.push_back(s);
  }
  test = train;

  std::cout << "== Matrix perceptron ==\n";
  MatrixPerceptron mp;
  mp.Configure({16, 8});
  auto rep = mp.Train(train, test, 3, 0.1, nullptr);
  std::cout << "epochs run: " << rep.epoch_errors.size()
            << ", last mean error: " << rep.epoch_errors.back() << "\n";

  std::cout << "\n== Graph perceptron ==\n";
  GraphPerceptron gp;
  gp.Configure({16, 8});
  auto rep2 = gp.Train(train, test, 3, 0.1, nullptr);
  std::cout << "epochs run: " << rep2.epoch_errors.size()
            << ", last mean error: " << rep2.epoch_errors.back() << "\n";

  std::cout << "\n== Experiment (matrix) ==\n";
  auto res = mp.RunExperiment(test, 1.0);
  std::cout << "accuracy=" << res.accuracy << " precision=" << res.precision
            << " recall=" << res.recall << " f-measure=" << res.f_measure
            << " time=" << res.total_time_seconds << "s\n";

  std::cout << "\n== Save/Load weights round-trip (matrix) ==\n";
  mp.SaveWeights("/tmp/w.bin");
  MatrixPerceptron mp2;
  mp2.Configure({16, 8});
  mp2.LoadWeights("/tmp/w.bin");
  std::cout << "predict before save = " << mp.Predict(train[0].input) << "\n";
  std::cout << "predict after load  = " << mp2.Predict(train[0].input) << "\n";

  std::cout << "\nAll smoke checks completed without exceptions.\n";
  return 0;
}
