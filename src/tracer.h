#pragma once

#include "simulator.h"

namespace cash {
namespace internal {

class ch_tracer : public ch_simulator {
public:

  template <typename... Devices>
  ch_tracer(std::ostream& out, const ch_device& device, const Devices&... more)
    : ch_tracer(out, {&device, &more...})
  {}

  ch_tracer(std::ostream& out) : ch_tracer(out, {}) {}

  ~ch_tracer();

  template <typename T>
  void add_trace(const std::string& name, const ch_busbase<T>& value) {
    this->add_trace(name, get_snode(value));
  }

protected:

  ch_tracer(std::ostream& out, const std::initializer_list<const ch_device*>& devices);

  ch_tracer(simulatorimpl* impl);

  void add_trace(const std::string& name, const snode& value);
};

void register_tap(const std::string& name, const lnode& node);

template <typename T>
void ch_tap(const std::string& name, const ch_bitbase<T>& value) {
  register_tap(name, get_lnode(value));
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

