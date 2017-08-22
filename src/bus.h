#pragma once

#include "busbase.h"

namespace cash {
namespace detail {

template <unsigned N> 
class ch_bus : public ch_busbase<N> {
public:  
  using base = ch_busbase<N>;
  using data_type = typename base::data_type;
  using bus_type = ch_bus;
      
  ch_bus() {}
  
  ch_bus(const ch_bus& rhs) : node_(rhs.node_, N) {}

  ch_bus(ch_bus&& rhs) : node_(std::move(rhs.node_)) {}
  
  ch_bus(const ch_busbase<N>& rhs) : node_(get_node(rhs)) {}
  
  explicit ch_bus(const bitvector& rhs) : node_(rhs) {}
 
#define CH_DEF_CTOR(type) \
  explicit ch_bus(type value) : node_(bitvector(N, value)) {}
  CH_DEF_CTOR(const std::initializer_list<uint32_t>&)
  CH_DEF_CTOR(bool)
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
    node_.assign(rhs.node_, N);
    return *this;
  }

  ch_bus& operator=(ch_bus&& rhs) {
    node_ = std::move(rhs.node_);
    return *this;
  }

  ch_bus& operator=(const bitvector& rhs) {
    node_.assign(rhs);
    return *this;
  }
  
  ch_bus& operator=(const ch_busbase<N>& rhs) {
    node_.assign(get_node(rhs), N);
    return *this;
  }

#define CH_DEF_AOP(type) \
  ch_bus& operator=(type value) { \
    node_.assign(bitvector(N, value)); \
    return *this; \
  } 
  CH_DEF_AOP(const std::initializer_list<uint32_t>&)
  CH_DEF_AOP(bool)
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
    return node_.is_equal(rhs.node_, N);
  }

  bool operator<(const ch_bus& rhs) const {
    return node_.is_less(rhs.node_, N);
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
  
  #define CH_DEF_READ(type) \
  explicit operator type() const { \
    static_assert(sizeof(type) * 8 >= N, "invalid ouput data size"); \
    return bitcast<type>(node_.read(0, N)); \
  } 
  CH_DEF_READ(bool)
  CH_DEF_READ(char)
  CH_DEF_READ(int8_t)
  CH_DEF_READ(uint8_t)
  CH_DEF_READ(int16_t)
  CH_DEF_READ(uint16_t)
  CH_DEF_READ(int32_t)
  CH_DEF_READ(uint32_t)
  #undef CH_DEF_READ
  
  explicit operator uint64_t() const {
    static_assert(sizeof(uint64_t) * 8 >= N, "invalid ouput data size");
    uint64_t value = node_.read(0, N);
    if (N > 32) {
      value = ((uint64_t)node_.read(1, N) << 32) | value;
    }
    return value;
  }
  
  explicit operator int64_t() const {
    return this->operator uint64_t();
  }
  
  void read(void* out, uint32_t offset, uint32_t length) const override {
    assert(offset + length <= N);
    node_.read(reinterpret_cast<uint8_t*>(out), offset, length, N);
  }
  
  void write(const void* in, uint32_t offset, uint32_t length) override {
    assert(offset + length <= N);
    node_.write(reinterpret_cast<const uint8_t*>(in), offset, length, N);
  }

protected:
  
  void read_data(data_type& inout, size_t offset, size_t length) const override {
    node_.read_data(inout, offset, length, N);
  }
  
  void write_data(size_t dst_offset, const data_type& in, size_t src_offset, size_t src_length) override {
    node_.write_data(dst_offset, in, src_offset, src_length, N);
  }
  
  snode node_;

  friend class context;
};

#define CH_DEF_COMP_IMPL(op, type) \
  template <unsigned N> \
  bool op(const ch_busbase<N>& lhs, type rhs) { \
    return lhs.op(ch_bus<N>(rhs)); \
  } \
  template <unsigned N> \
  bool op(type lhs, const ch_busbase<N>& rhs) { \
    return ch_bus<N>(lhs).op(rhs); \
  }
#define CH_DEF_COMP(type) \
  CH_DEF_COMP_IMPL(operator==, type) \
  CH_DEF_COMP_IMPL(operator!=, type) \
  CH_DEF_COMP_IMPL(operator< , type) \
  CH_DEF_COMP_IMPL(operator> , type) \
  CH_DEF_COMP_IMPL(operator<=, type) \
  CH_DEF_COMP_IMPL(operator>=, type)
  CH_DEF_COMP(const std::initializer_list<uint32_t>&)
  CH_DEF_COMP(char)
  CH_DEF_COMP(int8_t)
  CH_DEF_COMP(uint8_t)
  CH_DEF_COMP(int16_t)
  CH_DEF_COMP(uint16_t)
  CH_DEF_COMP(int32_t)
  CH_DEF_COMP(uint32_t)
  CH_DEF_COMP(int64_t)
  CH_DEF_COMP(uint64_t)
#undef CH_DEF_COMP
#undef CH_DEF_COMP_IMPL

}
}
