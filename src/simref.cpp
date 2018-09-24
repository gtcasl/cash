#include "simref.h"
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
#include "printimpl.h"
#include "timeimpl.h"
#include "udfimpl.h"

using namespace ch::internal;

using instr_map_t = std::unordered_map<uint32_t, const bitvector*>;

struct instr_proxy : instr_base {

  struct range_t {
    const bitvector* src_data;
    uint32_t src_offset;
    uint32_t dst_offset;
    uint32_t length;
  };

  std::vector<range_t> ranges;
  bitvector dst;

  instr_proxy(proxyimpl* node, instr_map_t& map)
    : dst(node->size()) {
    ranges.reserve(node->ranges().size());
    for (auto& range : node->ranges()) {
      range_t new_range = {
        map.at(node->src(range.src_idx).id()),
        range.src_offset,
        range.dst_offset,
        range.length
      };
      ranges.emplace_back(new_range);
    }
    map[node->id()] = &dst;
  }

  void eval() override {
    for (auto& range : ranges) {
      dst.copy(range.dst_offset, *range.src_data, range.src_offset, range.length);
    }
  }
};


///////////////////////////////////////////////////////////////////////////////

struct instr_output : instr_base {
  const bitvector* src;
  bitvector* dst;

  instr_output(outputimpl* node, instr_map_t& map)
    : src(map.at(node->src(0).id()))
    , dst(&node->value())
  {}

  void eval() override {
    *dst = *src;
  }
};

///////////////////////////////////////////////////////////////////////////////

struct instr_alu_base : instr_base {
  bool is_signed;
  bool need_resizing;
  const bitvector* o_src0;
  const bitvector* o_src1;
  const bitvector* src0;
  const bitvector* src1;
  bitvector t_src0;
  bitvector t_src1;
  bitvector dst;

  instr_alu_base(aluimpl* node, instr_map_t& map)
    : is_signed(node->is_signed())
    , need_resizing(false)
    , o_src0(nullptr)
    , o_src1(nullptr)
    , src0(nullptr)
    , src1(nullptr)
    , dst(node->size()){
    // access source node data
    if (node->srcs().size() > 0) {
      o_src0 = map.at(node->src(0).id());
      if (node->srcs().size() > 1) {
        o_src1 = map.at(node->src(1).id());
      }
    }
    src0 = o_src0;
    src1 = o_src1;

    // allocate shadow buffers if needed
    auto op = node->op();
    auto op_prop = CH_OP_PROP(op);
    if (op_prop & op_flags::eq_opd_size) {
      auto op_class = CH_OP_CLASS(op);
      if (op_flags::equality == op_class
       || op_flags::relational == op_class) {
        // resize source operands to match each other
        if (src0->size() != src1->size()) {
          if (src0->size() < src1->size()) {
            t_src0.resize(src1->size());
            src0 = &t_src0;
          } else {
            t_src1.resize(src0->size());
            src1 = &t_src1;
          }
          need_resizing = true;
        }
      } else {
        // resize source operands to match destination
        if (src0->size() != node->size()) {
          t_src0.resize(node->size());
          src0 = &t_src0;
          need_resizing = true;
        }
        if (src1 && src1->size() != node->size()) {
          t_src1.resize(node->size());
          src1 = &t_src1;
          need_resizing = true;
        }
      }
    }

    map[node->id()] = &dst;
  }

  void update_shadow_buffers() {
    if (src0 == &t_src0) {
      if (t_src0.size() > o_src0->size()) {
        if (is_signed) {
          bv_sext(t_src0, *o_src0);
        } else {
          bv_zext(t_src0, *o_src0);
        }
      } else {
        t_src0.copy(0, *o_src0, 0, t_src0.size());
      }
    }
    if (src1 == &t_src1) {
      if (t_src1.size() > o_src1->size()) {
        if (is_signed) {
          bv_sext(t_src1, *o_src1);
        } else {
          bv_zext(t_src1, *o_src1);
        }
      } else {
        t_src1.copy(0, *o_src1, 0, t_src1.size());
      }
    }
  }
};

template <ch_op op>
struct instr_alu : instr_alu_base {
  instr_alu(aluimpl* node, instr_map_t& map) : instr_alu_base(node, map) {}

  void eval() override {
    if constexpr (CH_OP_PROP(op) & op_flags::eq_opd_size) {
      if (need_resizing) {
        this->update_shadow_buffers();
      }
    }
    switch (op) {
    case ch_op::eq:
      dst = bv_eq(*src0, *src1);
      break;
    case ch_op::ne:
      dst = !bv_eq(*src0, *src1);
      break;
    case ch_op::lt:
      dst = is_signed ? bv_lts(*src0, *src1) : bv_ltu(*src0, *src1);
      break;
    case ch_op::gt:
      dst = is_signed ? bv_lts(*src1, *src0) : bv_ltu(*src1, *src0);
      break;
    case ch_op::le:
      dst = !(is_signed ? bv_lts(*src1, *src0) : bv_ltu(*src1, *src0));
      break;
    case ch_op::ge:
      dst = !(is_signed ? bv_lts(*src0, *src1) : bv_ltu(*src0, *src1));
      break;

    case ch_op::notl:
      dst = !bv_orr(*src0);
      break;
    case ch_op::andl:
      dst = bv_orr(*src0) && bv_orr(*src1);
      break;
    case ch_op::orl:
      dst = bv_orr(*src0) || bv_orr(*src1);
      break;

    case ch_op::inv:
      bv_inv(dst, *src0);
      break;
    case ch_op::andb:
      bv_and(dst, *src0, *src1);
      break;
    case ch_op::orb:
      bv_or(dst, *src0, *src1);
      break;
    case ch_op::xorb:
      bv_xor(dst, *src0, *src1);
      break;

    case ch_op::andr:
      dst = bv_andr(*src0);
      break;
    case ch_op::orr:
      dst = bv_orr(*src0);
      break;
    case ch_op::xorr:
      dst = bv_xorr(*src0);
      break;

    case ch_op::shl:
      bv_sll(dst, *src0, *src1);
      break;
    case ch_op::shr:
      if (is_signed) {
        bv_sra(dst, *src0, *src1);
      } else {
        bv_srl(dst, *src0, *src1);
      }
      break;

    case ch_op::add:
      bv_add(dst, *src0, *src1);
      break;
    case ch_op::sub:
      bv_sub(dst, *src0, *src1);
      break;
    case ch_op::neg:
      bv_neg(dst, *src0);
      break;
    case ch_op::mul:
      bv_mul(dst, *src0, *src1);
      break;
    case ch_op::div:
      if (is_signed) {
        bv_divs(dst, *src0, *src1);
      } else {
        bv_divu(dst, *src0, *src1);
      }
      break;
    case ch_op::mod:
      if (is_signed) {
        bv_mods(dst, *src0, *src1);
      } else {
        bv_modu(dst, *src0, *src1);
      }
      break;

    case ch_op::pad:
      if (is_signed) {
        bv_sext(dst, *src0);
      } else {
        bv_zext(dst, *src0);
      }
      break;

    default:
      CH_ABORT("invalid opcode");
    }
  }
};

static instr_alu_base* create_alu_instr(aluimpl* node, instr_map_t& map) {
#define CREATE_ALU_INST(op) case op: return new instr_alu<op>(node, map)
  switch (node->op()) {
  CREATE_ALU_INST(ch_op::eq);
  CREATE_ALU_INST(ch_op::ne);
  CREATE_ALU_INST(ch_op::lt);
  CREATE_ALU_INST(ch_op::gt);
  CREATE_ALU_INST(ch_op::le);
  CREATE_ALU_INST(ch_op::ge);
  CREATE_ALU_INST(ch_op::notl);
  CREATE_ALU_INST(ch_op::andl);
  CREATE_ALU_INST(ch_op::orl);
  CREATE_ALU_INST(ch_op::inv);
  CREATE_ALU_INST(ch_op::andb);
  CREATE_ALU_INST(ch_op::orb);
  CREATE_ALU_INST(ch_op::xorb);
  CREATE_ALU_INST(ch_op::andr);
  CREATE_ALU_INST(ch_op::orr);
  CREATE_ALU_INST(ch_op::xorr);
  CREATE_ALU_INST(ch_op::shl);
  CREATE_ALU_INST(ch_op::shr);
  CREATE_ALU_INST(ch_op::add);
  CREATE_ALU_INST(ch_op::sub);
  CREATE_ALU_INST(ch_op::neg);
  CREATE_ALU_INST(ch_op::mul);
  CREATE_ALU_INST(ch_op::div);
  CREATE_ALU_INST(ch_op::mod);
  CREATE_ALU_INST(ch_op::pad);
  default:
    CH_ABORT("invalid opcode");
  }
#undef CREATE_ALU_INST
}

///////////////////////////////////////////////////////////////////////////////

struct instr_select : instr_base {
  bool has_key;
  std::vector<const bitvector*> srcs;
  bitvector dst;

  instr_select(selectimpl* node, instr_map_t& map)
    : has_key(node->has_key())
    , dst(node->size()) {
    srcs.reserve(node->srcs().size());
    for (auto src : node->srcs()) {
      srcs.emplace_back(map.at(src.id()));
    }
    map[node->id()] = &dst;
  }

  void eval() override {
    uint32_t i, last(srcs.size() - 1);
    if (has_key) {
      auto key = srcs[0];
      for (i = 1; i < last; i += 2) {
        if (*key == *srcs[i])
          break;
      }
    } else {
      for (i = 0; i < last; i += 2) {
        if (static_cast<bool>(*srcs[i]))
          break;
      }
    }
    dst = (i < last) ? *srcs[i+1] : *srcs[last];
  }
};

///////////////////////////////////////////////////////////////////////////////

struct instr_cd : instr_base {
  const bitvector* clk;
  bool prev_val;
  bool pos_edge;
  bitvector dst;

  instr_cd(cdimpl* node, instr_map_t& map)
    : clk(map.at(node->clk().id()))
    , prev_val(false)
    , pos_edge(node->pos_edge())
    , dst(node->size()) {
    map[node->id()] = &dst;
  }

  void eval() override {
    auto value = static_cast<bool>(*clk);
    dst = (prev_val != value) && (0 == (value ^ pos_edge));
    prev_val = value;
  }
};

///////////////////////////////////////////////////////////////////////////////

struct instr_reg : instr_base {
  std::vector<bitvector> pipe;
  const bitvector* cd;
  const bitvector* next;
  const bitvector* enable;
  const bitvector* reset;
  const bitvector* initdata;
  bitvector dst;

  instr_reg(regimpl* node, instr_map_t& map)
    : pipe(node->length() - 1, bitvector(node->next().size()))
    , cd(nullptr)
    , next(nullptr)
    , enable(nullptr)
    , reset(nullptr)
    , initdata(nullptr)
    , dst(node->size()) {
    map[node->id()] = &dst;
  }

  void init(regimpl* node, instr_map_t& map) {
    cd = map.at(node->cd().id());
    next = map.at(node->next().id());
    enable = node->has_enable() ? map.at(node->enable().id()) : nullptr;
    reset = node->has_initdata() ? map.at(node->reset().id()) : nullptr;
    initdata = node->has_initdata() ? map.at(node->initdata().id()) : nullptr;
  }

  void eval() override {
    // check clock transition
    if (!static_cast<bool>(*cd))
      return;

    // check reset state
    if (reset && static_cast<bool>(*reset)) {
      dst = *initdata;
      for (auto& p : pipe) {
        p = dst;
      }
      return;
    }

    // check enable state
    if (enable && !static_cast<bool>(*enable))
      return;

    // advance pipeline
    bitvector* value = &dst;
    if (!pipe.empty()) {
      auto last = pipe.size() - 1;
      dst = pipe[last];
      for (int i = last; i > 0; --i) {
        pipe[i] = pipe[i-1];
      }
      value = &pipe[0];
    }
    // push next value
    *value = *next;
  }
};

///////////////////////////////////////////////////////////////////////////////

struct instr_mem : instr_base {

  struct rdport_t {
    bitvector data;
    const bitvector* addr;
    const bitvector* enable;

    rdport_t(unsigned size, const bitvector* addr, const bitvector* enable)
      : data(size)
      , addr(addr)
      , enable(enable)
    {}
  };

  struct wrport_t {
    const bitvector* data;
    const bitvector* addr;
    const bitvector* enable;

    wrport_t(const bitvector* data, const bitvector* addr, const bitvector* enable)
      : data(data)
      , addr(addr)
      , enable(enable)
    {}
  };

  std::vector<rdport_t> rdports;
  std::vector<wrport_t> wrports;
  bitvector dst;
  const bitvector* cd;
  uint32_t num_items;
  bool is_write_enable;

  instr_mem(memimpl* node, instr_map_t& map)
    : dst(node->size())
    , cd(nullptr)
    , is_write_enable(node->is_write_enable()) {
    if (node->is_sync_read()) {
      rdports.reserve(node->rdports().size());
      for (auto p : node->rdports()) {
        rdports.emplace_back(p->size(), nullptr, nullptr);
        map[p->id()] = &rdports.back().data;
      }
    }
    if (node->has_initdata()) {
      dst = node->initdata();
    }
    map[node->id()] = &dst;
  }

  void init(memimpl* node, instr_map_t& map) {
    cd = node->has_cd() ? map.at(node->cd().id()) : nullptr;    
    for (unsigned i = 0, n = rdports.size(); i < n; ++i) {
      auto p = node->rdports()[i];
      rdports[i].addr   = map.at(p->addr().id());
      rdports[i].enable = p->has_enable() ? map.at(p->enable().id()) : nullptr;
    }
    wrports.reserve(node->wrports().size());
    for (auto p : node->wrports()) {
      wrports.emplace_back(map.at(p->wdata().id()),
                           map.at(p->addr().id()),
                           p->has_enable() ? map.at(p->enable().id()) : nullptr);
    }
  }

  void eval() override {
    // check clock transition
    if (cd && static_cast<bool>(*cd)) {
      // evaluate synchronous read ports
      for (auto& p : rdports) {
        // check enable state
        if (p.enable && !static_cast<bool>(*p.enable))
          continue;
        // memory read
        auto addr = static_cast<uint32_t>(*p.addr);
        p.data.copy(0, dst, addr * p.data.size(), p.data.size());
      }

      // evaluate synchronous write ports
      for (auto& p : wrports) {
        // check enable state
        if (p.enable && !static_cast<bool>(*p.enable))
          continue;
        // memory write
        auto addr = static_cast<uint32_t>(*p.addr);
        dst.copy(addr * p.data->size(), *p.data, 0, p.data->size());
      }
    }
  }
};

///////////////////////////////////////////////////////////////////////////////

struct instr_mrport : instr_base {
  const bitvector* mem;
  const bitvector* addr;
  bitvector dst;

  instr_mrport(mrportimpl* node, instr_map_t& map)
    : mem(map.at(node->mem()->id()))
    , addr(map.at(node->addr().id()))
    , dst(node->size()) {
    map[node->id()] = &dst;
  }

  void eval() override {
    auto a = static_cast<uint32_t>(*addr);
    dst.copy(0, *mem, a * dst.size(), dst.size());
  }
};

///////////////////////////////////////////////////////////////////////////////

struct instr_tap : instr_base {
  const bitvector* src;
  bitvector* dst;

  instr_tap(tapimpl* node, instr_map_t& map)
    : src(map.at(node->src(0).id()))
    , dst(&node->value())
  {}

  void eval() override {
    *dst = *src;
  }
};

///////////////////////////////////////////////////////////////////////////////

struct instr_assert : instr_base {
  const bitvector* cond;
  const bitvector* pred;
  std::string message;
  source_location sloc;
  ch_tick tick;

  instr_assert(assertimpl* node, instr_map_t& map)
    : cond(map.at(node->condition().id()))
    , pred(node->is_predicated() ? map.at(node->predicate().id()) : nullptr)    
    , message(node->message())
    , sloc(node->sloc())
    , tick(0)
  {}

  void eval() override {
    if ((!pred || static_cast<bool>(*pred))
     && !static_cast<bool>(*cond)) {
      fprintf(stderr, "assertion failure at tick %ld, %s (%s:%d)\n", tick, message.c_str(), sloc.file(), sloc.line());
      std::abort();
    }
    ++tick;
  }
};

///////////////////////////////////////////////////////////////////////////////

struct instr_time : instr_base {
  ch_tick tick;
  bitvector dst;

  instr_time(timeimpl* node, instr_map_t& map)
    : tick(0)
    , dst(node->size()) {
    map[node->id()] = &dst;
  }

  void eval() override {
    dst = tick++;
  }
};

///////////////////////////////////////////////////////////////////////////////

struct instr_print : instr_base {
  std::vector<enum_string_cb> enum_strings;
  std::vector<const bitvector*> srcs;
  const bitvector* pred;
  std::string format;

  instr_print(printimpl* node, instr_map_t& map)
    : enum_strings(node->enum_strings())
    , pred(node->is_predicated() ? map.at(node->predicate().id()) : nullptr)
    , format(node->format()) {
    srcs.reserve(node->enum_strings().size());
    for (unsigned i = (pred ? 1 : 0), n = node->srcs().size(); i < n; ++i) {
      auto src = node->src(i).impl();
      srcs.emplace_back(map.at(src->id()));
    }
  }

  void eval() override {
    if (pred && !static_cast<bool>(*pred))
      return;
    if (format != "") {
      std::stringstream strbuf;
      for (const char *str = format.c_str(); *str != '\0'; ++str) {
        if (*str == '{') {
          fmtinfo_t fmt;
          str = parse_format_index(&fmt, str);
          auto src = srcs[fmt.index];
          switch (fmt.type) {
          case fmttype::Int:
            strbuf << *src;
            break;
          case fmttype::Float:
            strbuf << bit_cast<float>(static_cast<int>(*src));
            break;
          case fmttype::Enum:
            strbuf << enum_strings[fmt.index](static_cast<int>(*src));
           break;
          }
        } else {
          strbuf.put(*str);
        }
      }
      std::cout << strbuf.rdbuf();
    }
    std::cout << std::endl;
  }
};

///////////////////////////////////////////////////////////////////////////////

struct instr_udfc : instr_base {
  udf_iface* udf;
  udf_inputs srcs;
  bitvector dst;

  instr_udfc(udfcimpl* node, instr_map_t& map)
    : udf(node->udf())
    , dst(node->size()) {
    srcs.reserve(node->srcs().size());
    for (auto src : node->srcs()) {
      srcs.emplace_back(map.at(src.id()));
    }
    map[node->id()] = &dst;
  }

  void eval() override {
    udf->eval(dst, srcs);
  }
};

///////////////////////////////////////////////////////////////////////////////

struct instr_udfs : instr_base {
  std::vector<bitvector> pipe;
  udf_iface* udf;
  udf_inputs srcs;
  const bitvector* cd;
  const bitvector* reset;
  bitvector dst;

  instr_udfs(udfsimpl* node, instr_map_t& map)
    : udf(node->udf())
    , cd(nullptr)
    , reset(nullptr)
    , dst(node->size()) {
    srcs.reserve(node->srcs().size());    
    pipe.resize(udf->delta() - 1, bitvector(dst.size()));
    map[node->id()] = &dst;
  }

  void init(udfsimpl* node, instr_map_t& map) {
    cd = map.at(node->cd().id());
    reset = node->has_initdata() ? map.at(node->reset().id()) : nullptr;
    for (auto src : node->srcs()) {
      srcs.emplace_back(map.at(src.id()));
    }
  }

  void eval() override {
    // check clock transition
    if (!static_cast<bool>(*cd))
      return;

    bitvector* value = &dst;

    // advance the pipeline
    if (!pipe.empty()) {
      auto last = pipe.size() - 1;
      dst = pipe[last];
      for (int i = last; i > 0; --i) {
        pipe[i] = pipe[i-1];
      }
      value = &pipe[0];
    }

    // push new entry
    if (reset && static_cast<bool>(*reset)) {
      udf->reset(*value, srcs);
    } else {
      udf->eval(*value, srcs);
    }
  }
};

///////////////////////////////////////////////////////////////////////////////

simref::simref() {}

simref::~simref() {
  for (auto instr : instrs_) {
    delete instr;
  }
}

void simref::initialize(const std::vector<lnodeimpl*>& eval_list) {
  instr_map_t instr_map;
  std::unordered_map<uint32_t, instr_base*> snodes;
  instrs_.reserve(eval_list.size());

  // lower synchronous nodes
  for (auto node : eval_list) {
    switch (node->type()) {
    case type_reg:
      snodes[node->id()] = new instr_reg(reinterpret_cast<regimpl*>(node), instr_map);
      break;
    case type_mem:
      snodes[node->id()] = new instr_mem(reinterpret_cast<memimpl*>(node), instr_map);
      break;
    case type_udfs:
      snodes[node->id()] = new instr_udfs(reinterpret_cast<udfsimpl*>(node), instr_map);
      break;
    default:
      break;
    }
  }

  // lower all nodes
  for (auto node : eval_list) {
    switch (node->type()) {
    case type_undef:
      assert(false);
      break;
    case type_lit:
      instr_map[node->id()] = &reinterpret_cast<litimpl*>(node)->value();
      break;
    case type_proxy:
      instrs_.emplace_back(new instr_proxy(reinterpret_cast<proxyimpl*>(node), instr_map));
      break;
    case type_input: {
      auto input = reinterpret_cast<inputimpl*>(node);
      if (input->is_bind()) {
        instr_map[node->id()] = instr_map.at(input->binding().id());
      } else {
        instr_map[node->id()] = &input->value();
      }
    } break;
    case type_output: {
      auto output = reinterpret_cast<outputimpl*>(node);
      instr_map[node->id()] = instr_map.at(output->src(0).id());
      if (!output->is_bind()) {
        instrs_.emplace_back(new instr_output(output, instr_map));
      }
    } break;
    case type_alu:
      instrs_.emplace_back(create_alu_instr(reinterpret_cast<aluimpl*>(node), instr_map));
      break;
    case type_sel:
      instrs_.emplace_back(new instr_select(reinterpret_cast<selectimpl*>(node), instr_map));
      break;
    case type_cd:
      instrs_.emplace_back(new instr_cd(reinterpret_cast<cdimpl*>(node), instr_map));
      break;
    case type_reg: {
      auto instr = reinterpret_cast<instr_reg*>(snodes.at(node->id()));
      instr->init(reinterpret_cast<regimpl*>(node), instr_map);
      instrs_.emplace_back(instr);
    } break;
    case type_mem: {
      auto instr = reinterpret_cast<instr_mem*>(snodes.at(node->id()));
      instr->init(reinterpret_cast<memimpl*>(node), instr_map);
      instrs_.emplace_back(instr);
    } break;
    case type_mrport: {
      auto port = reinterpret_cast<mrportimpl*>(node);
      if (!port->is_sync_read()) {
        instrs_.emplace_back(new instr_mrport(port, instr_map));
      }
    } break;
    case type_mwport:
    case type_bind:
      // skip
      break;
    case type_bindin:
      instr_map[node->id()] = instr_map.at(reinterpret_cast<bindportimpl*>(node)->src(0).id());
      break;
    case type_bindout:
      instr_map[node->id()] = instr_map.at(reinterpret_cast<bindportimpl*>(node)->ioport().id());
      break;
    case type_tap:
      instrs_.emplace_back(new instr_tap(reinterpret_cast<tapimpl*>(node), instr_map));
      break;
    case type_assert:
      instrs_.emplace_back(new instr_assert(reinterpret_cast<assertimpl*>(node), instr_map));
      break;
    case type_time:
      instrs_.emplace_back(new instr_time(reinterpret_cast<timeimpl*>(node), instr_map));
      break;
    case type_print:
      instrs_.emplace_back(new instr_print(reinterpret_cast<printimpl*>(node), instr_map));
      break;
    case type_udfc:
      instrs_.emplace_back(new instr_udfc(reinterpret_cast<udfcimpl*>(node), instr_map));
      break;
    case type_udfs: {
      auto instr = reinterpret_cast<instr_udfs*>(snodes.at(node->id()));
      instr->init(reinterpret_cast<udfsimpl*>(node), instr_map);
      instrs_.emplace_back(instr);
    } break;
    }
  }
}

void simref::eval() {
  for (auto instr : instrs_) {
    instr->eval();
  }
}
