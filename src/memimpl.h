#pragma once

#include "ioimpl.h"
#include "cdomain.h"

namespace ch {
namespace internal {

class memportimpl;

class memimpl : public tickable, public ioimpl {
public:
  uint32_t get_total_size() const {
    return value_.get_size();
  }

  uint32_t get_data_width() const {
    return data_width_;
  }

  uint32_t get_addr_width() {
    return addr_width_;
  }

  bool has_initdata() const {
    return has_initdata_;
  }

  bool is_write_enable() const {
    return (wr_ports_offset_ != 0);
  }

  const std::vector<lnode>& get_ports() const {
    return ports_;
  }

  cdomain* get_cd() const {
    return cd_;
  }

  void load(const std::string& init_file);

  void load(const std::vector<uint8_t>& init_data);

  lnode& get_port(const lnode& addr);
  
  void tick(ch_tick t) override;

  void tick_next(ch_tick t) override;
  
  const bitvector& eval(ch_tick t) override;  

  void print(std::ostream& out, uint32_t level) const override;

protected:

  memimpl(context* ctx,
          uint32_t data_width,
          uint32_t addr_width,
          bool write_enable);

  ~memimpl();

  void load_data(const std::function<bool(uint8_t* out)>& getdata);
  
  std::vector<lnode> ports_;
  uint32_t data_width_;
  uint32_t addr_width_;
  uint32_t wr_ports_offset_;
  cdomain* cd_;
  bool has_initdata_;
  
  friend class memportimpl;
  friend class context;
};

class memportimpl : public ioimpl {
public:  
  const lnode& get_mem() const {
    return srcs_[mem_idx_];
  }

  const lnode& get_addr() const {
    return srcs_[addr_idx_];
  }

  const lnode& get_wdata() const {
    return srcs_[wdata_idx_];
  }

  bool has_wdata() const {
    return (wdata_idx_ != -1);
  }
  
  void write(const lnode& data);

  void tick(ch_tick t);
  void tick_next(ch_tick t);
  
  const bitvector& eval(ch_tick t) override;

protected:
  memportimpl(context* ctx, memimpl* mem, const lnode& addr);
  ~memportimpl() {}
    
  bitvector q_next_;
  uint32_t  a_next_;
  
  int mem_idx_;
  int addr_idx_;
  int wdata_idx_;
  
  ch_tick tick_;
  
  friend class memimpl;
  friend class context;
};

}
}
