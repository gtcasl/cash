#include "memimpl.h"
#include "mem.h"
#include "context.h"

using namespace std;
using namespace chdl_internal;

memimpl::memimpl(uint32_t data_width, uint32_t addr_width, 
                 bool sync_read, bool write_enable) 
  : m_content(1 << addr_width, bitvector(data_width))
  , m_syncRead(sync_read)
  , m_writeEnable(write_enable)
  , m_cd(nullptr) {  
  // register clock domain
  if (sync_read || write_enable) {
    context* ctx = ctx_curr();        
    m_cd = ctx->create_cdomain({clock_event(ctx->get_clk(), EDGE_POS)});
    m_cd->add_use(this);
  }
}

memimpl::memimpl(uint32_t data_width, uint32_t addr_width, 
                 bool sync_read, bool write_enable, 
                 const std::string& init_file)
  : memimpl(data_width, addr_width, sync_read, write_enable) {  
  uint32_t a = 0, i = 0;
  ifstream in(init_file.c_str());  
  while (in) {
    uint32_t value;
    in >> hex >> value;
    for (uint32_t j = 0; j < 32; ++j) {
      m_content[a][i++] = (value & (1 << j)) != 0;
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

memimpl::memimpl(uint32_t data_width, uint32_t addr_width, 
                 bool sync_read, bool write_enable, 
                 const std::vector<uint32_t>& init_data)
  : memimpl(data_width, addr_width, sync_read, write_enable) {  
  uint32_t a = 0, i = 0;
  for (uint32_t value : init_data) {
    for (uint32_t j = 0; j < 32; ++j) {
      m_content[a][i++] = (value & (1 << j)) != 0;
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

memportimpl* memimpl::read(lnodeimpl* addr) {
  return this->get_port(addr);
}

void memimpl::write(lnodeimpl* addr, lnodeimpl* data, lnodeimpl* enable) {
  memportimpl* port = this->get_port(addr);
  port->write(data, enable);
}

memportimpl* memimpl::get_port(lnodeimpl* addr) {
  memportimpl* port = nullptr; 
  for (memportimpl* item : m_ports) {
    if (item == addr) {
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
  TODO("Not yet implemented!");
}

void memimpl::print_vl(ostream& out) const {
  TODO("Not yet implemented!");  
}

///////////////////////////////////////////////////////////////////////////////

memportimpl::memportimpl(memimpl* mem, lnodeimpl* addr)
    : lnodeimpl("memport", addr->get_ctx(), mem->m_content[0].get_size())
    , m_mem(mem)
    , m_writeEnable(false)
    , m_addr(0)
    , m_do_write(false)
    , m_addr_id(-1)
    , m_clk_id(-1)
    , m_wdata_id(-1)
    , m_wenable_id(-1)
    , m_ctime(~0ull)
{
  mem->acquire();
  m_addr_id = m_srcs.size();
  m_srcs.emplace_back(addr);
  if (mem->m_cd) {
    lnodeimpl* clk = mem->m_cd->get_sensitivity_list()[0].get_signal();
    m_clk_id = m_srcs.size();
    m_srcs.emplace_back(clk);
  } 
  // add dependency from all write ports
  for (memportimpl* port : m_mem->m_ports) {
    if (port != this && port->m_writeEnable) {
      this->m_srcs.emplace_back(port);
    }
  }
}

memportimpl::~memportimpl() {
  m_mem->release();
}

void memportimpl::write(lnodeimpl* data, lnodeimpl* enable) {
  if (m_wdata_id == -1) {
    m_wdata_id = m_srcs.size();
    m_srcs.emplace_back(data);
  } else {
    m_srcs[m_wdata_id] = data;
  }
  
  if (m_wenable_id == -1) {
    m_wenable_id = m_srcs.size();
    m_srcs.emplace_back(enable);
  } else {
    m_srcs[m_wenable_id] = enable;
  }
  
  if (!m_writeEnable) {
    // add write dependency to all ports
    for (memportimpl* port : m_mem->m_ports) {
      if (port != this)
        port->m_srcs.emplace_back(this);
    }    
    m_writeEnable = true;
  }    
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
  m_addr = m_srcs[m_addr_id].eval(t).get_word(0);
  if (m_writeEnable) {
    m_do_write = m_srcs[m_wenable_id].eval(t)[0];
    if (m_do_write) {    
      m_wrdata = m_srcs[m_wdata_id].eval(t);
    }
  }
}

const bitvector& memportimpl::eval(ch_cycle t) {  
  if (m_ctime != t) {
    m_ctime = t;
    m_value = m_mem->m_syncRead ? m_rddata :
      m_mem->m_content[m_srcs[m_addr_id].eval(t).get_word(0)];
  }
  return m_value;
}

void memportimpl::print_vl(std::ostream& out) const {
  TODO("Not yet implemented!");
}

///////////////////////////////////////////////////////////////////////////////

memory::memory(uint32_t data_width, uint32_t addr_width, bool syncRead, bool writeEnable) {
  m_impl = new memimpl(data_width, addr_width, syncRead, writeEnable);
  m_impl->acquire();
}

memory::memory(uint32_t data_width, uint32_t addr_width, bool syncRead, bool writeEnable, const std::string& init_file) {
  m_impl = new memimpl(data_width, addr_width, syncRead, writeEnable, init_file);
  m_impl->acquire();
}

memory::memory(uint32_t data_width, uint32_t addr_width, bool syncRead, bool writeEnable, const std::vector<uint32_t>& init_data) {
  m_impl = new memimpl(data_width, addr_width, syncRead, writeEnable, init_data);
  m_impl->acquire();
}

memory::~memory() {
  if (m_impl)
    m_impl->release();
}

lnodeimpl* memory::read(lnodeimpl* addr) const {
  return m_impl->read(addr);
}

void memory::write(lnodeimpl* addr, lnodeimpl* data, lnodeimpl* enable) {
  m_impl->write(addr, data, enable);
}
