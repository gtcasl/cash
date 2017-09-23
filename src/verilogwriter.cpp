#include "verilogwriter.h"
#include "context.h"
#include "litimpl.h"
#include "regimpl.h"
#include "memimpl.h"
#include "ioimpl.h"
#include "snodeimpl.h"
#include "selectimpl.h"
#include "proxyimpl.h"
#include "memimpl.h"
#include "aluimpl.h"
#include "assertimpl.h"
#include "tickimpl.h"
#include <cstring>

using namespace cash::internal;

verilogwriter::verilogwriter(std::ostream& out) : out_(out) {
  //--
}

verilogwriter::~verilogwriter() {
  //--
}

void verilogwriter::print(context* ctx, const std::string& module_name) {
  // print header
  this->print_header(ctx, module_name);

  out_ << std::endl;

  // print body
  this->print_body(ctx);

  out_ << std::endl;

  // print footer
  this->print_footer(ctx);
}

void verilogwriter::print_header(context* ctx, const std::string& module_name) {
  //
  // ports declaration
  //
  out_ << "module " << module_name << '(';
  {
    auto_indent indent(out_, 2);
    const char* sep = "";

    for (auto input : ctx->get_inputs()) {
      out_ << sep << std::endl; sep = ",";
      this->print_port(input);
    }

    for (auto output : ctx->get_outputs()) {
      out_ << sep << std::endl; sep = ",";
      this->print_port(output);
    }

    for (auto tap : ctx->get_taps()) {
      out_ << sep << std::endl; sep = ",";
      this->print_port(tap);
    }

    if (strlen(sep) != 0)
      out_ << std::endl;
  }
  out_ << ");" << std::endl;

  out_ << std::endl;

  //
  // signals declaration
  //
  {
    auto_indent indent(out_, 2);

    for (auto node : ctx->get_nodes()) {
      this->print_decl(node);
    }
  }
}

void verilogwriter::print_body(context* ctx) {
  //
  // module logic
  //
  {
    auto_indent indent(out_, 2);
    for (auto node : ctx->get_nodes()) {
      auto op = node->get_op();
      switch (op) {
      case op_proxy:
        this->print_proxy(dynamic_cast<proxyimpl*>(node));
        break;
      case op_alu:
        this->print_alu(dynamic_cast<aluimpl*>(node));
        break;
      case op_select:
        this->print_select(dynamic_cast<selectimpl*>(node));
        break;
      case op_reg:
        this->print_reg(dynamic_cast<regimpl*>(node));
        break;
      case op_mem:
        this->print_mem(dynamic_cast<memimpl*>(node));
        break;
      default:
        break;
      }
    }
  }
}

void verilogwriter::print_footer(context* ctx) {
  //
  // output assignment
  //
  {
    auto_indent indent(out_, 2);
    for (auto node : ctx->get_outputs()) {
      out_ << "assign ";
      this->print_name(node);
      out_ << " = ";
      this->print_name(dynamic_cast<outputimpl*>(node)->get_src(0).get_impl());
      out_ << ";" << std::endl;
    }
  }
  out_ << std::endl;
  out_ << "endmodule" << std::endl;
}

void verilogwriter::print_port(lnodeimpl* node) {
  auto op = node->get_op();
  switch (op) {
  case op_input:
  case op_clk:
  case op_reset:
    out_ << "input";
    break;
  case op_output:
  case op_tap:
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

void verilogwriter::print_decl(lnodeimpl* node) {
  auto op = node->get_op();
  switch (op) {
  case op_proxy:
  case op_lit:
  case op_alu:
  case op_select:
  case op_reg:
  case op_mem:
    this->print_type(node);
    out_ << " ";
    this->print_name(node);
    if (op_lit == op) {
      out_ << " = ";
      this->print_value(node->get_value());
    } else
    if (op_mem == op) {
      auto addr_width = dynamic_cast<memimpl*>(node)->get_addr_width();
      out_ << "[0:" << (addr_width - 1) << "]";
    }
    out_ << ";" << std::endl;
    break;
  default:
    break;
  }
}

void verilogwriter::print_name(lnodeimpl* node) {
  auto op = node->get_op();
  switch (op) {
  case op_proxy:  out_ << "__x"; break;
  case op_lit:    out_ << "__l"; break;
  case op_input:  out_ << "__i"; break;
  case op_output: out_ << "__o"; break;
  case op_clk:    out_ << "__i"; break;
  case op_reset:  out_ << "__i"; break;
  case op_select: out_ << "__s"; break;
  case op_tap:    out_ << "__t"; break;
  case op_reg:    out_ << "__r"; break;
  case op_memport:out_ << "__m"; break;
  default:        out_ << "__w"; break;
  }
  out_ << node->get_id();
  if (op == op_tap) {
    out_ << "_" << dynamic_cast<tapimpl*>(node)->get_name();
  }
  out_ << "__";

}

void verilogwriter::print_type(lnodeimpl* node) {
  auto op = node->get_op();
  switch (op) {
  case op_reg:
  case op_mem:
    out_ << "reg";
    break;
  default:
    out_ << "wire";
    break;
  }
  if (op == op_mem) {
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
    const char* sep = "";
    for (int i = ranges.size() - 1; i >= 0; --i) {
      out_ << sep;
      sep = ", ";
      print_range(ranges[i]);
    }
    out_ << "}";
  } else {
    print_range(ranges[0]);
  }  
  out_ << ";" << std::endl;
}

void verilogwriter::print_alu(aluimpl* node) {
  auto alu_op = node->get_alu_op();
  if ((alu_op & (alu_binary | alu_int32))
    && (alu_op & alu_bitwise
     || alu_op & alu_compare
     || alu_op & alu_arithm
     || alu_op == alu_op_shl
     || alu_op == alu_op_shr)) {
    out_ << "assign ";
    this->print_name(node);
    out_ << " = ";
    this->print_name(node->get_src(0).get_impl());
    out_ << " ";
    this->print_operator(alu_op);
    out_ << " ";
    this->print_name(node->get_src(1).get_impl());
    out_ << ";" << std::endl;
  }
}

void verilogwriter::print_operator(ch_alu_op alu_op) {
  switch (alu_op) {
  case alu_op_and: out_ << "&"; break;
  case alu_op_or:  out_ << "|"; break;
  case alu_op_xor: out_ << "^"; break;
  case alu_op_add: out_ << "+"; break;
  case alu_op_sub: out_ << "-"; break;
  case alu_op_mult:out_ << "*"; break;
  case alu_op_div: out_ << "/"; break;
  case alu_op_mod: out_ << "%"; break;
  case alu_op_shl: out_ << "<<<"; break;
  case alu_op_shr: out_ << ">>>"; break;
  case alu_op_eq:  out_ << "=="; break;
  case alu_op_ne:  out_ << "!="; break;
  case alu_op_lt:  out_ << "<"; break;
  case alu_op_gt:  out_ << ">"; break;
  case alu_op_le:  out_ << "<="; break;
  case alu_op_ge:  out_ << ">="; break;
  default:
    break;
  }
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
    auto_indent indent(out_, 2);
    if (node->has_reset()) {
      out_ << "if (";
      this->print_name(node->get_reset().get_impl());
      out_ << ")" << std::endl;
      {
        auto_indent indent(out_, 2);
        assign_value(node->get_init());
      }
      if (node->has_enable()) {
        out_ << "else if (";
        this->print_name(node->get_enable().get_impl());
        out_ << ")" << std::endl;
        {
          auto_indent indent(out_, 2);
          assign_value(node->get_next());
        }
      } else {
        out_ << "else" << std::endl;
        {
          auto_indent indent(out_, 2);
          assign_value(node->get_next());
        }
      }
    } else
    if (node->has_enable()) {
      out_ << "if (";
      this->print_name(node->get_enable().get_impl());
      out_ << ")" << std::endl;
      {
        auto_indent indent(out_, 2);
        assign_value(node->get_next());
      }
    } else {
      assign_value(node->get_next());
    }
  }
  out_ << "end" << std::endl;
}

void verilogwriter::print_cdomain(cdomain* cd) {
  const char* sep = "";
  for (auto& e : cd->get_sensitivity_list()) {
    out_ << sep;
    sep = ", ";
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
  CH_UNUSED(node);
}
