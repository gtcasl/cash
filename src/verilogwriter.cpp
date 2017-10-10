#include "verilogwriter.h"
#include "verilog.h"
#include "context.h"
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

verilogwriter::verilogwriter(std::ostream& out) : out_(out) {
  //--
}

verilogwriter::~verilogwriter() {
  //--
}

void verilogwriter::print(context* ctx) {
  // includes
  std::string lib_file = "verilog.v";
  auto lib_dir = std::getenv("CASH_PATH");
  if (lib_dir) {
    lib_file = std::string(lib_dir) + "/" + lib_file;
  }
  out_ << "`include \"" << lib_file << "\"" << std::endl;
  out_ << std::endl;

  // print module
  this->print_impl(ctx);
}

bool verilogwriter::print_impl(context* ctx) {
  // print all child modules
  {
    auto_separator sep("\n");
    int written = 0;
    for (auto child_ctx : ctx->get_children()) {
      out_ << sep;
      written |= this->print_impl(child_ctx);
    }
    if (written)
      out_ << std::endl;
  }

  // print header
  this->print_header(ctx);

  // print body
  this->print_body(ctx);

  // print footer
  this->print_footer(ctx);

  return true;
}

void verilogwriter::print_header(context* ctx) {
  //
  // ports declaration
  //
  out_ << "module " << ctx->get_name() << '(';
  {
    auto_indent indent(out_);
    auto_separator sep(",");

    auto default_clk = ctx->get_default_clk();
    if (default_clk) {
      out_ << sep << std::endl;
      this->print_port(default_clk);
    }

    auto default_reset = ctx->get_default_reset();
    if (default_reset) {
      out_ << sep << std::endl;
      this->print_port(default_reset);
    }

    for (auto input : ctx->get_inputs()) {
      out_ << sep << std::endl;
      this->print_port(input);
    }

    for (auto output : ctx->get_outputs()) {
      out_ << sep << std::endl;
      this->print_port(output);
    }
  }
  out_ << std::endl << ");" << std::endl;
}

void verilogwriter::print_body(context* ctx) {
  //
  // declaration
  //
  {
    auto_indent indent(out_);
    int written = 0;
    for (auto node : ctx->get_nodes()) {
      written |= this->print_decl(node);
    }
    if (written)
      out_ << std::endl;
  }

  //
  // child modules binding
  //
  {
    auto_indent indent(out_);
    int written = 0;
    for (auto child_ctx : ctx->get_children()) {
      written |= this->print_binding(child_ctx);
    }
    if (written)
      out_ << std::endl;
  }

  //
  // body logic
  //
  {
    auto_indent indent(out_);
    int written = 0;
    for (auto node : ctx->get_nodes()) {
      written |= this->print_logic(node);
    }
    if (written)
      out_ << std::endl;
  }
}

void verilogwriter::print_footer(context* ctx) {
  //
  // output assignment
  //
  {
    auto_indent indent(out_);
    bool written = false;

    for (auto output : ctx->get_outputs()) {
      out_ << "assign ";
      this->print_name(output);
      out_ << " = ";
      this->print_name(dynamic_cast<outputimpl*>(output)->get_src(0).get_impl());
      out_ << ";" << std::endl;
      written = true;
    }

    if (written)
      out_ << std::endl;
  }

  out_ << "endmodule" << std::endl;
}

bool verilogwriter::print_binding(context* ctx) {
  auto_separator sep(", ");
  out_ << ctx->get_name() << " __module" << ctx->get_id() << "__(";
  for (auto input : ctx->get_inputs()) {
    out_ << sep << input->get_name() << "(";
    this->print_name(input->get_input().get_impl());
    ports_.emplace(input->get_input().get_id());
    out_ << ")";
  }
  for (auto output : ctx->get_outputs()) {
    out_ << sep << output->get_name() << "(";
    this->print_name(output->get_output().get_impl());
    ports_.emplace(output->get_output().get_id());
    out_ << ")";
  }
  out_ << ");" << std::endl;
  return true;
}

void verilogwriter::print_port(lnodeimpl* node) {
  auto type = node->get_type();
  switch (type) {
  case type_input:
  case type_clk:
  case type_reset:
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
  this->print_name(node);
}

bool verilogwriter::print_decl(lnodeimpl* node) {
  auto type = node->get_type();
  switch (type) {
  case type_mem:
    this->print_type(node);
    out_ << " ";
    this->print_name(node);
    out_ << "[0:" << ((1 << dynamic_cast<memimpl*>(node)->get_addr_width()) - 1) << "]";
    out_ << ";" << std::endl;
    return true;
  case type_lit:
    this->print_type(node);
    out_ << " ";
    this->print_name(node);
    out_ << " = ";
    this->print_value(node->get_value());
    out_ << ";" << std::endl;
    return true;
  case type_proxy:
  case type_alu:
  case type_select:
  case type_reg:
    this->print_type(node);
    out_ << " ";
    this->print_name(node);
    out_ << ";" << std::endl;
    return true;
  case type_input:
  case type_clk:
  case type_reset:
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

bool verilogwriter::print_logic(lnodeimpl* node) {
  auto type = node->get_type();
  switch (type) {  
  case type_proxy:
    if (0 == ports_.count(node->get_id())) {
      this->print_proxy(dynamic_cast<proxyimpl*>(node));
      return true;
    }
    return false;
  case type_alu:
    this->print_alu(dynamic_cast<aluimpl*>(node));
    return true;
  case type_select:
    this->print_select(dynamic_cast<selectimpl*>(node));
    return true;
  case type_reg:
    this->print_reg(dynamic_cast<regimpl*>(node));
    return true;
  case type_mem:
    this->print_mem(dynamic_cast<memimpl*>(node));
    return true;
  case type_lit:
  case type_input:
  case type_clk:
  case type_reset:
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

void verilogwriter::print_proxy(proxyimpl* node) {
  out_ << "assign ";
  this->print_name(node);
  out_ << " = ";
  const auto& ranges = node->get_ranges();
  uint32_t dst_offset = node->get_size();
  auto print_range = [&](const proxyimpl::range_t& range) {
    dst_offset -= range.length;
    assert(range.dst_offset == dst_offset);
    auto& src = node->get_src(range.src_idx);
    this->print_name(src.get_impl());
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
  out_ << ";" << std::endl;
}

void verilogwriter::print_alu(aluimpl* node) {
  auto op = node->get_op();
  if (op == alu_rotl) {
    this->print_rotate(node, false);
  } else
  if (op == alu_rotr) {
    this->print_rotate(node, true);
  } else
  if (op == alu_mux) {
    this->print_mux(node);
  } else
  if (CH_ALUOP_DATA(op) == alu_integer) {
    if (CH_ALUOP_ARY(op) == alu_binary) {
      out_ << "assign ";
      this->print_name(node);
      out_ << " = ";
      this->print_name(node->get_src(0).get_impl());
      out_ << " ";
      this->print_operator(op);
      out_ << " ";
      this->print_name(node->get_src(1).get_impl());
      out_ << ";" << std::endl;
    } else {
      assert(CH_ALUOP_ARY(op) == alu_unary);
      out_ << "assign ";
      this->print_name(node);
      out_ << " = ";
      this->print_operator(op);
      this->print_name(node->get_src(0).get_impl());
      out_ << ";" << std::endl;
    }
  } else {
    if (op == alu_fmult) {
      this->print_fmult(node);
    } else
    if (op == alu_fadd) {
      this->print_fadd(node);
    } else {
      CH_TODO();
    }
  }
}

void verilogwriter::print_rotate(aluimpl* node, bool right_dir) {
  out_ << "barrel_shift #(";
  out_ << (right_dir ? 1 : 0);
  out_ << ", ";
  out_ << node->get_size();
  out_ << ") __barrel_shift_";
  out_ << node->get_id() << "__(";
  this->print_name(node->get_src(0).get_impl());
  out_ << ", ";
  this->print_name(node);
  out_ << ", ";
  this->print_name(node->get_src(1).get_impl());
  out_ << ");" << std::endl;
}

void verilogwriter::print_mux(aluimpl* node) {
  out_ << "bus_mux #(";
  out_ << node->get_size();
  out_ << ", ";
  out_ << node->get_src(1).get_size();
  out_ << ") __bus_mux_";
  out_ << node->get_id() << "__(";
  this->print_name(node->get_src(0).get_impl());
  out_ << ", ";
  this->print_name(node->get_src(1).get_impl());
  out_ << ", ";
  this->print_name(node);
  out_ << ");" << std::endl;
}

void verilogwriter::print_fmult(aluimpl* node) {
  out_ << "fp_mult __fp_mult_";
  out_ << node->get_id() << "__(.clock(clk), .dataa(";
  this->print_name(node->get_src(0).get_impl());
  out_ << "), .datab(";
  this->print_name(node->get_src(1).get_impl());
  out_ << "), .result(";
  this->print_name(node);
  out_ << "));" << std::endl;
}

void verilogwriter::print_fadd(aluimpl* node) {
  out_ << "fp_add __fp_add_sub_";
  out_ << node->get_id() << "__(.clock(clk), .dataa(";
  this->print_name(node->get_src(0).get_impl());
  out_ << "), .datab(";
  this->print_name(node->get_src(1).get_impl());
  out_ << "), .result(";
  this->print_name(node);
  out_ << "));" << std::endl;
}

void verilogwriter::print_select(selectimpl* node) {
  out_ << "assign ";
  this->print_name(node);
  out_ << " = ";
  this->print_name(node->get_pred().get_impl());
  out_ << " ? ";
  this->print_name(node->get_true().get_impl());
  out_ << " : ";
  this->print_name(node->get_false().get_impl());
  out_ << ";" << std::endl;
}

void verilogwriter::print_reg(regimpl* node) {
  auto assign_value = [&](const lnode& value) {
    this->print_name(node);
    out_ << " <= ";
    this->print_name(value.get_impl());
    out_ << ";" << std::endl;
  };
  out_ << "always @ (";
  this->print_cdomain(node->get_cd());
  out_ << ")" << std::endl;
  out_  << "begin" << std::endl;
  {
    auto_indent indent(out_);
    if (node->has_reset()) {
      out_ << "if (";
      this->print_name(node->get_reset().get_impl());
      out_ << ")" << std::endl;
      {
        auto_indent indent(out_);
        assign_value(node->get_init());
      }
      if (node->has_enable()) {
        out_ << "else if (";
        this->print_name(node->get_enable().get_impl());
        out_ << ")" << std::endl;
        {
          auto_indent indent(out_);
          assign_value(node->get_next());
        }
      } else {
        out_ << "else" << std::endl;
        {
          auto_indent indent(out_);
          assign_value(node->get_next());
        }
      }
    } else
    if (node->has_enable()) {
      out_ << "if (";
      this->print_name(node->get_enable().get_impl());
      out_ << ")" << std::endl;
      {
        auto_indent indent(out_);
        assign_value(node->get_next());
      }
    } else {
      assign_value(node->get_next());
    }
  }
  out_ << "end" << std::endl;
}

void verilogwriter::print_cdomain(cdomain* cd) {
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
    this->print_name(e.get_signal().get_impl());
  }
}

void verilogwriter::print_mem(memimpl* node) {
  //
  // initialization data
  //
  if (node->is_initialized()) {
    out_ << "initial begin" << std::endl;
    {
      auto_indent indent(out_);
      const auto& value = node->get_value();
      uint32_t data_width = node->get_data_width();
      uint32_t addr_size = 1 << node->get_addr_width();
      for (uint32_t addr = 0; addr < addr_size; ++addr) {
        this->print_name(node);
        out_ << "[" << addr << "] = " << data_width << "'b";
        uint32_t data_msb = (addr + 1) * data_width - 1;
        auto it = value.begin() + data_msb;
        for (uint32_t n = data_width; n--;) {
          out_ << ((*it--) ? 1 : 0);
        }
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
    if (!p_impl->is_writable())
      continue;
    out_ << "always @(" ;
    this->print_cdomain(node->get_cd());
    out_ << ")" << std::endl;
    out_ << "begin" << std::endl;
    {
      auto_indent indent(out_);
      this->print_name(p_impl);
      out_ << " = ";
      this->print_name(p_impl->get_wdata().get_impl());
      out_ << ";" << std::endl;
    }
    out_ << "end" << std::endl;
  }
}

void verilogwriter::print_operator(ch_alu_op op) {
  switch (op) {
  case alu_inv: out_ << "~"; break;
  case alu_and: out_ << "&"; break;
  case alu_or:  out_ << "|"; break;
  case alu_xor: out_ << "^"; break;
  case alu_nand: out_ << "~&"; break;
  case alu_nor:  out_ << "~|"; break;
  case alu_xnor: out_ << "~^"; break;
  case alu_andr: out_ << "&"; break;
  case alu_orr:  out_ << "|"; break;
  case alu_xorr: out_ << "^"; break;
  case alu_nandr: out_ << "~&"; break;
  case alu_norr:  out_ << "~|"; break;
  case alu_xnorr: out_ << "~^"; break;
  case alu_neg: out_ << "-"; break;
  case alu_add: out_ << "+"; break;
  case alu_sub: out_ << "-"; break;
  case alu_mult:out_ << "*"; break;
  case alu_div: out_ << "/"; break;
  case alu_mod: out_ << "%"; break;
  case alu_sll: out_ << "<<"; break;
  case alu_srl: out_ << ">>"; break;
  case alu_sra: out_ << ">>>"; break;
  case alu_eq:  out_ << "=="; break;
  case alu_ne:  out_ << "!="; break;
  case alu_lt:  out_ << "<"; break;
  case alu_gt:  out_ << ">"; break;
  case alu_le:  out_ << "<="; break;
  case alu_ge:  out_ << ">="; break;
  default:
    assert(false);
  }
}

void verilogwriter::print_name(lnodeimpl* node) {
  auto print_basic_name = [&](char prefix) {
    out_ << "__" << prefix;
    out_ << node->get_id();
    out_ << "__";
  };
  auto type = node->get_type();
  switch (type) {
  case type_clk:
  case type_reset:
  case type_input:
  case type_output:
    out_ << dynamic_cast<ioimpl*>(node)->get_name();
    break;
  case type_proxy:
    print_basic_name('w');
    break;
  case type_lit:
    print_basic_name('l');
    break;
  case type_select:
    print_basic_name('s');
    break;
  case type_alu:
    print_basic_name('a');
    break;
  case type_reg:
    print_basic_name('r');
    break;
  case type_mem:
    print_basic_name('m');
    break;
  case type_memport:
    out_ << "__m";
    out_ << dynamic_cast<memportimpl*>(node)->get_mem().get_id();
    out_ << "__[";
    this->print_name(dynamic_cast<memportimpl*>(node)->get_addr().get_impl());
    out_ << "]";
    break;
  default:
    assert(false);
  }
}

void verilogwriter::print_type(lnodeimpl* node) {
  auto type = node->get_type();
  switch (type) {
  case type_reg:
  case type_mem:
    out_ << "reg";
    break;
  default:
    out_ << "wire";
    break;
  }
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

void verilogwriter::print_value(const bitvector& value) {
  out_ << value.get_size() << "'b";
  for (auto it = value.rbegin(), end = value.rend(); it != end;) {
    out_ << ((*it++) ? 1 : 0);
  }
}

///////////////////////////////////////////////////////////////////////////////

void ch::internal::toVerilog(std::ostream& out, const std::initializer_list<context*>& contexts) {
  verilogwriter writer(out);
  for (auto ctx : contexts) {
    writer.print(ctx);
  }
}
