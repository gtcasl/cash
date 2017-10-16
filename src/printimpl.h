#pragma once

#include "ioimpl.h"

namespace ch {
namespace internal {

class printimpl : public ioimpl {
public:
  const bitvector& eval(ch_tick t) override;

protected:
  printimpl(context* ctx,
            const std::string& format,
            const std::initializer_list<lnode>& args);
  ~printimpl() {}

  std::string format_;  
  std::stringstream strbuf_;  
  bool predicated_;
  ch_tick tick_;

  friend class context;
};

}
}
