#pragma once

#include <chdl.h>
#include "catch.h"

using namespace chdl::core;
using namespace chdl::sim;

bool runtest(const std::function<ch_logic()>& test, ch_cycle cycles = 1);

#define TEST(...) \
  REQUIRE(runtest(__VA_ARGS__))
