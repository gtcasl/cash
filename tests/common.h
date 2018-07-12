#pragma once

#include <string.h>
#include <cash.h>
#include "catch.h"

using namespace ch::core;
using namespace ch::literals;
using namespace ch::sim;

bool checkVerilog(const std::string& moduleName);

bool runtest(const std::function<ch_bool()> &test, ch_tick cycles = 0);

bool runtestx(const std::function<bool()> &test);

#define TEST(...) CHECK(runtest(__VA_ARGS__))

#define TESTX(...) CHECK(runtestx(__VA_ARGS__))

class RetCheck {
public:
  RetCheck() : count_(0) {}

  RetCheck& operator&=(bool value);

  operator bool() const {
    return count_ > 0;
  }

private:
  int count_;
};
