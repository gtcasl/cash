#pragma once

#include <string.h>
#include <cash.h>
#include "catch.h"

using namespace ch::logic;
using namespace ch::literals;
using namespace ch::system;

bool checkVerilog(const std::string& moduleName);

bool TEST(const std::function<ch_bool()> &test, ch_tick cycles = 0);

bool TESTX(const std::function<bool()> &test);

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
