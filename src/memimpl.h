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
          bool sync_read,
          bool raw,
          const std::vector<uint8_t>& init_data,
          const source_location& sloc);

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

  bool is_sync_read() const {
    return sync_read_;
  }

  bool is_raw() const {
    return raw_;
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

  memportimpl* read(const lnode& addr,
                    const lnode& enable,
                    const source_location& sloc);

  void write(const lnode& addr,
             const lnode& data,
             const lnode& enable,
             const source_location& sloc);

  void remove_port(memportimpl* port);

  void eval() override;

  void print(std::ostream& out, uint32_t level) const override;

protected:
  
  std::vector<memportimpl*> ports_;
  uint32_t data_width_;
  uint32_t num_items_;
  bool write_enable_;
  bool sync_read_;
  bool raw_;
  bool has_initdata_;
  cdimpl* cd_;
};

///////////////////////////////////////////////////////////////////////////////

class memportimpl : public ioimpl {
public:

  memportimpl(context* ctx,
              lnodetype type,
              memimpl* mem,
              const lnode& addr,
              const lnode& enable,
              const source_location& sloc);

  ~memportimpl();

  memimpl* mem() const {
    return mem_;
  }

  uint32_t index() const {
    return index_;
  }

  const lnode& addr() const {
    if (type_mrport == type_
     && !mem_->is_sync_read()) {
      return this->src(addr_idx_);
    } else {
      return mem_->src(addr_idx_);
    }
  }

  bool has_enable() const {
    return (enable_idx_ != -1);
  }

  const lnode& enable() const {
    return mem_->src(enable_idx_);
  }

protected:

  memimpl* mem_;
  uint32_t index_;
  int addr_idx_;  
  int enable_idx_;
};

///////////////////////////////////////////////////////////////////////////////


class mrportimpl : public memportimpl {
public:  

  mrportimpl(context* ctx,
             memimpl* mem,
             const lnode& addr,
             const lnode& enable,
             const source_location& sloc);

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
             const lnode& enable,
             const source_location& sloc);

  ~mwportimpl();

  const lnode& wdata() const {
    return mem_->src(wdata_idx_);
  }

  void eval() override;

protected:

  int wdata_idx_;
};

}
}
