#pragma once

#include "ioimpl.h"

namespace ch {
namespace internal {

class tickimpl : public ioimpl {
public:
  const bitvector& eval(ch_tick t) override;
  
protected:
  tickimpl(context* ctx);
  ~tickimpl() {}

  ch_tick tick_;

  friend class context;
};

}
}
