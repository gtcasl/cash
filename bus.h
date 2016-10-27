#pragma once

#include "busbase.h"
#include "bitv.h"

namespace chdl_internal {

template <unsigned N> 
class ch_bus : public ch_busbase<N> {
public:  
  using base = ch_busbase<N>;
  typedef typename base::data_type data_type;
  typedef ch_bus bus_type;
      
  ch_bus() {}
  
  ch_bus(const ch_bus& rhs) : m_node(rhs.m_node, N) {}
  
  ch_bus(const ch_busbase<N>& rhs) : m_node(rhs, N) {}
  
  ch_bus(const std::string& value) : m_node(value) {
    assert(m_node.get_size() == N);
  }
  
  ch_bus(const std::initializer_list<uint32_t>& value) : m_node(value, N) {}
  
  ch_bus(uint32_t value) : m_node({value}, N) {}
  
  ch_bus(char value) : m_node({to_value<N>(value)}, N) {} 
  
#define CHDL_DEF_CTOR(type) \
    ch_bus(type value) : m_node({bit_cast<uint32_t>(value)}, N) {}
  CHDL_DEF_CTOR(int8_t)
  CHDL_DEF_CTOR(uint8_t)
  CHDL_DEF_CTOR(int16_t)
  CHDL_DEF_CTOR(uint16_t)
  CHDL_DEF_CTOR(int32_t)
  CHDL_DEF_CTOR(int64_t)
  CHDL_DEF_CTOR(uint64_t)
#undef CHDL_DEF_CTOR
  
  explicit ch_bus(const snode& node) : m_node(node, N) {}
  
  ch_bus& operator=(const ch_bus& rhs) {
    m_node = rhs.m_node;
    return *this;
  }
  
  ch_bus& operator=(const ch_busbase<N>& rhs) {
    base::operator =(rhs);
    return *this;
  }
  
  ch_bus& operator=(const std::initializer_list<uint32_t>& value) {
    m_node.assign(value, N);
    return *this;
  }
  
  ch_bus& operator=(uint32_t value) {
    m_node.assign({value}, N);
    return *this;
  }
  
  ch_bus& operator=(char value) {
    m_node.assign({to_value<N>(value)}, N);
    return *this;
  }
  
#define CHDL_DEF_AOP(type) \
  ch_bus& operator=(type value) { \
    m_node.assign({bit_cast<uint32_t>(value)}, N); \
    return *this; \
  } 
  CHDL_DEF_AOP(int8_t)
  CHDL_DEF_AOP(uint8_t)
  CHDL_DEF_AOP(int16_t)
  CHDL_DEF_AOP(uint16_t)
  CHDL_DEF_AOP(int32_t)
  CHDL_DEF_AOP(int64_t)
  CHDL_DEF_AOP(uint64_t)
#undef CHDL_DEF_AOP
  
  uint32_t read(uint32_t idx) const {
    return m_node.read(idx, N);
  }
  
  void write(uint32_t idx, uint32_t value) {
    m_node.write(idx, value, N);
  }
  
  template <typename T>
  T read() const {  
    static_assert(sizeof(T) * 4 >= N, "invalid ouput data size");
    T value(0);    
    for (uint32_t i = 0, n = (N + 31) / 32; i < n; ++i) {      
      T part(m_node.read(i, N)); 
      value |= part << (i * 32);
    }
    return value;
  }
  
  template <typename T>
  void write(T value) {
    for (uint32_t i = 0, n = (N + 31) / 32; i < n; ++i) {
      m_node.write(i, value & 0xffffffff, N);
      value >>= ((i + 1 < n) ? 32 : (N % 32));
    }
    assert(value == 0);
  }
  
  bool read() const {
    static_assert(N == 1, "invalid object size");
    return m_node.read(0, N) != 0x0;
  }
  
  void write(char value) {
    static_assert(N == 1, "invalid object size");
    m_node.write(0, value != 0 && value != '0', N);
  }
  
  explicit operator bool() const {     
    return m_node.to_bool(N); 
  }
  
  operator snode() const { 
    m_node.ensureInitialized(N);
    return m_node; 
  }
  
protected:
  
  void read(std::vector< partition<data_type> >& out, size_t offset, size_t length) const override {
    m_node.read(out, offset, length, N);
  }
  
  void write(size_t dst_offset, const std::vector< partition<data_type> >& data, size_t src_offset, size_t src_length) override {
    m_node.write(dst_offset, data, src_offset, src_length, N);
  }
  
  snode m_node;
  
  friend class context;
};

}
