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
    
  template <typename Func, typename P,
            CH_REQUIRES(is_bit_convertible<P>::value)>
  if_t& elif_(const P& pred, const Func& func) {
    static_assert(1 == bitwidth_v<P>, "invalid predicate size");
    this->eval(get_lnode(pred), to_function_t<Func>(func));
    return *this; 
  }
  
  template <typename Func>
  void else_(const Func& func) {
    this->eval(to_function_t<Func>(func));
  }
};

template <typename Func, typename P,
          CH_REQUIRES(is_bit_convertible<P>::value)>
if_t ch_if(const P& pred, const Func& func) {
  static_assert(1 == bitwidth_v<P>, "invalid predicate size");
  return if_t(get_lnode(pred), func);
}

}
}

#define CH_IF_BODY(value)   value })
#define CH_IF(pred)         ch_if(pred, [&](){ CH_IF_BODY
#define CH_ELIF(pred)       .elif_(pred, [&](){ CH_IF_BODY
#define CH_ELSE(value)      .else_([&](){ value })
