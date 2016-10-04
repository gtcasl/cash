#include "device.h"
#include "context.h"
#include "opt.h"

using namespace std;
using namespace chdl_internal;

ch_device::~ch_device() {
  delete m_ctx;
}

void ch_device::bind_input(unsigned index, const lnode& input, const snode& bus) const {
  //--
}

void ch_device::bind_output(unsigned index, const lnode& output, const snode& bus) const {
  //--
}

/*void ch_device::register_inputs(const std::vector<ioport_arg>& inputs) {  
  unsigned i = 0;
  for (auto& input : inputs) {
    m_ctx->register_input(i++, input.m_node);
  }
  // ensure all undefined nodes are deleted
  assert(m_ctx->undefs.size() == 0);
}

void ch_device::register_outputs(const std::vector<ioport_arg>& outputs) {  
  unsigned i = 0;
  for (auto& output : outputs) {
    m_ctx->register_output(i++, output.m_node);
  }
}*/

/*void ch_device::bind(const std::vector<bus_arg>& args) {
  unsigned i = 0;
  for (auto& arg : args) {
    m_ctx->bind(i++, arg.m_node);
  }
}*/

void ch_device::compile() {
  optimizer opt(m_ctx);
  opt.optimize();
}

void ch_device::toVerilog(const std::string& module_name, std::ostream& out) {
  m_ctx->toVerilog(module_name, out);
}
