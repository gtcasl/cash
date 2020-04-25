#pragma once

#include "simulatorimpl.h"

namespace ch::internal::simref {

struct sim_ctx_t;

using data_map_t  = std::unordered_map<uint32_t, const block_type*>;

class driver : public sim_driver {
public:

  driver();

  ~driver();

  void initialize(const std::vector<lnodeimpl*>& eval_list) override;

  void getDataMap(data_map_t **t);
  void eval() override;

private:  

  sim_ctx_t* sim_ctx_;
};

}
