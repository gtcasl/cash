#pragma once

#include "bit.h"

namespace ch {
namespace internal {

class if_t {  
protected:

  using func_t = std::function<void ()>;

  void eval(const lnode& pred, func_t func);

  void eval(func_t func);

public:

  if_t(const lnode& pred, func_t func);
  
  ~if_t();
    
  template <typename Func>
  if_t& elif_(const ch_bitbase<1>& pred, const Func& func) {
    this->eval(get_lnode(pred), to_function(func));
    return *this; 
  }
  
  template <typename Func>
  void else_(const Func& func) {
    this->eval(to_function(func));
  }
};

template <typename Func>
if_t ch_if(const ch_bitbase<1>& pred, const Func& func) {
  return if_t(get_lnode(pred), func);
}

}
}

#define CH_IF_BODY(value)   value })
#define CH_IF(pred)         ch_if(pred, [&](){ CH_IF_BODY
#define CH_ELIF(pred)       .elif_(pred, [&](){ CH_IF_BODY
#define CH_ELSE(value)      .else_([&](){ value })
