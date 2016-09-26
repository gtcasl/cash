#include "device.h"
#include "context.h"
#include "opt.h"

using namespace std;
using namespace chdl_internal;

ch_device::~ch_device() {
  delete m_ctx;
}

void ch_device::register_io(const std::vector<ioport_arg>& args) {  
  for (unsigned i = 0, n = args.size(); i < n; ++i) {
    m_ctx->register_io(i, args[i].m_node);
  }
  // ensure all undefined nodes are deleted
  assert(m_ctx->undefs.size() == 0);
}

void ch_device::compile() {
  optimizer opt(m_ctx);
  opt.optimize();
}

void ch_device::bind(const std::vector<bus_arg>& args) {
  for (unsigned i = 0, n = args.size(); i < n; ++i) {
    m_ctx->bind(i, args[i].m_impl);
  }
}

void ch_device::toVerilog(const std::string& module_name, std::ostream& out) {
  m_ctx->toVerilog(module_name, out);
}
