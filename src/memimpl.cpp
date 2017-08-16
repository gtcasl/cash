#include "memimpl.h"
#include "mem.h"
#include "context.h"

using namespace std;
using namespace cash::detail;

memimpl::memimpl(context* ctx, uint32_t data_width, uint32_t addr_width, bool write_enable) 
  : lnodeimpl(op_mem, ctx, data_width << addr_width)
  , data_width_(data_width)
  , addr_width_(addr_width)
  , ports_offset_(0)
  , cd_(nullptr) {  
  if (write_enable) {
    lnodeimpl* const clk = ctx->get_clk();
    cd_ = ctx->create_cdomain({clock_event(clk, EDGE_POS)});
    cd_->add_use(this);
    srcs_.emplace_back(clk);
    ports_offset_ = 1;
  }
}

memimpl::~memimpl() {
  if (cd_) {
    cd_->remove_use(this);
  }
}

void memimpl::load(const std::vector<uint8_t>& data) {
  assert(8 * data.size() <= value_.get_size());
  value_.write(data.data(), 0, value_.get_size());
}

void memimpl::load(const std::string& file) {
  ifstream in(file.c_str(), std::ios::binary);
  uint32_t size = value_.get_size();
  uint32_t offset = 0;

  while ((size - offset) >= 64) {
    uint64_t x;
    in >> x;
    value_.write((uint8_t*)&x, offset, 64);
    offset += 64;
  }

  while (offset < size) {
    uint8_t x;
    in >> x;
    int len = std::min<int>(size - offset, 8);
    value_.write(&x, offset, len);
    offset += len;
  }

  in.close();
}

memportimpl* memimpl::read(const lnode& addr) {
  return this->get_port(addr, false);
}

void memimpl::write(const lnode& addr, const lnode& data) {
  memportimpl* port = this->get_port(addr, true);
  port->write(data);  
}

memportimpl* memimpl::get_port(const lnode& addr, bool writing) {
  memportimpl* port = nullptr; 
  for (uint32_t i = ports_offset_, n = srcs_.size(); i < n; ++i) {
    memportimpl* const item  = dynamic_cast<memportimpl*>(srcs_[i].get_impl());
    if (item->get_addr() == addr) {
      port = item;
      break;
    }
  }
  if (nullptr == port) {
    port = new memportimpl(this, addr);
    if (writing) {
      srcs_.emplace_back(port);
    }
  }
  return port;
}

void memimpl::tick(ch_cycle t) {    
  for (uint32_t i = ports_offset_, n = srcs_.size(); i < n; ++i) {
    memportimpl* const port = dynamic_cast<memportimpl*>(srcs_[i].get_impl());
    port->tick(t);
  }
}

void memimpl::tick_next(ch_cycle t) {
  for (uint32_t i = ports_offset_, n = srcs_.size(); i < n; ++i) {
   memportimpl* const port = dynamic_cast<memportimpl*>(srcs_[i].get_impl());
   port->tick_next(t);
  }
}

const bitvector& memimpl::eval(ch_cycle t) {
  CH_UNUSED(t);
  abort();
}

void memimpl::print(std::ostream& out, uint32_t level) const {
  CH_UNUSED(level);
  out << "#" << id_ << " <- " << this->get_name() << value_.get_size();
  uint32_t n = srcs_.size();
  if (n > 0) {
    out << "(";
    for (uint32_t i = 0; i < n; ++i) {
      if (i > 0)
        out << ", ";
      out << "#" << srcs_[i].get_id();
    }
    out << ")";
  }
}
void memimpl::print_vl(ostream& out) const {
  CH_UNUSED(out);
  CH_TODO();
}

///////////////////////////////////////////////////////////////////////////////

memportimpl::memportimpl(memimpl* mem, const lnode& addr)
  : lnodeimpl(op_memport, addr->get_ctx(), mem->data_width_)
  , a_next_(0)
  , addr_id_(-1)
  , wdata_id_(-1)
  , ctime_(~0ull) {
  srcs_.emplace_back(mem);
  addr_id_ = srcs_.size();
  srcs_.emplace_back(addr);
}

void memportimpl::write(const lnode& data) {
  // use explicit assignment to force conditionals resolution
  if (wdata_id_ == -1) {
    wdata_id_ = srcs_.size();
    if (ctx_->conditional_enabled(this)) {
      srcs_.emplace_back(ctx_->resolve_conditional(data, this));
    } else {
      srcs_.emplace_back(data);
    }
  } else {
    srcs_[wdata_id_].assign(data);
  }
}

void memportimpl::tick(ch_cycle t) {
  CH_UNUSED(t);
  if (wdata_id_ != -1) {
    memimpl* const mem = dynamic_cast<memimpl*>(srcs_[0].get_impl());
    mem->value_.write((uint8_t*)q_next_.get_words(),
                      a_next_ * mem->data_width_,
                      mem->data_width_);
  }  
}

void memportimpl::tick_next(ch_cycle t) {
  if (wdata_id_ != -1) {
    a_next_ = srcs_[addr_id_].eval(t).get_word(0);
    q_next_ = srcs_[wdata_id_].eval(t);
  }
}

const bitvector& memportimpl::eval(ch_cycle t) {  
  if (ctime_ != t) {
    ctime_ = t;
    memimpl* const mem = dynamic_cast<memimpl*>(srcs_[0].get_impl());
    uint32_t addr = srcs_[addr_id_].eval(t).get_word(0);    
    mem->value_.read((uint8_t*)value_.get_words(),
                     addr * mem->data_width_,
                     mem->data_width_);
  }
  return value_;
}

void memportimpl::print_vl(std::ostream& out) const {
  CH_UNUSED(out);
  CH_TODO();
}
///////////////////////////////////////////////////////////////////////////////

memory::memory(uint32_t data_width, uint32_t addr_width, bool writeEnable) {
  impl_ = new memimpl(ctx_curr(), data_width, addr_width, writeEnable);
}

void memory::load(const std::vector<uint8_t>& data) {
  impl_->load(data);
}

void memory::load(const std::string& file) {
  impl_->load(file);
}

lnodeimpl* memory::read(const lnode& addr) const {
  return impl_->read(addr);
}

void memory::write(const lnode& addr, const lnode& data) {
  impl_->write(addr, data);
}
