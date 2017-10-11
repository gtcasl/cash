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

  struct trace_t {
    trace_t(const std::string& _name, ioimpl* _node)
      : name(_name)
      , node(_node)
    {}
    std::string name;
    ioimpl* node;
  };

  unique_name unique_trace_names_;
  std::vector<trace_t> traces_;
  std::ofstream* file_;
  std::ostream& out_;
};

}
}
