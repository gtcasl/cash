#pragma once

#include "lnode.h"

namespace cash {
namespace internal {

enum ch_boolean {
  ch_false = 0,
  ch_true  = 1
};

template <unsigned N> class ch_bit;

template <unsigned N> const ch_bit<N> make_bit(const lnode& node);

template <typename T, unsigned N, bool R>
class bitbaseimpl;

template <typename T, unsigned N = T::bitcount, bool R = T::readonly>
class ch_bitbase : public bitbaseimpl<T, N, R> {
public:
  using base = bitbaseimpl<T, N, R>;
  using base::operator=;
};

template <>
struct data_traits <lnode> {
  template <typename T, unsigned N = T::bitcount, bool R = T::readonly> using base_t = ch_bitbase<T, N, R>;

  template <typename T> static const T make_type(const lnode& node) {
    return T(std::move(make_bit<T::bitcount>(node)));
  }
};

template <typename T, unsigned N>
class bitbaseimpl<T, N, false> : public typebase<T, lnode, N, false> {
public:
  using base = typebase<T, lnode, N, false>;
  using base::self;

  template <typename U>
  T& operator=(const ch_bitbase<U>& rhs) {
    static_assert(U::bitcount == N, "size mismatch");
    return this->assign(rhs);
  }

  template <typename U,
            CH_REQUIRES(is_scalar<U>::value)>
  T& operator=(U rhs) {
    return this->assign(rhs);
  }

  T& operator=(const ch_boolean& rhs) {
    return this->assign((int)rhs);
  }

  auto operator[](size_t index) & {
    return sliceref<T, 1>(*self(), index);
  }

  const auto operator[](size_t index) const & {
    return const_sliceref<ch_bit<1>, 1>(*self(), index);
  }

  const auto operator[](size_t index) const && {
    return const_sliceref<T, 1>(std::move(*self()), index);
  }

  template <unsigned M>
  auto slice(size_t index = 0) & {
    return sliceref<T, M>(*self(), index);
  }

  template <unsigned M>
  const auto slice(size_t index = 0) const & {
    return const_sliceref<ch_bit<M>, M>(*self(), index);
  }

  template <unsigned M>
  const auto slice(size_t index = 0) const && {
    return const_sliceref<T, M>(std::move(*self()), index);
  }

  template <unsigned M>
  auto aslice(size_t index = 0) & {
    return sliceref<T, M>(*self(), index * M);
  }

  template <unsigned M>
  const auto aslice(size_t index = 0) const & {
    return const_sliceref<ch_bit<M>, M>(*self(), index * M);
  }

  template <unsigned M>
  const auto aslice(size_t index = 0) const && {
    return const_sliceref<T, M>(std::move(*self()), index * M);
  }
};

template <typename T, unsigned N>
class bitbaseimpl<T, N, true> : public typebase<T, lnode, N, true> {
public:
  using base = typebase<T, lnode, N, true>;
  using base::self;

  const auto operator[](size_t index) const & {
    return const_sliceref<ch_bit<1>, 1>(*self(), index);
  }

  const auto operator[](size_t index) const && {
    return const_sliceref<T, 1>(std::move(*self()), index);
  }

  template <unsigned M>
  const auto slice(size_t index = 0) const & {
    return const_sliceref<ch_bit<M>, M>(*self(), index);
  }

  template <unsigned M>
  const auto slice(size_t index = 0) const && {
    return const_sliceref<T, M>(std::move(*self()), index);
  }

  template <unsigned M>
  const auto aslice(size_t index = 0) const & {
    return const_sliceref<ch_bit<M>, M>(*self(), index * M);
  }

  template <unsigned M>
  const auto aslice(size_t index = 0) const && {
    return const_sliceref<T, M>(std::move(*self()), index * M);
  }
};

}
}
