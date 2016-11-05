#pragma once

#include "ioimpl.h"

namespace chdl_internal {

class printimpl : public ioimpl {
public:
  printimpl(context* ctx, lnodeimpl* cond, const std::string& format, 
            const std::initializer_list<lnodeimpl*>& args);

  const bitvector& eval(ch_cycle t) override;  
  void print_vl(std::ostream& out) const override;
  
  std::string m_format;  
  std::stringstream m_strbuf;
  ch_cycle m_ctime;
  uint32_t m_args_offset;
};

}
