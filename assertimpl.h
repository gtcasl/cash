#pragma once

#include "nodeimpl.h"
#include "tickable.h"

namespace chdl_internal {

class assertion {
public:
  assertion(context* ctx, const ch_node& src, const std::string& msg);
  
  void eval(ch_cycle t);

private:
  ch_node m_x;
  std::string m_msg;
};

}
