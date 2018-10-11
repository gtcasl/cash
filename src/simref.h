#pragma once

#include "simulatorimpl.h"

namespace ch {
namespace internal {

namespace simref {

using data_map_t = std::unordered_map<uint32_t, const block_type*>;

struct instr_base {

  instr_base() : step(1) {}

  virtual ~instr_base() {}

  virtual void destroy() = 0;

  virtual void eval() = 0;

  uint32_t step;
};

class driver : public sim_driver {
public:

  driver();

  ~driver();

  void initialize(const std::vector<lnodeimpl*>& eval_list) override;

  void eval() override;

private:

  void setup_constants(context* ctx, data_map_t& data_map);

  void generate_clk_bypass_list(std::unordered_set<uint32_t>& out, context* ctx, uint32_t cd_id);

  std::vector<std::pair<block_type*, uint32_t>> constants_;
  std::vector<instr_base*> instrs_;
};

}}}
