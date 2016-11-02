#pragma once

#include "when.h"

namespace chdl_internal {

class case_impl {  
protected:
  
  using func_t = std::function<void ()>;
  
  struct stmt_t {
    lnodeimpl* value;
    func_t func;
  };
  
  struct stmts_t {
    lnodeimpl* key;
    std::stack<stmt_t> values;    
    stmts_t(lnodeimpl* key_) : key(key_) {}
  };
  
  stmts_t* m_stmts;
  
public:
  
  ~case_impl() {
    if (m_stmts) {
      CHDL_CHECK(m_stmts->values.empty(), "incomplete case statement");
      delete m_stmts;
    }
  }
    
  case_impl(lnodeimpl* key) {
    m_stmts = new stmts_t(key);
  }
  
  void push(lnodeimpl* value, const func_t& func) {
    m_stmts->values.push({value, func});
  }
  
  void eval();
};

template <unsigned N>
class case_t {
public:
    
  template <typename Func>
  case_t& _when(const ch_bitbase<N>& value, const Func& func) {
    m_impl.push(value.get_node().get_impl(), to_function(func));
    return *this;
  }
  
  template <typename Func>
  case_t& _when(const ch_bitv<N>& value, const Func& func) {    
    m_impl.push(value.get_node().get_impl(), to_function(func));
    return *this;
  }
  
  template <typename Func>
  void _else(const Func& func) {
    func(); // evaluate 'default' case
    m_impl.eval();
  }
  
  void _end() {
    m_impl.eval();
  }
  
protected:
  
  case_t(lnodeimpl* key) : m_impl(key) {}
  
  case_impl m_impl;
    
  template <unsigned N_> 
  friend case_t<N_> ch_case(const ch_bitbase<N_>& key);
};

template <unsigned N> 
case_t<N> ch_case(const ch_bitbase<N>& key) {
  return case_t<N>(key.get_node().get_impl());
}

}
