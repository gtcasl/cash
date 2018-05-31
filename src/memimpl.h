#pragma once

#include "ioimpl.h"
#include "cdimpl.h"

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

  uint32_t total_size() const {
    return value_.size();
  }

  uint32_t data_width() const {
    return data_width_;
  }

  uint32_t num_items() {
    return num_items_;
  }

  bool is_write_enable() const {
    return write_enable_;
  }

  bool has_initdata() const {
    return has_initdata_;
  }

  const lnode& cd() const {
    return srcs_[0];
  }

  auto& ports() const {
    return ports_;
  }

  memportimpl* port(const lnode& addr);

  void remove_port(memportimpl* port);

  void tick() override;

  void eval() override;

  void print(std::ostream& out, uint32_t level) const override;

protected:
  
  std::vector<memportimpl*> ports_;
  uint32_t data_width_;
  uint32_t num_items_;
  bool write_enable_;
  bool has_initdata_;
};

class memportimpl : public ioimpl {
public:  

  memportimpl(context* ctx, memimpl* mem, uint32_t index, const lnode& addr);

  ~memportimpl();

  uint32_t index() const {
    return index_;
  }

  const lnode& mem() const {
    return srcs_[0];
  }

  const lnode& addr() const {
    return srcs_[1];
  }

  const lnode& wdata() const {
    return srcs_[wdata_idx_];
  }

  const lnode& wenable() const {
    return srcs_[wenable_idx_];
  }

  bool has_wdata() const {
    return (wdata_idx_ != -1);
  }

  bool has_wenable() const {
    return (wenable_idx_ != -1);
  }

  bool is_read_enable() const {
    return read_enable_;
  }

  void read();
  
  void write(const lnode& data);

  void write(const lnode& data, const lnode& enable);

  void tick();

  void eval() override;

protected:

  int insert(int index, const lnode& value);

  uint32_t index_;
  bool read_enable_;
  bitvector q_next_;
  uint32_t a_next_;
  int wdata_idx_;
  int wenable_idx_;
  bool dirty_;
};

}
}
