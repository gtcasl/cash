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

static uint32_t to_value_size(uint32_t size) {
  uint32_t bytes = ceildiv(size, 8);
  switch (bytes) {
  case 1:
    return 8;
  case 2:
    return 16;
  case 3:
  case 4:
    return 32;
  default:
    return 64;
  }
}

static jit_type_t to_value_type(uint32_t size) {
  uint32_t bytes = ceildiv(size, 8);
  switch (bytes) {
  case 1:
    return jit_type_ubyte;
  case 2:
    return jit_type_ushort;
  case 3:
  case 4:
    return jit_type_uint;
  default:
    return jit_type_ulong;
  }
}

static uint32_t to_native_size(uint32_t size) {
  uint32_t bytes = ceildiv(size, 8);
  switch (bytes) {
  case 1:
  case 2:
  case 3:
  case 4:
    return 32;
  default:
    return 64;
  }
}

static jit_type_t to_native_type(uint32_t size) {
  uint32_t native_size = to_native_size(size);
  return to_value_type(native_size);
}

static uint32_t get_type_size(jit_type_t j_type) {
  return jit_type_get_size(j_type) * 8;
}

static uint32_t get_value_size(jit_value_t j_value) {
  auto j_type = jit_value_get_type(j_value);
  return get_type_size(j_type);
}

static void error_handler(int error_code) {
  switch (error_code) {
  case 1:
    std::cerr << "memory access out of bounds." << std::endl;
    break;
  }
  std::abort();
}

struct sim_state_t {
  block_type** ports;
  uint8_t*     vars;

  sim_state_t() : ports(nullptr), vars(nullptr) {}

  ~sim_state_t() {
    delete [] vars;
    delete [] ports;
  }
};

typedef int (*pfn_entry)(sim_state_t*);

struct sim_ctx_t {
  sim_ctx_t() : entry(nullptr) {
    j_ctx = jit_context_create();
  }

  ~sim_ctx_t() {
    if (j_ctx) {
      jit_context_build_end(j_ctx);
    }
  }

  sim_state_t state;
  pfn_entry entry;
  jit_context_t j_ctx;
};

class compiler {
public:

  compiler(sim_ctx_t* ctx)
    : sim_ctx_(ctx)
    , bypass_enable_(false)
  {}

  ~compiler() {}

  void build(const std::vector<lnodeimpl*>& eval_list) {
    // get context
    auto ctx = eval_list.back()->ctx();

    // begin build
    jit_context_build_start(sim_ctx_->j_ctx);

    // create JIT function
    this->create_function();

    // allocate objects
    this->allocate_nodes(ctx);

    // lower all nodes
    for (auto node : eval_list) {
      this->create_node_label(node);
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

    // return 0
    jit_insn_return(j_func_, this->constant(0, jit_type_int));

    // dump JIT assembly code
    if (platform::self().cflags() & cflags::dump_jit) {
      FILE* file = fopen("simjit.tac", "w");
      jit_dump_function(file, j_func_, "simjit");
      fclose(file);
    }

    // compile function
    jit_function_compile(j_func_);

    // end build
    jit_context_build_end(sim_ctx_->j_ctx);

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
        if (src.size() <= WORD_SIZE) {
          bv_init(&src_value->value, src.size());
        } else {
          auto addr = cp->addr_map_.at(src.id());
          switch (src.impl()->type()) {
          case type_input:
            src_value->ptr = cp->sim_ctx_->state.ports[addr];
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
        sdata_type value;
        for (const char *str = self->format; *str != '\0'; ++str) {
          if (*str == '{') {
            fmtinfo_t fmt;
            str = parse_format_index(&fmt, str);
            auto src_value = self->src_values[fmt.index];
            auto src_size = self->src_sizes[fmt.index];

            if (src_size > WORD_SIZE) {
              value.emplace(src_value.ptr, src_size);
            } else {
              value.emplace(&src_value.value, src_size);
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
          } else {
            strbuf.put(*str);
          }
        }
        std::cout << strbuf.rdbuf();
        value.emplace(nullptr, 0);
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
    auto sig = jit_type_create_signature(jit_abi_cdecl, jit_type_int, params, 1, 1);
    j_func_ = jit_function_create(sim_ctx_->j_ctx, sig);
    auto j_state = jit_value_get_param(j_func_, 0);
    j_vars_ = jit_insn_load_relative(j_func_, j_state, offsetof(sim_state_t, vars), jit_type_void_ptr);
    j_ports_ = jit_insn_load_relative(j_func_, j_state, offsetof(sim_state_t, ports), jit_type_void_ptr);
  }

  void emit_node(litimpl* node) {
    __source_location();

    uint32_t dst_width = node->size();
    if (dst_width <= WORD_SIZE) {
      auto j_type = to_native_type(dst_width);
      auto j_value = this->constant(node->value().word(0), j_type);
      scalar_map_[node->id()] = j_value;
    }
  }

  void emit_node(proxyimpl* node) {
    __source_location();
    assert(node->check_full());    
    uint32_t dst_width = node->size();
    if (dst_width <= WORD_SIZE) {
      auto j_type = to_native_type(dst_width);
      auto j_dst = jit_value_create(j_func_, j_type);
      scalar_map_[node->id()] = j_dst;
      for (uint i = 0, n = node->ranges().size(); i < n; ++i) {
        auto& range = node->range(i);
        auto& src = node->src(range.src_idx);
        auto j_src = this->load_slice_scalar(src.impl(), range.src_offset, range.length);
        auto jsrc_n = this->type_cast(j_src, j_type);
        if (0 == i) {
          assert(0 == range.dst_offset);
          jit_insn_store(j_func_, j_dst, jsrc_n);
        } else {
          auto j_dst_lsb = this->constant(range.dst_offset, jit_type_uint);
          auto j_src_s = jit_insn_shl(j_func_, jsrc_n, j_dst_lsb);
          auto j_tmp = jit_insn_or(j_func_, j_dst, j_src_s);
          jit_insn_store(j_func_, j_dst, j_tmp);
        }
      }
    } else {
      auto dst_addr = addr_map_.at(node->id());
      auto word_type = to_value_type(WORD_SIZE);
      auto j_dst = jit_value_create(j_func_, word_type);
      for (uint i = 0, n = node->ranges().size(); i < n; ++i) {
        auto& range = node->range(i);
        auto& src = node->src(range.src_idx);
        auto dst_idx = range.dst_offset / WORD_SIZE;
        auto dst_lsb = range.dst_offset % WORD_SIZE;
        if (range.length <= WORD_SIZE) {
          auto j_src = this->load_slice_scalar(src.impl(), range.src_offset, range.length);
          auto jsrc_w = this->type_cast(j_src, word_type);
          if (0 == dst_lsb) {
            jit_insn_store(j_func_, j_dst, jsrc_w);
          } else {
            auto j_dst_lsb = this->constant(dst_lsb, jit_type_uint);
            auto j_src_s = jit_insn_shl(j_func_, jsrc_w, j_dst_lsb);
            auto j_tmp = jit_insn_or(j_func_, j_src_s, j_dst);
            jit_insn_store(j_func_, j_dst, j_tmp);
            if (dst_lsb + range.length >= WORD_SIZE) {
              // flush current block
              jit_insn_store_relative(j_func_, j_vars_, dst_addr + dst_idx * sizeof(block_type), j_dst);
              // allocate next block
              j_dst = jit_value_create(j_func_, word_type);
              if (dst_lsb + range.length > WORD_SIZE) {
                // copy remaining bits into next block
                auto j_rem = this->constant(WORD_SIZE - dst_lsb, jit_type_uint);
                auto j_src_r = jit_insn_ushr(j_func_, j_src, j_rem);
                jit_insn_store(j_func_, j_dst, j_src_r);
              }
            }
          }
        } else {
          CH_TODO();
        }
      }
    }
  }

  void emit_node(inputimpl* node) {
    __source_location();
    uint32_t dst_width = node->size();
    uint32_t addr = addr_map_.at(node->id());
    auto j_ptr = jit_insn_load_relative(j_func_, j_ports_, addr * sizeof(block_type*), jit_type_void_ptr);
    if (dst_width <= WORD_SIZE) {
      auto j_type = to_native_type(dst_width);
      auto j_value = jit_insn_load_relative(j_func_, j_ptr, 0, j_type);
      scalar_map_[node->id()] = j_value;
    } else {
      scalar_map_[node->id()] = j_ptr;
    }
  }

  void emit_node(ioportimpl* node) {
    __source_location();
    uint32_t dst_width = node->size();
    uint32_t addr = addr_map_.at(node->id());
    auto j_dst_ptr = jit_insn_load_relative(j_func_, j_ports_, addr * sizeof(block_type*), jit_type_void_ptr);
    if (dst_width <= WORD_SIZE) {
      auto j_src_value = scalar_map_.at(node->src(0).id());
      jit_insn_store_relative(j_func_, j_dst_ptr, 0, j_src_value);
    } else {
      auto size = ceildiv(dst_width, 8);
      auto j_size = this->constant(size, jit_type_uint);
      auto j_src_ptr = this->load_address(node->src(0).impl());
      jit_insn_memcpy(j_func_, j_dst_ptr, j_src_ptr, j_size);
    }
  }

  void emit_node(aluimpl* node) {
    __source_location();
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
          auto j_src0 = this->load_scalar_elem(node->src(0).impl(), i);
          auto j_src1 = this->load_scalar_elem(node->src(1).impl(), i);
          auto j_dst  = jit_insn_and(j_func_, j_src0, j_src1);
          auto dst_addr = addr_map_.at(node->id());
          jit_insn_store_relative(j_func_, j_vars_, dst_addr + i * sizeof(block_type), j_dst);
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
          auto j_src0 = this->load_scalar_elem(node->src(0).impl(), i);
          auto j_src1 = this->load_scalar_elem(node->src(1).impl(), i);
          auto j_dst  = jit_insn_or(j_func_, j_src0, j_src1);
          auto dst_addr = addr_map_.at(node->id());
          jit_insn_store_relative(j_func_, j_vars_, dst_addr + i * sizeof(block_type), j_dst);
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
          auto j_src0 = this->load_scalar_elem(node->src(0).impl(), i);
          auto j_src1 = this->load_scalar_elem(node->src(1).impl(), i);
          auto j_dst  = jit_insn_xor(j_func_, j_src0, j_src1);
          auto dst_addr = addr_map_.at(node->id());
          jit_insn_store_relative(j_func_, j_vars_, dst_addr + i * sizeof(block_type), j_dst);
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
        auto dst_type = to_value_type(dst_width);
        auto j_src0_c = this->type_cast(j_src0, dst_type);
        auto j_dst  = jit_insn_shl(j_func_, j_src0_c, j_src1);
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
    jit_label_t l_exit = jit_label_undefined;

    uint32_t dst_width = node->size();
    if (dst_width <= WORD_SIZE) {
      auto j_type = to_native_type(dst_width);
      auto j_dst = jit_value_create(j_func_, j_type);
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
    auto addr = addr_map_.at(node->id());
    auto j_prev_clk = jit_insn_load_relative(j_func_, j_vars_, addr, jit_type_uint);
    auto j_clk = scalar_map_.at(node->src(0).id());
    auto j_clk_changed = jit_insn_xor(j_func_, j_clk, j_prev_clk);
    jit_value_t j_changed ;
    if (node->pos_edge()) {
      j_changed = jit_insn_and(j_func_, j_clk_changed, j_clk);
    } else {
      auto j_clk_n = jit_insn_not(j_func_, j_clk);
      j_changed = jit_insn_and(j_func_, j_clk_changed, j_clk_n);
    }
    jit_insn_store_relative(j_func_, j_vars_, addr, j_clk);

    bool bypass_enable = ch::internal::compiler::build_bypass_list(
          bypass_nodes_, node->ctx(), node->id());
    if (bypass_enable) {
      bypass_enable_ = true;
      jit_label_t j_label = jit_label_undefined;
      jit_insn_branch_if_not(j_func_, j_changed, &j_label);
      j_bypass_ = j_label;
    } else {
      scalar_map_[node->id()] = j_changed;
    }
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
    jit_label_t l_exit = jit_label_undefined;

    auto dst_addr = addr_map_.at(node->id());
    uint32_t dst_width = node->size();

    if (!bypass_enable_) {
      auto j_cd = scalar_map_.at(node->cd().id());
      jit_insn_branch_if_not(j_func_, j_cd, &l_exit);
    }

    if (node->is_pipe()) {
      uint32_t pipe_width = (node->length() - 1) * dst_width;
      auto pipe_type = to_native_type(pipe_width);
      auto pipe_addr = dst_addr + sizeof(block_type);
      bool is_scalar = (pipe_width <= WORD_SIZE);
      if (node->has_init_data()) {
        jit_label_t l_skip = jit_label_undefined;
        auto j_reset = scalar_map_.at(node->reset().id());        
        jit_insn_branch_if_not(j_func_, j_reset, &l_skip);
        if (is_scalar) {
          // reset pipe
          if (type_lit == node->init_data().impl()->type()) {
            auto lit = reinterpret_cast<litimpl*>(node->init_data().impl());
            block_type init_data(0);
            block_type init_value = lit->value().word(0);
            for (uint32_t i = 0, n = node->length() - 1; i < n; ++i) {
              init_data |= init_value << (i * dst_width);
            }
            auto j_init_data = this->constant(init_data, pipe_type);
            jit_insn_store_relative(j_func_, j_vars_, pipe_addr, j_init_data);
          } else {
            CH_TODO();
          }
          // reset base register
          auto j_init_data = scalar_map_.at(node->init_data().id());
          auto j_dst = scalar_map_.at(node->id());
          jit_insn_store(j_func_, j_dst, j_init_data);
          jit_insn_store_relative(j_func_, j_vars_, dst_addr, j_init_data);
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
        // dst <- pipe[0]
        auto j_pipe = jit_insn_load_relative(j_func_, j_vars_, pipe_addr, pipe_type);
        auto j_pipe_0 = this->load_slice_scalar(j_pipe, 0, dst_width);
        jit_insn_store_relative(j_func_, j_vars_, dst_addr, j_pipe_0);
        auto j_dst = scalar_map_.at(node->id());
        jit_insn_store(j_func_, j_dst, j_pipe_0);

        // pipe >>= dst_width
        auto j_shift = this->constant(dst_width, jit_type_uint);
        auto j_pipe_s = jit_insn_ushr(j_func_, j_pipe, j_shift);

        // pipe[n-1] <- next
        auto j_next = scalar_map_.at(node->next().id());
        auto j_shfn1 = this->constant((node->length() - 2) * dst_width, jit_type_uint);
        auto j_next_s = jit_insn_shl(j_func_, j_next, j_shfn1);
        auto j_pipe_n1 = jit_insn_or(j_func_, j_next_s, j_pipe_s);
        jit_insn_store_relative(j_func_, j_vars_, pipe_addr, j_pipe_n1);
      } else {
        CH_TODO();
      }
    } else {
      bool is_scalar = (dst_width <= WORD_SIZE);
      if (node->has_init_data()) {
        jit_label_t l_skip = jit_label_undefined;
        auto j_reset = scalar_map_.at(node->reset().id());
        jit_insn_branch_if_not(j_func_, j_reset, &l_skip);
        if (is_scalar) {
          auto j_init_data = scalar_map_.at(node->init_data().id());
          auto j_dst = scalar_map_.at(node->id());
          jit_insn_store(j_func_, j_dst, j_init_data);
          jit_insn_store_relative(j_func_, j_vars_, dst_addr, j_init_data);
        } else {
          auto size = ceildiv(dst_width, 8);
          auto j_size = this->constant(size, jit_type_uint);
          auto j_init_ptr = this->load_address(node->init_data().impl());
          auto j_dst_ptr = jit_insn_add_relative(j_func_, j_vars_, dst_addr);
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
        jit_insn_store_relative(j_func_, j_vars_, dst_addr, j_next);
        auto j_dst = scalar_map_.at(node->id());
        jit_insn_store(j_func_, j_dst, j_next);
      } else {
        auto size = ceildiv(dst_width, 8);
        auto j_size = this->constant(size, jit_type_uint);
        auto j_next_ptr = this->load_address(node->next().impl());
        auto j_dst_ptr = jit_insn_add_relative(j_func_, j_vars_, dst_addr);
        jit_insn_memcpy(j_func_, j_dst_ptr, j_next_ptr, j_size);
      }
    }

    jit_insn_label(j_func_, &l_exit);
  }

  void emit_node(marportimpl* node) {
    __source_location();
    auto dst_width = node->size();
    if (dst_width <= WORD_SIZE) {
      auto j_src_addr = scalar_map_.at(node->addr().id());
    #ifndef NDEBUG
      this->check_range(j_src_addr, 0, node->mem()->num_items());
    #endif
      jit_value_t j_src = this->load_array_scalar(node->mem(), j_src_addr, dst_width);
      scalar_map_[node->id()] = j_src;
    } else {
      CH_TODO();
    }
  }

  void emit_node(msrportimpl* node) {
    __source_location();
    jit_label_t l_exit = jit_label_undefined;
    auto dst_addr = addr_map_.at(node->id());
    auto dst_width = node->size();

    auto predicated = node->has_enable() || !bypass_enable_;
    if (predicated) {
      jit_value_t j_predicate = nullptr;
      if (node->has_enable()) {
        j_predicate = scalar_map_.at(node->enable().id());
      }
      if (!bypass_enable_) {
        auto j_cd = scalar_map_.at(node->cd().id());
        if (j_predicate) {
          auto j_tmp = jit_insn_and(j_func_, j_predicate, j_cd);
          jit_insn_store(j_func_, j_predicate, j_tmp);
        } else {
          j_predicate = j_cd;
        }
      }
      jit_insn_branch_if_not(j_func_, j_predicate, &l_exit);
    }

    if (dst_width <= WORD_SIZE) {
      auto j_src_addr = scalar_map_.at(node->addr().id());
    #ifndef NDEBUG
      this->check_range(j_src_addr, 0, node->mem()->num_items());
    #endif
      jit_value_t j_src = this->load_array_scalar(node->mem(), j_src_addr, dst_width);      
      jit_insn_store_relative(j_func_, j_vars_, dst_addr, j_src);
      auto j_dst = scalar_map_.at(node->id());
      jit_insn_store(j_func_, j_dst, j_src);
    } else {
      CH_TODO();
    }

    if (predicated) {
      jit_insn_label(j_func_, &l_exit);
    }
  }

  void emit_node(mwportimpl* node) {
    __source_location();
    jit_label_t l_exit = jit_label_undefined;
    auto data_width = node->mem()->data_width();

    auto predicated = node->has_enable() || !bypass_enable_;
    if (predicated) {
      jit_value_t j_predicate = nullptr;
      if (node->has_enable()) {
        j_predicate = scalar_map_.at(node->enable().id());
      }
      if (!bypass_enable_) {
        auto j_cd = scalar_map_.at(node->cd().id());
        if (j_predicate) {
          auto j_tmp = jit_insn_and(j_func_, j_predicate, j_cd);
          jit_insn_store(j_func_, j_predicate, j_tmp);
        } else {
          j_predicate = j_cd;
        }
      }
      jit_insn_branch_if_not(j_func_, j_predicate, &l_exit);
    }

    if (data_width <= WORD_SIZE) {      
      auto j_dst_addr = scalar_map_.at(node->addr().id());
    #ifndef NDEBUG
      this->check_range(j_dst_addr, 0, node->mem()->num_items());
    #endif
      auto j_wdata = this->load_slice_scalar(node->wdata().impl(), 0, data_width);
      this->store_array_scalar(node->mem(), j_dst_addr, data_width, j_wdata);
    } else {
      CH_TODO();
    }

    if (predicated) {
      jit_insn_label(j_func_, &l_exit);
    }
  }

  void emit_node(timeimpl* node) {
    __source_location();
    auto addr = addr_map_.at(node->id());
    auto j_value = scalar_map_.at(node->id());
    auto j_one = this->constant(1, jit_type_ulong);
    auto j_incr = jit_insn_add(j_func_, j_value, j_one);
    jit_insn_store_relative(j_func_, j_vars_, addr, j_incr);
  }

  void emit_node(printimpl* node) {
    __source_location();
    // copy scalar arguments
    auto addr = addr_map_.at(node->id());
    uint32_t src_idx = 0;
    for (auto& src : node->srcs()) {
      auto it = scalar_map_.find(src.id());
      if (it != scalar_map_.end()) {
        auto values_ptr = jit_insn_load_relative(j_func_,
                                                 j_vars_,
                                                 addr + offsetof(print_data_t, src_values),
                                                 jit_type_void_ptr);
        jit_insn_store_relative(j_func_, values_ptr, src_idx * sizeof(data_t), it->second);
      }
      ++src_idx;
    }
    // call native function
    auto j_data_ptr = jit_insn_add_relative(j_func_, j_vars_, addr);
    jit_type_t params[] = {jit_type_void_ptr};
    jit_type_t j_sig = jit_type_create_signature(jit_abi_cdecl,
                                                 jit_type_void,
                                                 params,
                                                 __countof(params),
                                                 1);
    jit_value_t args[] = {j_data_ptr};
    jit_insn_call_native(j_func_,
                         "print_data_t::eval",
                         (void*)print_data_t::eval,
                         j_sig,
                         args,
                         __countof(args),
                         JIT_CALL_NOTHROW);
  }

  void allocate_nodes(context* ctx) {
    uint32_t var_addr = 0;
    uint32_t port_addr = 0;

    for (auto node : ctx->nodes()) {
      uint32_t dst_width = node->size();
      auto type = node->type();
      switch (type) {
      case type_lit:
        break;
      case type_input:
      case type_output:
      case type_tap:
        addr_map_[node->id()] = port_addr++;
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

    if (port_addr) {
      sim_ctx_->state.ports = new block_type*[port_addr];
    }

    this->init_variables(ctx);
  }

  void init_variables(context* ctx) {
    for (auto node : ctx->nodes()) {
      uint32_t dst_width = node->size();
      auto j_type = to_native_type(dst_width);
      auto type = node->type();

      switch (type) {
      case type_lit:
        break;
      case type_input:
      case type_output:
      case type_tap: {
        auto addr = addr_map_.at(node->id());
        auto ioport = reinterpret_cast<ioportimpl*>(node);
        sim_ctx_->state.ports[addr] = ioport->value()->words();
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
          auto j_dst = jit_insn_load_relative(j_func_, j_vars_, addr, j_type);
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
          auto j_dst = jit_insn_load_relative(j_func_, j_vars_, addr, j_type);
          scalar_map_[node->id()] = j_dst;
        }
      } break;
      case type_time: {
        auto addr = addr_map_.at(node->id());
        reinterpret_cast<time_data_t*>(sim_ctx_->state.vars + addr)->init();
        // preload scalar value
        __source_location();
        auto j_dst = jit_insn_load_relative(j_func_, j_vars_, addr, jit_type_ulong);
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
      auto num_words = ceildiv(dst_width, WORD_SIZE);
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

  void init_constants(const std::vector<const_alloc_t>& constants,
                      uint32_t offset,
                      uint32_t size) {
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
  #ifndef NDEBUG
    assert((addr - offset) == size);
  #else
    CH_UNUSED(size);
  #endif
  }

  jit_value_t load_slice_scalar(jit_value_t j_value, uint32_t offset, uint32_t length) {
    __source_location();
    assert(length <= WORD_SIZE);
    assert(offset < WORD_SIZE);

    jit_value_t j_src;
    if (offset) {
      auto j_offset = this->constant(offset, jit_type_uint);
      j_src = jit_insn_ushr(j_func_, j_value, j_offset);
    } else {
      j_src = j_value;
    }      
    int clamp = get_value_size(j_src) - length;
    if (clamp) {
      assert(clamp > 0);
      auto j_clamp = this->constant(clamp, jit_type_uint);
      auto j_tmp = jit_insn_shl(j_func_, j_src, j_clamp);
      return jit_insn_ushr(j_func_, j_tmp, j_clamp);
    } else {
      return j_src;
    }
  }

  jit_value_t load_slice_scalar(lnodeimpl* node, uint32_t offset, uint32_t length) {
    __source_location();
    assert(length <= WORD_SIZE);
    auto j_type = to_native_type(length);
    uint32_t src_width = node->size();
    if (src_width != length) {
      if (src_width <= WORD_SIZE) {
        auto j_src_value = scalar_map_.at(node->id());
        return this->load_slice_scalar(j_src_value, offset, length);
      } else {
        auto src_lsb8 = offset % 8;
        auto src_end8 = src_lsb8 + length;
        if (0 == src_lsb8) {
          auto src_idx = offset / 8;
          auto j_src_value = this->load_scalar_relative(node, src_idx, j_type);
          return this->load_slice_scalar(j_src_value, 0, length);
        } else
        if (src_end8 <= WORD_SIZE) {
          auto value_size = to_value_size(src_end8);
          auto src_idx = ceildiv(offset + length, 8) - value_size / 8;
          auto src_lsb = offset - src_idx * 8;
          auto j_src_value = this->load_scalar_relative(node, src_idx, to_value_type(value_size));
          auto j_src_value_c = this->load_slice_scalar(j_src_value, src_lsb, length);
          return this->type_cast(j_src_value_c, j_type);
        } else {
          auto src_idx = offset / WORD_SIZE;
          auto src_lsb = offset % WORD_SIZE;
          auto j_src_lsb = this->constant(src_lsb, jit_type_uint);
          auto j_src_value0 = this->load_scalar_relative(node, src_idx * sizeof(block_type), to_value_type(WORD_SIZE));
          auto j_src_value0_s = jit_insn_ushr(j_func_, j_src_value0, j_src_lsb);
          auto j_src_value0_n = this->type_cast(j_src_value0_s, j_type);
          auto j_src_value1 = this->load_scalar_relative(node, (src_idx + 1) * sizeof(block_type), j_type);
          auto j_rem = this->constant(get_value_size(j_src_value1) - src_lsb, jit_type_uint);
          auto j_src_value1_s = jit_insn_shl(j_func_, j_src_value1, j_rem);
          auto j_src_value = jit_insn_or(j_func_, j_src_value1_s, j_src_value0_n);
          return this->load_slice_scalar(j_src_value, 0, length);
        }
      }
    } else {
      return scalar_map_.at(node->id());
    }
  }

  jit_value_t load_array_scalar(lnodeimpl* array,
                                jit_value_t j_index,
                                uint32_t length) {
    __source_location();
    assert(length <= WORD_SIZE);
    auto j_type = to_native_type(length);
    uint32_t array_width = array->size();
    auto array_addr = addr_map_.at(array->id());

    if (0 == (length % 8)) {
      auto j_array_ptr = jit_insn_add_relative(j_func_, j_vars_, array_addr);
      auto j_src_value = jit_insn_load_elem(j_func_, j_array_ptr, j_index, to_value_type(length));
      return this->type_cast(j_src_value, j_type);
    } else {
      auto word_type = to_value_type(WORD_SIZE);
      auto j_data_size = this->constant(length, jit_type_uint);
      auto j_src_offset = jit_insn_mul(j_func_, j_index, j_data_size);
      jit_value_t j_src;
      if (array_width <= WORD_SIZE) {
        auto j_src_value = jit_insn_load_relative(j_func_, j_vars_, array_addr, word_type);
        j_src = jit_insn_ushr(j_func_, j_src_value, j_src_offset);
      } else {
        auto j_block_logsize = this->constant(WORD_LOGSIZE, jit_type_uint);
        auto j_block_mask = this->constant(WORD_MASK, jit_type_uint);
        auto j_src_idx = jit_insn_ushr(j_func_, j_src_offset, j_block_logsize);
        auto j_src_lsb = jit_insn_and(j_func_, j_src_offset, j_block_mask);

        auto j_array_ptr = jit_insn_add_relative(j_func_, j_vars_, array_addr);
        auto j_src_ptr = jit_insn_load_elem_address(j_func_, j_array_ptr, j_src_idx, word_type);
        auto j_src_value0 = jit_insn_load_relative(j_func_, j_src_ptr, 0, word_type);
        j_src = jit_insn_ushr(j_func_, j_src_value0, j_src_lsb);

        jit_label_t l_skip = jit_label_undefined;
        auto j_src_rem = this->constant(WORD_SIZE - length, jit_type_uint);
        auto j_src_inclusive = jit_insn_le(j_func_, j_src_lsb, j_src_rem);
        jit_insn_branch_if(j_func_, j_src_inclusive, &l_skip);

        auto j_src_n = this->type_cast(j_src, j_type);
        auto j_src_value1 = jit_insn_load_relative(j_func_, j_src_ptr, sizeof(block_type), j_type);
        auto j_block_size = this->constant(get_value_size(j_src_value1), jit_type_uint);
        auto j_tmp1 = jit_insn_sub(j_func_, j_block_size, j_src_lsb);
        auto j_tmp2 = jit_insn_shl(j_func_, j_src_value1, j_tmp1);
        auto j_tmp3 = jit_insn_or(j_func_, j_src_n, j_tmp2);
        jit_insn_store(j_func_, j_src, j_tmp3);

        jit_insn_label(j_func_, &l_skip);
      }
      int clamp = get_value_size(j_src) - length;
      if (clamp) {
        assert(clamp > 0);
        auto j_clamp = this->constant(clamp, jit_type_uint);
        auto j_tmp1 = jit_insn_shl(j_func_, j_src, j_clamp);
        auto j_tmp2 = jit_insn_ushr(j_func_, j_tmp1, j_clamp);
        jit_insn_store(j_func_, j_src, j_tmp2);
      }
      return this->type_cast(j_src, j_type);
    }
  }

  void store_array_scalar(lnodeimpl* array,
                          jit_value_t j_index,
                          uint32_t length,
                          jit_value_t j_data) {
    __source_location();
    assert(length <= WORD_SIZE);
    uint32_t array_width = array->size();
    auto array_addr = addr_map_.at(array->id());

    if (0 == (length % 8)) {
      auto j_array_ptr = jit_insn_add_relative(j_func_, j_vars_, array_addr);
      auto j_wdata_n = this->type_cast(j_data, to_value_type(length));
      jit_insn_store_elem(j_func_, j_array_ptr, j_index, j_wdata_n);
    } else {
      auto word_type = to_value_type(WORD_SIZE);
      auto j_data_w = this->type_cast(j_data, word_type);
      auto j_data_size = this->constant(length, jit_type_uint);
      auto j_dst_offset = jit_insn_mul(j_func_, j_index, j_data_size);

      if (array_width <= WORD_SIZE) {
        auto j_dst_value = jit_insn_load_relative(j_func_, j_vars_, array_addr, word_type);
        auto j_mask = this->constant(WORD_MAX >> (WORD_SIZE - length), word_type);
        auto j_mask_s = jit_insn_shl(j_func_, j_mask, j_dst_offset);
        auto j_data_s = jit_insn_shl(j_func_, j_data_w, j_dst_offset);
        auto j_dst = this->blend(j_mask_s, j_dst_value, j_data_s);
        jit_insn_store_relative(j_func_, j_vars_, array_addr, j_dst);
      } else {
        auto j_block_logsize = this->constant(WORD_LOGSIZE, jit_type_uint);
        auto j_block_mask = this->constant(WORD_MASK, jit_type_uint);
        auto j_dst_idx = jit_insn_ushr(j_func_, j_dst_offset, j_block_logsize);
        auto j_dst_lsb = jit_insn_and(j_func_, j_dst_offset, j_block_mask);

        auto j_array_ptr = jit_insn_add_relative(j_func_, j_vars_, array_addr);
        auto j_dst_ptr = jit_insn_load_elem_address(j_func_, j_array_ptr, j_dst_idx, word_type);
        auto j_dst_value0 = jit_insn_load_relative(j_func_, j_dst_ptr, 0, word_type);
        auto j_mask0 = this->constant(WORD_MAX >> (WORD_SIZE - length), word_type);
        auto j_mask0_s = jit_insn_shl(j_func_, j_mask0, j_dst_lsb);
        auto j_data0_s = jit_insn_shl(j_func_, j_data_w, j_dst_lsb);
        auto j_dst0 = this->blend(j_mask0_s, j_dst_value0, j_data0_s);
        jit_insn_store_relative(j_func_, j_dst_ptr, 0, j_dst0);

        jit_label_t l_skip = jit_label_undefined;
        auto j_dst_rem = this->constant(WORD_SIZE - length, jit_type_uint);
        auto j_dst_inclusive = jit_insn_le(j_func_, j_dst_lsb, j_dst_rem);
        jit_insn_branch_if(j_func_, j_dst_inclusive, &l_skip);

        auto j_dst_value1 = jit_insn_load_relative(j_func_, j_dst_ptr, sizeof(block_type), word_type);
        auto j_mask1 = jit_insn_not(j_func_, j_mask0_s);
        auto j_mask1_s = jit_insn_ushr(j_func_, j_mask1, j_dst_rem);
        auto j_data1_s = jit_insn_ushr(j_func_, j_data_w, j_dst_rem);
        auto j_dst1 = this->blend(j_mask1_s, j_dst_value1, j_data1_s);
        jit_insn_store_relative(j_func_, j_dst_ptr, sizeof(block_type), j_dst1);

        jit_insn_label(j_func_, &l_skip);
      }
    }
  }

  void clear_extra_bits(lnodeimpl* node) {    
    __source_location();
    uint32_t dst_width = node->size();
    auto j_type = to_native_type(dst_width);
    auto native_size = to_native_size(dst_width);
    uint32_t extra_bits = dst_width % native_size;
    if (0 == extra_bits)
      return;
    if (dst_width <= native_size) {
      auto j_dst = scalar_map_.at(node->id());
      auto j_mask = this->constant(~(WORD_MAX << extra_bits), j_type);
      auto j_tmp = jit_insn_and(j_func_, j_dst, j_mask);
      scalar_map_[node->id()] = j_tmp;
    } else {
      CH_TODO();
    }
  }

  jit_value_t load_address(lnodeimpl* node, uint32_t offset = 0) {
    switch (node->type()) {
    case type_input: {
      auto j_ptr = scalar_map_.at(node->id());
      return offset ? jit_insn_add_relative(j_func_, j_ptr, offset) : j_ptr;
    }
    default: {
      auto addr = addr_map_.at(node->id()) + offset;
      return addr ? jit_insn_add_relative(j_func_, j_vars_, addr) : j_vars_;
    }}
  }

  jit_value_t load_scalar_relative(lnodeimpl* node, uint32_t offset, jit_type_t j_type) {
    switch (node->type()) {
    case type_input: {
      auto j_ptr = scalar_map_.at(node->id());
      return jit_insn_load_relative(j_func_, j_ptr, offset, j_type);
    }
    default: {
      auto addr = addr_map_.at(node->id()) + offset;
      return jit_insn_load_relative(j_func_, j_vars_, addr, j_type);
    }}
  }

  jit_value_t load_scalar_elem(lnodeimpl* node, uint32_t index) {
    auto j_type = to_native_type(node->size());
    auto size_in_bytes = get_type_size(j_type) / 8;
    return this->load_scalar_relative(node, index * size_in_bytes, j_type);
  }

  jit_value_t blend(jit_value_t mask, jit_value_t a, jit_value_t b) {
    auto j_tmp1 = jit_insn_xor(j_func_, a, b);
    auto j_tmp2 = jit_insn_and(j_func_, j_tmp1, mask);
    return jit_insn_xor(j_func_, j_tmp2, a);
  }

  jit_value_t type_cast(jit_value_t value, jit_type_t to_type) {
    auto from_kind = jit_type_get_kind(jit_value_get_type(value));
    auto to_kind = jit_type_get_kind(to_type);
    if (from_kind == to_kind)
      return value;
    auto j_ret = jit_value_create(j_func_, to_type);
    jit_insn_store(j_func_, j_ret, value);
    return j_ret;
  }

  void check_range(jit_value_t j_value, uint32_t start, uint32_t end) {
    auto j_start = this->constant(start, jit_type_uint);
    auto j_end = this->constant(end, jit_type_uint);
    auto j_check1 = jit_insn_ge(j_func_, j_value, j_start);
    auto j_check2 = jit_insn_lt(j_func_, j_value, j_end);
    auto j_check = jit_insn_and(j_func_, j_check1, j_check2);
    jit_label_t l_skip = jit_label_undefined;
    jit_insn_branch_if(j_func_, j_check, &l_skip);
    jit_insn_return(j_func_, this->constant(1, jit_type_int)); // return 1
    jit_insn_label(j_func_, &l_skip);
  }

  jit_value_t constant(long value, jit_type_t j_type) {
    auto size = jit_type_get_size(j_type);
    if (size <= 4) {
      return jit_value_create_nint_constant(j_func_, j_type, value);
    } else if (size <= 8) {
      return jit_value_create_long_constant(j_func_, j_type, value);
    } else {
      std::abort();
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
  jit_value_t     j_ports_;
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
  int ret = (sim_ctx_->entry)(&sim_ctx_->state);
  if (ret) {
    error_handler(ret);
  }
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

  auto error_out = [](const char* msg) {    
    DBG(2, "warning: JIT not supported, %s", msg);
    CH_UNUSED(msg);
    return false;
  };

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
          return error_out("proxy ranges size too big");
      }
    } break;
    case type_alu: {
      auto alu = reinterpret_cast<aluimpl*>(node);
      switch (alu->op()) {
      case ch_op::eq:
      case ch_op::ne:
        if (!is_scalar(alu)
         || (-1 != alu->should_resize_opds() && alu->is_signed()))
          return error_out("invalid alu size");
        break;
      case ch_op::lt:
      case ch_op::gt:
      case ch_op::le:
      case ch_op::ge:
        if (!is_scalar(alu)
         || alu->is_signed())
          return error_out("invalid alu size");
        break;

      case ch_op::notl:
      case ch_op::andl:
      case ch_op::orl:
        break;

      case ch_op::inv:
        if (!is_scalar(alu)
         || (-1 != alu->should_resize_opds() && alu->is_signed()))
          return error_out("invalid alu size");
        break;
      case ch_op::andb:
      case ch_op::orb:
      case ch_op::xorb:
        if ((is_scalar(alu) && -1 != alu->should_resize_opds() && alu->is_signed())
         || (!is_scalar(alu) && -1 != alu->should_resize_opds()))
          return error_out("invalid alu size");
        break;

      case ch_op::andr:
      case ch_op::orr:
      case ch_op::xorr:
        return error_out("invalid alu type");

      case ch_op::shl:
        if (!is_scalar(alu))
          return error_out("invalid alu size");
        break;
      case ch_op::shr:
        if (!is_scalar(alu)
         || alu->is_signed())
          return error_out("invalid alu size");
        break;

      case ch_op::neg:
      case ch_op::add:
      case ch_op::sub:
        if (!is_scalar(alu)
         || (-1 != alu->should_resize_opds() && alu->is_signed()))
          return error_out("invalid alu size");
        break;

      case ch_op::mult:
      case ch_op::div:
      case ch_op::mod:
        if (!is_scalar(alu)
         || alu->is_signed())
          return error_out("invalid alu size");
        break;

      case ch_op::pad:
        if (!is_scalar(alu)
         || alu->is_signed())
          return error_out("invalid alu size");
        break;
      default:
        std::abort();
        break;
      }
    } break;
    case type_sel: {
      if (dst_width > WORD_SIZE)
        return error_out("invalid select size");
      auto sel = reinterpret_cast<selectimpl*>(node);
      if (sel->has_key()
       && sel->key().size() > WORD_SIZE)
        return error_out("invalid case key size");
    } break;
    case type_reg: {
      auto reg = reinterpret_cast<regimpl*>(node);
      if (reg->is_pipe()) {
       if (((reg->length() - 1) * dst_width) > WORD_SIZE)
          return error_out("invalid pipe size");
       if (reg->has_init_data()
        && type_lit != reg->init_data().impl()->type())
         return error_out("invalid pipe init data");
      }
    } break;
    case type_mem:
      break;
    case type_marport:
    case type_msrport:
      if (dst_width > WORD_SIZE)
        return error_out("invalid port size");
      break;
    case type_mwport: {
      auto mport = reinterpret_cast<memportimpl*>(node);
      if (mport->mem()->data_width() > WORD_SIZE)
        return error_out("invalid port size");
    } break;
    case type_assert:
    case type_udfc:
    case type_udfs:
      return error_out("invalid node type");
    default:
      if (dst_width > WORD_SIZE)
        return error_out("invalid node size");
      break;
    }
  }
  return true;
}

}

#endif
