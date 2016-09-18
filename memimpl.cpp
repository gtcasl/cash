#include <fstream>
#include <iomanip>
#include <random>
#include "litimpl.h"
#include "memimpl.h"
#include "mem.h"
#include "context.h"

using namespace std;
using namespace chdl_internal;

/*static uint32_t toUint(const vector<node>& v, ch_cycle t) {
  uint32_t r(0);
  for (unsigned i = 0; i < v.size(); ++i) {
    if (v[i].eval(t)) {
      r |= 1ul << i;
    }
  }
  return r;
}

// Load a hex file.
static void load_contents(vector<bool>& contents, unsigned stride, const string& init_file) {
  ifstream in(init_file.c_str());
  size_t i = 0;
  while (in) {
    unsigned long long val;
    in >> hex >> val;
    for (unsigned j = 0; j < stride; ++j) {
      if (i * stride + j < contents.size()) {
        contents[i * stride + j] = val & 1;
      }
      val >>= 1;
    }
    ++i;
  }

  // fill remaining bits
  for (size_t j = i * stride; j < contents.size(); ++j) {
    contents[j] = i % 2;
  }
}

memimpl::memimpl(context* ctx,
               const vector<node>& d,
               const vector<node>& da,
               const vector<vector<node>>& qa,
               const node& w, 
               bool rd_sync,
               const string& init_file)
    : m_w(w)    
    , m_d(d.begin(), d.end())
    , m_da(da.begin(), da.end())
    , m_init_file(init_file)
    , m_rd_sync(rd_sync)
    , m_wrdata(d.size())
    , m_contents(d.size() << da.size())
    , m_cd(nullptr) {  
  // initialize memory content
  if (!init_file.empty()) {
    load_contents(m_contents, d.size(), init_file);
  }
  
  unsigned nports(qa.size()); 
  
  // set write enable 
  litimpl* wimpl = get_impl<litimpl>(w);
  m_wenable = (!wimpl || wimpl->eval(0));  
  
  // register clock domain
  if (m_wenable || m_rd_sync) {
    m_cd = ctx->create_cdomain({clock_event(ctx->get_clk(), EDGE_POS)});
    m_cd->add_use(this);
    m_cd->release();
  }
  
  if (m_rd_sync) {
    m_rdval.resize(nports);   
    for (unsigned p = 0; p < nports; ++p) {
      m_rdval[p] = vector<bool>(m_d.size());  
    }
    m_raddr.resize(nports);
  }
  
  m_qa.reserve(nports);
  for (auto& entry: qa) {
    m_qa.emplace_back(vector<node>(entry.begin(), entry.end()));
  }
  
  m_q.resize(nports);
  for (unsigned p = 0; p < nports; ++p) {
    for (unsigned i = 0; i < m_d.size(); ++i) {
      m_q[p].emplace_back(node(new qnodeimpl(ctx, this, p, i)));
    }
  }
}

memimpl::~memimpl() {
  if (m_cd) {
    m_cd->remove_use(this);
  }
}

void memimpl::tick(ch_cycle t) {    
  if (m_do_write) {
    for (unsigned i = 0, n = m_d.size(); i < n; ++i) {
      m_contents[m_waddr * n + i] = m_wrdata[i];
    }
  }
  
  if (m_rd_sync) {
    for (unsigned p = 0, P = m_q.size(); p < P; ++p) {
      for (unsigned i = 0, n = m_d.size(); i < n; ++i) {
        m_rdval[p][i] = m_contents[m_raddr[p] * n + i];
      }
    }
  }
}

void memimpl::tick_next(ch_cycle t) {
  m_do_write = m_wenable && m_w.eval(t);
  if (m_do_write) {    
    m_waddr = toUint(m_da, t);
    for (unsigned i = 0, n = m_d.size(); i < n; ++i) {
      m_wrdata[i] = m_d[i].eval(t);
    }
  }
  
  if (m_rd_sync) {
    for (unsigned p = 0, P = m_qa.size(); p < P; ++p) {
      m_raddr[p] = toUint(m_qa[p], t);
    }
  }
}

void memimpl::print(ostream& out) const {
  //--
}

void memimpl::print_vl(ostream& out) const {
  
  set<unsigned> dead_ports; // HACK
  unsigned id(m_q[0][0].get_id());

  // HACK: identify dead ports
  for (unsigned i = 0; i < m_q.size(); ++i) {
    bool dead = true;
    for (unsigned j = 0; j < m_q[i].size(); ++j) {
      if (m_q[i][j].get_id() != 0) {
        dead = false;
      }
    }
    if (dead)
      dead_ports.emplace(i);
  }

  size_t words(1ul << m_da.size());
  size_t bits(m_d.size());
  
  for (unsigned i = 0; i < m_qa.size(); ++i) {
    if (dead_ports.count(i) != 0)
      continue;
    
    out << "  wire [" << (m_qa[0].size() - 1) << ":0] __mem_qa" << id << '_' << i << ';' << endl;
    
    if (m_rd_sync) {
      out << "  reg [" << (bits - 1) << ":0] __mem_q" << id << '_' << i << ';' << endl;
    }
  }

  out << "  wire [" << m_da.size() - 1 << ":0] __mem_da" << id << ';' << endl
      << "  wire [" << bits - 1 << ":0] __mem_d" << id << ';' << endl
      << "  wire __mem_w" << id << ';' << endl
      << "  reg [" << (bits - 1) << ":0] __mem_array" << id << '[' << words - 1 << ":0];" << endl;
  
  if (m_rd_sync || m_wenable) {
    out << "  always @(" ;
    m_cd->print_vl(out);
    out << ")" << endl 
        << "    begin" << endl;
    
    if (m_rd_sync) {
      for (unsigned i = 0; i < m_q.size(); ++i) {
        if (dead_ports.count(i) != 0)
          continue;        
        out << "      __mem_q" << id << '_' << i << " <= __mem_array" << id << "[__mem_qa" << id << '_' << i << "];" << endl;
      }
    }
  
    if (m_wenable) {
      out << "      if (__mem_w" << id << ") __mem_array" << id << "[__mem_da" << id << "] <= __mem_d" << id << ';' << endl ;
    }
    
    out << "    end" << endl;    
  }

  out << "  assign __mem_w" << id << " = __x" << m_w << ';' << endl;
  
  for (unsigned j = 0; j < m_qa.size(); ++j) {
    if (dead_ports.count(j) != 0)
      continue;    
    for (unsigned i = 0; i < m_qa[0].size(); ++i) {
      out << "  assign __mem_qa" << id << '_' << j << '[' << i << "] = __x" << m_qa[j][i] << ';' << endl;
    }
  }

  for (unsigned i = 0; i < m_da.size(); ++i) {
    out << "  assign __mem_da" << id << '[' << i << "] = __x" << m_da[i] << ';' << endl;
  }

  for (unsigned j = 0; j < m_q.size(); ++j) {
    if (dead_ports.count(j) != 0)
      continue;    
    for (unsigned i = 0; i < m_q[j].size(); ++i) {
      if (m_rd_sync) {
        out << "  assign __x" << m_q[j][i] << " = __mem_q" << id << '_' << j << '[' << i << "];" << endl;
      } else {
        out << "  assign __x" << m_q[j][i] << " = __mem_array" << id << "[__mem_qa" << id << '_' << j << "] [" << i << "];" << endl;
      }
    }
  }

  for (unsigned i = 0; i < m_d.size(); ++i) {
    out << "  assign __mem_d" << id << '[' << i << "] = __x" << m_d[i] << ';' << endl;
  }
}

///////////////////////////////////////////////////////////////////////////////

qnodeimpl::qnodeimpl(context* ctx, memimpl *mem, unsigned port, unsigned idx)
    : nodeimpl(ctx)
    , m_mem(mem)
    , m_port(port)
    , m_idx(idx)
    , m_ctime(~0ull)
    , m_cval(0) 
{
  mem->add_ref();
  
  if (mem->m_cd) {
    // add source dependencies to clock signals
    auto& cd_events = mem->m_cd->get_sensitivity_list();
    m_srcs.reserve(cd_events.size());  
    for (auto& e : cd_events) {
      m_srcs.emplace_back(e.get_signal());
    }
    
    // add other dependencies    
    if (mem->m_rd_sync) {
      for (auto& qa : mem->m_qa[m_port]) {
        m_srcs.emplace_back(qa);
      }
    }
    if (mem->m_wenable) {
      m_srcs.emplace_back(mem->m_w);  
      for (auto& da : mem->m_da) {
        m_srcs.emplace_back(da);
      }
      for (auto& d : mem->m_d) {
        m_srcs.emplace_back(d);
      }
    }    
  }  
}

qnodeimpl::~qnodeimpl() {
  m_mem->release();
}

bool qnodeimpl::eval(ch_cycle t) {  
  if (m_ctime != t) {
    m_ctime = t;
    m_cval = m_mem->m_rd_sync ? m_mem->m_rdval[m_port][m_idx] :
      m_mem->m_contents[toUint(m_mem->m_qa[m_port], t) * m_mem->m_d.size() + m_idx];
  }
  return m_cval;
}

///////////////////////////////////////////////////////////////////////////////

void chdl_internal::memory_init(
    std::vector<std::vector<node>>& out,
    const std::vector<node>& d,
    const std::vector<node>& da,
    const std::vector<std::vector<node>>& qa,
    const node& w,
    bool rd_sync,
    const std::string& init_file) {
  memimpl* m = new memimpl(get_ctx(), d, da, qa, w, rd_sync, init_file);
  out.reserve(m->m_q.size());
  for (auto& entry : m->m_q) {
    out.push_back(std::vector<node>(entry.begin(), entry.end()));
  }
  m->release();
}*/
