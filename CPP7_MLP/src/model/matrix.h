#ifndef SRC_MODEL_MATRIX_H_
#define SRC_MODEL_MATRIX_H_

#include <cstddef>
#include <random>
#include <stdexcept>
#include <vector>

namespace s21 {

// Simple dense matrix used by the matrix-form perceptron.
class Matrix {
 public:
  Matrix() = default;
  Matrix(std::size_t rows, std::size_t cols) : rows_(rows), cols_(cols), data_(rows * cols, 0.0) {}

  static Matrix Random(std::size_t rows, std::size_t cols, double low = -0.5, double high = 0.5) {
    Matrix m(rows, cols);
    static thread_local std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<double> dist(low, high);
    for (auto &v : m.data_) v = dist(gen);
    return m;
  }

  std::size_t rows() const { return rows_; }
  std::size_t cols() const { return cols_; }

  double &at(std::size_t r, std::size_t c) { return data_[r * cols_ + c]; }
  double at(std::size_t r, std::size_t c) const { return data_[r * cols_ + c]; }

  // Matrix multiplication: (rows_ x cols_) * (other.rows_ x other.cols_)
  Matrix Multiply(const Matrix &other) const {
    if (cols_ != other.rows_) throw std::invalid_argument("Matrix::Multiply: dimension mismatch");
    Matrix res(rows_, other.cols_);
    for (std::size_t i = 0; i < rows_; ++i) {
      for (std::size_t k = 0; k < cols_; ++k) {
        double a = at(i, k);
        if (a == 0.0) continue;
        for (std::size_t j = 0; j < other.cols_; ++j) {
          res.at(i, j) += a * other.at(k, j);
        }
      }
    }
    return res;
  }

  Matrix Transpose() const {
    Matrix res(cols_, rows_);
    for (std::size_t i = 0; i < rows_; ++i)
      for (std::size_t j = 0; j < cols_; ++j) res.at(j, i) = at(i, j);
    return res;
  }

  Matrix Add(const Matrix &other) const {
    CheckSameShape(other);
    Matrix res(rows_, cols_);
    for (std::size_t i = 0; i < data_.size(); ++i) res.data_[i] = data_[i] + other.data_[i];
    return res;
  }

  Matrix Subtract(const Matrix &other) const {
    CheckSameShape(other);
    Matrix res(rows_, cols_);
    for (std::size_t i = 0; i < data_.size(); ++i) res.data_[i] = data_[i] - other.data_[i];
    return res;
  }

  // Element-wise (Hadamard) product
  Matrix HadamardProduct(const Matrix &other) const {
    CheckSameShape(other);
    Matrix res(rows_, cols_);
    for (std::size_t i = 0; i < data_.size(); ++i) res.data_[i] = data_[i] * other.data_[i];
    return res;
  }

  Matrix ScalarMultiply(double s) const {
    Matrix res(rows_, cols_);
    for (std::size_t i = 0; i < data_.size(); ++i) res.data_[i] = data_[i] * s;
    return res;
  }

  template <typename Fn>
  Matrix Apply(Fn fn) const {
    Matrix res(rows_, cols_);
    for (std::size_t i = 0; i < data_.size(); ++i) res.data_[i] = fn(data_[i]);
    return res;
  }

  const std::vector<double> &raw() const { return data_; }
  std::vector<double> &raw() { return data_; }

 private:
  void CheckSameShape(const Matrix &other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_)
      throw std::invalid_argument("Matrix: shape mismatch");
  }

  std::size_t rows_ = 0;
  std::size_t cols_ = 0;
  std::vector<double> data_;
};

}  // namespace s21

#endif  // SRC_MODEL_MATRIX_H_
