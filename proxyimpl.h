#pragma once

#include "lnodeimpl.h"

namespace chdl_internal {

class proxyimpl : public lnodeimpl {
public:  
  proxyimpl(context* ctx, uint32_t size);
  ~proxyimpl();
  
  void add_node(uint32_t start, lnodeimpl* src, uint32_t offset, uint32_t length, bool resize = false);
  
  void resize(uint32_t start, uint32_t length);
  
  bool includes(uint32_t start, uint32_t length) const;
  
  void remove_ref(const lnode* curr_owner, lnodeimpl* new_owner) override;
  void replace_undef_proxy(uint32_t start, lnodeimpl* new_owner, uint32_t offset, uint32_t length) override;
  
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
  
  std::vector<range_t> m_ranges; 
  ch_cycle m_ctime;
};

}
