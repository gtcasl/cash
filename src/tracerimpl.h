#pragma once

#include "simulatorimpl.h"

namespace ch {
namespace internal {

class tracerimpl : public simulatorimpl {
public:

  tracerimpl(const ch_device_list& devices);

  ~tracerimpl();

  void toText(const std::string& file);

  void toVCD(const std::string& file);

  void toTestBench(const std::string& file);

protected:

  void initialize();

  void eval(ch_tick t) override;

  uint32_t add_signal(const std::string& name, ioimpl* node);

  struct signal_t {
    std::string name;
    ioimpl* node;
  };

  struct trace_block_t {
    trace_block_t(uint32_t size, uint32_t width) : data(size, bitvector(width)), size(0), next(nullptr) {}
    std::vector<bitvector> data;
    uint32_t size;
    trace_block_t* next;
  };

  unique_names unique_trace_names_;
  std::vector<signal_t> signals_;
  uint32_t trace_width_;
  trace_block_t* trace_blocks_head_;
  trace_block_t* trace_blocks_tail_;
  uint32_t num_trace_blocks_;
};

}
}
