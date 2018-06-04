#pragma once

#include "ioimpl.h"
#include "cdimpl.h"

namespace ch {
namespace internal {

class memportimpl;

class memimpl : public ioimpl {
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

  cdimpl* cd() const {
    return cd_;
  }

  auto& ports() const {
    return ports_;
  }

  bool is_readwrite(memportimpl* port) const;

  memportimpl* read(const lnode& addr);

  void write(const lnode& addr, const lnode& data, const lnode& enable);

  void remove_port(memportimpl* port);

  void eval() override;

  void print(std::ostream& out, uint32_t level) const override;

protected:
  
  std::vector<memportimpl*> ports_;
  uint32_t data_width_;
  uint32_t num_items_;
  bool write_enable_;
  bool has_initdata_;
  cdimpl* cd_;
};

///////////////////////////////////////////////////////////////////////////////

class memportimpl : public ioimpl {
public:

  memportimpl(context* ctx,
              lnodetype type,
              memimpl* mem,
              const lnode& addr);

  ~memportimpl();

  memimpl* mem() const {
    return mem_;
  }

  uint32_t index() const {
    return index_;
  }

  const lnode& addr() const {
    return srcs_[0];
  }

protected:

  memimpl* mem_;
  uint32_t index_;
};

///////////////////////////////////////////////////////////////////////////////


class mrportimpl : public memportimpl {
public:  

  mrportimpl(context* ctx, memimpl* mem, const lnode& addr);

  ~mrportimpl();

  void eval() override;
};

///////////////////////////////////////////////////////////////////////////////

class mwportimpl : public memportimpl {
public:

  mwportimpl(context* ctx,
             memimpl* mem,
             const lnode& addr,
             const lnode& data,
             const lnode& enable);

  ~mwportimpl();

  const lnode& cd() const {
    return srcs_[1];
  }

  const lnode& wdata() const {
    return srcs_[2];
  }

  bool has_wenable() const {
    return (wenable_idx_ != -1);
  }

  const lnode& wenable() const {
    return srcs_[wenable_idx_];
  }

  void eval() override;

protected:

  int wenable_idx_;
};

}
}
