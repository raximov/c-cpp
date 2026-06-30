#ifndef SRC_MODEL_DATA_LOADER_H_
#define SRC_MODEL_DATA_LOADER_H_

#include <string>
#include <vector>

#include "perceptron_base.h"

namespace s21 {

class DataLoader {
 public:
  // Loads an EMNIST-letters style CSV file: each line is
  // "label,pixel0,pixel1,...,pixel783" with pixels in [0, 255] and
  // label in [1, 26] (1 = 'a', as in the original EMNIST mapping; this
  // is converted to a 0-based index internally).
  static std::vector<Sample> LoadCsv(const std::string &path);

  // Splits dataset into train/test, where test_ratio is in (0, 0.2].
  static void SplitTrainTest(const std::vector<Sample> &dataset, double test_ratio,
                              std::vector<Sample> *train, std::vector<Sample> *test);

  // Loads a BMP image (up to 512x512), converts to grayscale, resizes to
  // 28x28 and normalizes pixel values to [0, 1] to match the EMNIST format.
  static std::vector<double> LoadAndNormalizeBmp(const std::string &path);

  // Normalizes a 28x28 raw grayscale buffer (values 0..255) the same way
  // a hand-drawn canvas image is normalized before classification.
  static std::vector<double> NormalizeRaw28x28(const std::vector<unsigned char> &grayscale);
};

}  // namespace s21

#endif  // SRC_MODEL_DATA_LOADER_H_
