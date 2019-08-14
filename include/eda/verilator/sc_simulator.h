#pragma once

#include <array>
#include "systemc.h"

template <typename T>
class sc_simulator {
private:

  T top_;
  sc_trace_file* tfp_;
  sc_signal<bool> clock_;
  sc_signal<bool> reset_;

public:
  sc_simulator()
    : top_("top")
    , tfp_(nullptr) {
    clock_.write(false);
    reset_.write(false);
    top_.clk(clock_);
    top_.reset(reset_);
  }

  ~sc_simulator() {
    if (tfp_) {
      sc_close_vcd_trace_file(tfp_);
    }
  }

  unsigned long reset(unsigned long ticks) {
    reset_.write(true);
    ticks = tick(ticks);
    ticks = tick(ticks);
    reset_.write(false);
    return ticks;
  }

  unsigned long step(unsigned long ticks) {
    ticks = tick(ticks);
    ticks = tick(ticks);
    return ticks;
  }

  unsigned long tick(unsigned long ticks) {
    sc_start(1, SC_NS);
    clock_.write(!clock_.read());
    return ticks + 1;
  }

  auto create_trace(const char* name) {
    tfp_ = sc_create_vcd_trace_file(name);
    sc_trace(tfp_, clock_, "clock");
    sc_trace(tfp_, reset_, "reset");
    return tfp_;
  }

  auto operator->() {
    return &top_;
  }
};

template <unsigned N, typename... Args>
auto sc_make_bv(Args&&... args) {
  std::array<uint32_t, sizeof... (Args)> arr{static_cast<uint32_t>(std::forward<Args>(args))...};
  sc_bv<N> ret;
  for (size_t i = 0; i < sizeof... (Args); ++i) {
    ret.set_word(i, arr[i]);
  }
  return ret;
}