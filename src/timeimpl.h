#pragma once

#include "ioimpl.h"

namespace ch {
namespace internal {

class timeimpl : public ioimpl {
public:

  void initialize() override;

  void eval() override;
  
protected:

  timeimpl(context* ctx, const source_location& sloc);

  ch_tick tick_;

  friend class context;
};

}
}
