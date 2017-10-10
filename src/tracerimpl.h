#pragma once

#include "simulatorimpl.h"

namespace ch {
namespace internal {

class tracerimpl : public simulatorimpl {
public:
  tracerimpl(std::ostream& out, const std::initializer_list<context*>& contexts);
  tracerimpl(const char* file, const std::initializer_list<context*>& contexts);

  ~tracerimpl() {
    if (file_)
      delete file_;
  }

  void tick(ch_tick t) override;

protected:

  void ensureInitialize() override;

  void add_trace(const char* name, ioimpl* value);

  struct tap_t {
    tap_t(const std::string& _name, ioimpl* _node)
      : name(_name)
      , node(_node)
    {}
    std::string name;
    ioimpl* node;
  };

  tap_counts_t dup_taps_;
  std::vector<tap_t> taps_;
  std::ofstream* file_;
  std::ostream& out_;
};

}
}
