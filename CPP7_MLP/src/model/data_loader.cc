#include "data_loader.h"

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <random>
#include <sstream>
#include <stdexcept>

namespace s21 {

namespace {

#pragma pack(push, 1)
struct BmpFileHeader {
  uint16_t type;
  uint32_t size;
  uint16_t reserved1;
  uint16_t reserved2;
  uint32_t offset_data;
};

struct BmpInfoHeader {
  uint32_t size;
  int32_t width;
  int32_t height;
  uint16_t planes;
  uint16_t bit_count;
  uint32_t compression;
  uint32_t size_image;
  int32_t x_pixels_per_meter;
  int32_t y_pixels_per_meter;
  uint32_t colors_used;
  uint32_t colors_important;
};
#pragma pack(pop)

}  // namespace

std::vector<Sample> DataLoader::LoadCsv(const std::string &path) {
  std::ifstream file(path);
  if (!file) throw std::runtime_error("DataLoader::LoadCsv: cannot open file " + path);

  std::vector<Sample> dataset;
  std::string line;
  while (std::getline(file, line)) {
    if (line.empty()) continue;
    std::istringstream ss(line);
    std::string token;
    Sample sample;
    sample.input.reserve(kInputSize);

    std::getline(ss, token, ',');
    int raw_label = std::stoi(token);
    sample.label = raw_label - 1;  // EMNIST-letters uses 1-based labels

    while (std::getline(ss, token, ',')) {
      double pixel = std::stod(token) / 255.0;
      sample.input.push_back(pixel);
    }
    if (sample.input.size() != kInputSize)
      throw std::runtime_error("DataLoader::LoadCsv: malformed row (expected " +
                                std::to_string(kInputSize) + " pixels, got " +
                                std::to_string(sample.input.size()) + ")");
    dataset.push_back(std::move(sample));
  }
  return dataset;
}

void DataLoader::SplitTrainTest(const std::vector<Sample> &dataset, double test_ratio,
                                 std::vector<Sample> *train, std::vector<Sample> *test) {
  if (test_ratio < 0.0 || test_ratio > 0.2)
    throw std::invalid_argument("DataLoader::SplitTrainTest: test_ratio must be in [0, 0.2]");

  std::vector<std::size_t> indices(dataset.size());
  for (std::size_t i = 0; i < indices.size(); ++i) indices[i] = i;
  static thread_local std::mt19937 gen(std::random_device{}());
  std::shuffle(indices.begin(), indices.end(), gen);

  std::size_t test_count = static_cast<std::size_t>(dataset.size() * test_ratio);
  train->clear();
  test->clear();
  for (std::size_t i = 0; i < indices.size(); ++i) {
    if (i < test_count)
      test->push_back(dataset[indices[i]]);
    else
      train->push_back(dataset[indices[i]]);
  }
}

std::vector<double> DataLoader::NormalizeRaw28x28(const std::vector<unsigned char> &grayscale) {
  if (grayscale.size() != kInputSize)
    throw std::invalid_argument("DataLoader::NormalizeRaw28x28: expected 28x28 buffer");
  std::vector<double> result(kInputSize);
  for (std::size_t i = 0; i < kInputSize; ++i) result[i] = grayscale[i] / 255.0;
  return result;
}

std::vector<double> DataLoader::LoadAndNormalizeBmp(const std::string &path) {
  std::ifstream file(path, std::ios::binary);
  if (!file) throw std::runtime_error("DataLoader::LoadAndNormalizeBmp: cannot open file " + path);

  BmpFileHeader file_header{};
  BmpInfoHeader info_header{};
  file.read(reinterpret_cast<char *>(&file_header), sizeof(file_header));
  file.read(reinterpret_cast<char *>(&info_header), sizeof(info_header));

  if (file_header.type != 0x4D42) throw std::runtime_error("DataLoader: not a valid BMP file");
  if (info_header.bit_count != 24 && info_header.bit_count != 8)
    throw std::runtime_error("DataLoader: only 8-bit or 24-bit BMP supported");

  int width = info_header.width;
  int height = std::abs(info_header.height);
  bool top_down = info_header.height < 0;
  if (width <= 0 || width > 512 || height <= 0 || height > 512)
    throw std::runtime_error("DataLoader: BMP dimensions must be within 1..512");

  // Skip palette for 8-bit images, then jump to pixel data.
  file.seekg(file_header.offset_data, std::ios::beg);

  int bytes_per_pixel = info_header.bit_count / 8;
  int row_padded = (width * bytes_per_pixel + 3) & (~3);
  std::vector<unsigned char> row_buffer(row_padded);
  std::vector<unsigned char> gray(width * height);

  for (int y = 0; y < height; ++y) {
    file.read(reinterpret_cast<char *>(row_buffer.data()), row_padded);
    int dest_row = top_down ? y : (height - 1 - y);
    for (int x = 0; x < width; ++x) {
      unsigned char value;
      if (bytes_per_pixel == 3) {
        unsigned char b = row_buffer[x * 3 + 0];
        unsigned char g = row_buffer[x * 3 + 1];
        unsigned char r = row_buffer[x * 3 + 2];
        value = static_cast<unsigned char>(0.299 * r + 0.587 * g + 0.114 * b);
      } else {
        value = row_buffer[x];
      }
      gray[dest_row * width + x] = value;
    }
  }

  // Nearest-neighbor resize to 28x28.
  std::vector<unsigned char> resized(28 * 28);
  for (int y = 0; y < 28; ++y) {
    for (int x = 0; x < 28; ++x) {
      int src_x = x * width / 28;
      int src_y = y * height / 28;
      resized[y * 28 + x] = gray[src_y * width + src_x];
    }
  }
  return NormalizeRaw28x28(resized);
}

}  // namespace s21
