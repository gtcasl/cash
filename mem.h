#pragma once

#include "bitv.h"

namespace chdl_internal {

class memimpl;

class memory {
public:
  memory(uint32_t data_width, uint32_t addr_width, bool syncRead, bool writeEnable);
  memory(uint32_t data_width, uint32_t addr_width, bool syncRead, bool writeEnable, const std::string& init_file);
  memory(uint32_t data_width, uint32_t addr_width, bool syncRead, bool writeEnable, const std::vector<uint32_t>& init_data);
  ~memory();  
  
  lnodeimpl* read(lnodeimpl* addr) const;
  void write(lnodeimpl* addr, lnodeimpl* data, lnodeimpl* enable);
  
private:
  memimpl* m_impl;
};

template <unsigned N, unsigned A, bool SyncRead = false>
class ch_rom {
public:
    ch_rom() : m_mem(N, A, SyncRead, false) {}
  
    ch_rom(const std::string& init_file) : m_mem(N, A, SyncRead, false, init_file) {}
    
    ch_rom(const std::vector<uint32_t>& init_data) : m_mem(N, A, SyncRead, false, init_data) {}
    
    ch_bitv<N> read(const ch_bitbase<A>& addr) const {
      return ch_bitv<N>(m_mem.read(addr.get_node().get_impl()));
    }
    
    ch_bitv<N> read(const ch_bitv<A>& addr) const {
      return ch_bitv<N>(m_mem.read(addr.get_node().get_impl()));
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
      return ch_bitv<N>(m_mem.read(addr.get_node().get_impl()));
    }
    
    ch_bitv<N> read(const ch_bitv<A>& addr) const {
      return ch_bitv<N>(m_mem.read(addr.get_node().get_impl()));
    }
    
    void write(const ch_bitbase<A>& addr, const ch_bitbase<N>& data, const ch_logicbase& enable) {
      m_mem.write(addr.get_node().get_impl(), data.get_node().get_impl(), enable.get_node().get_impl());
    }
    
    void write(const ch_bitbase<A>& addr, const ch_bitbase<N>& data, const ch_logic& enable) {
      m_mem.write(addr.get_node().get_impl(), data.get_node().get_impl(), enable.get_node().get_impl());
    }
    
    void write(const ch_bitbase<A>& addr, const ch_bitv<N>& data, const ch_logicbase& enable) {
      m_mem.write(addr.get_node().get_impl(), data.get_node().get_impl(), enable.get_node().get_impl());
    }
    
    void write(const ch_bitbase<A>& addr, const ch_bitv<N>& data, const ch_logic& enable) {
      m_mem.write(addr.get_node().get_impl(), data.get_node().get_impl(), enable.get_node().get_impl());
    }
    
    void write(const ch_bitv<A>& addr, const ch_bitbase<N>& data, const ch_logicbase& enable) {
      m_mem.write(addr.get_node().get_impl(), data.get_node().get_impl(), enable.get_node().get_impl());
    }
    
    void write(const ch_bitv<A>& addr, const ch_bitbase<N>& data, const ch_logic& enable) {
      m_mem.write(addr.get_node().get_impl(), data.get_node().get_impl(), enable.get_node().get_impl());
    }
    
    void write(const ch_bitv<A>& addr, const ch_bitv<N>& data, const ch_logicbase& enable) {
      m_mem.write(addr.get_node().get_impl(), data.get_node().get_impl(), enable.get_node().get_impl());
    }
    
    void write(const ch_bitv<A>& addr, const ch_bitv<N>& data, const ch_logic& enable) {
      m_mem.write(addr.get_node().get_impl(), data.get_node().get_impl(), enable.get_node().get_impl());
    }
    
private:
    memory m_mem;
};

}
