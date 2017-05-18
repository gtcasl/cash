#pragma once

#include "lnodeimpl.h"

namespace cash {
namespace detail {

class proxyimpl : public lnodeimpl {
public:  
  proxyimpl(context* ctx, uint32_t size);
  
  void add_node(uint32_t start, const lnode& src, uint32_t offset, uint32_t length, bool resize = false);
  
  const bitvector& eval(ch_cycle t) override;  
  void print(std::ostream& out) const override;
  void print_vl(std::ostream& out) const override;
  
private:
  
  struct range_t {
    uint32_t srcidx;
    uint32_t start;
    uint32_t offset;    
    uint32_t length;
  };
  
  void merge_left(uint32_t idx);
  
  std::vector<range_t> ranges_; 
  ch_cycle ctime_;
};

}
}
