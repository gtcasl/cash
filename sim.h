#pragma once

#include <functional>
#include "device.h"

namespace chdl_internal {

class inputimpl;
class tapimpl;

class ch_simulator {
public:  
  ch_simulator();
  ~ch_simulator();

  void step(ch_cycle t);
  
  virtual void tick(ch_cycle t);

  void run(const std::function<bool(ch_cycle time)>& callback);
  
  void run(ch_cycle cycles = 20);

  ch_cycle reset(ch_cycle t);
  
  template <unsigned N> 
  void add_trace(const std::string& name, const ch_bus<N>& bus) {
    this->add_tap(name, static_cast<snodeimpl*>(static_cast<const snode&>(bus)));
  }  
  
  template <unsigned N> 
  void add_trace(const std::string& name, const ch_busbase<N>& bus) {
    this->add_trace<N>(name, ch_bus<N>(bus));
  }

protected:
  
  struct tap_t {
    tap_t(const std::string& name_, snodeimpl* bus_)
      : name(name_), bus(bus_)
    {}

    std::string name;
    snodeimpl* bus;
  };
  
  virtual void ensureInitialize();
  
  void bind(inputimpl* input, snodeimpl** bus);
  
  void bind(tapimpl* tap);
  
  void add_tap(const std::string& name, snodeimpl* bus);

  std::vector<tap_t> m_taps;
  std::map<std::string, unsigned> m_dup_taps;
  std::set<context*> m_contexts;  
  bool m_initialized;
  snodeimpl* m_clk;
  snodeimpl* m_reset;
};

class ch_tracer : public ch_simulator {
public:
  ch_tracer(std::ostream& out);
  ~ch_tracer();
  
  void tick(ch_cycle t);
  
protected:
  
  std::ostream& m_out;
};

void register_tap(const std::string& name, const lnode& node, uint32_t size);

template <unsigned N> 
void ch_tap(const std::string& name, const ch_bitv<N>& v) { 
  register_tap(name, v, N);
}

template <unsigned N> 
void ch_tap(const std::string& name, const ch_bitbase<N>& v) { 
  ch_tap(name, ch_bitv<N>(v));
}

}

#define CHDL_MAKE_TRACE(i, x) \
  __sim.add_trace(CHDL_STRINGIZE(x), x)

#define CHDL_MAKE_TRACE_SEP() ;

#define CHDL_TRACE(x, ...) do { \
  chdl_internal::ch_simulator& __sim = x; \
  CHDL_FOR_EACH(CHDL_MAKE_TRACE, CHDL_MAKE_TRACE_SEP, __VA_ARGS__); \
  } while (false)

#ifdef CHDL_DEBUG
  #define CHDL_TAP(x) \
    do {  \
      ch_tap(#x, x); \
    } while (0)
#else
  #define CHDL_TAP(x)
#endif
