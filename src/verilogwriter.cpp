#include "verilogwriter.h"
#include "verilog.h"
#include "context.h"
#include "deviceimpl.h"
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
#include "udfimpl.h"

using namespace ch::internal;

const auto IsRegType = [](lnodeimpl* node) {
  auto type = node->type();
  return (type_reg == type && (1 == reinterpret_cast<regimpl*>(node)->length()))
      || (type_mrport == type && reinterpret_cast<mrportimpl*>(node)->mem()->is_sync_read())
      || (type_mem == type)
      || (type_sel == type && !reinterpret_cast<selectimpl*>(node)->is_ternary());
};

const auto is_inline_literal = [](lnodeimpl* node) {
  assert(type_lit == node->type());
  return (node->size() <= 64);
};

verilogwriter::verilogwriter(context* ctx) : ctx_(ctx) {
  for (auto node : ctx->nodes()) {
    for (auto& src : node->srcs()) {
      uses_[src.id()].insert(node);
    }
  }
}

verilogwriter::~verilogwriter() {}

bool verilogwriter::is_inline_subscript(lnodeimpl* node) const {
  assert(type_proxy == node->type());
  if (reinterpret_cast<proxyimpl*>(node)->ranges().size() > 1)
    return false;
  if (type_proxy == node->src(0).impl()->type())
    return false;
  auto it = uses_.find(node->id());
  if (it != uses_.end()) {
    for (lnodeimpl* use : it->second) {
      if (type_proxy == use->type()
       || type_mem == use->type()
       || type_tap == use->type()
       || (type_alu == use->type()
        && ch_op::pad == reinterpret_cast<aluimpl*>(use)->op()))
        return false;
    }
  }
  return true;
}

bool verilogwriter::print(std::ostream& out,
                          std::unordered_set<std::string_view>& visited) {
  // ensure single instantiation
  if (visited.count(ctx_->name()))
    return false;
  visited.insert(ctx_->name());

  {
    // print dependent modules
    auto_separator sep("\n");
    int written = 0;    
    for (auto binding : ctx_->bindings()) {
      out << sep;
      verilogwriter child_module(binding->module());
      written |= child_module.print(out, visited);
    }
    if (written) {
      out << std::endl;
    }
  }

  // print header
  this->print_header(out);

  // print body
  this->print_body(out);

  // print footer
  this->print_footer(out);

  return true;
}

void verilogwriter::print_header(std::ostream& out) {
  //
  // ports declaration
  //
  out << "module " << ctx_->name() << '(';
  {
    auto_indent indent(out);
    auto_separator sep(",");

    std::vector<ioimpl*> ports;
    ports.reserve(ctx_->inputs().size() + ctx_->outputs().size());

    auto clk = ctx_->sys_clk();
    auto reset = ctx_->sys_reset();
    auto adjusted_port_id = [clk, reset](ioimpl* x)->uint32_t {
      if (x == clk)
        return 0;
      if (x == reset)
        return 1;
      return x->id() + 2;
    };

    // gather all ports and sort them in user-defined order
    // ensure system ports are written first
    ports.insert(ports.end(), ctx_->inputs().begin(), ctx_->inputs().end());
    ports.insert(ports.end(), ctx_->outputs().begin(), ctx_->outputs().end());
    std::sort(ports.begin(),
              ports.end(),
              [adjusted_port_id](ioimpl* a, ioimpl*b) {
                uint32_t a_id = adjusted_port_id(a);
                uint32_t b_id = adjusted_port_id(b);
                return a_id < b_id;
              });

    for (auto port : ports) {
      out << sep << std::endl;
      this->print_port(out, port);
    }
  }
  out << std::endl << ");" << std::endl;
}

void verilogwriter::print_body(std::ostream& out) {
  //
  // declaration
  //
  {
    auto_indent indent(out);
    std::unordered_set<uint32_t> visited;
    int written = 0;
    for (auto node : ctx_->literals()) {
      written |= this->print_decl(out, node, visited);
    }
    for (auto node : ctx_->nodes()) {
      written |= this->print_decl(out, node, visited);
    }
    if (written) {
      out << std::endl;
    }
  }

  //
  // body logic
  //
  {
    auto_indent indent(out);
    int written = 0;
    for (auto node : ctx_->nodes()) {
      written |= this->print_logic(out, node);
    }
    if (written) {
      out << std::endl;
    }
  }
}

void verilogwriter::print_footer(std::ostream& out) {
  //
  // output assignment
  //
  {
    auto_indent indent(out);
    bool written = false;

    for (auto output : ctx_->outputs()) {
      out << "assign ";
      this->print_name(out, output);
      out << " = ";
      this->print_name(out, reinterpret_cast<outputimpl*>(output)->src(0).impl());
      out << ";" << std::endl;
      written = true;
    }

    if (written) {
      out << std::endl;
    }
  }

  out << "endmodule" << std::endl;
}

bool verilogwriter::print_binding(std::ostream& out, bindimpl* node) {
  auto_separator sep(", ");
  auto m = node->module();
  out << m->name() << " __module" << m->id() << "__(";
  for (auto& input : node->inputs()) {
    auto b = reinterpret_cast<bindportimpl*>(input.impl());
    auto p = reinterpret_cast<ioimpl*>(b->ioport().impl());
    out << sep << "." << p->name() << "(";
    this->print_name(out, b);
    out << ")";
  }
  for (auto& output : node->outputs()) {
    auto b = reinterpret_cast<bindportimpl*>(output.impl());
    auto p = reinterpret_cast<ioimpl*>(b->ioport().impl());
    out << sep << "." << p->name() << "(";
    this->print_name(out, b);
    out << ")";
  }
  out << ");" << std::endl;
  return true;
}

bool verilogwriter::print_bindport(std::ostream& out, bindportimpl* node) {
  // outputs are sourced via binding already
  if (node->type() == type_bindout)
    return false;

  out << "assign ";
  this->print_name(out, node);
  out << " = ";
  this->print_name(out, node->src(0).impl());
  out << ";" << std::endl;
  return true;
}

void verilogwriter::print_port(std::ostream& out, ioimpl* node) {
  auto type = node->type();
  switch (type) {
  case type_input:
    out << "input";
    break;
  case type_output:
  case type_tap:
    out << "output";
    break;
  default:
    assert(false);
  }

  out << " ";
  this->print_type(out, node);

  out << " ";
  this->print_name(out, node);
}

bool verilogwriter::print_decl(std::ostream& out,
                               lnodeimpl* node,
                               std::unordered_set<uint32_t>& visited,
                               lnodeimpl* ref) {
  if (visited.count(node->id()))
    return false;

  auto type = node->type();
  switch (type) {
  case type_lit:
    visited.insert(node->id());
    if (is_inline_literal(node))
      return false;
    this->print_type(out, node);
    out << " ";
    this->print_name(out, node);
    out << " = ";
    this->print_value(out, reinterpret_cast<litimpl*>(node)->value(), true);
    out << ";" << std::endl;
    return true;
  case type_proxy:
    if (this->is_inline_subscript(node)) {
      visited.insert(node->id());
      return false;
    }
    [[fallthrough]];
  case type_bindin:
  case type_bindout:
  case type_alu:
  case type_sel:
  case type_reg:
  case type_mrport:
  case type_udfc:
  case type_udfs:
  case type_mem:
    if (ref
     && (IsRegType(ref) != IsRegType(node)
      || ref->size() != node->size()))
      return false;    
    if (ref) {
      out << ", ";
    } else {
      this->print_type(out, node);
      out << " ";
    }
    this->print_name(out, node);
    if (type_mem == type) {
      out << " [0:" << (reinterpret_cast<memimpl*>(node)->num_items() - 1) << "]";
    }
    visited.insert(node->id());
    if (!ref) {
      if (platform::self().cflags() & cflags::show_src_info) {
        out << ";";
        auto& sloc = node->sloc();
        if (!sloc.empty()) {
          this->print_sloc(out, sloc);
        }
        out << std::endl;
      } else {        
        for (auto other : node->ctx()->nodes()) {
          this->print_decl(out, other, visited, node);
        }
        out << ";" << std::endl;
      }
    }
    return true;
  case type_bind:
  case type_input:
  case type_output:
  case type_cd:
  case type_mwport:
  case type_tap:
  case type_assert:
  case type_print:
  case type_time:
    visited.insert(node->id());
    break;
  default:
    assert(false);
  }  
  return false;
}

void verilogwriter::print_sloc(std::ostream& out, const source_location& sloc) {
  out << " // " << (sloc.file() ? sloc.file() : "unknown")
      << "(" << sloc.line() << ")";
}

bool verilogwriter::print_logic(std::ostream& out, lnodeimpl* node) {
  auto type = node->type();
  switch (type) {
  case type_proxy:
    if (this->is_inline_subscript(node))
      return false;
    out << "assign ";
    this->print_name(out, node);
    out << " = ";
    this->print_proxy(out, reinterpret_cast<proxyimpl*>(node));
    out << ";" << std::endl;
    return true;
  case type_alu:
    this->print_alu(out, reinterpret_cast<aluimpl*>(node));
    return true;
  case type_sel:
    this->print_select(out, reinterpret_cast<selectimpl*>(node));
    return true;
  case type_reg:
    this->print_reg(out, reinterpret_cast<regimpl*>(node));
    return true;
  case type_mem:
    this->print_mem(out, reinterpret_cast<memimpl*>(node));
    return true;
  case type_bind:
    this->print_binding(out, reinterpret_cast<bindimpl*>(node));
    return true;
  case type_bindin:
  case type_bindout:
    this->print_bindport(out, reinterpret_cast<bindportimpl*>(node));
    return true;  
  case type_udfc:
  case type_udfs:
    this->print_udf(out, reinterpret_cast<udfimpl*>(node));
    return true;
  case type_lit:
  case type_input:
  case type_output:
  case type_cd:
  case type_mrport:
  case type_mwport:
  case type_tap:
  case type_assert:
  case type_print:
  case type_time:
    break;
  default:
    assert(false);
  }
  return false;
}

void verilogwriter::print_proxy(std::ostream& out, proxyimpl* node) {
  const auto& ranges = node->ranges();
  uint32_t dst_offset = node->size();
  auto print_range = [&](const proxyimpl::range_t& range) {
    dst_offset -= range.length;
    assert(range.dst_offset == dst_offset);
    auto& src = node->src(range.src_idx);
    this->print_name(out, src.impl());
    if (range.length < src.size()) {
      out << "[";
      if (range.length > 1) {
        out << (range.src_offset + range.length - 1) << ":" << range.src_offset;
      } else {
        out << range.src_offset;
      }
      out << "]";
    };
  };
  if (ranges.size() > 1) {
    out << "{";
    auto_separator sep(", ");
    for (int i = ranges.size() - 1; i >= 0; --i) {
      out << sep;
      print_range(ranges[i]);
    }
    out << "}";
  } else {
    print_range(ranges[0]);
  }
}

void verilogwriter::print_alu(std::ostream& out, aluimpl* node) {
  auto print_signed_operand = [&](unsigned index) {
    if (node->is_signed())
      out << "$signed(";
    this->print_name(out, node->src(index).impl());
    if (node->is_signed())
      out << ")";
  };
  auto op = node->op();
  if (op == ch_op::pad) {
    if (node->is_signed())
      this->print_sext(out, node);
    else
      this->print_zext(out, node);
  } else {
    out << "assign ";
    this->print_name(out, node);
    out << " = ";
    if (CH_OP_ARY(op) == op_flags::binary) {
      if (CH_OP_CLASS(op) == op_flags::shift
       || CH_OP_CLASS(op) == op_flags::relational
       || CH_OP_CLASS(op) == op_flags::logical
       || CH_OP_CLASS(op) == op_flags::arithmetic) {
        print_signed_operand(0);
        out << " ";
        this->print_operator(out, op);
        out << " ";
        if (op == ch_op::shl || op == ch_op::shr) {
          this->print_name(out, node->src(1).impl());
        } else {
          print_signed_operand(1);
        }
      } else {
        this->print_name(out, node->src(0).impl());
        out << " ";
        this->print_operator(out, op);
        out << " ";
        this->print_name(out, node->src(1).impl());
      }
      out << ";" << std::endl;
    } else {
      assert(CH_OP_ARY(op) == op_flags::unary);
      this->print_operator(out, op);
      this->print_name(out, node->src(0).impl());
      out << ";" << std::endl;
    }
  }
}

void verilogwriter::print_zext(std::ostream& out, aluimpl* node) {
  out << "assign ";
  this->print_name(out, node);
  out << " = {{" << node->size() - node->src(0).size() << "{1'b0}}, ";
  this->print_name(out, node->src(0).impl());
  out << "};" << std::endl;
}

void verilogwriter::print_sext(std::ostream& out, aluimpl* node) {
  out << "assign ";
  this->print_name(out, node);
  out << " = {{" << node->size() - node->src(0).size() << "{";
  this->print_name(out, node->src(0).impl());
  out << "[" << (node->src(0).size() - 1) << "]}}, ";
  this->print_name(out, node->src(0).impl());
  out << "};" << std::endl;
}

void verilogwriter::print_select(std::ostream& out, selectimpl* node) {
  bool has_key = node->has_key();
  uint32_t i = has_key ? 1 : 0;  
  if (node->is_ternary()) {
    out << "assign ";
    this->print_name(out, node);
    out << " = ";
    if (has_key) {
      out << "(";
      this->print_name(out, node->src(0).impl());
      out << " == ";
      this->print_name(out, node->src(1).impl());
      out << ")";
    } else {
      this->print_name(out, node->src(0).impl());
    }
    out << " ? ";
    this->print_name(out, node->src(i+1).impl());
    out << " : ";
    this->print_name(out, node->src(i+2).impl());
    out << ";" << std::endl;
  } else {
    uint32_t last = node->num_srcs() - 1;
    out << "always @(*) begin" << std::endl;
    if (has_key) {
      auto_indent indent1(out);
      out << "case (";
      this->print_name(out, node->src(0).impl());
      out << ")" << std::endl;
      {
        auto_indent indent2(out);
        for (; i < last; i += 2) {
          assert(type_lit == node->src(i).impl()->type());
          auto& value = reinterpret_cast<litimpl*>(node->src(i).impl())->value();
          print_value(out, value, false);
          out << ": ";
          this->print_name(out, node);
          out << " = ";
          this->print_name(out, node->src(i + 1).impl());
          out << ";" << std::endl;
        }
        out << "default: ";
        this->print_name(out, node);
        out << " = ";
        this->print_name(out, node->src(i).impl());
        out << ";" << std::endl;
      }
      out << "endcase" << std::endl;
    } else {
      auto_indent indent1(out);
      for (; i < last; i += 2) {
        out << (0 == i ? "if (" : "else if (");
        this->print_name(out, node->src(i).impl());
        out << ")" << std::endl;
        {
          auto_indent indent2(out);
          this->print_name(out, node);
          out << " = ";
          this->print_name(out, node->src(i + 1).impl());
          out << ";" << std::endl;
        }
      }
      out << "else" << std::endl;
      {
        auto_indent indent2(out);
        this->print_name(out, node);
        out << " = ";
        this->print_name(out, node->src(i).impl());
        out << ";" << std::endl;
      }
    }
    out << "end" << std::endl;
  }
}

void verilogwriter::print_reg(std::ostream& out, regimpl* node) {
  auto print_sr_name = [&]() {
    this->print_name(out, node);
    out << "_sr";
  };
  auto print_sr_iter = [&]() {
    this->print_name(out, node);
    out << "_i";
  };
  auto print_sr_loop_header = [&](unsigned start, unsigned end) {
    out << "for (";
    print_sr_iter();
    out << " = " << start << "; ";
    print_sr_iter();
    out << " < " << end << "; ";
    print_sr_iter();
    out << " = ";
    print_sr_iter();
    out << " + 1) begin" << std::endl;
  };
  if (node->length() > 1) {
    out << "reg";
    if (node->size() > 1) {
      out << "[" << (node->size() - 1) << ":0]";
    }
    out << " ";
    print_sr_name();
    out << " [" << (node->length()-1) << ":0];" << std::endl;
    out << "integer ";
    print_sr_iter();
    out << ";" << std::endl;
    out << "always @ (";
    auto cd = reinterpret_cast<cdimpl*>(node->cd().impl());
    this->print_cdomain(out, cd);
    out << ") begin" << std::endl;
    {
      auto_indent indent(out);
      if (node->has_initdata()) {
        out << "if (";
        this->print_name(out, node->reset().impl());
        out << ") begin" << std::endl;        
        indent.push();
        print_sr_loop_header(0, node->length());
        indent.push();
        print_sr_name();
        out << "[";
        print_sr_iter();
        out << "] <= ";
        this->print_name(out, node->initdata().impl());
        out << ";" << std::endl;
        indent.pop();
        out << "end" << std::endl;
        indent.pop();
        out << "end" << std::endl;
        out << "else" << std::endl;
      }
      if (node->has_enable()) {
        out << "if (";
        this->print_name(out, node->enable().impl());
        out << ") begin" << std::endl;
        indent.push();
      } else {
        if (node->has_initdata()) {
          out << "begin" << std::endl;
          indent.push();
        }
      }
      print_sr_loop_header(0, node->length()-1);
      indent.push();
      print_sr_name();
      out << "[" << (node->length() - 1) << "-";
      print_sr_iter();
      out << "] <= ";
      print_sr_name();
      out << "[" << (node->length() - 2) << "-";
      print_sr_iter();
      out << "];" << std::endl;
      indent.pop();
      out << "end" << std::endl;
      print_sr_name();
      out << "[0] <= ";
      this->print_name(out, node->next().impl());
      out << ";" << std::endl;
      if (node->has_initdata() || node->has_enable()) {
        indent.pop();
        out << "end" << std::endl;
      }
    }
    out << "end" << std::endl;
    out << "assign ";
    this->print_name(out, node);
    out << " = ";
    print_sr_name();
    out << "[" << (node->length() - 1) << "];" << std::endl;
  } else {
    out << "always @ (";
    auto cd = reinterpret_cast<cdimpl*>(node->cd().impl());
    this->print_cdomain(out, cd);
    out << ") begin" << std::endl;
    {
      auto_indent indent(out);
      if (node->has_initdata()) {
        out << "if (";
        this->print_name(out, node->reset().impl());
        out << ")" << std::endl;
        indent.push();
        this->print_name(out, node);
        out << " <= ";
        this->print_name(out, node->initdata().impl());
        out << ";" << std::endl;
        indent.pop();
        out << "else" << std::endl;
      }
      if (node->has_enable()) {
        out << "if (";
        this->print_name(out, node->enable().impl());
        out << ")" << std::endl;
        indent.push();
      } else {
        if (node->has_initdata()) {
          indent.push();
        }
      }
      this->print_name(out, node);
      out << " <= ";
      this->print_name(out, node->next().impl());
      out << ";" << std::endl;
      if (node->has_initdata() || node->has_enable()) {
        indent.pop();
      }
    }
    out << "end" << std::endl;
  }
}

void verilogwriter::print_cdomain(std::ostream& out, cdimpl* cd) {
  out << (cd->pos_edge() ? "posedge" : "negedge") << " ";
  this->print_name(out, cd->clk().impl());
}

void verilogwriter::print_mem(std::ostream& out, memimpl* node) {
  auto print_port = [&](std::ostream& out, memportimpl* p) {
    this->print_name(out, p->mem());
    out << "[";
    this->print_name(out, p->addr().impl());
    out << "]";
  };

  //
  // initialization data
  //
  if (node->has_initdata()) {
    out << "initial begin" << std::endl;
    {
      auto_indent indent(out);
      const auto& value = node->initdata();
      uint32_t data_width = node->data_width();
      uint32_t num_items = node->num_items();
      for (uint32_t i = 0; i < num_items; ++i) {
        this->print_name(out, node);
        out << "[" << i << "] = ";
        uint32_t offset = i * data_width;
        this->print_value(out, value, true, offset, data_width);
        out << ";" << std::endl;
      }
    }
    out << "end" << std::endl;
  }

  //
  //  ports logic
  //
  for (auto p : node->rdports()) {
    if (node->is_sync_read()) {
      out << "always @ (";
      this->print_cdomain(out, reinterpret_cast<cdimpl*>(node->cd().impl()));
      out << ") begin" << std::endl;
      {
        auto_indent indent1(out);
        if (p->has_enable()) {
          out << "if (";
          this->print_name(out, p->enable().impl());
          out << ") begin" << std::endl;
          {
            auto_indent indent2(out);
            this->print_name(out, p);
            out << " <= ";
            print_port(out, p);
            out << ";" << std::endl;
          }
          out << "end" << std::endl;
        } else {
          this->print_name(out, p);
          out << " <= ";
          print_port(out, p);
          out << ";" << std::endl;
        }
      }
      out << "end" << std::endl;
    } else {
      out << "assign ";
      this->print_name(out, p);
      out << " = ";
      print_port(out, p);
      out << ";" << std::endl;
    }
  }

  for (auto p : node->wrports()) {
    out << "always @ (";
    this->print_cdomain(out, reinterpret_cast<cdimpl*>(node->cd().impl()));
    out << ") begin" << std::endl;
    {
      auto_indent indent1(out);
      if (p->has_enable()) {
        out << "if (";
        this->print_name(out, p->enable().impl());
        out << ") begin" << std::endl;
        {
          auto_indent indent2(out);
          print_port(out, p);
          out << " <= ";
          this->print_name(out, p->wdata().impl());
          out << ";" << std::endl;
        }
        out << "end" << std::endl;
      } else {
        print_port(out, p);
        out << " <= ";
        this->print_name(out, p->wdata().impl());
        out << ";" << std::endl;
      }
    }
    out << "end" << std::endl;
  }
}

void verilogwriter::print_udf(std::ostream& out, udfimpl* node) {
  std::unordered_map<std::string, std::string> dic;

  auto add_to_dic = [&](const std::string& key, lnodeimpl* value) {
    std::ostringstream os;
    this->print_name(os, value);
    dic[key] = os.str();
  };

  auto udf = node->udf();

  dic["id"] = std::to_string(node->id());
  add_to_dic("dst", node);

  for (uint32_t i = 0, n = udf->inputs_sizes().size(); i < n; ++i) {
    add_to_dic("src" + std::to_string(i), node->src(i).impl());
  }

  if (udf->delta() != 0) {
    auto udfs = reinterpret_cast<udfsimpl*>(node);
    auto cd = reinterpret_cast<cdimpl*>(udfs->cd().impl());
    add_to_dic("clock", cd->clk().impl());
    if (udfs->has_initdata()) {
      add_to_dic("reset", udfs->reset().impl());
    }
  }

  std::string code;
  {
    // load code template
    std::ostringstream os;
    udf->to_verilog(os);
    code = os.str();
  }

  // replace tokens
  static const std::string Identifier("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_");
  std::string::size_type start = 0, pos = 0;
  auto len = code.length();
  while ((pos = code.find('$', pos)) != std::string::npos) {
    auto k = pos + 1;
    if (k < len) {
      auto end = code.find_first_not_of(Identifier, k);
      if (end == std::string::npos || end > k) {
        auto key = code.substr(k, end - k);
        auto it = dic.find(key);
        if (it != dic.end()) {
          out << code.substr(start, pos - start);
          out << it->second;
          start = end;
          pos = end;
          if (pos == std::string::npos)
            break;
          continue;
        }
      }
    }
    out << code.substr(start, k - start);
    start = k;
    pos = k;
  }
  if (start != std::string::npos) {
    out << code.substr(start);
  }
  out << std::endl;
}

void verilogwriter::print_name(std::ostream& out, lnodeimpl* node, bool force) {
  auto print_unique_name = [&](const lnode& node) {
    out << node.name() << node.id();
  };

  auto type = node->type();
  switch (type) {
  case type_input:
  case type_output:
    out << node->name();
    break;
  case type_proxy:    
    if (!force && this->is_inline_subscript(node)) {
      this->print_proxy(out, reinterpret_cast<proxyimpl*>(node));
    } else {
      print_unique_name(node);
    }
    break;
  case type_lit:
    if (!force && is_inline_literal(node)) {
      auto& value = reinterpret_cast<litimpl*>(node)->value();
      print_value(out, value, true);
    } else {
      print_unique_name(node);
    }
    break;
  case type_sel:
  case type_alu:
  case type_reg:
  case type_mem:
  case type_mrport:
  case type_mwport:
  case type_bindin:
  case type_bindout:
  case type_udfc:
  case type_udfs:
    print_unique_name(node);
    break;
  case type_time:
    out << "$time";
    break;
  default:
    assert(false);
  }
}

void verilogwriter::print_type(std::ostream& out, lnodeimpl* node) {  
  out << (IsRegType(node) ? "reg" : "wire");
  auto type = node->type();
  if (type == type_mem) {
    auto data_width = reinterpret_cast<memimpl*>(node)->data_width();
    if (data_width > 1) {
      out << "[" << (data_width - 1) << ":0]";
    }
  } else {
    if (node->size() > 1) {
      out << "[" << (node->size() - 1) << ":0]";
    }
  }
}

void verilogwriter::print_value(std::ostream& out,
                                const sdata_type& value,
                                bool skip_zeros,
                                uint32_t offset,
                                uint32_t size) {
  if (0 == size) {
    size = value.size();
  }

  out << size << "'h";
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
}

void verilogwriter::print_operator(std::ostream& out, ch_op op) {
  switch (op) {

  case ch_op::eq:    out << "=="; break;
  case ch_op::ne:    out << "!="; break;

  case ch_op::lt:    out << "<"; break;
  case ch_op::gt:    out << ">"; break;
  case ch_op::le:    out << "<="; break;
  case ch_op::ge:    out << ">="; break;

  case ch_op::notl:  out << "!"; break;
  case ch_op::andl:  out << "&&"; break;
  case ch_op::orl:   out << "||"; break;

  case ch_op::inv:   out << "~"; break;
  case ch_op::andb:  out << "&"; break;
  case ch_op::orb:   out << "|"; break;
  case ch_op::xorb:  out << "^"; break;

  case ch_op::andr:  out << "&"; break;
  case ch_op::orr:   out << "|"; break;
  case ch_op::xorr:  out << "^"; break;

  case ch_op::shl:   out << "<<"; break;
  case ch_op::shr:   out << ">>"; break;

  case ch_op::neg:   out << "-"; break;
  case ch_op::add:   out << "+"; break;
  case ch_op::sub:   out << "-"; break;
  case ch_op::mult:   out << "*"; break;
  case ch_op::div:   out << "/"; break;
  case ch_op::mod:   out << "%"; break;

  default:
    assert(false);
  }
}

///////////////////////////////////////////////////////////////////////////////

void ch::internal::ch_toVerilog(std::ostream& out, const device& device) {

  std::function<void (context*, std::unordered_set<udf_iface*>&)> print_udf_dependencies = [&](
      context* ctx, std::unordered_set<udf_iface*>& visited) {
    for (auto node : ctx->bindings()) {
      print_udf_dependencies(node->module(), visited);
    }
    for (auto node : ctx->nodes()) {
      if (type_udfc != node->type()
       && type_udfs != node->type())
        continue;
      auto udf = reinterpret_cast<udfimpl*>(node)->udf();
      if (0 == visited.count(udf)) {
        udf->init_verilog(out);
        out << std::endl;
        visited.insert(udf);
      }
    }
  };

  auto ctx = device.impl()->ctx();

  if (!ctx->udfs().empty()) {
    std::unordered_set<udf_iface*> udf_visited;
    print_udf_dependencies(ctx, udf_visited);
  }

  {
    std::unordered_set<std::string_view> visited;
    verilogwriter writer(ctx);
    writer.print(out, visited);
  }
}
