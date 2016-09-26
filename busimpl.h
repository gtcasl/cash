#pragma once

#include "bitvector.h"

namespace chdl_internal {

class iobridge;
class obridge;
class context;

class busimpl : public refcounted {
public:
  explicit busimpl(uint32_t size);
  ~busimpl();
  
  void bind(context* ctx, unsigned index, iobridge* bridge);
  
  void bind(busimpl* src);
  
  bool ready() const;
  
  bool valid() const;
  
  const bitvector& eval(ch_cycle t);
   
  template <typename T>
  T read() const {
    T value = 0;
    for (uint32_t i = 0, n = m_value.get_size(); i < n; ++i) {
      T sign = m_value.get_bit(i) ? 1 : 0;
      value |= sign << i;
    }
    return value;
  }
  
  template <typename T>
  void write(T value) {
    for (uint32_t i = 0, n = m_value.get_size(); i < n; ++i) {
      m_value.set_bit(i, value & 0x1);
      value >>= 1;
    }
    assert(value == 0);
  }
  
  bool get_bit(uint32_t bidx) const {
    return m_value.get_bit(bidx);
  }
  
  void set_bit(uint32_t bidx, bool value ) {
    m_value.set_bit(bidx, value);
  }
  
  uint32_t get_size() const {
    return m_value.get_size();
  }
  
  void get_bindings(std::set<context*>& bindings) const;
  
  operator const bitvector&() const { 
    return m_value; 
  }
  
protected:

  struct portid_t {
    context* ctx;
    unsigned idx;

    bool operator<(const portid_t& rhs) const {
      return (ctx < rhs.ctx) || 
            ((ctx == rhs.ctx) && (idx < rhs.idx));
    }
  };

  typedef std::map<portid_t, iobridge*> bridges_t;

  const portid_t* get_portid(iobridge* bridge) const;

  bridges_t m_bridges;
  obridge*  m_obridge;
  bitvector m_value;
  ch_cycle  m_ctime;
};

template<>
inline uint32_t busimpl::read<uint32_t>() const {
  return m_value.get_word(0);
}

template<>
inline void busimpl::write<uint32_t>(uint32_t value) {
  assert((value >> m_value.get_size()) == 0);
  m_value.set_word(0, value);    
}

}
