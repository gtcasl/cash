#include <iostream>
#include <vector>
#include <assert.h>
#include <core.h>
#include <htl/counter.h>
#include "common.h"

using namespace ch::core;
using namespace ch::htl;

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
    ch_vec<ch_vec<ch_module<MAC<I, O>>, P>, N> macs;
    ch_counter<N+P+M> ctr(io.valid_in); // valid counter

    // MAC array connections
    for (unsigned r = 0; r < N; ++r) {
      auto p = ch_delayEn(io.a_in[r], io.valid_in, r, 0);
      for (unsigned c = 0; c < P; ++c) {
        auto q = ch_delayEn(io.b_in[c], io.valid_in, c, 0);
        macs[r][c].io.enable = io.valid_in;
        macs[r][c].io.a_in = c ? macs[r][c-1].io.a_out.as_int() : p;
        macs[r][c].io.b_in = r ? macs[r-1][c].io.b_out.as_int() : q;        
        io.c_out[r][c] = macs[r][c].io.c_out;
      }
    }

    // output valid?
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
    return (!matmul.io.valid_out) && (t < MAX_TICKS);
  }, 2);

  std::cout << "result:" << std::endl;
  std::cout << "out = "  << matmul.io.c_out << std::endl;

  // Verify
  auto c = a * b;
  for (size_t j = 0; j < c.height(); ++j)  {
    for (size_t i = 0; i < c.width(); ++i) {
      CHECK(c.at(i, j) == matmul.io.c_out[j][i]);
    }
  }

  ch_toVerilog("matmul.v", matmul);
  ch_toFIRRTL("matmul.fir", matmul);

  tracer.toText("matmul.log");
  tracer.toVCD("matmul.vcd");
  tracer.toVerilog("matmul_tb.v", "matmul.v");
  tracer.toVerilator("matmul_tb.h", "MatMul");
  int ret = !system("iverilog matmul_tb.v -o matmul_tb.iv")
          & !system("! vvp matmul_tb.iv | grep 'ERROR' || false");
  return (0 == ret);
}
