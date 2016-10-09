#pragma once

#include "bitv.h"

namespace chdl_internal {

class memimpl_ptr;

class memory {
public:
  memory(uint32_t data_width, uint32_t addr_width, bool syncRead, bool writeEnable);
  memory(uint32_t data_width, uint32_t addr_width, bool syncRead, bool writeEnable, const std::string& init_file);
  memory(uint32_t data_width, uint32_t addr_width, bool syncRead, bool writeEnable, const std::vector<uint32_t>& init_data);
  ~memory();  
  
  lnode read(const lnode& addr) const;
  void write(const lnode& addr, const lnode& value, const lnode& enable);
  
private:
  memimpl_ptr m_impl;
};

template <unsigned N, unsigned A, bool SyncRead = false>
class ch_rom {
public:
    ch_rom() : m_mem(N, A, SyncRead, false) {}
  
    ch_rom(const std::string& init_file) : m_mem(N, A, SyncRead, false, init_file) {}
    
    ch_rom(const std::vector<uint32_t>& init_data) : m_mem(N, A, SyncRead, false, init_data) {}
    
    ch_bitv<N> read(const ch_bitbase<A>& addr) const {
      return ch_bitv<N>(m_mem.read(addr));
    }
    
    ch_bitv<N> read(const ch_bitv<A>& addr) const {
      return ch_bitv<N>(m_mem.read(addr));
    }
    
private:
    memory m_mem;
};

template <unsigned N, unsigned A, bool SyncRead = false>
class ch_mem {
public:  
    ch_mem() : m_mem(N, A, SyncRead, true) {}
  
    ch_mem(const std::string& init_file) : m_mem(N, A, SyncRead, true, init_file) {}
    
    ch_mem(const std::vector<uint32_t>& init_data) : m_mem(N, A, SyncRead, true, init_data) {}
    
    ch_bitv<N> read(const ch_bitbase<A>& addr) const {
      return ch_bitv<N>(m_mem.read(addr));
    }
    
    ch_bitv<N> read(const ch_bitv<A>& addr) const {
      return ch_bitv<N>(m_mem.read(addr));
    }
    
    void write(const ch_bitbase<A>& addr, const ch_bitbase<N>& value, const ch_logicbase& enable) {
      m_mem.write(addr, value, enable);
    }
    
    void write(const ch_bitv<A>& addr, const ch_bitbase<N>& value, const ch_logicbase& enable) {
      m_mem.write(addr, value, enable);
    }
    
    void write(const ch_bitbase<A>& addr, const ch_bitv<N>& value, const ch_logicbase& enable) {
      m_mem.write(addr, value, enable);
    }
    
    void write(const ch_bitv<A>& addr, const ch_bitv<N>& value, const ch_logicbase& enable) {
      m_mem.write(addr, value, enable);
    }
    
    void write(const ch_bitv<A>& addr, const ch_bitbase<N>& value, const ch_logic& enable) {
      m_mem.write(addr, value, enable);
    }
    
    void write(const ch_bitbase<A>& addr, const ch_bitv<N>& value, const ch_logic& enable) {
      m_mem.write(addr, value, enable);
    }
    
    void write(const ch_bitv<A>& addr, const ch_bitv<N>& value, const ch_logic& enable) {
      m_mem.write(addr, value, enable);
    }
    
private:
    memory m_mem;
};

}
