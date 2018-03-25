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
    cd_ = ctx->create_cdomain({clock_event(clk, true)});
    cd_->add_use(this);
    srcs_.emplace_back(clk);
  }
  if (has_initdata_) {
    assert(8 * init_data.size() >= value_.get_size());
    value_.write(0, init_data.data(), init_data.size(), 0, value_.get_size());
  }
}

memimpl::~memimpl() {
  // detach ports
  while (!ports_.empty()) {
    dynamic_cast<memportimpl*>(ports_.front().get_impl())->detach();
  }
  if (cd_) {
    cd_->remove_use(this);
  }
}

void memimpl::remove_port(memportimpl* port) {
  for (auto it = ports_.begin(), end = ports_.end(); it != end; ++it) {
    if (it->get_id() == port->get_id()) {
      ports_.erase(it);
      break;
    }
  }
}

lnode& memimpl::get_port(const lnode& addr) {
  for (auto& port : ports_) {
    auto impl = dynamic_cast<memportimpl*>(port.get_impl());
    if (impl->get_addr().get_id() == addr.get_id()) {
      return port;
    }
  }
  auto impl = ctx_->createNode<memportimpl>(this, ports_.size(), addr);
  ports_.emplace_back(impl);
  return ports_.back();
}

void memimpl::tick(ch_tick t) {
  for (auto& port : ports_) {
    dynamic_cast<memportimpl*>(port.get_impl())->tick(t);
  }
}

void memimpl::tick_next(ch_tick t) {
  for (auto& port : ports_) {
    dynamic_cast<memportimpl*>(port.get_impl())->tick_next(t);
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
  if (level == 2) {
    out << " = " << value_;
  }
}

///////////////////////////////////////////////////////////////////////////////

memportimpl::memportimpl(context* ctx, memimpl* mem, unsigned index, const lnode& addr)
  : ioimpl(ctx, type_memport, mem->get_data_width())
  , index_(index)
  , read_enable_(false)
  , a_next_(0)  
  , wdata_idx_(-1)
  , wenable_idx_(-1)
  , dirty_(false)
  , tick_(~0ull) {
  srcs_.emplace_back(mem);
  srcs_.emplace_back(addr);
}

memportimpl::~memportimpl() {
  this->detach();
}

void memportimpl::detach() {
  if (!srcs_[0].is_empty()) {
    dynamic_cast<memimpl*>(srcs_[0].get_impl())->remove_port(this);
    srcs_[0].clear();
  }
}


void memportimpl::read() {
  read_enable_ = true;
}

void memportimpl::write(const lnode& data) {
  if (wdata_idx_ == -1) {
    // add write port to memory sources to enforce DFG dependencies
    memimpl* mem = dynamic_cast<memimpl*>(srcs_[0].get_impl());
    mem->get_srcs().emplace_back(this);
  }
  // add data source
  wdata_idx_ = this->add_src(wdata_idx_, data);
}

void memportimpl::write(const lnode& data, const lnode& enable) {
  // add data source
  this->write(data);

  // add enable predicate
  wenable_idx_ = this->add_src(wenable_idx_, enable);
}

void memportimpl::tick(ch_tick t) {
  CH_UNUSED(t);
  if (dirty_) {
    auto mem = dynamic_cast<memimpl*>(srcs_[0].get_impl());
    auto data_width = mem->get_data_width();
    mem->get_value().write(a_next_ * data_width,
                           q_next_.get_words(),
                           q_next_.get_cbsize(),
                           0,
                           data_width);
  }
}

void memportimpl::tick_next(ch_tick t) {
  if (wdata_idx_ != -1) {
    // synchronous memory write
    dirty_ = (wenable_idx_ != -1) ? srcs_[wenable_idx_].eval(t).get_word(0) : true;
    if (dirty_) {
      a_next_ = srcs_[1].eval(t).get_word(0);
      q_next_ = srcs_[wdata_idx_].eval(t);
    }
  }
}

const bitvector& memportimpl::eval(ch_tick t) {  
  if (tick_ != t) {
    tick_ = t;
    // asynchronous memory read
    auto mem = dynamic_cast<memimpl*>(srcs_[0].get_impl());
    auto data_width = mem->get_data_width();
    uint32_t addr = srcs_[1].eval(t).get_word(0);
    mem->get_value().read(0,
                          value_.get_words(),
                          value_.get_cbsize(),
                          addr * data_width,
                          data_width);
  }
  return value_;
}

///////////////////////////////////////////////////////////////////////////////

memory::memory(uint32_t data_width,
               uint32_t num_items,
               bool write_enable,
               const std::vector<uint8_t>& init_data) {
  CH_CHECK(!ctx_curr()->conditional_enabled(), "memory objects cannot be nested inside a conditional block");
  impl_ = ctx_curr()->createNode<memimpl>(data_width, num_items, write_enable, init_data);
}

const lnode& memory::read(const lnode& addr) const {
  auto& port = impl_->get_port(addr);
  dynamic_cast<memportimpl*>(port.get_impl())->read();
  return port;
}

void memory::write(const lnode& addr, const lnode& value) {
  auto& port = impl_->get_port(addr);
  dynamic_cast<memportimpl*>(port.get_impl())->write(value);
}

void memory::write(const lnode& addr, const lnode& value, const lnode& enable) {
  auto& port = impl_->get_port(addr);
  dynamic_cast<memportimpl*>(port.get_impl())->write(value, enable);
}
