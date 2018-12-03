#pragma once

#include "simulatorimpl.h"

namespace ch {
namespace internal {

class tracerimpl : public simulatorimpl {
public:

  tracerimpl(const ch_device_list& devices);

  ~tracerimpl();

  void toText(std::ofstream& out);

  void toVCD(std::ofstream& out);

  void toTestBench(std::ofstream& out,
                   const std::string& module,
                   bool passthru);

  void toVerilator(std::ofstream& out,
                   const std::string& module);

protected:

  void initialize();

  void eval() override;

  uint32_t add_signal(ioportimpl* node);

  void allocate_trace(uint32_t block_width);

  struct signal_t {
    std::string name;
    ioportimpl* node;
  };

  struct trace_block_t {
    trace_block_t(block_type* data)
      : data(data)
      , size(0)
      , next(nullptr)
    {}

    block_type* data;
    uint32_t size;
    trace_block_t* next;
  };

  dup_tracker<std::string> dup_names_;
  std::vector<signal_t> signals_;  
  std::vector<std::pair<block_type*, uint32_t>> prev_values;
  sdata_type valid_mask_;
  uint32_t trace_width_;
  uint32_t ticks_;
  trace_block_t* trace_head_;
  trace_block_t* trace_tail_;
  uint32_t num_traces_;
};

}
}
