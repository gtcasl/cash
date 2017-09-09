#include "tracerimpl.h"
#include "tracer.h"
#include "ioimpl.h"

using namespace cash::internal;

void tracerimpl::ensureInitialize() {
  // call parent ensureInitialize()
  simulatorimpl::ensureInitialize();

  // register clock signals
  if (clk_) {
    this->add_trace("clk", clk_);
  }
  if (reset_) {
    this->add_trace("reset", reset_);
  }

  // register context taps
  for (auto ctx : contexts_) {
    for (tapimpl* tap : ctx->taps_) {
      this->add_trace(tap->get_tapName(), tap->get_bus());
    #ifndef NDEBUG
      int dump_cfg_level = platform::self().get_dump_cfg();
      if (dump_cfg_level) {
        std::cout << "CFG dump for tap variable: " << tap->get_tapName() << std::endl;
        ctx->dump_cfg(tap, std::cout, dump_cfg_level);
      }
    #endif
    }
  }
}

void tracerimpl::add_trace(const std::string& name, const snode& value) {
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
      iter->name = fstring("%s_%d", name.c_str(), 0);
    }
    full_name = fstring("%s_%d", name.c_str(), instances);
  }
  taps_.emplace_back(full_name, value);
}

void tracerimpl::tick(ch_tick t) {
  // advance simulation
  simulatorimpl::tick(t);

  CH_TODO();
}

///////////////////////////////////////////////////////////////////////////////

ch_tracer::ch_tracer(std::ostream& out,
                     const std::initializer_list<const ch_device*>& devices)
  : ch_simulator(new tracerimpl(out, devices))
{}

ch_tracer::ch_tracer(simulatorimpl* impl) : ch_simulator(impl) {}

ch_tracer::~ch_tracer() {}

void ch_tracer::add_trace(const std::string& name, const snode& value) {
  dynamic_cast<tracerimpl*>(impl_)->add_trace(name, value);
}

///////////////////////////////////////////////////////////////////////////////

void cash::internal::register_tap(const std::string& name, const lnode& node) {
  node.get_ctx()->register_tap(name, node);
}
