#pragma once

#include "if.h"

namespace chdl_internal {

class switch_impl {  
protected:
  
  using func_t = std::function<void ()>;
  
  struct stmt_t { // LCOV_EXCL_LINE
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
  
  ~switch_impl() {
    if (m_stmts) {
      CHDL_CHECK(m_stmts->values.empty(), "incomplete switch statement");
      delete m_stmts;
    }
  }
    
  switch_impl(lnodeimpl* key) {
    m_stmts = new stmts_t(key);
  }
  
  void push(lnodeimpl* value, const func_t& func) {
    m_stmts->values.push({value, func});
  }
  
  void eval(func_t func);
};

template <unsigned N>
class switch_t {
public:
    
  template <typename Func>
  switch_t& case_(const ch_bitbase<N>& value, const Func& func) {
    m_impl.push(value.get_node().get_impl(), to_function(func));
    return *this;
  }
  
  template <typename Func>
  switch_t& case_(const ch_bit<N>& value, const Func& func) {    
    m_impl.push(value.get_node().get_impl(), to_function(func));
    return *this;
  }
  
  template <typename Func>
  void default_(const Func& func) {
    m_impl.eval(to_function(func));
  }
  
  void operator()() {
    m_impl.eval(nullptr);
  }
  
protected:
  
  switch_t(lnodeimpl* key) : m_impl(key) {}
  
  switch_impl m_impl;
    
  template <unsigned N_> 
  friend switch_t<N_> ch_switch(const ch_bitbase<N_>& key);
};

template <unsigned N> 
switch_t<N> ch_switch(const ch_bitbase<N>& key) {
  return switch_t<N>(key.get_node().get_impl());
}

#define CHDL_SWITCH_BODY(body)    body
#define CHDL_SWITCH(key)          ch_switch(key) CHDL_SWITCH_BODY
#define CHDL_CASE_BODY(value)     value })
#define CHDL_CASE(cond)           .case_(cond, [&](){ CHDL_CASE_BODY
#define CHDL_DEFAULT(value)       .default_([&](){ value })

}
