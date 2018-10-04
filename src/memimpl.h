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

  bool has_init_data() const {
    return init_data_.size() != 0;
  }

  const sdata_type& init_data() const {
    return init_data_;
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

  auto& rdport(uint32_t index) const {
    return rdports_[index];
  }

  auto& wrports() const {
    return wrports_;
  }

  auto& wrport(uint32_t index) const {
    return wrports_[index];
  }

  int port_index(memportimpl* port) const;

  bool is_readwrite(memportimpl* port) const;

  virtual lnodeimpl* clone(context* ctx, const clone_map& cloned_nodes) override;

  mrportimpl* create_rdport(lnodeimpl* addr,
                            lnodeimpl* enable,
                            const source_location& sloc);

  mwportimpl* create_wrport(lnodeimpl* addr,
                            lnodeimpl* data,
                            lnodeimpl* enable,
                            const source_location& sloc);

  void remove_port(mrportimpl* port);

  void remove_port(mwportimpl* port);

  void print(std::ostream& out) const override;

protected:

  memimpl(context* ctx,
          uint32_t data_width,
          uint32_t num_items,
          bool write_enable,
          bool sync_read,
          const sdata_type& init_data,
          lnodeimpl* cd,
          const source_location& sloc);
  
  std::vector<mrportimpl*> rdports_;
  std::vector<mwportimpl*> wrports_;
  sdata_type init_data_;
  int cd_idx_;
  uint32_t data_width_;
  uint32_t num_items_;
  bool is_write_enable_;
  bool is_sync_read_;

  friend class context;
};

///////////////////////////////////////////////////////////////////////////////

class memportimpl : public ioimpl {
public:

  memimpl* mem() const {
    return mem_;
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

  void init(memimpl* mem, lnodeimpl* addr, lnodeimpl* enable);

protected:

  memportimpl(context* ctx, lnodetype type, uint32_t size, const source_location& sloc);

  ~memportimpl();

  memimpl* mem_;
  int addr_idx_;  
  int enable_idx_;
};

///////////////////////////////////////////////////////////////////////////////

class mrportimpl : public memportimpl {
public:

  bool is_sync_read() const {
    return mem_->is_sync_read();
  }  

  void init(memimpl* mem, lnodeimpl* addr, lnodeimpl* enable);

  virtual lnodeimpl* clone(context* ctx, const clone_map& cloned_nodes) override;

protected:

  mrportimpl(context* ctx,
             memimpl* mem,
             lnodeimpl* addr,
             lnodeimpl* enable,
             const source_location& sloc);

  mrportimpl(context* ctx, uint32_t size, const source_location& sloc);

  ~mrportimpl();

  friend class context;
};

///////////////////////////////////////////////////////////////////////////////

class mwportimpl : public memportimpl {
public:

  const lnode& wdata() const {
    return mem_->src(wdata_idx_);
  }

  void init(memimpl* mem, lnodeimpl* addr, lnodeimpl* wdata, lnodeimpl* enable);

  virtual lnodeimpl* clone(context* ctx, const clone_map& cloned_nodes) override;

  friend class context;

protected:

  mwportimpl(context* ctx,
             memimpl* mem,
             lnodeimpl* addr,
             lnodeimpl* wdata,
             lnodeimpl* enable,
             const source_location& sloc);

  mwportimpl(context* ctx, uint32_t size, const source_location& sloc);

  ~mwportimpl();

  int wdata_idx_;
};

}
}
