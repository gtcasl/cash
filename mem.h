#pragma once

#include "bit.h"

namespace chdl_internal {

class memimpl;

class memory {
public:
  memory(uint32_t data_width, uint32_t addr_width, bool writeEnable);
  memory(uint32_t data_width, uint32_t addr_width, bool writeEnable, const std::string& init_file);
  memory(uint32_t data_width, uint32_t addr_width, bool writeEnable, const std::vector<uint32_t>& init_data);
  
  lnodeimpl* read(lnodeimpl* addr) const;
  void write(lnodeimpl* addr, lnodeimpl* data);
  
private:
  memimpl* m_impl;
};

template <unsigned N, unsigned A>
class ch_rom {
public:
    ch_rom() : m_mem(N, A, false) {}
  
    ch_rom(const std::string& init_file) : m_mem(N, A, false, init_file) {}
    
    ch_rom(const std::vector<uint32_t>& init_data) : m_mem(N, A, false, init_data) {}
    
    ch_rom(const std::initializer_list<uint32_t>& init_data) : m_mem(N, A, false, init_data) {}
    
    ch_bit<N> operator[](const ch_bitbase<A>& addr) const {
      return ch_bit<N>(m_mem.read(addr.get_node().get_impl()));
    }
    
    ch_bit<N> operator[](const ch_bit<A>& addr) const {
      return ch_bit<N>(m_mem.read(addr.get_node().get_impl()));
    }
    
private:
    memory m_mem;
};

template <unsigned N, unsigned A>
class ch_mem {
public:    
    class reference {
    public:    
      
      void operator=(const ch_bitbase<N>& data) {
        m_mem.write(m_addr.get_node().get_impl(), data.get_node().get_impl());
      }
      
      void operator=(const ch_bit<N>& data) {
        m_mem.write(m_addr.get_node().get_impl(), data.get_node().get_impl());
      }
      
      lnode get_node() const { 
        return this->operator ch_bit<N>().get_node();
      }
      
      operator ch_bit<N>() const {
        return ch_bit<N>(m_mem.read(m_addr.get_node().get_impl()));
      }
      
    protected:
      
      reference(memory& mem, const ch_bitbase<A>& addr) : m_mem(mem), m_addr(addr) {}
      
      memory& m_mem;
      const ch_bitbase<A>& m_addr;
      
      friend class ch_mem;
    };  
  
    ch_mem() : m_mem(N, A, true) {}
  
    ch_mem(const std::string& init_file) : m_mem(N, A, true, init_file) {}
    
    ch_mem(const std::vector<uint32_t>& init_data) : m_mem(N, A, true, init_data) {}
    
    ch_mem(const std::initializer_list<uint32_t>& init_data) : m_mem(N, A, true, init_data) {}
    
    ch_bit<N> operator[](const ch_bitbase<A>& addr) const {
      return ch_bit<N>(m_mem.read(addr.get_node().get_impl()));
    }
    
    ch_bit<N> operator[](const ch_bit<A>& addr) const {
      return ch_bit<N>(m_mem.read(addr.get_node().get_impl()));
    }
    
    reference operator[](const ch_bitbase<A>& addr) {
      return reference(m_mem, addr);
    }
    
    reference operator[](const ch_bit<A>& addr) {
      return reference(m_mem, addr);
    }
    
private:    
    memory m_mem;
};

}
