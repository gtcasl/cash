#pragma once

#include <functional>
#include "device.h"

namespace chdl_internal {

class ioimpl;

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
    this->add_tap(name, bus);
  }

protected:
  
  struct tap_t {
    tap_t(const std::string& name_, busimpl* bus_)
      : name(name_), bus(bus_)
    {}

    std::string name;
    busimpl* bus;
  };
  
  virtual void ensureInitialize();
  
  void bind(ioimpl* ioport);

  void add_tap(const std::string& name, busimpl* bus);

  std::vector<tap_t> m_taps;
  std::map<std::string, unsigned> m_dup_taps;
  std::set<context*> m_contexts;  
  bool m_initialized;
  busimpl* m_clk;
  busimpl* m_reset;
};

class ch_tracer : public ch_simulator {
public:
  ch_tracer(std::ostream& out);
  ~ch_tracer();
  
  void tick(ch_cycle t);
  
protected:
  
  std::ostream& m_out;
};

void register_tap(const std::string& name, const ch_node& node);

template <unsigned N> 
void ch_tap(const std::string& name, const ch_bitv<N>& v) { 
  register_tap(name, v.m_node);
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
