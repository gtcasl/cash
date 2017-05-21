#pragma once

#include "lnodeimpl.h"
#include "cdomain.h"

namespace cash {
namespace detail {

class memportimpl;

class memimpl : public tickable, public lnodeimpl {
public:  
  memimpl(context* ctx, uint32_t data_width, uint32_t addr_width, bool write_enable);  
  memimpl(context* ctx, uint32_t data_width, uint32_t addr_width, bool write_enable, const std::string& init_file);  
  memimpl(context* ctx, uint32_t data_width, uint32_t addr_width, bool write_enable, const std::vector<uint32_t>& init_data);
  ~memimpl();
  
  memportimpl* read(lnodeimpl* addr);
  void write(lnodeimpl* addr, lnodeimpl* data);  
  
  void tick(ch_cycle t) override;
  void tick_next(ch_cycle t) override;
  
  const bitvector& eval(ch_cycle t) override;  
  void print_vl(std::ostream& out) const override;
  
  uint32_t get_total_size() const {
    return content_.size() * content_[0].get_size();
  }

protected:
  
  void load_data(const std::function<bool(uint32_t* out)>& getdata);
  
  memportimpl* get_port(lnodeimpl* addr, bool writing);
  
  std::vector<bitvector> content_;
  uint32_t ports_offset_;
  cdomain* cd_;
  
  friend class memportimpl;
};

class memportimpl : public lnodeimpl {
public:  
  memportimpl(memimpl* mem, lnodeimpl* addr);
  
  lnodeimpl* get_addr() const {
    return srcs_[addr_id_].get_impl();
  }
  
  void write(lnodeimpl* data);  
  
  void tick(ch_cycle t);
  void tick_next(ch_cycle t);
  
  const bitvector& eval(ch_cycle t) override;
  void print_vl(std::ostream& out) const override;

protected:
    
  bitvector q_next_;
  uint32_t  a_next_;
  
  int       addr_id_;
  int       wdata_id_;
  
  ch_cycle  ctime_;
  
  friend class memimpl;
};

}
}
