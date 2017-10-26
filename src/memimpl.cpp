#include "memimpl.h"
#include "mem.h"
#include "context.h"

using namespace ch::internal;

memimpl::memimpl(context* ctx,
                 uint32_t data_width,
                 uint32_t addr_width,
                 bool write_enable)
  : ioimpl(ctx, type_mem, data_width << addr_width)
  , data_width_(data_width)
  , addr_width_(addr_width)
  , cd_(nullptr)
  , has_initdata_(false) {
  if (write_enable) {
    lnode clk(ctx->get_clk());
    cd_ = ctx->create_cdomain({clock_event(clk, EDGE_POS)});
    cd_->add_use(this);
    srcs_.emplace_back(clk);
  }
}

memimpl::~memimpl() {
  if (cd_) {
    cd_->remove_use(this);
  }
}

void memimpl::load(const std::vector<uint8_t>& init_data) {
  assert(8 * init_data.size() >= value_.get_size());
  value_.write(0, init_data.data(), init_data.size(), 0, value_.get_size());
  has_initdata_ = true;
}

void memimpl::load(const std::string& init_file) {
  std::ifstream in(init_file, std::ios::binary);
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
  has_initdata_ = true;
}

lnode& memimpl::get_port(const lnode& addr) {
  for (auto& port : ports_) {
    auto impl = dynamic_cast<memportimpl*>(port.get_impl());
    if (impl->get_addr().get_id() == addr.get_id())
      return port;
  }
  auto impl = ctx_->createNode<memportimpl>(this, addr);
  ports_.emplace_back(impl);
  return ports_.back();
}

void memimpl::tick(ch_tick t) {    
  for (auto& port : ports_) {
    auto impl = dynamic_cast<memportimpl*>(port.get_impl());
    impl->tick(t);
  }
}

void memimpl::tick_next(ch_tick t) {
  for (auto& port : ports_) {
    auto impl = dynamic_cast<memportimpl*>(port.get_impl());
    impl->tick_next(t);
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

memportimpl::memportimpl(context* ctx, memimpl* mem, const lnode& addr)
  : ioimpl(ctx, type_memport, mem->data_width_)
  , a_next_(0)
  , mem_idx_(-1)
  , addr_idx_(-1)
  , wdata_idx_(-1)
  , tick_(~0ull) {
  mem_idx_ = srcs_.size();
  srcs_.emplace_back(mem);

  addr_idx_ = srcs_.size();
  srcs_.emplace_back(addr);
}

void memportimpl::write(const lnode& data) {
  if (wdata_idx_ == -1) {
    // add write port to memory sources to enforce DFG dependencies
    memimpl* mem = dynamic_cast<memimpl*>(srcs_[mem_idx_].get_impl());
    mem->srcs_.emplace_back(this);

    // port source initially points to memory content
    wdata_idx_ = srcs_.size();
    srcs_.emplace_back(this);
  }
  srcs_[wdata_idx_].write(0, data, 0, data.get_size(), this->get_size());
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
  impl_ = ctx_curr()->createNode<memimpl>(data_width, addr_width, writeEnable);
}

void memory::load(const std::vector<uint8_t>& init_data) {
  impl_->load(init_data);
}

void memory::load(const std::string& init_file) {
  impl_->load(init_file);
}

const lnode& memory::get_port(const lnode& addr) const {
  return impl_->get_port(addr);
}

///////////////////////////////////////////////////////////////////////////////

void mem_buffer::write(uint32_t dst_offset,
                       const lnode& data,
                       uint32_t src_offset,
                       uint32_t length) {
  CH_CHECK(0 == dst_offset
        && 0 == src_offset
        && length == size_, "partial memory update not supported");
  auto port = dynamic_cast<memportimpl*>(value_.get_impl());
  assert(port);
  port->write(data);
}
