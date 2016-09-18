#pragma once

#include "busimpl.h"

namespace chdl_internal {

template <unsigned N> class ch_bitv;

template <unsigned N> 
class ch_bus {
public:  
  typedef ch_bus     bus_type;
  typedef ch_bitv<N> logic_type;
      
  ch_bus() : m_impl(nullptr) {}
  
  ch_bus(const ch_bus& b) : m_impl(b.m_impl){
    if (m_impl)
      m_impl->add_ref();
  }

  ch_bus(const std::initializer_list<uint32_t>& value) {
    uint32_t W = N / value.size();
    if (W * value.size() != N)
        CHDL_ABORT("initializer list size mismatch");
    uint32_t i = value.size() - 1;
    m_impl = new busimpl(N);
    for (uint32_t word : value) {
      for (uint32_t j = 0; j < W; ++j) {
        m_impl->set_bit(i * W + j, word & 0x1);
        word >>= 1;
      }
      assert(word == 0);
      --i;
    }
  }
  
  ch_bus(uint32_t value) : ch_bus({value}) {}   
  
  ~ch_bus() {
    if (m_impl)
      m_impl->release();
  }
  
  template <typename T>
  void write(T value) {
    this->ensureInitialized();
    for (uint32_t i = 0; i < N; ++i) {
      m_impl->set_bit(i, value & 0x1);
      value >>= 1;
    }
    assert(value == 0);
  }
  
  template <typename T>
  T read() const {
   this->ensureInitialized();
    T value = 0;
    for (uint32_t i = 0; i < N; ++i) {
      T sign = m_impl->get_bit(i) ? 1 : 0;
      value |= sign << i;
    }
    return value;
  }
  
protected:
  
  void ensureInitialized() const {
    if (m_impl == nullptr)
      m_impl = new busimpl(N);
  }
  
  template <unsigned N_> 
  friend busimpl* get_impl(const ch_bus<N_>& bus);
  
  friend class context;
  friend class ch_simulator;
  
  mutable busimpl* m_impl;
};

template <unsigned N> 
busimpl* get_impl(const ch_bus<N>& bus) {
  bus.ensureInitialized();
  return bus.m_impl;
}


class ch_signal : public ch_bus<1> {
public:  
  using base = ch_bus<1>;
  
  ch_signal() {}
  
  ch_signal(bool value) : base(value ? 1 : 0) {}
  
  ch_signal(char value) : base((value == 0 || value == '0') ? 0 : 1) {}
  
  void write(bool value) {
    base::write<uint32_t>(value ? 1 : 0);
  }
  
  bool read() const {
    return base::read<uint32_t>();
  }
};

}
