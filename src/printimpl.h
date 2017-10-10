#pragma once

#include "ioimpl.h"

namespace ch {
namespace internal {

class printimpl : public ioimpl {
public:
  printimpl(context* ctx,
            const char* format,
            const std::initializer_list<lnode>& args);

  const bitvector& eval(ch_tick t) override;

private:
  std::string format_;  
  std::stringstream strbuf_;  
  bool predicated_;
  ch_tick tick_;
};

}
}
