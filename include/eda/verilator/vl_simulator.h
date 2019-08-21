#pragma once

#include <array>
#include "verilated.h"

#if VM_TRACE
#include <verilated_vcd_c.h>	// Trace file format header
#endif

template <typename T>
class vl_simulator {
private:

  T top_;
#if VM_TRACE
  VerilatedVcdC tfp_;
#endif

public:

  vl_simulator() {
    top_.clk = 0;
    top_.reset = 0;
  #if VM_TRACE
    Verilated::traceEverOn(true);
    top_.trace(&tfp_, 99);
    tfp_.open("vl_trace.vcd");
  #endif
  }

  ~vl_simulator() {
  #if VM_TRACE
    tfp_.close();
  #endif
    top_.final();
  }

  unsigned long reset(unsigned long ticks) {
    top_.reset = 1;
    ticks = this->step(ticks);
    top_.reset = 0;
    return ticks;
  }

  unsigned long step(unsigned long ticks) {
    ticks = this->tick(ticks);
    ticks = this->tick(ticks);
    return ticks;
  }

  unsigned long tick(unsigned long ticks) {
    top_.eval();
  #if VM_TRACE
    tfp.dump(ticks);
  #endif
    top_.clk = !top_.clk;
    return ticks + 1;
  }

  auto operator->() {
    return &top_;
  }
};

template <typename... Args>
void vl_setw(uint32_t* dst, Args&&... args) {
  std::array<uint32_t, sizeof... (Args)> arr{static_cast<uint32_t>(std::forward<Args>(args))...};
  for (size_t i = 0; i < sizeof... (Args); ++i) {
    dst[i] = arr[i];
  }
}