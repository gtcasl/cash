#pragma once

#include "reg.h"

namespace ch {
namespace internal {

template <typename T>
class ch_seq final : public const_type_t<T> {
public:
  using base = const_type_t<T>;
  using traits = logic_traits<bitwidth_v<T>, ch_seq, const_type_t<T>, T, scalar_type_t<T>>;

  T next;

  ch_seq(const bit_buffer& buffer = bit_buffer(bitwidth_v<T>, CH_SOURCE_LOCATION))
    : base(buffer) {
    auto reg = createRegNode(get_lnode(next), get_lnode<int, bitwidth_v<T>>(0));
    bit_accessor::set_data(*this, reg);
    next = *this;
  }

  template <typename U, CH_REQUIRES(is_cast_convertible<T, U>::value)>
  explicit ch_seq(const U& init,
                  const source_location& sloc = CH_SOURCE_LOCATION)
    : base(bit_buffer(bitwidth_v<T>, sloc)) {
    auto reg = createRegNode(get_lnode(next), get_lnode<U, T>(init));
    bit_accessor::set_data(*this, reg);
    next = *this;
  }

  ch_seq(ch_seq&& rhs) : base(std::move(rhs)) {}

  ch_seq& operator=(ch_seq&& rhs) {
    base::operator=(std::move(rhs));
    return *this;
  }

protected:

  ch_seq(ch_seq&) = delete;

  ch_seq& operator=(const ch_seq&) = delete;  
};

}
}
