#pragma once

#include "reg.h"

namespace ch {
namespace internal {

template <typename T>
class ch_seq final : public const_type_t<T> {
public:
  using base = const_type_t<T>;
  using traits = logic_traits<ch_seq, const_type_t<T>, T, scalar_type_t<T>>;

  T next;

  ch_seq() {
    base::assign(ch_reg(next));
    next = *this;
  }
  
  template <typename U,
            CH_REQUIRES(is_cast_convertible<T, U>::value)>
  explicit ch_seq(const U& init) {
    base::assign(ch_reg(next, init));
    next = *this;
  }

protected:

  ch_seq(ch_seq&&) = delete;
  ch_seq& operator=(const ch_seq&) = delete;
  ch_seq& operator=(ch_seq&&) = delete;
};

}
}
