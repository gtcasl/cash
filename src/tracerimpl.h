#pragma once

#include "simulatorimpl.h"

namespace cash {
namespace internal {

class tracerimpl : public simulatorimpl {
public:
  tracerimpl(std::ostream& out, const std::initializer_list<const ch_device*>& devices)
    : simulatorimpl(devices)
    , out_(out)
  {}

  ~tracerimpl() {}

  void add_trace(const std::string& name, const snode& value);

  void tick(ch_tick t) override;

protected:

  void ensureInitialize() override;

  struct tap_t {
    tap_t(const std::string& p_name, const snode& p_bus)
      : name(p_name)
      , bus(p_bus)
    {}
    std::string name;
    snode bus;
  };

  std::unordered_map<std::string, unsigned> dup_taps_;
  std::vector<tap_t> taps_;
  std::ostream& out_;
};

}
}
