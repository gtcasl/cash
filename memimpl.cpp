#include <fstream>
#include "memimpl.h"
#include "mem.h"
#include "context.h"

using namespace std;
using namespace chdl_internal;

memimpl::memimpl(uint32_t data_width, uint32_t addr_width, bool sync_read, bool write_enable) 
  : m_syncRead(sync_read)
  , m_writeEnable(write_enable) {
  m_content.resize(1 << addr_width);
  for (auto& line : m_content) {
    line.resize(data_width);
  }
  
  // register clock domain
  if (sync_read || write_enable) {
    context* ctx = ctx_curr();        
    m_cd = ctx->create_cdomain({clock_event(ctx->get_clk(), EDGE_POS)});
    m_cd->add_use(this);
    m_cd->release();
  }
}

memimpl::memimpl(uint32_t data_width, uint32_t addr_width, bool sync_read, bool write_enable, const std::string& init_file)
  : memimpl(data_width, addr_width, sync_read, write_enable) {  
  uint32_t a = 0, i = 0;
  ifstream in(init_file.c_str());  
  while (in) {
    uint32_t value;
    in >> hex >> value;
    for (uint32_t j = 0; j < 32; ++j) {
      m_content[a].set_bit(i++, value & 1);
      value >>= 1;
      if (i == data_width) {
        i = 0;
        ++a;
        break;
      }
    }
    if (a == (1 << addr_width))
      break;
  }
  in.close();
}

memimpl::memimpl(uint32_t data_width, uint32_t addr_width, bool sync_read, bool write_enable, const std::vector<uint32_t>& init_data)
  : memimpl(data_width, addr_width, sync_read, write_enable) {  
  uint32_t a = 0, i = 0;
  for (uint32_t value : init_data) {
    for (uint32_t j = 0; j < 32; ++j) {
      m_content[a].set_bit(i++, value & 1);
      value >>= 1;
      if (i == data_width) {
        i = 0;
        ++a;
        break;
      }
    }
    if (a == (1 << addr_width))
      break;
  }
}

memimpl::~memimpl() {
  if (m_cd) {
    m_cd->remove_use(this);
  }
}

memportimpl* memimpl::read(const ch_node& addr) {
  return this->get_port(addr);
}

void memimpl::write(const ch_node& addr, const ch_node& value, const ch_node& enable) {
  memportimpl* port = this->get_port(addr);
  port->write(value, enable);
}

memportimpl* memimpl::get_port(const ch_node& addr) {
  memportimpl* port = nullptr; 
  for (auto item : m_ports) {
    if (item->m_srcs[0].get_id() == addr.get_id()) {
      port = item;
      break;
    }
  }
  if (port == nullptr) {
    port = new memportimpl(this, addr);
    m_ports.push_back(port);
  }
  return port;
}

void memimpl::tick(ch_cycle t) {    
  for (auto& port : m_ports) {
    port->tick(t);
  }
}

void memimpl::tick_next(ch_cycle t) {
  for (auto& port : m_ports) {
    port->tick_next(t);
  }
}

void memimpl::print(ostream& out) const {
  TODO();
}

void memimpl::print_vl(ostream& out) const {
  TODO();  
}

///////////////////////////////////////////////////////////////////////////////

memportimpl::memportimpl(memimpl* mem, const ch_node& addr)
    : nodeimpl(addr.get_ctx(), mem->m_content[0].get_size())
    , m_mem(mem)
    , m_writeEnable(false)
    , m_addr(0)
    , m_do_write(false)
    , m_ctime(~0ull)
{
  mem->add_ref();
  m_srcs.push_back(addr); // idx=0 
  if (mem->m_cd) {
    const ch_node& clk = mem->m_cd->get_sensitivity_list()[0].get_signal();
    m_srcs.push_back(clk); // idx=1
  }
}

memportimpl::~memportimpl() {
  m_mem->release();
}

void memportimpl::write(const ch_node& value, const ch_node& enable) {
  m_srcs.push_back(value); // idx=2
  m_srcs.push_back(enable); // idx=3
  m_writeEnable = true;
}

void memportimpl::tick(ch_cycle t) {
  if (m_do_write) {
    m_mem->m_content[m_addr] = m_wrdata;
  }  
  if (m_mem->m_syncRead) {
    m_rddata = m_mem->m_content[m_addr];    
  }
}

void memportimpl::tick_next(ch_cycle t) {
  m_addr = m_srcs[0].eval(t).get_word(0);
  if (m_writeEnable) {
    m_do_write = m_srcs[3].eval(t).get_bit(0);
    if (m_do_write) {    
      m_wrdata = m_srcs[2].eval(t);
    }
  }
}

const bitvector& memportimpl::eval(ch_cycle t) {  
  if (m_ctime != t) {
    m_ctime = t;
    m_value = m_mem->m_syncRead ? m_rddata :
      m_mem->m_content[m_srcs[0].eval(t).get_word(0)];
  }
  return m_value;
}

void memportimpl::print(std::ostream& out) const {
  TODO();
}

void memportimpl::print_vl(std::ostream& out) const {
  TODO();
}

///////////////////////////////////////////////////////////////////////////////

memory::memory(uint32_t data_width, uint32_t addr_width, bool syncRead, bool writeEnable) {
  m_impl = new memimpl(data_width, addr_width, syncRead, writeEnable);
}

memory::memory(uint32_t data_width, uint32_t addr_width, bool syncRead, bool writeEnable, const std::string& init_file) {
  m_impl = new memimpl(data_width, addr_width, syncRead, writeEnable, init_file);
}

memory::memory(uint32_t data_width, uint32_t addr_width, bool syncRead, bool writeEnable, const std::vector<uint32_t>& init_data) {
  m_impl = new memimpl(data_width, addr_width, syncRead, writeEnable, init_data);
}

memory::~memory() {
  if (m_impl)
    m_impl->release();
}

ch_node memory::read(const ch_node& addr) const {
  return ch_node(m_impl->read(addr));
}

void memory::write(const ch_node& addr, const ch_node& value, const ch_node& enable) {
  m_impl->write(addr, value, enable);
}
