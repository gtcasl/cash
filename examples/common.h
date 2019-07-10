#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <stdio.h>

#define CHECK(x) do { if (!(x)) { std::cout << "FAILED: " << #x << std::endl; std::abort(); } } while (false)

const uint64_t MAX_TICKS = 100000000;

inline bool readPGM(const char* filename,
                    uint32_t* width,
                    uint32_t* height,
                    std::vector<uint8_t>* image) {
  std::ifstream infile(filename);
  if (!infile) {
    std::cerr << "Error: invalid input file name." << std::endl;
    return false;
  }

  std::string line;

  // parse magic number
  std::getline(infile, line);
  if (line != "P5") {
    std::cerr << "Error: invalid file format." << std::endl;
    return false;
  }

  // parse comments
  do {
    std::getline(infile, line);
  } while (line[0] == '#');

  // parse image dimensions
  if (sscanf(line.c_str(), "%u %u", width, height) != 2) {
    std::cerr << "Error: invalid file format." << std::endl;
    return false;
  }

  std::getline(infile, line);
  if (line != "255") {
    std::cerr << "Error: invalid file format." << std::endl;
    return false;
  }

  // parse image data
  uint32_t image_size = *width * *height;
  image->resize(image_size);
  infile.read((char*)image->data(), image_size);

  return true;
}

inline bool writePGM(const std::vector<uint8_t>& image,
                     uint32_t width,
                     uint32_t height,
                     const char* filename) {
  std::ofstream outfile(filename);
  if (!outfile) {
    std::cerr << "Error: invalid output file name." << std::endl;
    return false;
  }

  outfile << "P5" << std::endl;
  outfile << "# Sobel filter output image" << std::endl;
  outfile << width << " " << height << std::endl;
  outfile << "255" << std::endl;
  outfile.write((const char*)image.data(), width * height);

  return true;
}

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class Matrix {
protected:

  std::vector<T> buffer_;
  size_t width_;
  size_t height_;

  friend std::ostream& operator<<(std::ostream& out, const Matrix& in) {
    for (size_t j = 0; j < in.height(); ++j) {
      for (size_t i = 0; i < in.width(); ++i) {
        out << in.at(i, j) << " ";
      }
      out << std::endl;
    }
    return out;
  }

public:

  Matrix(size_t width, size_t height)
    : buffer_(width * height)
    , width_(width)
    , height_(height)
  {}

  Matrix(size_t width, size_t height, const std::vector<T>& other)
    : buffer_(other)
    , width_(width)
    , height_(height) {
    assert(buffer_.size() == width * height);
  }

  auto width() const {
    return width_;
  }

  auto height() const {
    return height_;
  }

  const T& at(int x, int y) const {
    return buffer_.at(x + y * width_);
  }

  T& at(int x, int y) {
    return buffer_.at(x + y * width_);
  }

  bool operator==(const Matrix& other) const {
    if (width_ == other.width()
     && height_ == other.height()) {
      for (size_t j = 0; j < height_; ++j) {
        for (size_t i = 0; i < width_; ++i) {
          if (this->at(i, j) != other.at(i, j))
            return false;
        }
      }
    }
    return true;
  }

  bool operator!=(const Matrix& other) const {
    return !this->operator ==(other);
  }

  friend Matrix<T> operator*(const Matrix<T>& lhs, const Matrix<T>& rhs) {
    assert(lhs.width() == rhs.height());
    Matrix<T> out(rhs.width(), lhs.height());
    for (size_t j = 0; j < lhs.height(); ++j)  {
      for (size_t i = 0; i < rhs.width(); ++i) {
        int sum = 0;
        for (size_t m = 0; m < lhs.width(); ++m) {
            sum += lhs.at(m, j) * rhs.at(i, m);
        }
        out.at(i, j) = sum;
      }
    }
    return out;
  }
};
