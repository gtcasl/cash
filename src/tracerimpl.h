#pragma once

#include "simulatorimpl.h"

namespace ch {
namespace internal {

class tracerimpl : public simulatorimpl {
public:

  tracerimpl(std::ostream& out, const std::initializer_list<context*>& contexts);

  tracerimpl(const std::string& file, const std::initializer_list<context*>& contexts);

  ~tracerimpl();

  void add_trace(const std::string& name, const scalar_buffer_ptr& node);

protected:

  void ensureInitialize() override;

  void tick(ch_tick t) override;

  void add_trace(const std::string& name, ioimpl* node);

  struct io_trace_t {
    io_trace_t(const std::string& p_name, ioimpl* p_node)
      : name(p_name)
      , node(p_node)
    {}
    std::string name;
    ioimpl* node;
  };

  struct sc_trace_t {
    sc_trace_t(const std::string& p_name, const scalar_buffer_ptr& p_node)
      : name(p_name)
      , node(p_node)
    {}
    std::string name;
    scalar_buffer_ptr node;
  };

  unique_name unique_trace_names_;
  std::vector<io_trace_t> io_traces_;
  std::vector<sc_trace_t> sc_traces_;
  std::ofstream* file_;
  std::ostream& out_;
};

}
}
