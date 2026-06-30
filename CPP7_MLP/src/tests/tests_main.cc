#include <gtest/gtest.h>

#include <cmath>

#include "../model/activation.h"
#include "../model/data_loader.h"
#include "../model/graph_perceptron.h"
#include "../model/matrix.h"
#include "../model/matrix_perceptron.h"

namespace s21 {
namespace {

TEST(MatrixTest, MultiplyIdentity) {
  Matrix a(2, 2);
  a.at(0, 0) = 1;
  a.at(0, 1) = 0;
  a.at(1, 0) = 0;
  a.at(1, 1) = 1;
  Matrix b(2, 2);
  b.at(0, 0) = 5;
  b.at(0, 1) = 6;
  b.at(1, 0) = 7;
  b.at(1, 1) = 8;
  Matrix c = a.Multiply(b);
  EXPECT_DOUBLE_EQ(c.at(0, 0), 5);
  EXPECT_DOUBLE_EQ(c.at(0, 1), 6);
  EXPECT_DOUBLE_EQ(c.at(1, 0), 7);
  EXPECT_DOUBLE_EQ(c.at(1, 1), 8);
}

TEST(MatrixTest, MultiplyDimensionMismatchThrows) {
  Matrix a(2, 3);
  Matrix b(2, 2);
  EXPECT_THROW(a.Multiply(b), std::invalid_argument);
}

TEST(MatrixTest, AddSubtract) {
  Matrix a(2, 2), b(2, 2);
  a.at(0, 0) = 1;
  b.at(0, 0) = 2;
  Matrix sum = a.Add(b);
  EXPECT_DOUBLE_EQ(sum.at(0, 0), 3);
  Matrix diff = b.Subtract(a);
  EXPECT_DOUBLE_EQ(diff.at(0, 0), 1);
}

TEST(MatrixTest, Transpose) {
  Matrix a(2, 3);
  a.at(0, 1) = 9;
  Matrix t = a.Transpose();
  EXPECT_EQ(t.rows(), 3u);
  EXPECT_EQ(t.cols(), 2u);
  EXPECT_DOUBLE_EQ(t.at(1, 0), 9);
}

TEST(MatrixTest, HadamardProduct) {
  Matrix a(1, 3), b(1, 3);
  a.at(0, 0) = 2;
  a.at(0, 1) = 3;
  a.at(0, 2) = 4;
  b.at(0, 0) = 5;
  b.at(0, 1) = 6;
  b.at(0, 2) = 7;
  Matrix h = a.HadamardProduct(b);
  EXPECT_DOUBLE_EQ(h.at(0, 0), 10);
  EXPECT_DOUBLE_EQ(h.at(0, 1), 18);
  EXPECT_DOUBLE_EQ(h.at(0, 2), 28);
}

TEST(ActivationTest, SigmoidBounds) {
  EXPECT_NEAR(Sigmoid(0.0), 0.5, 1e-9);
  EXPECT_GT(Sigmoid(10.0), 0.99);
  EXPECT_LT(Sigmoid(-10.0), 0.01);
}

TEST(ActivationTest, MetricsPerfectPrediction) {
  std::vector<int> pred = {0, 1, 2, 3};
  std::vector<int> actual = {0, 1, 2, 3};
  double acc, prec, rec, f1;
  ComputeClassificationMetrics(pred, actual, &acc, &prec, &rec, &f1);
  EXPECT_DOUBLE_EQ(acc, 1.0);
  EXPECT_DOUBLE_EQ(prec, 1.0);
  EXPECT_DOUBLE_EQ(rec, 1.0);
  EXPECT_DOUBLE_EQ(f1, 1.0);
}

TEST(ActivationTest, MetricsAllWrong) {
  std::vector<int> pred = {1, 0};
  std::vector<int> actual = {0, 1};
  double acc, prec, rec, f1;
  ComputeClassificationMetrics(pred, actual, &acc, &prec, &rec, &f1);
  EXPECT_DOUBLE_EQ(acc, 0.0);
}

std::vector<Sample> MakeTinyDataset(int count) {
  std::vector<Sample> data;
  for (int i = 0; i < count; ++i) {
    Sample s;
    s.input.assign(kInputSize, (i % kOutputSize) / static_cast<double>(kOutputSize));
    s.label = i % kOutputSize;
    data.push_back(s);
  }
  return data;
}

TEST(MatrixPerceptronTest, ConfigureRejectsInvalidLayerCount) {
  MatrixPerceptron mp;
  EXPECT_THROW(mp.Configure({8}), std::invalid_argument);
  EXPECT_THROW(mp.Configure({8, 8, 8, 8, 8, 8}), std::invalid_argument);
  EXPECT_NO_THROW(mp.Configure({8, 8}));
}

TEST(MatrixPerceptronTest, TrainReducesErrorOnTinySet) {
  MatrixPerceptron mp;
  mp.Configure({16, 8});
  auto data = MakeTinyDataset(26);
  auto report = mp.Train(data, data, 20, 0.5, nullptr);
  ASSERT_FALSE(report.epoch_errors.empty());
  EXPECT_LE(report.epoch_errors.back(), report.epoch_errors.front());
}

TEST(MatrixPerceptronTest, PredictReturnsValidLabel) {
  MatrixPerceptron mp;
  mp.Configure({8, 8});
  auto data = MakeTinyDataset(5);
  int label = mp.Predict(data[0].input);
  EXPECT_GE(label, 0);
  EXPECT_LT(label, static_cast<int>(kOutputSize));
}

TEST(MatrixPerceptronTest, SaveLoadRoundTrip) {
  MatrixPerceptron mp;
  mp.Configure({8, 8});
  auto data = MakeTinyDataset(5);
  int before = mp.Predict(data[0].input);

  std::string path = "/tmp/s21_test_weights_matrix.bin";
  mp.SaveWeights(path);

  MatrixPerceptron mp2;
  mp2.Configure({8, 8});
  mp2.LoadWeights(path);
  int after = mp2.Predict(data[0].input);
  EXPECT_EQ(before, after);
}

TEST(GraphPerceptronTest, ConfigureRejectsInvalidLayerCount) {
  GraphPerceptron gp;
  EXPECT_THROW(gp.Configure({8}), std::invalid_argument);
  EXPECT_NO_THROW(gp.Configure({8, 8, 8}));
}

TEST(GraphPerceptronTest, TrainReducesErrorOnTinySet) {
  GraphPerceptron gp;
  gp.Configure({16, 8});
  auto data = MakeTinyDataset(26);
  auto report = gp.Train(data, data, 20, 0.5, nullptr);
  ASSERT_FALSE(report.epoch_errors.empty());
  EXPECT_LE(report.epoch_errors.back(), report.epoch_errors.front());
}

TEST(GraphPerceptronTest, SaveLoadRoundTrip) {
  GraphPerceptron gp;
  gp.Configure({8, 8});
  auto data = MakeTinyDataset(5);
  int before = gp.Predict(data[0].input);

  std::string path = "/tmp/s21_test_weights_graph.bin";
  gp.SaveWeights(path);

  GraphPerceptron gp2;
  gp2.Configure({8, 8});
  gp2.LoadWeights(path);
  int after = gp2.Predict(data[0].input);
  EXPECT_EQ(before, after);
}

TEST(DataLoaderTest, SplitTrainTestRespectsRatio) {
  auto data = MakeTinyDataset(100);
  std::vector<Sample> train, test;
  DataLoader::SplitTrainTest(data, 0.2, &train, &test);
  EXPECT_EQ(test.size(), 20u);
  EXPECT_EQ(train.size(), 80u);
}

TEST(DataLoaderTest, SplitTrainTestRejectsInvalidRatio) {
  auto data = MakeTinyDataset(10);
  std::vector<Sample> train, test;
  EXPECT_THROW(DataLoader::SplitTrainTest(data, 0.5, &train, &test), std::invalid_argument);
}

TEST(DataLoaderTest, NormalizeRaw28x28) {
  std::vector<unsigned char> raw(kInputSize, 255);
  auto normalized = DataLoader::NormalizeRaw28x28(raw);
  EXPECT_DOUBLE_EQ(normalized[0], 1.0);
}

}  // namespace
}  // namespace s21

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
