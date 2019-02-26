#include <iostream>
#include <vector>
#include <assert.h>
#include <cash.h>
#include <htl/counter.h>

using namespace ch::logic;
using namespace ch::htl;
using namespace ch::system;

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

///////////////////////////////////////////////////////////////////////////////

template <uint I, uint O>
struct MAC {
  __io (
    __in  (ch_bool)   enable,
    __in  (ch_int<I>) a_in,
    __in  (ch_int<I>) b_in,
    __out (ch_int<I>) a_out,
    __out (ch_int<I>) b_out,
    __out (ch_int<O>) c_out
  );

  void describe() {
    io.a_out = ch_nextEn(io.a_in, io.enable, 0);
    io.b_out = ch_nextEn(io.b_in, io.enable, 0);
    io.c_out = ch_nextEn(io.c_out + ch_mul<O>(io.a_in, io.b_in), io.enable, 0);
  }
};

template <unsigned I, unsigned O, unsigned N, unsigned P, unsigned M>
struct MatMul {
  __io (
    __in  (ch_bool) valid_in,
    __in  (ch_vec<ch_int<I>, N>) a_in,
    __in  (ch_vec<ch_int<I>, P>) b_in,
    __out (ch_vec<ch_vec<ch_int<O>, P>, N>) c_out,
    __out (ch_bool) valid_out
  );

  void describe() {
    // systolic array of MAC units
    std::array<std::array<ch_module<MAC<I, O>>, P>, N> macs;
    ch_counter<N+P+M> ctr(io.valid_in);

    for (unsigned r = 0; r < N; ++r) {
      for (unsigned c = 0; c < P; ++c) {
        macs[r][c].io.enable = io.valid_in;
        macs[r][c].io.a_in = c ? macs[r][c-1].io.a_out.as_int() : ch_delayEn(io.a_in[r], io.valid_in, r, 0);
        macs[r][c].io.b_in = r ? macs[r-1][c].io.b_out.as_int() : ch_delayEn(io.b_in[c], io.valid_in, c, 0);
        io.c_out[r][c] = macs[r][c].io.c_out;
      }
    }
    io.valid_out = ch_nextEn(ctr.value() == N+P+M-1, io.valid_in, false);
  }
};

int main() {
  auto a = Matrix<int>(4, 4);
  auto b = Matrix<int>(4, 4);

  for (size_t j = 0; j < a.height(); ++j)  {
    for (size_t i = 0; i < a.width(); ++i) {
      a.at(i, j) = j * a.width() + i;
    }
  }

  for (size_t j = 0; j < b.height(); ++j)  {
    for (size_t i = 0; i < b.width(); ++i) {
      b.at(i, j) = j * b.width() + i;
    }
  }

  ch_device<MatMul<8, 24, 4, 4, 4>> matmul;

  ch_tracer tracer(matmul);
  tracer.run([&](ch_tick t)->bool {
    matmul.io.valid_in = true;
    auto j = t / 2;
    for (size_t i = 0; i < a.height(); ++i) {
      matmul.io.a_in[i] = (j < a.width()) ? a.at(j, i) : 0;
    }
    for (size_t i = 0; i < b.width(); ++i) {
      matmul.io.b_in[i] = (j < a.width()) ? b.at(i, j) : 0;
    }
    return (!matmul.io.valid_out) && (t < 100000);
  });

  std::cout << "result:" << std::endl;
  std::cout << "out = "  << matmul.io.c_out << std::endl;

  // Verify
  auto c = a * b;
  for (size_t j = 0; j < c.height(); ++j)  {
    for (size_t i = 0; i < c.width(); ++i) {
      assert(c.at(i, j) == matmul.io.c_out[j][i]);
    }
  }

  ch_toVerilog("matmul.v", matmul);
  ch_toFIRRTL("matmul.fir", matmul);

  tracer.toText("matmul.log");
  tracer.toVCD("matmul.vcd");
  tracer.toTestBench("matmul_tb.v", "matmul.v");
  tracer.toVerilator("matmul_tb.h", "MatMul");
  int ret = system("iverilog matmul_tb.v -o matmul_tb.iv")
          | system("! vvp matmul_tb.iv | grep 'ERROR' || false");
  return ret != 0;
}
