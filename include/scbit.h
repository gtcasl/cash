#pragma once

#include "system.h"

namespace ch {
namespace internal {

template <unsigned N> class ch_bit;

template <unsigned N>
class ch_scbit : public system_op_equality<ch_scbit, N,
                          system_op_logical<ch_scbit, N,
                            system_op_bitwise<ch_scbit, N,
                              system_op_shift<ch_scbit, N,
                                system_op_cast<ch_scbit, N,
                                  system_op_slice<ch_scbit, N>>>>>> {
public:
  using traits = system_traits<N, false, ch_scbit, ch_bit<N>>;
  using base = system_op_equality<ch_scbit, N,
                system_op_logical<ch_scbit, N,
                  system_op_bitwise<ch_scbit, N,
                    system_op_shift<ch_scbit, N,
                      system_op_cast<ch_scbit, N,
                        system_op_slice<ch_scbit, N>>>>>>;
  using Q = bool;

  explicit ch_scbit(const system_buffer_ptr& buffer = make_system_buffer(N))
    : buffer_(buffer) {
    assert(N == buffer->size());
  }

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  ch_scbit(const U& other)
    : buffer_(make_system_buffer(sdata_type(N , other)))
  {}

  template <typename U,
            CH_REQUIRE_0(is_bitvector_extended_type_v<U>)>
  explicit ch_scbit(U&& other)
    : buffer_(make_system_buffer(sdata_type(N , std::forward<U>(other))))
  {}

  template <typename U,
            CH_REQUIRE_0(is_scbit_base_v<U>),
            CH_REQUIRE_0(ch_width_v<U> < N)>
  explicit ch_scbit(const U& other) {
    sdata_type ret(N);
    if constexpr (ch_signed_v<U>) {
      bv_sext(ret.words(), N, system_accessor::data(other).words(), ch_width_v<U>);
    } else {
      bv_zext(ret.words(), N, system_accessor::data(other).words(), ch_width_v<U>);
    }
    buffer_ = make_system_buffer(std::move(ret));
  }

  ch_scbit(const ch_scbit& other)
    : base()
    , buffer_(system_accessor::copy(other))
  {}

  ch_scbit(ch_scbit&& other) : buffer_(std::move(other.buffer_)) {}

  ch_scbit& operator=(const ch_scbit& other) {
    system_accessor::copy(*this, other);
    return *this;
  }

  ch_scbit& operator=(ch_scbit&& other) {
    system_accessor::move(*this, std::move(other));
    return *this;
  }

  // subscript operators

  auto operator[](size_t index) const {
    assert(index < N);
    return this->template slice<1>(index);
  }

  auto operator[](size_t index) {
    assert(index < N);
    return this->template sliceref<1>(index);
  }

  CH_SYSTEM_INTERFACE(ch_scbit)

protected:

  const system_buffer_ptr& buffer() const {
    return buffer_;
  }

  system_buffer_ptr buffer_;

  friend class system_accessor;

  friend std::ostream& operator<<(std::ostream& out, const ch_scbit& in) {
    return out << system_accessor::data(in);
  }
};

}
}
