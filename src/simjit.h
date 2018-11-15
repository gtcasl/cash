#pragma once

#include "simulatorimpl.h"

namespace ch::internal::simjit {

struct sim_ctx_t;

class driver : public sim_driver {
public:

  driver();

  ~driver();

  void initialize(const std::vector<lnodeimpl*>& eval_list) override;

  void eval() override;  

private:

  sim_ctx_t* sim_ctx_;
};

}
