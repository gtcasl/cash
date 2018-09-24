#include "tracerimpl.h"
#include "tracer.h"
#include "ioimpl.h"

using namespace ch::internal;

#define NUM_BLOCKS 100

auto is_system_signal = [](const std::string& name) {
  return (name == "clk") || (name == "reset");
};

auto get_value = [](const bitvector& src, uint32_t size, uint32_t src_offset) {
  bitvector value(size);
  value.copy(0, src, src_offset, size);
  return value;
};

tracerimpl::tracerimpl(const ch_device_list& devices)
  : simulatorimpl(devices)  
  , trace_blocks_head_(nullptr)
  , trace_blocks_tail_(nullptr)
  , num_trace_blocks_(0)
  , trace_width_(0) {
  // initialize
  this->initialize();
}

tracerimpl::~tracerimpl() {
  auto block = trace_blocks_head_;
  while (block) {
    auto next = block->next;
    delete block;
    block = next;
  }
}

void tracerimpl::initialize() {
  // register signals
  for (auto ctx : contexts_) {
    // get inputs
    for (auto node : ctx->inputs()) {
      trace_width_ += this->add_signal(node);
    }

    // get outputs
    for (auto node : ctx->outputs()) {
      trace_width_ += this->add_signal(node);
    }

    // get taps
    for (auto node : ctx->taps()) {
      trace_width_ += this->add_signal(node);
    }
  }
}

uint32_t tracerimpl::add_signal(ioportimpl* node) {
  auto name = node->name();
  if (is_system_signal(name)) {
    if (unique_names_.exits(name))
      return 0;
  } else {
    if (contexts_.size() >= 2) {
      name = node->ctx()->name() + "_" + name;
    }
  }
  name = unique_names_.get(name);
  signals_.emplace_back(signal_t{name, node});
  return node->size();
}

void tracerimpl::eval() {
  // advance simulation
  simulatorimpl::eval();

  // allocate trace new trace block
  if (nullptr == trace_blocks_tail_
   || NUM_BLOCKS == trace_blocks_tail_->size) {
    auto trace_block = new trace_block_t(NUM_BLOCKS, trace_width_);
    if (nullptr == trace_blocks_head_) {
      trace_blocks_head_ = trace_block;
    }
    if (trace_blocks_tail_) {
      trace_blocks_tail_->next = trace_block;
    }
    trace_blocks_tail_ = trace_block;
    ++num_trace_blocks_;
  }

  // log trace data
  uint32_t block_idx = trace_blocks_tail_->size++;
  auto& block = trace_blocks_tail_->data.at(block_idx);
  uint32_t dst_offset = 0;
  for (auto& trace : signals_) {
    auto& value = trace.node->value();
    block.copy(dst_offset, value, 0, value.size());
    dst_offset += value.size();
  }
}

void tracerimpl::toText(const std::string& file) {
  // log trace data
  std::ofstream out(file);
  uint32_t t = 0;
  uint32_t max_traces = NUM_BLOCKS * (num_trace_blocks_ - 1) +
                          (trace_blocks_tail_ ? trace_blocks_tail_->size : 0);
  auto indices_width = std::to_string(max_traces).length();
  auto trace_block = trace_blocks_head_;
  while (trace_block) {
    for (uint32_t block_idx = 0; block_idx < trace_block->size; ++block_idx) {
      auto& block = trace_block->data.at(block_idx);
      out << std::setw(indices_width) << t++ << ":";
      auto src_offset = 0;
      auto_separator sep(",");
      for (auto& signal : signals_) {
        bitvector value = get_value(block, signal.node->size(), src_offset);
        src_offset += value.size();
        out << sep << " " << signal.name << "=" << value;
      }
      out << std::endl;
    }
    trace_block = trace_block->next;
  }
}

void tracerimpl::toVCD(const std::string& file) {
  // remove [] from signal name
  auto fixup_name = [&](const std::string name) {
    std::string ret(name);
    ret.erase(std::remove(ret.begin(), ret.end(), '['), ret.end());
    ret.erase(std::remove(ret.begin(), ret.end(), ']'), ret.end());
    return ret;
  };

  std::ofstream out(file);
  // log trace header
  out << "$timescale 1 ns $end" << std::endl;
  for (auto& tap : signals_) {
    auto name = fixup_name(tap.name);
    out << "$var reg " << tap.node->size() << ' ' << name << ' '
         << name << " $end" << std::endl;
  }
  out << "$enddefinitions $end" << std::endl;

  // log trace data
  uint32_t t = 0;
  auto trace_block = trace_blocks_head_;
  while (trace_block) {
    for (uint32_t block_idx = 0; block_idx < trace_block->size; ++block_idx) {
      auto& block = trace_block->data.at(block_idx);
      out << '#' << t++ << std::endl;
      auto value_iter = block.begin();
      for (auto& signal : signals_) {
        auto signal_size = signal.node->size();
        if (signal_size > 1)
          out << 'b';
        for (int j = signal_size-1; j >= 0; --j) {
          out << (*value_iter++ ? '1' : '0');
        }
        if (signal_size > 1)
          out << ' ';
        out << fixup_name(signal.name) << std::endl;
      }
    }
    trace_block = trace_block->next;
  }
}

void tracerimpl::toTestBench(const std::string& file, const std::string& module) {
  //--
  auto full_name = [&](const lnode& x) {
    return stringf("__module%d__.%s%d", x.impl()->ctx()->id(), x.name().c_str(), x.id());
  };

  //--
  auto signal_name = [&](ioimpl* node) {
    if (is_system_signal(node->name()))
      return node->name();
    for (auto& signal : signals_) {
      if (signal.node->id() == node->id())
        return signal.name;
    }
    return std::string();
  };

  //--
  auto print_type = [](std::ostream& out, ioimpl* node) {
    out << (type_input == node->type() ? "reg" : "wire");
    if (node->size() > 1)
      out << "[" << (node->size() - 1) << ":0]";
  };

  //--
  auto print_value = [](std::ostream& out, const bitvector& value) {
    out << value.size() << "'h";
    auto oldflags = out.flags();
    out.setf(std::ios_base::hex, std::ios_base::basefield);

    bool skip_zeros = true;
    uint32_t word = 0;
    auto size = value.size();

    for (auto it = value.begin() + (size - 1); size;) {
      word = (word << 0x1) | *it--;
      if (0 == (--size & 0x3)) {
        if (0 == size || (word != 0 ) || !skip_zeros) {
          out << word;
          skip_zeros = false;
        }
        word = 0;
      }
    }
    if (0 != (size & 0x3)) {
      out << word;
    }
    out.flags(oldflags);
  };

  //--
  auto print_module = [&](std::ostream& out, context* ctx) {
    auto_separator sep(", ");
    out << ctx->name() << " __module" << ctx->id() << "__(";
    for (auto input : ctx->inputs()) {
      out << sep << "." << input->name() << "(" << signal_name(input) << ")";
    }
    for (auto output : ctx->outputs()) {
      out << sep << "." << output->name() << "(" << signal_name(output) << ")";
    }
    out << ");" << std::endl;
    return true;
  };

  std::ofstream out(file);

  // log header
  out << "`timescale 1ns/1ns" << std::endl;
  out << "`include \"" << module << "\"" << std::endl << std::endl;
  out << "`define check(x, y) if ((x == y) !== 1'b1)"
         " if ((x == y) === 1'b0) $error(\"x=%h, expected=%h\", x, y);"
         " else $warning(\"x=%h, expected=%h\", x, y)" << std::endl << std::endl;
  out << "module testbench();" << std::endl << std::endl;

  {
    auto_indent indent(out);
    int has_clock = 0;
    int has_taps = 0;

    // declare signals
    for (auto& signal : signals_) {
      print_type(out, signal.node);
      out << " " << signal.name << ";" << std::endl;
      has_clock |= (signal.name == "clk");
      has_taps |= (type_tap == signal.node->type());
    }
    out << std::endl;

    // declare modules
    for (auto ctx : contexts_) {
      print_module(out, ctx);
    }
    out << std::endl;

    if (has_taps) {
      // declare taps
      for (auto& signal : signals_) {
        if (type_tap != signal.node->type())
          continue;
        out << "assign " << signal.name << " = " << full_name(signal.node->src(0)) << ";" << std::endl;
      }
      out << std::endl;
    }

    // declare clock process
    if (has_clock) {
      out << "always begin" << std::endl;
      {
        auto_indent indent1(out);
        out << "#1 clk = !clk;" << std::endl;
      }
      out << "end" << std::endl << std::endl;
    }

    // declare simulation process
    out << "initial begin" << std::endl;
    {
      auto_indent indent1(out);

      auto trace_block = trace_blocks_head_;
      while (trace_block) {
        for (uint32_t block_idx = 0; block_idx < trace_block->size; ++block_idx) {
          auto& block = trace_block->data.at(block_idx);
          {
            out << "#0";
            auto src_offset = 0;
            for (auto& signal : signals_) {
              if (type_input == signal.node->type()) {
                auto value = get_value(block, signal.node->size(), src_offset);
                out << " " << signal.name << "=";
                print_value(out, value);
                out << ";";
              }
              src_offset += signal.node->size();
            }
            out << std::endl;
          }
          {
            out << "#1";
            auto src_offset = 0;
            for (auto& signal : signals_) {
              if (type_input != signal.node->type()) {
                auto value = get_value(block, signal.node->size(), src_offset);
                out << " `check(" << signal.name << ", ";
                print_value(out, value);
                out << ");";
              }
              src_offset += signal.node->size();
            }
            out << std::endl;
          }
        }
        trace_block = trace_block->next;
      }
      out << "#1 $finish;" << std::endl;
    }
    out << "end" << std::endl << std::endl;
  }

  // log footer
  out << "endmodule" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////

ch_tracer::ch_tracer(const ch_device_list& devices)
  : ch_simulator(new tracerimpl(devices))
{}

ch_tracer::ch_tracer(simulatorimpl* impl) : ch_simulator(impl) {}

ch_tracer::ch_tracer(const ch_tracer& other) : ch_simulator(other) {}

ch_tracer::ch_tracer(ch_tracer&& other) : ch_simulator(std::move(other)) {}

ch_tracer::~ch_tracer() {}

ch_tracer& ch_tracer::operator=(const ch_tracer& other) {
  ch_simulator::operator=(other);
  return *this;
}

ch_tracer& ch_tracer::operator=(ch_tracer&& other) {
  ch_simulator::operator=(std::move(other));
  return *this;
}

void ch_tracer::toText(const std::string& file) {
  return reinterpret_cast<tracerimpl*>(impl_)->toText(file);
}

void ch_tracer::toVCD(const std::string& file) {
  return reinterpret_cast<tracerimpl*>(impl_)->toVCD(file);
}

void ch_tracer::toTestBench(const std::string& file, const std::string& module) {
  return reinterpret_cast<tracerimpl*>(impl_)->toTestBench(file, module);
}
