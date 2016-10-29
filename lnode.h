#pragma once

#include "typebase.h"
#include "bitvector.h"

namespace chdl_internal {

class lnodeimpl;
class context;

typedef uint64_t ch_cycle;

class lnode {
public:

  lnode() : m_impl(nullptr) {}
  
  lnode(const lnode& rhs);
  lnode(lnode&& rhs);
  explicit lnode(lnodeimpl* impl);
  lnode(const std::vector< partition<lnode> >& data, uint32_t size);
  lnode(const bitvector& value);
  
  virtual ~lnode();
  
  lnode& operator=(const lnode& rhs);
  
  lnode& operator=(lnode&& rhs);
  
  lnode& operator=(lnodeimpl* rhs);
  
  uint32_t get_id() const;
  
  uint32_t get_size() const;
  
  context* get_ctx() const;
  
  bool ready() const;
  
  bool valid() const;
 
  const bitvector& eval(ch_cycle t);  
  
  void assign(const bitvector& value);
  
  void read(std::vector< partition<lnode> >& out, uint32_t offset, uint32_t length, uint32_t size) const;
  
  void write(uint32_t dst_offset, const std::vector< partition<lnode> >& src, uint32_t src_offset, uint32_t src_length, uint32_t size); 
    
  operator lnodeimpl*() const { 
    assert(m_impl);
    return m_impl; 
  }  

protected:  
  
  const lnode& ensureInitialized(uint32_t size, uint32_t offset = 0, uint32_t length = 0) const;
  
  void reset(lnodeimpl* impl = nullptr, bool initialization = false) const;

  void assign(lnodeimpl* impl, bool initialization = false) const;
  
  void move(lnode& rhs);
  
  void assign(uint32_t dst_offset, lnodeimpl* src, uint32_t src_offset, uint32_t src_length, uint32_t size, bool initialization);
  
  mutable lnodeimpl* m_impl;
  
  friend class lnodeimpl;
  friend class proxyimpl;
  friend class context;
  friend class ch_device;
  template <unsigned N> friend class ch_bitv;
};

inline std::ostream& operator<<(std::ostream& out, const lnode& rhs) {
  out << rhs.get_id();
  return out;
}

lnodeimpl* createNullNode(uint32_t size);

}
