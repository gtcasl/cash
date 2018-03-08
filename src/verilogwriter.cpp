#include "verilogwriter.h"
#include "verilog.h"
#include "context.h"
#include "bindimpl.h"
#include "litimpl.h"
#include "regimpl.h"
#include "memimpl.h"
#include "ioimpl.h"
#include "selectimpl.h"
#include "proxyimpl.h"
#include "memimpl.h"
#include "aluimpl.h"
#include "assertimpl.h"
#include "tickimpl.h"
#include <cstring>

using namespace ch::internal;

const auto IsRegType = [](lnodetype type) {
  return (type_reg == type) || (type_mem == type) || (type_memport == type);
};

const auto is_inline_literal = [](lnodeimpl* node) {
  assert(type_lit == node->get_type());
  return (node->get_size() <= 32);
};

verilogwriter::module_t::module_t(context* p_ctx)
  : ctx(p_ctx)
  , num_temps(0)
{
  for (lnodeimpl* node : ctx->get_nodes()) {
    for (auto& src : node->get_srcs()) {
      uses[src.get_id()].insert(node);
    }
  }
}

bool verilogwriter::module_t::is_inline_subscript(lnodeimpl* node) const {
  assert(type_proxy == node->get_type());
  if (dynamic_cast<proxyimpl*>(node)->get_ranges().size() > 1)
    return false;
  auto it = uses.find(node->get_id());
  if (it != uses.end()) {
    for (lnodeimpl* use : it->second) {
      if (type_proxy == use->get_type()
       || type_memport == use->get_type())
        return false;
    }
  }
  lnodeimpl* src = node->get_src(0).get_impl();
  if (type_proxy == src->get_type()
   || type_memport == src->get_type())
    return false;
  return true;
}

verilogwriter::verilogwriter(std::ostream& out) : out_(out) {
  //--
}

verilogwriter::~verilogwriter() {
  //--
}

void verilogwriter::print(const std::initializer_list<context*>& contexts) {
  // includes
  out_ << "`include \"cash.v\"" << std::endl;
  out_ << std::endl;

  // print top modules
  for (auto ctx : contexts) {
    module_t module(ctx);
    this->print_module(module);
  }
}

bool verilogwriter::print_module(module_t& module) {
  // ensure single instantiation
  if (visited_.count(module.ctx->get_name()))
    return false;
  visited_.insert(module.ctx->get_name());

  {
    // print dependent modules
    auto_separator sep("\n");
    int written = 0;    
    for (auto binding : module.ctx->get_bindings()) {
      out_ << sep;
      module_t child_module(binding->get_module());
      written |= this->print_module(child_module);
    }
    if (written) {
      out_ << std::endl;
    }
  }

  // print header
  this->print_header(module);

  // print body
  this->print_body(module);

  // print footer
  this->print_footer(module);

  return true;
}

void verilogwriter::print_header(module_t& module) {
  //
  // ports declaration
  //
  out_ << "module " << module.ctx->get_name() << '(';
  {
    auto_indent indent(out_);
    auto_separator sep(",");
    for (auto input : module.ctx->get_inputs()) {
      out_ << sep << std::endl;
      this->print_port(module, input);
    }
    for (auto output : module.ctx->get_outputs()) {
      out_ << sep << std::endl;
      this->print_port(module, output);
    }
  }
  out_ << std::endl << ");" << std::endl;
}

void verilogwriter::print_body(module_t& module) {
  //
  // declaration
  //
  {
    auto_indent indent(out_);    
    std::unordered_set<uint32_t> visited;
    int written = 0;
    for (auto node : module.ctx->get_literals()) {
      written |= this->print_decl(module, node, visited);
    }
    for (auto node : module.ctx->get_nodes()) {
      written |= this->print_decl(module, node, visited);
    }
    if (written) {
      out_ << std::endl;
    }
  }

  //
  // body logic
  //
  {
    auto_indent indent(out_);
    int written = 0;
    for (auto node : module.ctx->get_nodes()) {
      written |= this->print_logic(module, node);
    }
    if (written) {
      out_ << std::endl;
    }
  }
}

void verilogwriter::print_footer(module_t& module) {
  //
  // output assignment
  //
  {
    auto_indent indent(out_);
    bool written = false;

    for (auto output : module.ctx->get_outputs()) {
      out_ << "assign ";
      this->print_name(module, output);
      out_ << " = ";
      this->print_name(module, dynamic_cast<outputimpl*>(output)->get_src(0).get_impl());
      out_ << ";" << std::endl;
      written = true;
    }

    if (written) {
      out_ << std::endl;
    }
  }

  out_ << "endmodule" << std::endl;
}

bool verilogwriter::print_binding(module_t& module, bindimpl* node) {
  auto_separator sep(", ");
  auto m = node->get_module();
  out_ << m->get_name() << " __module" << m->get_id() << "__(";
  for (auto& input : node->get_inputs()) {
    auto b = dynamic_cast<bindportimpl*>(input.get_impl());
    auto p = dynamic_cast<ioimpl*>(b->get_ioport().get_impl());
    out_ << sep << "." << p->get_name() << "(";
    this->print_name(module, b);
    out_ << ")";
  }
  for (auto& output : node->get_outputs()) {
    auto b = dynamic_cast<bindportimpl*>(output.get_impl());
    auto p = dynamic_cast<ioimpl*>(b->get_ioport().get_impl());
    out_ << sep << "." << p->get_name() << "(";
    this->print_name(module, b);
    out_ << ")";
  }
  out_ << ");" << std::endl;
  return true;
}

bool verilogwriter::print_bindport(module_t& module, bindportimpl* node) {
  // outputs are sourced via binding already
  if (node->is_output())
    return false;

  out_ << "assign ";
  this->print_name(module, node);
  out_ << " = ";
  this->print_name(module, node->get_src(0).get_impl());
  out_ << ";" << std::endl;
  return true;
}

void verilogwriter::print_port(module_t& module, lnodeimpl* node) {
  auto type = node->get_type();
  switch (type) {
  case type_input:
    out_ << "input";
    break;
  case type_output:
  case type_tap:
    out_ << "output";
    break;
  default:
    assert(false);
  }

  out_ << " ";
  this->print_type(node);

  out_ << " ";
  this->print_name(module, node);
}

bool verilogwriter::print_decl(module_t& module,
                               lnodeimpl* node,
                               std::unordered_set<uint32_t>& visited,
                               lnodeimpl* ref) {
  if (visited.count(node->get_id()))
    return false;

  auto type = node->get_type();
  switch (type) {
  case type_lit:
    visited.insert(node->get_id());
    if (is_inline_literal(node))
      return false;
    this->print_type(node);
    out_ << " ";
    this->print_name(module, node);
    out_ << " = ";
    this->print_value(node->get_value(), true);
    out_ << ";" << std::endl;    
    return true;
  case type_proxy:
    if (module.is_inline_subscript(node)) {
      visited.insert(node->get_id());
      return false;
    }
    [[fallthrough]];
  case type_bindport:
  case type_alu:
  case type_sel:
  case type_reg:
  case type_mem:    
    if (ref
     && (IsRegType(ref->get_type()) != IsRegType(type)
      || ref->get_size() != node->get_size()))
      return false;    
    if (ref) {
      out_ << ", ";
    } else {
      this->print_type(node);
      out_ << " ";
    }
    this->print_name(module, node);
    if (type_mem == type) {
      out_ << "[0:" << (dynamic_cast<memimpl*>(node)->get_num_items() - 1) << "]";
    }
    visited.insert(node->get_id());
    if (!ref) {
      if (0 == platform::self().get_dbg_verilog()) {
        for (auto other : node->get_ctx()->get_nodes()) {
          this->print_decl(module, other, visited, node);
        }
        out_ << ";" << std::endl;
      } else {        
        out_ << ";";
        auto& sloc = node->get_source_location();
        if (!sloc.is_empty() || node->get_var_id() != 0) {
          out_ << " // ";
          if (node->get_var_id() != 0) {
            out_ << "v" << node->get_var_id();
            if (!sloc.is_empty()) {
              out_ << " - ";
            }
          }
          if (!sloc.is_empty()) {
            out_ << (sloc.file() ? sloc.file() : "unknown")
                 << "(" << sloc.line() << ")";
          }
        }
        out_ << std::endl;
      }
    }
    return true;
  case type_bind:
  case type_input:
  case type_output:
  case type_tap:
  case type_memport:
  case type_assert:
  case type_print:
  case type_tick:
    visited.insert(node->get_id());
    break;
  default:
    assert(false);
  }  
  return false;
}

bool verilogwriter::print_logic(module_t& module, lnodeimpl* node) {
  auto type = node->get_type();
  switch (type) {
  case type_proxy:
    if (module.is_inline_subscript(node))
      return false;
    out_ << "assign ";
    this->print_name(module, node);
    out_ << " = ";
    this->print_proxy(module, dynamic_cast<proxyimpl*>(node));
    out_ << ";" << std::endl;
    return true;
  case type_alu:
    this->print_alu(module, dynamic_cast<aluimpl*>(node));
    return true;
  case type_sel:
    this->print_select(module, dynamic_cast<selectimpl*>(node));
    return true;
  case type_reg:
    this->print_reg(module, dynamic_cast<regimpl*>(node));
    return true;
  case type_mem:
    this->print_mem(module, dynamic_cast<memimpl*>(node));
    return true;
  case type_bind:
    this->print_binding(module, dynamic_cast<bindimpl*>(node));
    return true;
  case type_bindport:
    this->print_bindport(module, dynamic_cast<bindportimpl*>(node));
    return true;  
  case type_lit:
  case type_input:
  case type_output:
  case type_tap:
  case type_memport:
  case type_assert:
  case type_print:
  case type_tick:
    break;
  default:
    assert(false);
  }
  return false;
}

void verilogwriter::print_proxy(module_t& module, proxyimpl* node) {
  const auto& ranges = node->get_ranges();
  uint32_t dst_offset = node->get_size();
  auto print_range = [&](const proxyimpl::range_t& range) {
    dst_offset -= range.length;
    assert(range.dst_offset == dst_offset);
    auto& src = node->get_src(range.src_idx);
    this->print_name(module, src.get_impl());
    if (range.length < src.get_size()) {
      out_ << "[";
      if (range.length > 1) {
        out_ << (range.src_offset + range.length - 1) << ":" << range.src_offset;
      } else {
        out_ << range.src_offset;
      }
      out_ << "]";
    };
  };
  if (ranges.size() > 1) {
    out_ << "{";
    auto_separator sep(", ");
    for (int i = ranges.size() - 1; i >= 0; --i) {
      out_ << sep;
      print_range(ranges[i]);
    }
    out_ << "}";
  } else {
    print_range(ranges[0]);
  }
}

void verilogwriter::print_alu(module_t& module, aluimpl* node) {
  auto op = node->get_op();
  if (op == alu_rotl) {
    this->print_rotate(module, node, false);
  } else
  if (op == alu_rotr) {
    this->print_rotate(module, node, true);
  } else
  if (op == alu_mux) {
    this->print_mux(module, node);
  } else
  if (CH_ALUOP_DTYPE(op) == alu_integer) {    
    out_ << "assign ";
    this->print_name(module, node);
    out_ << " = ";
    if (CH_ALUOP_ARY(op) == alu_binary) {
      this->print_name(module, node->get_src(0).get_impl());
      out_ << " ";
      this->print_operator(op);
      out_ << " ";
      this->print_name(module, node->get_src(1).get_impl());
      out_ << ";" << std::endl;
    } else {
      assert(CH_ALUOP_ARY(op) == alu_unary);
      this->print_operator(op);
      this->print_name(module, node->get_src(0).get_impl());
      out_ << ";" << std::endl;
    }
  } else {
    if (op == alu_fmult) {
      this->print_fmult(module, node);
    } else
    if (op == alu_fadd) {
      this->print_fadd(module, node);
    } else {
      CH_TODO();
    }
  }
}

void verilogwriter::print_rotate(module_t& module, aluimpl* node, bool right_dir) {
  out_ << "barrel_shift #(";
  out_ << (right_dir ? 1 : 0);
  out_ << ", ";
  out_ << node->get_size();
  out_ << ") __barrel_shift_";
  out_ << node->get_id() << "__(";
  this->print_name(module, node->get_src(0).get_impl());
  out_ << ", ";
  this->print_name(module, node);
  out_ << ", ";
  this->print_name(module, node->get_src(1).get_impl());
  out_ << ");" << std::endl;
}

void verilogwriter::print_mux(module_t& module, aluimpl* node) {
  out_ << "bus_mux #(";
  out_ << node->get_size();
  out_ << ", ";
  out_ << node->get_src(1).get_size();
  out_ << ") __bus_mux_";
  out_ << node->get_id() << "__(";
  this->print_name(module, node->get_src(0).get_impl());
  out_ << ", ";
  this->print_name(module, node->get_src(1).get_impl());
  out_ << ", ";
  this->print_name(module, node);
  out_ << ");" << std::endl;
}

void verilogwriter::print_fmult(module_t& module, aluimpl* node) {
  auto dalu = dynamic_cast<delayed_aluimpl*>(node);
  out_ << "fp_mult __fp_mult_";
  out_ << node->get_id() << "__(.clock(";
  this->print_name(module, dalu->get_clk().get_impl());
  out_ << "), .clk_en(";
  if (dalu->has_enable()) {
    this->print_name(module, dalu->get_enable().get_impl());
  } else {
    out_ << "1b'1";
  }
  out_ << "), .dataa(";
  this->print_name(module, node->get_src(0).get_impl());
  out_ << "), .datab(";
  this->print_name(module, node->get_src(1).get_impl());
  out_ << "), .result(";
  this->print_name(module, node);
  out_ << "));" << std::endl;
}

void verilogwriter::print_fadd(module_t& module, aluimpl* node) {
  auto dalu = dynamic_cast<delayed_aluimpl*>(node);
  out_ << "fp_add __fp_add_sub_";
  out_ << node->get_id() << "__(.clock(";
  this->print_name(module, dalu->get_clk().get_impl());
  out_ << "), .clk_en(";
  if (dalu->has_enable()) {
    this->print_name(module, dalu->get_enable().get_impl());
  } else {
    out_ << "1b'1";
  }
  out_ << "), .dataa(";
  this->print_name(module, node->get_src(0).get_impl());
  out_ << "), .datab(";
  this->print_name(module, node->get_src(1).get_impl());
  out_ << "), .result(";
  this->print_name(module, node);
  out_ << "));" << std::endl;
}

void verilogwriter::print_select(module_t& module, selectimpl* node) {
  bool has_key = node->has_key();
  uint32_t i = has_key ? 1 : 0;  
  if (node->is_ternary()) {
    out_ << "assign ";
    this->print_name(module, node);
    out_ << " = ";
    if (has_key) {
      out_ << "(";
      this->print_name(module, node->get_src(0).get_impl());
      out_ << " == ";
      this->print_name(module, node->get_src(1).get_impl());
      out_ << ")";
    } else {
      this->print_name(module, node->get_src(0).get_impl());
    }
    out_ << " ? ";
    this->print_name(module, node->get_src(i+1).get_impl());
    out_ << " : ";
    this->print_name(module, node->get_src(i+2).get_impl());
    out_ << ";" << std::endl;
  } else {
    uint32_t last = node->get_num_srcs() - 1;
    out_ << "always @(*) begin" << std::endl;
    if (has_key) {
      auto_indent indent1(out_);
      out_ << "case (";
      this->print_name(module, node->get_src(0).get_impl());
      out_ << ")" << std::endl;
      {
        auto_indent indent2(out_);
        for (; i < last; i += 2) {
          print_value(node->get_src(i).get_impl()->get_value(), false);
          out_ << ": ";
          this->print_name(module, node);
          out_ << " = ";
          this->print_name(module, node->get_src(i + 1).get_impl());
          out_ << ";" << std::endl;
        }
        out_ << "default: ";
        this->print_name(module, node);
        out_ << " = ";
        this->print_name(module, node->get_src(i).get_impl());
        out_ << ";" << std::endl;
      }
      out_ << "endcase" << std::endl;
    } else {
      auto_indent indent1(out_);
      for (; i < last; i += 2) {
        out_ << (0 == i ? "if (" : "else if (");
        this->print_name(module, node->get_src(i).get_impl());
        out_ << ")" << std::endl;
        {
          auto_indent indent2(out_);
          this->print_name(module, node);
          out_ << " = ";
          this->print_name(module, node->get_src(i + 1).get_impl());
          out_ << ";" << std::endl;
        }
      }
      out_ << "else" << std::endl;
      {
        auto_indent indent2(out_);
        this->print_name(module, node);
        out_ << " = ";
        this->print_name(module, node->get_src(i).get_impl());
        out_ << ";" << std::endl;
      }
    }
    out_ << "end" << std::endl;
  }
}

void verilogwriter::print_reg(module_t& module, regimpl* node) {
  out_ << "always @ (";
  this->print_cdomain(module, node->get_cd());
  out_ << ") begin" << std::endl;
  {
    auto_indent indent(out_);
    this->print_name(module, node);
    out_ << " <= ";
    if (node->has_reset()) {
      this->print_name(module, node->get_reset().get_impl());
      out_ << " ? ";
      this->print_name(module, node->get_init().get_impl());
      out_ << " : ";
      if (node->has_enable()) {
        out_ << "(";
        this->print_name(module, node->get_enable().get_impl());
        out_ << " ? ";
        this->print_name(module, node->get_next().get_impl());
        out_ << " : ";
        this->print_name(module, node);
        out_ << ")";
      } else {
        this->print_name(module, node->get_next().get_impl());
      }
    } else
    if (node->has_enable()) {
      this->print_name(module, node->get_enable().get_impl());
      out_ << " ? ";
      this->print_name(module, node->get_next().get_impl());
      out_ << " : ";
      this->print_name(module, node);
    } else {
      this->print_name(module, node->get_next().get_impl());
    }
    out_ << ";" << std::endl;
  }
  out_ << "end" << std::endl;
}

void verilogwriter::print_cdomain(module_t& module, cdomain* cd) {
  auto_separator sep(", ");
  for (auto& e : cd->get_sensitivity_list()) {
    out_ << sep;
    switch (e.get_edgedir()) {
    case EDGE_POS:
      out_ << "posedge ";
      break;
    case EDGE_NEG:
      out_ << "negedge ";
      break;
    default:
      break;
    }
    this->print_name(module, e.get_signal().get_impl());
  }
}

void verilogwriter::print_mem(module_t& module, memimpl* node) {
  //
  // initialization data
  //
  if (node->has_initdata()) {
    out_ << "initial begin" << std::endl;
    {
      auto_indent indent(out_);
      const auto& value = node->get_value();
      uint32_t data_width = node->get_data_width();
      uint32_t num_items = node->get_num_items();
      for (uint32_t i = 0; i < num_items; ++i) {
        this->print_name(module, node, true);
        out_ << "[" << i << "] = ";
        uint32_t offset = i * data_width;
        this->print_value(value, true, offset, data_width);
        out_ << ";" << std::endl;
      }
    }
    out_ << "end" << std::endl;
  }

  //
  // write ports logic
  //
  for (auto& p : node->get_ports()) {
    auto p_impl = dynamic_cast<memportimpl*>(p.get_impl());
    if (!p_impl->has_wdata())
      continue;
    out_ << "always @(" ;
    this->print_cdomain(module, node->get_cd());
    out_ << ") begin" << std::endl;
    {
      auto_indent indent1(out_);
      if (p_impl->has_enable()) {
        out_ << "if (";
        this->print_name(module, p_impl->get_enable().get_impl());
        out_ << ") begin" << std::endl;
        {
          auto_indent indent2(out_);
          this->print_name(module, p_impl);
          out_ << " = ";
          this->print_name(module, p_impl->get_wdata().get_impl());
          out_ << ";" << std::endl;
        }
        out_ << "end" << std::endl;
      } else {
        this->print_name(module, p_impl);
        out_ << " = ";
        this->print_name(module, p_impl->get_wdata().get_impl());
        out_ << ";" << std::endl;
      }
    }
    out_ << "end" << std::endl;
  }
}

void verilogwriter::print_name(module_t& module, lnodeimpl* node, bool force) {
  auto print_unique_name = [&](const lnode& node) {
    out_ << node.get_name() << node.get_id();
  };

  auto type = node->get_type();
  switch (type) {
  case type_input:
  case type_output:
    out_ << node->get_name();
    break;
  case type_proxy:    
    if (!force && module.is_inline_subscript(node)) {
      this->print_proxy(module, dynamic_cast<proxyimpl*>(node));
    } else {
      print_unique_name(node);
    }
    break;
  case type_lit:
    if (!force && is_inline_literal(node)) {
      print_value(node->get_value(), true);
    } else {
      print_unique_name(node);
    }
    break;
  case type_sel:
  case type_alu:
  case type_reg:
  case type_mem:
  case type_bindport:
    print_unique_name(node);
    break;
  case type_memport: {
    auto memport = dynamic_cast<memportimpl*>(node);
    this->print_name(module, memport->get_mem().get_impl());
    out_ << "[";
    this->print_name(module, memport->get_addr().get_impl());
    out_ << "]";
  } break;
  default:
    assert(false);
  }
}

void verilogwriter::print_type(lnodeimpl* node) {
  auto type = node->get_type();

  bool is_reg_type = (type_sel == type) ?
        !dynamic_cast<selectimpl*>(node)->is_ternary() :
        IsRegType(type);

  out_ << (is_reg_type ? "reg" : "wire");

  if (type == type_mem) {
    auto data_width = dynamic_cast<memimpl*>(node)->get_data_width();
    if (data_width > 1) {
      out_ << "[" << (data_width - 1) << ":0]";
    }
  } else {
    if (node->get_size() > 1) {
      out_ << "[" << (node->get_size() - 1) << ":0]";
    }
  }
}

void verilogwriter::print_value(const bitvector& value,
                                bool skip_leading_zeros_enable,
                                unsigned offset,
                                unsigned size) {
  //--
  auto skip_leading_zeros = [&](int word)->bool {
    if (skip_leading_zeros_enable) {
      if (0 == word) {
        return true;
      } else {
        skip_leading_zeros_enable = false;
      }
    }
    return false;
  };

  if (0 == size) {
    size = value.get_size();
  }

  offset += (size -1);

  int word = 0;
  int wsize = 0;

  out_ << size << "'h";
  auto oldflags = out_.flags();
  out_.setf(std::ios_base::hex, std::ios_base::basefield);
  for (auto it = value.begin() + offset; size--;) {
    word = (word << 0x1) | *it--;
    if (0 == (++wsize & 0x3)) {
      if (0 == size || !skip_leading_zeros(word)) {
        out_ << word;
      }
      word = 0;
    }
  }
  if (0 != (wsize & 0x3)) {
    out_ << word;
  }
  out_.flags(oldflags);
}

void verilogwriter::print_operator(ch_alu_op op) {
  switch (op) {
  case alu_inv:   out_ << "~"; break;
  case alu_and:   out_ << "&"; break;
  case alu_or:    out_ << "|"; break;
  case alu_xor:   out_ << "^"; break;
  case alu_andr:  out_ << "&"; break;
  case alu_orr:   out_ << "|"; break;
  case alu_xorr:  out_ << "^"; break;

  case alu_neg:   out_ << "-"; break;
  case alu_add:   out_ << "+"; break;
  case alu_sub:   out_ << "-"; break;
  case alu_mult:  out_ << "*"; break;
  case alu_div:   out_ << "/"; break;
  case alu_mod:   out_ << "%"; break;

  case alu_sll:   out_ << "<<"; break;
  case alu_srl:   out_ << ">>"; break;
  case alu_sra:   out_ << ">>>"; break;

  case alu_eq:    out_ << "=="; break;
  case alu_ne:    out_ << "!="; break;
  case alu_lt:    out_ << "<"; break;
  case alu_gt:    out_ << ">"; break;
  case alu_le:    out_ << "<="; break;
  case alu_ge:    out_ << ">="; break;
  default:
    assert(false);
  }
}

///////////////////////////////////////////////////////////////////////////////

void ch::internal::toVerilog(std::ostream& out,
                             const std::initializer_list<context*>& contexts) {
  verilogwriter writer(out);
  writer.print(contexts);
}
