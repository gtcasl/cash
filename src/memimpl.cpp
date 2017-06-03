#include "memimpl.h"
#include "mem.h"
#include "context.h"

using namespace std;
using namespace cash::detail;

memimpl::memimpl(context* ctx, uint32_t data_width, uint32_t addr_width, bool write_enable) 
  : lnodeimpl(op_mem, ctx, 0)
  , content_(1 << addr_width, bitvector(data_width))
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

memimpl::memimpl(context* ctx, uint32_t data_width, uint32_t addr_width, bool write_enable, 
                 const std::string& init_file)
  : memimpl(ctx, data_width, addr_width, write_enable) {  
  ifstream in(init_file.c_str());
  in.setf(std::ios_base::hex);
  this->load_data([&in](uint32_t* out)->bool {
    if (in.eof())
      return false;
    in >> *out;
    return true;
  });
  in.close();
}

memimpl::memimpl(context* ctx, uint32_t data_width, uint32_t addr_width, bool write_enable, 
                 const std::vector<uint32_t>& init_data)
  : memimpl(ctx, data_width, addr_width, write_enable) {  
  auto iter = init_data.begin(), iterEnd = init_data.end();
  this->load_data([&iter, &iterEnd](uint32_t* out)->bool {    
    if (iter == iterEnd)
      return false;
    *out = *iter++;
    return true;
  });
}

void memimpl::load_data(const std::function<bool(uint32_t* out)>& getdata) {
  uint32_t max_addr   = content_.size();  
  uint32_t num_words  = content_[0].get_num_words();
  uint32_t data_width = content_[0].get_size();
  uint32_t mask_bits  = data_width;
  uint32_t a = 0;
  uint32_t w = 0;
  uint32_t value;
  while (getdata(&value)) {
    uint32_t mask;
    if (mask_bits >= 32) {
      mask = 0xffffffff;
      mask_bits -= 32;
    } else {
      mask = (1 << mask_bits)-1;
      mask_bits = 0;
    }
    CH_CHECK(a < max_addr && w < num_words, "input value overflow");
    content_[a].set_word(w++, value & mask);
    if (0 == mask_bits) {
      CH_CHECK((value & ~mask) == 0, "input value overflow");
      mask_bits = data_width;        
      w = 0;
      ++a;
    }
  }
}

memimpl::~memimpl() {
  if (cd_) {
    cd_->remove_use(this);
  }
}

memportimpl* memimpl::read(lnodeimpl* addr) {
  return this->get_port(addr, false);
}

void memimpl::write(lnodeimpl* addr, lnodeimpl* data) {
  memportimpl* port = this->get_port(addr, true);
  port->write(data);  
}

memportimpl* memimpl::get_port(lnodeimpl* addr, bool writing) {
  memportimpl* port = nullptr; 
  for (uint32_t i = ports_offset_, n = srcs_.size(); i < n; ++i) {
    memportimpl* const item  = dynamic_cast<memportimpl*>(srcs_[i].get_impl());
    if (item->get_addr().get_impl() == addr) {
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

void memimpl::print_vl(ostream& out) const {
  CH_UNUSED(out);
  CH_TODO();
}

///////////////////////////////////////////////////////////////////////////////

memportimpl::memportimpl(memimpl* mem, lnodeimpl* addr)
  : lnodeimpl(op_memport, addr->get_ctx(), mem->content_[0].get_size())
  , a_next_(0)
  , addr_id_(-1)
  , wdata_id_(-1)
  , ctime_(~0ull) {
  srcs_.emplace_back(mem);
  addr_id_ = srcs_.size();
  srcs_.emplace_back(addr);
}

void memportimpl::write(lnodeimpl* data) {
  // use explicit assignment to force conditionals resolution
  if (wdata_id_ == -1) {
    wdata_id_ = srcs_.size();
    srcs_.emplace_back(this);
  }
  srcs_[wdata_id_] = data;
}

void memportimpl::tick(ch_cycle t) {
  CH_UNUSED(t);
  if (wdata_id_ != -1) {
    memimpl* const mem = dynamic_cast<memimpl*>(srcs_[0].get_impl());
    mem->content_[a_next_] = q_next_;
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
    value_ = mem->content_[addr];
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

memory::memory(uint32_t data_width, uint32_t addr_width, bool writeEnable, 
               const std::string& init_file) {
  impl_ = new memimpl(ctx_curr(), data_width, addr_width, writeEnable, init_file);
}

memory::memory(uint32_t data_width, uint32_t addr_width, bool writeEnable, 
               const std::vector<uint32_t>& init_data) {
  impl_ = new memimpl(ctx_curr(), data_width, addr_width, writeEnable, init_data);
}

lnodeimpl* memory::read(lnodeimpl* addr) const {
  return impl_->read(addr);
}

void memory::write(lnodeimpl* addr, lnodeimpl* data) {
  impl_->write(addr, data);
}
