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

  using block_t = uint64_t;
  using bv_t = bitvector<block_t>;
  static_assert(bitwidth_v<block_t> >= bitwidth_v<block_type>);

  struct trace_block_t {
    trace_block_t(block_t* data)
      : data(data)
      , size(0)
      , next(nullptr)
    {}

    block_t* data;
    uint32_t size;
    trace_block_t* next;
  };

  void initialize();

  void eval() override;

  void allocate_trace(uint32_t block_width);

  static auto is_system_signal(const std::string& name) {
    return (name == "clk") || (name == "reset");
  }

  static auto get_value(const block_t* src, uint32_t size, uint32_t src_offset) {
    bv_t value(size);
    bv_copy(value.words(), 0, src, src_offset, size);
    return value;
  }

  std::vector<context*> get_module_path(context* ctx);

  std::vector<ioportimpl*> signals_;
  std::vector<std::pair<block_t*, uint32_t>> prev_values_;
  bv_t valid_mask_;
  uint32_t trace_width_;
  uint32_t ticks_;
  trace_block_t* trace_head_;
  trace_block_t* trace_tail_;
  uint32_t num_traces_;
};

}
}
