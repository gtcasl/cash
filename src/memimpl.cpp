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
                 const std::vector<uint8_t>& init_data,
                 const source_location& sloc)
  : ioimpl(ctx, type_mem, data_width * num_items, sloc)
  , data_width_(data_width)
  , num_items_(num_items)
  , write_enable_(write_enable)
  , has_initdata_(!init_data.empty())
  , cd_(nullptr) {
  if (write_enable) {
    cd_ = ctx->current_cd(sloc);
  }
  if (has_initdata_) {
    assert(8 * init_data.size() >= value_.size());
    value_.write(0, init_data.data(), init_data.size(), 0, value_.size());
  } else {
    // initialize with dirty content
    value_.deadbeef();
  }
}

memimpl::~memimpl() {}

void memimpl::remove_port(memportimpl* port) {
  for (auto it = ports_.begin(), end = ports_.end(); it != end; ++it) {
    if ((*it)->id() == port->id()) {
      ports_.erase(it);
      break;
    }
  }
}

memportimpl* memimpl::read(const lnode& addr, const source_location& sloc) {
  for (auto port : ports_) {
    if (port->addr().id() == addr.id() && port->type() == type_mrport) {
      return port;
    }
  }
  auto impl = ctx_->create_node<mrportimpl>(this, addr, sloc);
  ports_.emplace_back(impl);
  return ports_.back();
}

void memimpl::write(const lnode& addr,
                    const lnode& data,
                    const lnode& enable,
                    const source_location& sloc) {
  for (auto port : ports_) {
    if (port->addr().id() == addr.id() && port->type() == type_mwport) {
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
  //--
}

void memimpl::print(std::ostream& out, uint32_t level) const {
  CH_UNUSED(level);
  out << "#" << id_ << " <- " << this->type() << value_.size();
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
    out << " = " << value_;
  }
}

///////////////////////////////////////////////////////////////////////////////

memportimpl::memportimpl(context* ctx,
                         lnodetype type,
                         memimpl* mem,
                         const lnode& addr,
                         const source_location& sloc)
  : ioimpl(ctx, type, mem->data_width(), sloc)
  , mem_(mem)
  , index_(mem->ports().size()) {
  mem->acquire();  
  srcs_.emplace_back(addr);
}

memportimpl::~memportimpl() {
  mem_->remove_port(this);
  mem_->release();
}

///////////////////////////////////////////////////////////////////////////////

mrportimpl::mrportimpl(context* ctx,
                       memimpl* mem,
                       const lnode& addr,
                       const source_location& sloc)
  : memportimpl(ctx, type_mrport, mem, addr, sloc) {
  srcs_.emplace_back(mem); // make memory a source
}

mrportimpl::~mrportimpl() {}

void mrportimpl::eval() {
  // asynchronous read
  auto data_width = mem_->data_width();
  auto addr = this->addr().data().word(0);
  mem_->value().read(addr * data_width,
                     value_.data(),
                     value_.num_bytes(),
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
  : memportimpl(ctx, type_mwport, mem, addr, sloc) {
  mem->srcs().emplace_back(this); // add to memory sources

  // add clock domain
  srcs_.emplace_back(mem->cd());

  // add data source
  srcs_.emplace_back(data);

  // add enable predicate
  if (enable.impl()->type() == type_lit) {
    wenable_idx_ = (1 == enable.data().word(0)) ? -1 : 0;
  } else {
    wenable_idx_ = this->add_src(enable);
  }
}

mwportimpl::~mwportimpl() {}

void mwportimpl::eval() {
  // check clock transition
  if (0 == this->cd().data().word(0))
    return;

  // synchronous memory write
  int wenable = this->has_wenable() ? this->wenable().data().word(0) : wenable_idx_;
  if (wenable) {
    auto data_width = mem_->data_width();
    auto addr = this->addr().data().word(0);
    auto& data = this->wdata().data();
    mem_->value().write(addr * data_width,
                        data.data(),
                        data.num_bytes(),
                        0,
                        data_width);
  }
}

///////////////////////////////////////////////////////////////////////////////

memory::memory(uint32_t data_width,
               uint32_t num_items,
               bool write_enable,
               const std::vector<uint8_t>& init_data,
               const source_location& sloc) {
  CH_CHECK(!ctx_curr()->conditional_enabled(), "memory objects cannot be nested inside a conditional block");
  impl_ = ctx_curr()->create_node<memimpl>(data_width, num_items, write_enable, init_data, sloc);
}

lnodeimpl* memory::read(const lnode& addr, const source_location& sloc) const {
  return impl_->read(addr, sloc);
}

void memory::write(const lnode& addr,
                   const lnode& value,
                   const lnode& enable,
                   const source_location& sloc) {
  impl_->write(addr, value, enable, sloc);
}
