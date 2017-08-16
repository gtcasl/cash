#pragma once

#include "bit.h"

namespace cash {
namespace detail {

class if_t {
public:
  
  ~if_t();
    
  template <typename Func>
  if_t& elif_(const ch_bitbase<1>& cond, const Func& func) {
    this->eval(get_node(cond), to_function(func));
    return *this; 
  }
  
  template <typename Func>
  void else_(const Func& func) {
    this->eval(nullptr, to_function(func));
  }
  
protected:
  
  using func_t = std::function<void ()>;
  
  if_t(const lnode& cond, func_t func);
  
  void eval(const lnode& cond, func_t func);
  
  template <typename Func> 
  friend if_t ch_if(const ch_bitbase<1>& cond, const Func& func);
};

template <typename Func> 
if_t ch_if(const ch_bitbase<1>& cond, const Func& func) {
  return if_t(get_node(cond), to_function(func));
}

}
}

#define CH_IF_BODY(value)   value })
#define CH_IF(cond)         ch_if(cond, [&](){ CH_IF_BODY
#define CH_ELIF(cond)       .elif_(cond, [&](){ CH_IF_BODY
#define CH_ELSE(value)      .else_([&](){ value })
