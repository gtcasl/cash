#pragma once

#include "ioimpl.h"

namespace chdl_internal {

class ibridge;

class busimpl : public refcounted {
public:
  explicit busimpl(uint32_t size);
  ~busimpl();
  
  void bind(context* ctx, unsigned index, iobridge* bridge);
  
  void bind(busimpl* src);
  
  bool ready() const;
  
  bool valid() const;
  
  const bitvector& eval(ch_cycle t);
  
  bool get_bit(uint32_t idx) const {
    return m_value.get_bit(idx);
  }
  
  void set_bit(uint32_t idx, bool value ) {
    m_value.set_bit(idx, value);
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
  ch_cycle m_ctime;
};

}
