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
    ticks = this->step(ticks);
    reset_.write(false);
    return ticks;
  }

  unsigned long step(unsigned long ticks) {
    ticks = this->tick(ticks);
    ticks = this->tick(ticks);
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

template <typename T, typename... Args>
void sc_setw(sc_signal<T>& sig, Args&&... args) {
  T value;
  std::array<uint32_t, sizeof... (Args)> arr{static_cast<uint32_t>(std::forward<Args>(args))...};  
  for (size_t i = 0; i < sizeof... (Args); ++i) {
    value.set_word(i, arr[i]);
  }
  sig.write(value);
}

template <typename T, typename... Args>
int sc_cmpw(const sc_signal<T>& sig, Args&&... args) {
  std::array<uint32_t, sizeof... (Args)> arr{static_cast<uint32_t>(std::forward<Args>(args))...};
  for (size_t i = 0; i < sizeof... (Args); ++i) {
    if (sig.read().get_word(i) < arr[i])
      return -1;
    if (sig.read().get_word(i) > arr[i])
      return 1;
  }
  return 0;
}