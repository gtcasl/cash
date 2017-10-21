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
    auto& buffer = bit_accessor::get_buffer(*this);
    auto reg = createRegNode(get_lnode<T>(next), get_lnode<int, T::bitwidth>(0));
    buffer.set_data(reg);
    next = *this;
  }
  
  template <typename U,
            CH_REQUIRES(is_cast_convertible<T, U>::value)>
  explicit ch_seq(const U& init) {
    auto& buffer = bit_accessor::get_buffer(*this);
    auto reg = createRegNode(get_lnode<T>(next), get_lnode<U, T::bitwidth>(init));
    buffer.set_data(reg);
    next = *this;
  }

protected:

  ch_seq(ch_seq&) = delete;
  ch_seq(ch_seq&&) = delete;
  ch_seq& operator=(const ch_seq&) = delete;
  ch_seq& operator=(ch_seq&&) = delete;
};

}
}
