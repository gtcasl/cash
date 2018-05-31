#include "firrtlwriter.h"
#include "firrtl.h"
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

const auto is_inline_literal = [](lnodeimpl* node) {
  assert(type_lit == node->type());
  return (node->size() <= 32);
};

firrtlwriter::module_t::module_t(context* p_ctx)
  : ctx(p_ctx)
  , num_temps(0)
{
  for (lnodeimpl* node : ctx->nodes()) {
    for (auto& src : node->srcs()) {
      uses[src.id()].insert(node);
    }
  }
}

bool firrtlwriter::module_t::is_inline_subscript(lnodeimpl* node) const {
  assert(type_proxy == node->type());
  if (reinterpret_cast<proxyimpl*>(node)->ranges().size() > 1)
    return false;
  auto it = uses.find(node->id());
  if (it != uses.end()) {
    for (lnodeimpl* use : it->second) {
      if (type_proxy == use->type()
       || type_memport == use->type())
        return false;
    }
  }
  lnodeimpl* src = node->src(0).impl();
  if (type_proxy == src->type()
   || type_memport == src->type())
    return false;
  return true;
}

firrtlwriter::firrtlwriter(std::ostream& out) : out_(out) {
  //--
}

firrtlwriter::~firrtlwriter() {
  //--
}

void firrtlwriter::print(context* ctx) {
  // header
  out_ << "circuit " << ctx->name() << ":" << std::endl;
  {
    // print top module
    auto_indent indent(out_);
    module_t module(ctx);
    this->print_module(module);
  }
}

bool firrtlwriter::print_module(module_t& module) {
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

  out_ << "module " << module.ctx->name() << ':' << std::endl;
  {
    auto_indent indent(out_);

    // print header
    this->print_header(module);

    // print body
    this->print_body(module);

    // print footer
    this->print_footer(module);
  }

  return true;
}

void firrtlwriter::print_header(module_t& module) {
  //
  // ports declaration
  //  
  for (auto input : module.ctx->inputs()) {
    this->print_port(input);
    out_ << std::endl;
  }
  for (auto output : module.ctx->outputs()) {
    this->print_port(output);
    out_ << std::endl;
  }
  out_ << std::endl;
}

void firrtlwriter::print_body(module_t& module) {
  //
  // declaration
  //
  {
    std::unordered_set<uint32_t> visited;
    int written = 0;
    for (auto node : module.ctx->literals()) {
      written |= this->print_decl(node, visited);
    }
    for (auto node : module.ctx->nodes()) {
      written |= this->print_decl(node, visited);
    }
    if (written) {
      out_ << std::endl;
    }
  }

  //
  // body logic
  //
  {
    int written = 0;
    for (auto node : module.ctx->nodes()) {
      written |= this->print_logic(module, node);
    }
    if (written) {
      out_ << std::endl;
    }
  }
}

void firrtlwriter::print_footer(module_t& module) {
  //
  // output assignment
  //
  int written = 0;
  for (auto output : module.ctx->outputs()) {
    this->print_name(output);
    out_ << " <= ";
    this->print_name(reinterpret_cast<outputimpl*>(output)->src(0).impl());
    out_ << std::endl;
    written = 1;
  }
  if (written) {
    out_ << std::endl;
  }
}

bool firrtlwriter::print_binding(bindimpl* node) {
  auto m = node->module();
  out_ << "inst __module" << m->id() << " of ";
  out_ << m->name() << std::endl;
  for (auto& input : node->inputs()) {
    auto b = reinterpret_cast<bindportimpl*>(input.impl());
    auto p = reinterpret_cast<ioimpl*>(b->ioport().impl());
    out_ << "__module" << m->id() << "." << p->name() << " <= ";
    this->print_name(b);
    out_ << std::endl;
  }
  for (auto& output : node->outputs()) {
    auto b = reinterpret_cast<bindportimpl*>(output.impl());
    auto p = reinterpret_cast<ioimpl*>(b->ioport().impl());
    this->print_name(b);
    out_ << " <= __module" << m->id() << "." << p->name() << std::endl;
  }
  return true;
}

bool firrtlwriter::print_bindport(bindportimpl* node) {
  // outputs are sourced via binding already
  if (node->is_output())
    return false;
  this->print_name(node);
  out_ << " <= ";
  this->print_name(node->src(0).impl());
  out_ << std::endl;
  return true;
}

void firrtlwriter::print_port(lnodeimpl* node) {
  //--
  this->print_type(node);
  out_ << " ";
  this->print_name(node);
  out_ << " : ";
  this->print_dtype(node);
}

bool firrtlwriter::print_decl(lnodeimpl* node,
                              std::unordered_set<uint32_t>& visited) {
  if (visited.count(node->id()))
    return false;
  visited.insert(node->id());

  auto type = node->type();
  switch (type) {
  case type_lit:    
    if (is_inline_literal(node))
      return false;
    [[fallthrough]];
  case type_proxy:
  case type_bindport:
  case type_alu:
  case type_sel:
  case type_reg:
  case type_mem: {
    this->print_type(node);
    out_ << " ";
    this->print_name(node);
    out_ << " : ";
    this->print_dtype(node);
    auto& sloc = node->sloc();
    if (!sloc.empty() || node->var_id() != 0) {
      out_ << " @[";
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
      out_ << "]";
    }
    out_ << std::endl;
    return true;
  }
  case type_bind:
  case type_input:
  case type_output:
  case type_cd:
  case type_tap:
  case type_memport:
  case type_assert:
  case type_print:
  case type_time:
    break;
  default:
    assert(false);
  }
  return false;
}

bool firrtlwriter::print_logic(module_t& module, lnodeimpl* node) {
  auto type = node->type();
  switch (type) {
  case type_lit:
    if (is_inline_literal(node))
      return false;
    this->print_lit(reinterpret_cast<litimpl*>(node));
    return true;
  case type_proxy:
    this->print_proxy(module, reinterpret_cast<proxyimpl*>(node));
    return true;
  case type_alu:
    this->print_alu(module, reinterpret_cast<aluimpl*>(node));
    return true;
  case type_sel:
    this->print_select(module, reinterpret_cast<selectimpl*>(node));
    return true;
  case type_reg:
    this->print_reg(dynamic_cast<regimpl*>(node));
    return true;
  case type_mem:
    this->print_mem(dynamic_cast<memimpl*>(node));
    return true;
  case type_bind:
    this->print_binding(reinterpret_cast<bindimpl*>(node));
    return true;
  case type_bindport:
    this->print_bindport(reinterpret_cast<bindportimpl*>(node));
    return true;
  case type_input:
  case type_output:
  case type_cd:
  case type_tap:  
  case type_memport:
  case type_assert:
  case type_print:
  case type_time:
    break;
  default:
    assert(false);
  }
  return false;
}

void firrtlwriter::print_lit(litimpl* node) {
  this->print_name(node);
  out_ << " <= ";
  this->print_value(node->value(), true);
  out_ << std::endl;
}

void firrtlwriter::print_proxy(module_t& module, proxyimpl* node) {
  //--
  struct range_hash {
      std::size_t operator()(const proxyimpl::range_t& range) const noexcept {
        auto h0 = std::hash<uint32_t>{}(range.src_idx);
        auto h1 = std::hash<uint32_t>{}(range.dst_offset);
        auto h2 = std::hash<uint32_t>{}(range.src_offset);
        auto h3 = std::hash<uint32_t>{}(range.length);
        return hash_combine(h0, hash_combine(h1, hash_combine(h2, h3)));
      }
  };

  //--
  const auto& ranges = node->ranges();  
  std::unordered_map<proxyimpl::range_t, uint32_t, range_hash> tmps;

  //--
  auto alloc_tmp = [&](const proxyimpl::range_t& range)->uint32_t {
    auto tmp = module.num_temps++;
    tmps[range] = tmp;
      return tmp;
  };

  //--
  auto print_range = [&](const proxyimpl::range_t& range) {
    auto& src = node->src(range.src_idx);
    if (range.length == src.size()) {
      this->print_name(src.impl());
    } else {
      out_ << "_t" << tmps[range];
    }
  };

  //--  
  for (auto& range : ranges) {
    auto& src = node->src(range.src_idx);
    if (range.length != src.size()) {
      out_ << "node _t" << alloc_tmp(range) << " = bits(";
      this->print_name(src.impl());
      out_ << ", " << (range.src_offset + range.length - 1);
      out_ << ", " << range.src_offset << ")";
      out_ << std::endl;
    }
  }

  //--  
  if (ranges.size() > 1) {
    uint32_t prev_dst(0);
    for (uint32_t i = 1, n = ranges.size(); i < n; ++i) {
      uint32_t dst = 0;
      if (i+1 == n) {
        this->print_name(node);
        out_ << " <= ";
      } else {
        dst = module.num_temps++;
        out_ << "node _t" << dst << " = ";
      }

      out_ << "cat(";
      print_range(ranges[i]);
      out_ << ", ";
      if (1 == i) {
        print_range(ranges[0]);
      } else {
        out_ << "_t" << prev_dst;
      }
      out_ << ")";
      prev_dst = dst;
    }
  } else {
    this->print_name(node);
    out_ << " <= ";
    print_range(ranges[0]);
  }
  out_ << std::endl;
}

void firrtlwriter::print_alu(module_t& module, aluimpl* node) {
  auto op = node->op();
  if (op == op_sub) {
    auto dst = module.num_temps++;
    out_ << "node _t" << dst << " = sub(";
    this->print_name(node->src(0).impl());
    out_ << ", ";
    this->print_name(node->src(1).impl());
    out_ << ")" << std::endl;
    this->print_name(node);
    out_ << " <= asUInt(_t" << dst << ")" << std::endl;
  } else
  if (op == op_neg) {
    auto dst = module.num_temps++;
    out_ << "node _t" << dst << " = neg(";
    this->print_name(node->src(0).impl());
    out_ << ")" << std::endl;
    this->print_name(node);
    out_ << " <= asUInt(_t" << dst << ")" << std::endl;
  } else
  if (op == op_sra) {
    auto dst = module.num_temps++;
    out_ << "node _t" << dst << " = asSInt(";
    this->print_name(node->src(0).impl());
    out_ << ")" << std::endl;
    this->print_name(node);
    out_ << " <= dshr(_t" << dst << ", ";
    this->print_name(node->src(1).impl());
    out_ << ")" << std::endl;
  } else
  if (op == op_zext) {
    this->print_name(node);
    out_ << " <= pad<" << node->size() << ">(";
    this->print_name(node->src(0).impl());
    out_ << ")" << std::endl;
  } else
  if (op == op_sext) {
    auto src = module.num_temps++;
    auto dst = module.num_temps++;
    out_ << "node _t" << src << " = asSInt(";
    this->print_name(node->src(0).impl());
    out_ << ")" << std::endl;
    out_ << "node _t" << dst << " = pad<" << node->size() << ">(";
    out_ << "_t" << src << ")" << std::endl;
    this->print_name(node);
    out_ << " <= asUInt(_t" << dst << ")" << std::endl;
  } else{
    this->print_name(node);
    out_ << " <= ";
    if (CH_OP_ARY(op) == op_binary) {
      this->print_operator(op);
      out_ << "(";
      this->print_name(node->src(0).impl());
      out_ << ", ";
      this->print_name(node->src(1).impl());
      out_ << ")" << std::endl;
    } else {
      assert(CH_OP_ARY(op) == op_unary);
      this->print_operator(op);
      out_ << "(";
      this->print_name(node->src(0).impl());
      out_ << ")" << std::endl;
    }
  }
}

void firrtlwriter::print_select(module_t& module, selectimpl* node) {
  bool has_key = node->has_key();
  if (!has_key && node->is_ternary()) {
    this->print_name(node);
    out_ << " <= mux(";
    this->print_name(node->src(0).impl());
    out_ << ", ";
    this->print_name(node->src(1).impl());
    out_ << ", ";
    this->print_name(node->src(2).impl());
    out_ << ")" << std::endl;
  } else {
    std::unordered_map<uint32_t, uint32_t> tmps;
    uint32_t i = has_key ? 1 : 0;
    uint32_t last = node->num_srcs() - 1;
    if (has_key) {
      for (uint32_t j = i; j < last; j += 2) {
        auto dst = module.num_temps++;
        tmps[node->src(j).id()] = dst;
        out_ << "node _t" << dst << " = eq(";
        this->print_name(node->src(0).impl());
        out_ << ", ";
        this->print_name(node->src(j).impl());
        out_ << ")" << std::endl;
      }
    }

    auto_separator sep("else ");
    for (; i < last; i += 2) {
      out_ << sep << "when ";
      if (has_key) {
        out_ << "_t" << tmps[node->src(i).id()];
      } else {
        this->print_name(node->src(i).impl());
      }
      out_ << " :" << std::endl;
      {
        auto_indent indent(out_);
        this->print_name(node);
        out_ << " <= ";
        this->print_name(node->src(i + 1).impl());
        out_ << std::endl;
      }
    }
    out_ << "else :" << std::endl;
    {
      auto_indent indent(out_);
      this->print_name(node);
      out_ << " <= ";
      this->print_name(node->src(i).impl());
      out_ << std::endl;
    }
  }
}

void firrtlwriter::print_reg(regimpl* node) {
  this->print_name(node);
  out_ << " <= ";
  if (node->has_init()) {
    out_ << " mux(";
    auto cd = reinterpret_cast<cdimpl*>(node->cd().impl());
    this->print_name(cd->rst().impl());
    out_ << ", ";
    this->print_name(node->init().impl());
    out_ << ", ";
    this->print_name(node->next().impl());
    out_ << ")";
  } else {
    this->print_name(node->next().impl());
  }
  out_ << std::endl;
}

void firrtlwriter::print_cdomain(cdimpl* cd) {
  assert(cd->posedge());
  this->print_name(cd->clk().impl());
}

void firrtlwriter::print_mem(memimpl* node) {
  auto print_attributes = [&](memportimpl* port) {
    char type;
    if (port->has_wdata()) {
      if (port->is_read_enable()) {
        type = 'x';
        this->print_name(node);
        out_ << '.' << type << port->index() << ".wmode <= UInt<1>(\"h1\")";
        out_ << std::endl;
      } else {
        type = 'w';
      }

      this->print_name(node);
      out_ << '.' << type << port->index() << ".data <= ";
      this->print_name(port->wdata().impl());
      out_ << std::endl;

      this->print_name(node);
      out_ << '.' << type << port->index() << ".mask <= ";
      std::string mask(port->wdata().size(), '1');
      this->print_value(bitvector(port->wdata().size(), mask + "b"));
      out_ << std::endl;

      this->print_name(node);
      out_ << '.' << type << port->index() << ".en <= ";
      if (port->has_wenable()) {
        this->print_name(port->wenable().impl());
      } else {
        out_ << "UInt<1>(\"h1\")";
      }
      out_ << std::endl;
    } else {
      type = 'r';
      this->print_name(node);
      out_ << '.' << type << port->index() << ".en <= UInt<1>(\"h1\")";
      out_ << std::endl;
    }

    this->print_name(node);
    out_ << '.' << type << port->index() << ".addr <= ";
    this->print_name(port->addr().impl());
    out_ << std::endl;

    this->print_name(node);
    out_ << '.' << type << port->index() << ".clk <= ";
    auto cd = reinterpret_cast<cdimpl*>(node->cd().impl());
    this->print_cdomain(cd);
    out_ << std::endl;
  };

  if (node->is_write_enable()) {
    // initialization data not supported!
    assert(!node->has_initdata());
    for (auto port : node->ports()) {
      print_attributes(port);
    }
  } else {
    assert(node->has_initdata());
    auto data_width = node->data_width();
    auto data_cbsize = CH_CEILDIV(data_width, 8);
    bitvector value(data_width);
    for (uint32_t i = 0, n = node->num_items(); i < n; ++i) {
      this->print_name(node);
      out_ << "[" << i << "] <= ";
      node->value().read(0, value.words(), data_cbsize, i * data_width, data_width);
      this->print_value(value);
      out_ << std::endl;
    }
  }
}

void firrtlwriter::print_operator(ch_op op) {
  switch (op) {
  case op_inv:   out_ << "not"; break;
  case op_and:   out_ << "and"; break;
  case op_or:    out_ << "or"; break;
  case op_xor:   out_ << "xor"; break;
  case op_andr:  out_ << "andr"; break;
  case op_orr:   out_ << "orr"; break;
  case op_xorr:  out_ << "xorr"; break;

  case op_neg:   out_ << "neg"; break;
  case op_add:   out_ << "add"; break;
  case op_sub:   out_ << "sub"; break;
  case op_mult:  out_ << "mul"; break;
  case op_div:   out_ << "div"; break;
  case op_mod:   out_ << "mod"; break;

  case op_sll:   out_ << "dshl"; break;
  case op_srl:   out_ << "dshr"; break;
  case op_sra:   out_ << "dshr"; break;

  case op_eq:    out_ << "eq"; break;
  case op_ne:    out_ << "neq"; break;
  case op_lt:    out_ << "lt"; break;
  case op_gt:    out_ << "gt"; break;
  case op_le:    out_ << "leq"; break;
  case op_ge:    out_ << "geq"; break;
  default:
    assert(false);
  }
}

void firrtlwriter::print_name(lnodeimpl* node, bool force) {
  auto print_unique_name = [&](lnodeimpl* node) {
    out_ << node->name() << node->id();
  };

  auto type = node->type();
  switch (type) {
  case type_input:
  case type_output:
    out_ << node->name();
    break;
  case type_proxy:
    print_unique_name(node);
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
  case type_bindport:
    print_unique_name(node);
    break;
  case type_memport: {
    auto port = reinterpret_cast<memportimpl*>(node);
    auto mem = dynamic_cast<memimpl*>(port->mem().impl());
    this->print_name(mem);
    if (mem->is_write_enable()) {
      if (port->is_read_enable()
       && !port->has_wdata()) {
        // read-only
        out_ << ".r" << port->index() << ".data";
      } else
      if (!port->is_read_enable()
       && port->has_wdata()) {
        // write-only
        out_ << ".w" << port->index() << ".data";
      } else {
        assert(port->is_read_enable());
        assert(port->has_wdata());
        // read-write
        out_ << ".x" << port->index() << ".rdata";
      }
    } else {
      out_ << "[";
      print_unique_name(port->addr().impl());
      out_ << "]";
    }
  } break;
  default:
    assert(false);
  }
}

void firrtlwriter::print_type(lnodeimpl* node) {
  auto type = node->type();
  switch (type) {
  case type_input:
    out_ << "input";
    break;
  case type_output:
  case type_tap:
    out_ << "output";
    break;
  case type_lit:
  case type_proxy:
  case type_sel:
  case type_alu:
  case type_bindport:
  case type_memport:
    out_ << "wire";
    break;
  case type_reg:
    out_ << "reg";
    break;
  case type_mem: {
    auto mem = dynamic_cast<memimpl*>(node);
    out_ << (mem->is_write_enable() ? "mem" : "wire");
  } break;
  default:
    assert(false);
  }
}

void firrtlwriter::print_dtype(lnodeimpl* node) {
  auto type = node->type();
  switch (type) {
  case type_input:
    if ("clk" == reinterpret_cast<inputimpl*>(node)->name()) {
      out_ << "Clock";
    } else {
      out_ << "UInt<" << node->size() << ">";
    }
    break;
  case type_reg: {
    out_ << "UInt<" << node->size() << ">, ";
    auto cd = reinterpret_cast<cdimpl*>(dynamic_cast<regimpl*>(node)->cd().impl());
    this->print_cdomain(cd);
  } break;
  case type_mem: {    
    auto mem = dynamic_cast<memimpl*>(node);
    if (mem->is_write_enable()) {
      auto_indent indent(out_);
      out_ << std::endl;
      out_ << "data-type => UInt<" << mem->data_width() << ">" << std::endl;
      out_ << "depth => " << mem->num_items() << std::endl;
      out_ << "read-latency => 0" << std::endl;
      out_ << "write-latency => 1" << std::endl;
      out_ << "read-under-write => undefined" << std::endl;

      auto_separator sep("\n");
      for (auto port : mem->ports()) {
        out_ << sep;
        if (port->is_read_enable()
        && !port->has_wdata()) {
          // read-only
          out_ << "reader => r" << port->index();
        } else
        if (!port->is_read_enable()
         && port->has_wdata()) {
          // write-only
          out_ << "writer => w" << port->index();
        } else {
          assert(port->is_read_enable() && port->has_wdata());
          // read-write
          out_ << "readwriter => x" << port->index();
        }
      }
    } else {
      out_ << "UInt<" << mem->data_width() << ">"
           << "[" << mem->num_items() << "]";
    }
  } break;
  case type_bindport: {
    auto b = reinterpret_cast<bindportimpl*>(node);
    auto p = reinterpret_cast<ioimpl*>(b->ioport().impl());
    if (type_input == p->type()
     && "clk" == reinterpret_cast<inputimpl*>(p)->name()) {
      out_ << "Clock";
    } else {
      out_ << "UInt<" << node->size() << ">";
    }
  } break;
  default:
    out_ << "UInt<" << node->size() << ">";
    break;
  }
}

void firrtlwriter::print_value(const bitvector& value,
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

  out_ << "UInt<" << size << ">(\"h";
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
  out_ << "\")";
}

///////////////////////////////////////////////////////////////////////////////

void ch::internal::toFIRRTL(std::ostream& out, context* ctx) {
  firrtlwriter writer(out);
  writer.print(ctx);
}
