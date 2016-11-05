#pragma once

#include <string.h>
#include <chdl.h>
#include "catch.h"

using namespace chdl::core;
using namespace chdl::sim;

bool runtest(const std::function<ch_logic()>& test, ch_cycle cycles = 1);

inline bool runtestx(const std::function<bool()>& test) {
  return test();
}

#define TEST(...) \
  CHECK(runtest(__VA_ARGS__))

#define TESTX(...) \
  CHECK(runtestx(__VA_ARGS__))
