#pragma once

#include "lnodeimpl.h"

namespace chdl_internal {

class proxyimpl : public lnodeimpl {
public:  
  proxyimpl(context* ctx, uint32_t size);
  ~proxyimpl();
  
  void add_src(uint32_t dst_offset, const lnode& src, uint32_t src_offset, uint32_t src_length);
  
  const bitvector& eval(ch_cycle t) override;  
  void print_vl(std::ostream& out) const override;
  
private:
  
  struct range_t {
    uint32_t src;
    uint32_t offset;    
    uint32_t length;
  };
  
  std::vector<range_t> m_ranges; 
  ch_cycle m_ctime;
};

}
