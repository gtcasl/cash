#include "tracerimpl.h"
#include "tracer.h"
#include "ioimpl.h"

using namespace ch::internal;

tracerimpl::tracerimpl(std::ostream& out, const std::initializer_list<context*>& contexts)
  : simulatorimpl(contexts)
  , file_(nullptr)
  , out_(out)
{}

tracerimpl::tracerimpl(const char* file, const std::initializer_list<context*>& contexts)
  : simulatorimpl(contexts)
  , file_(new std::ofstream(file))
  , out_(*file_)
{}

void tracerimpl::ensureInitialize() {
  // call parent ensureInitialize()
  simulatorimpl::ensureInitialize();

  bool clk_found = false;
  bool reset_found = false;

  // register context taps
  for (auto ctx : contexts_) {
    // get clk
    if (!clk_found) {
      auto clk = ctx->get_default_clk();
      if (clk) {
        this->add_trace("clk", clk);
        clk_found = true;
      }
    }

    // get reset
    if (!reset_found) {
      auto reset = ctx->get_default_reset();
      if (reset) {
        this->add_trace("reset", reset);
        reset_found = true;
      }
    }

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

void tracerimpl::add_trace(const char* name, ioimpl* value) {
  CH_CHECK(!initialized_, "new tap not allowed after simulation has started");

  // resolve duplicate names
  std::string full_name(name);
  unsigned instances = dup_taps_[name]++;
  if (instances > 0) {
    if (instances == 1) {
      // rename first instance
      auto iter = std::find_if(taps_.begin(), taps_.end(),
        [name](const tap_t& t)->bool { return t.name == name; });
      assert(iter != taps_.end());
      iter->name = fstring("%s_%d", name, 0);
    }
    full_name = fstring("%s_%d", name, instances);
  }
  taps_.emplace_back(full_name, value);
}

void tracerimpl::tick(ch_tick t) {
  // advance simulation
  simulatorimpl::tick(t);

  // log tap values
  for (auto& tap : taps_) {
    out_ << tap.name << " = " << tap.node << std::endl;
  }
}

///////////////////////////////////////////////////////////////////////////////

ch_tracer::ch_tracer(std::ostream& out,
                     const std::initializer_list<context*>& contexts)
  : ch_simulator(new tracerimpl(out, contexts))
{}

ch_tracer::ch_tracer(const char* file,
                     const std::initializer_list<context*>& contexts)
  : ch_simulator(new tracerimpl(file, contexts))
{}

ch_tracer::ch_tracer(simulatorimpl* impl) : ch_simulator(impl) {}

ch_tracer::~ch_tracer() {}
