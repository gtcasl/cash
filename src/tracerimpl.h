#pragma once

#include "simulatorimpl.h"

namespace ch {
namespace internal {

class tracerimpl : public simulatorimpl {
public:
  tracerimpl(std::ostream& out, const std::initializer_list<const ch_device*>& devices)
    : simulatorimpl(devices)
    , file_(nullptr)
    , out_(out)
  {}

  tracerimpl(const std::string& file, const std::initializer_list<const ch_device*>& devices)
    : simulatorimpl(devices)
    , file_(new std::ofstream(file))
    , out_(*file_)
  {}

  ~tracerimpl() {
    if (file_)
      delete file_;
  }

  void add_trace(const std::string& name, const lnode& value);

  void tick(ch_tick t) override;

protected:

  void ensureInitialize() override;

  struct tap_t {
    tap_t(const std::string& p_name, const lnode& p_node)
      : name(p_name)
      , node(p_node)
    {}
    std::string name;
    lnode node;
  };

  std::unordered_map<std::string, unsigned> dup_taps_;
  std::vector<tap_t> taps_;
  std::ofstream* file_;
  std::ostream& out_;
};

}
}
