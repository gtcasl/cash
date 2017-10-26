#pragma once

#include <string.h>
#include <cash.h>
#include <../stl/fifo.h>
#include "catch.h"

using namespace ch::core;
using namespace ch::literals;
using namespace ch::sim;
using namespace ch::stl;

bool checkVerilog(const std::string& moduleName);

int syscall(const std::string& cmd);

int syscall(const std::string& cmd, std::string& output);

bool runtest(const std::function<ch_bit<1>()> &test, ch_tick ticks = 1);

bool runtestx(const std::function<bool()> &test);

#define TEST(...) CHECK(runtest(__VA_ARGS__))

#define TESTX(...) CHECK(runtestx(__VA_ARGS__))
