#pragma once

#include "reg.h"

namespace cash {
namespace internal {

template <typename T>
class ch_seq : public T::const_t {
public:
  using base = typename T::const_t;
  using value_t = T;

  T next;

  ch_seq() {
    this->assign(ch_reg(next));
    next = *this;
  }
  
  template <typename U,
            CH_REQUIRES(is_cast_convertible<U, T>::value)>
  explicit ch_seq(const U& init) {
    this->assign(ch_reg(next, init));
    next = *this;
  }

protected:

  ch_seq(ch_seq&&) = delete;
  ch_seq& operator=(const ch_seq&) = delete;
  ch_seq& operator=(ch_seq&&) = delete;
};

}
}
