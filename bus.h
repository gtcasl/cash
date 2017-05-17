#pragma once

#include "busbase.h"

namespace cash_internal {

template <unsigned N> 
class ch_bus : public ch_busbase<N> {
public:  
  using base = ch_busbase<N>;
  using bitstream_type = typename base::bitstream_type;
  using bus_type = ch_bus;
      
  ch_bus() {}
  
  ch_bus(const ch_bus& rhs) : node_(rhs.node_.ensureInitialized(N)) {}
  
  ch_bus(const ch_busbase<N>& rhs) : node_(rhs.get_node().get_impl()) {}
  
  ch_bus(const bitvector& rhs) : node_(rhs) {
    assert(rhs.get_size() == N);
  }
  
  explicit ch_bus(bool value) : node_(bitvector(value ? 0x1 : 0x0, N)) { \
    static_assert(N == 1, "bool assignents only allowed on single-bit objects");
  }
 
#define CH_DEF_CTOR(type) \
  explicit ch_bus(type value) : node_(bitvector(value, N))  { \
    assert(node_.get_size() == N); \
  }
  CH_DEF_CTOR(const std::initializer_list<uint32_t>&)
  CH_DEF_CTOR(char)
  CH_DEF_CTOR(int8_t)
  CH_DEF_CTOR(uint8_t)
  CH_DEF_CTOR(int16_t)
  CH_DEF_CTOR(uint16_t)
  CH_DEF_CTOR(int32_t)
  CH_DEF_CTOR(uint32_t)
  CH_DEF_CTOR(int64_t)
  CH_DEF_CTOR(uint64_t)
#undef CH_DEF_CTOR
   
  explicit ch_bus(snodeimpl* node) : node_(node) {
    assert(node_.get_size() == N);
  }
  
  ch_bus& operator=(const ch_bus& rhs) {
    node_ = rhs.node_.ensureInitialized(N);
    return *this;
  }
  
  ch_bus& operator=(const ch_busbase<N>& rhs) {
    base::operator =(rhs);
    return *this;
  }
  
  ch_bus& operator=(bool value) {
    static_assert(N == 1, "bool assignents only allowed on single-bit objects");
    node_.assign(bitvector(value ? 0x1 : 0x0, N)); \
    assert(node_.get_size() == N); \
    return *this;
  } 
 
#define CH_DEF_AOP(type) \
  ch_bus& operator=(type value) { \
    node_.assign(bitvector(value, N)); \
    assert(node_.get_size() == N); \
    return *this; \
  } 
  CH_DEF_AOP(const std::initializer_list<uint32_t>&)
  CH_DEF_AOP(char)
  CH_DEF_AOP(int8_t)
  CH_DEF_AOP(uint8_t)
  CH_DEF_AOP(int16_t)
  CH_DEF_AOP(uint16_t)
  CH_DEF_AOP(int32_t)
  CH_DEF_AOP(uint32_t)
  CH_DEF_AOP(int64_t)
  CH_DEF_AOP(uint64_t)
#undef CH_DEF_AOP
  
  bool operator==(const ch_bus& rhs) const {
    node_.ensureInitialized(N);
    rhs.node_.ensureInitialized(N);
    return (node_ == rhs.node_);
  }
  
  bool operator<(const ch_bus& rhs) const {
    node_.ensureInitialized(N);
    rhs.node_.ensureInitialized(N);
    return (node_ < rhs.node_);
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
    node_.ensureInitialized(N);
    return node_.read(0) != 0;
  }
  
  explicit operator char() const {
    static_assert(sizeof(char) * 8 >= N, "invalid ouput data size");
    node_.ensureInitialized(N);
    return node_.read(0) ? '1' : '0';
  }
  
  #define CH_DEF_READ(type) \
  explicit operator type() const { \
    static_assert(sizeof(type) * 8 >= N, "invalid ouput data size"); \
    node_.ensureInitialized(N); \
    return bit_cast<type>(node_.read(0)); \
  } 
  CH_DEF_READ(int8_t)
  CH_DEF_READ(uint8_t)
  CH_DEF_READ(int16_t)
  CH_DEF_READ(uint16_t)
  CH_DEF_READ(int32_t)
  CH_DEF_READ(uint32_t)
  #undef CH_DEF_READ
  
  explicit operator uint64_t() const {
    static_assert(sizeof(uint64_t) * 8 >= N, "invalid ouput data size");
    node_.ensureInitialized(N);
    uint64_t value = node_.read(0);
    if (N > 32) {
      value = ((uint64_t)node_.read(1) << 32) | value;  
    }
    return value;
  }
  
  explicit operator int64_t() const {
    return this->operator uint64_t();
  }
  
  void read(void* out, uint32_t sizeInBytes) const override {  
    assert(sizeInBytes * 8 >= N);
    node_.ensureInitialized(N);
    node_.read(reinterpret_cast<uint8_t*>(out), sizeInBytes);
  }
  
  void write(const void* in, uint32_t sizeInBytes) override {
    assert(sizeInBytes * 8 >= N);
    node_.ensureInitialized(N);
    node_.write(reinterpret_cast<const uint8_t*>(in), sizeInBytes);
  }

  snode get_node() const override { 
    return node_.ensureInitialized(N);
  }  
  
protected:
  
  void read(bitstream_type& inout, size_t offset, size_t length) const override {
    node_.read(inout, offset, length, N);
  }
  
  void write(size_t dst_offset, const bitstream_type& in, size_t src_offset, size_t src_length) override {
    node_.write(dst_offset, in, src_offset, src_length, N);
  }
  
  snode node_;
  
  friend class context;
};

}
