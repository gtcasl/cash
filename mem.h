#pragma once

#include "bit.h"

namespace cash {
namespace detail {

class memimpl;

class memory {
public:
  memory(uint32_t data_width, uint32_t addr_width, bool writeEnable);
  memory(uint32_t data_width, uint32_t addr_width, bool writeEnable, const std::string& init_file);
  memory(uint32_t data_width, uint32_t addr_width, bool writeEnable, const std::vector<uint32_t>& init_data);
  
  lnodeimpl* read(lnodeimpl* addr) const;
  void write(lnodeimpl* addr, lnodeimpl* data);
  
private:
  memimpl* impl_;
};

template <unsigned N, unsigned A>
class ch_rom {
public:
    ch_rom() : mem_(N, A, false) {}
  
    ch_rom(const std::string& init_file) : mem_(N, A, false, init_file) {}
    
    ch_rom(const std::vector<uint32_t>& init_data) : mem_(N, A, false, init_data) {}
    
    ch_rom(const std::initializer_list<uint32_t>& init_data) : mem_(N, A, false, init_data) {}
    
    ch_bit<N> operator[](const ch_bitbase<A>& addr) const {
      return ch_bit<N>(mem_.read(get_node(addr).get_impl()));
    }
    
    ch_bit<N> operator[](const ch_bit<A>& addr) const {
      return ch_bit<N>(mem_.read(get_node(addr).get_impl()));
    }
    
private:
    memory mem_;
};

template <unsigned N, unsigned A>
class ch_mem {
public:    
    class reference {
    public:    
      
      void operator=(const ch_bitbase<N>& data) {
        mem_.write(get_node(addr_).get_impl(), get_node(data).get_impl());
      }
      
      void operator=(const ch_bit<N>& data) {
        mem_.write(get_node(addr_).get_impl(), get_node(data).get_impl());
      }
      
      operator ch_bit<N>() const {
        return ch_bit<N>(mem_.read(get_node(addr_).get_impl()));
      }
      
    protected:
      
      reference(memory& mem, const ch_bitbase<A>& addr) : mem_(mem), addr_(addr) {}
      
      memory& mem_;
      const ch_bitbase<A>& addr_;
      
      friend class ch_mem;
    };  
  
    ch_mem() : mem_(N, A, true) {}
  
    ch_mem(const std::string& init_file) : mem_(N, A, true, init_file) {}
    
    ch_mem(const std::vector<uint32_t>& init_data) : mem_(N, A, true, init_data) {}
    
    ch_mem(const std::initializer_list<uint32_t>& init_data) : mem_(N, A, true, init_data) {}
    
    ch_bit<N> operator[](const ch_bitbase<A>& addr) const {
      return ch_bit<N>(mem_.read(get_node(addr).get_impl()));
    }
    
    ch_bit<N> operator[](const ch_bit<A>& addr) const {
      return ch_bit<N>(mem_.read(get_node(addr).get_impl()));
    }
    
    reference operator[](const ch_bitbase<A>& addr) {
      return reference(mem_, addr);
    }
    
    reference operator[](const ch_bit<A>& addr) {
      return reference(mem_, addr);
    }
    
private:    
    memory mem_;
};

}
}
