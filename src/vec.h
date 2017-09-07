#pragma once

#include "typebase.h"

namespace cash {
namespace internal {

template <typename T, unsigned N> 
class ch_vec : public typebase<N * T::bitcount, typename T::data_type> {
public:
  using base = typebase<N * T::bitcount, typename T::data_type>;
  using base::operator=;
  using data_type = typename base::data_type;
  using bus_type = ch_vec<typename T::bus_type, N>;
  
  ch_vec() {}

  ch_vec(const ch_vec& rhs) : items_(rhs.items_) {}

  ch_vec(ch_vec&& rhs) : items_(std::move(rhs.items_)) {}
  
  template <typename U>
  explicit ch_vec(const ch_vec<U, N>& rhs) : items_(rhs.items_) {}

  template<typename... Vs,
           typename = typename std::enable_if<N == sizeof...(Vs)>::type,
           typename = typename if_all_convertible<T, Vs...>::type>
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
  
  template <typename U>
  ch_vec& operator=(const std::initializer_list<U>& rhs) {
    static_assert(N == rhs.size(), "initializer list size missmatch!");
    unsigned i = N;
    for (auto& x : rhs) {
      items_[--i] = x;
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
    items_[N-1] = value;
  }

  template <typename V0, typename... Vs>
  void init(const V0& value0, const Vs&... values) {
    items_[N - sizeof...(Vs)] = value0;
    this->init(values...);
  }
  
  void read_data(data_type& out, size_t offset, size_t length) const override {
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
  
  void write_data(size_t dst_offset, const data_type& data, size_t src_offset, size_t length) override {
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
