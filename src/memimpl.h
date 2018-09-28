#pragma once

#include "ioimpl.h"
#include "cdimpl.h"

namespace ch {
namespace internal {

class memportimpl;
class mrportimpl;
class mwportimpl;

class memimpl : public ioimpl {
public:

  memimpl(context* ctx,
          uint32_t data_width,
          uint32_t num_items,
          bool write_enable,
          bool sync_read,
          const std::vector<uint8_t>& init_data,
          const source_location& sloc);

  uint32_t total_size() const {
    return size_;
  }

  uint32_t data_width() const {
    return data_width_;
  }

  uint32_t num_items() {
    return num_items_;
  }

  bool is_write_enable() const {
    return is_write_enable_;
  }

  bool is_sync_read() const {
    return is_sync_read_;
  }

  bool has_initdata() const {
    return has_initdata_;
  }

  const sdata_type& initdata() const {
    return initdata_;
  }

  bool has_cd() const {
    return (cd_idx_ != -1);
  }

  auto& cd() const {
    return srcs_[cd_idx_];
  }

  auto& rdports() const {
    return rdports_;
  }

  auto& wrports() const {
    return wrports_;
  }

  bool is_readwrite(memportimpl* port) const;

  mrportimpl* create_port(const lnode& addr,
                          const lnode& enable,
                          const source_location& sloc);

  mwportimpl* create_port(const lnode& addr,
                          const lnode& data,
                          const lnode& enable,
                          const source_location& sloc);

  void remove_port(mrportimpl* port);

  void remove_port(mwportimpl* port);

  void print(std::ostream& out) const override;

protected:
  
  std::vector<mrportimpl*> rdports_;
  std::vector<mwportimpl*> wrports_;
  sdata_type initdata_;
  int cd_idx_;
  uint32_t data_width_;
  uint32_t num_items_;
  bool is_write_enable_;
  bool is_sync_read_;
  bool has_initdata_;  
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
    if (type_mrport == type_ && !mem_->is_sync_read()) {
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

  bool is_sync_read() const {
    return mem_->is_sync_read();
  }

  ~mrportimpl();
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

protected:

  int wdata_idx_;
};

}
}
