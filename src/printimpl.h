#pragma once

#include "ioimpl.h"

namespace cash {
namespace internal {

class printimpl : public ioimpl {
public:
  printimpl(context* ctx,
            const std::string& format,
            const std::initializer_list<lnode>& args);

  const bitvector& eval(ch_cycle t) override;  

  void print_vl(std::ostream& out) const override;

private:
  std::string format_;  
  std::stringstream strbuf_;  
  bool predicated_;
  ch_cycle ctime_;
};

}
}
