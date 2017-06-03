#pragma once

#include "typebase.h"

namespace cash {
namespace detail {

template <typename T, unsigned N> 
class ch_vec : public typebase<N * T::bit_count, typename T::data_type> {
public:
  using base = typebase<N * T::bit_count, typename T::data_type>;
  using base::operator=;
  using data_type = typename base::data_type;
  using bus_type = ch_vec<typename T::bus_type, N>;
  
  ch_vec() {}
  
  template <typename U>
  ch_vec(const ch_vec<U, N>& rhs) {
    for (unsigned i = 0; i < N; ++i) {
      items_[i] = rhs.items_[i];
    }
  }
  
  ch_vec(const ch_bitbase<T::bit_count>& rhs) {
    data_type data(N);
    rhs.read(data, 0, N);
    this->write(0, data, 0, N);
  }
  
  explicit ch_vec(const T& rhs) {
    for (unsigned i = 0; i < N; ++i) {
      items_[i] = rhs;
    }
  }
  
  template <typename U>
  ch_vec(const std::initializer_list<U>& rhs) {
    CH_CHECK(rhs.size() == N, "initializer list size missmatch!");
    unsigned i = N;
    for (auto& x : rhs) {
      items_[--i] = x;
    }
  }
  
  ch_vec(const base& rhs) {
    this->operator =(rhs);
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
    CH_CHECK(rhs.size() == N, "initializer list size missmatch!");
    unsigned i = N;
    for (auto& x : rhs) {
      items_[--i] = x;
    }
    return *this;
  }

  auto operator[](size_t i) {
    CH_CHECK(i < N, "invalid subscript index");
    return items_[i];
  }

  auto operator[](size_t i) const {
    CH_CHECK(i < N, "invalid subscript index");
    return items_[i];
  }

protected:
  
  std::array<T, N> items_;
  
  void read_data(data_type& out, size_t offset, size_t length) const override {
    CH_CHECK(offset + length <= ch_vec::bit_count, "invalid vector read range");
    for (unsigned i = 0; length && i < N; ++i) {
      if (offset < T::bit_count) {     
        size_t len = std::min<size_t>(length, T::bit_count - offset);
        detail::read_data(items_[i], out, offset, len);
        length -= len;
        offset = T::bit_count;
      }
      offset -= T::bit_count;
    }
  }
  
  void write_data(size_t dst_offset, const data_type& data, size_t src_offset, size_t src_length) override {
    CH_CHECK(dst_offset + src_length <= ch_vec::bit_count, "invalid vector write range");
    for (unsigned i = 0; src_length && i < N; ++i) {
      if (dst_offset < T::bit_count) {
        size_t len = std::min<size_t>(src_length, T::bit_count - dst_offset);
        detail::write_data(items_[i], dst_offset, data, src_offset, len);
        src_length -= len;
        src_offset += len;
        dst_offset = T::bit_count;
      }
      dst_offset -= T::bit_count;
    }
  }
};

}
}
