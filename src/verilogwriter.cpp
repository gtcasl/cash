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
#include "timeimpl.h"
#include <cstring>

using namespace ch::internal;

const auto IsRegType = [](lnodetype type) {
  return (type_reg == type) || (type_mem == type) || (type_mrport == type) || (type_mwport == type);
};

const auto is_inline_literal = [](lnodeimpl* node) {
  assert(type_lit == node->type());
  return (node->size() <= 64);
};

verilogwriter::module_t::module_t(context* p_ctx)
  : ctx(p_ctx)
  , num_temps(0)
{
  for (lnodeimpl* node : ctx->nodes()) {
    for (auto& src : node->srcs()) {
      uses[src.id()].insert(node);
    }
  }
}

bool verilogwriter::module_t::is_inline_subscript(lnodeimpl* node) const {
  assert(type_proxy == node->type());
  if (reinterpret_cast<proxyimpl*>(node)->ranges().size() > 1)
    return false;
  auto it = uses.find(node->id());
  if (it != uses.end()) {
    for (lnodeimpl* use : it->second) {
      if (type_proxy  == use->type()
       || type_mrport == use->type()
       || type_mwport == use->type())
        return false;
    }
  }
  lnodeimpl* src = node->src(0).impl();
  if (type_proxy  == src->type()
   || type_mrport == src->type()
   || type_mwport == src->type())
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
  // print top modules
  for (auto ctx : contexts) {
    module_t module(ctx);
    this->print_module(module);
  }
}

bool verilogwriter::print_module(module_t& module) {
  // ensure single instantiation
  if (visited_.count(module.ctx->name()))
    return false;
  visited_.insert(module.ctx->name());

  {
    // print dependent modules
    auto_separator sep("\n");
    int written = 0;    
    for (auto binding : module.ctx->bindings()) {
      out_ << sep;
      module_t child_module(binding->module());
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
  out_ << "module " << module.ctx->name() << '(';
  {
    auto_indent indent(out_);
    auto_separator sep(",");
    for (auto input : module.ctx->inputs()) {
      out_ << sep << std::endl;
      this->print_port(module, input);
    }
    for (auto output : module.ctx->outputs()) {
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
    for (auto node : module.ctx->literals()) {
      written |= this->print_decl(module, node, visited);
    }
    for (auto node : module.ctx->nodes()) {
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
    for (auto node : module.ctx->nodes()) {
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

    for (auto output : module.ctx->outputs()) {
      out_ << "assign ";
      this->print_name(module, output);
      out_ << " = ";
      this->print_name(module, reinterpret_cast<outputimpl*>(output)->src(0).impl());
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
  auto m = node->module();
  out_ << m->name() << " __module" << m->id() << "__(";
  for (auto& input : node->inputs()) {
    auto b = reinterpret_cast<bindportimpl*>(input.impl());
    auto p = reinterpret_cast<ioimpl*>(b->ioport().impl());
    out_ << sep << "." << p->name() << "(";
    this->print_name(module, b);
    out_ << ")";
  }
  for (auto& output : node->outputs()) {
    auto b = reinterpret_cast<bindportimpl*>(output.impl());
    auto p = reinterpret_cast<ioimpl*>(b->ioport().impl());
    out_ << sep << "." << p->name() << "(";
    this->print_name(module, b);
    out_ << ")";
  }
  out_ << ");" << std::endl;
  return true;
}

bool verilogwriter::print_bindport(module_t& module, bindportimpl* node) {
  // outputs are sourced via binding already
  if (node->type() == type_bindout)
    return false;

  out_ << "assign ";
  this->print_name(module, node);
  out_ << " = ";
  this->print_name(module, node->src(0).impl());
  out_ << ";" << std::endl;
  return true;
}

void verilogwriter::print_port(module_t& module, lnodeimpl* node) {
  auto type = node->type();
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
  if (visited.count(node->id()))
    return false;

  auto type = node->type();
  switch (type) {
  case type_lit:
    visited.insert(node->id());
    if (is_inline_literal(node))
      return false;
    this->print_type(node);
    out_ << " ";
    this->print_name(module, node);
    out_ << " = ";
    this->print_value(node->value(), true);
    out_ << ";" << std::endl;    
    return true;
  case type_proxy:
    if (module.is_inline_subscript(node)) {
      visited.insert(node->id());
      return false;
    }
    [[fallthrough]];
  case type_bindin:
  case type_bindout:
  case type_alu:
  case type_sel:
  case type_reg:
  case type_mem:    
    if (ref
     && (IsRegType(ref->type()) != IsRegType(type)
      || ref->size() != node->size()))
      return false;    
    if (ref) {
      out_ << ", ";
    } else {
      this->print_type(node);
      out_ << " ";
    }
    this->print_name(module, node);
    if (type_mem == type) {
      out_ << "[0:" << (reinterpret_cast<memimpl*>(node)->num_items() - 1) << "]";
    }
    visited.insert(node->id());
    if (!ref) {
      if (0 == platform::self().dbg_verilog()) {
        for (auto other : node->ctx()->nodes()) {
          this->print_decl(module, other, visited, node);
        }
        out_ << ";" << std::endl;
      } else {        
        out_ << ";";
        auto& sloc = node->sloc();
        if (!sloc.empty() || node->var_id() != 0) {
          out_ << " // ";
          if (node->var_id() != 0) {
            out_ << "v" << node->var_id();
            if (!sloc.empty()) {
              out_ << " - ";
            }
          }
          if (!sloc.empty()) {
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
  case type_cd:
  case type_tap:
  case type_mrport:
  case type_mwport:
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

bool verilogwriter::print_logic(module_t& module, lnodeimpl* node) {
  auto type = node->type();
  switch (type) {
  case type_proxy:
    if (module.is_inline_subscript(node))
      return false;
    out_ << "assign ";
    this->print_name(module, node);
    out_ << " = ";
    this->print_proxy(module, reinterpret_cast<proxyimpl*>(node));
    out_ << ";" << std::endl;
    return true;
  case type_alu:
    this->print_alu(module, reinterpret_cast<aluimpl*>(node));
    return true;
  case type_sel:
    this->print_select(module, reinterpret_cast<selectimpl*>(node));
    return true;
  case type_reg:
    this->print_reg(module, reinterpret_cast<regimpl*>(node));
    return true;
  case type_mem:
    this->print_mem(module, reinterpret_cast<memimpl*>(node));
    return true;
  case type_bind:
    this->print_binding(module, reinterpret_cast<bindimpl*>(node));
    return true;
  case type_bindin:
  case type_bindout:
    this->print_bindport(module, reinterpret_cast<bindportimpl*>(node));
    return true;  
  case type_lit:
  case type_input:
  case type_output:
  case type_cd:
  case type_tap:
  case type_mrport:
  case type_mwport:
  case type_assert:
  case type_print:
  case type_time:
    break;
  default:
    assert(false);
  }
  return false;
}

void verilogwriter::print_proxy(module_t& module, proxyimpl* node) {
  const auto& ranges = node->ranges();
  uint32_t dst_offset = node->size();
  auto print_range = [&](const proxyimpl::range_t& range) {
    dst_offset -= range.length;
    assert(range.dst_offset == dst_offset);
    auto& src = node->src(range.src_idx);
    this->print_name(module, src.impl());
    if (range.length < src.size()) {
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
  auto op = node->op();
  if (op == op_zext) {
    this->print_zext(module, node);
  } else
  if (op == op_sext) {
    this->print_sext(module, node);
  } else {
    out_ << "assign ";
    this->print_name(module, node);
    out_ << " = ";
    if (CH_OP_ARY(op) == op_binary) {
      this->print_name(module, node->src(0).impl());
      out_ << " ";
      this->print_operator(op);
      out_ << " ";
      this->print_name(module, node->src(1).impl());
      out_ << ";" << std::endl;
    } else {
      assert(CH_OP_ARY(op) == op_unary);
      this->print_operator(op);
      this->print_name(module, node->src(0).impl());
      out_ << ";" << std::endl;
    }
  }
}

void verilogwriter::print_zext(module_t& module, aluimpl* node) {
  out_ << "assign ";
  this->print_name(module, node);
  out_ << " = {{" << node->size() - node->src(0).size() << "{1'b0}}, ";
  this->print_name(module, node->src(0).impl());
  out_ << "};" << std::endl;
}

void verilogwriter::print_sext(module_t& module, aluimpl* node) {
  out_ << "assign ";
  this->print_name(module, node);
  out_ << " = {{" << node->size() - node->src(0).size() << "{";
  this->print_name(module, node->src(0).impl());
  out_ << "[" << (node->src(0).size() - 1) << "]}";
  this->print_name(module, node->src(0).impl());
  out_ << ";" << std::endl;
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
      this->print_name(module, node->src(0).impl());
      out_ << " == ";
      this->print_name(module, node->src(1).impl());
      out_ << ")";
    } else {
      this->print_name(module, node->src(0).impl());
    }
    out_ << " ? ";
    this->print_name(module, node->src(i+1).impl());
    out_ << " : ";
    this->print_name(module, node->src(i+2).impl());
    out_ << ";" << std::endl;
  } else {
    uint32_t last = node->num_srcs() - 1;
    out_ << "always @(*) begin" << std::endl;
    if (has_key) {
      auto_indent indent1(out_);
      out_ << "case (";
      this->print_name(module, node->src(0).impl());
      out_ << ")" << std::endl;
      {
        auto_indent indent2(out_);
        for (; i < last; i += 2) {
          print_value(node->src(i).impl()->value(), false);
          out_ << ": ";
          this->print_name(module, node);
          out_ << " = ";
          this->print_name(module, node->src(i + 1).impl());
          out_ << ";" << std::endl;
        }
        out_ << "default: ";
        this->print_name(module, node);
        out_ << " = ";
        this->print_name(module, node->src(i).impl());
        out_ << ";" << std::endl;
      }
      out_ << "endcase" << std::endl;
    } else {
      auto_indent indent1(out_);
      for (; i < last; i += 2) {
        out_ << (0 == i ? "if (" : "else if (");
        this->print_name(module, node->src(i).impl());
        out_ << ")" << std::endl;
        {
          auto_indent indent2(out_);
          this->print_name(module, node);
          out_ << " = ";
          this->print_name(module, node->src(i + 1).impl());
          out_ << ";" << std::endl;
        }
      }
      out_ << "else" << std::endl;
      {
        auto_indent indent2(out_);
        this->print_name(module, node);
        out_ << " = ";
        this->print_name(module, node->src(i).impl());
        out_ << ";" << std::endl;
      }
    }
    out_ << "end" << std::endl;
  }
}

void verilogwriter::print_reg(module_t& module, regimpl* node) {
  out_ << "always @ (";
  auto cd = reinterpret_cast<cdimpl*>(node->cd().impl());
  this->print_cdomain(module, cd);
  out_ << ") begin" << std::endl;
  {
    auto_indent indent(out_);
    this->print_name(module, node);
    out_ << " <= ";
    if (node->has_init()) {
      this->print_name(module, cd->rst().impl());
      out_ << " ? ";
      this->print_name(module, node->init().impl());
      out_ << " : ";
      this->print_name(module, node->next().impl());
    } else {
      this->print_name(module, node->next().impl());
    }
    out_ << ";" << std::endl;
  }
  out_ << "end" << std::endl;
}

void verilogwriter::print_cdomain(module_t& module, cdimpl* cd) {
  out_ << (cd->posedge() ? "posedge" : "negedge") << " ";
  this->print_name(module, cd->clk().impl());
}

void verilogwriter::print_mem(module_t& module, memimpl* node) {
  //
  // initialization data
  //
  if (node->has_initdata()) {
    out_ << "initial begin" << std::endl;
    {
      auto_indent indent(out_);
      const auto& value = node->value();
      uint32_t data_width = node->data_width();
      uint32_t num_items = node->num_items();
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
  for (auto p : node->ports()) {
    if (p->type() == type_mrport)
      continue;
    auto mwport = reinterpret_cast<mwportimpl*>(p);
    out_ << "always @(" ;
    auto cd = reinterpret_cast<cdimpl*>(mwport->cd().impl());
    this->print_cdomain(module, cd);
    out_ << ") begin" << std::endl;
    {
      auto_indent indent1(out_);
      if (mwport->has_wenable()) {
        out_ << "if (";
        this->print_name(module, mwport->wenable().impl());
        out_ << ") begin" << std::endl;
        {
          auto_indent indent2(out_);
          this->print_name(module, mwport);
          out_ << " = ";
          this->print_name(module, mwport->wdata().impl());
          out_ << ";" << std::endl;
        }
        out_ << "end" << std::endl;
      } else {
        this->print_name(module, mwport);
        out_ << " = ";
        this->print_name(module, mwport->wdata().impl());
        out_ << ";" << std::endl;
      }
    }
    out_ << "end" << std::endl;
  }
}

void verilogwriter::print_name(module_t& module, lnodeimpl* node, bool force) {
  auto print_unique_name = [&](const lnode& node) {
    out_ << node.name() << node.id();
  };

  auto type = node->type();
  switch (type) {
  case type_input:
  case type_output:
    out_ << node->name();
    break;
  case type_proxy:    
    if (!force && module.is_inline_subscript(node)) {
      this->print_proxy(module, reinterpret_cast<proxyimpl*>(node));
    } else {
      print_unique_name(node);
    }
    break;
  case type_lit:
    if (!force && is_inline_literal(node)) {
      print_value(node->value(), true);
    } else {
      print_unique_name(node);
    }
    break;
  case type_sel:
  case type_alu:
  case type_reg:
  case type_mem:
  case type_bindin:
  case type_bindout:
    print_unique_name(node);
    break;
  case type_mrport:
  case type_mwport: {
    auto memport = reinterpret_cast<memportimpl*>(node);
    this->print_name(module, memport->mem());
    out_ << "[";
    this->print_name(module, memport->addr().impl());
    out_ << "]";
  } break;
  case type_time:
    out_ << "$time";
    break;
  default:
    assert(false);
  }
}

void verilogwriter::print_type(lnodeimpl* node) {
  auto type = node->type();

  auto is_reg_type = (type_sel == type) ?
        !reinterpret_cast<selectimpl*>(node)->is_ternary() :
        IsRegType(type);

  out_ << (is_reg_type ? "reg" : "wire");

  if (type == type_mem) {
    auto data_width = reinterpret_cast<memimpl*>(node)->data_width();
    if (data_width > 1) {
      out_ << "[" << (data_width - 1) << ":0]";
    }
  } else {
    if (node->size() > 1) {
      out_ << "[" << (node->size() - 1) << ":0]";
    }
  }
}

void verilogwriter::print_value(const bitvector& value,
                                bool skip_leading_zeros_enable,
                                uint32_t offset,
                                uint32_t size) {
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
    size = value.size();
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

void verilogwriter::print_operator(ch_op op) {
  switch (op) {
  case op_inv:   out_ << "~"; break;
  case op_and:   out_ << "&"; break;
  case op_or:    out_ << "|"; break;
  case op_xor:   out_ << "^"; break;
  case op_andr:  out_ << "&"; break;
  case op_orr:   out_ << "|"; break;
  case op_xorr:  out_ << "^"; break;

  case op_neg:   out_ << "-"; break;
  case op_add:   out_ << "+"; break;
  case op_sub:   out_ << "-"; break;
  case op_mult:  out_ << "*"; break;
  case op_div:   out_ << "/"; break;
  case op_mod:   out_ << "%"; break;

  case op_sll:   out_ << "<<"; break;
  case op_srl:   out_ << ">>"; break;
  case op_sra:   out_ << ">>>"; break;

  case op_eq:    out_ << "=="; break;
  case op_ne:    out_ << "!="; break;
  case op_lt:    out_ << "<"; break;
  case op_gt:    out_ << ">"; break;
  case op_le:    out_ << "<="; break;
  case op_ge:    out_ << ">="; break;
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
