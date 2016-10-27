#include "device.h"
#include "context.h"
#include "opt.h"

using namespace std;
using namespace chdl_internal;

ch_device::~ch_device() {
  m_ctx->release();
}

void ch_device::bind_input_(const lnode& input, const snode& bus) const {
  input.assign(m_ctx->bind_input(bus));
}

snode ch_device::bind_output_(const lnode& output) const {
  return snode(m_ctx->bind_output(output));
}

snode ch_device::get_tap(std::string& name, uint32_t size) const {
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

void ch_device::toVerilog(const std::string& module_name, std::ostream& out) {
  m_ctx->toVerilog(module_name, out);
}
