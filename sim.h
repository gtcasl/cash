#pragma once

#include "device.h"

namespace chdl_internal {

class inputimpl;
class tapimpl;

class ch_simulator {
public:  
  
  template<typename ...Devices>
  ch_simulator(const Devices&... devices) : ch_simulator({&devices...}) {}  
  ch_simulator(const std::initializer_list<const ch_device*>& devices);
  ~ch_simulator();
  
  void add_device(const ch_device& device);

  void step(ch_cycle t);
  
  virtual void tick(ch_cycle t);

  void run(const std::function<bool(ch_cycle time)>& callback);
  
  void run(ch_cycle cycles = 20);

  ch_cycle reset(ch_cycle t);

protected:
  
  virtual void ensureInitialize();
  
  std::set<context*> m_contexts;  
  bool m_initialized;
  snodeimpl* m_clk;
  snodeimpl* m_reset;
};

class ch_tracer : public ch_simulator {
public:
  
  template<typename ...Devices>
  ch_tracer(std::ostream& out, const Devices&... devices) : ch_tracer(out, {&devices...}) {}
  ch_tracer(std::ostream& out, const std::initializer_list<const ch_device*>& devices);
  ~ch_tracer();
    
  template <unsigned N> 
  void add_trace(const std::string& name, const ch_bus<N>& bus) {
    this->add_trace(name, static_cast<snodeimpl*>(static_cast<const snode&>(bus)));
  }  
  
  template <unsigned N> 
  void add_trace(const std::string& name, const ch_busbase<N>& bus) {
    this->add_trace<N>(name, ch_bus<N>(bus));
  }
  
  void tick(ch_cycle t);
  
protected:
  
  struct tap_t {
    tap_t(const std::string& name_, snodeimpl* bus_) : name(name_), bus(bus_) {}

    std::string name;
    snodeimpl* bus;
  };
  
  void ensureInitialize() override;  
  
  void add_trace(const std::string& name, snodeimpl* bus);
  
  std::map<std::string, unsigned> m_dup_taps;
  std::vector<tap_t> m_taps;
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
  __tracer.add_trace(CHDL_STRINGIZE(x), x)

#define CHDL_MAKE_TRACE_SEP() ;

#define CHDL_TRACE(x, ...) do { \
    chdl_internal::ch_tracer& __tracer = x; \
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
