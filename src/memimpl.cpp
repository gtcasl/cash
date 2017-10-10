#include "memimpl.h"
#include "mem.h"
#include "context.h"

using namespace ch::internal;

memimpl::memimpl(context* ctx,
                 uint32_t data_width,
                 uint32_t addr_width,
                 bool write_enable)
  : ioimpl(type_mem, ctx, data_width << addr_width)
  , data_width_(data_width)
  , addr_width_(addr_width)
  , wr_ports_offset_(0)
  , cd_(nullptr)
  , initialized_(false) {
  if (write_enable) {
    lnode clk(ctx->get_clk());
    cd_ = ctx->create_cdomain({clock_event(clk, EDGE_POS)});
    cd_->add_use(this);
    srcs_.emplace_back(clk);
    wr_ports_offset_ = 1;
  }
}

memimpl::~memimpl() {
  if (cd_) {
    cd_->remove_use(this);
  }
}

void memimpl::load(const std::vector<uint8_t>& data) {
  assert(8 * data.size() >= value_.get_size());
  value_.write(0, data.data(), data.size(), 0, value_.get_size());
  initialized_ = true;
}

void memimpl::load(const char* file) {
  std::ifstream in(file, std::ios::binary);
  uint32_t size = value_.get_size();
  uint32_t offset = 0;

  while ((size - offset) >= 64) {
    uint64_t x;
    in >> x;
    value_.write(offset, &x, sizeof(x), 0, 64);
    offset += 64;
  }

  while (offset < size) {
    uint8_t x;
    in >> x;
    int len = std::min<int>(size - offset, 8);
    value_.write(offset, &x, sizeof(x), 0, len);
    offset += len;
  }

  in.close();
  initialized_ = true;
}

lnode& memimpl::read(const lnode& addr) {
  return this->get_port(addr, false);
}

void memimpl::write(const lnode& addr, const nodelist& in) {
  auto& port = this->get_port(addr, true);
  auto impl = dynamic_cast<memportimpl*>(port.get_impl());
  impl->write(in);
}

lnode& memimpl::get_port(const lnode& addr, bool writable) {
  for (auto& port : ports_) {
    auto impl = dynamic_cast<memportimpl*>(port.get_impl());
    if (impl->get_addr() == addr) {
      if (writable && !impl->is_writable()) {
        impl->set_writable(true);
        srcs_.emplace_back(impl);
      }
      return port;
    }
  }
  auto impl = new memportimpl(this, addr, writable);
  ports_.emplace_back(impl);
  if (writable) {
    srcs_.emplace_back(impl);
  }
  return ports_.back();
}

void memimpl::tick(ch_tick t) {    
  for (uint32_t i = wr_ports_offset_, n = srcs_.size(); i < n; ++i) {
    auto port = dynamic_cast<memportimpl*>(srcs_[i].get_impl());
    port->tick(t);
  }
}

void memimpl::tick_next(ch_tick t) {
  for (uint32_t i = wr_ports_offset_, n = srcs_.size(); i < n; ++i) {
    auto port = dynamic_cast<memportimpl*>(srcs_[i].get_impl());
    port->tick_next(t);
  }
}

// LCOV_EXCL_START
const bitvector& memimpl::eval(ch_tick t) {
  CH_UNUSED(t);
  CH_ABORT("invalid call");
}
// LCOV_EXCL_STOP

void memimpl::print(std::ostream& out, uint32_t level) const {
  CH_UNUSED(level);
  out << "#" << id_ << " <- " << this->get_type() << value_.get_size();
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

///////////////////////////////////////////////////////////////////////////////

memportimpl::memportimpl(memimpl* mem, const lnode& addr, bool writable)
  : ioimpl(type_memport, mem->get_ctx(), mem->data_width_)
  , a_next_(0)
  , mem_idx_(-1)
  , addr_idx_(-1)
  , wdata_idx_(-1)
  , writable_(writable)
  , tick_(~0ull) {
  mem_idx_ = srcs_.size();
  srcs_.emplace_back(mem);

  addr_idx_ = srcs_.size();
  srcs_.emplace_back(addr);
}

void memportimpl::write(const nodelist& in) {
  assert(writable_);
  if (wdata_idx_ == -1) {
    wdata_idx_ = srcs_.size();
    srcs_.emplace_back(this);
  }
  srcs_[wdata_idx_].write_data(0, in, 0, in.get_size(), this->get_size());
}

void memportimpl::tick(ch_tick t) {
  CH_UNUSED(t);
  if (wdata_idx_ != -1) {
    auto mem = dynamic_cast<memimpl*>(srcs_[mem_idx_].get_impl());
    mem->value_.write(a_next_ * mem->data_width_,
                      q_next_.get_words(),
                      CH_CEILDIV(q_next_.get_size(), 8),
                      0,
                      mem->data_width_);
  }  
}

void memportimpl::tick_next(ch_tick t) {
  if (wdata_idx_ != -1) {
    a_next_ = srcs_[addr_idx_].eval(t).get_word(0);
    q_next_ = srcs_[wdata_idx_].eval(t);
  }
}

const bitvector& memportimpl::eval(ch_tick t) {  
  if (tick_ != t) {
    tick_ = t;
    auto mem = dynamic_cast<memimpl*>(srcs_[mem_idx_].get_impl());
    uint32_t addr = srcs_[addr_idx_].eval(t).get_word(0);    
    mem->value_.read(0,
                     value_.get_words(),
                     CH_CEILDIV(value_.get_size(), 8),
                     addr * mem->data_width_,
                     mem->data_width_);
  }
  return value_;
}

///////////////////////////////////////////////////////////////////////////////

memory::memory(uint32_t data_width, uint32_t addr_width, bool writeEnable) {
  CH_CHECK(!ctx_curr()->conditional_enabled(), "memory objects cannot be nested inside a conditional block");
  impl_ = new memimpl(ctx_curr(), data_width, addr_width, writeEnable);
}

void memory::load(const std::vector<uint8_t>& data) {
  impl_->load(data);
}

void memory::load(const char* file) {
  impl_->load(file);
}

lnode& memory::read(const lnode& addr) const {
  return impl_->read(addr);
}

void memory::write(const lnode& addr,
                   size_t dst_offset,
                   const nodelist& in,
                   size_t src_offset,
                   size_t length) {
  assert(0 == dst_offset);
  if (0 == src_offset) {
    impl_->write(addr, in);
  } else {
    nodelist in2(length, true);
    for (const auto& slice : in) {
      if (src_offset < slice.length) {
        uint32_t len = std::min(slice.length - src_offset, length);
        in2.push(slice.src, slice.offset + src_offset, len);
        length -= len;
        if (0 == length)
          break;
        src_offset = slice.length;
      }
      src_offset -= slice.length;
    }
    impl_->write(addr, in2);
  }
}
