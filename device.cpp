#include "device.h"
#include "context.h"
#include "opt.h"

using namespace std;
using namespace chdl_internal;

ch_device::~ch_device() {
  m_ctx->release();
}

lnodeimpl* ch_device::bind_input_(snodeimpl* bus) const {
  return m_ctx->bind_input(bus);
}

snodeimpl* ch_device::bind_output_(lnodeimpl* output) const {
  return m_ctx->bind_output(output);
}

snodeimpl* ch_device::get_tap(const std::string& name, uint32_t size) const {
  return m_ctx->get_tap(name, size);
}

void ch_device::compile() {
  // syntax check
  m_ctx->syntax_check();
  
  {
    // run optimizer
    optimizer opt(m_ctx);
    opt.optimize();
  }
}

// LCOV_EXCL_START
void ch_device::toVerilog(const std::string& module_name, std::ostream& out) {
  m_ctx->toVerilog(module_name, out);
}
// LCOV_EXCL_END
