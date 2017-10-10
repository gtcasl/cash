#pragma once

#include "ioimpl.h"

namespace ch {
namespace internal {

class assertimpl : public ioimpl {
public:
  const bitvector& eval(ch_tick t) override;

protected:
  assertimpl(context* ctx, const lnode& pred, const char* msg);
  ~assertimpl() {}

  std::string msg_;
  bool predicated_;

  friend class context;
};

}
}
