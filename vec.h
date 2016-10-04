#pragma once

#include "typebase.h"

namespace chdl_internal {

template <typename T, unsigned N> 
class ch_vec : public typebase<N * T::bit_count, typename T::data_type> {
public:
  using base = typebase<N * T::bit_count, typename T::data_type>;
  using base::operator=;
  typedef typename base::data_type data_type;
  typedef ch_vec<typename T::logic_type, N> logic_type;
  typedef ch_vec<typename T::bus_type, N> bus_type;
  
  ch_vec() {}
  
  ch_vec(const ch_vec& v) {
    for (unsigned i = 0; i < N; ++i) {
      m_items[i] = v[i];
    }
  }
  
  ch_vec(const T& v) {
    for (unsigned i = 0; i < N; ++i) {
      m_items[i] = v;
    }
  }
       
  ch_vec(const std::initializer_list<T>& rhs) {
    if (rhs.size() != N)
      CHDL_ABORT("initializer list size missmatch!");
    unsigned i = 0;
    for (auto& x : rhs) {
      m_items[i++] = x;
    }
  }
  
  ch_vec(const base& rhs) {
    this->operator =(rhs);
  }
 
  virtual ~ch_vec() {}

  typename std::vector<T>::reference operator[](size_t i) {
    if (i >= N) 
      CHDL_ABORT("invalid subscript index");
    return m_items[i];
  }

  typename std::vector<T>::const_reference operator[](size_t i) const {
    if (i >= N) 
      CHDL_ABORT("invalid subscript index");
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
  
  void read(std::vector< partition<data_type> >& out, size_t offset, size_t length) const override {
    if (offset + length > ch_vec::bit_count) 
      CHDL_ABORT("invalid vector read range");
    for (unsigned i = 0; i < N && length > 0; ++i) {
      if (offset < (i + 1) * T::bit_count) {
        size_t off = offset % T::bit_count;        
        size_t len = std::min<size_t>(length, T::bit_count - off);                
        read_data(m_items[i], out, off, len);        
        length -= len;
        offset = 0;
      }
    }
  }
  
  void write(size_t dst_offset, const std::vector< partition<data_type> >& src, size_t src_offset, size_t src_length) override {
    if (dst_offset + src_length > ch_vec::bit_count) 
      CHDL_ABORT("invalid vector write range");
    for (unsigned i = 0; i < N && src_length > 0; ++i) {
      if (dst_offset < (i + 1) * T::bit_count) {
        size_t off = dst_offset % T::bit_count;
        size_t len = std::min<size_t>(src_length, T::bit_count - off);        
        write_data(m_items[i], off, src, src_offset, len);
        src_length -= len;
        src_offset += len;
        dst_offset = 0;
      }
    }
  }
};

}
