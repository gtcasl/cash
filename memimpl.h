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
  void write(lnodeimpl* addr, lnodeimpl* data);  
  
  void tick(ch_cycle t) override;
  void tick_next(ch_cycle t) override;
  
  void print(std::ostream& out) const;
  void print_vl(std::ostream& out) const;

protected:
  
  void load_data(const std::function<bool(uint32_t* out)>& getdata);
  
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
  
  lnodeimpl* get_addr() const {
    return m_srcs[m_addr_id].get_impl();
  }
  
  void write(lnodeimpl* data);  
  
  void tick(ch_cycle t);
  void tick_next(ch_cycle t);
  
  const bitvector& eval(ch_cycle t) override;
  void print_vl(std::ostream& out) const override;

protected:
  
  memimpl*  m_mem;
  
  bitvector m_q_next;
  uint32_t  m_a_next;
  
  int       m_addr_id;
  int       m_clk_id;
  int       m_wdata_id;
  
  ch_cycle  m_ctime;
  
  friend class memimpl;
};

}
