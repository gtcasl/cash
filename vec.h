#pragma once

#include "typebase.h"

namespace chdl_internal {

template <unsigned N, typename T> 
class ch_vec : public typebase<N * T::bit_count, typename T::data_type> {
public:
  using base = typebase<N * T::bit_count, typename T::data_type>;
  using base::operator=;
  typedef typename base::data_type data_type;
  
  ch_vec(): m_items(N) {}
  
  ch_vec(const ch_vec& v) {
    m_items.resize(N);
    for (unsigned i = 0; i < N; ++i) {
      m_items[i] = v[i];
    }
  }
  
  ch_vec(const T& v) {
    m_items.resize(N);
    for (unsigned i = 0; i < N; ++i) {
      m_items[i] = v;
    }
  }
       
  ch_vec(const std::initializer_list<T>& l) {
    if (l.size() != N)
      CHDL_ABORT("initializer list size missmatch!");
    m_items.resize(N);
    unsigned i = 0;
    for (auto& x : l) {
      m_items[i++] = x;
    }
  }
  
  template <typename U>  
  ch_vec(const typebase<N, U>& p) {
    m_items.resize(N);
    for (unsigned i = 0; i < N; ++i) {
      m_items[i] = p[i];
    }
  }
 
  virtual ~ch_vec() {}

  typename std::vector<T>::reference operator[](size_t i) {
    check_range(i, N);
    return m_items[i];
  }

  typename std::vector<T>::const_reference operator[](size_t i) const {
    check_range(i, N); 
    return m_items[i];
  }
    
  std::vector<T>& data() {
    return m_items;
  }
  
  const std::vector<T>& data() const {
    return m_items;
  }

protected:
  
  std::vector<T> m_items;

  void check_range(size_t i, size_t n) const { 
    if (i >= n) 
      CHDL_ABORT("invalid subscript index");        
  }
  
  void read(std::vector< partition<data_type> >& out, size_t offset, size_t length) const override {
    if (offset + length > ch_vec::bit_count) 
      CHDL_ABORT("invalid vector read range");
    for (unsigned i = 0; i < N; ++i) {
      if (length > 0 && offset <= i * T::bit_count) {
        size_t offset_ = offset; 
        if (offset != 0) {
          offset_ = offset % T::bit_count;
          offset = 0;
        }
        size_t length_ = std::min<size_t>(length, T::bit_count);
        length -= length_;
        m_items[i].read(out, offset, length_);        
      }
    }
  }
  
  void write(size_t dst_offset, const std::vector< partition<data_type> >& src, size_t src_offset, size_t src_length) override {
    if (dst_offset + src_length > ch_vec::bit_count) 
      CHDL_ABORT("invalid vector write range");
    for (unsigned i = 0; i < N; ++i) {
      if (src_length > 0 && dst_offset <= i * T::bit_count) {
        size_t dst_offset_ = dst_offset; 
        if (dst_offset != 0) {
          dst_offset_ = dst_offset % T::bit_count;
          dst_offset = 0;
        }
        size_t length_ = std::min<size_t>(src_length, T::bit_count - dst_offset_);
        src_length -= length_;
        m_items[i].write(dst_offset_, src, src_offset, length_);
        src_offset += length_;
      }
    }
  }
};

}
