#pragma once

#include "simulatorimpl.h"

namespace ch {
namespace internal {

struct instr_base {

  instr_base() : step(1) {}

  virtual ~instr_base() {}

  virtual void destroy() = 0;

  virtual void eval() = 0;

  uint32_t step;
};

class simref : public sim_driver {
public:

  simref();

  ~simref();

  void initialize(const std::vector<lnodeimpl*>& eval_list) override;

  void eval() override;

private:

  void generate_clk_bypass_list(std::unordered_set<uint32_t>& out, context* ctx, uint32_t cd_id);

  block_type* create_constants(litimpl* node);

  std::vector<block_type*> constants_;
  std::vector<instr_base*> instrs_;
};

}}
