#include "memimpl.h"
#include "mem.h"
#include "context.h"

using namespace std;
using namespace chdl_internal;

memimpl::memimpl(context* ctx, uint32_t data_width, uint32_t addr_width, bool write_enable) 
  : lnodeimpl(op_mem, ctx, 0)
  , m_content(1 << addr_width, bitvector(data_width))
  , m_ports_offset(0)
  , m_cd(nullptr) {  
  if (write_enable) {
    lnodeimpl* const clk = ctx->get_clk();
    m_cd = ctx->create_cdomain({clock_event(clk, EDGE_POS)});
    m_cd->add_use(this);
    m_srcs.emplace_back(clk);
    m_ports_offset = 1;
  }
}

// LCOV_EXCL_START
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
// LCOV_EXCL_END

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
  uint32_t max_addr   = m_content.size();  
  uint32_t num_words  = m_content[0].get_num_words();
  uint32_t data_width = m_content[0].get_size();
  uint32_t mask_bits  = data_width;
  uint32_t a = 0, w = 0, value;
  while (getdata(&value)) {
    uint32_t mask;
    if (mask_bits >= 32) {
      mask = 0xffffffff;
      mask_bits -= 32;
    } else {
      mask = (1 << mask_bits)-1;
      mask_bits = 0;
    }
    CHDL_CHECK(a < max_addr && w < num_words, "input value overflow");
    m_content[a].set_word(w++, value & mask);
    if (mask_bits == 0) {
      CHDL_CHECK((value & ~mask) == 0, "input value overflow");
      mask_bits = data_width;        
      w = 0;
      ++a;
    }
  }
}

memimpl::~memimpl() {
  if (m_cd) {
    m_cd->remove_use(this);
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
  for (uint32_t i = m_ports_offset, n = m_srcs.size(); i < n; ++i) {
    memportimpl* const item  = dynamic_cast<memportimpl*>(m_srcs[i].get_impl());
    if (item->get_addr() == addr) {
      port = item;
      break;
    }
  }
  if (port == nullptr) {
    port = new memportimpl(this, addr);
    if (writing) {
      m_srcs.emplace_back(port);
    }
  }
  return port;
}

void memimpl::tick(ch_cycle t) {    
  for (uint32_t i = m_ports_offset, n = m_srcs.size(); i < n; ++i) {
    memportimpl* const port = dynamic_cast<memportimpl*>(m_srcs[i].get_impl());
    port->tick(t);
  }
}

void memimpl::tick_next(ch_cycle t) {
  for (uint32_t i = m_ports_offset, n = m_srcs.size(); i < n; ++i) {
   memportimpl* const port = dynamic_cast<memportimpl*>(m_srcs[i].get_impl());
   port->tick_next(t);
  }
}

const bitvector& memimpl::eval(ch_cycle t) {
  //--
}

// LCOV_EXCL_START
void memimpl::print_vl(ostream& out) const {
  TODO("Not yet implemented!");
}
// LCOV_EXCL_END

///////////////////////////////////////////////////////////////////////////////

memportimpl::memportimpl(memimpl* mem, lnodeimpl* addr)
    : lnodeimpl(op_memport, addr->get_ctx(), mem->m_content[0].get_size())
    , m_a_next(0)
    , m_addr_id(-1)
    , m_wdata_id(-1)
    , m_ctime(~0ull) {
  m_srcs.emplace_back(mem);
  m_addr_id = m_srcs.size();
  m_srcs.emplace_back(addr);
}

void memportimpl::write(lnodeimpl* data) {
  // use explicit assignment to force conditionals resolution
  if (m_wdata_id == -1) {
    m_wdata_id = m_srcs.size();
    m_srcs.emplace_back(this);
  } 
  m_srcs[m_wdata_id] = data;
}

void memportimpl::tick(ch_cycle t) {
  if (m_wdata_id != -1) {
    memimpl* const mem = dynamic_cast<memimpl*>(m_srcs[0].get_impl());
    mem->m_content[m_a_next] = m_q_next;
  }  
}

void memportimpl::tick_next(ch_cycle t) {
  if (m_wdata_id != -1) {
    m_a_next = m_srcs[m_addr_id].eval(t).get_word(0);
    m_q_next = m_srcs[m_wdata_id].eval(t);
  }
}

const bitvector& memportimpl::eval(ch_cycle t) {  
  if (m_ctime != t) {
    m_ctime = t;
    uint32_t addr = m_srcs[m_addr_id].eval(t).get_word(0);
    memimpl* const mem = dynamic_cast<memimpl*>(m_srcs[0].get_impl());
    m_value = mem->m_content[addr];
  }
  return m_value;
}

// LCOV_EXCL_START
void memportimpl::print_vl(std::ostream& out) const {
  TODO("Not yet implemented!");
}
// LCOV_EXCL_END

///////////////////////////////////////////////////////////////////////////////

memory::memory(uint32_t data_width, uint32_t addr_width, bool writeEnable) {
  m_impl = new memimpl(ctx_curr(), data_width, addr_width, writeEnable);
}

memory::memory(uint32_t data_width, uint32_t addr_width, bool writeEnable, 
               const std::string& init_file) {
  m_impl = new memimpl(ctx_curr(), data_width, addr_width, writeEnable, init_file);
}

memory::memory(uint32_t data_width, uint32_t addr_width, bool writeEnable, 
               const std::vector<uint32_t>& init_data) {
  m_impl = new memimpl(ctx_curr(), data_width, addr_width, writeEnable, init_data);
}

lnodeimpl* memory::read(lnodeimpl* addr) const {
  return m_impl->read(addr);
}

void memory::write(lnodeimpl* addr, lnodeimpl* data) {
  m_impl->write(addr, data);
}
