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
    
  select_when_t<N> operator()(const ch_logic& test, const ch_bitv<N>& value) {
    return select_when_t<N>(m_stmts, test, value);
  }
  
  select_when_t<N> operator()(const ch_logic& test, const ch_bitbase<N>& value) {
    return select_when_t<N>(m_stmts, test, value);
  }
  
  ch_bitv<N> operator()(const ch_bitv<N>& value) {
    return this->eval(value);
  }

  ch_bitv<N> operator()(const ch_bitbase<N>& value) {
    return this->eval(value);
  }
  
protected:

  typedef std::pair<ch_logic, const ch_bitbase<N>*> select_stmt;
  struct select_stmts : public refcounted {
    std::stack<select_stmt> values;
  };

  select_when_t(const ch_logic& test, const ch_bitbase<N>& value)
    : select_when_t(new select_stmts(), test, value) {
    m_stmts->release();
  }

  select_when_t(select_stmts* stmts, const ch_logic& test, const ch_bitbase<N>& value) {
    stmts->add_ref();
    m_stmts = stmts;
    stmts->values.emplace(test, &value);
  }
  
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
ch_bitv<N> ch_select(const ch_logic& test, const ch_bitv<N>& True, const ch_bitv<N>& False) {
  return ch_bitv<N>(createSelectNode(test, True, False));
}

template <unsigned N>
ch_bitv<N> ch_select(const ch_logic& test, const ch_bitbase<N>& True, const ch_bitv<N>& False) {
  return ch_bitv<N>(createSelectNode(test, True, False));
}

template <unsigned N>
ch_bitv<N> ch_select(const ch_logic& test, const ch_bitv<N>& True, const ch_bitbase<N>& False) {
  return ch_bitv<N>(createSelectNode(test, True, False));
}

template <unsigned N>
ch_bitv<N> ch_select(const ch_logic& test, const ch_bitbase<N>& True, const ch_bitbase<N>& False) {
  return ch_bitv<N>(createSelectNode(test, True, False));
}

/*inline ch_logic ch_select(const ch_logic& test, const ch_logic& True, const ch_logic& False) {
  return ch_logic(createSelectNode(test, True, False));
}*/

template <unsigned N> 
select_when_t<N> ch_select(const ch_logic& test, const ch_bitbase<N>& value) {
  return select_when_t<N>(test, value);
}

template <unsigned N> 
select_when_t<N> ch_select(const ch_logic& test, const ch_bitv<N>& value) {
  return ch_select(test, reinterpret_cast<const ch_bitbase<N>&>(value));
}

/*inline select_when_t<1> ch_select(const ch_logic& test, const ch_logic& value) {
  return select_when_t<1>(test, value);
}*/

}
