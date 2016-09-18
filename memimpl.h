#pragma once

#include "nodeimpl.h"
#include "cdomain.h"

namespace chdl_internal {

/*class memimpl : public tickable, public refcounted {
public:  
  memimpl(context* ctx,
         const std::vector<node>& d,
         const std::vector<node>& da,
         const std::vector<std::vector<node>>& qa,
         const node& w, 
         bool rd_sync,
         const std::string& init_file);
  
  ~memimpl();
  
  void tick(ch_cycle t);
  void tick_next(ch_cycle t);
  
  void print(std::ostream& out) const;
  void print_vl(std::ostream& out) const;

protected:
  
  node m_w;
  std::vector<node> m_d;
  std::vector<node> m_da;
  std::vector<std::vector<node>> m_q;
  std::vector<std::vector<node>> m_qa;
  
  bool m_do_write;
  std::vector<bool> m_wrdata;
  size_t m_waddr;
  std::vector<size_t> m_raddr;
  std::vector<std::vector<bool>> m_rdval;
  std::vector<bool> m_contents;
  std::string m_init_file;
  bool m_rd_sync;
  bool m_wenable;
  
  cdomain* m_cd;
  
  friend class qnodeimpl;
  friend void memory_init(
      std::vector<std::vector<node>>& out,
      const std::vector<node>& d,
      const std::vector<node>& da,
      const std::vector<std::vector<node>>& qa,
      const node& w,
      bool rd_sync,   
      const std::string& init_file);
};

class qnodeimpl : public nodeimpl {
public:  
  qnodeimpl(context* ctx, memimpl *mem, unsigned port, unsigned idx);
  ~qnodeimpl();
  
  bool eval(ch_cycle t) override;

  void print(std::ostream& out) const override {
    if (m_port == 0 && m_idx == 0)
      m_mem->print(out);
  }

  void print_vl(std::ostream& out) const override {
    if (m_port == 0 && m_idx == 0)
      m_mem->print_vl(out);
  }

protected:
  memimpl* m_mem;
  unsigned m_port;
  unsigned m_idx;
  ch_cycle m_ctime;
  bool     m_cval;
};*/

}
