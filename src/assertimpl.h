#pragma once

#include "ioimpl.h"

namespace ch {
namespace internal {

class assertimpl : public ioimpl {
public:
  assertimpl(const lnode& pred, const std::string& msg);
  
  const bitvector& eval(ch_tick t) override;

private:
  std::string msg_;
  bool predicated_;
};

}
}
