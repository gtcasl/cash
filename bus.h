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
  
  explicit ch_bus(bool value) : m_node(bitvector(value ? 0x1 : 0x0, N)) { \
    static_assert(N == 1, "bool assignents only allowed on single-bit objects");
  }
 
#define CHDL_DEF_CTOR(type) \
  explicit ch_bus(type value) : m_node(bitvector(value, N))  { \
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
  
  ch_bus& operator=(bool value) {
    static_assert(N == 1, "bool assignents only allowed on single-bit objects");
    m_node.assign(bitvector(value ? 0x1 : 0x0, N)); \
    assert(m_node.get_size() == N); \
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
    
  explicit operator bool() const {     
    static_assert(N == 1, "bool assignents only allowed on single-bit objects");
    m_node.ensureInitialized(N);
    return m_node.read(0) != 0;
  }
  
  explicit operator char() const {
    static_assert(sizeof(char) * 8 >= N, "invalid ouput data size");
    m_node.ensureInitialized(N);
    return m_node.read(0) ? '1' : '0';
  }
  
  #define CHDL_DEF_READ(type) \
  explicit operator type() const { \
    static_assert(sizeof(type) * 8 >= N, "invalid ouput data size"); \
    m_node.ensureInitialized(N); \
    return bit_cast<type>(m_node.read(0)); \
  } 
  CHDL_DEF_READ(int8_t)
  CHDL_DEF_READ(uint8_t)
  CHDL_DEF_READ(int16_t)
  CHDL_DEF_READ(uint16_t)
  CHDL_DEF_READ(int32_t)
  CHDL_DEF_READ(uint32_t)
  #undef CHDL_DEF_READ
  
  explicit operator uint64_t() const {
    static_assert(sizeof(uint64_t) * 8 >= N, "invalid ouput data size");
    m_node.ensureInitialized(N);
    uint64_t value = m_node.read(0);
    if (N > 32) {
      value = ((uint64_t)m_node.read(1) << 32) | value;  
    }
    return value;
  }
  
  explicit operator int64_t() const {
    return this->operator uint64_t();
  }
  
  void read(void* out, uint32_t sizeInBytes) const {  
    assert(sizeInBytes * 8 >= N);
    m_node.ensureInitialized(N);
    m_node.readBytes(reinterpret_cast<uint8_t*>(out), sizeInBytes);
  }
  
  void write(const void* in, uint32_t sizeInBytes) {
    assert(sizeInBytes * 8 >= N);
    m_node.ensureInitialized(N);
    m_node.writeBytes(reinterpret_cast<const uint8_t*>(in), sizeInBytes);
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
