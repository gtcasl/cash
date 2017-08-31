#pragma once

#include "device.h"

namespace cash {
namespace internal {

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
  
  std::unordered_set<context*> contexts_;
  bool initialized_;
  snodeimpl* clk_;
  snodeimpl* reset_;
};

class ch_tracer : public ch_simulator {
public:
  
  template<typename ...Devices>
  ch_tracer(std::ostream& out, const Devices&... devices) : ch_tracer(out, {&devices...}) {}
  ch_tracer(std::ostream& out, const std::initializer_list<const ch_device*>& devices);
  ~ch_tracer();
    
  template <unsigned N> 
  void add_trace(const std::string& name, const ch_bus<N>& value) {
    this->add_trace(name, get_node(value));
  }  
  
  template <unsigned N> 
  void add_trace(const std::string& name, const ch_busbase<N>& value) {
    this->add_trace(name, get_node(value));
  }
  
  void tick(ch_cycle t) override;
  
protected:
  
  struct tap_t {
    tap_t(const std::string& p_name, const snode& p_bus)
      : name(p_name)
      , bus(p_bus)
    {}
    std::string name;
    snode bus;
  };
  
  void ensureInitialize() override;  
  
  void add_trace(const std::string& name, const snode& value);
  
  std::unordered_map<std::string, unsigned> dup_taps_;
  std::vector<tap_t> taps_;
  std::ostream& out_;
};

void register_tap(const std::string& name, const lnode& node);

template <unsigned N> 
void ch_tap(const std::string& name, const ch_bit<N>& value) {
  register_tap(name, get_node(value));
}

template <unsigned N> 
void ch_tap(const std::string& name, const ch_bitbase<N>& value) {
  register_tap(name, get_node(value));
}

}
}

#define CH_MAKE_TRACE(i, x) \
  __tracer.add_trace(CH_STRINGIZE(x), x)

#define CH_MAKE_TRACE_SEP() ;

#define CH_TRACE(x, ...) \
  do { \
    cash::internal::ch_tracer& __tracer = x; \
    CH_FOR_EACH(CH_MAKE_TRACE, CH_MAKE_TRACE_SEP, __VA_ARGS__); \
  } while (0)

#ifndef NDEBUG
  #define CH_TAP(x) ch_tap(#x, x)
#else
  #define CH_TAP(x)
#endif
