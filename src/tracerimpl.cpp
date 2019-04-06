#include "tracerimpl.h"
#include "tracer.h"
#include "ioimpl.h"
#include "bindimpl.h"

using namespace ch::internal;

#define NUM_TRACES 100

auto remove_path = [](const std::string& path) {
  auto pos = path.find('.');
  return (pos != std::string::npos) ? path.substr(pos+1) : path;
};

tracerimpl::tracerimpl(const ch_device_list& devices)
  : simulatorimpl(devices)
  , trace_width_(0)
  , ticks_(0)
  , trace_head_(nullptr)
  , trace_tail_(nullptr)
  , num_traces_(0)
  , is_merged_context_(!(1 == contexts_.size() && 0 == contexts_.back()->bindings().size())) {
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
  auto trace_width = 0;
  auto clk = eval_ctx_->sys_clk();
  if (clk) {
    trace_width += add_signal(clk);
  }

  auto reset = eval_ctx_->sys_reset();
  if (reset) {
    trace_width += add_signal(reset);
  }
  for (auto node : eval_ctx_->inputs()) {
    auto signal = reinterpret_cast<ioportimpl*>(node);
    if (signal == clk || signal == reset)
      continue;
    trace_width += add_signal(signal);
  }
  for (auto node : eval_ctx_->outputs()) {
    auto signal = reinterpret_cast<ioportimpl*>(node);
    trace_width += add_signal(signal);
  }
  for (auto node : eval_ctx_->taps()) {
    auto signal = reinterpret_cast<ioportimpl*>(node);
    trace_width += add_signal(signal);
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

void tracerimpl::toText(std::ofstream& out) {
  //--
  auto get_signal_name = [&](ioportimpl* node) {
    if (is_merged_context_ && 1 == contexts_.size()) {
      return remove_path(node->name());
    }
    return node->name();
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
        auto signal_name = get_signal_name(signal);
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
  dup_tracker<std::string> dup_mod_names;

  // log trace header
  out << "$timescale 1 ns $end" << std::endl;
  std::list<std::string> mod_stack;
  for (auto node : signals_) {
    if (!is_merged_context_) {
      out << "$var reg " << node->size() << ' ' << node->id() << ' '
          << node->name() << " $end" << std::endl;
    } else {
      auto path = split(node->name(), '.');
      auto name = path.back(); // get name
      path.pop_back(); // remove name
      if (path.empty()) {
        path.push_back("sys");
      }
      auto path_it = path.begin();
      auto stack_it = mod_stack.begin();
      while (path_it != path.end()
          && stack_it != mod_stack.end()) {
        if (*stack_it != *path_it) {
          auto del_it = stack_it;
          while (del_it != mod_stack.end()) {
            out << "$upscope $end" << std::endl;
            del_it = mod_stack.erase(del_it);
          }
          break;
        }
        ++path_it;
        ++stack_it;
      }
      while (path_it != path.end()) {
        auto mod = *path_it++;
        auto mod_name = mod;
        auto num_dups = dup_mod_names.insert(mod_name);
        if (num_dups) {
          mod_name = stringf("%s_%ld", mod_name.c_str(), num_dups);
        }
        out << "$scope module " << mod_name << " $end" << std::endl;
        mod_stack.push_back(mod);
      }
      out << "$var reg " << node->size() << ' ' << node->id() << ' '
          << name << " $end" << std::endl;
    }
  }
  while (!mod_stack.empty()) {
    out << "$upscope $end" << std::endl;
    mod_stack.pop_back();
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
          if (signal_size > 1) {
            out << 'b';
          }
          size_t q = 0;
          for (auto it = value.rbegin(), end = value.rend(); it != end;) {
            ++q;
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
                             const std::string& moduleFileName,
                             bool passthru) {
  //--
  auto id_from_name = [&](const std::string& name)->uint32_t {
    auto pos = name.find_last_of('_');
    assert(pos != std::string::npos);
    return std::stoul(name.substr(pos+1).c_str(), nullptr);
  };

  //--
  auto find_ctx = [&](const std::string& name)->context* {
    auto id = id_from_name(name);
    for (auto ctx : contexts_) {
      if (ctx->id() == id)
        return ctx;
    }
    return nullptr;
  };

  //--
  auto find_module = [&](context* ctx, const std::string& name)->context* {
    auto id = id_from_name(name);
    for (auto node : ctx->bindings()) {
      auto binding = reinterpret_cast<bindimpl*>(node);
      if (binding->id() == id)
        return binding->module();
    }
    return nullptr;
  };

  //--
  auto find_tap = [&](context* ctx, const std::string& name)->tapimpl* {
    for (auto node : ctx->taps()) {
      auto tap = reinterpret_cast<tapimpl*>(node);
      if (tap->name() == name)
        return tap;
    }
    return nullptr;
  };

  //--
  auto netlist_name = [&](lnodeimpl* node)->std::string {
    switch (node->type()) {
    case type_bindin:
    case type_bindout: {
      std::stringstream ss;
      auto p = reinterpret_cast<bindportimpl*>(node);
      ss << p->binding()->type() << "_" << p->binding()->name() << "_"
         << p->binding()->id() << "_" << p->ioport().name();
      return ss.str();
    }
    case type_time:
      return "$time";
    default: {
      std::stringstream ss;
      ss << node->type();
      if (!node->name().empty()) {
        ss << "_" << node->name();
      }
      ss << "_" << node->id();
      return ss.str();
    }
    }
  };

  //--
  auto get_tap_path = [&](tapimpl* node) {
    if (is_merged_context_) {
      auto path = split(node->name(), '.');
      auto name = path.back(); // get name
      path.pop_back(); // remove name
      assert(!path.empty());
      context* ctx = find_ctx(path[0]);
      for (uint32_t i = 1; i < path.size(); ++i) {
        ctx = find_module(ctx, path[i]);
      }
      auto tap = find_tap(ctx, name);
      auto pos = node->name().find_last_of('.');
      auto sname = netlist_name(tap->src(0).impl());
      return stringf("%s.%s", node->name().substr(0, pos).c_str(), sname.c_str());
    } else {
      auto tap = find_tap(contexts_[0], node->name());
      return netlist_name(tap->src(0).impl());
    }
  };

  //--
  auto get_signal_name = [&](ioportimpl* node) {
    auto path = node->name();
    if (is_merged_context_) {
      auto no_root = remove_path(path);
      if (no_root == "clk" || no_root == "reset")
        return no_root;
      if (1 == contexts_.size()) {
        path = no_root;
      }
    }
    std::replace(path.begin(), path.end(), '.', '_');
    return path;
  };

  //--
  auto find_signal_name = [&](ioportimpl* node) {
    if ((node->name() == "clk") || (node->name() == "reset"))
      return node->name();
    auto name = node->name();
    if (is_merged_context_) {
      name = stringf("%s_%d.%s", node->ctx()->name().c_str(), node->ctx()->id(), name.c_str());
    }
    for (auto signal : signals_) {      
      if (signal->name() == name)
        return get_signal_name(signal);
    }
    std::abort();
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
    out << ctx->name() << " " << ctx->name() << "_" << ctx->id() << "(";
    for (auto node : ctx->inputs()) {
      auto input = reinterpret_cast<inputimpl*>(node);
      out << sep << "." << input->name() << "(" << find_signal_name(input) << ")";
    }
    for (auto node : ctx->outputs()) {
      auto output = reinterpret_cast<outputimpl*>(node);
      out << sep << "." << output->name() << "(" << find_signal_name(output) << ")";
    }
    out << ");" << std::endl;
    return true;
  };

  // log header
  out << "`timescale 1ns/1ns" << std::endl;
  out << "`include \"" << moduleFileName << "\"" << std::endl << std::endl;
  out << "`define check(x, y) if ((x == y) !== 1'b1)"
         " if ((x == y) === 1'b0) $error(\"x=%h, expected=%h\", x, y);"
         " else $warning(\"x=%h, expected=%h\", x, y)" << std::endl << std::endl;
  out << "module testbench();" << std::endl << std::endl;

  {
    auto_indent indent(out);
    int has_clock = 0;
    int has_taps = 0;

    // declare signals
    for (auto signal : signals_) {
      print_type(out, signal);
      auto name = get_signal_name(signal);
      out << " " << name << ";" << std::endl;
      has_clock |= (name == "clk");
      has_taps |= (type_tap == signal->type());
    }
    out << std::endl;

    // declare modules
    for (auto ctx : contexts_) {
      print_module(out, ctx);
      out << std::endl;
    }

    if (has_taps) {
      for (auto signal : signals_) {
        if (type_tap != signal->type())
          continue;
        out << "assign " << get_signal_name(signal) << " = "
            << get_tap_path(reinterpret_cast<tapimpl*>(signal)) << ";" << std::endl;
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
                if ((type_input != signal_type) // is not an input signal
                 || (tc != 0 && signal_name == "clk")) {  // is not clk signal initialization
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
                             const std::string& moduleTypeName) {
  //--
  auto get_signal_name = [&](ioportimpl* node) {
    auto path = node->name();
    if (is_merged_context_ && 1 == contexts_.size()) {
      path = remove_path(path);
    }
    std::replace(path.begin(), path.end(), '.', '_');
    return path;
  };

  //--
  auto print_value = [](std::ostream& out,
                        const bv_t& value,
                        uint32_t size = 0,
                        uint32_t offset = 0) {
    out << "0x";

    bool skip_zeros = true;
    if (0 == size) {
      size = value.size();
    }

    auto oldflags = out.flags();
    out.setf(std::ios_base::hex, std::ios_base::basefield);

    uint32_t word(0);
    for (auto it = value.begin() + offset + (size - 1); size;) {
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

  if (contexts_.size() > 1) {
    CH_ABORT("multiple devices not supported!");
    return;
  }

  uint64_t tc = 0;
  auto mask_width = valid_mask_.size();

  for (uint32_t i = 0, n = signals_.size(); i < n; ++i) {
    prev_values_[i] = std::make_pair<block_t*, uint32_t>(nullptr, 0);
  }

  out << "bool eval(" << moduleTypeName << "* device, uint64_t tick) {" << std::endl;
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
            auto signal_name = get_signal_name(signal);
            if ((tc != 0 && signal_name == "clk")
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
            if (signal_size > 64) {
              for (uint32_t j = 0; j < signal_size;) {
                out << "device->" << signal_name << "[" << j << "]=";
                auto s = (j+8 <= signal_size) ? 8 : (signal_size-j);
                print_value(out, value, s, j);
                out << ";";
                j += s;
              }
            } else {
              out << "device->" << signal_name << "=";
              print_value(out, value);
              out << ";";
            }            
          }
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
            if (signal_size > 64) {
              for (uint32_t j = 0; j < signal_size;) {
                out << "assert(device->" << signal_name << "[" << j << "] == ";
                auto s = (j+8 <= signal_size) ? 8 : (signal_size-j);
                print_value(out, value, s, j);
                out << ");";
                j += s;
              }
            } else {
              out << "assert(device->" << signal_name << " == ";
              print_value(out, value);
              out << ");";
            }            
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
            if (signal_size > 64) {
              for (uint32_t j = 0; j < signal_size;) {
                out << "assert(device->" << signal_name << "[" << j << "] == ";
                auto s = (j+8 <= signal_size) ? 8 : (signal_size-j);
                print_value(out, value, s, j);
                out << ");";
                j += s;
              }
            } else {
              out << "assert(device->" << signal_name << " == ";
              print_value(out, value);
              out << ");";
            }
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
                            const std::string& moduleFileName,
                            bool passthru) {
  return reinterpret_cast<tracerimpl*>(impl_)->toTestBench(out, moduleFileName, passthru);
}

void ch_tracer::toVerilator(std::ofstream& out,
                            const std::string& moduleTypeName) {
  return reinterpret_cast<tracerimpl*>(impl_)->toVerilator(out, moduleTypeName);
}
