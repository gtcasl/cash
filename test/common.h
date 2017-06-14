#pragma once

#include <string.h>
#include <cash.h>
#include "catch.h"

using namespace cash::core;
using namespace cash::sim;

bool runtest(const std::function<ch_bit<1>()>& test, ch_cycle cycles = 1);

bool runtestx(const std::function<bool()>& test);

#define TEST(...) \
  CHECK(runtest(__VA_ARGS__))

#define TESTX(...) \
  CHECK(runtestx(__VA_ARGS__))
