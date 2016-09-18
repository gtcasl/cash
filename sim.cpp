#include "sim.h"
#include "cdomain.h"
#include "context.h"
#include "busimpl.h"
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
  delete m_clk;
  delete m_reset;
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
    if (ctx->g_clk) {
      if (m_clk == nullptr) {
        // setup global clock
        m_clk = new busimpl(1);
        this->add_tap("clk", m_clk);
      }

      // bind global clock
      ibridge* bridge = new ibridge(m_clk);
      ctx->g_clk->bind(bridge);
      bridge->release();
    }

    if (ctx->g_reset) {
      if (m_reset == nullptr) {
        // setup global reset
        m_reset = new busimpl(1);
        this->add_tap("reset", m_reset);
      }

      // bind global reset
      ibridge* bridge = new ibridge(m_reset);
      ctx->g_reset->bind(bridge);
      bridge->release();
    }
    
    // bind debug taps
    for (auto tap : ctx->taps) {
      this->bind(tap);
    }
  }
  
  m_initialized = true;
}

void ch_simulator::bind(ioimpl* ioport) {  
  obridge* bridge = new obridge(ioport);
  ioport->bind(bridge);
  bridge->release();

  busimpl* bus = new busimpl(ioport->get_size());
  bus->bind(ioport->get_ctx(), 0, bridge);

  // add to list
  this->add_tap(ioport->get_name(), bus);
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
  ch_cycle time = this->reset(0);
  for (; callback(time); ++time) {
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

void chdl_internal::register_tap(const string& name, const ch_node& node) {
  node.get_ctx()->register_tap(name, node);
}
