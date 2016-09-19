#pragma once

#include "bitv.h"

namespace chdl_internal {

ch_node createSelectNode(const ch_node& test, const ch_node& a, const ch_node& b);

template <unsigned N> class select_when_t {
public:
  ~select_when_t() {
    m_stmts->release();
  }
    
  select_when_t<N> operator()(const ch_logic& test, const ch_bitv<N>& value) {
    return select_when_t<N>(m_stmts, test, value);
  }

  ch_bitv<N> operator()(const ch_bitbase<N>& value) {
    ch_bitv<N> curr;
    const ch_bitbase<N>* pcurr = &value;
    auto& values = m_stmts->values;
    while (!values.empty()) {
      auto& stmt = values.top();
      curr = ch_bitv<N>(createSelectNode(stmt.first, ch_bitv<N>(*stmt.second), ch_bitv<N>(*pcurr)));
      pcurr = &curr;
      values.pop();
    }
    return curr;
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
  
  select_stmts* m_stmts;
  
  template <unsigned N2> friend select_when_t<N2> ch_select(const ch_logic& test, const ch_bitbase<N2>& value);
};

template <unsigned N>
ch_bitv<N> ch_select(const ch_logic& test, const ch_bitbase<N>& True, const ch_bitbase<N>& False) {
  return ch_bitv<N>(createSelectNode(test, ch_bitv<N>(True), ch_bitv<N>(False)));
}

template <unsigned N> 
select_when_t<N> ch_select(const ch_logic& test, const ch_bitbase<N>& value) {
  return select_when_t<N>(test, value);
}

}
