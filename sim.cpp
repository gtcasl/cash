#include "sim.h"
#include "cdomain.h"
#include "context.h"
#include "snodeimpl.h"
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

  // gather active contexts from output taps 
  for (auto tap : m_taps) {
    context* ctx = tap.bus->get_ctx();
    if (ctx)
      m_contexts.emplace(ctx);
  }

  // bind context taps
  for (auto ctx : m_contexts) {
    if (ctx->m_clk) {
      if (m_clk == nullptr) {
        m_clk = new snodeimpl(1);
        m_clk->acquire();
      }
      ctx->m_clk->bind(m_clk);
    }

    if (ctx->m_reset) {
      if (m_reset == nullptr) {
        m_reset = new snodeimpl(1);
        m_reset->acquire();
      }
      ctx->m_reset->bind(m_reset);
    }
    
    for (tapimpl* tap : ctx->m_taps) {
      this->add_tap(tap->get_tapName(), new snodeimpl(tap));
    }
  }
  
  m_initialized = true;
}

void ch_simulator::add_tap(const std::string& name, snodeimpl* bus) {
  CHDL_REQUIRED(!m_initialized, "new tap not allowed after simulation has started");
  
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
  bus->acquire();
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
    (*m_reset)[0] = true;    
    this->step(t++);
    (*m_reset)[0] = false;
    this->step(t++);
  }
  
  return t;
}

void ch_simulator::step(ch_cycle t) {
  if (m_clk) {
    for (int i = 0; i < 2; ++i) {
      this->tick(t * 2 + i);
      (*m_clk)[0] = !(*m_clk)[0];
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
  
  TODO("Not yet implemented!");
}

///////////////////////////////////////////////////////////////////////////////

void chdl_internal::register_tap(const string& name, const lnode& node, uint32_t size) {
  node.ensureInitialized(size);
  node.get_ctx()->register_tap(name, node);
}
