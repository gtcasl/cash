#pragma once

#include "ioimpl.h"

namespace ch {
namespace internal {

class timeimpl : public ioimpl {
public:

  const bitvector& eval(ch_tick t) override;
  
protected:

  timeimpl(context* ctx);

  ~timeimpl() {}

  ch_tick tick_;

  friend class context;
};

}
}
