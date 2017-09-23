#pragma once

#include "ioimpl.h"

namespace cash {
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
