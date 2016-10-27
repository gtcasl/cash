#pragma once

#include "bitv.h"

namespace chdl_internal {

lnodeimpl* createSelectNode(lnodeimpl* cond, lnodeimpl* a, lnodeimpl* b);

template <unsigned N> 
class select_t {
public:
  
  ~select_t() {
    if (m_stmts)
      delete m_stmts;
  }
    
  select_t<N> operator()(const ch_logic& cond, const ch_bitbase<N>& value) {
    return this->push(cond, value);
  }
  
  select_t<N> operator()(const ch_logic& cond, const ch_bitv<N>& value) {
    return this->push(cond, value);
  }
  
  ch_bitv<N> operator()(const ch_bitbase<N>& value) {
    return this->eval(value);
  }
  
  ch_bitv<N> operator()(const ch_bitv<N>& value) {
    return this->eval(value);
  }
  
protected:

  struct stmt_t {
    const ch_logic& cond;
    const ch_bitbase<N>& value;
  };
  
  typedef std::stack<stmt_t> stmts_t;
  
  select_t(stmts_t* stmts = new stmts_t()) : m_stmts(stmts) {}
  
  select_t push(const ch_logic& cond, const ch_bitbase<N>& value) {
    stmts_t* stmts = m_stmts;
    m_stmts = nullptr;
    stmts->push({cond, value});
    return select_t(stmts);
  }  
  
  ch_bitv<N> eval(const ch_bitbase<N>& value) {
    ch_bitv<N> curr;
    const ch_bitbase<N>* pcurr = &value;
    stmts_t* stmts = m_stmts;
    while (!stmts->empty()) {
      const stmt_t& stmt = stmts->top();
      curr = ch_bitv<N>(createSelectNode(stmt.cond, stmt.value, *pcurr));
      pcurr = &curr;
      stmts->pop();
    }
    return curr;
  }
  
  stmts_t* m_stmts;
  
  template <unsigned N2> friend select_t<N2> ch_select(const ch_logic& cond, const ch_bitbase<N2>& value);
  friend select_t<1> ch_select(const ch_logic& cond, const ch_logic& value);
};

template <unsigned N> 
select_t<N> ch_select(const ch_logic& cond, const ch_bitbase<N>& value) {
  return select_t<N>().push(cond, value);
}

template <unsigned N> 
select_t<N> ch_select(const ch_logic& cond, const ch_bitv<N>& value) {
  return ch_select(cond, reinterpret_cast<const ch_bitbase<N>&>(value));
}

template <unsigned N>
ch_bitv<N> ch_select(const ch_logic& cond, const ch_bitbase<N>& True, const ch_bitbase<N>& False) {
  return ch_bitv<N>(createSelectNode(cond, True, False));
}

#define CHDL_SELECT_GEN(type) \
  template <unsigned N> ch_bitv<N> ch_select(const ch_logic& cond, type True, const ch_bitbase<N>& False) { return ch_select(cond, ch_bitv<N>(True), False); } \
  template <unsigned N> ch_bitv<N> ch_select(const ch_logic& cond, const ch_bitbase<N>& True, type False) { return ch_select(cond, True, ch_bitv<N>(False)); } \
  template <unsigned N> ch_bitv<N> ch_select(const ch_logic& cond, type True, type False) { return ch_select(cond, ch_bitv<N>(True), ch_bitv<N>(False)); }
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
