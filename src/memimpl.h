#pragma once

#include "ioimpl.h"
#include "cdomain.h"

namespace cash {
namespace internal {

class memportimpl;

class memimpl : public tickable, public ioimpl {
public:  
  memimpl(context* ctx, uint32_t data_width, uint32_t addr_width, bool write_enable);  
  ~memimpl();

  void load(const std::string& file);
  void load(const std::vector<uint8_t>& data);
  
  memportimpl* read(const lnode& addr);
  void write(const lnode& addr, const lnode& data);
  
  void tick(ch_cycle t) override;
  void tick_next(ch_cycle t) override;
  
  const bitvector& eval(ch_cycle t) override;  
  void print(std::ostream& out, uint32_t level) const override;
  void print_vl(std::ostream& out) const override;
  
  uint32_t get_total_size() const {
    return value_.get_size();
  }

protected:
  
  void load_data(const std::function<bool(uint8_t* out)>& getdata);
  
  memportimpl* get_port(const lnode& addr, bool writing);
  
  uint32_t data_width_;
  uint32_t addr_width_;
  uint32_t ports_offset_;
  cdomain* cd_;
  
  friend class memportimpl;
};

class memportimpl : public ioimpl {
public:  
  memportimpl(memimpl* mem, const lnode& addr);
  
  const lnode& get_addr() const {
    return srcs_[addr_id_];
  }
  
  void write(const lnode& data);
  
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
