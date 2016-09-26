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
  
  ch_bus(const ch_bus& rhs) : m_impl(rhs.m_impl) {
    if (m_impl)
      m_impl->add_ref();
  }
  
  ch_bus(ch_bus&& rhs) : m_impl(rhs.m_impl) {
    rhs.m_impl = nullptr;
  }

  ch_bus(const std::initializer_list<uint32_t>& value) : m_impl(nullptr) {
    this->operator =(value);
  }
  
  ch_bus(uint32_t value) : m_impl(nullptr) {
    this->operator =({value});
  }
  
  ~ch_bus() {
    if (m_impl)
      m_impl->release();
  }
  
  template <typename T>
  void write(T value) {
    this->ensureInitialized();
    m_impl->write(value);
  }
  
  template <typename T>
  T read() const {
    this->ensureInitialized();
    return m_impl->read<T>();
  }
  
  bool read(uint32_t bit) const {
    this->ensureInitialized();
    return m_impl->get_bit(bit);
  }
  
  void write(uint32_t bit, bool value) {
    this->ensureInitialized();
    return m_impl->set_bit(bit, value);
  }
  
  ch_bus& operator=(const ch_bus& rhs) {
    if (m_impl)
      m_impl->release();
     m_impl = rhs.m_impl;
     if (m_impl)
       m_impl->add_ref();
    return *this;
  }
  
  ch_bus& operator=(ch_bus&& rhs) {
    if (m_impl)
      m_impl->release();
    m_impl = rhs.m_impl;
    rhs.m_impl = nullptr;
    return *this;
  }
  
  ch_bus& operator=(const std::initializer_list<uint32_t>& value) {
    this->ensureInitialized();
    uint32_t W = N / value.size();
    if (W * value.size() != N)
        CHDL_ABORT("initializer list size mismatch");
    uint32_t i = value.size() - 1;
    for (uint32_t word : value) {
      for (uint32_t j = 0; j < W; ++j) {
        m_impl->set_bit(i * W + j, word & 0x1);
        word >>= 1;
      }
      assert(word == 0);
      --i;
    }
    return *this; 
  }
  
  ch_bus& operator=(uint32_t value) {
    return this->operator =({value});
  }
  
  explicit operator busimpl*() const { 
    this->ensureInitialized();
    return m_impl; 
  }
  
protected:
  
  void ensureInitialized() const {
    if (m_impl == nullptr)
      m_impl = new busimpl(N);
  }
  
  friend class context;
  
  mutable busimpl* m_impl;
};

class ch_signal : public ch_bus<1> {
public:  
  using base = ch_bus<1>;
  using base::base; // inherit base constructors
  
  ch_signal() {}
  
  ch_signal(bool value) : base() {
    this->operator =(value);
  }
  
  ch_signal(char value) : base() {
    this->operator =(value);
  }
  
  void write(bool value) {
    base::write(0, value);
  }
  
  bool read() const {
    return base::read(0);
  }
  
  ch_signal& operator=(bool value) {
    base::write(0, value);
    return *this;
  }
  
  ch_signal& operator=(char value) {
    base::write(0, !(value == 0 || value == '0'));
    return *this;
  }
};

}
