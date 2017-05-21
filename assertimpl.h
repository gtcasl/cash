#pragma once

#include "ioimpl.h"

namespace cash {
namespace detail {

class assertimpl : public ioimpl {
public:
  assertimpl(lnodeimpl* src, const std::string& msg);
  
  const bitvector& eval(ch_cycle t) override;
  
  void print_vl(std::ostream& out) const override {
    CH_UNREFERENCED_PARAMETER(out);
  }

private:
  std::string msg_;
};

}
}
