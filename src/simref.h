#pragma once

#include "simulatorimpl.h"

namespace ch {
namespace internal {

namespace simref {

struct instr_base {

  instr_base() : step(1) {}

  virtual ~instr_base() {}

  virtual void destroy() = 0;

  virtual void eval() = 0;

  uint32_t step;
};

using data_map_t  = std::unordered_map<uint32_t, const block_type*>;
using instr_map_t = std::unordered_map<uint32_t, instr_base*>;
using node_map_t  = std::unordered_map<uint32_t, uint32_t>;

class driver : public sim_driver {
public:

  driver();

  ~driver();

  void initialize(const std::vector<lnodeimpl*>& eval_list) override;

  void eval() override;

private:

  void setup_constants(context* ctx, data_map_t& data_map);

  void cdomain_bypass(context* ctx, instr_map_t& instr_map, node_map_t& node_map);

  void build_bypass_list(std::unordered_set<uint32_t>& out, context* ctx, uint32_t cd_id);

  std::vector<std::pair<block_type*, uint32_t>> constants_;
  std::vector<instr_base*> instrs_;
};

}}}
