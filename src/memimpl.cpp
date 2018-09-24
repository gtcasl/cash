#include "memimpl.h"
#include "mem.h"
#include "context.h"
#include "litimpl.h"
#include "proxyimpl.h"

using namespace ch::internal;

std::vector<uint8_t> toByteVector(const std::string& init_file,
                                  uint32_t data_width,
                                  uint32_t num_items) {
  std::vector<uint8_t> packed(ceildiv<int>(data_width * num_items, 8));
  std::ifstream in(init_file, std::ios::binary);
  in.read((char*)packed.data(), packed.size());
  return packed;
}

///////////////////////////////////////////////////////////////////////////////

memimpl::memimpl(context* ctx,
                 uint32_t data_width,
                 uint32_t num_items,
                 bool write_enable,
                 bool sync_read,
                 const std::vector<uint8_t>& init_data,
                 const source_location& sloc)
  : ioimpl(ctx, type_mem, data_width * num_items, sloc)
  , initdata_(data_width * num_items)
  , cd_idx_(-1)
  , data_width_(data_width)
  , num_items_(num_items)
  , is_write_enable_(write_enable)
  , is_sync_read_(sync_read)
  , has_initdata_(!init_data.empty()) {
  if (write_enable || sync_read) {
    // allocate clock domain
    auto cd = ctx->current_cd(sloc);
    cd_idx_ = this->add_src(cd);
  }
  if (has_initdata_) {
    assert(8 * init_data.size() >= size_);
    initdata_.write(0, init_data.data(), 0, size_);
  } else {
    // initialize with dirty content
    initdata_.deadbeef();
  }
}

void memimpl::remove_port(mrportimpl* port) {
  for (auto it = rdports_.begin(), end = rdports_.end(); it != end; ++it) {
    if ((*it)->id() == port->id()) {
      rdports_.erase(it);
      break;
    }
  }
}

void memimpl::remove_port(mwportimpl* port) {
  for (auto it = wrports_.begin(), end = wrports_.end(); it != end; ++it) {
    if ((*it)->id() == port->id()) {
      wrports_.erase(it);
      break;
    }
  }
}

mrportimpl* memimpl::create_port(const lnode& addr,
                                 const lnode& enable,
                                 const source_location& sloc) {
  for (auto port : rdports_) {
    if (port->addr().id() == addr.id())
      return port;
  }
  auto impl = ctx_->create_node<mrportimpl>(this, addr, enable, sloc);
  rdports_.emplace_back(impl);
  return impl;
}

mwportimpl* memimpl::create_port(const lnode& addr,
                                 const lnode& data,
                                 const lnode& enable,
                                 const source_location& sloc) {
  for (auto port : wrports_) {
    if (port->addr().id() == addr.id())
      CH_ABORT("duplicate memory write to the same address not allowed");
  }
  auto impl = ctx_->create_node<mwportimpl>(this, addr, data, enable, sloc);
  wrports_.emplace_back(impl);
  return impl;
}

bool memimpl::is_readwrite(memportimpl* port) const {
  if (type_mrport == port->type()) {
    for (auto p : wrports_) {
      if (p->addr().id() == port->id())
        return true;
    }
  } else {
    for (auto p : rdports_) {
      if (p->addr().id() == port->id())
        return true;
    }
  }
  return false;
}

void memimpl::print(std::ostream& out) const {
  out << "#" << id_ << " <- " << this->type() << size_;
  uint32_t n = srcs_.size();
  if (n > 0) {
    out << "(";
    for (uint32_t i = 0; i < n; ++i) {
      if (i > 0)
        out << ", ";
      out << "#" << srcs_[i].id();
    }
    out << ")";
  }
}

///////////////////////////////////////////////////////////////////////////////

memportimpl::memportimpl(context* ctx,
                         lnodetype type,
                         memimpl* mem,
                         const lnode& addr,
                         const lnode& enable,
                         const source_location& sloc)
  : ioimpl(ctx, type, mem->data_width(), sloc)
  , mem_(mem)
  , index_((type_mrport == type) ? mem->rdports().size() : mem->wrports().size())
  , enable_idx_(-1) {
  mem->acquire();

  // add port address
  if (type_mrport == type && !mem->is_sync_read()) {
    addr_idx_ = this->add_src(addr);
  } else {
    addr_idx_ = mem_->add_src(addr);
  }

  // add enable predicate
  if (type_lit != enable.impl()->type()
   || !static_cast<bool>(reinterpret_cast<litimpl*>(enable.impl())->value())) {
    enable_idx_ = mem_->add_src(enable);
  }
}

memportimpl::~memportimpl() {  
  mem_->release();
}

///////////////////////////////////////////////////////////////////////////////

mrportimpl::mrportimpl(context* ctx,
                       memimpl* mem,
                       const lnode& addr,
                       const lnode& enable,
                       const source_location& sloc)
  : memportimpl(ctx, type_mrport, mem, addr, enable, sloc) {
  // add memory as source
  srcs_.emplace_back(mem);
}

mrportimpl::~mrportimpl() {
  mem_->remove_port(this);
}

///////////////////////////////////////////////////////////////////////////////

mwportimpl::mwportimpl(context* ctx,
                       memimpl* mem,
                       const lnode& addr,
                       const lnode& data,
                       const lnode& enable,
                       const source_location& sloc)
  : memportimpl(ctx, type_mwport, mem, addr, enable, sloc) {
  // add as memory source
  mem->srcs().emplace_back(this);

  // add data source
  wdata_idx_ = mem_->add_src(data);
}

mwportimpl::~mwportimpl() {
  mem_->remove_port(this);
}

///////////////////////////////////////////////////////////////////////////////

memory::memory(uint32_t data_width,
               uint32_t num_items,
               bool write_enable,
               bool sync_read,
               const std::vector<uint8_t>& init_data,
               const source_location& sloc) {
  CH_CHECK(!ctx_curr()->conditional_enabled(), "memory objects cannot be nested inside a conditional block");
  impl_ = ctx_curr()->create_node<memimpl>(
        data_width, num_items, write_enable, sync_read, init_data, sloc);
}

lnodeimpl* memory::read(const lnode& addr,
                        const lnode& enable,
                        const source_location& sloc) const {
  return impl_->create_port(addr, enable, sloc);
}

void memory::write(const lnode& addr,
                   const lnode& value,
                   const lnode& enable,
                   const source_location& sloc) {
  impl_->create_port(addr, value, enable, sloc);
}
