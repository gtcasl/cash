#pragma once

#include "bitvector.h"

namespace chdl_internal {

class iobridge;
class obridge;
class context;

class snodeimpl : public refcounted {
public:
  snodeimpl(uint32_t size);
  snodeimpl(const std::initializer_list<uint32_t>& value, uint32_t size);
  ~snodeimpl();
  
  void bind(context* ctx, unsigned index, iobridge* bridge);
  
  void bind(snodeimpl* src);
  
  bool ready() const;
  
  bool valid() const;
  
  const bitvector& eval(ch_cycle t);
   
  bitvector::const_reference operator[](uint32_t idx) const {
    return m_value[idx];
  }
  
  bitvector::reference operator[](uint32_t idx) {
    return m_value[idx];
  }
  
  uint32_t read(uint32_t idx) const {
    return m_value.get_word(idx);
  }
  
  void write(uint32_t idx, uint32_t value) {
    m_value.set_word(idx, value);
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

}
