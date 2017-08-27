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
  
  ch_bus(const bitvector& rhs) : node_(rhs) {}
 
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
  
#define CH_DEF_CAST(type) \
  explicit operator type() const { \
    return static_cast<type>(node_.get_value()); \
  } 
  CH_DEF_CAST(bool)
  CH_DEF_CAST(char)
  CH_DEF_CAST(int8_t)
  CH_DEF_CAST(uint8_t)
  CH_DEF_CAST(int16_t)
  CH_DEF_CAST(uint16_t)
  CH_DEF_CAST(int32_t)
  CH_DEF_CAST(uint32_t)
  CH_DEF_CAST(int64_t)
  CH_DEF_CAST(uint64_t)
#undef CH_DEF_CAST
  
  void read(void* out, uint32_t offset, uint32_t length) const {
    assert(offset + length <= N);
    node_.read(reinterpret_cast<uint8_t*>(out), offset, length, N);
  }
  
  void write(const void* in, uint32_t offset, uint32_t length) {
    assert(offset + length <= N);
    node_.write(reinterpret_cast<const uint8_t*>(in), offset, length, N);
  }

protected:

  ch_bus(snodeimpl* node) : node_(node) {
    assert(node_.get_size() == N);
  }
  
  void read_data(data_type& inout, size_t offset, size_t length) const override {
    node_.read_data(inout, offset, length, N);
  }
  
  void write_data(size_t dst_offset, const data_type& in, size_t src_offset, size_t src_length) override {
    node_.write_data(dst_offset, in, src_offset, src_length, N);
  }
  
  snode node_;

  template <unsigned M> friend ch_bus<M> make_bus(snodeimpl* node);
};

template <unsigned N>
ch_bus<N> make_bus(snodeimpl* node) {
  return ch_bus<N>(node);
}

#define CH_DEF_COMP_IMPL(op, type) \
  template <unsigned N> \
  bool op(const ch_busbase<N>& lhs, type rhs) { \
    return op(lhs, ch_bus<N>(rhs)); \
  } \
  template <unsigned N> \
  bool op(type lhs, const ch_busbase<N>& rhs) { \
    return op(ch_bus<N>(lhs), rhs); \
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
