#include "tracerimpl.h"
#include "tracer.h"
#include "ioimpl.h"

using namespace ch::internal;

#define NUM_BLOCKS 100

tracerimpl::tracerimpl(const ch_device_list& devices)
  : simulatorimpl(devices)
  , trace_width_(0)
  , trace_blocks_head_(nullptr)
  , trace_blocks_tail_(nullptr)
  , num_trace_blocks_(0) {
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
      trace_width_ += this->add_signal(node->name(), node);
    }

    // get outputs
    for (auto node : ctx->outputs()) {
      trace_width_ += this->add_signal(node->name(), node);
    }

    // get taps
    for (auto node : ctx->taps()) {
      trace_width_ += this->add_signal(node->name(), node);
    }
  }
}

uint32_t tracerimpl::add_signal(const std::string& name, ioimpl* node) {
  signals_.emplace_back(signal_t{unique_trace_names_.get(name), node});
  return node->size();
}

void tracerimpl::eval(ch_tick t) {
  // advance simulation
  simulatorimpl::eval(t);

  // allocate trace new trace block
  if (nullptr == trace_blocks_tail_
   || trace_blocks_tail_->size == NUM_BLOCKS) {
    auto trace_block = new trace_block_t(100, trace_width_);
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
    block.write(dst_offset, value.data(), value.num_bytes(), 0, value.size());
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
        bitvector tmp(signal.node->size());
        block.read(src_offset, tmp.data(), tmp.num_bytes(), 0, tmp.size());
        out << sep << " " << signal.name << "=" << tmp;
        src_offset += tmp.size();
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

void tracerimpl::toTestBench(const std::string& /*file*/) {
  //--
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

void ch_tracer::toTestBench(const std::string& file) {
  return reinterpret_cast<tracerimpl*>(impl_)->toTestBench(file);
}
