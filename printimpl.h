#pragma once

#include "ioimpl.h"

namespace cash_internal {

class printimpl : public ioimpl {
public:
  printimpl(context* ctx, lnodeimpl* cond, const std::string& format, 
            const std::initializer_list<lnodeimpl*>& args);

  const bitvector& eval(ch_cycle t) override;  
  void print_vl(std::ostream& out) const override;
  
  std::string format_;  
  std::stringstream strbuf_;
  ch_cycle ctime_;
  uint32_t args_offset_;
};

}
