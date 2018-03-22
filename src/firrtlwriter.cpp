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
#include "tickimpl.h"
#include <cstring>

using namespace ch::internal;

const auto is_inline_literal = [](lnodeimpl* node) {
  assert(type_lit == node->get_type());
  return (node->get_size() <= 32);
};

firrtlwriter::module_t::module_t(context* p_ctx)
  : ctx(p_ctx)
  , num_temps(0)
{
  for (lnodeimpl* node : ctx->get_nodes()) {
    for (auto& src : node->get_srcs()) {
      uses[src.get_id()].insert(node);
    }
  }
}

bool firrtlwriter::module_t::is_inline_subscript(lnodeimpl* node) const {
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

firrtlwriter::firrtlwriter(std::ostream& out) : out_(out) {
  //--
}

firrtlwriter::~firrtlwriter() {
  //--
}

void firrtlwriter::print(context* ctx) {
  // header
  out_ << "circuit " << ctx->get_name() << ":" << std::endl;
  {
    // print top module
    auto_indent indent(out_);
    module_t module(ctx);
    this->print_module(module);
  }
}

bool firrtlwriter::print_module(module_t& module) {
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

  out_ << "module " << module.ctx->get_name() << ':' << std::endl;
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
  for (auto input : module.ctx->get_inputs()) {
    this->print_port(input);
    out_ << std::endl;
  }
  for (auto output : module.ctx->get_outputs()) {
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
    for (auto node : module.ctx->get_literals()) {
      written |= this->print_decl(node, visited);
    }
    for (auto node : module.ctx->get_nodes()) {
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
    for (auto node : module.ctx->get_nodes()) {
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
  for (auto output : module.ctx->get_outputs()) {
    this->print_name(output);
    out_ << " <= ";
    this->print_name(dynamic_cast<outputimpl*>(output)->get_src(0).get_impl());
    out_ << std::endl;
    written = 1;
  }
  if (written) {
    out_ << std::endl;
  }
}

bool firrtlwriter::print_binding(bindimpl* node) {
  auto m = node->get_module();
  out_ << "inst __module" << m->get_id() << " of ";
  out_ << m->get_name() << std::endl;
  for (auto& input : node->get_inputs()) {
    auto b = dynamic_cast<bindportimpl*>(input.get_impl());
    auto p = dynamic_cast<ioimpl*>(b->get_ioport().get_impl());
    out_ << "__module" << m->get_id() << "." << p->get_name() << " <= ";
    this->print_name(b);
    out_ << std::endl;
  }
  for (auto& output : node->get_outputs()) {
    auto b = dynamic_cast<bindportimpl*>(output.get_impl());
    auto p = dynamic_cast<ioimpl*>(b->get_ioport().get_impl());
    this->print_name(b);
    out_ << " <= __module" << m->get_id() << "." << p->get_name() << std::endl;
  }
  return true;
}

bool firrtlwriter::print_bindport(bindportimpl* node) {
  // outputs are sourced via binding already
  if (node->is_output())
    return false;
  this->print_name(node);
  out_ << " <= ";
  this->print_name(node->get_src(0).get_impl());
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
  if (visited.count(node->get_id()))
    return false;
  visited.insert(node->get_id());

  auto type = node->get_type();
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
    auto& sloc = node->get_source_location();
    if (!sloc.is_empty() || node->get_var_id() != 0) {
      out_ << " @[";
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
      out_ << "]";
    }
    out_ << std::endl;
    return true;
  }
  case type_bind:
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

bool firrtlwriter::print_logic(module_t& module, lnodeimpl* node) {
  auto type = node->get_type();
  switch (type) {
  case type_lit:
    if (is_inline_literal(node))
      return false;
    this->print_lit(dynamic_cast<litimpl*>(node));
    return true;
  case type_proxy:
    this->print_proxy(module, dynamic_cast<proxyimpl*>(node));
    return true;
  case type_alu:
    this->print_alu(module, dynamic_cast<aluimpl*>(node));
    return true;
  case type_sel:
    this->print_select(module, dynamic_cast<selectimpl*>(node));
    return true;
  case type_reg:
    this->print_reg(dynamic_cast<regimpl*>(node));
    return true;
  case type_mem:
    this->print_mem(dynamic_cast<memimpl*>(node));
    return true;
  case type_bind:
    this->print_binding(dynamic_cast<bindimpl*>(node));
    return true;
  case type_bindport:
    this->print_bindport(dynamic_cast<bindportimpl*>(node));
    return true;
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

void firrtlwriter::print_lit(litimpl* node) {
  this->print_name(node);
  out_ << " <= ";
  this->print_value(node->get_value(), true);
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
  const auto& ranges = node->get_ranges();  
  std::unordered_map<proxyimpl::range_t, uint32_t, range_hash> tmps;

  //--
  auto alloc_tmp = [&](const proxyimpl::range_t& range)->uint32_t {
    auto tmp = module.num_temps++;
    tmps[range] = tmp;
      return tmp;
  };

  //--
  auto print_range = [&](const proxyimpl::range_t& range) {
    auto& src = node->get_src(range.src_idx);
    if (range.length == src.get_size()) {
      this->print_name(src.get_impl());
    } else {
      out_ << "_t" << tmps[range];
    }
  };

  //--  
  for (auto& range : ranges) {
    auto& src = node->get_src(range.src_idx);
    if (range.length != src.get_size()) {
      out_ << "node _t" << alloc_tmp(range) << " = bits(";
      this->print_name(src.get_impl());
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
  auto op = node->get_op();
  if (op == alu_sub) {
    auto dst = module.num_temps++;
    out_ << "node _t" << dst << " = sub(";
    this->print_name(node->get_src(0).get_impl());
    out_ << ", ";
    this->print_name(node->get_src(1).get_impl());
    out_ << ")" << std::endl;
    this->print_name(node);
    out_ << " <= asUInt(_t" << dst << ")" << std::endl;
  } else
  if (op == alu_neg) {
    auto dst = module.num_temps++;
    out_ << "node _t" << dst << " = ned(";
    this->print_name(node->get_src(0).get_impl());
    out_ << ")" << std::endl;
    this->print_name(node);
    out_ << " <= asUInt(_t" << dst << ")" << std::endl;
  } else
  if (op == alu_sra) {
    auto dst = module.num_temps++;
    out_ << "node _t" << dst << " = asSInt(";
    this->print_name(node->get_src(0).get_impl());
    out_ << ")" << std::endl;
    this->print_name(node);
    out_ << " <= dshr(_t" << dst << ", ";
    this->print_name(node->get_src(1).get_impl());
    out_ << ")" << std::endl;
  } else
  if (CH_ALUOP_DTYPE(op) == alu_integer) {
    this->print_name(node);
    out_ << " <= ";
    if (CH_ALUOP_ARY(op) == alu_binary) {
      this->print_operator(op);
      out_ << "(";
      this->print_name(node->get_src(0).get_impl());
      out_ << ", ";
      this->print_name(node->get_src(1).get_impl());
      out_ << ")" << std::endl;
    } else {
      assert(CH_ALUOP_ARY(op) == alu_unary);
      this->print_operator(op);
      out_ << "(";
      this->print_name(node->get_src(0).get_impl());
      out_ << ")" << std::endl;
    }
  } else {
    assert(false);
  }
}

void firrtlwriter::print_select(module_t& module, selectimpl* node) {
  bool has_key = node->has_key();
  if (!has_key && node->is_ternary()) {
    this->print_name(node);
    out_ << " <= mux(";
    this->print_name(node->get_src(0).get_impl());
    out_ << ", ";
    this->print_name(node->get_src(1).get_impl());
    out_ << ", ";
    this->print_name(node->get_src(2).get_impl());
    out_ << ")" << std::endl;
  } else {
    std::unordered_map<uint32_t, uint32_t> tmps;
    uint32_t i = has_key ? 1 : 0;
    uint32_t last = node->get_num_srcs() - 1;
    if (has_key) {
      for (uint32_t j = i; j < last; j += 2) {
        auto dst = module.num_temps++;
        tmps[node->get_src(j).get_id()] = dst;
        out_ << "node _t" << dst << " = eq(";
        this->print_name(node->get_src(0).get_impl());
        out_ << ", ";
        this->print_name(node->get_src(j).get_impl());
        out_ << ")" << std::endl;
      }
    }

    auto_separator sep("else ");
    for (; i < last; i += 2) {
      out_ << sep << "when ";
      if (has_key) {
        out_ << "_t" << tmps[node->get_src(i).get_id()];
      } else {
        this->print_name(node->get_src(i).get_impl());
      }
      out_ << " :" << std::endl;
      {
        auto_indent indent(out_);
        this->print_name(node);
        out_ << " <= ";
        this->print_name(node->get_src(i + 1).get_impl());
        out_ << std::endl;
      }
    }
    out_ << "else :" << std::endl;
    {
      auto_indent indent(out_);
      this->print_name(node);
      out_ << " <= ";
      this->print_name(node->get_src(i).get_impl());
      out_ << std::endl;
    }
  }
}

void firrtlwriter::print_reg(regimpl* node) {
  assert(node->has_reset());
  assert(!node->has_enable());
  this->print_name(node);
  out_ << " <= ";
  out_ << " mux(";
  this->print_name(node->get_reset().get_impl());
  out_ << ", ";
  this->print_name(node->get_init().get_impl());
  out_ << ", ";
  this->print_name(node->get_next().get_impl());
  out_ << ")" << std::endl;
}

void firrtlwriter::print_cdomain(cdomain* cd) {
  assert(1 == cd->get_sensitivity_list().size());
  auto& e = cd->get_sensitivity_list()[0];
  assert(EDGE_POS == e.get_edgedir());
  this->print_name(e.get_signal().get_impl());
}

void firrtlwriter::print_mem(memimpl* node) {
  auto print_attributes = [&](memportimpl* port) {
    char type;
    if (port->has_wdata()) {
      if (port->is_read_enable()) {
        type = 'x';
        this->print_name(node);
        out_ << '.' << type << port->get_index() << ".wmode <= UInt<1>(\"h1\")";
        out_ << std::endl;
      } else {
        type = 'w';
      }

      this->print_name(node);
      out_ << '.' << type << port->get_index() << ".data <= ";
      this->print_name(port->get_wdata().get_impl());
      out_ << std::endl;

      this->print_name(node);
      out_ << '.' << type << port->get_index() << ".mask <= ";
      std::string mask(port->get_wdata().get_size(), '1');
      this->print_value(bitvector(port->get_wdata().get_size(), mask + "b"));
      out_ << std::endl;

      this->print_name(node);
      out_ << '.' << type << port->get_index() << ".en <= ";
      if (port->has_enable()) {
        this->print_name(port->get_enable().get_impl());
      } else {
        out_ << "UInt<1>(\"h1\")";
      }
      out_ << std::endl;
    } else {
      type = 'r';
      this->print_name(node);
      out_ << '.' << type << port->get_index() << ".en <= UInt<1>(\"h1\")";
      out_ << std::endl;
    }

    this->print_name(node);
    out_ << '.' << type << port->get_index() << ".addr <= ";
    this->print_name(port->get_addr().get_impl());
    out_ << std::endl;

    this->print_name(node);
    out_ << '.' << type << port->get_index() << ".clk <= ";
    this->print_cdomain(node->get_cd());
    out_ << std::endl;
  };

  if (node->is_write_enable()) {
    // initialization data not supported!
    assert(!node->has_initdata());
    for (auto& port : node->get_ports()) {
      auto p = dynamic_cast<memportimpl*>(port.get_impl());
      print_attributes(p);
    }
  } else {
    assert(node->has_initdata());
    auto data_width = node->get_data_width();
    auto data_cbsize = CH_CEILDIV(data_width, 8);
    bitvector value(data_width);
    for (unsigned i = 0, n = node->get_num_items(); i < n; ++i) {
      this->print_name(node);
      out_ << "[" << i << "] <= ";
      node->get_value().read(0, value.get_words(), data_cbsize, i * data_width, data_width);
      this->print_value(value);
      out_ << std::endl;
    }
  }
}

void firrtlwriter::print_operator(ch_alu_op op) {
  switch (op) {
  case alu_inv:   out_ << "not"; break;
  case alu_and:   out_ << "and"; break;
  case alu_or:    out_ << "or"; break;
  case alu_xor:   out_ << "xor"; break;
  case alu_andr:  out_ << "andr"; break;
  case alu_orr:   out_ << "orr"; break;
  case alu_xorr:  out_ << "xorr"; break;

  case alu_neg:   out_ << "neg"; break;
  case alu_add:   out_ << "add"; break;
  case alu_sub:   out_ << "sub"; break;
  case alu_mult:  out_ << "mul"; break;
  case alu_div:   out_ << "div"; break;
  case alu_mod:   out_ << "mod"; break;

  case alu_sll:   out_ << "dshl"; break;
  case alu_srl:   out_ << "dshr"; break;
  case alu_sra:   out_ << "dshr"; break;

  case alu_eq:    out_ << "eq"; break;
  case alu_ne:    out_ << "neq"; break;
  case alu_lt:    out_ << "lt"; break;
  case alu_gt:    out_ << "gt"; break;
  case alu_le:    out_ << "leq"; break;
  case alu_ge:    out_ << "geq"; break;
  default:
    assert(false);
  }
}

void firrtlwriter::print_name(lnodeimpl* node, bool force) {
  auto print_unique_name = [&](lnodeimpl* node) {
    out_ << node->get_name() << node->get_id();
  };

  auto type = node->get_type();
  switch (type) {
  case type_input:
  case type_output:
    out_ << node->get_name();
    break;
  case type_proxy:
    print_unique_name(node);
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
    auto port = dynamic_cast<memportimpl*>(node);
    auto mem = dynamic_cast<memimpl*>(port->get_mem().get_impl());
    this->print_name(mem);
    if (mem->is_write_enable()) {
      if (port->is_read_enable()
       && !port->has_wdata()) {
        // read-only
        out_ << ".r" << port->get_index() << ".data";
      } else
      if (!port->is_read_enable()
       && port->has_wdata()) {
        // write-only
        out_ << ".w" << port->get_index() << ".data";
      } else {
        assert(port->is_read_enable());
        assert(port->has_wdata());
        // read-write
        out_ << ".x" << port->get_index() << ".rdata";
      }
    } else {
      out_ << "[";
      print_unique_name(port->get_addr().get_impl());
      out_ << "]";
    }
  } break;
  default:
    assert(false);
  }
}

void firrtlwriter::print_type(lnodeimpl* node) {
  auto type = node->get_type();
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
  auto type = node->get_type();
  switch (type) {
  case type_input:
    if ("clk" == dynamic_cast<inputimpl*>(node)->get_name()) {
      out_ << "Clock";
    } else {
      out_ << "UInt<" << node->get_size() << ">";
    }
    break;
  case type_reg:
    out_ << "UInt<" << node->get_size() << ">, ";
    this->print_cdomain(dynamic_cast<regimpl*>(node)->get_cd());
    break;
  case type_mem: {    
    auto mem = dynamic_cast<memimpl*>(node);
    if (mem->is_write_enable()) {
      auto_indent indent(out_);
      out_ << std::endl;
      out_ << "data-type => UInt<" << mem->get_data_width() << ">" << std::endl;
      out_ << "depth => " << mem->get_num_items() << std::endl;
      out_ << "read-latency => 0" << std::endl;
      out_ << "write-latency => 1" << std::endl;
      out_ << "read-under-write => undefined" << std::endl;

      auto_separator sep("\n");
      for (auto& port : mem->get_ports()) {
        out_ << sep;
        auto p = dynamic_cast<memportimpl*>(port.get_impl());
        if (p->is_read_enable()
        && !p->has_wdata()) {
          // read-only
          out_ << "reader => r" << p->get_index();
        } else
        if (!p->is_read_enable()
         && p->has_wdata()) {
          // write-only
          out_ << "writer => w" << p->get_index();
        } else {
          assert(p->is_read_enable() && p->has_wdata());
          // read-write
          out_ << "readwriter => x" << p->get_index();
        }
      }
    } else {
      out_ << "UInt<" << mem->get_data_width() << ">"
           << "[" << mem->get_num_items() << "]";
    }
  } break;
  case type_bindport: {
    auto b = dynamic_cast<bindportimpl*>(node);
    auto p = dynamic_cast<ioimpl*>(b->get_ioport().get_impl());
    if (type_input == p->get_type()
     && "clk" == dynamic_cast<inputimpl*>(p)->get_name()) {
      out_ << "Clock";
    } else {
      out_ << "UInt<" << node->get_size() << ">";
    }
  } break;
  default:
    out_ << "UInt<" << node->get_size() << ">";
    break;
  }
}

void firrtlwriter::print_value(const bitvector& value,
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
