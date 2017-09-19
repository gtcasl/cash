#pragma once

#include "typebase.h"

namespace cash {
namespace internal {

template <typename T, unsigned N>
class ch_vec;

template <typename T, unsigned N>
class const_vec;

template <typename T, unsigned N>
class ch_vec : public data_traits<typename T::data_t>::template base_t< ch_vec<T, N> > {
public:
  using base = typename data_traits<typename T::data_t>::template base_t< ch_vec<T, N> >;
  using base::operator=;
  using data_t  = typename base::data_t;
  using value_t = ch_vec<T, N>;
  using const_t = const_vec<T, N>;
  using bus_t   = ch_vec<typename T::bus_t, N>;
  
  ch_vec() {}

  ch_vec(const ch_vec& rhs) : items_(rhs.items_) {}

  ch_vec(ch_vec&& rhs) : items_(std::move(rhs.items_)) {}

  template <typename U>
  ch_vec(const ch_vec<U, N>& rhs) {
    this->operator =(rhs);
  }

  ch_vec(const base& rhs) {
    data_t data(base::bitcount);
    cash::internal::read_data(rhs, data, 0, base::bitcount);
    this->write_data(0, data, 0, base::bitcount);
  }

  template <typename V,
           CH_REQUIRES(N > 1),
           CH_REQUIRES(std::is_assignable<ch_vec, V>::value)>
  explicit ch_vec(const V& value) {
    this->operator =(value);
  }

  template <typename... Vs,
           CH_REQUIRES(N == sizeof...(Vs)),
           CH_REQUIRES(are_all_cast_convertible<T, Vs...>::value)>
  explicit ch_vec(const Vs&... values) {
    this->init(values...);
  }

  ch_vec& operator=(const ch_vec& rhs) {
    items_ = rhs.items_;
    return *this;
  }

  ch_vec& operator=(ch_vec&& rhs) {
    items_ = std::move(rhs.items_);
    return *this;
  }

  template <typename U>
  ch_vec& operator=(const ch_vec<U, N>& rhs) {
    for (unsigned i = 0; i < N; ++i) {
      items_[i] = rhs.items_[i];
    }
    return *this;
  }

  T& operator[](size_t i) {
    CH_CHECK(i < N, "invalid subscript index");
    return items_[i];
  }

  const T& operator[](size_t i) const {
    CH_CHECK(i < N, "invalid subscript index");
    return items_[i];
  }

protected:
  
  std::array<T, N> items_;

  template <typename V>
  void init(const V& value) {
    items_[0] = value;
  }

  template <typename V0, typename... Vs>
  void init(const V0& value0, const Vs&... values) {
    items_[sizeof...(Vs)] = value0;
    this->init(values...);
  }
  
  void read_data(data_t& out, size_t offset, size_t length) const {
    CH_CHECK(offset + length <= ch_vec::bitcount, "invalid vector read range");
    for (unsigned i = 0; length && i < N; ++i) {
      if (offset < T::bitcount) {
        size_t len = std::min<size_t>(length, T::bitcount - offset);
        cash::internal::read_data(items_[i], out, offset, len);
        length -= len;
        offset = T::bitcount;
      }
      offset -= T::bitcount;
    }
  }
  
  void write_data(size_t dst_offset, const data_t& data, size_t src_offset, size_t length) {
    CH_CHECK(dst_offset + length <= ch_vec::bitcount, "invalid vector write range");
    for (unsigned i = 0; length && i < N; ++i) {
      if (dst_offset < T::bitcount) {
        size_t len = std::min<size_t>(length, T::bitcount - dst_offset);
        cash::internal::write_data(items_[i], dst_offset, data, src_offset, len);
        length -= len;
        src_offset += len;
        dst_offset = T::bitcount;
      }
      dst_offset -= T::bitcount;
    }
  }
};

}
}
