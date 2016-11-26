#pragma once

#include "bit.h"

namespace chdl_internal {

class if_t {
public:
  
  ~if_t() {
    if (m_stmts) {
      CHDL_CHECK(m_stmts->empty(), "incomplete if statement");
      delete m_stmts;
    }
  }
    
  template <typename Func>
  if_t& elif_(const ch_logicbase& cond, const Func& func) {
    m_stmts->push({cond.get_node().get_impl(), to_function(func)});
    return *this; 
  }
  
  template <typename Func>
  void else_(const Func& func) {
    func(); // evaluate 'else' case
    this->eval();
  }
  
  void operator()() {
    this->eval();
  }
  
protected:
  
  using func_t = std::function<void ()>;
  
  struct stmt_t { // LCOV_EXCL_LINE
    lnodeimpl* cond;
    func_t func;
  };
  
  using stmts_t = std::stack<stmt_t>;
  
  if_t(lnodeimpl* cond, func_t func) : m_stmts(new stmts_t()) {
    m_stmts->push({cond, func});
  }
  
  void eval();
  
  stmts_t* m_stmts;
    
  template <typename Func> 
  friend if_t ch_if(const ch_logicbase& cond, const Func& func);
};

template <typename Func> 
if_t ch_if(const ch_logicbase& cond, const Func& func) {
  return if_t(cond.get_node().get_impl(), to_function(func));
}

#define CHDL_IF_BODY(value)   value})
#define CHDL_IF(cond)         ch_if(cond, [&](){CHDL_IF_BODY
#define CHDL_ELIF(cond)       .elif_(cond, [&](){CHDL_IF_BODY
#define CHDL_ELSE(value)      .else_([&](){value})

}
