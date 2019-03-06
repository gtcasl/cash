#include "firrtlwriter.h"
#include "codegen.h"
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

using namespace ch::internal;

const auto is_inline_literal = [](lnodeimpl* node) {
  assert(type_lit == node->type());
  return (node->size() <= 32);
};

firrtlwriter::firrtlwriter(context* ctx)
  : ctx_(ctx)
  , num_temps_(0) {
  for (lnodeimpl* node : ctx->nodes()) {
    for (auto& src : node->srcs()) {
      uses_[src.id()].insert(node);
    }
  }
}

firrtlwriter::~firrtlwriter() {}

void firrtlwriter::print(std::ostream& out,
                         std::unordered_set<std::string_view>& visited) {
  // print dependent modules
  for (auto node : ctx_->bindings()) {
    auto binding = reinterpret_cast<bindimpl*>(node);
    // ensure single instantiation
    if (visited.count(ctx_->name()))
      continue;
    visited.insert(ctx_->name());
    firrtlwriter child_module(binding->module());
    child_module.print(out, visited);
    out << std::endl;
  }

  out << "module " << ctx_->name() << ':' << std::endl;
  {
    auto_indent indent(out);

    // print header
    this->print_header(out);

    // print body
    this->print_body(out);

    // print footer
    this->print_footer(out);
  }
}

void firrtlwriter::print_header(std::ostream& out) {
  //
  // ports declaration
  //
  for (auto node : ctx_->inputs()) {
    auto input = reinterpret_cast<inputimpl*>(node);
    this->print_port(out, input);
    out << std::endl;
  }
  for (auto node : ctx_->outputs()) {
    auto output = reinterpret_cast<outputimpl*>(node);
    this->print_port(out, output);
    out << std::endl;
  }
  out << std::endl;
}

void firrtlwriter::print_body(std::ostream& out) {
  //
  // declaration
  //
  {
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
    int written = 0;
    for (auto node : ctx_->nodes()) {
      written |= this->print_logic(out, node);
    }
    if (written) {
      out << std::endl;
    }
  }
}

void firrtlwriter::print_footer(std::ostream& out) {
  //
  // output assignment
  //
  int written = 0;
  for (auto output : ctx_->outputs()) {
    this->print_name(out, output);
    out << " <= ";
    this->print_name(out, reinterpret_cast<outputimpl*>(output)->src(0).impl());
    out << std::endl;
    written = 1;
  }
  if (written) {
    out << std::endl;
  }
}

bool firrtlwriter::print_binding(std::ostream& out, bindimpl* node) {
  auto module = node->module();
  out << "inst ";
  this->print_name(out, node);
  out << " of ";
  out << module->name() << std::endl;
  for (auto& input : node->inputs()) {
    auto b = reinterpret_cast<bindportimpl*>(input.impl());
    auto p = reinterpret_cast<ioimpl*>(b->ioport().impl());
    this->print_name(out, node);
    out << "." << p->name() << " <= ";
    this->print_name(out, b);
    out << std::endl;
  }
  for (auto& output : node->outputs()) {
    auto b = reinterpret_cast<bindportimpl*>(output.impl());
    auto p = reinterpret_cast<ioimpl*>(b->ioport().impl());
    this->print_name(out, b);
    out << " <= ";
    this->print_name(out, node);
    out << "." << p->name() << std::endl;
  }
  return true;
}

bool firrtlwriter::print_bindport(std::ostream& out, bindportimpl* node) {
  // outputs are sourced via binding already
  if (node->type() == type_bindout)
    return false;
  this->print_name(out, node);
  out << " <= ";
  this->print_name(out, node->src(0).impl());
  out << std::endl;
  return true;
}

void firrtlwriter::print_port(std::ostream& out, ioimpl* node) {
  //--
  this->print_type(out, node);
  out << " ";
  this->print_name(out, node);
  out << " : ";
  this->print_dtype(out, node);
}

bool firrtlwriter::print_decl(std::ostream& out,
                              lnodeimpl* node,
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
  case type_bindin:
  case type_bindout:
  case type_alu:
  case type_sel:
  case type_reg:
  case type_mem: {
    this->print_type(out, node);
    out << " ";
    this->print_name(out, node);
    out << " : ";
    this->print_dtype(out, node);
    auto& sloc = node->sloc();
    if (!sloc.empty()) {
      out << " @[" << sloc << "]";
    }
    out << std::endl;
    return true;
  }
  case type_bind:
  case type_input:
  case type_output:
  case type_cd:
  case type_marport:
  case type_msrport:
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

bool firrtlwriter::print_logic(std::ostream& out, lnodeimpl* node) {
  auto type = node->type();
  switch (type) {
  case type_lit:
    return this->print_lit(out, reinterpret_cast<litimpl*>(node));
  case type_proxy:
    return this->print_proxy(out, reinterpret_cast<proxyimpl*>(node));
  case type_alu:
    return this->print_alu(out, reinterpret_cast<aluimpl*>(node));
  case type_sel:
    return this->print_select(out, reinterpret_cast<selectimpl*>(node));
  case type_reg:
    return this->print_reg(out, reinterpret_cast<regimpl*>(node));
  case type_mem:
    return this->print_mem(out, reinterpret_cast<memimpl*>(node));
  case type_bind:
    return this->print_binding(out, reinterpret_cast<bindimpl*>(node));
  case type_bindin:
  case type_bindout:
    return this->print_bindport(out, reinterpret_cast<bindportimpl*>(node));
  default:
    assert(false);
  case type_input:
  case type_output:
  case type_cd:
  case type_marport:
  case type_msrport:
  case type_mwport:
  case type_tap:
  case type_assert:
  case type_print:
  case type_time:
    return false;
  }
}

bool firrtlwriter::print_lit(std::ostream& out, litimpl* node) {
  if (is_inline_literal(node))
    return false;
  this->print_name(out, node);
  out << " <= ";
  this->print_value(out, node->value(), true);
  out << std::endl;
  return true;
}

bool firrtlwriter::print_proxy(std::ostream& out, proxyimpl* node) {
  //--
  const auto& ranges = node->ranges();  
  std::unordered_map<proxyimpl::range_t, uint32_t, proxyimpl::range_t::hash_t> tmps;

  //--
  auto alloc_tmp = [&](const proxyimpl::range_t& range)->uint32_t {
    auto t = num_temps_++;
    tmps[range] = t;
    return t;
  };

  //--
  auto print_range = [&](const proxyimpl::range_t& range) {
    auto& src = node->src(range.src_idx);
    if (range.length == src.size()) {
      this->print_name(out, src.impl());
    } else {
      out << "_t" << tmps[range];
    }
  };

  //--  
  for (auto& range : ranges) {
    auto& src = node->src(range.src_idx);
    if (range.length != src.size()) {
      out << "node _t" << alloc_tmp(range) << " = bits(";
      this->print_name(out, src.impl());
      out << ", " << (range.src_offset + range.length - 1);
      out << ", " << range.src_offset << ")";
      out << std::endl;
    }
  }

  //--  
  if (ranges.size() > 1) {
    uint32_t prev_dst(0);
    for (uint32_t i = 1, n = ranges.size(); i < n; ++i) {
      uint32_t t = 0;
      if (i+1 == n) {
        this->print_name(out, node);
        out << " <= ";
      } else {
        t = num_temps_++;
        out << "node _t" << t << " = ";
      }

      out << "cat(";
      print_range(ranges[i]);
      out << ", ";
      if (1 == i) {
        print_range(ranges[0]);
      } else {
        out << "_t" << prev_dst;
      }
      out << ")" << std::endl;
      prev_dst = t;
    }
  } else {
    this->print_name(out, node);
    out << " <= ";
    print_range(ranges[0]);
    out << std::endl;
  }  
  return true;
}

bool firrtlwriter::print_alu(std::ostream& out, aluimpl* node) {
  //--
  auto op = node->op();

  //--
  auto print_default = [&]() {
    this->print_name(out, node);
    out << " <= ";
    if (CH_OP_ARY(op) == op_flags::binary) {
      this->print_operator(out, op);
      out << "(";
      this->print_name(out, node->src(0).impl());
      out << ", ";
      this->print_name(out, node->src(1).impl());
      out << ")" << std::endl;
    } else {
      assert(CH_OP_ARY(op) == op_flags::unary);
      this->print_operator(out, op);
      out << "(";
      this->print_name(out, node->src(0).impl());
      out << ")" << std::endl;
    }
  };

  //--
  switch (op) {
  case ch_op::notl: {
    auto src0 = node->src(0).impl();
    if (src0->size() > 1) {
      auto t1 = num_temps_++;
      auto t2 = num_temps_++;
      out << "node _t" << t1 << " = orr(";
      this->print_name(out, src0);
      out << ")" << std::endl;
      out << "node _t" << t2 << " = not(_t" << t1 << ")" << std::endl;
      this->print_name(out, node);
      out << " <= asUInt(_t" << t2 << ")" << std::endl;
    } else {
      print_default();
    }
  } break;
  case ch_op::andl: {
    auto src0 = node->src(0).impl();
    auto src1 = node->src(1).impl();
    if (src0->size() > 1
     || src1->size() > 1) {
      auto t1 = num_temps_++;
      auto t2 = num_temps_++;
      out << "node _t" << t1 << " = orr(";
      this->print_name(out, src0);
      out << ")" << std::endl;
      out << "node _t" << t2 << " = orr(";
      this->print_name(out, src1);
      out << ")" << std::endl;
      this->print_name(out, node);
      out << " <= and(_t" << t1 << ", _t" << t2 << ")" << std::endl;
    } else {
      print_default();
    }
  } break;
  case ch_op::orl: {
    auto src0 = node->src(0).impl();
    auto src1 = node->src(1).impl();
    if (src0->size() > 1
     || src1->size() > 1) {
      auto t1 = num_temps_++;
      auto t2 = num_temps_++;
      out << "node _t" << t1 << " = orr(";
      this->print_name(out, src0);
      out << ")" << std::endl;
      out << "node _t" << t2 << " = orr(";
      this->print_name(out, src1);
      out << ")" << std::endl;
      this->print_name(out, node);
      out << " <= or(_t" << t1 << ", _t" << t2 << ")" << std::endl;
    } else {
      print_default();
    }
  } break;
  case ch_op::neg: {
    auto t = num_temps_++;
    out << "node _t" << t << " = neg(";
    this->print_name(out, node->src(0).impl());
    out << ")" << std::endl;
    this->print_name(out, node);
    out << " <= asUInt(_t" << t << ")" << std::endl;
  } break;
  case ch_op::shr: {
    if (node->is_signed()) {
      auto t = num_temps_++;
      out << "node _t" << t << " = asSInt(";
      this->print_name(out, node->src(0).impl());
      out << ")" << std::endl;
      this->print_name(out, node);
      out << " <= dshr(_t" << t << ", ";
      this->print_name(out, node->src(1).impl());
      out << ")" << std::endl;
    } else {
     print_default();
    }
  } break;
  case ch_op::sub: {
    auto t = num_temps_++;
    out << "node _t" << t << " = sub(";
    this->print_name(out, node->src(0).impl());
    out << ", ";
    this->print_name(out, node->src(1).impl());
    out << ")" << std::endl;
    this->print_name(out, node);
    out << " <= asUInt(_t" << t << ")" << std::endl;
  } break;
  case ch_op::pad: {
    if (node->is_signed()) {
      auto t1 = num_temps_++;
      auto t2 = num_temps_++;
      out << "node _t" << t1 << " = asSInt(";
      this->print_name(out, node->src(0).impl());
      out << ")" << std::endl;
      out << "node _t" << t2 << " = pad<" << node->size() << ">(";
      out << "_t" << t1 << ")" << std::endl;
      this->print_name(out, node);
      out << " <= asUInt(_t" << t2 << ")" << std::endl;
    } else {
      this->print_name(out, node);
      out << " <= pad<" << node->size() << ">(";
      this->print_name(out, node->src(0).impl());
      out << ")" << std::endl;
    }
  } break;
  default:
   print_default();
   break;
  }
  return true;
}

bool firrtlwriter::print_select(std::ostream& out, selectimpl* node) {
  bool has_key = node->has_key();
  if (!has_key && node->is_ternary()) {
    this->print_name(out, node);
    out << " <= mux(";
    this->print_name(out, node->src(0).impl());
    out << ", ";
    this->print_name(out, node->src(1).impl());
    out << ", ";
    this->print_name(out, node->src(2).impl());
    out << ")" << std::endl;
  } else {
    std::unordered_map<uint32_t, uint32_t> tmps;
    uint32_t i = has_key ? 1 : 0;
    uint32_t last = node->num_srcs() - 1;
    if (has_key) {
      for (uint32_t j = i; j < last; j += 2) {
        auto t = num_temps_++;
        tmps[node->src(j).id()] = t;
        out << "node _t" << t << " = eq(";
        this->print_name(out, node->src(0).impl());
        out << ", ";
        this->print_name(out, node->src(j).impl());
        out << ")" << std::endl;
      }
    }

    auto_separator sep("else ");
    for (; i < last; i += 2) {
      out << sep << "when ";
      if (has_key) {
        out << "_t" << tmps[node->src(i).id()];
      } else {
        this->print_name(out, node->src(i).impl());
      }
      out << " :" << std::endl;
      {
        auto_indent indent(out);
        this->print_name(out, node);
        out << " <= ";
        this->print_name(out, node->src(i + 1).impl());
        out << std::endl;
      }
    }
    out << "else :" << std::endl;
    {
      auto_indent indent(out);
      this->print_name(out, node);
      out << " <= ";
      this->print_name(out, node->src(i).impl());
      out << std::endl;
    }
  }
  return true;
}

bool firrtlwriter::print_reg(std::ostream& out, regimpl* node) {
  this->print_name(out, node);
  out << " <= ";
  if (node->has_init_data()) {
    out << " mux(";
    this->print_name(out, node->reset().impl());
    out << ", ";
    this->print_name(out, node->init_data().impl());
    out << ", ";
    this->print_name(out, node->next().impl());
    out << ")";
  } else {
    this->print_name(out, node->next().impl());
  }
  out << std::endl;
  return true;
}

bool firrtlwriter::print_cdomain(std::ostream& out, cdimpl* cd) {
  assert(cd->pos_edge());
  this->print_name(out, cd->clk().impl());
  return true;
}

bool firrtlwriter::print_mem(std::ostream& out, memimpl* node) {
  auto print_attributes = [&](memportimpl* port, uint32_t port_index) {
    char type;
    if (port->type() == type_mwport) {
      auto mwport = reinterpret_cast<mwportimpl*>(port);
      if (node->is_readwrite(mwport)) {
        type = 'x';
        this->print_name(out, node);
        out << '.' << type << port_index << ".wmode <= UInt<1>(\"h1\")";
        out << std::endl;
      } else {
        type = 'w';
      }

      this->print_name(out, node);
      out << '.' << type << port_index << ".data <= ";
      this->print_name(out, mwport->wdata().impl());
      out << std::endl;

      this->print_name(out, node);
      out << '.' << type << port_index << ".mask <= ";
      std::string mask(mwport->wdata().size(), '1');
      this->print_value(out, sdata_type(mwport->wdata().size(), mask + "b"));
      out << std::endl;

      this->print_name(out, node);
      out << '.' << type << port_index << ".en <= ";
      if (mwport->has_enable()) {
        this->print_name(out, mwport->enable().impl());
      } else {
        out << "UInt<1>(\"h1\")";
      }
      out << std::endl;
    } else {
      if (node->is_readwrite(port))
        return;
      type = 'r';
      this->print_name(out, node);
      out << '.' << type << port_index << ".en <= UInt<1>(\"h1\")";
      out << std::endl;
    }

    this->print_name(out, node);
    out << '.' << type << port_index << ".addr <= ";
    this->print_name(out, port->addr().impl());
    out << std::endl;

    if (port->has_cd()) {
      this->print_name(out, node);
      out << '.' << type << port_index << ".clk <= ";
      this->print_cdomain(out, reinterpret_cast<cdimpl*>(port->cd().impl()));
    }
    out << std::endl;
  };

  if (node->is_logic_rom()) {
    assert(node->has_init_data());
    auto data_width = node->data_width();
    sdata_type value(data_width);
    for (uint32_t i = 0, n = node->num_items(); i < n; ++i) {
      this->print_name(out, node);
      out << "[" << i << "] <= ";
      value.copy(0, node->init_data(), i * data_width, data_width);
      this->print_value(out, value);
      out << std::endl;
    }
  } else {
    CH_CHECK(!node->has_init_data(), "initialization data not supported!");
    for (uint32_t i = 0, n = node->rdports().size(); i < n; ++i) {
      print_attributes(node->rdport(i), i);
    }
    for (uint32_t i = 0, n = node->wrports().size(); i < n; ++i) {
      print_attributes(node->wrport(i), i);
    }
  }
  return true;
}

void firrtlwriter::print_operator(std::ostream& out, ch_op op) {
  switch (op) {
  case ch_op::eq:    out << "eq"; break;
  case ch_op::ne:    out << "neq"; break;

  case ch_op::lt:    out << "lt"; break;
  case ch_op::gt:    out << "gt"; break;
  case ch_op::le:    out << "leq"; break;
  case ch_op::ge:    out << "geq"; break;

  case ch_op::notl:  out << "not"; break;
  case ch_op::andl:  out << "and"; break;
  case ch_op::orl:   out << "or"; break;

  case ch_op::inv:   out << "not"; break;
  case ch_op::andb:  out << "and"; break;
  case ch_op::orb:   out << "or"; break;
  case ch_op::xorb:  out << "xor"; break;

  case ch_op::andr:  out << "andr"; break;
  case ch_op::orr:   out << "orr"; break;
  case ch_op::xorr:  out << "xorr"; break;

  case ch_op::shl:   out << "dshl"; break;
  case ch_op::shr:   out << "dshr"; break;

  case ch_op::neg:   out << "neg"; break;
  case ch_op::add:   out << "add"; break;
  case ch_op::sub:   out << "sub"; break;
  case ch_op::mul:   out << "mul"; break;
  case ch_op::div:   out << "div"; break;
  case ch_op::mod:   out << "mod"; break;

  default:
    assert(false);
  }
}

void firrtlwriter::print_name(std::ostream& out, lnodeimpl* node, bool force) {
  //--
  auto print_unique_name = [&](lnodeimpl* node) {
    out << node->type() << node->id();
    if (!node->name().empty()) {
      out << "_" << node->name();
    }
  };

  auto type = node->type();
  switch (type) {
  case type_input:
  case type_output:
    out << node->name();
    break;
  case type_proxy:
    print_unique_name(node);
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
    print_unique_name(node);
    break;
  case type_marport:
  case type_msrport:
  case type_mwport: {
    auto port = reinterpret_cast<memportimpl*>(node);
    auto mem = port->mem();
    this->print_name(out, mem);
    if (mem->is_logic_rom()) {
      out << "[";
      print_unique_name(port->addr().impl());
      out << "]";
    } else {
      auto port_index = mem->port_index(port);
      if (mem->is_readwrite(port)) {
        // read-write
        out << ".x" << port_index << ".rdata";
      } else
      if (port->type() == type_mwport) {
        // write-only
        out << ".w" << port_index << ".data";
      } else {
        // read-only
        out << ".r" << port_index << ".data";
      }
    }
  } break;
  case type_bind: {
    auto bind = reinterpret_cast<bindimpl*>(node);
    out << bind->module()->name() << "_" << bind->id();
  } break;
  case type_bindin:
  case type_bindout: {
    auto bindport = reinterpret_cast<bindportimpl*>(node);
    print_name(out, bindport->binding());
    out << "_" << bindport->ioport().name();
  } break;
  default:
    assert(false);
  }
}

void firrtlwriter::print_type(std::ostream& out, lnodeimpl* node) {
  auto type = node->type();
  switch (type) {
  case type_input:
    out << "input";
    break;
  case type_output:
    out << "output";
    break;
  case type_lit:
  case type_proxy:
  case type_sel:
  case type_alu:
  case type_bindin:
  case type_bindout:
  case type_marport:
  case type_msrport:
  case type_mwport:
    out << "wire";
    break;
  case type_reg:
    out << "reg";
    break;
  case type_mem: {
    auto mem = reinterpret_cast<memimpl*>(node);
    out << (mem->is_logic_rom() ? "wire" : "mem");
  } break;
  default:
    assert(false);
  }
}

void firrtlwriter::print_dtype(std::ostream& out, lnodeimpl* node) {
  auto type = node->type();
  switch (type) {
  case type_input:
    if ("clk" == reinterpret_cast<inputimpl*>(node)->name()) {
      out << "Clock";
    } else {
      out << "UInt<" << node->size() << ">";
    }
    break;
  case type_reg: {
    out << "UInt<" << node->size() << ">, ";
    auto reg = reinterpret_cast<regimpl*>(node);
    auto cd = reinterpret_cast<cdimpl*>(reg->cd().impl());
    this->print_cdomain(out, cd);
  } break;
  case type_mem: {    
    auto mem = reinterpret_cast<memimpl*>(node);
    if (mem->is_logic_rom()) {
      out << "UInt<" << mem->data_width() << ">"
           << "[" << mem->num_items() << "]";
    } else {
      auto_indent indent(out);
      out << std::endl;
      out << "data-type => UInt<" << mem->data_width() << ">" << std::endl;
      out << "depth => " << mem->num_items() << std::endl;
      out << "read-latency => 0" << std::endl;
      out << "write-latency => 1" << std::endl;
      out << "read-under-write => undefined" << std::endl;

      auto_separator sep("\n");
      for (uint32_t i = 0, n = mem->rdports().size(); i < n; ++i) {
        if (mem->is_readwrite(mem->rdport(i)))
          continue;
        out << sep;        
        // read-only
        out << "reader => r" << i;
      }
      for (uint32_t i = 0, n = mem->wrports().size(); i < n; ++i) {
        out << sep;
        if (mem->is_readwrite(mem->wrport(i))) {
          // read-write
          out << "readwriter => x" << i;
        } else {
          // write-only
          out << "writer => w" << i;
        }
      }
    }
  } break;
  case type_bindin:
  case type_bindout: {
    auto b = reinterpret_cast<bindportimpl*>(node);
    auto p = reinterpret_cast<ioimpl*>(b->ioport().impl());
    if (p->type() == type_input
     && "clk" == reinterpret_cast<inputimpl*>(p)->name()) {
      out << "Clock";
    } else {
      out << "UInt<" << node->size() << ">";
    }
  } break;
  default:
    out << "UInt<" << node->size() << ">";
    break;
  }
}

void firrtlwriter::print_value(std::ostream& out,
                               const sdata_type& value,
                               bool skip_zeros,
                               uint32_t offset,
                               uint32_t size) {
  if (0 == size) {
    size = value.size();
  }

  out << "UInt<" << size << ">(\"h";
  auto oldflags = out.flags();
  out.setf(std::ios_base::hex, std::ios_base::basefield);

  uint32_t word = 0;
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
  out << "\")";
}

///////////////////////////////////////////////////////////////////////////////

void ch::internal::ch_toFIRRTL(std::ostream& out, const device& device) {
  std::unordered_set<std::string_view> visited;
  auto ctx = device.impl()->ctx();
  visited.insert(ctx->name());
  out << "circuit " << ctx->name() << ":" << std::endl;
  firrtlwriter writer(ctx);  
  writer.print(out, visited);
}

void ch_toFIRRTL(std::ostream& out, const ch_device_list& devices) {
  std::unordered_set<std::string_view> visited;

  for (auto& device : devices) {
    auto ctx = device.impl()->ctx();
    if (visited.count(ctx->name()))
      continue;
    out << "circuit " << ctx->name() << ":" << std::endl;
    firrtlwriter writer(ctx);
    writer.print(out, visited);
  }
}
