#pragma once

#include "system.h"

namespace ch {
namespace internal {

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

  ch_scbit(const system_buffer_ptr& buffer = make_system_buffer(N, idname<ch_scbit>()))
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
  ch_scbit(const U& other) {
    sdata_type tmp(N);
    bv_pad<ch_signed_v<U>>(tmp.words(), N, system_accessor::data(other).words(), ch_width_v<U>);
    buffer_ = make_system_buffer(std::move(tmp));
  }

  ch_scbit(const ch_scbit& other)
    : base()
    , buffer_(system_accessor::copy(other))
  {}

  ch_scbit(ch_scbit&& other) : buffer_(std::move(other.buffer_)) {}

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  ch_scbit& operator=(const U& other) {
    system_accessor::assign(*this, sdata_type(N , other));
    return *this;
  }

  template <typename U,
            CH_REQUIRE_0(is_scbit_base_v<U>),
            CH_REQUIRE_0(ch_width_v<U> < N)>
  ch_scbit& operator=(const U& other) {
    sdata_type tmp(N);
    bv_pad<ch_signed_v<U>>(tmp.words(), N, system_accessor::data(other).words(), ch_width_v<U>);
    system_accessor::assign(*this, tmp);
    return *this;
  }

  ch_scbit& operator=(const ch_scbit& other) {
    system_accessor::assign(*this, other);
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

  const system_buffer_ptr& __buffer() const {
    return buffer_;
  }

  system_buffer_ptr buffer_;

  friend class system_accessor;
                   template <typename T>
                   static auto copy(const T& obj) {
                     assert(obj.__buffer()->size() == ch_width_v<T>);
                     return make_system_buffer(*obj.__buffer());
                   }
  friend std::ostream& operator<<(std::ostream& out, const ch_scbit& in) {
    return out << system_accessor::data(in);
  }
};

//
// read/write function
//

template <typename T, typename U>
void ch_read(const T& obj,
             uint32_t src_offset,
             U* out,
             uint32_t dst_offset = 0,
             uint32_t length = ch_width_v<T>) {
  static_assert(is_system_type_v<T>, "invalid type");
  system_accessor::buffer(obj)->read(src_offset, out, sizeof(U), dst_offset, length);
}

template <typename T, typename U>
void ch_write(T& obj,
              uint32_t dst_offset,
              U* in,
              uint32_t src_offset = 0,
              uint32_t length = ch_width_v<T>) {
  static_assert(is_system_type_v<T>, "invalid type");
  system_accessor::buffer(obj)->write(dst_offset, in, sizeof(U), src_offset, length);
}

}
}
