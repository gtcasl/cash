#include "tracerimpl.h"
#include "tracer.h"
#include "ioimpl.h"
#include "bindimpl.h"

using namespace ch::internal;

#define NUM_TRACES 100

tracerimpl::tracerimpl(const ch_device_list& devices)
  : simulatorimpl(devices)
  , trace_width_(0)
  , ticks_(0)
  , trace_head_(nullptr)
  , trace_tail_(nullptr)
  , num_traces_(0) {
  // initialize
  this->initialize();
}

tracerimpl::~tracerimpl() {
  auto block = trace_head_;
  while (block) {
    auto next = block->next;
    block->~trace_block_t();
    ::operator delete [](block);
    block = next;
  }
}

void tracerimpl::initialize() {
  //--
  auto add_signal = [&](ioportimpl* node) {
    signals_.emplace_back(node);
    return node->size();
  };

  //--
  std::function<uint32_t (context*, bool)>
      resurse_get_signals = [&](context* ctx, bool is_top) {
    uint32_t trace_width = 0;
    if (is_top) {
      // get inputs
      for (auto node : ctx->inputs()) {
        trace_width += add_signal(node);
      }
      // get outputs
      for (auto node : ctx->outputs()) {
        trace_width += add_signal(node);
      }
    }
    // get taps
    for (auto node : ctx->taps()) {
      trace_width += add_signal(node);
    }
    // visit submodules
    for (auto binding : ctx->bindings()) {
      trace_width += resurse_get_signals(binding->module(), false);
    }
    return trace_width;
  };

  // register signals
  auto trace_width = 0;
  for (auto ctx : contexts_) {
    trace_width += resurse_get_signals(ctx, true);
  }

  trace_width_ = trace_width + signals_.size();
  prev_values_.resize(signals_.size());
  valid_mask_.resize(signals_.size());
}

void tracerimpl::eval() {
  // advance simulation
  simulatorimpl::eval();

  // allocate new trace block
  auto block_width = NUM_TRACES * trace_width_;
  if (nullptr == trace_tail_
   || (trace_tail_->size + trace_width_) > block_width) {
    this->allocate_trace(block_width);
  }

  // log trace data
  valid_mask_.reset();
  auto dst_block = trace_tail_->data;
  auto dst_offset = trace_tail_->size;
  dst_offset += valid_mask_.size();
  for (uint32_t i = 0, n = signals_.size(); i < n; ++i) {
    auto value = signals_.at(i)->value();
    auto& prev = prev_values_.at(i);
    if (prev.first) {
      if (0 == bv_cmp(reinterpret_cast<const block_type*>(prev.first),
                      prev.second, value->words(), 0, value->size()))
        continue;
    }
    prev.first = dst_block;
    prev.second = dst_offset;
    bv_copy(reinterpret_cast<block_type*>(dst_block),
            dst_offset, value->words(), 0, value->size());
    dst_offset += value->size();    
    valid_mask_[i] = true;
  }
  // set valid mask
  bv_copy(dst_block, trace_tail_->size, valid_mask_.words(), 0, valid_mask_.size());

  // updsate offset
  trace_tail_->size = dst_offset;

  ++ticks_;
}

void tracerimpl::allocate_trace(uint32_t block_width) {
  auto block_size = (bitwidth_v<block_t> / 8) * ceildiv(block_width, bitwidth_v<block_t>);
  auto buf = new uint8_t[sizeof(trace_block_t) + block_size]();
  auto data = reinterpret_cast<block_t*>(buf + sizeof(trace_block_t));
  auto trace_block = new (buf) trace_block_t(data);
  if (nullptr == trace_head_) {
    trace_head_ = trace_block;
  }
  if (trace_tail_) {
    trace_tail_->next = trace_block;
  }
  trace_tail_ = trace_block;
  ++num_traces_;
}

std::vector<context*> tracerimpl::get_module_path(context* ctx) {
  std::vector<context*> path;
  context* curr = ctx;
  while (curr) {
    path.push_back(curr);
    curr = curr->parent();
  }
  std::reverse(path.begin(), path.end());  
  return path;
}

void tracerimpl::toText(std::ofstream& out) {
  //--
  auto full_name = [&](ioportimpl* node) {
    // ignore scope for single contexts
    if ((1 == contexts_.size())
     && (0 == contexts_.front()->bindings().size())) {
      return node->name();
    }
    std::stringstream ss;
    auto path = this->get_module_path(node->ctx());
    for (auto ctx : path) {
      if (contexts_.size() == 1
       && contexts_[0] == ctx)
        continue;
      ss << ctx->name() << ".";
    }
    ss << node->name();
    return ss.str();
  };

  uint32_t t = 0;
  auto mask_width = valid_mask_.size();
  auto indices_width = std::to_string(ticks_).length();

  for (uint32_t i = 0, n = signals_.size(); i < n; ++i) {
    prev_values_[i] = std::make_pair<block_t*, uint32_t>(nullptr, 0);
  }

  auto trace_block = trace_head_;
  while (trace_block) {
    auto src_block = trace_block->data;
    auto src_width = trace_block->size;
    uint32_t src_offset = 0;
    while (src_offset < src_width) {
      uint32_t mask_offset = src_offset;
      src_offset += mask_width;
      out << std::setw(indices_width) << t << ":";
      auto_separator sep(",");
      for (uint32_t i = 0, n = signals_.size(); i < n; ++i) {
        auto signal = signals_.at(i);
        auto signal_type = signal->type();
        auto signal_size = signal->size();
        auto signal_name = full_name(signal);
        bool valid = bv_get(src_block, mask_offset + i);
        if (valid) {
          auto value = get_value(src_block, signal_size, src_offset);
          out << sep << " " << signal_name << "=" << value;
          if (type_input != signal_type) {
            auto& prev = prev_values_.at(i);
            prev.first = src_block;
            prev.second = src_offset;
          }
          src_offset += signal_size;
        } else {
          if (type_input != signal_type) {
            auto& prev = prev_values_.at(i);
            assert(prev.first);
            auto value = get_value(prev.first, signal_size, prev.second);
            out << sep << " " << signal_name << "=" << value;
          }
        }
      }
      out << std::endl;
      ++t;
    }
    trace_block = trace_block->next;
  }
}

void tracerimpl::toVCD(std::ofstream& out) {
  // remove [] from signal name
  auto fixup_name = [&](const std::string name) {
    std::string ret(name);
    ret.erase(std::remove(ret.begin(), ret.end(), '['), ret.end());
    ret.erase(std::remove(ret.begin(), ret.end(), ']'), ret.end());
    return ret;
  };

  dup_tracker<std::string> dup_mod_names;

  // log trace header
  out << "$timescale 1 ns $end" << std::endl;
  std::list<context*> ctx_stack;
  for (auto node : signals_) {
    auto name = fixup_name(node->name());
    // ignore scope for single contexts
    if ((1 == contexts_.size())
     && (0 == contexts_.front()->bindings().size())) {
      out << "$var reg " << node->size() << ' ' << node->id() << ' '
          << name << " $end" << std::endl;
    } else {
      auto path = this->get_module_path(node->ctx());
      auto path_it = path.begin();
      auto stack_it = ctx_stack.begin();
      while (path_it != path.end()
          && stack_it != ctx_stack.end()) {
        if (*stack_it != *path_it) {
          auto del_it = stack_it;
          while (del_it != ctx_stack.end()) {
            out << "$upscope $end" << std::endl;
            del_it = ctx_stack.erase(del_it);
          }
          break;
        }
        ++path_it;
        ++stack_it;
      }
      while (path_it != path.end()) {
        auto ctx = *path_it++;
        std::string mod_name = fixup_name(ctx->name());
        auto num_dups = dup_mod_names.insert(mod_name);
        if (num_dups) {
          mod_name = stringf("%s_%ld", mod_name.c_str(), num_dups);
        }
        out << "$scope module " << mod_name << " $end" << std::endl;
        ctx_stack.push_back(ctx);
      }
      out << "$var reg " << node->size() << ' ' << node->id() << ' '
          << name << " $end" << std::endl;
    }
  }
  while (!ctx_stack.empty()) {
    out << "$upscope $end" << std::endl;
    ctx_stack.pop_back();
  }
  out << "$enddefinitions $end" << std::endl;

  // log trace data
  uint32_t t = 0;
  auto mask_width = valid_mask_.size();

  auto trace_block = trace_head_;
  while (trace_block) {
    auto src_block = trace_block->data;
    auto src_width = trace_block->size;
    uint32_t src_offset = 0;
    while (src_offset < src_width) {
      uint32_t mask_offset = src_offset;
      src_offset += mask_width;
      bool new_trace = false;
      for (uint32_t i = 0, n = signals_.size(); i < n; ++i) {
        bool valid = bv_get(src_block, mask_offset + i);
        if (valid) {
          if (!new_trace) {
            out << '#' << t << std::endl;
            new_trace = true;
          }
          auto signal = signals_.at(i);
          auto signal_size = signal->size();
          auto value = get_value(src_block, signal_size, src_offset);
          src_offset += signal_size;
          if (signal_size > 1)
            out << 'b';
          for (auto it = value.rbegin(), end = value.rend(); it != end;) {
            out << (*it++ ? '1' : '0');
          }
          if (signal_size > 1)
            out << ' ';
          out << signal->id() << std::endl;
        }
      }
      if (new_trace)
        out << std::endl;
      ++t;
    }
    trace_block = trace_block->next;
  }
}

void tracerimpl::toTestBench(std::ofstream& out,
                             const std::string& module,
                             bool passthru) {
  //--
  std::set<context*> root_ctx_map(contexts_.begin(), contexts_.end());

  //--
  auto get_signal_path = [&](ioportimpl* node) {
    std::stringstream ss;
    auto path = this->get_module_path(node->ctx());
    for (uint32_t i = 0; i < path.size(); ++i) {
      auto ctx = path.at(i);
      if (i == 0) {
        ss << "__module" << ctx->id();
      } else {
        uint32_t bind_id = 0;
        for (auto bind : ctx->parent()->bindings()) {
          if (bind->module()->id() == ctx->id()) {
            bind_id = bind->id();
            break;
          }
        }
        ss << "." << ctx->name() << bind_id;
      }
    }

    auto module_path = ss.str();
    return stringf("%s.%s", module_path.c_str(), node->name().c_str());
  };

  //--
  auto get_signal_name = [&](lnodeimpl* node) {
    std::stringstream ss;
    auto path = this->get_module_path(node->ctx());
    for (uint32_t i = 0; i < path.size(); ++i) {
      auto ctx = path.at(i);
      if (0 == i) {
        if (contexts_.size() != 1) {
          ss << "__module" << ctx->id();
        }
      } else {
        uint32_t bind_id = 0;
        for (auto bind : ctx->parent()->bindings()) {
          if (bind->module()->id() == ctx->id()) {
            bind_id = bind->id();
            break;
          }
        }
        ss << "_" << ctx->name() << bind_id;
      }
    }
    auto module_path = ss.str();
    if (module_path.empty()) {
      return node->name();
    } else {
      return stringf("%s_%s", module_path.c_str(), node->name().c_str());
    }
  };

  //--
  auto find_signal_name = [&](ioimpl* node) {
    if ((node->name() == "clk")
     || (node->name() == "reset"))
      return node->name();
    for (auto signal : signals_) {
      if (signal->id() == node->id())
        return get_signal_name(signal);
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
  auto print_value = [](std::ostream& out, const bv_t& value) {
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
    out << ctx->name() << " __module" << ctx->id() << "(";
    for (auto input : ctx->inputs()) {
      out << sep << "." << input->name() << "(" << find_signal_name(input) << ")";
    }
    for (auto output : ctx->outputs()) {
      out << sep << "." << output->name() << "(" << find_signal_name(output) << ")";
    }
    out << ");" << std::endl;
    return true;
  };

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
    int has_internal_signals = 0;

    // declare signals
    for (auto signal : signals_) {
      print_type(out, signal);
      out << " " << get_signal_name(signal) << ";" << std::endl;
      has_clock |= (signal->name() == "clk");
      has_internal_signals |= (type_tap == signal->type()
                            || 0 == root_ctx_map.count(signal->ctx()));
    }
    out << std::endl;

    // declare modules
    for (auto ctx : contexts_) {
      print_module(out, ctx);
      out << std::endl;
    }

    if (has_internal_signals) {
      for (auto signal : signals_) {
        if (type_tap != signal->type()
         && root_ctx_map.count(signal->ctx()))
          continue;
        out << "assign " << get_signal_name(signal) << " = " << get_signal_path(signal) << ";" << std::endl;
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

      uint64_t tc = 0, tp = 0;
      auto mask_width = valid_mask_.size();

      for (uint32_t i = 0, n = signals_.size(); i < n; ++i) {
        prev_values_[i] = std::make_pair<block_t*, uint32_t>(nullptr, 0);
      }

      auto trace_block = trace_head_;
      while (trace_block) {
        auto src_block = trace_block->data;
        auto src_width = trace_block->size;
        uint32_t src_offset = 0;
        while (src_offset < src_width) {
          uint32_t mask_offset = src_offset;
          auto in_offset = mask_offset + mask_width;
          auto out_offset = mask_offset + mask_width;
          bool in_trace = false;
          bool out_trace = false;
          {
            for (uint32_t i = 0, n = signals_.size(); i < n; ++i) {
              bool valid = bv_get(src_block, mask_offset + i);
              if (valid) {
                auto signal = signals_.at(i);
                auto signal_type = signal->type();
                auto signal_size = signal->size();
                auto signal_name = get_signal_name(signal);
                if (0 == root_ctx_map.count(signal->ctx())  // is nested signal
                 || (tc != 0 && signal->name() == "clk")    // is not clk signal initialization
                 || (type_input != signal_type)) {          // is not an input signal
                  in_offset += signal_size;
                  continue;
                }
                if (!in_trace) {
                  out << "#" << (tc - tp);
                  tp = tc;
                  in_trace = true;
                }
                auto value = get_value(src_block, signal_size, in_offset);
                in_offset += signal_size;
                out << " " << signal_name << "=";
                print_value(out, value);
                out << ";";
              }
            }
            if (in_trace) {
              out << std::endl;
            }
          }

          {
            for (uint32_t i = 0, n = signals_.size(); i < n; ++i) {
              auto signal = signals_.at(i);
              auto signal_type = signal->type();
              auto signal_size = signal->size();
              auto signal_name = get_signal_name(signal);
              bool valid = bv_get(src_block, mask_offset + i);
              if (valid) {
                if (type_input == signal_type) {
                  out_offset += signal_size;
                  continue;
                }

                auto& prev = prev_values_.at(i);
                prev.first = src_block;
                prev.second = out_offset;

                if (passthru
                 && (tc + 1) < ticks_) {
                  out_offset += signal_size;
                  continue;
                }

                if (!out_trace) {
                  out << "#" << (tc - tp + 1);
                  tp = tc + 1;
                  out_trace = true;
                }

                auto value = get_value(src_block, signal_size, out_offset);
                out_offset += signal_size;
                out << " `check(" << signal_name << ", ";
                print_value(out, value);
                out << ");";
              } else {
                if (type_input == signal_type)
                  continue;

                if (passthru
                 && (tc + 1) < ticks_)
                  continue;

                if (!out_trace) {
                  out << "#" << (tc - tp  + 1);
                  tp = tc + 1;
                  out_trace = true;
                }

                auto& prev = prev_values_.at(i);
                assert(prev.first);
                auto value = get_value(prev.first, signal_size, prev.second);
                out << " `check(" << signal_name << ", ";
                print_value(out, value);
                out << ");";
              }
            }
            if (out_trace) {
              out << std::endl;
            }
          }

          src_offset = in_offset;
          ++tc;
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

void tracerimpl::toVerilator(std::ofstream& out,
                             const std::string& module) {
  //--
  auto print_value = [](std::ostream& out, const bv_t& value) {
    out << "0x";
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


  uint64_t tc = 0;
  auto mask_width = valid_mask_.size();

  for (uint32_t i = 0, n = signals_.size(); i < n; ++i) {
    prev_values_[i] = std::make_pair<block_t*, uint32_t>(nullptr, 0);
  }

  out << "bool eval(" << module << "* device, uint64_t tick) {" << std::endl;
  out << "switch (tick) {" << std::endl;
  auto trace_block = trace_head_;
  while (trace_block) {
    auto src_block = trace_block->data;
    auto src_width = trace_block->size;
    uint32_t src_offset = 0;
    while (src_offset < src_width) {
      uint32_t mask_offset = src_offset;
      auto in_offset = mask_offset + mask_width;
      auto out_offset = mask_offset + mask_width;
      bool trace_enable = false;
      {
        for (uint32_t i = 0, n = signals_.size(); i < n; ++i) {
          bool valid = bv_get(src_block, mask_offset + i);
          if (valid) {
            auto signal = signals_.at(i);
            auto signal_type = signal->type();
            auto signal_size = signal->size();
            if ((tc != 0 && signal->name() == "clk")
             || (type_input != signal_type)) {
              in_offset += signal_size;
              continue;
            }
            if (!trace_enable) {
              out << "case " << tc << ":" << std::endl;
              trace_enable = true;
            }
            auto value = get_value(src_block, signal_size, in_offset);
            in_offset += signal_size;
            out << "device->" << signal->name() << "=";
            print_value(out, value);
            out << ";";
          }
        }
      }

      {
        for (uint32_t i = 0, n = signals_.size(); i < n; ++i) {
          auto signal = signals_.at(i);
          auto signal_type = signal->type();
          auto signal_size = signal->size();
          bool valid = bv_get(src_block, mask_offset + i);
          if (valid) {
            if (type_input == signal_type) {
              out_offset += signal_size;
              continue;
            }

            auto& prev = prev_values_.at(i);
            prev.first = src_block;
            prev.second = out_offset;

            if ((tc + 1) < ticks_) {
              out_offset += signal_size;
              continue;
            }

            if (!trace_enable) {
              out << "case " << (tc + 1) << ":" << std::endl;
              trace_enable = true;
            }

            auto value = get_value(src_block, signal_size, out_offset);
            out_offset += signal_size;
            out << "assert(device->" << signal->name() << " == ";
            print_value(out, value);
            out << ");";
          } else {
            if (type_input == signal_type)
              continue;

            if ((tc + 1) < ticks_)
              continue;

            if (!trace_enable) {
              out << "case " << (tc + 1) << ":" << std::endl;
              trace_enable = true;
            }

            auto& prev = prev_values_.at(i);
            assert(prev.first);
            auto value = get_value(prev.first, signal_size, prev.second);
            out << "assert(device->" << signal->name() << " == ";
            print_value(out, value);
            out << ");";
          }
        }
      }
      if (trace_enable) {
        out << "break;" << std::endl;
      }
      src_offset = in_offset;
      ++tc;
    }
    trace_block = trace_block->next;
  }
  out << "}" << std::endl;
  out << "return (tick < " << ticks_ << ");" << std::endl;
  out << "}" << std::endl;
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

void ch_tracer::toText(std::ofstream& out) {
  return reinterpret_cast<tracerimpl*>(impl_)->toText(out);
}

void ch_tracer::toVCD(std::ofstream& out) {
  return reinterpret_cast<tracerimpl*>(impl_)->toVCD(out);
}

void ch_tracer::toTestBench(std::ofstream& out,
                            const std::string& module,
                            bool passthru) {
  return reinterpret_cast<tracerimpl*>(impl_)->toTestBench(out, module, passthru);
}

void ch_tracer::toVerilator(std::ofstream& out,
                            const std::string& module) {
  return reinterpret_cast<tracerimpl*>(impl_)->toVerilator(out, module);
}
