#pragma once

#include "bit.h"

namespace cash_internal {

class if_t {
public:
  
  ~if_t();
    
  template <typename Func>
  if_t& elif_(const ch_logicbase& cond, const Func& func) {
    this->eval(cond.get_node().get_impl(), to_function(func));
    return *this; 
  }
  
  template <typename Func>
  void else_(const Func& func) {
    this->eval(nullptr, to_function(func));
  }
  
protected:
  
  using func_t = std::function<void ()>;
  
  if_t(lnodeimpl* cond, func_t func);
  
  void eval(lnodeimpl* cond, func_t func);
  
  template <typename Func> 
  friend if_t ch_if(const ch_logicbase& cond, const Func& func);
};

template <typename Func> 
if_t ch_if(const ch_logicbase& cond, const Func& func) {
  return if_t(cond.get_node().get_impl(), to_function(func));
}

#define CH_IF_BODY(value)   value })
#define CH_IF(cond)         ch_if(cond, [&](){ CH_IF_BODY
#define CH_ELIF(cond)       .elif_(cond, [&](){ CH_IF_BODY
#define CH_ELSE(value)      .else_([&](){ value })

}
