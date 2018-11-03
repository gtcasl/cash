#ifndef NLIBJIT

#include "simjit.h"
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
#include "jit/jit.h"
#include "jit/jit-dump.h"
#include "compile.h"

namespace ch::internal::simjit {

using alloc_map_t  = std::unordered_map<uint32_t, uint32_t>;
using var_map_t    = std::unordered_map<uint32_t, jit_value_t>;
using label_map_t  = std::unordered_map<uint32_t, jit_label_t>;
using bypass_set_t = std::unordered_set<uint32_t>;

static constexpr uint32_t WORD_SIZE = bitwidth_v<block_type>;
static constexpr uint32_t WORD_LOGSIZE = log2floor(WORD_SIZE);
static constexpr uint32_t WORD_MASK = bitwidth_v<block_type> - 1;
static constexpr block_type WORD_MAX = std::numeric_limits<block_type>::max();

#define __align_block(...) ((((__VA_ARGS__) + WORD_MASK) / WORD_SIZE) * sizeof(block_type))
#define __countof(arr) (sizeof(arr) / sizeof(arr[0]))
#define __source_location() jit_insn_mark_offset(j_func_, __LINE__)

struct sim_state_t {
  uint8_t*     vars;
  block_type** inputs;
  block_type** outputs;
};

typedef void (*pfn_entry)(sim_state_t*);

struct sim_ctx_t {
  sim_ctx_t() : state{}, entry(nullptr) {
    // create JIT context
    jit = jit_context_create();
  }

  ~sim_ctx_t() {
    if (jit) {
      jit_context_build_end(jit);
    }
    delete [] state.vars;
    delete [] state.inputs;
    delete [] state.outputs;
  }

  sim_state_t state;
  pfn_entry entry;
  jit_context_t jit;
};

class compiler {
public:

  compiler(sim_ctx_t* ctx) : sim_ctx_(ctx), bypass_enable_(false) {}
  ~compiler() {}

  void build(const std::vector<lnodeimpl*>& eval_list) {
    // get context
    auto ctx = eval_list.back()->ctx();
    assert(ctx->cdomains().size() <= 1);

    // begin build
    jit_context_build_start(sim_ctx_->jit);

    // create JIT function
    this->create_function();

    // allocate objects
    this->allocate_nodes(ctx);

    // lower all nodes
    for (auto node : eval_list) {
      switch (node->type()) {
      case type_lit:
        this->emit_node(reinterpret_cast<litimpl*>(node));
        break;
      case type_proxy:
        this->emit_node(reinterpret_cast<proxyimpl*>(node));
        break;        
      case type_input:
        this->emit_node(reinterpret_cast<inputimpl*>(node));
        break;
      case type_output:
      case type_tap:
        this->emit_node(reinterpret_cast<outputimpl*>(node));
        break;
      case type_alu:
        this->emit_node(reinterpret_cast<aluimpl*>(node));
        break;
      case type_sel:
        this->emit_node(reinterpret_cast<selectimpl*>(node));
        break;
      case type_cd:
        this->emit_node(reinterpret_cast<cdimpl*>(node));
        break;
      case type_reg:
        this->emit_node(reinterpret_cast<regimpl*>(node));
        break;
      case type_marport:
        this->emit_node(reinterpret_cast<marportimpl*>(node));
        break;
      case type_msrport:        
        this->emit_node(reinterpret_cast<msrportimpl*>(node));
        break;
      case type_mwport:
        this->emit_node(reinterpret_cast<mwportimpl*>(node));
        break;
      case type_time:
        this->emit_node(reinterpret_cast<timeimpl*>(node));
        break;
      case type_assert:
        CH_TODO();
        break;
      case type_print:
        this->emit_node(reinterpret_cast<printimpl*>(node));
        break;
      case type_udfc:
        CH_TODO();
        break;
      case type_udfs:
        CH_TODO();
        break;
      case type_mem:
        break;
      default:
        std::abort();
        break;
      }
    }

    // create end label
    this->create_node_label(nullptr);

    // dump JIT assembly code
    if (platform::self().cflags() & cflags::dump_jit) {
      FILE* file = fopen("simjit.tac", "w");
      jit_dump_function(file, j_func_, "simjit");
      fclose(file);
    }

    // compile function
    jit_function_compile(j_func_);

    // end build
    jit_context_build_end(sim_ctx_->jit);

    // dump JIT assembly code
    if (platform::self().cflags() & cflags::dump_asm) {
      FILE* file = fopen("simjit.asm", "w");
      jit_dump_function(file, j_func_, "simjit");
      fclose(file);
    }

    // get closure
    sim_ctx_->entry = reinterpret_cast<pfn_entry>(jit_function_to_closure(j_func_));
  }

private:

  struct const_alloc_t {
    const_alloc_t(block_type* data, uint32_t size, uint32_t node_id)
      : data(data)
      , size(size) {
      nodes.push_back(node_id);
    }

    block_type* data;
    uint32_t    size;
    std::vector<uint32_t> nodes;
  };

  union data_t {
    block_type  value;
    block_type* ptr;
  };

  struct cd_data_t {
    int prev_value;

    static uint32_t size() {
      return sizeof(cd_data_t);
    }

    void init() {
      this->prev_value = 0;
    }
  };

  typedef const char* (*enum_string_cb)(uint32_t value);

  struct print_data_t {
    bool predicated;
    char* format;
    enum_string_cb* enum_strings;
    data_t* src_values;
    uint32_t* src_sizes;

    static uint32_t size(printimpl* node) {
      uint32_t size = sizeof(print_data_t);
      size += node->format().size() + 1;
      size += node->enum_strings().size() * sizeof(enum_string_cb);
      size += node->srcs().size() * sizeof(data_t);
      size += node->srcs().size() * sizeof(uint32_t);
      return size;
    }

    void init(printimpl* node, const compiler* cp) {
      auto buf = reinterpret_cast<uint8_t*>(this) + sizeof(print_data_t);

      this->predicated = node->has_pred();

      auto fmtlen = node->format().size();
      if (fmtlen) {
        format = reinterpret_cast<char*>(buf);
        memcpy(format, node->format().c_str(), fmtlen + 1);
        buf += fmtlen + 1;
      } else {
        format = nullptr;
      }

      this->enum_strings = reinterpret_cast<enum_string_cb*>(buf);
      auto e = this->enum_strings;
      for (auto cb : node->enum_strings()) {
        *e++ = cb;
      }
      buf += node->enum_strings().size() * sizeof(enum_string_cb);

      this->src_values = reinterpret_cast<data_t*>(buf);
      buf += node->srcs().size() * sizeof(data_t);

      this->src_sizes = reinterpret_cast<uint32_t*>(buf);
      buf += node->srcs().size() * sizeof(uint32_t);

      auto src_value = this->src_values;
      auto src_size = this->src_sizes;
      for (auto& src : node->srcs()) {
        if (src.size() > WORD_SIZE) {
          auto addr = cp->addr_map_.at(src.id());
          switch (src.impl()->type()) {
          case type_input:
            src_value->ptr = cp->sim_ctx_->state.inputs[addr];
            break;
          default:
            src_value->ptr = reinterpret_cast<block_type*>(cp->sim_ctx_->state.vars + addr);
            break;
          }
        }
        ++src_value;
        *src_size++ = src.size();
      }
    }

    static void eval(print_data_t* self) {
      if (self->predicated && !static_cast<bool>(self->src_values[0].value))
        return;
      if (self->format) {
        std::stringstream strbuf;
        for (const char *str = self->format; *str != '\0'; ++str) {
          if (*str == '{') {
            fmtinfo_t fmt;
            str = parse_format_index(&fmt, str);
            auto src_value = self->src_values[fmt.index];
            auto src_size = self->src_sizes[fmt.index];
            sdata_type value;
            if (src_size > WORD_SIZE) {
              value.emplace(src_value.ptr, src_size);
            } else {
              value.resize(src_size);
              value = src_value.value;
            }
            switch (fmt.type) {
            case fmttype::Int:
              strbuf << value;
             break;
            case fmttype::Float:
              strbuf << bit_cast<float>(static_cast<int>(value));
             break;
            case fmttype::Enum:
              strbuf << self->enum_strings[fmt.index](static_cast<int>(value));
             break;
            }
            if (src_size > WORD_SIZE) {
              value.emplace(nullptr, 0);
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

  struct time_data_t {
    uint64_t value;

    static uint32_t size() {
      return sizeof(time_data_t);
    }

    void init() {
      this->value = 0;
    }
  };


  void create_function() {
    jit_type_t params[1] = {jit_type_void_ptr};
    auto sig = jit_type_create_signature(jit_abi_cdecl, jit_type_void, params, 1, 1);
    j_func_ = jit_function_create(sim_ctx_->jit, sig);
    auto j_state = jit_value_get_param(j_func_, 0);
    j_vars_ = jit_insn_load_relative(j_func_, j_state, offsetof(sim_state_t, vars), jit_type_void_ptr);
    j_inputs_ = jit_insn_load_relative(j_func_, j_state, offsetof(sim_state_t, inputs), jit_type_void_ptr);
    j_outputs_ = jit_insn_load_relative(j_func_, j_state, offsetof(sim_state_t, outputs), jit_type_void_ptr);
    j_block_logsize_ = jit_value_create_nint_constant(j_func_, jit_type_uint, WORD_LOGSIZE);
    j_block_mask_ = jit_value_create_nint_constant(j_func_, jit_type_uint, WORD_MASK);
  }

  void emit_node(litimpl* node) {
    __source_location();
    this->create_node_label(node);
    uint32_t dst_width = node->size();
    if (dst_width <= WORD_SIZE) {
      auto j_value = jit_value_create_long_constant(j_func_, jit_type_ulong, node->value().word(0));
      scalar_map_[node->id()] = j_value;
    }
  }

  void emit_node(proxyimpl* node) {
    __source_location();
    assert(node->check_full());
    this->create_node_label(node);
    uint32_t dst_width = node->size();
    if (dst_width <= WORD_SIZE) {
      // inline code
      auto j_dst = jit_value_create(j_func_, jit_type_ulong);
      scalar_map_[node->id()] = j_dst;
      for (uint i = 0, n = node->ranges().size(); i < n; ++i) {
        auto& range = node->range(i);
        auto& src = node->src(range.src_idx);
        jit_value_t j_src;
        if  (src.size() <= WORD_SIZE) {
          if (src.size() != range.length) {
            j_src = this->slice_scalar(scalar_map_.at(src.id()), range.src_offset, range.length);
          } else {
            j_src = scalar_map_.at(src.id());
          }
        } else {
          j_src = this->slice_vsmall(src.impl()->type(), addr_map_.at(src.id()), range.src_offset, range.length);
        }

        jit_value_t j_src_s;
        if (0 == range.dst_offset) {
          j_src_s = j_src;
        } else {
          auto j_dst_lsb = jit_value_create_nint_constant(j_func_, jit_type_uint, range.dst_offset);
          j_src_s = jit_insn_shl(j_func_, j_src, j_dst_lsb);
        }

        if (0 == i) {
          jit_insn_store(j_func_, j_dst, j_src_s);
        } else {
          auto j_tmp = jit_insn_or(j_func_, j_dst, j_src_s);
          jit_insn_store(j_func_, j_dst, j_tmp);
        }
      }
    } else {
      // function call
      uint32_t dst_offset = 0;
      for (uint i = 0, n = node->ranges().size(); i < n; ++i) {
        auto& range = node->range(i);
        auto& src = node->src(range.src_idx);
        auto dst_idx = dst_offset / WORD_SIZE;
        auto dst_lsb = dst_offset % WORD_SIZE;
        auto dst_msb = (dst_lsb + range.length - 1) % WORD_SIZE;
        if (range.length <= WORD_SIZE) {
          jit_value_t j_src;
          if  (src.size() <= WORD_SIZE) {
            j_src = this->slice_scalar_source(scalar_map_.at(src.id()), range.src_offset);
          } else {
            j_src = this->slice_vsmall_source(src.impl()->type(), addr_map_.at(src.id()), range.src_offset, range.length);
          }
          auto j_dst_lsb = jit_value_create_nint_constant(j_func_, jit_type_uint, dst_lsb);
          auto j_tmp1 = jit_insn_shl(j_func_, j_src, j_dst_lsb);
          auto dst_addr = addr_map_.at(node->id());
          auto j_dst_value0 = jit_insn_load_relative(j_func_, this->buffer(node->type()), dst_addr + dst_idx * sizeof(block_type), jit_type_ulong);
          auto j_mask0 = jit_value_create_long_constant(j_func_, jit_type_ulong, (WORD_MAX >> (WORD_SIZE - range.length)) << dst_lsb);
          auto j_tmp2 = this->blend(j_mask0, j_dst_value0, j_tmp1);
          jit_insn_store_relative(j_func_, this->buffer(node->type()), dst_addr + dst_idx * sizeof(block_type), j_tmp2);
          if (dst_lsb + range.length > WORD_SIZE) {
            auto j_dst_value1 = jit_insn_load_relative(j_func_, this->buffer(node->type()), dst_addr + (dst_idx + 1) * sizeof(block_type), jit_type_ulong);
            auto j_mask1 = jit_value_create_long_constant(j_func_, jit_type_ulong, (WORD_MAX << 1) << dst_msb);
            auto j_tmp3 = jit_value_create_nint_constant(j_func_, jit_type_uint, WORD_SIZE - dst_lsb);
            auto j_tmp4 = jit_insn_ushr(j_func_, j_src, j_tmp3);
            auto j_tmp5 = this->blend(j_mask1, j_tmp4, j_dst_value1);
            jit_insn_store_relative(j_func_, this->buffer(node->type()), dst_addr + (dst_idx + 1) * sizeof(block_type), j_tmp5);
          }
        } else {
          CH_TODO();
        }
        dst_offset += range.length;
      }
    }
  }

  void emit_node(inputimpl* node) {
    __source_location();
    this->create_node_label(node);
    uint32_t dst_width = node->size();
    uint32_t addr = addr_map_.at(node->id());
    auto j_src_ptr = jit_insn_load_relative(j_func_, j_inputs_, addr * sizeof(block_type*), jit_type_void_ptr);
    if (dst_width <= WORD_SIZE) {
      auto j_src_value = jit_insn_load_relative(j_func_, j_src_ptr, 0, jit_type_ulong);
      scalar_map_[node->id()] = j_src_value;
    } else {
      scalar_map_[node->id()] = j_src_ptr;
    }
  }

  void emit_node(ioportimpl* node) {
    __source_location();
    this->create_node_label(node);
    uint32_t dst_width = node->size();
    uint32_t addr = addr_map_.at(node->id());
    auto j_dst_ptr = jit_insn_load_relative(j_func_, j_outputs_, addr * sizeof(block_type*), jit_type_void_ptr);
    if (dst_width <= WORD_SIZE) {
      auto j_src_value = scalar_map_.at(node->src(0).id());
      jit_insn_store_relative(j_func_, j_dst_ptr, 0, j_src_value);
    } else {
      auto num_words = ceildiv<uint32_t>(dst_width, WORD_SIZE);
      auto j_size = jit_value_create_nint_constant(j_func_, jit_type_uint, num_words * sizeof(block_type));
      auto src_addr = addr_map_.at(node->src(0).id());
      auto j_src_ptr = jit_insn_add_relative(j_func_, this->buffer(node->src(0).impl()->type()), src_addr);
      jit_insn_memcpy(j_func_, j_dst_ptr, j_src_ptr, j_size);
    }
  }

  void emit_node(aluimpl* node) {
    __source_location();
    this->create_node_label(node);
    uint32_t dst_width = node->size();
    switch (node->op()) {
    case ch_op::eq:
      if (dst_width <= WORD_SIZE) {
        assert(-1 == node->should_resize_opds() || !node->is_signed());
        auto j_src0 = scalar_map_.at(node->src(0).id());
        auto j_src1 = scalar_map_.at(node->src(1).id());
        auto j_dst  = jit_insn_eq(j_func_, j_src0, j_src1);
        scalar_map_[node->id()] = j_dst;
      } else {
        CH_TODO();
      }
      break;
    case ch_op::ne:
      if (dst_width <= WORD_SIZE) {
        assert(-1 == node->should_resize_opds() || !node->is_signed());
        auto j_src0 = scalar_map_.at(node->src(0).id());
        auto j_src1 = scalar_map_.at(node->src(1).id());
        auto j_dst  = jit_insn_ne(j_func_, j_src0, j_src1);
        scalar_map_[node->id()] = j_dst;
      } else {
        CH_TODO();
      }
      break;

    case ch_op::lt:
      if (dst_width <= WORD_SIZE) {
        assert(!node->is_signed());
        auto j_src0 = scalar_map_.at(node->src(0).id());
        auto j_src1 = scalar_map_.at(node->src(1).id());
        auto j_dst  = jit_insn_lt(j_func_, j_src0, j_src1);
        scalar_map_[node->id()] = j_dst;
      } else {
        CH_TODO();
      }
      break;
    case ch_op::gt:
      if (dst_width <= WORD_SIZE) {
        assert(!node->is_signed());
        auto j_src0 = scalar_map_.at(node->src(0).id());
        auto j_src1 = scalar_map_.at(node->src(1).id());
        auto j_dst  = jit_insn_gt(j_func_, j_src0, j_src1);
        scalar_map_[node->id()] = j_dst;
      } else {
        CH_TODO();
      }
      break;
    case ch_op::le:
      if (dst_width <= WORD_SIZE) {
        assert(!node->is_signed());
        auto j_src0 = scalar_map_.at(node->src(0).id());
        auto j_src1 = scalar_map_.at(node->src(1).id());
        auto j_dst  = jit_insn_le(j_func_, j_src0, j_src1);
        scalar_map_[node->id()] = j_dst;
      } else {
        CH_TODO();
      }
      break;
    case ch_op::ge:
      if (dst_width <= WORD_SIZE) {
        assert(!node->is_signed());
        auto j_src0 = scalar_map_.at(node->src(0).id());
        auto j_src1 = scalar_map_.at(node->src(1).id());
        auto j_dst  = jit_insn_ge(j_func_, j_src0, j_src1);
        scalar_map_[node->id()] = j_dst;
      } else {
        CH_TODO();
      }
      break;

    case ch_op::notl:
      if (dst_width <= WORD_SIZE) {
        auto j_src0 = scalar_map_.at(node->src(0).id());
        auto j_dst  = jit_insn_to_not_bool(j_func_, j_src0);
        scalar_map_[node->id()] = j_dst;
      } else {
        CH_TODO();
      }
      break;
    case ch_op::andl:
      if (dst_width <= WORD_SIZE) {
        auto j_src0 = scalar_map_.at(node->src(0).id());
        auto j_src1 = scalar_map_.at(node->src(1).id());
        auto j_src0_b = node->src(0).size() > 1 ? jit_insn_to_bool(j_func_, j_src0) : j_src0;
        auto j_src1_b = node->src(1).size() > 1 ? jit_insn_to_bool(j_func_, j_src1) : j_src1;
        auto j_dst  = jit_insn_and(j_func_, j_src0_b, j_src1_b);
        scalar_map_[node->id()] = j_dst;
      } else {
        CH_TODO();
      }
      break;
    case ch_op::orl:
      if (dst_width <= WORD_SIZE) {
        auto j_src0 = scalar_map_.at(node->src(0).id());
        auto j_src1 = scalar_map_.at(node->src(1).id());
        auto j_src0_b = node->src(0).size() > 1 ? jit_insn_to_bool(j_func_, j_src0) : j_src0;
        auto j_src1_b = node->src(1).size() > 1 ? jit_insn_to_bool(j_func_, j_src1) : j_src1;
        auto j_dst  = jit_insn_or(j_func_, j_src0_b, j_src1_b);
        scalar_map_[node->id()] = j_dst;
      } else {
        CH_TODO();
      }
      break;

    case ch_op::inv:
      if (dst_width <= WORD_SIZE) {
        assert(-1 == node->should_resize_opds() || !node->is_signed());
        auto j_src = scalar_map_.at(node->src(0).id());
        auto j_dst = jit_insn_not(j_func_, j_src);
        scalar_map_[node->id()] = j_dst;
      } else {
        CH_TODO();
      }
      this->clear_extra_bits(node);
      break;
    case ch_op::andb:
      if (dst_width <= WORD_SIZE) {
        assert(-1 == node->should_resize_opds() || !node->is_signed());
        auto j_src0 = scalar_map_.at(node->src(0).id());
        auto j_src1 = scalar_map_.at(node->src(1).id());
        auto j_dst  = jit_insn_and(j_func_, j_src0, j_src1);
        scalar_map_[node->id()] = j_dst;
      } else {
        assert(-1 == node->should_resize_opds());
        uint32_t num_words = ceildiv(dst_width, WORD_SIZE);
        for (uint32_t i = 0; i < num_words; ++i) {
          auto src0_addr = addr_map_.at(node->src(0).id());
          auto j_src0 = jit_insn_load_relative(j_func_, this->buffer(node->src(0).impl()->type()), src0_addr + i * sizeof(block_type), jit_type_ulong);
          auto src1_addr = addr_map_.at(node->src(1).id());
          auto j_src1 = jit_insn_load_relative(j_func_, this->buffer(node->src(1).impl()->type()), src1_addr + i * sizeof(block_type), jit_type_ulong);
          auto j_dst  = jit_insn_and(j_func_, j_src0, j_src1);
          auto dst_addr = addr_map_.at(node->id());
          jit_insn_store_relative(j_func_, this->buffer(node->type()), dst_addr + i * sizeof(block_type), j_dst);
        }
      }
      break;
    case ch_op::orb:
      if (dst_width <= WORD_SIZE) {
        assert(-1 == node->should_resize_opds() || !node->is_signed());
        auto j_src0 = scalar_map_.at(node->src(0).id());
        auto j_src1 = scalar_map_.at(node->src(1).id());
        auto j_dst  = jit_insn_or(j_func_, j_src0, j_src1);
        scalar_map_[node->id()] = j_dst;
      } else {
        assert(-1 == node->should_resize_opds());
        uint32_t num_words = ceildiv(dst_width, WORD_SIZE);
        for (uint32_t i = 0; i < num_words; ++i) {
          auto src0_addr = addr_map_.at(node->src(0).id());
          auto j_src0 = jit_insn_load_relative(j_func_, this->buffer(node->src(0).impl()->type()), src0_addr + i * sizeof(block_type), jit_type_ulong);
          auto src1_addr = addr_map_.at(node->src(1).id());
          auto j_src1 = jit_insn_load_relative(j_func_, this->buffer(node->src(1).impl()->type()), src1_addr + i * sizeof(block_type), jit_type_ulong);
          auto j_dst  = jit_insn_or(j_func_, j_src0, j_src1);
          auto dst_addr = addr_map_.at(node->id());
          jit_insn_store_relative(j_func_, this->buffer(node->type()), dst_addr + i * sizeof(block_type), j_dst);
        }
      }
      break;
    case ch_op::xorb:
      if (dst_width <= WORD_SIZE) {
        assert(-1 == node->should_resize_opds() || !node->is_signed());
        auto j_src0 = scalar_map_.at(node->src(0).id());
        auto j_src1 = scalar_map_.at(node->src(1).id());
        auto j_dst  = jit_insn_xor(j_func_, j_src0, j_src1);
        scalar_map_[node->id()] = j_dst;
      } else {
        assert(-1 == node->should_resize_opds());
        uint32_t num_words = ceildiv(dst_width, WORD_SIZE);
        for (uint32_t i = 0; i < num_words; ++i) {
          auto src0_addr = addr_map_.at(node->src(0).id());
          auto j_src0 = jit_insn_load_relative(j_func_, this->buffer(node->src(0).impl()->type()), src0_addr + i * sizeof(block_type), jit_type_ulong);
          auto src1_addr = addr_map_.at(node->src(1).id());
          auto j_src1 = jit_insn_load_relative(j_func_, this->buffer(node->src(1).impl()->type()), src1_addr + i * sizeof(block_type), jit_type_ulong);
          auto j_dst  = jit_insn_xor(j_func_, j_src0, j_src1);
          auto dst_addr = addr_map_.at(node->id());
          jit_insn_store_relative(j_func_, this->buffer(node->type()), dst_addr + i * sizeof(block_type), j_dst);
        }
      }
      break;

    case ch_op::andr:
      CH_TODO();
      break;
    case ch_op::orr:
      CH_TODO();
      break;
    case ch_op::xorr:
      CH_TODO();
      break;

    case ch_op::shl:
      if (dst_width <= WORD_SIZE) {
        auto j_src0 = scalar_map_.at(node->src(0).id());
        auto j_src1 = scalar_map_.at(node->src(1).id());
        auto j_dst  = jit_insn_shl(j_func_, j_src0, j_src1);
        scalar_map_[node->id()] = j_dst;
      } else {
        CH_TODO();
      }
      this->clear_extra_bits(node);
      break;
    case ch_op::shr:
      if (dst_width <= WORD_SIZE) {
        assert(!node->is_signed());
        auto j_src0 = scalar_map_.at(node->src(0).id());
        auto j_src1 = scalar_map_.at(node->src(1).id());
        auto j_dst  = jit_insn_shr(j_func_, j_src0, j_src1);
        scalar_map_[node->id()] = j_dst;
      } else {
        CH_TODO();
      }
      break;

    case ch_op::neg:
      if (dst_width <= WORD_SIZE) {
        assert(-1 == node->should_resize_opds() || !node->is_signed());
        auto j_src = scalar_map_.at(node->src(0).id());
        auto j_dst = jit_insn_neg(j_func_, j_src);
        scalar_map_[node->id()] = j_dst;
      } else {
        CH_TODO();
      }
      this->clear_extra_bits(node);
      break;
    case ch_op::add:
      if (dst_width <= WORD_SIZE) {
        assert(-1 == node->should_resize_opds() || !node->is_signed());
        auto j_src0 = scalar_map_.at(node->src(0).id());
        auto j_src1 = scalar_map_.at(node->src(1).id());
        auto j_dst  = jit_insn_add(j_func_, j_src0, j_src1);
        scalar_map_[node->id()] = j_dst;
      } else {
        CH_TODO();
      }
      this->clear_extra_bits(node);
      break;
    case ch_op::sub:
      if (dst_width <= WORD_SIZE) {
        assert(-1 == node->should_resize_opds() || !node->is_signed());
        auto j_src0 = scalar_map_.at(node->src(0).id());
        auto j_src1 = scalar_map_.at(node->src(1).id());
        auto j_dst  = jit_insn_sub(j_func_, j_src0, j_src1);
        scalar_map_[node->id()] = j_dst;
      } else {
        CH_TODO();
      }
      this->clear_extra_bits(node);
      break;

    case ch_op::mult:
      if (dst_width <= WORD_SIZE) {
        assert(!node->is_signed());
        auto j_src0 = scalar_map_.at(node->src(0).id());
        auto j_src1 = scalar_map_.at(node->src(1).id());
        auto j_dst  = jit_insn_mul(j_func_, j_src0, j_src1);
        scalar_map_[node->id()] = j_dst;
      } else {
        CH_TODO();
      }
      this->clear_extra_bits(node);
      break;
    case ch_op::div:
      if (dst_width <= WORD_SIZE) {
        assert(!node->is_signed());
        auto j_src0 = scalar_map_.at(node->src(0).id());
        auto j_src1 = scalar_map_.at(node->src(1).id());
        auto j_dst  = jit_insn_div(j_func_, j_src0, j_src1);
        scalar_map_[node->id()] = j_dst;
      } else {
        CH_TODO();
      }
      this->clear_extra_bits(node);
      break;
    case ch_op::mod:
      if (dst_width <= WORD_SIZE) {
        assert(!node->is_signed());
        auto j_src0 = scalar_map_.at(node->src(0).id());
        auto j_src1 = scalar_map_.at(node->src(1).id());
        auto j_dst  = jit_insn_rem(j_func_, j_src0, j_src1);
        scalar_map_[node->id()] = j_dst;
      } else {
        CH_TODO();
      }
      this->clear_extra_bits(node);
      break;

    case ch_op::pad:
      if (dst_width <= WORD_SIZE) {
        if (node->is_signed()) {
          CH_TODO();
        } else {
          auto j_dst = scalar_map_.at(node->src(0).id());
          scalar_map_[node->id()] = j_dst;
        }
      } else {
        CH_TODO();
      }
      break;
    default:
      std::abort();
      break;
    }
  }

  void emit_node(selectimpl* node) {
    __source_location();
    this->create_node_label(node);
    jit_label_t l_exit = jit_label_undefined;

    uint32_t dst_width = node->size();
    if (dst_width <= WORD_SIZE) {
      auto j_dst = jit_value_create(j_func_, jit_type_ulong);
      scalar_map_[node->id()] = j_dst;
      if (node->has_key()) {
        if (node->key().size() <= WORD_SIZE) {
          auto j_key = scalar_map_.at(node->src(0).id());
          uint32_t i = 1, l = node->srcs().size() - 1;
          for (;i < l; i += 2) {
            jit_label_t l_skip = jit_label_undefined;            
            auto j_val = scalar_map_.at(node->src(i).id());
            auto j_eq  = jit_insn_eq(j_func_, j_key, j_val);
            jit_insn_branch_if_not(j_func_, j_eq, &l_skip);
            auto j_src = scalar_map_.at(node->src(i+1).id());
            jit_insn_store(j_func_, j_dst, j_src);
            jit_insn_branch(j_func_, &l_exit);
            jit_insn_label(j_func_, &l_skip);
          }
          auto j_src = scalar_map_.at(node->src(i).id());
          jit_insn_store(j_func_, j_dst, j_src);
        } else {
          CH_TODO();
        }
      } else {
        uint32_t i = 0, l = node->srcs().size() - 1;
        for (;i < l; i += 2) {
          jit_label_t l_skip = jit_label_undefined;
          auto j_pred = scalar_map_.at(node->src(i).id());
          jit_insn_branch_if_not(j_func_, j_pred, &l_skip);
          auto j_src = scalar_map_.at(node->src(i+1).id());
          jit_insn_store(j_func_, j_dst, j_src);
          jit_insn_branch(j_func_, &l_exit);
          jit_insn_label(j_func_, &l_skip);
        }
        auto j_src = scalar_map_.at(node->src(i).id());
        jit_insn_store(j_func_, j_dst, j_src);
      }
    } else {
      CH_TODO();
    }

    jit_insn_label(j_func_, &l_exit);
  }

  void emit_node(cdimpl* node) {
    __source_location();
    ch::internal::compiler::build_bypass_list(bypass_nodes_, node->ctx(), node->id());
    auto addr = addr_map_.at(node->id());
    auto j_prev_clk = jit_insn_load_relative(j_func_, this->buffer(node->type()), addr, jit_type_uint);
    auto j_clk = this->cast(scalar_map_.at(node->src(0).id()), jit_type_uint);
    auto j_clk_changed = jit_insn_xor(j_func_, j_clk, j_prev_clk);
    jit_value_t j_changed ;
    if (node->pos_edge()) {
      j_changed = jit_insn_and(j_func_, j_clk_changed, j_clk);
    } else {
      auto j_clk_n = jit_insn_not(j_func_, j_clk);
      j_changed = jit_insn_and(j_func_, j_clk_changed, j_clk_n);
    }
    jit_insn_store_relative(j_func_, this->buffer(node->type()), addr, j_clk);
    jit_label_t j_label = jit_label_undefined;
    jit_insn_branch_if_not(j_func_, j_changed, &j_label);
    j_bypass_ = j_label;
    bypass_enable_ = true;
  }

  void create_node_label(lnodeimpl* node) {    
    if (!bypass_enable_)
      return;
    if (node) {
      if (!bypass_nodes_.empty()
       && bypass_nodes_.count(node->id())) {
        jit_insn_label(j_func_, &j_bypass_);
        bypass_enable_ = false;
      }
    } else {
      jit_insn_label(j_func_, &j_bypass_);
      bypass_enable_ = false;
    }
  }

  void emit_node(regimpl* node) {
    __source_location();
    this->create_node_label(node);
    jit_label_t l_exit = jit_label_undefined;

    auto dst_addr = addr_map_.at(node->id());
    uint32_t dst_width = node->size();
    if (!node->is_pipe()) {
      bool is_scalar = (dst_width <= WORD_SIZE);
      if (node->has_init_data()) {
        jit_label_t l_skip = jit_label_undefined;
        auto j_reset = scalar_map_.at(node->reset().id());
        jit_insn_branch_if_not(j_func_, j_reset, &l_skip);
        if (is_scalar) {
          auto j_init_data = scalar_map_.at(node->init_data().id());
          auto j_dst = scalar_map_.at(node->id());
          jit_insn_store(j_func_, j_dst, j_init_data);
          jit_insn_store_relative(j_func_, this->buffer(node->type()), dst_addr, j_init_data);
        } else {
          auto num_words = ceildiv<uint32_t>(dst_width, WORD_SIZE);
          auto j_size = jit_value_create_nint_constant(j_func_, jit_type_uint, num_words * sizeof(block_type));
          auto init_addr = addr_map_.at(node->init_data().id());
          auto j_init_ptr = jit_insn_add_relative(j_func_, this->buffer(node->init_data().impl()->type()), init_addr);
          auto j_dst_ptr = jit_insn_add_relative(j_func_, this->buffer(node->type()), dst_addr);
          jit_insn_memcpy(j_func_, j_dst_ptr, j_init_ptr, j_size);
        }
        jit_insn_branch(j_func_, &l_exit);
        jit_insn_label(j_func_, &l_skip);
      }
      if (node->has_enable()) {
        auto j_enable = scalar_map_.at(node->enable().id());
        jit_insn_branch_if_not(j_func_, j_enable, &l_exit);
      }
      if (is_scalar) {
        auto j_next = scalar_map_.at(node->next().id());
        auto j_dst = scalar_map_.at(node->id());
        jit_insn_store(j_func_, j_dst, j_next);
        jit_insn_store_relative(j_func_, this->buffer(node->type()), dst_addr, j_next);
      } else {
        auto num_words = ceildiv<uint32_t>(dst_width, WORD_SIZE);
        auto j_size = jit_value_create_nint_constant(j_func_, jit_type_uint, num_words * sizeof(block_type));
        auto next_addr = addr_map_.at(node->next().id());
        auto j_next_ptr = jit_insn_add_relative(j_func_, this->buffer(node->next().impl()->type()), next_addr);
        auto j_dst_ptr = jit_insn_add_relative(j_func_, this->buffer(node->type()), dst_addr);
        jit_insn_memcpy(j_func_, j_dst_ptr, j_next_ptr, j_size);
      }
    } else {
      bool is_scalar = ((node->length() - 1) * dst_width <= WORD_SIZE);
      if (node->has_init_data()) {
        jit_label_t l_skip = jit_label_undefined;
        auto j_reset = scalar_map_.at(node->reset().id());
        jit_insn_branch_if_not(j_func_, j_reset, &l_skip);
        if (is_scalar) {
          jit_value_t j_init_data;
          if (type_lit == node->init_data().impl()->type()) {
            auto lit = reinterpret_cast<litimpl*>(node->init_data().impl());
            block_type init_data(0);
            block_type init_value = lit->value().word(0);
            for (uint32_t i = 0, n = node->length() - 1; i < n; ++i) {
              init_data |= init_value << (i * dst_width);
            }
            j_init_data = jit_value_create_long_constant(j_func_, jit_type_ulong, init_data);
          } else {
            CH_TODO();
          }
          auto j_dst = scalar_map_.at(node->id());
          jit_insn_store(j_func_, j_dst, j_init_data);
          jit_insn_store_relative(j_func_, this->buffer(node->type()), dst_addr + sizeof(block_type), j_init_data);
        } else {
          CH_TODO();
        }
        jit_insn_branch(j_func_, &l_exit);
        jit_insn_label(j_func_, &l_skip);
      }
      if (node->has_enable()) {
        auto j_enable = scalar_map_.at(node->enable().id());
        jit_insn_branch_if_not(j_func_, j_enable, &l_exit);
      }
      if (is_scalar) {
        auto j_pipe = jit_insn_load_relative(j_func_, this->buffer(node->type()), dst_addr + sizeof(block_type), jit_type_ulong);
        auto j_tmp1 = this->slice_scalar(j_pipe, 0, dst_width);
        auto j_dst = scalar_map_.at(node->id());
        jit_insn_store(j_func_, j_dst, j_tmp1);
        jit_insn_store_relative(j_func_, this->buffer(node->type()), dst_addr, j_tmp1);
        auto j_shift = jit_value_create_nint_constant(j_func_, jit_type_uint, dst_width);
        auto j_tmp2 = jit_insn_ushr(j_func_, j_pipe, j_shift);
        auto j_next = scalar_map_.at(node->next().id());
        auto j_tmp3 = this->copy_scalar(j_tmp2, (node->length() - 2) * dst_width, j_next, 0, dst_width);
        jit_insn_store_relative(j_func_, this->buffer(node->type()), dst_addr + sizeof(block_type), j_tmp3);
      } else {
        CH_TODO();
      }
    }

    jit_insn_label(j_func_, &l_exit);
  }

  void emit_node(marportimpl* node) {
    __source_location();
    this->create_node_label(node);
    auto data_width = node->mem()->data_width();
    if (data_width <= WORD_SIZE) {
      auto j_data_size = jit_value_create_nint_constant(j_func_, jit_type_uint, data_width);
      auto j_src_addr = this->cast(scalar_map_.at(node->addr().id()), jit_type_uint);
      auto j_src_off = jit_insn_mul(j_func_, j_src_addr, j_data_size);
      auto j_src_idx = jit_insn_ushr(j_func_, j_src_off, j_block_logsize_);
      auto j_src_lsb = jit_insn_and(j_func_, j_src_off, j_block_mask_);
      auto mem_addr = addr_map_.at(node->mem()->id());
      auto mem_base_ptr = jit_insn_add_relative(j_func_, this->buffer(node->mem()->type()), mem_addr);
      auto j_mem_ptr = jit_insn_load_elem_address(j_func_, mem_base_ptr, j_src_idx, jit_type_ulong);
      auto j_src_value0 = jit_insn_load_relative(j_func_, j_mem_ptr, 0, jit_type_ulong);
      auto j_src_value = jit_insn_ushr(j_func_, j_src_value0, j_src_lsb);
      auto j_dst_rem = jit_value_create_nint_constant(j_func_, jit_type_uint, WORD_SIZE - data_width);
      if (node->mem()->size() >= WORD_SIZE) {
        jit_label_t l_skip = jit_label_undefined;
        auto j_src_inclusive = jit_insn_le(j_func_, j_src_lsb, j_dst_rem);

        jit_insn_branch_if(j_func_, j_src_inclusive, &l_skip);
        auto j_src_value1 = jit_insn_load_relative(j_func_, j_mem_ptr, sizeof(block_type), jit_type_ulong);
        auto j_block_size = jit_value_create_nint_constant(j_func_, jit_type_uint, WORD_SIZE);
        auto j_tmp1 = jit_insn_sub(j_func_, j_block_size, j_src_lsb);
        auto j_tmp2 = jit_insn_shl(j_func_, j_src_value1, j_tmp1);
        auto j_tmp3 = jit_insn_or(j_func_, j_src_value, j_tmp2);
        jit_insn_store(j_func_, j_src_value, j_tmp3);

        jit_insn_label(j_func_, &l_skip);
      }
      auto j_tmp1 = jit_insn_shl(j_func_, j_src_value, j_dst_rem);
      auto j_tmp2 = jit_insn_ushr(j_func_, j_tmp1, j_dst_rem);
      scalar_map_[node->id()] = j_tmp2;
    } else {
      CH_TODO();
    }
  }

  void emit_node(msrportimpl* node) {
    __source_location();
    this->create_node_label(node);
    jit_label_t l_exit = jit_label_undefined;
    auto data_width = node->mem()->data_width();

    if (node->has_enable()) {
      auto j_enable = scalar_map_.at(node->enable().id());
      jit_insn_branch_if_not(j_func_, j_enable, &l_exit);
    }

    if (data_width <= WORD_SIZE) {
      auto j_data_size = jit_value_create_nint_constant(j_func_, jit_type_uint, data_width);
      auto j_src_addr = this->cast(scalar_map_.at(node->addr().id()), jit_type_uint);
      auto j_src_off = jit_insn_mul(j_func_, j_src_addr, j_data_size);
      auto j_src_idx = jit_insn_ushr(j_func_, j_src_off, j_block_logsize_);
      auto j_src_lsb = jit_insn_and(j_func_, j_src_off, j_block_mask_);
      auto mem_addr = addr_map_.at(node->mem()->id());
      auto mem_base_ptr = jit_insn_add_relative(j_func_, this->buffer(node->mem()->type()), mem_addr);
      auto j_mem_ptr = jit_insn_load_elem_address(j_func_, mem_base_ptr, j_src_idx, jit_type_ulong);
      auto j_src_value0 = jit_insn_load_relative(j_func_, j_mem_ptr, 0, jit_type_ulong);
      auto j_src_value = jit_insn_ushr(j_func_, j_src_value0, j_src_lsb);
      auto j_dst_rem = jit_value_create_nint_constant(j_func_, jit_type_uint, WORD_SIZE - data_width);
      if (node->mem()->size() >= WORD_SIZE) {
        jit_label_t l_skip = jit_label_undefined;
        auto j_src_inclusive = jit_insn_le(j_func_, j_src_lsb, j_dst_rem);

        jit_insn_branch_if(j_func_, j_src_inclusive, &l_skip);
        auto j_src_value1 = jit_insn_load_relative(j_func_, j_mem_ptr, sizeof(block_type), jit_type_ulong);
        auto j_block_size = jit_value_create_nint_constant(j_func_, jit_type_uint, WORD_SIZE);
        auto j_tmp1 = jit_insn_sub(j_func_, j_block_size, j_src_lsb);
        auto j_tmp2 = jit_insn_shl(j_func_, j_src_value1, j_tmp1);
        auto j_tmp3 = jit_insn_or(j_func_, j_src_value, j_tmp2);
        jit_insn_store(j_func_, j_src_value, j_tmp3);

        jit_insn_label(j_func_, &l_skip);
      }
      auto j_tmp1 = jit_insn_shl(j_func_, j_src_value, j_dst_rem);
      auto j_tmp2 = jit_insn_ushr(j_func_, j_tmp1, j_dst_rem);
      scalar_map_[node->id()] = j_tmp2;
    } else {
      CH_TODO();
    }

    jit_insn_label(j_func_, &l_exit);
  }

  void emit_node(mwportimpl* node) {
    __source_location();
    this->create_node_label(node);
    jit_label_t l_exit = jit_label_undefined;
    auto data_width = node->mem()->data_width();

    if (node->has_enable()) {
      auto j_enable = scalar_map_.at(node->enable().id());
      jit_insn_branch_if_not(j_func_, j_enable, &l_exit);
    }

    if (data_width <= WORD_SIZE) {
      auto j_data_size = jit_value_create_nint_constant(j_func_, jit_type_uint, data_width);
      auto j_data_size_m1 = jit_value_create_nint_constant(j_func_, jit_type_uint, data_width - 1);
      auto j_dst_addr = this->cast(scalar_map_.at(node->addr().id()), jit_type_uint);
      auto j_dst_off = jit_insn_mul(j_func_, j_dst_addr, j_data_size);
      auto j_dst_idx = jit_insn_ushr(j_func_, j_dst_off, j_block_logsize_);
      auto j_dst_lsb = jit_insn_and(j_func_, j_dst_off, j_block_mask_);
      auto j_dst_msb = jit_insn_and(j_func_, jit_insn_add(j_func_, j_dst_lsb, j_data_size_m1), j_block_mask_);

      auto j_wdata = this->slice_scalar_source(scalar_map_.at(node->wdata().id()), 0);

      auto mem_addr = addr_map_.at(node->mem()->id());
      auto mem_base_ptr = jit_insn_add_relative(j_func_, this->buffer(node->mem()->type()), mem_addr);
      auto j_mem_ptr = jit_insn_load_elem_address(j_func_, mem_base_ptr, j_dst_idx, jit_type_ulong);

      auto j_dst_value0 = jit_insn_load_relative(j_func_, j_mem_ptr, 0, jit_type_ulong);
      auto j_mask0 = jit_value_create_long_constant(j_func_, jit_type_ulong, (WORD_MAX >> (WORD_SIZE - data_width)));
      auto j_mask0_s = jit_insn_shl(j_func_, j_mask0, j_dst_lsb);
      auto j_wdata0 = jit_insn_shl(j_func_, j_wdata, j_dst_lsb);
      auto j_tmp1 = this->blend(j_mask0_s, j_dst_value0, j_wdata0);
      jit_insn_store_relative(j_func_, j_mem_ptr, 0, j_tmp1);

      auto j_dst_rem = jit_value_create_nint_constant(j_func_, jit_type_uint, WORD_SIZE - data_width);

      if (node->mem()->size() >= WORD_SIZE) {
        jit_label_t l_skip = jit_label_undefined;
        auto j_dst_inclusive = jit_insn_le(j_func_, j_dst_lsb, j_dst_rem);
        jit_insn_branch_if(j_func_, j_dst_inclusive, &l_skip);

        auto j_dst_value1 = jit_insn_load_relative(j_func_, j_mem_ptr, 1, jit_type_ulong);
        auto j_mask1 = jit_value_create_long_constant(j_func_, jit_type_ulong, (WORD_MAX  << 1));
        auto j_mask1_s = jit_insn_shl(j_func_, j_mask1, j_dst_msb);
        auto j_wdata1 = jit_insn_ushr(j_func_, j_wdata, j_dst_rem);
        auto j_tmp1 = this->blend(j_mask1_s, j_wdata1, j_dst_value1);
        jit_insn_store_relative(j_func_, j_mem_ptr, 1, j_tmp1);

        jit_insn_label(j_func_, &l_skip);
      }
    } else {
      CH_TODO();
    }

    jit_insn_label(j_func_, &l_exit);
  }

  void emit_node(timeimpl* node) {
    __source_location();
    this->create_node_label(node);
    auto addr = addr_map_.at(node->id());
    auto j_value = scalar_map_.at(node->id());
    auto j_one = jit_value_create_long_constant(j_func_, jit_type_ulong, 1);
    auto j_incr = jit_insn_add(j_func_, j_value, j_one);
    jit_insn_store_relative(j_func_, this->buffer(node->type()), addr, j_incr);
  }

  void emit_node(printimpl* node) {
    __source_location();
    this->create_node_label(node);
    // copy scalar arguments
    auto addr = addr_map_.at(node->id());
    uint32_t src_idx = 0;
    for (auto& src : node->srcs()) {
      auto it = scalar_map_.find(src.id());
      if (it != scalar_map_.end()) {
        auto values_ptr = jit_insn_load_relative(j_func_, this->buffer(node->type()), addr + offsetof(print_data_t, src_values), jit_type_void_ptr);
        jit_insn_store_relative(j_func_, values_ptr, src_idx * sizeof(data_t), it->second);
      }
      ++src_idx;
    }
    // call native function
    auto j_data_ptr = jit_insn_add_relative(j_func_, this->buffer(node->type()), addr);
    jit_type_t params[] = {jit_type_void_ptr};
    jit_type_t j_sig = jit_type_create_signature(jit_abi_cdecl, jit_type_void, params, __countof(params), 1);
    jit_value_t args[] = {j_data_ptr};
    jit_insn_call_native(j_func_, "print_data_t::eval", (void*)print_data_t::eval, j_sig, args, __countof(args), JIT_CALL_NOTHROW);
  }

  void allocate_nodes(context* ctx) {
    uint32_t var_addr = 0;
    uint32_t input_addr = 0;
    uint32_t output_addr = 0;

    for (auto node : ctx->nodes()) {
      uint32_t dst_width = node->size();
      auto type = node->type();
      switch (type) {
      case type_lit:
        break;
      case type_input:
        addr_map_[node->id()] = input_addr++;
        break;
      case type_output:
      case type_tap:
        addr_map_[node->id()] = output_addr++;
        break;
      case type_cd:
        addr_map_[node->id()] = var_addr;
        var_addr += __align_block(cd_data_t::size() * 8);
        break;
      case type_reg: {
        addr_map_[node->id()] = var_addr;
        auto reg = reinterpret_cast<regimpl*>(node);
        var_addr += __align_block(reg->size());
        var_addr += __align_block((reg->length() - 1) * reg->size());
      } break;
      case type_mem:
      case type_msrport:
      case type_udfs:
        addr_map_[node->id()] = var_addr;
        var_addr += __align_block(dst_width);
        break;
      case type_time: {
        addr_map_[node->id()] = var_addr;
        var_addr += __align_block(time_data_t::size() * 8);
      } break;
      case type_print: {
        addr_map_[node->id()] = var_addr;
        auto print = reinterpret_cast<printimpl*>(node);
        var_addr += __align_block(print_data_t::size(print) * 8);
      } break;
      default:
        // only allocate nodes with size bigger than WORD_SIZE bits
        if (dst_width > WORD_SIZE) {
          addr_map_[node->id()] = var_addr;
          var_addr += __align_block(dst_width);
        }
        break;
      }
    }

    {
      std::vector<const_alloc_t> constants;
      uint32_t consts_size = this->alloc_constants(ctx, constants);
      uint32_t vars_size = var_addr + consts_size;
      if (vars_size) {
        sim_ctx_->state.vars = new uint8_t[vars_size];
        if (consts_size) {
          this->init_constants(constants, var_addr, consts_size);
        }
      }
    }

    if (input_addr) {
      sim_ctx_->state.inputs = new block_type*[input_addr];
    }

    if (output_addr) {
      sim_ctx_->state.outputs = new block_type*[output_addr];
    }

    this->init_variables(ctx);
  }

  void init_variables(context* ctx) {
    for (auto node : ctx->nodes()) {
      uint32_t dst_width = node->size();
      auto type = node->type();

      switch (type) {
      case type_lit:
        break;
      case type_input: {
        auto addr = addr_map_.at(node->id());
        auto input = reinterpret_cast<inputimpl*>(node);
        sim_ctx_->state.inputs[addr] = input->value()->words();
      } break;
      case type_output:
      case type_tap: {
        auto addr = addr_map_.at(node->id());
        auto ioport = reinterpret_cast<ioportimpl*>(node);
        sim_ctx_->state.outputs[addr] = ioport->value()->words();
      } break;
      case type_cd: {
        auto addr = addr_map_.at(node->id());
        reinterpret_cast<cd_data_t*>(sim_ctx_->state.vars + addr)->init();
      } break;
      case type_reg: {
        auto addr = addr_map_.at(node->id());
        auto reg = reinterpret_cast<regimpl*>(node);
        bv_init(reinterpret_cast<block_type*>(sim_ctx_->state.vars + addr), dst_width);
        if (reg->is_pipe()) {
          // initialize the pipe
          auto pipe_addr = addr + __align_block(dst_width);
          auto pipe_size = (reg->length() - 1) * dst_width;
          bv_init(reinterpret_cast<block_type*>(sim_ctx_->state.vars + pipe_addr), pipe_size);
        }
        if (dst_width <= WORD_SIZE) {
          // preload scalar value
          __source_location();
          auto addr = addr_map_.at(node->id());
          auto j_dst = jit_insn_load_relative(j_func_, this->buffer(node->type()), addr, jit_type_ulong);
          scalar_map_[node->id()] = j_dst;
        }
      } break;
      case type_mem: {
        auto addr = addr_map_.at(node->id());
        auto mem = reinterpret_cast<memimpl*>(node);
        auto buf = reinterpret_cast<block_type*>(sim_ctx_->state.vars + addr);
        if (mem->has_init_data()) {
          bv_copy(buf, mem->init_data().words(), dst_width);
        } else {
          bv_init(buf, dst_width);
        }
      } break;
      case type_msrport:
      case type_udfs: {
        auto addr = addr_map_.at(node->id());
        bv_init(reinterpret_cast<block_type*>(sim_ctx_->state.vars + addr), dst_width);
        if (dst_width <= WORD_SIZE) {
          // preload scalar value
          __source_location();
          auto j_dst = jit_insn_load_relative(j_func_, this->buffer(node->type()), addr, jit_type_ulong);
          scalar_map_[node->id()] = j_dst;
        }
      } break;
      case type_time: {
        auto addr = addr_map_.at(node->id());
        reinterpret_cast<time_data_t*>(sim_ctx_->state.vars + addr)->init();
        // preload scalar value
        __source_location();
        auto j_dst = jit_insn_load_relative(j_func_, this->buffer(node->type()), addr, jit_type_ulong);
        scalar_map_[node->id()] = j_dst;
      } break;
      case type_print: {
        auto addr = addr_map_.at(node->id());
        auto print = reinterpret_cast<printimpl*>(node);
        reinterpret_cast<print_data_t*>(sim_ctx_->state.vars + addr)->init(print, this);
      } break;
      default:
        if (dst_width > WORD_SIZE) {
          auto addr = addr_map_.at(node->id());
          bv_init(reinterpret_cast<block_type*>(sim_ctx_->state.vars + addr), dst_width);
        }
        break;
      }
    }
  }

  uint32_t alloc_constants(context* ctx, std::vector<const_alloc_t>& constants) {
    uint32_t total_words = 0;
    for (auto node : ctx->literals()) {
      uint32_t dst_width = node->size();
      if (dst_width <= WORD_SIZE)
        continue;
      // allocate literals with size bigger than WORD_SIZE bits
      auto num_words = ceildiv<uint32_t>(dst_width, WORD_SIZE);
      bool found = false;
      for (auto& constant : constants) {
        if (constant.size >= num_words) {
          if (bv_eq(constant.data, node->value().words(), num_words * WORD_SIZE)) {
            constant.nodes.push_back(node->id());
            found = true;
            break;
          }
        } else
        if (bv_eq(constant.data, node->value().words(), constant.size * WORD_SIZE)) {
          auto buf = reinterpret_cast<block_type*>(std::realloc(constant.data, num_words * sizeof(block_type)));
          std::copy_n(node->value().words(), num_words, buf);
          total_words += (num_words - constant.size);
          constant.data = buf;
          constant.size = num_words;
          constant.nodes.push_back(node->id());
          found = true;
          break;
        }
      }
      if (!found) {
        auto buf = reinterpret_cast<block_type*>(std::malloc(num_words * sizeof(block_type)));
        std::copy_n(node->value().words(), num_words, buf);
        constants.emplace_back(buf, num_words, node->id());
        total_words += num_words;
      }
    }
    return total_words * sizeof(block_type);
  }

  void init_constants(const std::vector<const_alloc_t>& constants, uint32_t offset, uint32_t size) {
    auto buf = reinterpret_cast<block_type*>(sim_ctx_->state.vars + offset);
    auto addr = offset;
    for (auto& constant : constants) {
      std::copy_n(constant.data, constant.size, buf);
      std::free(constant.data);
      buf += constant.size;
      for (auto node_id : constant.nodes) {
        addr_map_[node_id] = addr;
      }
      addr += constant.size * sizeof(block_type);      
    }
    assert((addr - offset) == size);
  }

  jit_value_t slice_scalar_source(const jit_value_t& j_src_value, uint32_t offset) {
    auto src_lsb = offset % WORD_SIZE;
    auto j_src_lsb = jit_value_create_nint_constant(j_func_, jit_type_uint, src_lsb);
    return src_lsb ? jit_insn_ushr(j_func_, j_src_value, j_src_lsb) : j_src_value;
  }

  jit_value_t slice_vsmall_source(lnodetype type, uint32_t src_addr, uint32_t offset, uint32_t length) {
    auto src_idx = offset / WORD_SIZE;
    auto src_lsb = offset % WORD_SIZE;
    auto j_src_lsb = jit_value_create_nint_constant(j_func_, jit_type_uint, src_lsb);
    auto j_src_value0 = jit_insn_load_relative(j_func_, this->buffer(type), src_addr + src_idx * sizeof(block_type), jit_type_ulong);
    auto j_src = src_lsb ? jit_insn_ushr(j_func_, j_src_value0, j_src_lsb) : j_src_value0;
    if (src_lsb + length > WORD_SIZE) {
      auto j_src_value1 = jit_insn_load_relative(j_func_, this->buffer(type), src_addr + (src_idx + 1) * sizeof(block_type), jit_type_ulong);
      auto j_tmp1 = jit_value_create_nint_constant(j_func_, jit_type_uint, WORD_SIZE - src_lsb);
      auto j_tmp2 = jit_insn_shl(j_func_, j_src_value1, j_tmp1);
      return jit_insn_or(j_func_, j_src, j_tmp2);
    } else {
      return j_src;
    }
  }

  jit_value_t slice_scalar(const jit_value_t& j_src_value, uint32_t src_offset, uint32_t src_length) {
    auto j_src = this->slice_scalar_source(j_src_value, src_offset);
    auto j_dst_rem = jit_value_create_nint_constant(j_func_, jit_type_uint, WORD_SIZE - src_length);
    auto j_tmp1 = jit_insn_shl(j_func_, j_src, j_dst_rem);
    return jit_insn_ushr(j_func_, j_tmp1, j_dst_rem);
  }

  jit_value_t slice_vsmall(lnodetype type, uint32_t src_addr, uint32_t src_offset, uint32_t src_length) {
    auto j_src = this->slice_vsmall_source(type, src_addr, src_offset, src_length);
    auto j_dst_rem = jit_value_create_nint_constant(j_func_, jit_type_uint, WORD_SIZE - src_length);
    auto j_tmp1 = jit_insn_shl(j_func_, j_src, j_dst_rem);
    return jit_insn_ushr(j_func_, j_tmp1, j_dst_rem);
  }

  jit_value_t copy_scalar(const jit_value_t& j_dst_value,
                          uint32_t dst_offset,
                          const jit_value_t& j_src_value,
                          uint32_t src_offset,
                          uint32_t src_length) {
    auto j_src = this->slice_scalar_source(j_src_value, src_offset);
    auto j_dst_lsb = jit_value_create_nint_constant(j_func_, jit_type_uint, dst_offset);
    auto j_src_s = jit_insn_shl(j_func_, j_src, j_dst_lsb);
    auto j_mask = jit_value_create_long_constant(j_func_, jit_type_ulong, (WORD_MAX >> (WORD_SIZE - src_length)) << dst_offset);
    return this->blend(j_mask, j_dst_value, j_src_s);
  }

  void clear_extra_bits(lnodeimpl* node) {
    uint32_t dst_width = node->size();
    uint32_t extra_bits = dst_width % WORD_SIZE;
    if (0 == extra_bits)
      return;
    if (dst_width <= WORD_SIZE) {
      auto j_dst = scalar_map_.at(node->id());
      auto j_mask = jit_value_create_long_constant(j_func_, jit_type_ulong, ~(WORD_MAX << extra_bits));
      auto j_tmp = jit_insn_and(j_func_, j_dst, j_mask);
      scalar_map_[node->id()] = j_tmp;
    } else {
      CH_TODO();
    }
  }

  jit_value_t blend(const jit_value_t& mask, const jit_value_t& a, const jit_value_t& b) {
    auto j_tmp1 = jit_insn_xor(j_func_, a, b);
    auto j_tmp2 = jit_insn_and(j_func_, j_tmp1, mask);
    return jit_insn_xor(j_func_, j_tmp2, a);
  }

  jit_value_t cast(const jit_value_t& value, jit_type_t to_type) {
    if (to_type == jit_value_get_type(value))
      return value;
    auto j_ret = jit_value_create(j_func_, to_type);
    jit_insn_store(j_func_, j_ret, value);
    return j_ret;
  }

  jit_value_t buffer(lnodetype type) {
    switch (type) {
    case type_input:
      return j_inputs_;
    case type_output:
      return j_outputs_;
    default:
      return j_vars_;
    }
  }

  sim_ctx_t*      sim_ctx_;
  alloc_map_t     addr_map_;
  var_map_t       scalar_map_;
  jit_label_t     j_bypass_;
  bypass_set_t    bypass_nodes_;
  bool            bypass_enable_;
  jit_function_t  j_func_;
  jit_value_t     j_vars_;
  jit_value_t     j_inputs_;
  jit_value_t     j_outputs_;  
  jit_value_t     j_block_logsize_;
  jit_value_t     j_block_mask_;
};

///////////////////////////////////////////////////////////////////////////////

driver::driver() {
  sim_ctx_ = new sim_ctx_t();
}

driver::~driver() {
  delete sim_ctx_;
}

void driver::initialize(const std::vector<lnodeimpl*>& eval_list) {
  compiler compiler(sim_ctx_);
  compiler.build(eval_list);
}

void driver::eval() {
  (sim_ctx_->entry)(&sim_ctx_->state);
}

bool check_compatible(context* ctx) {
  auto is_scalar = [](lnodeimpl* node) {
    if (node->size() > WORD_SIZE)
      return false;
    for (auto& src : node->srcs()) {
      if (src.size() > WORD_SIZE)
        return false;
    }
    return true;
  };

  if (ctx->cdomains().size() > 1)
    return false;

  for (auto node : ctx->nodes()) {
    uint32_t dst_width = node->size();
    switch (node->type()) {
    case type_lit:
    case type_input:
    case type_output:
    case type_tap:
      break;
    case type_proxy: {
      auto proxy = reinterpret_cast<proxyimpl*>(node);
      for (auto& range : proxy->ranges()) {
        if (range.length > WORD_SIZE)
          return false;
      }
    } break;
    case type_alu: {
      auto alu = reinterpret_cast<aluimpl*>(node);
      switch (alu->op()) {
      case ch_op::eq:
      case ch_op::ne:
        if (!is_scalar(alu)
         || (-1 != alu->should_resize_opds() && alu->is_signed()))
          return false;
        break;
      case ch_op::lt:
      case ch_op::gt:
      case ch_op::le:
      case ch_op::ge:
        if (!is_scalar(alu)
         || alu->is_signed())
          return false;
        break;

      case ch_op::notl:
      case ch_op::andl:
      case ch_op::orl:
        break;

      case ch_op::inv:
        if (!is_scalar(alu)
         || (-1 != alu->should_resize_opds() && alu->is_signed()))
          return false;
        break;
      case ch_op::andb:
      case ch_op::orb:
      case ch_op::xorb:
        if ((is_scalar(alu) && -1 != alu->should_resize_opds() && alu->is_signed())
         || (!is_scalar(alu) && -1 != alu->should_resize_opds()))
          return false;
        break;

      case ch_op::andr:
      case ch_op::orr:
      case ch_op::xorr:
        return false;

      case ch_op::shl:
        if (!is_scalar(alu))
          return false;
        break;
      case ch_op::shr:
        if (!is_scalar(alu)
         || alu->is_signed())
          return false;
        break;

      case ch_op::neg:
      case ch_op::add:
      case ch_op::sub:
        if (!is_scalar(alu)
         || (-1 != alu->should_resize_opds() && alu->is_signed()))
          return false;
        break;

      case ch_op::mult:
      case ch_op::div:
      case ch_op::mod:
        if (!is_scalar(alu)
         || alu->is_signed())
          return false;
        break;

      case ch_op::pad:
        if (!is_scalar(alu)
         || alu->is_signed())
          return false;
        break;
      default:
        std::abort();
        break;
      }
    } break;
    case type_sel: {
      if (dst_width > WORD_SIZE)
        return false;
      auto sel = reinterpret_cast<selectimpl*>(node);
      if (sel->has_key()
       && sel->key().size() > WORD_SIZE)
        return false;
    } break;
    case type_reg: {
      auto reg = reinterpret_cast<regimpl*>(node);
      if (reg->is_pipe()
       && ((reg->length() - 1) * dst_width) > WORD_SIZE)
        return false;
    } break;
    case type_mem:
      break;
    case type_marport:
    case type_msrport:
      if (dst_width > WORD_SIZE)
        return false;
      break;
    case type_mwport: {
      auto mport = reinterpret_cast<memportimpl*>(node);
      if (mport->mem()->data_width() > WORD_SIZE)
        return false;
    } break;
    case type_assert:
    case type_udfc:
    case type_udfs:
      return false;
    default:
      if (dst_width > WORD_SIZE)
        return false;
      break;
    }
  }
  return true;
}

}

#endif
