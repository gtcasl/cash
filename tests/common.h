#pragma once

#include <string.h>
#include <cash.h>
#include "../src/platform.h"
#include "catch.h"

using namespace ch::internal;
using namespace ch::logic;
using namespace ch::literals;
using namespace ch::system;

template <typename F, typename... Args>
struct GenericFunction {};

template <typename F>
struct GenericFunction<F> {
  using return_type = std::invoke_result_t<F>;
  __io (
    __out (return_type) out
  );
  GenericFunction(const F& func) : func_(func) {}
  void describe() {
    io.out = func_();
  }
  F func_;
};

template <typename F, typename T0>
struct GenericFunction<F, T0> {
  using return_type = std::invoke_result_t<F, T0>;
  __io (
    __in (T0) in,
    __out (return_type) out
  );
  GenericFunction(const F& func) : func_(func) {}
  void describe() {
    io.out = func_(io.in);
  }
  F func_;
};

template <typename F, typename T0, typename T1>
struct GenericFunction<F, T0, T1> {
  using return_type = std::invoke_result_t<F, T0, T1>;
  __io (
    __in (T0) in0,
    __in (T1) in1,
    __out (return_type) out
  );
  GenericFunction(const F& func) : func_(func) {}
  void describe() {
    io.out = func_(io.in0, io.in1);
  }
  F func_;
};

template <typename F, typename T0, typename T1, typename T2>
struct GenericFunction<F, T0, T1, T2> {
  using return_type = std::invoke_result_t<F, T0, T1, T2>;
  __io (
    __in (T0) in0,
    __in (T1) in1,
    __in (T2) in2,
    __out (return_type) out
  );
  GenericFunction(const F& func) : func_(func) {}
  void describe() {
    io.out = func_(io.in0, io.in1, io.in2);
  }
  F func_;
};

template <typename F, typename T0, typename T1, typename T2, typename T3>
struct GenericFunction<F, T0, T1, T2, T3> {
  using return_type = std::invoke_result_t<F, T0, T1, T2, T3>;
  __io (
    __in (T0) in0,
    __in (T1) in1,
    __in (T2) in2,
    __in (T3) in3,
    __out (std::invoke_result_t<F, T0, T1, T2, T3>) out
  );
  GenericFunction(const F& func) : func_(func) {}
  void describe() {
    io.out = func_(io.in0, io.in1, io.in2, io.in3);
  }
  F func_;
};

template <typename F>
auto TestFunction(F&& f) {
  using GF = GenericFunction<F>;
  ch_device<GF> device(f);
  ch_simulator sim(device);
  sim.run();
  ch_system_t<typename GF::return_type> ret;
  ret = device.io.out;
  return ret;
}

template <typename F, typename T0>
auto TestFunction(F&& f, const T0& a) {
  using GF = GenericFunction<F, ch_logic_t<T0>>;
  ch_device<GF> device(f);
  device.io.in0 = a;
  ch_simulator sim(device);
  sim.run();
  ch_system_t<typename GF::return_type> ret;
  ret = device.io.out;
  return ret;
}

template <typename F, typename T0, typename T1>
auto TestFunction(F&& f, const T0& a, const T1& b) {
  using GF = GenericFunction<F, ch_logic_t<T0>, ch_logic_t<T1>>;
  ch_device<GF> device(f);
  device.io.in0 = a;
  device.io.in1 = b;
  ch_simulator sim(device);
  sim.run();
  ch_system_t<typename GF::return_type> ret;
  ret = device.io.out;
  return ret;
}

template <typename F, typename T0, typename T1, typename T2>
auto TestFunction(F&& f, const T0& a, const T1& b, const T2& c) {
  using GF = GenericFunction<F, ch_logic_t<T0>, ch_logic_t<T1>, ch_logic_t<T2>>;
  ch_device<GF> device(f);
  device.io.in0 = a;
  device.io.in1 = b;
  device.io.in2 = c;
  ch_simulator sim(device);
  sim.run();
  ch_system_t<typename GF::return_type> ret;
  ret = device.io.out;
  return ret;
}

template <typename F, typename T0, typename T1, typename T2, typename T3>
auto TestFunction(F&& f, const T0& a, const T1& b, const T2& c, const T2& d) {
  using GF = GenericFunction<F, ch_logic_t<T0>, ch_logic_t<T1>, ch_logic_t<T2>, ch_logic_t<T3>>;
  ch_device<GF> device(f);
  device.io.in0 = a;
  device.io.in1 = b;
  device.io.in2 = c;
  device.io.in3 = d;
  ch_simulator sim(device);
  sim.run();
  ch_system_t<typename GF::return_type> ret;
  ret = device.io.out;
  return ret;
}

///////////////////////////////////////////////////////////////////////////////

bool checkVerilog(const std::string& moduleName);

bool TEST(const std::function<ch_bool()> &test, ch_tick cycles = 0);

bool TESTX(const std::function<bool()> &test);

///////////////////////////////////////////////////////////////////////////////

class RetCheck {
public:
  RetCheck() : count_(0) {}

  RetCheck& operator&=(bool value);

  operator bool() const {
    return count_ > 0;
  }

private:
  int64_t count_;
};

///////////////////////////////////////////////////////////////////////////////

class auto_cflags_disable {
public:
  auto_cflags_disable(int flags) {
    cflags_ = platform::self().cflags();
    platform::self().set_cflags(cflags(cflags_ & ~flags));
  }
  auto_cflags_disable(cflags flags) {
    cflags_ = platform::self().cflags();
    platform::self().set_cflags(cflags(cflags_ & ~(int)flags));
  }
  ~auto_cflags_disable() {
    platform::self().set_cflags(cflags_);
  }
private:
  ch::internal::cflags cflags_;
};
