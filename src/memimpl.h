#pragma once

#include "ioimpl.h"
#include "cdomain.h"

namespace ch {
namespace internal {

class memportimpl;

class memimpl : public tickable, public ioimpl {
public:  
  memimpl(context* ctx,
          uint32_t data_width,
          uint32_t addr_width,
          bool write_enable);
  ~memimpl();

  uint32_t get_total_size() const {
    return value_.get_size();
  }

  uint32_t get_data_width() const {
    return data_width_;
  }

  uint32_t get_addr_width() {
    return addr_width_;
  }

  bool is_initialized() const {
    return initialized_;
  }

  const std::vector<lnode>& get_ports() const {
    return ports_;
  }

  cdomain* get_cd() const {
    return cd_;
  }

  void load(const std::string& file);
  void load(const std::vector<uint8_t>& data);
  
  lnode& read(const lnode& addr);
  void write(const lnode& addr, const lnode& data);
  
  void tick(ch_tick t) override;
  void tick_next(ch_tick t) override;
  
  const bitvector& eval(ch_tick t) override;  
  void print(std::ostream& out, uint32_t level) const override;

protected:

  void load_data(const std::function<bool(uint8_t* out)>& getdata);
  
  lnode& get_port(const lnode& addr, bool writable);
  
  std::vector<lnode> ports_;
  uint32_t data_width_;
  uint32_t addr_width_;
  uint32_t wr_ports_offset_;
  cdomain* cd_;
  bool initialized_;
  
  friend class memportimpl;
};

class memportimpl : public ioimpl {
public:  
  memportimpl(memimpl* mem, const lnode& addr, bool writable);

  const lnode& get_mem() const {
    return srcs_[mem_idx_];
  }

  const lnode& get_addr() const {
    return srcs_[addr_idx_];
  }

  const lnode& get_wdata() const {
    return srcs_[wdata_idx_];
  }

  bool is_writable() const {
    return writable_;
  }

  void set_writable(bool writable) {
    writable_ = writable;
  }
  
  void write(const lnode& data);

  void tick(ch_tick t);
  void tick_next(ch_tick t);
  
  const bitvector& eval(ch_tick t) override;

protected:
    
  bitvector q_next_;
  uint32_t  a_next_;
  
  int mem_idx_;
  int addr_idx_;
  int wdata_idx_;
  bool writable_;
  
  ch_tick tick_;
  
  friend class memimpl;
};

}
}
