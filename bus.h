#pragma once

#include "busbase.h"
#include "bitv.h"

namespace chdl_internal {

template <unsigned N> 
class ch_bus : public ch_busbase<N> {
public:  
  using base = ch_busbase<N>;
  using base::operator=;
  typedef typename base::data_type data_type;
  typedef ch_bus     bus_type;
  typedef ch_bitv<N> logic_type;
      
  ch_bus() {}
  
  ch_bus(const ch_bus& rhs) : m_node(rhs.m_node, N) {}
  
  ch_bus(const ch_busbase<N>& rhs) {
    this->operator =(rhs);
  }
  
  ch_bus(int value) : m_node({(uint32_t)value}, N) {}

  ch_bus(const std::initializer_list<uint32_t>& value) : m_node(value, N) {} 
  
  explicit ch_bus(const snode& node) : m_node(node, N) {}
  
  base& operator=(const std::initializer_list<uint32_t>& value) {
    m_node.assign(value, N);
    return *this;
  }
  
  uint32_t read(uint32_t idx) const {
    m_node.ensureInitialized(N);
    return m_node.read(idx);
  }
  
  void write(uint32_t idx, uint32_t value) {
    m_node.ensureInitialized(N);
    m_node.write(idx, value);
  }
  
  template <typename T>
  T read() const {  
    static_assert(sizeof(T) * 4 >= N, "invalid ouput data size");
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
    static_assert(sizeof(T) * 4 <= N, "invalid input data size");
    m_node.ensureInitialized(N);
    for (uint32_t i = 0, n = (N + 31) / 32; i < n; ++i) {
      m_node.write(i, value & 0xffffffff);
      value >>= ((i + 1 < n) ? 32 : (N % 32));
    }
    assert(value == 0);
  }
  
  operator const snode&() const { 
    return m_node; 
  }
  
  operator snode&() { 
    return m_node; 
  }
  
protected:
  
  void read(std::vector< partition<data_type> >& out, size_t offset, size_t length) const override {
    m_node.ensureInitialized(N);
    out.push_back({m_node, offset, length});
  }
  
  void write(size_t dst_offset, const std::vector< partition<data_type> >& src, size_t src_offset, size_t src_length) override {
    for (auto& p : src) {
      if (src_offset < p.length) {
        size_t len = std::min(p.length - src_offset, src_length);
        m_node.assign(dst_offset, p.data, p.offset + src_offset, len, 1);         
        src_length -= len;
        if (src_length == 0)
          return;
        dst_offset += len;                
        src_offset = p.length;
      }
      src_offset -= p.length;
    }
  }
  
  snode m_node;
  
  friend class context;
};

/*template <>
class ch_bus<1> : public ch_busbase<1> {
public:  
  using base = ch_busbase<1>;
  using base::operator=;
  typedef typename base::data_type data_type;
  typedef ch_bus<1> bus_type;
  typedef ch_logic  logic_type;
  
  ch_bus() {}
  
  ch_bus(const ch_bus& rhs) : m_node(rhs.m_node, 1) {}
  
  ch_bus(const ch_busbase<1>& rhs) {
    this->operator =(rhs);
  }
  
  ch_bus(int value) : m_node({(uint32_t)value}, 1) {}
  
  explicit ch_bus(const snode& node) : m_node(node, 1) {}
  
  ch_bus(const std::initializer_list<uint32_t>& value) : m_node(value, 1) {} 
  
  ch_bus(bool value) : base() {
    this->write(value);
  }
  
  ch_bus(char value) : base() {
    this->write(value);
  }
  
  base& operator=(const std::initializer_list<uint32_t>& value) {
    m_node.assign(value, 1);
    return *this;
  }
  
  ch_bus& operator=(bool value) {
    this->write(value);
    return *this;
  }
  
  ch_bus& operator=(char value) {
    this->write(value);
    return *this;
  }  
  
  uint32_t read(uint32_t idx) const {
    m_node.ensureInitialized(1);
    return m_node.read(idx);
  }
  
  void write(uint32_t idx, uint32_t value) {
    m_node.ensureInitialized(1);
    m_node.write(idx, value);
  }
  
  template <typename T>
  T read() const {    
    m_node.ensureInitialized(1);
    T value(m_node.read(0));
    return value;
  }
  
  template <typename T>
  void write(T value) {
    m_node.ensureInitialized(1);
    m_node.write(0, value & 0x1);
    value >>= 1;
    assert(value == 0);
  }
  
  bool read() const {
    return m_node.read(0) != 0;
  }
  
  void write(bool value) {
    m_node.write(0, value ? 0x1 : 0x0);
  }
  
  void write(char value) {
    this->write(value != '0');
  }
  
  operator const snode&() const { 
    return m_node; 
  }
  
  operator snode&() { 
    return m_node; 
  }
  
protected:
  
  void read(std::vector< partition<data_type> >& out, size_t offset, size_t length) const override {
    assert(length == 1);
    m_node.ensureInitialized(1);
    out.push_back({m_node, offset, 1});
  }
  
  void write(size_t dst_offset, const std::vector< partition<data_type> >& src, size_t src_offset, size_t src_length) override {
    assert(src_length == 1);
    for (auto& p : src) {
      if (src_offset < p.length) {
        m_node.assign(dst_offset, p.data, p.offset + src_offset, 1, 1);         
        return;
      }
      src_offset -= p.length;
    }
  }
  
  snode m_node;
  
  friend class context;
};*/

}
