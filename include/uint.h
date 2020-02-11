#pragma once

#include "numbase.h"

namespace ch {
namespace internal {

template <unsigned N = 32>
class ch_suint : public ch_snumbase<ch_suint<N>> {
public:
  using traits = system_traits<N, false, ch_suint, ch_uint<N>>;
  using base = ch_snumbase<ch_suint<N>>;
  using base::operator=;

  explicit ch_suint(const system_buffer& buffer = make_system_buffer(N))
    : buffer_(buffer) {
    assert(N == buffer->size());
  }

  template <typename U,
            CH_REQUIRES(std::is_integral_v<U>)>
  ch_suint(const U& other)
    : ch_suint(make_system_buffer(N)) {
    this->operator=(other);
  }

  template <typename U,
            CH_REQUIRES(is_bitvector_extended_type_v<U>)>
  explicit ch_suint(U&& other)
    : ch_suint(make_system_buffer(N)) {
    this->operator=(ch_suint(make_system_buffer(sdata_type(N , std::forward<U>(other)))));
  }

  template <typename U,
            CH_REQUIRES(ch_width_v<U> <= N)>
  explicit ch_suint(const ch_sbitbase<U>& other)
    : ch_suint(make_system_buffer(N)) {
    this->operator=(reinterpret_cast<const U&>(other));
  }

  ch_suint(const ch_sbool& other)
    : ch_suint(make_system_buffer(N)) {
    this->operator=(other);
  }

  template <unsigned M,
            CH_REQUIRES(M <= N)>
  ch_suint(const ch_sbit<M>& other)
    : ch_suint(make_system_buffer(N)) {
    this->operator=(other);
  }

  template <unsigned M,
            CH_REQUIRES(M <= N)>
  ch_suint(const ch_sint<M>& other)
    : ch_suint(make_system_buffer(N)) {
    this->operator=(other);
  }

  template <unsigned M,
            CH_REQUIRES(M < N)>
  ch_suint(const ch_suint<M>& other)
    : ch_suint(make_system_buffer(N)) {
    this->operator=(other);
  }

  ch_suint(const ch_suint& other)
    : ch_suint(system_accessor::copy(other)) {
    this->operator=(other);
  }

  ch_suint(ch_suint&& other) : buffer_(std::move(other.buffer_)) {}

  ch_suint& operator=(const ch_suint& other) {
    system_accessor::assign(*this, other);
    return *this;
  }

  ch_suint& operator=(ch_suint&& other) {
    system_accessor::move(*this, std::move(other));
    return *this;
  }

protected:

  const system_buffer& __buffer() const {
    return buffer_;
  }

  system_buffer buffer_;

  friend class system_accessor;
};

///////////////////////////////////////////////////////////////////////////////

template <unsigned N = 32>
class ch_uint : public ch_numbase<ch_uint<N>> {
public:  
  using traits = logic_traits<N, false, ch_uint, ch_suint<N>>;
  using base = ch_numbase<ch_uint<N>>;
  using base::operator=;

  explicit ch_uint(const logic_buffer& buffer 
    = make_logic_buffer(N, CH_CUR_SRC_INFO))
    : buffer_(buffer) {
    assert(N == buffer.size());
  }

  template <typename U,
            CH_REQUIRES(std::is_integral_v<U>)>
  ch_uint(const U& other, CH_SRC_INFO)
    : ch_uint(make_logic_buffer(N, srcinfo)) {
    this->operator=(other);
  }

  template <typename U,
            CH_REQUIRES(ch_width_v<U> <= N)>
  explicit ch_uint(const ch_sbitbase<U>& other, CH_SRC_INFO)
    : ch_uint(make_logic_buffer(N, srcinfo)) {
    this->operator=(reinterpret_cast<const U&>(other));
  }

  ch_uint(const ch_sbool& other, CH_SRC_INFO)
    : ch_uint(make_logic_buffer(N, srcinfo)) {
    this->operator=(other);
  }

  template <unsigned M,
            CH_REQUIRES(M <= N)>
  ch_uint(const ch_sbit<M>& other, CH_SRC_INFO)
    : ch_uint(make_logic_buffer(N, srcinfo)) {
    this->operator=(other);
  }

  template <unsigned M,
            CH_REQUIRES(M <= N)>
  ch_uint(const ch_sint<M>& other, CH_SRC_INFO)
    : ch_uint(make_logic_buffer(N, srcinfo)) {
    this->operator=(other);
  }

  template <unsigned M,
            CH_REQUIRES(M <= N)>
  ch_uint(const ch_suint<M>& other, CH_SRC_INFO)
    : ch_uint(make_logic_buffer(N, srcinfo)) {
    this->operator=(other);
  }

  template <typename U,
            CH_REQUIRES(ch_width_v<U> <= N)>
  explicit ch_uint(const ch_bitbase<U>& other, CH_SRC_INFO)
    : ch_uint(make_logic_buffer(N, srcinfo)) {
    this->operator=(reinterpret_cast<const U&>(other));
  }

  ch_uint(const ch_bool& other, CH_SRC_INFO)
    : ch_uint(make_logic_buffer(N, srcinfo)) {
    this->operator=(other);
  }

  template <unsigned M,
            CH_REQUIRES(M <= N)>
  ch_uint(const ch_bit<M>& other, CH_SRC_INFO)
    : ch_uint(make_logic_buffer(N, srcinfo)) {
    this->operator=(other);
  }

  template <unsigned M,
            CH_REQUIRES(M <= N)>
  ch_uint(const ch_int<M>& other, CH_SRC_INFO)
    : ch_uint(make_logic_buffer(N, srcinfo)) {
    this->operator=(other);
  }

  template <unsigned M,
            CH_REQUIRES(M < N)>
  ch_uint(const ch_uint<M>& other, CH_SRC_INFO)
    : ch_uint(make_logic_buffer(N, srcinfo)) {
    this->operator=(other);
  }

  ch_uint(const ch_uint& other, CH_SRC_INFO)
    : ch_uint(make_logic_buffer(N, srcinfo)) {
    this->operator=(other);
  }

  ch_uint(ch_uint&& other) : buffer_(std::move(other.buffer_)) {}

  ch_uint& operator=(const ch_uint& other) {
    logic_accessor::assign(*this, other);
    return *this;
  }

  ch_uint& operator=(ch_uint&& other) {
    logic_accessor::move(*this, std::move(other));
    return *this;
  }

protected:

  const logic_buffer& __buffer() const {
    return buffer_;
  }

  logic_buffer buffer_;

  friend class logic_accessor;
};

}}
