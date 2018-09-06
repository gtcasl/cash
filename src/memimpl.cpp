#include "memimpl.h"
#include "mem.h"
#include "context.h"
#include "proxyimpl.h"

using namespace ch::internal;

std::vector<uint8_t> toByteVector(const std::string& init_file,
                                  uint32_t data_width,
                                  uint32_t num_items) {
  std::vector<uint8_t> packed(CH_CEILDIV(data_width * num_items, 8));
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
  , data_width_(data_width)
  , num_items_(num_items)
  , write_enable_(write_enable)
  , sync_read_(sync_read)
  , has_initdata_(!init_data.empty())
  , cd_(nullptr) {
  if (write_enable || sync_read) {
    // allocate clock domain
    cd_ = ctx->current_cd(sloc);
    srcs_.emplace_back(cd_);
  }
  if (has_initdata_) {
    assert(8 * init_data.size() >= data_.size());
    data_.write(0, init_data.data(), init_data.size(), 0, data_.size());
  } else {
    // initialize with dirty content
    data_.deadbeef();
  }
}

void memimpl::remove_port(memportimpl* port) {
  for (auto it = ports_.begin(), end = ports_.end(); it != end; ++it) {
    if ((*it)->id() == port->id()) {
      ports_.erase(it);
      break;
    }
  }
}

memportimpl* memimpl::read(const lnode& addr,
                           const lnode& enable,
                           const source_location& sloc) {
  for (auto port : ports_) {
    if (port->addr().id() == addr.id()
     && port->type() != type_mwport) {
      return port;
    }
  }
  auto impl = ctx_->create_node<mrportimpl>(this, addr, enable, sloc);
  ports_.emplace_back(impl);
  return ports_.back();
}

void memimpl::write(const lnode& addr,
                    const lnode& data,
                    const lnode& enable,
                    const source_location& sloc) {
  for (auto port : ports_) {
    if (port->addr().id() == addr.id()
     && port->type() == type_mwport) {
      CH_ABORT("duplicate memory write to the same address not allowed");
    }
  }
  auto impl = ctx_->create_node<mwportimpl>(this, addr, data, enable, sloc);
  ports_.emplace_back(impl);
}

bool memimpl::is_readwrite(memportimpl* port) const {
  for (auto p : ports_) {
    if (p->addr().id() == port->id() && p->type() != port->type())
      return true;
  }
  return false;
}

void memimpl::eval() {
  // check clock transition
  if (nullptr == cd_ || !static_cast<bool>(cd_->data()))
    return;

  if (sync_read_) {
    // evaluate read ports
    for (auto p : ports_) {
      if (type_mrport != p->type())
        continue;

      // check enable state
      auto port = reinterpret_cast<mrportimpl*>(p);
      int enable = port->has_enable() ? static_cast<bool>(port->enable().data()) : true;
      if (!enable)
        return;

      // memory read
      auto addr = static_cast<uint32_t>(port->addr().data());
      auto& data = port->data();
      data_.read(addr * data_width_,
                  data.data(),
                  data.num_bytes(),
                  0,
                  data_width_);
    }
  }

  // evaluate write ports
  for (auto p : ports_) {
    if (type_mwport != p->type())
      continue;

    // check enable state
    auto port = reinterpret_cast<mwportimpl*>(p);
    int enable = port->has_enable() ? static_cast<bool>(port->enable().data()) : true;
    if (!enable)
      return;

    // memory write
    auto addr = static_cast<uint32_t>(port->addr().data());
    auto& data = port->wdata().data();
    data_.write(addr * data_width_,
                 data.data(),
                 data.num_bytes(),
                 0,
                 data_width_);
  }
}

void memimpl::print(std::ostream& out, uint32_t level) const {
  CH_UNUSED(level);
  out << "#" << id_ << " <- " << this->type() << data_.size();
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
  if (level == 2) {
    out << " = " << data_;
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
  , index_(mem->ports().size())
  , enable_idx_(-1) {
  mem->acquire();

  // add port address
  if (type_mrport == type
   && !mem->is_sync_read()) {
    addr_idx_ = this->add_src(addr);
  } else {
    addr_idx_ = mem_->add_src(addr);
  }

  // add enable predicate
  if (enable.impl()->type() != type_lit) {
    enable_idx_ = mem_->add_src(enable);
  } else {
    // the constant value should be one
    assert(static_cast<bool>(enable.impl()->data()));
  }
}

memportimpl::~memportimpl() {
  mem_->remove_port(this);
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

void mrportimpl::eval() {
  if (mem_->is_sync_read())
    return;

  // memory read
  auto data_width = mem_->data_width();
  auto addr = static_cast<uint32_t>(this->addr().data());
  mem_->data().read(addr * data_width,
              data_.data(),
              data_.num_bytes(),
              0,
              data_width);
}

///////////////////////////////////////////////////////////////////////////////

mwportimpl::mwportimpl(context* ctx,
                       memimpl* mem,
                       const lnode& addr,
                       const lnode& data,
                       const lnode& enable,
                       const source_location& sloc)
  : memportimpl(ctx, type_mwport, mem, addr, enable, sloc) {
  // add to memory sources
  mem->srcs().emplace_back(this);

  // add data source
  wdata_idx_ = mem_->add_src(data);
}

void mwportimpl::eval() {}

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
  return impl_->read(addr, enable, sloc);
}

void memory::write(const lnode& addr,
                   const lnode& value,
                   const lnode& enable,
                   const source_location& sloc) {
  impl_->write(addr, value, enable, sloc);
}
