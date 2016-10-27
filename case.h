#pragma once

#include "when.h"

namespace chdl_internal {

class case_impl {  
protected:
  
  typedef std::function<void ()> func_t;
  
  struct stmt_t {
    lnodeimpl* value;
    func_t func;
  };
  
  struct stmts_t {
    lnodeimpl* key;
    std::stack<stmt_t> values;    
    stmts_t(lnodeimpl* key_) : key(key_) {}
  };
  
  mutable stmts_t* m_stmts;
  
public:
  
  ~case_impl() {
    if (m_stmts) {
      CHDL_CHECK(m_stmts->values.empty(), "incomplete case statement");
      delete m_stmts;
    }
  }
  
  case_impl(stmts_t* stmts) : m_stmts(stmts) {}
  
  case_impl(lnodeimpl* key) {
    m_stmts = new stmts_t(key);
  }
  
  case_impl(const case_impl& rhs) : m_stmts(rhs.m_stmts) {
    rhs.m_stmts = nullptr;
  }
  
  case_impl push(const lnode& value, const func_t& func) {    
    stmts_t* stmts = m_stmts;
    m_stmts = nullptr;
    stmts->values.push({value, func});
    return case_impl(stmts);
  }
  
  void eval();
};

template <unsigned N>
class case_t {
public:
    
  template <typename Func>
  case_t when(const ch_bitbase<N>& value, const Func& func) {
    return case_t(m_impl.push(value, to_function(func)));
  }
  
  template <typename Func>
  case_t when(const ch_bitv<N>& value, const Func& func) {
    return case_t(m_impl.push(value, to_function(func)));
  }
  
  template <typename Func>
  void end(const Func& func) {
    func(); // evaluate 'default' case
    m_impl.eval();
  }
  
  void end() {
    m_impl.eval();
  }
  
protected:
  
  case_t(lnodeimpl* key) : m_impl(key) {}
  
  case_t(const case_impl& impl) : m_impl(impl) {}
    
  case_impl m_impl;
    
  template <unsigned N_> 
  friend case_t<N_> ch_case(const ch_bitbase<N_>& key);
};

template <unsigned N> 
case_t<N> ch_case(const ch_bitbase<N>& key) {
  return case_t<N>(key);
}

template <unsigned N> 
case_t<N> ch_case(const ch_bitv<N>& key) {
  return ch_case<N>(reinterpret_cast<const ch_bitbase<N>&>(key));
}

}
