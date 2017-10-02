#pragma once

#include "bitbase.h"

namespace ch {
namespace internal {

template <typename T, unsigned N>
class ch_vec;

template <typename T, unsigned N>
class const_vec;

template <typename T, unsigned N>
class const_vec : public ch_bitbase<N * T::bitcount> {
public:
  using base = ch_bitbase<N * T::bitcount>;
  using value_type = ch_vec<T, N>;
  using const_type = const_vec;
  
  const_vec() {}

  const_vec(const const_vec& rhs) : items_(rhs.items_) {}

  const_vec(const_vec&& rhs) : items_(std::move(rhs.items_)) {}

  template <typename U,
            CH_REQUIRES(is_cast_convertible<U, T>::value)>
  const_vec(const const_vec<U, N>& rhs) {
    for (unsigned i = 0; i < N; ++i) {
      items_[i] = rhs.items_[i];
    }
  }

  const_vec(const base& rhs) {
    this->assign(rhs);
  }

  template <typename... Vs,
           CH_REQUIRES(are_all_cast_convertible<T, Vs...>::value)>
  explicit const_vec(const Vs&... values) {
    this->init(values...);
  }

  template <typename U,
            CH_REQUIRES(ch::internal::is_ch_scalar<U>::value)>
  explicit const_vec(U value) {
    this->assign(value);
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
  
  void read_data(nodelist& out, size_t offset, size_t length) const override {
    for (unsigned i = 0; length && i < N; ++i) {
      if (offset < T::bitcount) {
        size_t len = std::min<size_t>(length, T::bitcount - offset);
        ch::internal::read_data(items_[i], out, offset, len);
        offset = T::bitcount;        
        length -= len;
      }
      offset -= T::bitcount;
    }
  }
  
  void write_data(size_t dst_offset, const nodelist& data, size_t src_offset, size_t length) override {
    for (unsigned i = 0; length && i < N; ++i) {
      if (dst_offset < T::bitcount) {
        size_t len = std::min<size_t>(length, T::bitcount - dst_offset);
        ch::internal::write_data(items_[i], dst_offset, data, src_offset, len);
        src_offset += len;
        dst_offset = T::bitcount;
        length -= len;
      }
      dst_offset -= T::bitcount;
    }
  }

  void read_bytes(uint32_t dst_offset, void* out, uint32_t out_cbsize, uint32_t src_offset, uint32_t length) const override {
    for (unsigned i = 0; length && i < N; ++i) {
      if (dst_offset < T::bitcount) {
        size_t len = std::min<size_t>(length, T::bitcount - dst_offset);
        ch::internal::read_bytes(items_[i], dst_offset, out, out_cbsize, src_offset, len);
        src_offset += len;
        dst_offset = T::bitcount;
        length -= len;
      }
      dst_offset -= T::bitcount;
    }
  }

  void write_bytes(uint32_t dst_offset, const void* in, uint32_t in_cbsize, uint32_t src_offset, uint32_t length) const override {
    for (unsigned i = 0; length && i < N; ++i) {
      if (dst_offset < T::bitcount) {
        size_t len = std::min<size_t>(length, T::bitcount - dst_offset);
        ch::internal::write_bytes(items_[i], dst_offset, in, in_cbsize, src_offset, len);
        src_offset += len;
        dst_offset = T::bitcount;
        length -= len;
      }
      dst_offset -= T::bitcount;
    }
  }
};

template <typename T, unsigned N>
class ch_vec : public const_vec<T, N> {
public:
  using base = const_vec<T, N>;
  using value_type = ch_vec;
  using const_type = const_vec<T, N>;

  using base::items_;

  ch_vec() {}

  ch_vec(const ch_vec& rhs) : base(rhs) {}

  ch_vec(ch_vec&& rhs) : base(rhs) {}

  template <typename U,
            CH_REQUIRES(is_cast_convertible<U, T>::value)>
  ch_vec(const const_vec<U, N>& rhs) : base(rhs) {}

  template <typename U,
            CH_REQUIRES(is_cast_convertible<U, T>::value)>
  ch_vec(const ch_vec<U, N>& rhs) : base(rhs) {}

  ch_vec(const ch_bitbase<base::bitcount>& rhs) : base(rhs) {}

  template <typename... Vs,
           CH_REQUIRES(are_all_cast_convertible<T, Vs...>::value)>
  explicit ch_vec(const Vs&... values) : base(values...) {}

  template <typename U,
            CH_REQUIRES(ch::internal::is_ch_scalar<U>::value)>
  explicit ch_vec(U value) : base(value) {} \

  ch_vec& operator=(const ch_vec& rhs) {
    items_ = rhs.items_;
    return *this;
  }

  ch_vec& operator=(ch_vec&& rhs) {
    items_ = std::move(rhs.items_);
    return *this;
  }

  template <typename U,
            CH_REQUIRES(is_cast_convertible<U, T>::value)>
  ch_vec& operator=(const ch_vec<U, N>& rhs) {
    for (unsigned i = 0; i < N; ++i) {
      items_[i] = rhs.items_[i];
    }
    return *this;
  }

  ch_vec& operator=(const ch_bitbase<base::bitcount>& rhs) {
    this->assign(rhs);
    return *this;
  }

  template <typename U, CH_REQUIRES(ch::internal::is_ch_scalar<U>::value)>
  ch_vec& operator=(U rhs) {
    this->assign(rhs);
    return *this;
  }

  const T& operator[](size_t i) const {
    CH_CHECK(i < N, "invalid subscript index");
    return items_[i];
  }

  T& operator[](size_t i) {
    CH_CHECK(i < N, "invalid subscript index");
    return items_[i];
  }
};

}
}
