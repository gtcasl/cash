#include "tracerimpl.h"
#include "tracer.h"
#include "ioimpl.h"

using namespace ch::internal;

tracerimpl::tracerimpl(std::ostream& out, const std::initializer_list<context*>& contexts)
  : simulatorimpl(contexts)
  , file_(nullptr)
  , out_(out)
{}

tracerimpl::tracerimpl(const std::string& file, const std::initializer_list<context*>& contexts)
  : simulatorimpl(contexts)
  , file_(new std::ofstream(file))
  , out_(*file_)
{}

void tracerimpl::ensureInitialize() {
  // call parent ensureInitialize()
  simulatorimpl::ensureInitialize();

  // register context taps
  for (auto ctx : contexts_) {
    // get inputs
    for (auto node : ctx->get_inputs()) {
      this->add_trace(node->get_name(), node);
    }

    // get outputs
    for (auto node : ctx->get_outputs()) {
      this->add_trace(node->get_name(), node);
    }

    // get taps
    for (auto node : ctx->get_taps()) {
      this->add_trace(node->get_name(), node);
    }
  }
}

void tracerimpl::add_trace(const std::string& name, ioimpl* value) {
  traces_.emplace_back(unique_trace_names_.get(name), value);
}

void tracerimpl::tick(ch_tick t) {
  // advance simulation
  simulatorimpl::tick(t);

  // log tap values
  for (auto& tap : traces_) {
    out_ << tap.name << " = " << tap.node << std::endl;
  }
}

///////////////////////////////////////////////////////////////////////////////

ch_tracer::ch_tracer(std::ostream& out,
                     const std::initializer_list<context*>& contexts)
  : ch_simulator(new tracerimpl(out, contexts))
{}

ch_tracer::ch_tracer(const std::string& file,
                     const std::initializer_list<context*>& contexts)
  : ch_simulator(new tracerimpl(file, contexts))
{}

ch_tracer::ch_tracer(simulatorimpl* impl) : ch_simulator(impl) {}

ch_tracer::~ch_tracer() {}
