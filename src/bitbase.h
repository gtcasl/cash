#pragma once

#include "lnode.h"

namespace cash {
namespace internal {

enum ch_boolean {
  ch_false = 0,
  ch_true  = 1
};

template <typename Derived>
class ch_bitbase;

template <unsigned N> class ch_bit;

template <unsigned N> const ch_bit<N> make_bit(const lnode& node);

template <>
struct data_traits <lnode> {
  template <typename T> using base_type = ch_bitbase<T>;

  template <typename T> static const T make_type(const lnode& node) {
    return T(std::move(make_bit<traits<T>::bitcount>(node)));
  }
};

template <typename Derived>
struct traits < ch_bitbase<Derived> > {
  static constexpr unsigned bitcount = traits<Derived>::bitcount;
};

template <typename Derived, bool readonly>
class bitbaseimpl;

template <typename Derived>
class bitbaseimpl<Derived, false> : public typebase<Derived> {
public:
  using base = typebase<Derived>;
  using base::self;

  static_assert(std::is_same<typename traits<Derived>::data_type, lnode>::value, "data type mismatch");

  template <typename OtherDerived,
            CH_REQUIRES(traits<OtherDerived>::bitcount == traits<Derived>::bitcount)>
  Derived& operator=(const ch_bitbase<OtherDerived>& rhs) {
    return this->assign(rhs);
  }

  template <typename T,
            CH_REQUIRES(is_scalar<T>::value)>
  Derived& operator=(const T& rhs) {
    return this->assign(rhs);
  }
  
  Derived& operator=(const ch_boolean& rhs) {
    return this->assign((int)rhs);
  }

  auto operator[](size_t index) & {
    return sliceref<Derived, 1>(*self(), index);
  }

  const auto operator[](size_t index) const & {
    return const_sliceref<ch_bit<1>, 1>(*self(), index);
  }

  const auto operator[](size_t index) const && {
    return const_sliceref<Derived, 1>(std::move(*self()), index);
  }

  template <unsigned M>
  auto slice(size_t index = 0) & {
    return sliceref<Derived, M>(*self(), index);
  }

  template <unsigned M>
  const auto slice(size_t index = 0) const & {
    return const_sliceref<ch_bit<M>, M>(*self(), index);
  }

  template <unsigned M>
  const auto slice(size_t index = 0) const && {
    return const_sliceref<Derived, M>(std::move(*self()), index);
  }

  template <unsigned M>
  auto aslice(size_t index = 0) & {
    return sliceref<Derived, M>(*self(), index * M);
  }

  template <unsigned M>
  const auto aslice(size_t index = 0) const & {
    return const_sliceref<ch_bit<M>, M>(*self(), index * M);
  }

  template <unsigned M>
  const auto aslice(size_t index = 0) const && {
    return const_sliceref<Derived, M>(std::move(*self()), index * M);
  }
};

template <typename Derived>
class bitbaseimpl<Derived, true> : public typebase<Derived> {
public:
  using base = typebase<Derived>;
  using base::self;

  static_assert(std::is_same<typename traits<Derived>::data_type, lnode>::value, "data type mismatch");

  const auto operator[](size_t index) const & {
    return const_sliceref<ch_bit<1>, 1>(*self(), index);
  }

  const auto operator[](size_t index) const && {
    return const_sliceref<Derived, 1>(std::move(*self()), index);
  }

  template <unsigned M>
  const auto slice(size_t index = 0) const & {
    return const_sliceref<ch_bit<M>, M>(*self(), index);
  }

  template <unsigned M>
  const auto slice(size_t index = 0) const && {
    return const_sliceref<Derived, M>(std::move(*self()), index);
  }

  template <unsigned M>
  const auto aslice(size_t index = 0) const & {
    return const_sliceref<ch_bit<M>, M>(*self(), index * M);
  }

  template <unsigned M>
  const auto aslice(size_t index = 0) const && {
    return const_sliceref<Derived, M>(std::move(*self()), index * M);
  }
};

template <typename Derived>
class ch_bitbase : public bitbaseimpl<Derived, traits<Derived>::readonly> {
public:
  using base = bitbaseimpl<Derived, traits<Derived>::readonly>;
  using base::operator=;
};

}
}
