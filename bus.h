#pragma once

#include "busbase.h"

namespace chdl_internal {

template <unsigned N> 
class ch_bus : public ch_busbase<N> {
public:  
  using base = ch_busbase<N>;
  using bitstream_type = typename base::bitstream_type;
  using bus_type = ch_bus;
      
  ch_bus() {}
  
  ch_bus(const ch_bus& rhs) : m_node(rhs.m_node.ensureInitialized(N)) {}
  
  ch_bus(const ch_busbase<N>& rhs) : m_node(rhs.get_node().get_impl()) {}
  
  ch_bus(const bitvector& rhs) : m_node(rhs) {
    assert(rhs.get_size() == N);
  }
 
#define CHDL_DEF_CTOR(type) \
    ch_bus(type value) : m_node(bitvector(value, N))  { \
      assert(m_node.get_size() == N); \
    }
  CHDL_DEF_CTOR(const std::initializer_list<uint32_t>&)
  CHDL_DEF_CTOR(char)
  CHDL_DEF_CTOR(int8_t)
  CHDL_DEF_CTOR(uint8_t)
  CHDL_DEF_CTOR(int16_t)
  CHDL_DEF_CTOR(uint16_t)
  CHDL_DEF_CTOR(int32_t)
  CHDL_DEF_CTOR(uint32_t)
  CHDL_DEF_CTOR(int64_t)
  CHDL_DEF_CTOR(uint64_t)
#undef CHDL_DEF_CTOR
   
  explicit ch_bus(snodeimpl* node) : m_node(node) {
    assert(m_node.get_size() == N);
  }
  
  ch_bus& operator=(const ch_bus& rhs) {
    m_node = rhs.m_node.ensureInitialized(N);
    return *this;
  }
  
  ch_bus& operator=(const ch_busbase<N>& rhs) {
    base::operator =(rhs);
    return *this;
  }
 
#define CHDL_DEF_AOP(type) \
  ch_bus& operator=(type value) { \
    m_node.assign(bitvector(value, N)); \
    assert(m_node.get_size() == N); \
    return *this; \
  } 
  CHDL_DEF_AOP(const std::initializer_list<uint32_t>&)
  CHDL_DEF_AOP(char)
  CHDL_DEF_AOP(int8_t)
  CHDL_DEF_AOP(uint8_t)
  CHDL_DEF_AOP(int16_t)
  CHDL_DEF_AOP(uint16_t)
  CHDL_DEF_AOP(int32_t)
  CHDL_DEF_AOP(uint32_t)
  CHDL_DEF_AOP(int64_t)
  CHDL_DEF_AOP(uint64_t)
#undef CHDL_DEF_AOP
  
  template <typename T>
  T read() const {  
    static_assert(sizeof(T) * 8 >= N, "invalid ouput data size");
    T value(0);    
    m_node.ensureInitialized(N);
    for (uint32_t i = 0, n = (N + 31) / 32; i < n; ++i) {      
      T part(m_node.read(i)); 
      value |= part << (i * 32);
    }
    return value;
  }
  
  template <typename T>
  void write(T value) {
    m_node.ensureInitialized(N);
    for (uint32_t i = 0, n = (N + 31) / 32; i < n; ++i) {
      m_node.write(i, value & 0xffffffff);
      value >>= ((i + 1 < n) ? 32 : (N % 32));
    }
    assert(value == 0);
  }
  
  bool operator==(const ch_bus& rhs) const {
    m_node.ensureInitialized(N);
    rhs.m_node.ensureInitialized(N);
    return (m_node == rhs.m_node);
  }
  
  bool operator<(const ch_bus& rhs) const {
    m_node.ensureInitialized(N);
    rhs.m_node.ensureInitialized(N);
    return (m_node < rhs.m_node);
  } 
  
  bool operator!=(const ch_bus& rhs) const {
    return !(*this == rhs);
  }
  
  bool operator>(const ch_bus& rhs) const {
    return (rhs < *this);
  }
  
  bool operator<=(const ch_bus& rhs) const {
    return !(*this > rhs);
  }
  
  bool operator>=(const ch_bus& rhs) const {
    return !(*this < rhs);
  }
  
  template <typename T>
  explicit operator T() const {     
    return this->read<T>();
  }
  
  explicit operator bool() const {     
    m_node.ensureInitialized(N);
    return m_node.to_bool(); 
  }

  snode get_node() const override { 
    return m_node.ensureInitialized(N);
  }  
  
protected:
  
  void read(bitstream_type& inout, size_t offset, size_t length) const override {
    m_node.read(inout, offset, length, N);
  }
  
  void write(size_t dst_offset, const bitstream_type& in, size_t src_offset, size_t src_length) override {
    m_node.write(dst_offset, in, src_offset, src_length, N);
  }
  
  snode m_node;
  
  friend class context;
};

}
