#include "sim.h"
#include "cdomain.h"
#include "context.h"
#include "busimpl.h"
#include "ioimpl.h"
#include "opt.h"

using namespace std;
using namespace chdl_internal;

ch_simulator::ch_simulator()
  : m_initialized(false)
  , m_clk(nullptr)
  , m_reset(nullptr) {
  //--  
}

ch_simulator::~ch_simulator() {
  for (auto& tap : m_taps) {
    tap.bus->release();
  }
  if (m_clk)
    m_clk->release();
  if (m_reset)
    m_reset->release();
}

void ch_simulator::ensureInitialize() {
  if (m_initialized)
    return;

  // gather active contexts
  for (auto tap : m_taps) {
    tap.bus->get_bindings(m_contexts);
  }

  // bind context taps
  for (auto ctx : m_contexts) {
    if (ctx->g_clk)
      this->bind(ctx->g_clk, &m_clk);

    if (ctx->g_reset)
      this->bind(ctx->g_reset, &m_reset);
    
    for (tapimpl* tap : ctx->taps) {
      this->bind(tap);
    }
  }
  
  m_initialized = true;
}

void ch_simulator::bind(inputimpl* input, busimpl** bus) {
  if (*bus == nullptr) {
    *bus = new busimpl(1);
    this->add_tap(input->get_name(), *bus);
  }    
  ibridge* bridge = new ibridge(*bus);
  input->bind(bridge);
  bridge->release();
}

void ch_simulator::bind(tapimpl* tap) {  
  obridge* bridge = new obridge(tap);
  tap->bind(bridge);
  bridge->release();

  busimpl* bus = new busimpl(tap->get_size());
  bus->bind(tap->get_ctx(), 0, bridge);

  // add to list
  this->add_tap(tap->get_tapName(), bus);
  bus->add_ref();
}

void ch_simulator::add_tap(const std::string& name, busimpl* bus) {
  if (m_initialized) {
    CHDL_ABORT("new tap not allowed after simulation has started");
  }

  // resolve duplicate names  
  string full_name(name);
  unsigned instances = m_dup_taps[name]++;
  if (instances > 0) {
    if (instances == 1) {
      // rename first instance
      auto iter = std::find_if(m_taps.begin(), m_taps.end(),
        [name](const tap_t& t)->bool { return t.name == name; });
      assert(iter != m_taps.end());
      iter->name = fstring("%s_%d", name.c_str(), 0);
    }
    full_name = fstring("%s_%d", name.c_str(), instances);
  }
  m_taps.emplace_back(full_name, bus);
  bus->add_ref();
}

void ch_simulator::tick(ch_cycle t) { 
  // ensure initialized
  this->ensureInitialize();
  
  // evaluate context registers  
  for (auto ctx : m_contexts) {
    ctx->tick(t);
  }
  for (auto ctx : m_contexts) {
    ctx->tick_next(t);
  }
  
  // evaluate all signals
  for (auto tap : m_taps) {
    tap.bus->eval(t);
  }
}

void ch_simulator::run(const std::function<bool(ch_cycle time)>& callback) {
  ch_cycle start = this->reset(0);
  for (ch_cycle time = start; callback(time - start); ++time) {
    this->step(time);
  }
}

void ch_simulator::run(ch_cycle cycles) {
  ch_cycle time = this->reset(0);
  for (; time < cycles; ++time) {
    this->step(time);
  }
}

ch_cycle ch_simulator::reset(ch_cycle t) {
  // ensure initialized
  this->ensureInitialize();

  if (m_reset) {
    m_reset->set_bit(0, true);    
    this->step(t++);
    m_reset->set_bit(0, false);
    this->step(t++);
  }
  
  return t;
}

void ch_simulator::step(ch_cycle t) {
  if (m_clk) {
    for (int i = 0; i < 2; ++i) {
      this->tick(t * 2 + i);
      m_clk->set_bit(0, !m_clk->get_bit(0));
    }
  } else {
    this->tick(t);
  }
}

///////////////////////////////////////////////////////////////////////////////

ch_tracer::ch_tracer(std::ostream& out) : m_out(out) {}

ch_tracer::~ch_tracer() {}

void ch_tracer::tick(ch_cycle t) {
  // advance simulation
  ch_simulator::tick(t);
  
  TODO();
}

///////////////////////////////////////////////////////////////////////////////

void chdl_internal::register_tap(const string& name, const ch_node& node, uint32_t size) {
  node.ensureInitialized(size);
  node.get_ctx()->register_tap(name, node);
}
