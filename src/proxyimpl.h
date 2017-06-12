#pragma once

#include "lnodeimpl.h"

namespace cash {
namespace detail {

class proxyimpl : public lnodeimpl {
public:  
  proxyimpl(context* ctx, uint32_t size);
  
  void add_source(uint32_t dst_offset,
                  lnodeimpl* src,
                  uint32_t src_offset,
                  uint32_t src_length);

  std::vector<lnode>::iterator erase_source(std::vector<lnode>::iterator iter);

  void assign(uint32_t dst_offset,
              lnodeimpl* src,
              uint32_t src_offset,
              uint32_t src_length) override;
  
  const bitvector& eval(ch_cycle t) override;  
  void print(std::ostream& out, uint32_t level) const override;
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
