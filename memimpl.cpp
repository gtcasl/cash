#include <fstream>
#include "memimpl.h"
#include "mem.h"
#include "context.h"

using namespace std;
using namespace chdl_internal;

memimpl::memimpl(uint32_t data_width, uint32_t addr_width, 
                 bool sync_read, bool write_enable) 
  : m_content(1 << addr_width, bitvector(data_width))
  , m_syncRead(sync_read)
  , m_writeEnable(write_enable) {  
  // register clock domain
  if (sync_read || write_enable) {
    context* ctx = ctx_curr();        
    m_cd = ctx->create_cdomain({clock_event(ctx->get_clk(), EDGE_POS)});
    m_cd->add_use(this);
    m_cd->release();
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
      m_content[a][i++] = (value & 1) != 0;
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

memimpl::memimpl(uint32_t data_width, uint32_t addr_width, 
                 bool sync_read, bool write_enable, 
                 const std::vector<uint32_t>& init_data)
  : memimpl(data_width, addr_width, sync_read, write_enable) {  
  uint32_t a = 0, i = 0;
  for (uint32_t value : init_data) {
    for (uint32_t j = 0; j < 32; ++j) {
      m_content[a][i++] = (value & 1) != 0;
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

memportimpl* memimpl::read(const lnode& addr) {
  return this->get_port(addr);
}

void memimpl::write(const lnode& addr, const lnode& value, const lnode& enable) {
  memportimpl* port = this->get_port(addr);
  port->write(value, enable);
}

memportimpl* memimpl::get_port(const lnode& addr) {
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
  TODO("Not yet implemented!");
}

void memimpl::print_vl(ostream& out) const {
  TODO("Not yet implemented!");  
}

///////////////////////////////////////////////////////////////////////////////

memportimpl::memportimpl(memimpl* mem, const lnode& addr)
    : lnodeimpl("memport", addr.get_ctx(), mem->m_content[0].get_size())
    , m_mem(mem)
    , m_writeEnable(false)
    , m_addr(0)
    , m_do_write(false)
    , m_ctime(~0ull)
{
  mem->acquire();
  m_srcs.push_back(addr); // idx=0 
  if (mem->m_cd) {
    const lnode& clk = mem->m_cd->get_sensitivity_list()[0].get_signal();
    m_srcs.emplace_back(clk); // idx=1
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

void memportimpl::write(const lnode& value, const lnode& enable) {
  // positions 0 & 1 are used by addr and clk nodes respectively
  // local port write source nodes have fixed position (2, 3)
  // write source nodes from other ports are appended starting at 
  // index 2 if local port is not writeenable otherwise index 4
  if (m_writeEnable) {
    // replace local port sources
    m_srcs[2] = value;
    m_srcs[3] = enable;
  } else {
    // add local port sources
    if (m_srcs.size() > 2) {
      // push write dependency nodes to the right
      m_srcs.insert(m_srcs.begin() + 2, value); 
      m_srcs.insert(m_srcs.begin() + 3, enable);
    } else {
      assert(m_srcs.size() == 2);
      m_srcs.push_back(value);
      m_srcs.push_back(enable);
    }        
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
  m_addr = m_srcs[0].eval(t).get_word(0);
  if (m_writeEnable) {
    m_do_write = m_srcs[3].eval(t)[0];
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

void memportimpl::print_vl(std::ostream& out) const {
  TODO("Not yet implemented!");
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

lnode memory::read(const lnode& addr) const {
  return lnode(m_impl->read(addr));
}

void memory::write(const lnode& addr, const lnode& value, const lnode& enable) {
  m_impl->write(addr, value, enable);
}
