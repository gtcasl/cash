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

tracerimpl::~tracerimpl() {
  if (file_) {
    delete file_;
  }
}

void tracerimpl::initialize() {
  // call parent initialize()
  simulatorimpl::initialize();

  // register context taps
  for (auto ctx : contexts_) {
    // get inputs
    for (auto node : ctx->inputs()) {
      this->add_trace(node->name(), node);
    }

    // get outputs
    for (auto node : ctx->outputs()) {
      this->add_trace(node->name(), node);
    }

    // get taps
    for (auto node : ctx->taps()) {
      this->add_trace(node->name(), node);
    }
  }
}

void tracerimpl::add_trace(const std::string& name, ioimpl* node) {
  io_traces_.emplace_back(unique_trace_names_.get(name), node);
}

void tracerimpl::add_trace(const std::string& name, const scalar_buffer_ptr& node) {
  sc_traces_.emplace_back(unique_trace_names_.get(name), node);
}

void tracerimpl::eval(ch_tick t) {
  // advance simulation
  simulatorimpl::eval(t);

  // log io nodes
  for (auto& trace : io_traces_) {
    out_ << trace.name << " = " << trace.node << std::endl;
  }

  // log scalars
  for (auto& trace : sc_traces_) {
    out_ << trace.name << " = " << trace.node->data() << std::endl;
  }
}

///////////////////////////////////////////////////////////////////////////////

tracerimpl::io_trace_t::io_trace_t(const std::string& p_name, ioimpl* p_node)
  : name(p_name)
  , node(p_node)
{}

tracerimpl::sc_trace_t::sc_trace_t(const std::string& p_name, const scalar_buffer_ptr& p_node)
  : name(p_name)
  , node(p_node)
{}

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

void ch_tracer::add_trace(const std::string& name, const scalar_buffer_ptr& buffer) {
  return reinterpret_cast<tracerimpl*>(impl_)->add_trace(name, buffer);
}

