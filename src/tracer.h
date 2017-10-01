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

  template <typename... Devices>
  ch_tracer(const std::string& file, const ch_device& device, const Devices&... more)
    : ch_tracer(file, {&device, &more...})
  {}

  ch_tracer(std::ostream& out) : ch_tracer(out, {}) {}

  ch_tracer(const std::string& file) : ch_tracer(file, {}) {}

  ~ch_tracer();

  template <unsigned N>
  void add_trace(const std::string& name, const ch_bitbase<N>& value) {
    this->add_trace(name, get_lnode(value));
  }

protected:

  ch_tracer(std::ostream& out, const std::initializer_list<const ch_device*>& devices);

  ch_tracer(const std::string& file, const std::initializer_list<const ch_device*>& devices);

  ch_tracer(simulatorimpl* impl);

  void add_trace(const std::string& name, const lnode& value);
};

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

