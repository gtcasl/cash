#pragma once

#include "typebase.h"

namespace chdl_internal {

template <typename T, unsigned N> 
class ch_vec : public typebase<N * T::bit_count, typename T::bitstream_type> {
public:
  using base = typebase<N * T::bit_count, typename T::bitstream_type>;
  using base::operator=;
  typedef typename base::bitstream_type bitstream_type;
  typedef ch_vec<typename T::bus_type, N> bus_type;
  
  ch_vec() {}
  
  template <typename U>
  ch_vec(const ch_vec<U, N>& rhs) {
    for (unsigned i = 0; i < N; ++i) {
      m_items[i] = rhs.m_items[i];
    }
  }
  
  ch_vec(const ch_bitbase<T::bit_count>& rhs) {
    bitstream_type data(N);
    rhs.read(data, 0, N);
    this->write(0, data, 0, N);
  }
  
  explicit ch_vec(const T& rhs) {
    for (unsigned i = 0; i < N; ++i) {
      m_items[i] = rhs;
    }
  }
  
  template <typename U>
  ch_vec(const std::initializer_list<U>& rhs) {
    CHDL_CHECK(rhs.size() == N, "initializer list size missmatch!");
    unsigned i = N;
    for (auto& x : rhs) {
      m_items[--i] = x;
    }
  }
  
  ch_vec(const base& rhs) {
    this->operator =(rhs);
  }
 
  ~ch_vec() {}
  
  template <typename U>
  ch_vec& operator=(const ch_vec<U, N>& rhs) {
    for (unsigned i = 0; i < N; ++i) {
      m_items[i] = rhs.m_items[i];
    }
    return *this;
  }
  
  template <typename U>
  ch_vec& operator=(const std::initializer_list<U>& rhs) {
    CHDL_CHECK(rhs.size() == N, "initializer list size missmatch!");
    unsigned i = N;
    for (auto& x : rhs) {
      m_items[--i] = x;
    }
    return *this;
  }

  typename std::vector<T>::reference operator[](size_t i) {
    CHDL_CHECK(i < N, "invalid subscript index");
    return m_items[i];
  }

  typename std::vector<T>::const_reference operator[](size_t i) const {
    CHDL_CHECK(i < N, "invalid subscript index");
    return m_items[i];
  }
    
  std::array<T, N>& data() {
    return m_items;
  }
  
  const std::array<T, N>& data() const {
    return m_items;
  }

protected:
  
  std::array<T, N> m_items;
  
  void read(bitstream_type& out, size_t offset, size_t length) const override {
    CHDL_CHECK(offset + length <= ch_vec::bit_count, "invalid vector read range");
    for (unsigned i = 0; length && i < N; ++i) {
      if (offset < T::bit_count) {     
        size_t len = std::min<size_t>(length, T::bit_count - offset);                
        read_data(m_items[i], out, offset, len);        
        length -= len;
        offset = T::bit_count;
      }
      offset -= T::bit_count;
    }
  }
  
  void write(size_t start, const bitstream_type& data, size_t offset, size_t length) override {
    CHDL_CHECK(start + length <= ch_vec::bit_count, "invalid vector write range");
    for (unsigned i = 0; length && i < N; ++i) {
      if (start < T::bit_count) {
        size_t len = std::min<size_t>(length, T::bit_count - start);        
        write_data(m_items[i], start, data, offset, len);
        length -= len;
        offset += len;
        start = T::bit_count;
      }
      start -= T::bit_count;
    }
  }
};

}
