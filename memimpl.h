#pragma once

#include "lnodeimpl.h"
#include "cdomain.h"

namespace chdl_internal {

class memportimpl;

class memimpl : public tickable, public refcounted {
public:  
  memimpl(uint32_t data_width, uint32_t addr_width, bool sync_read, bool write_enable);  
  memimpl(uint32_t data_width, uint32_t addr_width, bool sync_read, bool write_enable, const std::string& init_file);  
  memimpl(uint32_t data_width, uint32_t addr_width, bool sync_read, bool write_enable, const std::vector<uint32_t>& init_data);
  ~memimpl();
  
  memportimpl* read(lnodeimpl* addr);
  void write(lnodeimpl* addr, lnodeimpl* data, lnodeimpl* enable);  
  
  void tick(ch_cycle t) override;
  void tick_next(ch_cycle t) override;
  
  void print(std::ostream& out) const;
  void print_vl(std::ostream& out) const;

protected:
  
  memportimpl* get_port(lnodeimpl* addr);
  
  std::vector<memportimpl*> m_ports;
  std::vector<bitvector> m_content;
  bool     m_syncRead;
  bool     m_writeEnable;   
  cdomain* m_cd;
  
  friend class memportimpl;
};

class memportimpl : public lnodeimpl {
public:  
  memportimpl(memimpl* mem, lnodeimpl* addr);
  ~memportimpl();
  
  bool operator==(lnodeimpl* addr) const {
    return (m_srcs[m_addr_id].get_impl() == addr);
  }
  
  void write(lnodeimpl* data, lnodeimpl* enable);  
  
  void tick(ch_cycle t);
  void tick_next(ch_cycle t);
  
  const bitvector& eval(ch_cycle t) override;
  void print_vl(std::ostream& out) const override;

protected:
  
  memimpl*  m_mem;
  bool      m_writeEnable;
  
  bitvector m_rddata;
  bitvector m_wrdata;
  uint32_t  m_addr;
  bool      m_do_write;  
  
  int       m_addr_id;
  int       m_clk_id;
  int       m_wdata_id;
  int       m_wenable_id;
  
  ch_cycle  m_ctime;
  
  friend class memimpl;
};

}
