#pragma once

#include "bitv.h"

namespace chdl_internal {

lnode createSelectNode(const lnode& test, const lnode& a, const lnode& b);

template <unsigned N> 
class select_when_t {
public:
  
  ~select_when_t() {
    m_stmts->release();
  }
    
  select_when_t<N> operator()(const ch_logic& test, const ch_bitbase<N>& value) {
    return select_when_t<N>(m_stmts, test, value);
  }
  
  select_when_t<N> operator()(const ch_logic& test, const ch_bitv<N>& value) {
    return select_when_t<N>(m_stmts, test, value);
  }
  
  ch_bitv<N> operator()(const ch_bitbase<N>& value) {
    return this->eval(value);
  }
  
  ch_bitv<N> operator()(const ch_bitv<N>& value) {
    return this->eval(value);
  }
  
protected:

  typedef std::pair<ch_logic, const ch_bitbase<N>*> select_stmt;
  struct select_stmts : public refcounted {
    std::stack<select_stmt> values;
  };
  
  select_when_t(select_stmts* stmts, const ch_logic& test, const ch_bitbase<N>& value) 
    : m_stmts(stmts) {    
    stmts->values.emplace(test, &value);
    stmts->acquire();
  }
  
  select_when_t(const ch_logic& test, const ch_bitbase<N>& value)
    : select_when_t(new select_stmts(), test, value) {}  
  
  ch_bitv<N> eval(const ch_bitbase<N>& value) {
    ch_bitv<N> curr;
    const ch_bitbase<N>* pcurr = &value;
    auto& values = m_stmts->values;
    while (!values.empty()) {
      auto& stmt = values.top();
      curr = ch_bitv<N>(createSelectNode(stmt.first, *stmt.second, *pcurr));
      pcurr = &curr;
      values.pop();
    }
    return curr;
  }
  
  select_stmts* m_stmts;
  
  template <unsigned N2> friend select_when_t<N2> ch_select(const ch_logic& test, const ch_bitbase<N2>& value);
  friend select_when_t<1> ch_select(const ch_logic& test, const ch_logic& value);
};

template <unsigned N> 
select_when_t<N> ch_select(const ch_logic& test, const ch_bitbase<N>& value) {
  return select_when_t<N>(test, value);
}

template <unsigned N> 
select_when_t<N> ch_select(const ch_logic& test, const ch_bitv<N>& value) {
  return ch_select(test, reinterpret_cast<const ch_bitbase<N>&>(value));
}

template <unsigned N>
ch_bitv<N> ch_select(const ch_logic& test, const ch_bitbase<N>& True, const ch_bitbase<N>& False) {
  return ch_bitv<N>(createSelectNode(test, True, False));
}

#define CHDL_SELECT_GEN(type) \
  template <unsigned N> ch_bitv<N> ch_select(const ch_logic& test, type True, const ch_bitbase<N>& False) { return ch_select(test, ch_bitv<N>(True), False); } \
  template <unsigned N> ch_bitv<N> ch_select(const ch_logic& test, const ch_bitbase<N>& True, type False) { return ch_select(test, True, ch_bitv<N>(False)); } \
  template <unsigned N> ch_bitv<N> ch_select(const ch_logic& test, type True, type False) { return ch_select(test, ch_bitv<N>(True), ch_bitv<N>(False)); }
CHDL_SELECT_GEN(char)
CHDL_SELECT_GEN(int8_t)
CHDL_SELECT_GEN(uint8_t)
CHDL_SELECT_GEN(int16_t)
CHDL_SELECT_GEN(uint16_t)
CHDL_SELECT_GEN(int32_t)
CHDL_SELECT_GEN(uint32_t)
CHDL_SELECT_GEN(int64_t)
CHDL_SELECT_GEN(uint64_t)
#undef CHDL_SELECT_GEN

}
