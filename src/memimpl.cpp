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
                 const std::vector<uint8_t>& init_data)
  : ioimpl(ctx, type_mem, data_width * num_items)
  , data_width_(data_width)
  , num_items_(num_items)
  , cd_(nullptr)
  , has_initdata_(!init_data.empty()) {
  if (write_enable) {
    lnode clk(ctx->get_clk());
    cd_ = ctx->create_cdomain({clock_event(clk, EDGE_POS)});
    cd_->add_use(this);
    srcs_.emplace_back(clk);
  }
  if (has_initdata_) {
    assert(8 * init_data.size() >= value_.get_size());
    value_.write(0, init_data.data(), init_data.size(), 0, value_.get_size());
  }
}

memimpl::~memimpl() {
  // detach connected ports for cleanup
  while (!ports_.empty()) {
    auto impl = dynamic_cast<memportimpl*>(ports_.front().get_impl());
    impl->detach();
  }
  if (cd_) {
    cd_->remove_use(this);
  }
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

void memimpl::remove(memportimpl* port) {
  for (auto it = ports_.begin(), end = ports_.end(); it != end; ++it) {
    if (it->get_id() == port->get_id()) {
      ports_.erase(it);
      break;
    }
  }
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
  : ioimpl(ctx, type_memport, mem->get_data_width())
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

memportimpl::~memportimpl() {
  this->detach();
}

void memportimpl::detach() {
  if (mem_idx_ != -1) {
    auto mem = dynamic_cast<memimpl*>(srcs_[mem_idx_].get_impl());
    mem->remove(this);
    mem_idx_ = -1;
  }
}

void memportimpl::write(const lnode& data) {
  if (wdata_idx_ == -1) {
    // add write port to memory sources to enforce DFG dependencies
    memimpl* mem = dynamic_cast<memimpl*>(srcs_[mem_idx_].get_impl());
    mem->get_srcs().emplace_back(this);

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
    mem->get_value().write(a_next_ * mem->get_data_width(),
                           q_next_.get_words(),
                           CH_CEILDIV(q_next_.get_size(), 8),
                           0,
                           mem->get_data_width());
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
    mem->get_value().read(0,
                          value_.get_words(),
                          CH_CEILDIV(value_.get_size(), 8),
                          addr * mem->get_data_width(),
                          mem->get_data_width());
  }
  return value_;
}

///////////////////////////////////////////////////////////////////////////////

memory::memory(uint32_t data_width,
               uint32_t num_items,
               bool writeEnable,
               const std::vector<uint8_t>& init_data) {
  CH_CHECK(!ctx_curr()->conditional_enabled(), "memory objects cannot be nested inside a conditional block");
  impl_ = ctx_curr()->createNode<memimpl>(data_width, num_items, writeEnable, init_data);
}

const lnode& memory::get_port(const lnode& addr) const {
  return impl_->get_port(addr);
}

///////////////////////////////////////////////////////////////////////////////

void mem_buffer::write(uint32_t dst_offset,
                       const lnode& data,
                       uint32_t src_offset,
                       uint32_t length) {
  assert(0 == src_offset && (dst_offset + length) <= size_);
  auto port = dynamic_cast<memportimpl*>(value_.get_impl());
  assert(port);

  // if partial write, use masking
  if (length != size_) {
    // build write mask
    bitvector one(size_, 1), tmp1(size_), tmp2(size_);
    Sll(tmp1, one, length);
    Sub(tmp2, tmp1, one);

    // resize source
    lnode zero(bitvector(size_ - data.get_size(), 0));
    auto resized_data = data.get_ctx()->createNode<proxyimpl>(size_);
    resized_data->add_source(0, data);
    resized_data->add_source(data.get_size(), zero);
    auto lhs = createAluNode(alu_and, resized_data, tmp2);
    lhs = createAluNode(alu_sll, lhs, bitvector(size_, dst_offset));
    Sll(tmp1, tmp2, dst_offset);
    Inv(tmp2, tmp1);
    auto rhs = createAluNode(alu_and, port, tmp2);
    auto dst = createAluNode(alu_or, lhs, rhs);
    port->write(dst);
  } else {
    port->write(data);
  }
}

void mem_buffer::move(const lnode& data) {
  this->write(0, data, 0, size_);
}
