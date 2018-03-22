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
          uint32_t num_items,
          bool write_enable,
          const std::vector<uint8_t>& init_data);
  ~memimpl();

  uint32_t get_total_size() const {
    return value_.get_size();
  }

  uint32_t get_data_width() const {
    return data_width_;
  }

  uint32_t get_num_items() {
    return num_items_;
  }

  bool is_write_enable() const {
    return (cd_ != nullptr);
  }

  bool has_initdata() const {
    return has_initdata_;
  }

  cdomain* get_cd() const {
    return cd_;
  }

  const std::vector<lnode>& get_ports() const {
    return ports_;
  }

  lnode& get_port(const lnode& addr);

  void remove(memportimpl* port);
  
  void tick(ch_tick t) override;
  void tick_next(ch_tick t) override;
  
  const bitvector& eval(ch_tick t) override;  
  void print(std::ostream& out, uint32_t level) const override;

protected:
  
  std::vector<lnode> ports_;
  uint32_t data_width_;
  uint32_t num_items_;
  cdomain* cd_;
  bool has_initdata_;
};

class memportimpl : public ioimpl {
public:  

  memportimpl(context* ctx, memimpl* mem, unsigned index, const lnode& addr);
  ~memportimpl();

  const lnode& get_mem() const {
    return srcs_[mem_idx_];
  }

  unsigned get_index() const {
    return index_;
  }

  const lnode& get_addr() const {
    return srcs_[addr_idx_];
  }

  const lnode& get_wdata() const {
    return srcs_[wdata_idx_];
  }

  const lnode& get_enable() const {
    return srcs_[enable_idx_];
  }

  bool has_wdata() const {
    return (wdata_idx_ != -1);
  }

  bool has_enable() const {
    return (enable_idx_ != -1);
  }

  bool is_read_enable() const {
    return read_enable_;
  }

  void detach();

  void read();
  
  void write(const lnode& data);

  void write(const lnode& data, const lnode& enable);

  void tick(ch_tick t);

  void tick_next(ch_tick t);
  
  const bitvector& eval(ch_tick t) override;

protected:

  int insert(int index, const lnode& value);

  unsigned index_;
  bitvector q_next_;
  uint32_t a_next_;
  bool en_next_;
  
  int mem_idx_;
  int addr_idx_;
  int wdata_idx_;
  int enable_idx_;

  bool read_enable_;

  ch_tick tick_;
};

}
}
