#pragma once

#include "lnode.h"

namespace ch {
namespace internal {

struct instr_t {
  ch_op op;
  bitvector dst;
  std::vector<bitvector> srcs;
};

class simref {
public:

  void eval();

private:
  std::vector<instr_t*> instrs_;
};

}}
