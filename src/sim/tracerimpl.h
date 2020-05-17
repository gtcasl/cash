#pragma once

#include "simulatorimpl.h"
#include "ioimpl.h"

namespace ch {
namespace internal {

class tracerimpl : public simulatorimpl {
public:

  tracerimpl(const std::vector<device_base>& devices);

  ~tracerimpl();

  void initialize() override;

  void toText(std::ofstream& out) const;

  void toVCD(std::ofstream& out) const;

  void toVerilog(std::ofstream& out,
                 const std::string& moduleFileName,
                 bool passthru) const;

  void toVerilator(std::ofstream& out,
                   const std::string& moduleTypeName) const;

  void toSystemC(std::ofstream& out,
                 const std::string& moduleTypeName) const;

  void toVPI(const std::string& vfile, 
             const std::string& cfile, 
             const std::string& moduleFileName) const;

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

  void eval() override;

  void allocate_trace(uint32_t block_width);

  static auto get_value(const block_t* src, uint32_t size, uint32_t src_offset) {
    bv_t value(size);
    bv_copy(value.words(), 0, src, src_offset, size);
    return value;
  }

  void toVPI_c(std::ofstream& out) const;

  void toVPI_v(std::ofstream& out, const std::string& moduleTypeName) const;

  std::vector<ioportimpl*> signals_;
  std::vector<std::pair<block_t*, uint32_t>> prev_values_;
  bv_t valid_mask_;
  uint32_t trace_width_;
  trace_block_t* trace_head_;
  trace_block_t* trace_tail_;
  uint32_t num_traces_;
  bool is_single_context_;
};

}
}
