#include "memimpl.h"
#include "mem.h"
#include "context.h"
#include "litimpl.h"
#include "proxyimpl.h"

using namespace ch::internal;

std::vector<uint8_t> toByteVector(const std::string& init_file,
                                  uint32_t data_width,
                                  uint32_t num_items) {
  std::vector<uint8_t> packed(ceildiv<uint32_t>(data_width * num_items, 8));
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
                 const sdata_type& init_data,
                 lnodeimpl* cd,
                 const source_location& sloc)
  : ioimpl(ctx, type_mem, data_width * num_items, sloc)
  , init_data_(init_data)
  , cd_idx_(-1)
  , data_width_(data_width)
  , num_items_(num_items)
  , is_write_enable_(write_enable)
  , is_sync_read_(sync_read) {
  if (write_enable || sync_read) {
    // allocate clock domain
    if (nullptr == cd) {
      cd = ctx->current_cd(sloc);
    }
    cd_idx_ = this->add_src(cd);
  }
}

lnodeimpl* memimpl::clone(context* ctx, const clone_map& cloned_nodes) {
  lnodeimpl* cd = nullptr;
  if (this->has_cd()) {
    cd = cloned_nodes.at(this->cd().id());
  }

  auto mem = ctx->create_node<memimpl>(data_width_, num_items_,
                                       is_write_enable_, is_sync_read_,
                                       init_data_, cd, sloc_);
  for (auto p : rdports_) {
    auto it = cloned_nodes.find(p->id());
    if (it == cloned_nodes.end())
      continue;
    auto port = reinterpret_cast<mrportimpl*>(it->second);
    auto addr = cloned_nodes.at(p->addr().id());
    lnodeimpl* enable = nullptr;
    if (p->has_enable()) {
      enable = cloned_nodes.at(p->enable().id());
    }
    port->init(mem, addr, enable);
    mem->rdports_.emplace_back(port);
  }

  for (auto p : wrports_) {
    auto it = cloned_nodes.find(p->id());
    if (it == cloned_nodes.end())
      continue;
    auto port = reinterpret_cast<mwportimpl*>(it->second);
    auto addr = cloned_nodes.at(p->addr().id());
    auto wdata = cloned_nodes.at(p->wdata().id());
    lnodeimpl* enable = nullptr;
    if (p->has_enable()) {
      enable = cloned_nodes.at(p->enable().id());
    }
    port->init(mem, addr, wdata, enable);
    mem->wrports_.emplace_back(port);
  }

  return mem;
}

mrportimpl* memimpl::create_rdport(lnodeimpl* addr,
                                   lnodeimpl* enable,
                                   const source_location& sloc) {
  for (auto port : rdports_) {
    if (port->addr().id() == addr->id())
      return port;
  }
  auto impl = ctx_->create_node<mrportimpl>(this, addr, enable, sloc);
  rdports_.emplace_back(impl);
  return impl;
}

mwportimpl* memimpl::create_wrport(lnodeimpl* addr,
                                   lnodeimpl* data,
                                   lnodeimpl* enable,
                                   const source_location& sloc) {
  for (auto port : wrports_) {
    if (port->addr().id() == addr->id())
      CH_ABORT("duplicate memory write to the same address not allowed");
  }
  auto impl = ctx_->create_node<mwportimpl>(this, addr, data, enable, sloc);
  wrports_.emplace_back(impl);
  return impl;
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

int memimpl::port_index(memportimpl* port) const {
  for (int i = 0, n = rdports_.size(); i < n; ++i) {
    if (rdports_[i]->id() == port->id())
      return i;
  }

  for (int i = 0, n = wrports_.size(); i < n; ++i) {
    if (wrports_[i]->id() == port->id())
      return i;
  }

  return -1;
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
                         uint32_t size,
                         const source_location& sloc)
  : ioimpl(ctx, type, size, sloc)
  , mem_(nullptr)
  , addr_idx_(-1)
  , enable_idx_(-1)
{}

void memportimpl::init(memimpl* mem, lnodeimpl* addr, lnodeimpl* enable) {
  mem_ = mem;
  mem->acquire();

  // add port address
  if (type_mrport == type_ && !mem->is_sync_read()) {
    addr_idx_ = this->add_src(addr);
  } else {
    addr_idx_ = mem->add_src(addr);
  }

  // add enable predicate
  if (enable) {
    enable_idx_ = mem->add_src(enable);
  }
}

memportimpl::~memportimpl() {
  mem_->release();
}

///////////////////////////////////////////////////////////////////////////////

mrportimpl::mrportimpl(context* ctx,
                       memimpl* mem,
                       lnodeimpl* addr,
                       lnodeimpl* enable,
                       const source_location& sloc)
  : memportimpl(ctx, type_mrport, mem->data_width(), sloc) {
  this->init(mem, addr, enable);
}

mrportimpl::mrportimpl(context* ctx, uint32_t size, const source_location& sloc)
  : memportimpl(ctx, type_mrport, size, sloc)
{}

void mrportimpl::init(memimpl* mem, lnodeimpl* addr, lnodeimpl* enable) {
  memportimpl::init(mem, addr, enable);

  // add memory as source
  srcs_.emplace_back(mem);
}

mrportimpl::~mrportimpl() {
  mem_->remove_port(this);
}

lnodeimpl* mrportimpl::clone(context* ctx, const clone_map& cloned_nodes) {
  auto it = cloned_nodes.find(this->mem()->id());
  if (it != cloned_nodes.end()
   && type_mem == it->second->type()) {
    auto mem = reinterpret_cast<memimpl*>(it->second);
    auto addr = cloned_nodes.at(this->addr().id());
    lnodeimpl* enable = nullptr;
    if (this->has_enable()) {
      enable = cloned_nodes.at(this->enable().id());
    }
    return mem->create_rdport(addr, enable, sloc_);
  } else {
    return ctx->create_node<mrportimpl>(size_, sloc_);
  }
}

///////////////////////////////////////////////////////////////////////////////

mwportimpl::mwportimpl(context* ctx,
                       memimpl* mem,
                       lnodeimpl* addr,
                       lnodeimpl* wdata,
                       lnodeimpl* enable,
                       const source_location& sloc)
  : memportimpl(ctx, type_mwport, mem->data_width(), sloc) {
  this->init(mem, addr, wdata, enable);
}

mwportimpl::mwportimpl(context* ctx, uint32_t size, const source_location& sloc)
  : memportimpl(ctx, type_mwport, size, sloc)
{}

void mwportimpl::init(memimpl* mem, lnodeimpl* addr, lnodeimpl* wdata, lnodeimpl* enable) {
  memportimpl::init(mem, addr, enable);

  // add as memory source
  mem->srcs().emplace_back(this);

  // add data source
  wdata_idx_ = mem_->add_src(wdata);
}

mwportimpl::~mwportimpl() {
  mem_->remove_port(this);
}

lnodeimpl* mwportimpl::clone(context* ctx, const clone_map&) {
  return ctx->create_node<mwportimpl>(size_, sloc_);
}

///////////////////////////////////////////////////////////////////////////////

memory::memory(uint32_t data_width,
               uint32_t num_items,
               bool write_enable,
               bool sync_read,
               const std::vector<uint8_t>& init_data,
               const source_location& sloc) {
  CH_CHECK(!ctx_curr()->conditional_enabled(), "memory objects cannot be nested inside a conditional block");
  sdata_type _init_data;
  if (!init_data.empty()) {
    _init_data.resize(data_width * num_items);
    _init_data.write(0, init_data.data(), 0, _init_data.size());
  }
  impl_ = ctx_curr()->create_node<memimpl>(
        data_width, num_items, write_enable, sync_read, _init_data, nullptr, sloc);
}

lnodeimpl* memory::read(const lnode& addr, const source_location& sloc) const {
  return impl_->create_rdport(addr.impl(), nullptr, sloc);
}

lnodeimpl* memory::read(const lnode& addr,
                        const lnode& enable,
                        const source_location& sloc) const {
  return impl_->create_rdport(addr.impl(), enable.impl(), sloc);
}

void memory::write(const lnode& addr, const lnode& value, const source_location& sloc) {
  impl_->create_wrport(addr.impl(), value.impl(), nullptr, sloc);
}

void memory::write(const lnode& addr,
                   const lnode& value,
                   const lnode& enable,
                   const source_location& sloc) {
  impl_->create_wrport(addr.impl(), value.impl(), enable.impl(), sloc);
}
