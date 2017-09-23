#pragma once

#include "ioimpl.h"

namespace cash {
namespace internal {

class tickimpl : public ioimpl {
public:
  tickimpl(context* ctx);

  const bitvector& eval(ch_tick t) override;
  
private:
  ch_tick tick_;
};

}
}
