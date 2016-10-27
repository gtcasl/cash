#pragma once

#include "bitv.h"

namespace chdl_internal {

class when_t {
public:
  
  ~when_t() {
    if (m_stmts) {
      CHDL_CHECK(m_stmts->empty(), "incomplete when statement");
      delete m_stmts;
    }
  }
    
  template <typename Func>
  when_t when(const ch_logic& cond, const Func& func) {
    return this->push(cond, to_function(func));
  }
  
  template <typename Func>
  void end(const Func& func) {
    func(); // evaluate 'else' case
    this->eval();
  }
  
  void end() {
    this->eval();
  }
  
protected:
  
  typedef std::function<void ()> func_t;
  
  struct stmt_t {
    const ch_logic& cond;
    func_t func;
  };
  
  typedef std::stack<stmt_t> stmts_t;
  
  when_t(stmts_t* stmts = new stmts_t()) : m_stmts(stmts) {}
  
  when_t push(const ch_logic& cond, const func_t& func) {    
    stmts_t* stmts = m_stmts;
    m_stmts = nullptr;
    stmts->push({cond, func});
    return when_t(stmts);
  }
  
  void eval();
  
  stmts_t* m_stmts;
    
  template <typename Func> 
  friend when_t ch_when(const ch_logic& cond, const Func& func);
};

template <typename Func> 
when_t ch_when(const ch_logic& cond, const Func& func) {
  return when_t().push(cond, to_function(func));
}

}
