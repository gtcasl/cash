#pragma once

#include "simulatorimpl.h"

namespace ch {
namespace internal {

struct instr_base {

  instr_base() {}

  virtual ~instr_base() {}

  virtual void destroy() = 0;

  virtual void eval() = 0;
};

class simref : public sim_driver {
public:

  simref();

  ~simref();

  void initialize(const std::vector<lnodeimpl*>& eval_list) override;

  void eval() override;

private:

  block_type* create_constants(litimpl* node);

  std::vector<block_type*> constants_;
  std::vector<instr_base*> instrs_;
};

}}
