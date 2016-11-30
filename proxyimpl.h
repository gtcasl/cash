#pragma once

#include "lnodeimpl.h"

namespace chdl_internal {

class proxyimpl : public lnodeimpl {
public:  
  proxyimpl(context* ctx, uint32_t size);
  
  void add_node(uint32_t start, lnodeimpl* src, uint32_t offset, uint32_t length, bool resize = false);
  
  void resize(uint32_t start, uint32_t length);
  
  void ensureInitialized(uint32_t start, uint32_t length) {
    if (!includes(start, length)) {
      this->resize(start, length);
    }
  }
  
  void ensureInitialized() {
    this->ensureInitialized(0, this->get_size());
  }
  
  
  bool is_slice() const;
  
  bool includes(uint32_t start, uint32_t length) const;
  
  void remove_ref(const lnode* node, lnodeimpl* src) override;
  
  void replace_undefs(uint32_t start, lnodeimpl* src, uint32_t offset, uint32_t length) override;
  
  bool has_undefs() {
    return true;
  }
  
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
