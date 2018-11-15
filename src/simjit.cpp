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

#define __align_word_size(...) ((((__VA_ARGS__) + WORD_MASK) / WORD_SIZE) * sizeof(block_type))
#define __countof(arr) (sizeof(arr) / sizeof(arr[0]))
#define __source_location() jit_insn_mark_offset(j_func_, __LINE__)

#define __alu_call_relational(fname, ...) \
  [&]()->jit_value_t { \
    void* pfn; \
    if (is_signed) { \
      if (is_resize) { \
        pfn = reinterpret_cast<void*>(fname<true, block_type, StaticBitAccessor<true, true, block_type>>); \
      } else { \
        pfn = reinterpret_cast<void*>(fname<true, block_type, StaticBitAccessor<true, false, block_type>>); \
      } \
    } else { \
      if (is_resize) { \
        pfn = reinterpret_cast<void*>(fname<false, block_type, StaticBitAccessor<false, true, block_type>>); \
      } else { \
        pfn = reinterpret_cast<void*>(fname<false, block_type, StaticBitAccessor<false, false, block_type>>); \
      } \
    } \
    return this->emit_alu_call_relational(pfn, #fname, __VA_ARGS__); \
  }()

static uint32_t to_value_size(uint32_t size) {
  uint32_t bytes = ceildiv(size, 8);
  switch (bytes) {
  case 0:
    return 0;
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

static bool is_value_size(uint32_t size) {
  switch (size) {
  case 8:
  case 16:
  case 32:
  case 64:
    return true;
  default:
    return false;
  }
}

static jit_type_t to_value_type(uint32_t size) {
  uint32_t bytes = ceildiv(size, 8);
  switch (bytes) {
  case 0:
    return jit_type_void;
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
  case 0:
    return 0;
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
  uint32_t nbytes = jit_type_get_size(j_type);
  return nbytes * 8;
}

static uint32_t get_value_size(jit_value_t j_value) {
  auto j_type = jit_value_get_type(j_value);
  return get_type_size(j_type);
}

static bool is_signed_type(jit_type_t j_type) {
  auto kind = jit_type_get_kind(j_type);
  switch (kind) {
  case JIT_TYPE_SBYTE:
  case JIT_TYPE_SHORT:
  case JIT_TYPE_INT:
  case JIT_TYPE_LONG:
    return true;
  default:
    return false;
  }
}

static jit_type_t to_signed_type(jit_type_t j_type) {
  auto kind = jit_type_get_kind(j_type);
  switch (kind) {
  case JIT_TYPE_UBYTE:
  case JIT_TYPE_SBYTE:
    return jit_type_sbyte;
  case JIT_TYPE_USHORT:
  case JIT_TYPE_SHORT:
    return jit_type_short;
  case JIT_TYPE_UINT:
  case JIT_TYPE_INT:
    return jit_type_int;
  case JIT_TYPE_ULONG:
  case JIT_TYPE_LONG:
    return jit_type_long;
  default:
    std::abort();
  }
}

#ifndef NDEBUG
static void ext_watch(uint64_t value, char* name) {
  auto oldflags = std::cout.flags();
  std::cout.setf(std::ios_base::hex, std::ios_base::basefield);
  std::cout << "DBG:" << name << " = " << value << std::endl;
  std::cout.flags(oldflags);
}
#define __watch(x) this->emit_watch(x, #x)
#endif

static void error_handler(int error_code) {
  switch (error_code) {
  case 1:
    std::cerr << "memory access out of bounds." << std::endl;
    break;
  }
  std::abort();
}

static void ext_copy_vector(block_type* dst,
                            uint32_t dst_offset,
                            const block_type* src,
                            uint32_t src_offset,
                            uint32_t length) {
  assert(length > WORD_SIZE);

  auto w_dst_idx = dst_offset / WORD_SIZE;
  auto w_dst_lsb = dst_offset % WORD_SIZE;
  auto w_src_idx = src_offset / WORD_SIZE;
  auto w_src_lsb = src_offset % WORD_SIZE;
  bv_copy_vector(dst + w_dst_idx, w_dst_lsb, src + w_src_idx, w_src_lsb, length);
}

struct sim_state_t {
  block_type** ports;
  uint8_t* vars;
#ifndef NDEBUG
  char* dbg;
#endif

  sim_state_t()
    : ports(nullptr)
    , vars(nullptr)
  #ifndef NDEBUG
    , dbg(nullptr)
  #endif
  {}

  ~sim_state_t() {
    delete [] vars;
    delete [] ports;
  #ifndef NDEBUG
    delete [] dbg;
  #endif
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
    , word_type_(to_value_type(WORD_SIZE))
  #ifndef NDEBUG
    , dbg_off_(0)
  #endif
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
        this->emit_node(reinterpret_cast<assertimpl*>(node));
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
    jit_insn_return(j_func_, j_zero_);

    // dump JIT assembly code
    if (platform::self().cflags() & cflags::dump_jit) {
      auto file = fopen("simjit.tac", "w");
      jit_dump_function(file, j_func_, "simjit");
      fclose(file);
    }

    // compile function
    jit_function_compile(j_func_);

    // end build
    jit_context_build_end(sim_ctx_->j_ctx);

    // dump JIT assembly code
    if (platform::self().cflags() & cflags::dump_asm) {
      auto file = fopen("simjit.asm", "w");
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

  struct data_t {
    block_type* value;
    uint32_t size;

    void  init(lnodeimpl* node, const compiler* cp) {
      auto it = cp->addr_map_.find(node->id());
      if (it != cp->addr_map_.end()) {
        auto addr = it->second;
        switch (node->type()) {
        case type_input:
          value = cp->sim_ctx_->state.ports[addr];
          break;
        default:
          value = reinterpret_cast<block_type*>(cp->sim_ctx_->state.vars + addr);
          break;
        }
      }
      size = node->size();
    }
  };

  struct eval_data_t {
    eval_data_t(data_t& data) {
      value.emplace(data.value, data.size);
    }
    ~eval_data_t() {
      value.emplace(nullptr, 0);
    }
    sdata_type value;
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
    char* format;
    enum_string_cb* enum_strings;
    data_t* src_values;

    static uint32_t size(printimpl* node) {
      auto num_srcs = node->srcs().size() + (node->has_pred() ? -1 : 0);
      uint32_t size = sizeof(print_data_t);
      size += node->format().size() + 1; // format
      size += node->enum_strings().size() * sizeof(enum_string_cb); // enum_strings
      size += num_srcs * sizeof(data_t); // src_values
      return size;
    }

    void init(printimpl* node, const compiler* cp) {
      auto buf = reinterpret_cast<uint8_t*>(this) + sizeof(print_data_t);

      auto fmt_len = node->format().size() + 1;
      format = reinterpret_cast<char*>(buf);
      memcpy(format, node->format().c_str(), fmt_len);
      buf += fmt_len;

      this->enum_strings = reinterpret_cast<enum_string_cb*>(buf);
      auto e = this->enum_strings;
      for (auto cb : node->enum_strings()) {
        *e++ = cb;
      }
      buf += node->enum_strings().size() * sizeof(enum_string_cb);

      auto num_srcs = node->srcs().size() + (node->has_pred() ? -1 : 0);
      this->src_values = reinterpret_cast<data_t*>(buf);
      buf += num_srcs * sizeof(data_t);

      auto src_value = this->src_values;
      for (uint32_t i = (node->has_pred() ? 1 : 0), n = node->srcs().size(); i < n; ++i) {
        auto src = node->src(i).impl();
        src_value->init(src, cp);
        ++src_value;
      }
    }

    static void eval(print_data_t* self) {
      std::stringstream strbuf;
      for (const char *str = self->format; *str != '\0'; ++str) {
        if (*str == '{') {
          fmtinfo_t fmt;
          str = parse_format_index(&fmt, str);
          eval_data_t src(self->src_values[fmt.index]);
          switch (fmt.type) {
          case fmttype::Int:
            strbuf << src.value;
           break;
          case fmttype::Float:
            strbuf << bit_cast<float>(static_cast<int>(src.value));
           break;
          case fmttype::Enum:
            strbuf << self->enum_strings[fmt.index](static_cast<int>(src.value));
           break;
          }
        } else {
          strbuf.put(*str);
        }
      }
      std::cout << strbuf.rdbuf();
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

  struct assert_data_t {
    char* msg;
    data_t* time;
    source_location sloc;

    static uint32_t size(assertimpl* node) {
      uint32_t size = sizeof(assert_data_t);
      size += node->msg().size() + 1; // msg
      size += sizeof(data_t);  // time
      return size;
    }

    void init(assertimpl* node, const compiler* cp) {
      auto buf = reinterpret_cast<uint8_t*>(this) + sizeof(print_data_t);

      auto msg_len = node->msg().size() + 1;
      msg = reinterpret_cast<char*>(buf);
      memcpy(msg, node->msg().c_str(), msg_len);
      buf += msg_len;

      time = reinterpret_cast<data_t*>(buf);
      time->init(node->time().impl(), cp);
      buf += sizeof(data_t);

      sloc = node->sloc();
    }

    static void eval(assert_data_t* self) {
      eval_data_t tick(*self->time);
      fprintf(stderr, "assertion failure at tick %ld, %s (%s:%d)\n",
              static_cast<uint64_t>(tick.value), self->msg, self->sloc.file(), self->sloc.line());
      std::abort();
    }
  };


  void create_function() {
    jit_type_t params[1] = {jit_type_void_ptr};
    auto sig = jit_type_create_signature(jit_abi_cdecl, jit_type_int, params, 1, 1);
    j_func_ = jit_function_create(sim_ctx_->j_ctx, sig);
    auto j_state = jit_value_get_param(j_func_, 0);
    j_vars_ = jit_insn_load_relative(j_func_, j_state, offsetof(sim_state_t, vars), jit_type_void_ptr);
    j_ports_ = jit_insn_load_relative(j_func_, j_state, offsetof(sim_state_t, ports), jit_type_void_ptr);
  #ifndef NDEBUG
    j_dbg_ = jit_insn_load_relative(j_func_, j_state, offsetof(sim_state_t, dbg), jit_type_void_ptr);
  #endif
    j_zero_ = this->emit_constant(0, jit_type_uint);
    j_one_ = this->emit_constant(1, jit_type_uint);
    j_block_logsize_ = this->emit_constant(WORD_LOGSIZE, jit_type_uint);
    j_block_mask_ = this->emit_constant(WORD_MASK, jit_type_uint);
  }

  void emit_node(litimpl* node) {
    __source_location();

    uint32_t dst_width = node->size();
    if (dst_width <= WORD_SIZE) {
      auto j_type = to_native_type(dst_width);
      auto j_value = this->emit_constant(node->value().word(0), j_type);
      scalar_map_[node->id()] = j_value;
    }
  }

  void emit_node(proxyimpl* node) {
    __source_location();
    assert(node->check_full());    
    uint32_t dst_width = node->size();
    auto j_type = to_native_type(dst_width);
    if (dst_width <= WORD_SIZE) {
      jit_value_t j_dst = nullptr;
      for (uint i = 0, n = node->ranges().size(); i < n; ++i) {
        auto& range = node->range(i);
        auto& src = node->src(range.src_idx);
        auto j_src = this->emit_load_slice_scalar(src.impl(), range.src_offset, range.length, j_type);
        j_dst = this->emit_append_slice_scalar(j_dst, range.dst_offset, j_src);
      }
      scalar_map_[node->id()] = j_dst;
    } else {
      auto dst_addr = addr_map_.at(node->id());

      bool has_scalar_sources = true;
      for (auto& range : node->ranges()) {
        has_scalar_sources &= (range.length <= WORD_SIZE);
      }
      if (has_scalar_sources) {
        jit_value_t j_dst_tmp = nullptr;
        for (uint i = 0, n = node->ranges().size(); i < n; ++i) {
          auto& range = node->range(i);
          auto& src = node->src(range.src_idx);
          auto j_src = this->emit_load_slice_scalar(src.impl(), range.src_offset, range.length, word_type_);
          j_dst_tmp = this->emit_append_slice_vector(
                j_dst_tmp, dst_addr, dst_width, range.dst_offset, j_src, range.length);
        }
      } else {
        auto j_dst_ptr = this->emit_store_address(node);
        for (uint i = 0, n = node->ranges().size(); i < n; ++i) {
          auto& range = node->range(i);
          auto& src = node->src(range.src_idx);
          auto it = scalar_map_.find(src.id());
          if (it != scalar_map_.end()) {
            this->emit_copy_scalar(j_dst_ptr, range.dst_offset, it->second, range.src_offset, range.length);
          } else {
            auto j_src_ptr = this->emit_load_address(src.impl());
            this->emit_copy_vector(j_dst_ptr, range.dst_offset, j_src_ptr, range.src_offset, range.length);
          }
        }
      }
    }
  }

  void emit_node(inputimpl* node) {
    __source_location();
    uint32_t dst_width = node->size();
    auto j_type = to_native_type(dst_width);
    uint32_t addr = addr_map_.at(node->id());
    auto j_ptr = jit_insn_load_relative(j_func_, j_ports_, addr * sizeof(block_type*), jit_type_void_ptr);
    if (dst_width <= WORD_SIZE) {
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
      auto j_src_ptr = this->emit_load_address(node->src(0).impl());
      this->emit_memcpy(j_dst_ptr, j_src_ptr, ceildiv(dst_width, 8));
    }
  }

  void emit_node(aluimpl* node) {
    __source_location();

    uint32_t dst_width = node->size();
    auto j_type = to_native_type(dst_width);
    bool is_signed = node->is_signed();

    bool is_scalar = (dst_width <= bitwidth_v<block_type>);
    for (auto& src : node->srcs()) {
      is_scalar &= (src.size() <= bitwidth_v<block_type>);
    }

    auto is_resize = (node->should_resize_opds() != -1);
    auto j_src0 = this->emit_alu_operand(node, 0, is_scalar, is_resize);
    auto j_src1 = this->emit_alu_operand(node, 1, is_scalar, is_resize);

    switch (node->op()) {
    case ch_op::eq:
      if (is_scalar) {
        auto j_dst = jit_insn_eq(j_func_, j_src0, j_src1);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_type);
      } else {
        jit_value_t j_dst;
        if (is_resize) {
          j_dst = __alu_call_relational(bv_eq_vector, j_src0, node->src(0).size(), j_src1, node->src(1).size());
        } else {
          j_dst = this->emit_eq_vector(j_src0, j_src1, node->src(1).size());
        }
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_type);
      }
      break;
    case ch_op::ne:
      if (is_scalar) {
        auto j_dst = jit_insn_ne(j_func_, j_src0, j_src1);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_type);
      } else {
        jit_value_t j_dst;
        if (is_resize) {
          j_dst = __alu_call_relational(bv_eq_vector, j_src0, node->src(0).size(), j_src1, node->src(1).size());
        } else {
          j_dst = this->emit_eq_vector(j_src0, j_src1, node->src(1).size());
        }
        auto j_dst_n = jit_insn_not(j_func_, j_dst);
        scalar_map_[node->id()] = this->emit_cast(j_dst_n, j_type);
      }
      break;

    case ch_op::lt:
      if (is_scalar) {
        auto j_src0_s = is_signed ? this->emit_sign_ext(j_src0, node->src(0).size()) : j_src0;
        auto j_src1_s = is_signed ? this->emit_sign_ext(j_src1, node->src(1).size()) : j_src1;
        auto j_dst = jit_insn_lt(j_func_, j_src0_s, j_src1_s);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_type);
      } else {
        auto j_dst = __alu_call_relational(bv_lt_vector, j_src0, node->src(0).size(), j_src1, node->src(1).size());
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_type);
      }
      break;
    case ch_op::gt:
      if (is_scalar) {
        auto j_src0_s = is_signed ? this->emit_sign_ext(j_src0, node->src(0).size()) : j_src0;
        auto j_src1_s = is_signed ? this->emit_sign_ext(j_src1, node->src(1).size()) : j_src1;
        auto j_dst = jit_insn_gt(j_func_, j_src0_s, j_src1_s);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_type);
      } else {
        auto j_dst = __alu_call_relational(bv_lt_vector, j_src1, node->src(1).size(), j_src0, node->src(0).size());
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_type);
      }
      break;
    case ch_op::le:
      if (is_scalar) {
        auto j_src0_s = is_signed ? this->emit_sign_ext(j_src0, node->src(0).size()) : j_src0;
        auto j_src1_s = is_signed ? this->emit_sign_ext(j_src1, node->src(1).size()) : j_src1;
        auto j_dst = jit_insn_le(j_func_, j_src0_s, j_src1_s);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_type);
      } else {
        auto j_dst = __alu_call_relational(bv_lt_vector, j_src1, node->src(1).size(), j_src0, node->src(0).size());
        auto j_dst_n = jit_insn_not(j_func_, j_dst);
        scalar_map_[node->id()] = this->emit_cast(j_dst_n, j_type);
      }
      break;
    case ch_op::ge:
      if (is_scalar) {
        auto j_src0_s = is_signed ? this->emit_sign_ext(j_src0, node->src(0).size()) : j_src0;
        auto j_src1_s = is_signed ? this->emit_sign_ext(j_src1, node->src(1).size()) : j_src1;
        auto j_dst = jit_insn_ge(j_func_, j_src0_s, j_src1_s);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_type);
      } else {
        auto j_dst = __alu_call_relational(bv_lt_vector, j_src0, node->src(0).size(), j_src1, node->src(1).size());
        auto j_dst_n = jit_insn_not(j_func_, j_dst);
        scalar_map_[node->id()] = this->emit_cast(j_dst_n, j_type);
      }
      break;

    case ch_op::notl:
      if (is_scalar) {
        auto j_dst = jit_insn_to_not_bool(j_func_, j_src0);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_type);
      } else {
        CH_TODO();
      }
      break;
    case ch_op::andl:
      if (is_scalar) {
        auto j_src0_b = (node->src(0).size() > 1) ? jit_insn_to_bool(j_func_, j_src0) : j_src0;
        auto j_src1_b = (node->src(1).size() > 1) ? jit_insn_to_bool(j_func_, j_src1) : j_src1;
        auto j_dst = jit_insn_and(j_func_, j_src0_b, j_src1_b);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_type);
      } else {
        CH_TODO();
      }
      break;
    case ch_op::orl:
      if (is_scalar) {
        auto j_src0_b = (node->src(0).size() > 1) ? jit_insn_to_bool(j_func_, j_src0) : j_src0;
        auto j_src1_b = (node->src(1).size() > 1) ? jit_insn_to_bool(j_func_, j_src1) : j_src1;
        auto j_dst = jit_insn_or(j_func_, j_src0_b, j_src1_b);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_type);
      } else {
        CH_TODO();
      }
      break;

    case ch_op::inv:
      if (is_scalar) {
        auto j_dst = jit_insn_not(j_func_, j_src0);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_type);
        this->emit_clear_extra_bits(node);
      } else {
        CH_TODO();
      }      
      break;
    case ch_op::andb:
      if (is_scalar) {
        auto j_dst = jit_insn_and(j_func_, j_src0, j_src1);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_type);
      } else {
        assert(-1 == node->should_resize_opds());
        uint32_t num_words = ceildiv(dst_width, WORD_SIZE);
        for (uint32_t i = 0; i < num_words; ++i) {
          auto j_src0 = this->emit_load_scalar_elem(node->src(0).impl(), i, word_type_);
          auto j_src1 = this->emit_load_scalar_elem(node->src(1).impl(), i, word_type_);
          auto j_dst  = jit_insn_and(j_func_, j_src0, j_src1);
          auto dst_addr = addr_map_.at(node->id());
          jit_insn_store_relative(j_func_, j_vars_, dst_addr + i * sizeof(block_type), j_dst);
        }
      }
      break;
    case ch_op::orb:
      if (is_scalar) {
        auto j_dst = jit_insn_or(j_func_, j_src0, j_src1);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_type);
      } else {
        assert(-1 == node->should_resize_opds());
        auto dst_addr = addr_map_.at(node->id());
        uint32_t num_words = ceildiv(dst_width, WORD_SIZE);
        for (uint32_t i = 0; i < num_words; ++i) {
          auto j_src0 = this->emit_load_scalar_elem(node->src(0).impl(), i, word_type_);
          auto j_src1 = this->emit_load_scalar_elem(node->src(1).impl(), i, word_type_);
          auto j_dst  = jit_insn_or(j_func_, j_src0, j_src1);          
          jit_insn_store_relative(j_func_, j_vars_, dst_addr + i * sizeof(block_type), j_dst);
        }
      }
      break;
    case ch_op::xorb:
      if (is_scalar) {
        auto j_dst = jit_insn_xor(j_func_, j_src0, j_src1);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_type);
      } else {
        assert(-1 == node->should_resize_opds());
        auto dst_addr = addr_map_.at(node->id());
        uint32_t num_words = ceildiv(dst_width, WORD_SIZE);
        for (uint32_t i = 0; i < num_words; ++i) {
          auto j_src0 = this->emit_load_scalar_elem(node->src(0).impl(), i, word_type_);
          auto j_src1 = this->emit_load_scalar_elem(node->src(1).impl(), i, word_type_);
          auto j_dst  = jit_insn_xor(j_func_, j_src0, j_src1);
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
      if (is_scalar) {        
        auto j_src0_d = this->emit_cast(j_src0, j_type);
        auto j_dst = jit_insn_shl(j_func_, j_src0_d, j_src1);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_type);
        this->emit_clear_extra_bits(node);
      } else {
        CH_TODO();
      }
      break;
    case ch_op::shr:
      if (is_scalar) {
        if (is_signed) {
          auto j_src0_s = this->emit_sign_ext(j_src0, node->src(0).size());
          auto j_dst = jit_insn_shr(j_func_, j_src0_s, j_src1);
          scalar_map_[node->id()] = this->emit_cast(j_dst, j_type);
          this->emit_clear_extra_bits(node);
        } else {
          auto j_dst = jit_insn_ushr(j_func_, j_src0, j_src1);
          scalar_map_[node->id()] = this->emit_cast(j_dst, j_type);
        }
      } else {
        CH_TODO();
      }
      break;

    case ch_op::neg:
      if (is_scalar) {
        auto j_dst = jit_insn_neg(j_func_, j_src0);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_type);
        this->emit_clear_extra_bits(node);
      } else {
        CH_TODO();
      }
      break;
    case ch_op::add:
      if (is_scalar) {
        auto j_dst = jit_insn_add(j_func_, j_src0, j_src1);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_type);
        this->emit_clear_extra_bits(node);
      } else {
        CH_TODO();
      }
      break;
    case ch_op::sub:
      if (is_scalar) {
        auto j_dst = jit_insn_sub(j_func_, j_src0, j_src1);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_type);
        this->emit_clear_extra_bits(node);
      } else {
        CH_TODO();
      }
      break;

    case ch_op::mult:
      if (is_scalar) {
        auto j_src0_d = this->emit_cast(j_src0, j_type);
        auto j_src1_d = this->emit_cast(j_src1, j_type);
        auto j_src0_s = is_signed ? this->emit_sign_ext(j_src0_d, node->src(0).size()) : j_src0_d;
        auto j_src1_s = is_signed ? this->emit_sign_ext(j_src1_d, node->src(1).size()) : j_src1_d;
        auto j_dst = jit_insn_mul(j_func_, j_src0_s, j_src1_s);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_type);
        this->emit_clear_extra_bits(node);
      } else {
        CH_TODO();
      }
      break;
    case ch_op::div:
      if (is_scalar) {
        auto j_src0_s = is_signed ? this->emit_sign_ext(j_src0, node->src(0).size()) : j_src0;
        auto j_src1_s = is_signed ? this->emit_sign_ext(j_src1, node->src(1).size()) : j_src1;
        auto j_dst = jit_insn_div(j_func_, j_src0_s, j_src1_s);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_type);
        this->emit_clear_extra_bits(node);
      } else {
        CH_TODO();
      }
      break;
    case ch_op::mod:
      if (is_scalar) {
        auto j_src0_s = is_signed ? this->emit_sign_ext(j_src0, node->src(0).size()) : j_src0;
        auto j_src1_s = is_signed ? this->emit_sign_ext(j_src1, node->src(1).size()) : j_src1;
        auto j_dst = jit_insn_rem(j_func_, j_src0_s, j_src1_s);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_type);
        this->emit_clear_extra_bits(node);
      } else {
        CH_TODO();
      }
      break;

    case ch_op::pad:
      if (is_scalar) {
        if (node->is_signed()) {
          auto j_dst = this->emit_sign_ext(j_src0, node->src(0).size());
          scalar_map_[node->id()] = this->emit_cast(j_dst, j_type);
          this->emit_clear_extra_bits(node);
        } else {
          scalar_map_[node->id()]= j_src0;
        }
      } else {
        auto j_dst = this->emit_store_address(node);
        this->emit_pad_vector(j_dst, node->size(), j_src0, node->src(0).size());
      }
      break;
    default:
      std::abort();
      break;
    }
  }

  jit_value_t emit_alu_operand(aluimpl* node,
                               uint32_t opd,
                               bool is_scalar,
                               bool resize) {
    if (opd >= node->srcs().size())
      return nullptr;
    auto src = node->src(opd).impl();
    auto is_signed = node->is_signed();
    if (is_scalar) {
      auto j_value = scalar_map_.at(src->id());
      if (resize && is_signed) {
        j_value = this->emit_sign_ext(j_value, src->size());
      }
      return j_value;
    } else {
      auto it = scalar_map_.find(src->id());
      if (it != scalar_map_.end()) {
         return this->emit_address_of(it->second, word_type_);
      } else {
        return this->emit_load_address(src);
      }
    }
  }

  jit_value_t emit_alu_call_relational(void* pfn,
                                       const char* name,
                                       jit_value_t j_arg0,
                                       uint32_t arg0_size,
                                       jit_value_t j_arg1,
                                       uint32_t arg1_size) {
    __source_location();

    // setup arguments
    auto j_arg0_size = this->emit_constant(arg0_size, jit_type_uint);
    auto j_arg1_size = this->emit_constant(arg1_size, jit_type_uint);

    // call native function
    jit_type_t params[] = {jit_type_void_ptr, jit_type_uint, jit_type_void_ptr, jit_type_uint};
    jit_type_t j_sig = jit_type_create_signature(jit_abi_cdecl,
                                                 jit_type_uint,
                                                 params,
                                                 __countof(params),
                                                 1);
    jit_value_t args[] = {j_arg0, j_arg0_size, j_arg1, j_arg1_size};
    return jit_insn_call_native(j_func_,
                                name,
                                pfn,
                                j_sig,
                                args,
                                __countof(args),
                                JIT_CALL_NOTHROW);
  }

  void emit_node(selectimpl* node) {
    __source_location();
    jit_label_t l_exit = jit_label_undefined;

    uint32_t dst_width = node->size();   
    bool is_scalar = (dst_width <= WORD_SIZE);
    auto j_type = to_native_type(dst_width);

    jit_value_t j_dst = nullptr;
    if (is_scalar) {
      j_dst = jit_value_create(j_func_, j_type);
      scalar_map_[node->id()] = j_dst;
    }

    if (node->has_key()) {      
      uint32_t i = 1, l = node->srcs().size() - 1;
      for (;i < l; i += 2) {
        jit_label_t l_skip = jit_label_undefined;
        if (node->key().size() <= WORD_SIZE) {
          auto j_key = scalar_map_.at(node->src(0).id());
          auto j_val = scalar_map_.at(node->src(i).id());
          auto j_eq = jit_insn_eq(j_func_, j_key, j_val);
          jit_insn_branch_if_not(j_func_, j_eq, &l_skip);
        } else {
          auto j_key_ptr = this->emit_store_address(node->src(0).impl());
          auto j_val_ptr = this->emit_load_address(node->src(i).impl());
          auto j_eq = this->emit_eq_vector(j_key_ptr, j_val_ptr, dst_width);
          jit_insn_branch_if_not(j_func_, j_eq, &l_skip);
        }
        if (is_scalar) {
          auto j_src = scalar_map_.at(node->src(i+1).id());
          jit_insn_store(j_func_, j_dst, j_src);
        } else {
          auto j_dst_ptr = this->emit_store_address(node);
          auto j_src_ptr = this->emit_load_address(node->src(i+1).impl());
          this->emit_memcpy(j_dst_ptr, j_src_ptr, ceildiv(dst_width, 8));
        }
        jit_insn_branch(j_func_, &l_exit);
        jit_insn_label(j_func_, &l_skip);
      }
      if (is_scalar) {
        auto j_src = scalar_map_.at(node->src(i).id());
        jit_insn_store(j_func_, j_dst, j_src);
      } else {
        auto j_dst_ptr = this->emit_store_address(node);
        auto j_src_ptr = this->emit_load_address(node->src(i).impl());
        this->emit_memcpy(j_dst_ptr, j_src_ptr, ceildiv(dst_width, 8));
      }
    } else {
      uint32_t i = 0, l = node->srcs().size() - 1;
      for (;i < l; i += 2) {
        jit_label_t l_skip = jit_label_undefined;
        auto j_pred = scalar_map_.at(node->src(i).id());
        jit_insn_branch_if_not(j_func_, j_pred, &l_skip);
        if (is_scalar) {
          auto j_src = scalar_map_.at(node->src(i+1).id());
          jit_insn_store(j_func_, j_dst, j_src);
        } else {
          auto j_dst_ptr = this->emit_store_address(node);
          auto j_src_ptr = this->emit_load_address(node->src(i+1).impl());
          this->emit_memcpy(j_dst_ptr, j_src_ptr, ceildiv(dst_width, 8));
        }
        jit_insn_branch(j_func_, &l_exit);
        jit_insn_label(j_func_, &l_skip);
      }
      if (is_scalar) {
        auto j_src = scalar_map_.at(node->src(i).id());
        jit_insn_store(j_func_, j_dst, j_src);
      } else {
        auto j_dst_ptr = this->emit_store_address(node);
        auto j_src_ptr = this->emit_load_address(node->src(i).impl());
        this->emit_memcpy(j_dst_ptr, j_src_ptr, ceildiv(dst_width, 8));
      }
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

    uint32_t dst_width = node->size();
    auto j_type = to_native_type(dst_width);
    auto is_scalar = (dst_width <= WORD_SIZE);
    auto dst_addr = addr_map_.at(node->id());

    jit_value_t j_dst = nullptr;
    jit_value_t j_next = nullptr;
    jit_value_t j_enable = nullptr;
    jit_value_t j_init_data = nullptr;
    jit_value_t j_reset = nullptr;

    if (is_scalar) {
      j_dst = scalar_map_.at(node->id());
      j_next = scalar_map_.at(node->next().id());
      if (node->has_init_data()) {
        j_init_data = scalar_map_.at(node->init_data().id());
      }
    }

    if (node->has_init_data()) {
      j_reset = scalar_map_.at(node->reset().id());
    }

    if (node->has_enable()) {
      j_enable = scalar_map_.at(node->enable().id());
    }

    if (!bypass_enable_) {
      auto j_cd = scalar_map_.at(node->cd().id());
      jit_insn_branch_if_not(j_func_, j_cd, &l_exit);
    }

    if (node->is_pipe()) {
      uint32_t pipe_width = (node->length() - 1) * dst_width;
      auto j_pipe_type = to_native_type(pipe_width);
      auto pipe_addr = dst_addr + __align_word_size(dst_width);
      auto is_pipe_scalar = (pipe_width <= WORD_SIZE);

      if (node->has_init_data()) {
        jit_label_t l_skip = jit_label_undefined;
        auto j_reset = scalar_map_.at(node->reset().id());
        jit_insn_branch_if_not(j_func_, j_reset, &l_skip);

        if (is_pipe_scalar) {
          assert(is_scalar);
          // reset dst register
          auto j_init_data_p = this->emit_cast(j_init_data, j_pipe_type);
          jit_insn_store(j_func_, j_dst, j_init_data);
          jit_insn_store_relative(j_func_, j_vars_, dst_addr, j_init_data);

          // reset pipe registers
          jit_value_t j_pipe_init_data = nullptr;
          for (uint32_t i = 0, n = node->length() - 1; i < n; ++i) {
            j_pipe_init_data = this->emit_append_slice_scalar(
                  j_pipe_init_data, i * dst_width, j_init_data_p);
          }
          jit_insn_store_relative(j_func_, j_vars_, pipe_addr, j_pipe_init_data);
        } else {
          if (is_scalar) {
            // reset dst register
            jit_insn_store(j_func_, j_dst, j_init_data);
            jit_insn_store_relative(j_func_, j_vars_, dst_addr, j_init_data);

            // reset pipe registers
            auto j_init_data_w = this->emit_cast(j_init_data, word_type_);
            jit_value_t j_pipe_tmp = nullptr;
            for (uint32_t i = 0, n = node->length() - 1; i < n; ++i) {
              j_pipe_tmp = this->emit_append_slice_vector(
                    j_pipe_tmp, pipe_addr, pipe_width, i * dst_width, j_init_data_w, dst_width);
            }
          } else {
            // reset dst register
            auto j_dst_ptr = jit_insn_add_relative(j_func_, j_vars_, dst_addr);
            auto j_init_ptr = this->emit_load_address(node->init_data().impl());
            this->emit_memcpy(j_dst_ptr, j_init_ptr, ceildiv(dst_width, 8));

            // reset pipe registers
            auto j_pipe_ptr = jit_insn_add_relative(j_func_, j_vars_, pipe_addr);
            for (uint32_t i = 0, n = node->length() - 1; i < n; ++i) {
              this->emit_copy_vector(j_pipe_ptr, i * dst_width, j_init_ptr, 0, dst_width);
            }
          }
        }

        jit_insn_branch(j_func_, &l_exit);
        jit_insn_label(j_func_, &l_skip);
      }

      if (node->has_enable()) {
        jit_insn_branch_if_not(j_func_, j_enable, &l_exit);
      }

      if (is_pipe_scalar) {
        assert(is_scalar);
        if (pipe_width == dst_width) {
          // dst <- pipe
          auto j_pipe = jit_insn_load_relative(j_func_, j_vars_, pipe_addr, j_pipe_type);
          jit_insn_store_relative(j_func_, j_vars_, dst_addr, j_pipe);
          jit_insn_store(j_func_, j_dst, j_pipe);

          // pipe <- next
          jit_insn_store_relative(j_func_, j_vars_, pipe_addr, j_next);
        } else {
          // dst <- pipe[0]
          auto j_pipe = jit_insn_load_relative(j_func_, j_vars_, pipe_addr, j_pipe_type);
          auto j_pipe_0 = this->emit_load_slice_scalar(j_pipe, 0, dst_width, j_type);
          jit_insn_store_relative(j_func_, j_vars_, dst_addr, j_pipe_0);
          jit_insn_store(j_func_, j_dst, j_pipe_0);

          // pipe >>= dst_width
          auto j_shift = this->emit_constant(dst_width, jit_type_uint);
          auto j_pipe_s = jit_insn_ushr(j_func_, j_pipe, j_shift);

          // pipe[n-1] <- next
          auto j_shfn1  = this->emit_constant((node->length() - 2) * dst_width, jit_type_uint);
          auto j_next_p = this->emit_cast(j_next, j_pipe_type);
          auto j_next_s = jit_insn_shl(j_func_, j_next_p, j_shfn1);
          auto j_or     = jit_insn_or(j_func_, j_next_s, j_pipe_s);
          jit_insn_store_relative(j_func_, j_vars_, pipe_addr, j_or);
        }
      } else {
        if (pipe_width == dst_width) {
          // dst <- pipe
          auto j_pipe_ptr = jit_insn_add_relative(j_func_, j_vars_, pipe_addr);
          auto j_dst_ptr = jit_insn_add_relative(j_func_, j_vars_, dst_addr);
          this->emit_memcpy(j_dst_ptr, j_pipe_ptr, ceildiv(dst_width, 8));

          // pipe <- next
          auto j_next_ptr = this->emit_load_address(node->next().impl());
          this->emit_memcpy(j_pipe_ptr, j_next_ptr, ceildiv(dst_width, 8));
        } else {
          // load pipe index
          auto pipe_index_addr = pipe_addr + __align_word_size(pipe_width);
          auto j_pipe_index = jit_insn_load_relative(j_func_, j_vars_, pipe_index_addr, jit_type_uint);
          auto j_pipe_ptr = jit_insn_add_relative(j_func_, j_vars_, pipe_addr);

          if (is_scalar) {
            // pop pipe data
            auto j_data = this->emit_load_array_scalar(j_pipe_ptr, pipe_width, j_pipe_index, dst_width, j_type);
            jit_insn_store_relative(j_func_, j_vars_, dst_addr, j_data);
            jit_insn_store(j_func_, j_dst, j_data);

            // push next data
            this->emit_store_array_scalar(j_pipe_ptr, pipe_width, j_pipe_index, j_next, dst_width);
          } else {
            // pop pipe data
            auto j_dst_ptr = jit_insn_add_relative(j_func_, j_vars_, dst_addr);
            this->emit_load_array_vector(j_dst_ptr, dst_width, j_pipe_ptr, j_pipe_index);

            // push next data
            auto j_next_ptr = this->emit_load_address(node->next().impl());
            this->emit_store_array_vector(j_pipe_ptr, j_pipe_index, j_next_ptr, dst_width);
          }

          // advance pipe index
          auto j_max  = this->emit_constant(node->length() - 2, jit_type_uint);
          auto j_sub = jit_insn_sub(j_func_, j_pipe_index, j_one_);
          auto j_min = jit_insn_min(j_func_, j_sub, j_max);
          jit_insn_store_relative(j_func_, j_vars_, pipe_index_addr, j_min);
        }
      }
    } else {      
      if (node->has_init_data()) {
        jit_label_t l_skip = jit_label_undefined;
        jit_insn_branch_if_not(j_func_, j_reset, &l_skip);

        if (is_scalar) {
          jit_insn_store(j_func_, j_dst, j_init_data);
          jit_insn_store_relative(j_func_, j_vars_, dst_addr, j_init_data);
        } else {
          auto j_dst_ptr = jit_insn_add_relative(j_func_, j_vars_, dst_addr);
          auto j_init_ptr = this->emit_load_address(node->init_data().impl());
          this->emit_memcpy(j_dst_ptr, j_init_ptr, ceildiv(dst_width, 8));
        }

        jit_insn_branch(j_func_, &l_exit);
        jit_insn_label(j_func_, &l_skip);
      }

      if (node->has_enable()) {
        jit_insn_branch_if_not(j_func_, j_enable, &l_exit);
      }

      if (is_scalar) {
        jit_insn_store_relative(j_func_, j_vars_, dst_addr, j_next);
        jit_insn_store(j_func_, j_dst, j_next);
      } else {
        auto j_dst_ptr = jit_insn_add_relative(j_func_, j_vars_, dst_addr);
        auto j_next_ptr = this->emit_load_address(node->next().impl());
        this->emit_memcpy(j_dst_ptr, j_next_ptr, ceildiv(dst_width, 8));
      }
    }

    jit_insn_label(j_func_, &l_exit);
  }

  void emit_node(marportimpl* node) {
    __source_location();
    auto dst_width = node->size();
    auto j_type = to_native_type(dst_width);
    bool is_scalar = (dst_width <= WORD_SIZE);

    auto j_src_addr = scalar_map_.at(node->addr().id());
  #ifndef NDEBUG
    this->emit_range_check(j_src_addr, 0, node->mem()->num_items());
  #endif
    auto j_array_ptr = this->emit_load_address(node->mem());
    uint32_t array_width = node->mem()->size();

    if (is_scalar) {
      auto j_src = this->emit_load_array_scalar(j_array_ptr, array_width, j_src_addr, dst_width, j_type);
      scalar_map_[node->id()] = j_src;
    } else {
       auto j_dst_ptr = this->emit_store_address(node);
      this->emit_load_array_vector(j_dst_ptr, dst_width, j_array_ptr, j_src_addr);
    }
  }

  void emit_node(msrportimpl* node) {
    __source_location();
    jit_label_t l_exit = jit_label_undefined;

    auto dst_width = node->size();
    auto j_type = to_native_type(dst_width);
    bool is_scalar = (dst_width <= WORD_SIZE);
    auto dst_addr = addr_map_.at(node->id());

    auto predicated = node->has_enable() || !bypass_enable_;
    if (predicated) {
      jit_value_t j_predicate = nullptr;
      if (node->has_enable()) {
        j_predicate = scalar_map_.at(node->enable().id());
      }
      if (!bypass_enable_) {
        auto j_cd = scalar_map_.at(node->cd().id());
        if (j_predicate) {
          j_predicate = jit_insn_and(j_func_, j_predicate, j_cd);
        } else {
          j_predicate = j_cd;
        }
      }
      jit_insn_branch_if_not(j_func_, j_predicate, &l_exit);
    }

    auto j_src_addr = scalar_map_.at(node->addr().id());
  #ifndef NDEBUG
    this->emit_range_check(j_src_addr, 0, node->mem()->num_items());
  #endif
    auto j_array_ptr = this->emit_load_address(node->mem());
    uint32_t array_width = node->mem()->size();

    if (is_scalar) {
      auto j_src = this->emit_load_array_scalar(j_array_ptr, array_width, j_src_addr, dst_width, j_type);
      jit_insn_store_relative(j_func_, j_vars_, dst_addr, j_src);
      auto j_dst = scalar_map_.at(node->id());
      jit_insn_store(j_func_, j_dst, j_src);
    } else {
       auto j_dst_ptr = this->emit_store_address(node);
      this->emit_load_array_vector(j_dst_ptr, dst_width, j_array_ptr, j_src_addr);
    }

    if (predicated) {
      jit_insn_label(j_func_, &l_exit);
    }
  }

  void emit_node(mwportimpl* node) {
    __source_location();
    jit_label_t l_exit = jit_label_undefined;
    auto data_width = node->mem()->data_width();
    bool is_scalar = (data_width <= WORD_SIZE);

    auto predicated = node->has_enable() || !bypass_enable_;
    if (predicated) {
      jit_value_t j_predicate = nullptr;
      if (node->has_enable()) {
        j_predicate = scalar_map_.at(node->enable().id());
      }
      if (!bypass_enable_) {
        auto j_cd = scalar_map_.at(node->cd().id());
        if (j_predicate) {
          auto j_and = jit_insn_and(j_func_, j_predicate, j_cd);
          jit_insn_store(j_func_, j_predicate, j_and);
        } else {
          j_predicate = j_cd;
        }
      }
      jit_insn_branch_if_not(j_func_, j_predicate, &l_exit);
    }

    auto j_dst_addr = scalar_map_.at(node->addr().id());
  #ifndef NDEBUG
    this->emit_range_check(j_dst_addr, 0, node->mem()->num_items());
  #endif
    auto j_array_ptr = this->emit_store_address(node->mem());
    uint32_t array_width = node->mem()->size();

    if (is_scalar) {
      auto j_wdata = scalar_map_.at(node->wdata().id());
      this->emit_store_array_scalar(j_array_ptr, array_width, j_dst_addr, j_wdata, data_width);
    } else {
      auto j_wdata_ptr = this->emit_load_address(node->wdata().impl());
      this->emit_store_array_vector(j_array_ptr, j_dst_addr, j_wdata_ptr, data_width);
    }

    if (predicated) {
      jit_insn_label(j_func_, &l_exit);
    }
  }

  void emit_node(timeimpl* node) {
    __source_location();
    auto addr = addr_map_.at(node->id());
    auto j_value = scalar_map_.at(node->id());
    auto j_incr = jit_insn_add(j_func_, j_value, j_one_);
    jit_insn_store_relative(j_func_, j_vars_, addr, j_incr);
  }

  void emit_node(printimpl* node) {
    __source_location();
    jit_label_t l_exit = jit_label_undefined;

    auto predicated = node->has_pred();
    if (predicated) {
      auto j_predicate = scalar_map_.at(node->pred().id());
      jit_insn_branch_if_not(j_func_, j_predicate, &l_exit);
    }

    // copy scalar arguments
    auto addr = addr_map_.at(node->id());
    uint32_t src_idx = 0;
    for (uint32_t i = (node->has_pred() ? 1 : 0), n = node->srcs().size(); i < n; ++i) {
      auto src = node->src(i).impl();
      auto it = scalar_map_.find(src->id());
      if (it != scalar_map_.end()) {
        auto values_ptr = jit_insn_load_relative(j_func_,
                                                 j_vars_,
                                                 addr + offsetof(print_data_t, src_values),
                                                 jit_type_void_ptr);
        auto j_value = this->emit_address_of(it->second, word_type_);
        jit_insn_store_relative(j_func_, values_ptr, src_idx * sizeof(data_t), j_value);
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

    if (predicated) {
      jit_insn_label(j_func_, &l_exit);
    }
  }

  void emit_node(assertimpl* node) {
    __source_location();
    jit_label_t l_exit = jit_label_undefined;

    auto j_cond = scalar_map_.at(node->cond().id());
    if (node->has_pred()) {
      auto j_pred = scalar_map_.at(node->pred().id());
      auto j_pred_n = jit_insn_not(j_func_, j_pred);
      j_cond = jit_insn_or(j_func_, j_cond, j_pred_n);
    }
    jit_insn_branch_if(j_func_, j_cond, &l_exit);

    // copy scalar arguments
    auto addr = addr_map_.at(node->id());
    auto it = scalar_map_.find(node->time().id());
    if (it != scalar_map_.end()) {
      auto time_ptr = jit_insn_load_relative(j_func_,
                                             j_vars_,
                                             addr + offsetof(assert_data_t, time),
                                             jit_type_void_ptr);
      auto j_value = this->emit_address_of(it->second, word_type_);
      jit_insn_store_relative(j_func_, time_ptr, 0, j_value);
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
                         "assert_data_t::eval",
                         (void*)assert_data_t::eval,
                         j_sig,
                         args,
                         __countof(args),
                         JIT_CALL_NOTHROW);

    jit_insn_label(j_func_, &l_exit);
  }

  /////////////////////////////////////////////////////////////////////////////

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
        var_addr += __align_word_size(cd_data_t::size() * 8);
        break;
      case type_reg: {
        addr_map_[node->id()] = var_addr;
        auto reg = reinterpret_cast<regimpl*>(node);
        var_addr += __align_word_size(reg->size());
        if (reg->is_pipe()) {
          uint32_t pipe_width = (reg->length() - 1) * reg->size();
          var_addr += __align_word_size(pipe_width);
          if (pipe_width > WORD_SIZE) {
            var_addr += sizeof(uint32_t); // pipe index
          }
        }
      } break;
      case type_mem:
      case type_msrport:
      case type_udfs:
        addr_map_[node->id()] = var_addr;
        var_addr += __align_word_size(dst_width);
        break;
      case type_time: {
        addr_map_[node->id()] = var_addr;
        var_addr += __align_word_size(time_data_t::size() * 8);
      } break;
      case type_assert: {
        addr_map_[node->id()] = var_addr;
        auto a = reinterpret_cast<assertimpl*>(node);
        var_addr += __align_word_size(assert_data_t::size(a) * 8);
      } break;
      case type_print: {
        addr_map_[node->id()] = var_addr;
        auto p = reinterpret_cast<printimpl*>(node);
        var_addr += __align_word_size(print_data_t::size(p) * 8);
      } break;
      default:
        // only allocate nodes with size bigger than WORD_SIZE bits
        if (dst_width > WORD_SIZE) {
          addr_map_[node->id()] = var_addr;
          var_addr += __align_word_size(dst_width);
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

  #ifndef NDEBUG
    sim_ctx_->state.dbg = new char[4096];
  #endif

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
          auto pipe_addr = addr + __align_word_size(dst_width);
          auto pipe_width = (reg->length() - 1) * dst_width;
          bv_init(reinterpret_cast<block_type*>(sim_ctx_->state.vars + pipe_addr), pipe_width);
          if (pipe_width > WORD_SIZE) {
            auto pipe_index_addr = pipe_addr + __align_word_size(pipe_width);
            *reinterpret_cast<uint32_t*>(sim_ctx_->state.vars + pipe_index_addr) = 0;
          }
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
      case type_assert: {
        auto addr = addr_map_.at(node->id());
        auto a = reinterpret_cast<assertimpl*>(node);
        reinterpret_cast<assert_data_t*>(sim_ctx_->state.vars + addr)->init(a, this);
      } break;
      case type_print: {
        auto addr = addr_map_.at(node->id());
        auto p = reinterpret_cast<printimpl*>(node);
        reinterpret_cast<print_data_t*>(sim_ctx_->state.vars + addr)->init(p, this);
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
          uint32_t width = num_words * WORD_SIZE;
          if (bv_eq<false, block_type, ClearBitAccessor<block_type>>(
                constant.data, width, node->value().words(), width)) {
            constant.nodes.push_back(node->id());
            found = true;
            break;
          }
        } else {
          uint32_t width = constant.size * WORD_SIZE;
          if (bv_eq<false, block_type, ClearBitAccessor<block_type>>(
                constant.data, width, node->value().words(), width)) {
            auto buf = reinterpret_cast<block_type*>(
                  std::realloc(constant.data, num_words * sizeof(block_type)));
            std::copy_n(node->value().words(), num_words, buf);
            total_words += (num_words - constant.size);
            constant.data = buf;
            constant.size = num_words;
            constant.nodes.push_back(node->id());
            found = true;
            break;
          }
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

  /////////////////////////////////////////////////////////////////////////////

  jit_value_t emit_eq_vector(jit_value_t j_ptr1, jit_value_t j_ptr2, uint32_t length) {
    auto j_num_words = this->emit_constant(ceildiv(length, WORD_SIZE), jit_type_uint);
    auto j_ret = jit_value_create(j_func_, jit_type_uint);
    auto j_idx = jit_value_create(j_func_, jit_type_uint);

    jit_insn_store(j_func_, j_ret, j_zero_);
    jit_insn_store(j_func_, j_idx, j_zero_);

    jit_label_t l_loop = jit_label_undefined;
    jit_insn_label(j_func_, &l_loop);

    auto j_value1 = jit_insn_load_elem(j_func_, j_ptr1, j_idx, word_type_);
    auto j_value2 = jit_insn_load_elem(j_func_, j_ptr2, j_idx, word_type_);
    auto j_eq = jit_insn_eq(j_func_, j_value1, j_value2);
    jit_insn_store(j_func_, j_ret, j_eq);
    auto j_idx_next = jit_insn_add(j_func_, j_idx, j_one_);
    jit_insn_store(j_func_, j_idx, j_idx_next);
    auto j_not_done = jit_insn_lt(j_func_, j_idx_next, j_num_words);
    auto j_continue = jit_insn_and(j_func_, j_not_done, j_eq);

    jit_insn_branch_if(j_func_, j_continue, &l_loop);
    return j_ret;
  }

  jit_value_t emit_pad_vector(jit_value_t j_dst_ptr,
                              uint32_t dst_size,
                              jit_value_t j_src_ptr,
                              uint32_t src_size) {
    CH_UNUSED(j_dst_ptr, dst_size, j_src_ptr, src_size);
    CH_TODO();
  }

  /////////////////////////////////////////////////////////////////////////////

  jit_value_t emit_load_slice_scalar(jit_value_t j_value,
                                     uint32_t offset,
                                     uint32_t length,
                                     jit_type_t j_type) {
    __source_location();
    assert(length <= WORD_SIZE);
    assert(offset < WORD_SIZE);

    jit_value_t j_src = j_value;
    if (offset) {
      auto j_offset = this->emit_constant(offset, jit_type_uint);
      j_src = jit_insn_ushr(j_func_, j_value, j_offset);
    }
    int clamp = get_value_size(j_src) - length;
    if (clamp) {
      assert(clamp > 0);
      uint64_t mask = (1ull << length) - 1;
      auto j_mask = this->emit_constant(mask, jit_value_get_type(j_src));
      j_src = jit_insn_and(j_func_, j_src, j_mask);
    }
    return this->emit_cast(j_src, j_type);
  }

  jit_value_t emit_load_slice_scalar(lnodeimpl* node,
                                     uint32_t offset,
                                     uint32_t length,
                                     jit_type_t j_type) {
    __source_location();
    assert(length <= WORD_SIZE);
    uint32_t src_width = node->size();
    if (src_width != length) {
      if (src_width <= WORD_SIZE) {
        auto j_src_value = scalar_map_.at(node->id());
        return this->emit_load_slice_scalar(j_src_value, offset, length, j_type);
      } else {
        auto src_lsb8 = offset % 8;
        auto src_end8 = src_lsb8 + length;
        if (src_end8 <= WORD_SIZE) {
          auto block_size = to_value_size(src_end8);
          auto src_idx = ceildiv(offset + length, 8) - block_size / 8;
          auto src_lsb = offset - src_idx * 8;
          auto j_src_value = this->emit_load_scalar_relative(node, src_idx, to_value_type(block_size));
          return this->emit_load_slice_scalar(j_src_value, src_lsb, length, j_type);
        } else {
          auto src_idx = offset / WORD_SIZE;
          auto src_lsb = offset % WORD_SIZE;
          auto j_ntype = to_native_type(length);
          auto j_src_lsb = this->emit_constant(src_lsb, jit_type_uint);
          auto j_src_value0 = this->emit_load_scalar_relative(node, src_idx * sizeof(block_type), word_type_);
          auto j_src_value0_s = jit_insn_ushr(j_func_, j_src_value0, j_src_lsb);
          auto j_src_value0_n = this->emit_cast(j_src_value0_s, j_ntype);
          auto j_src_value1 = this->emit_load_scalar_relative(node, (src_idx + 1) * sizeof(block_type), j_ntype);
          auto j_rem = this->emit_constant(get_value_size(j_src_value1) - src_lsb, jit_type_uint);
          auto j_src_value1_s = jit_insn_shl(j_func_, j_src_value1, j_rem);
          auto j_src_value = jit_insn_or(j_func_, j_src_value1_s, j_src_value0_n);
          return this->emit_load_slice_scalar(j_src_value, 0, length, j_type);
        }
      }
    } else {
      auto j_src_value = scalar_map_.at(node->id());
      return this->emit_cast(j_src_value, j_type);
    }
  }

  jit_value_t emit_load_array_scalar(jit_value_t j_array_ptr,
                                     uint32_t array_width,
                                     jit_value_t j_index,
                                     uint32_t length,
                                     jit_type_t j_type) {
    __source_location();
    assert(length <= WORD_SIZE);

    if (is_value_size(length)) {
      auto j_src_value = jit_insn_load_elem(j_func_, j_array_ptr, j_index, to_value_type(length));
      return this->emit_cast(j_src_value, j_type);
    } else {
      auto j_data_size = this->emit_constant(length, jit_type_uint);
      auto j_src_offset = jit_insn_mul(j_func_, j_index, j_data_size);
      jit_value_t j_src;
      if (array_width <= WORD_SIZE) {
        auto j_src_value = jit_insn_load_relative(j_func_, j_array_ptr, 0, word_type_);
        j_src = jit_insn_ushr(j_func_, j_src_value, j_src_offset);
      } else {
        auto j_ntype = to_native_type(length);
        auto j_src_idx = jit_insn_ushr(j_func_, j_src_offset, j_block_logsize_);
        auto j_src_lsb = jit_insn_and(j_func_, j_src_offset, j_block_mask_);

        auto j_src_ptr = jit_insn_load_elem_address(j_func_, j_array_ptr, j_src_idx, word_type_);
        auto j_src_value0 = jit_insn_load_relative(j_func_, j_src_ptr, 0, word_type_);
        auto j_src0_s = jit_insn_ushr(j_func_, j_src_value0, j_src_lsb);
        j_src = this->emit_cast(j_src0_s, j_ntype);

        jit_label_t l_skip = jit_label_undefined;
        auto j_src_rem = this->emit_constant(WORD_SIZE - length, jit_type_uint);
        auto j_src_inclusive = jit_insn_le(j_func_, j_src_lsb, j_src_rem);
        jit_insn_branch_if(j_func_, j_src_inclusive, &l_skip);

        auto j_src_value1 = jit_insn_load_relative(j_func_, j_src_ptr, sizeof(block_type), j_ntype);
        auto j_block_size = this->emit_constant(get_value_size(j_src_value1), jit_type_uint);
        auto j_rem = jit_insn_sub(j_func_, j_block_size, j_src_lsb);
        auto j_src1_s = jit_insn_shl(j_func_, j_src_value1, j_rem);
        auto j_or = jit_insn_or(j_func_, j_src, j_src1_s);
        jit_insn_store(j_func_, j_src, j_or);

        jit_insn_label(j_func_, &l_skip);
      }
      int clamp = get_value_size(j_src) - length;
      if (clamp) {
        assert(clamp > 0);
        uint64_t mask = (1ull << length) - 1;
        auto j_mask = this->emit_constant(mask, jit_value_get_type(j_src));
        auto j_src_c = jit_insn_and(j_func_, j_src, j_mask);
        return this->emit_cast(j_src_c, j_type);
      } else {
        return this->emit_cast(j_src, j_type);
      }
    }
  }

  void emit_store_array_scalar(jit_value_t j_array_ptr,
                               uint32_t array_width,
                               jit_value_t j_index,
                               jit_value_t j_data,
                               uint32_t length) {
    __source_location();
    assert(length <= WORD_SIZE);

    if (is_value_size(length)) {
      auto j_wdata_n = this->emit_cast(j_data, to_value_type(length));
      jit_insn_store_elem(j_func_, j_array_ptr, j_index, j_wdata_n);
    } else {
      auto j_mask = this->emit_constant(WORD_MAX >> (WORD_SIZE - length), word_type_);
      auto j_data_w = this->emit_cast(j_data, word_type_);
      auto j_data_size = this->emit_constant(length, jit_type_uint);
      auto j_dst_offset = jit_insn_mul(j_func_, j_index, j_data_size);

      if (array_width <= WORD_SIZE) {
        auto j_dst_value = jit_insn_load_relative(j_func_, j_array_ptr, 0, word_type_);
        auto j_mask_s = jit_insn_shl(j_func_, j_mask, j_dst_offset);
        auto j_data_s = jit_insn_shl(j_func_, j_data_w, j_dst_offset);
        auto j_dst = this->emit_blend(j_mask_s, j_dst_value, j_data_s);
        jit_insn_store_relative(j_func_, j_array_ptr, 0, j_dst);
      } else {        
        auto j_dst_idx = jit_insn_ushr(j_func_, j_dst_offset, j_block_logsize_);
        auto j_dst_lsb = jit_insn_and(j_func_, j_dst_offset, j_block_mask_);

        auto j_dst_ptr = jit_insn_load_elem_address(j_func_, j_array_ptr, j_dst_idx, word_type_);
        auto j_dst_value0 = jit_insn_load_relative(j_func_, j_dst_ptr, 0, word_type_);
        auto j_mask0_s = jit_insn_shl(j_func_, j_mask, j_dst_lsb);
        auto j_data0_s = jit_insn_shl(j_func_, j_data_w, j_dst_lsb);
        auto j_dst0 = this->emit_blend(j_mask0_s, j_dst_value0, j_data0_s);
        jit_insn_store_relative(j_func_, j_dst_ptr, 0, j_dst0);

        jit_label_t l_skip = jit_label_undefined;
        auto j_dst_rem = this->emit_constant(WORD_SIZE - length, jit_type_uint);
        auto j_dst_inclusive = jit_insn_le(j_func_, j_dst_lsb, j_dst_rem);
        jit_insn_branch_if(j_func_, j_dst_inclusive, &l_skip);

        auto j_dst_value1 = jit_insn_load_relative(j_func_, j_dst_ptr, sizeof(block_type), word_type_);
        auto j_mask1 = jit_insn_not(j_func_, j_mask0_s);
        auto j_mask1_s = jit_insn_ushr(j_func_, j_mask1, j_dst_rem);
        auto j_data1_s = jit_insn_ushr(j_func_, j_data_w, j_dst_rem);
        auto j_dst1 = this->emit_blend(j_mask1_s, j_dst_value1, j_data1_s);
        jit_insn_store_relative(j_func_, j_dst_ptr, sizeof(block_type), j_dst1);

        jit_insn_label(j_func_, &l_skip);
      }
    }
  }

  void emit_load_array_vector(jit_value_t j_dst_ptr,
                              uint32_t dst_width,
                              jit_value_t j_array_ptr,
                              jit_value_t j_index) {
    if (0 == (dst_width % 8)) {
      auto j_size = this->emit_constant(dst_width / 8, jit_type_uint);
      auto j_src_offset = jit_insn_mul(j_func_, j_index, j_size);
      auto j_src_ptr = jit_insn_load_elem_address(j_func_, j_array_ptr, j_src_offset, jit_type_ubyte);
      this->emit_memcpy(j_dst_ptr, j_src_ptr, dst_width / 8);
    } else {
      auto j_src_width = this->emit_constant(dst_width, jit_type_uint);
      auto j_src_offset = jit_insn_mul(j_func_, j_index, j_src_width);
      this->emit_copy_vector(j_dst_ptr, j_zero_, j_array_ptr, j_src_offset, dst_width);
    }
  }

  void emit_store_array_vector(jit_value_t j_array_ptr,
                               jit_value_t j_index,
                               jit_value_t j_src_ptr,
                               uint32_t src_width) {
    if (0 == (src_width % 8)) {
      auto j_size = this->emit_constant(src_width / 8, jit_type_uint);
      auto j_dst_offset = jit_insn_mul(j_func_, j_index, j_size);
      auto j_dst_ptr = jit_insn_load_elem_address(j_func_, j_array_ptr, j_dst_offset, jit_type_ubyte);
      this->emit_memcpy(j_dst_ptr, j_src_ptr, src_width / 8);
    } else {
      auto j_dst_width = this->emit_constant(src_width, jit_type_uint);
      auto j_dst_offset = jit_insn_mul(j_func_, j_index, j_dst_width);
      this->emit_copy_vector(j_array_ptr, j_dst_offset, j_src_ptr, j_zero_, src_width);
    }
  }

  void emit_copy_scalar(jit_value_t j_dst_ptr,
                        uint32_t dst_offset,
                        jit_value_t j_src,
                        uint32_t src_offset,
                        uint32_t length) {
    assert(length <= WORD_SIZE);
    auto w_dst_idx = dst_offset / WORD_SIZE;
    auto w_dst_lsb = dst_offset % WORD_SIZE;

    block_type mask0 = (WORD_MAX >> (WORD_SIZE - length)) << w_dst_lsb;
    block_type mask1 = ~mask0 >> (WORD_SIZE - length);

    auto j_src_offset = this->emit_constant(src_offset, jit_type_uint);
    auto j_dst_lsb = this->emit_constant(w_dst_lsb, jit_type_uint);
    auto j_src_s = jit_insn_ushr(j_func_, j_src, j_src_offset);
    auto j_src_w = this->emit_cast(j_src_s, word_type_);
    auto j_src_0 = jit_insn_shl(j_func_, j_src_w, j_dst_lsb);
    auto j_dst_0 = jit_insn_load_relative(j_func_, j_dst_ptr, w_dst_idx * sizeof(block_type), word_type_);
    auto j_mask0 = this->emit_constant(mask0, word_type_);
    auto j_blend0 = this->emit_blend(j_mask0, j_dst_0, j_src_0);
    jit_insn_store_relative(j_func_, j_dst_ptr, w_dst_idx * sizeof(block_type), j_blend0);
    if (w_dst_lsb > (WORD_SIZE - length)) {
      auto j_dst_1 = jit_insn_load_relative(j_func_, j_dst_ptr, (w_dst_idx + 1) * sizeof(block_type), word_type_);
      auto j_rem = this->emit_constant(WORD_SIZE - w_dst_lsb, jit_type_uint);
      auto j_src_1 = jit_insn_ushr(j_func_, j_src_w, j_rem);
      auto j_mask1 = this->emit_constant(mask1, word_type_);
      auto j_blend1 = this->emit_blend(j_mask1, j_dst_1, j_src_1);
      jit_insn_store_relative(j_func_, j_dst_ptr, (w_dst_idx + 1) * sizeof(block_type), j_blend1);
    }
  }

  void emit_copy_vector(jit_value_t j_dst_ptr,
                        uint32_t dst_offset,
                        jit_value_t j_src_ptr,
                        uint32_t src_offset,
                        uint32_t length) {
    if (0 == (dst_offset % 8)
     && 0 == (src_offset % 8)) {
      auto j_dst_ptr8 = jit_insn_add_relative(j_func_, j_dst_ptr, dst_offset / 8);
      auto j_src_ptr8 = jit_insn_add_relative(j_func_, j_src_ptr, src_offset / 8);
      this->emit_memcpy(j_dst_ptr8, j_src_ptr8, length / 8);
      uint32_t rem = length % 8;
      if (rem) {
        auto offset = length / 8;
        auto j_src_value = jit_insn_load_relative(j_func_, j_src_ptr8, offset, jit_type_ubyte);
        auto j_dst_value = jit_insn_load_relative(j_func_, j_dst_ptr8, offset, jit_type_ubyte);
        auto j_mask = this->emit_constant(0xff << rem, jit_type_ubyte);
        auto j_dst = this->emit_blend(j_mask, j_src_value, j_dst_value);
        jit_insn_store_relative(j_func_, j_dst_ptr8, offset, j_dst);
      }
    } else {
      auto j_dst_offset = this->emit_constant(dst_offset, jit_type_uint);
      auto j_src_offset = this->emit_constant(src_offset, jit_type_uint);
      this->emit_copy_vector(j_dst_ptr, j_dst_offset, j_src_ptr, j_src_offset, length);
    }
  }

  void emit_copy_vector(jit_value_t j_dst_ptr,
                        jit_value_t j_dst_offset,
                        jit_value_t j_src_ptr,
                        jit_value_t j_src_offset,
                        uint32_t length) {
    auto j_length = this->emit_constant(length, jit_type_uint);

    // call native function
    jit_type_t params[] = {jit_type_void_ptr, jit_type_uint, jit_type_void_ptr, jit_type_uint, jit_type_uint};
    jit_type_t j_sig = jit_type_create_signature(jit_abi_cdecl,
                                                 jit_type_void,
                                                 params,
                                                 __countof(params),
                                                 1);
    jit_value_t args[] = {j_dst_ptr, j_dst_offset, j_src_ptr, j_src_offset, j_length};
    jit_insn_call_native(j_func_,
                         "ext_copy_vector",
                         (void*)ext_copy_vector,
                         j_sig,
                         args,
                         __countof(args),
                         JIT_CALL_NOTHROW);
  }

  jit_value_t emit_append_slice_vector(jit_value_t j_dst,
                                       uint32_t dst_addr,
                                       uint32_t dst_width,
                                       uint32_t dst_offset,
                                       jit_value_t j_src,
                                       uint32_t length) {
    auto dst_idx = dst_offset / WORD_SIZE;
    auto dst_lsb = dst_offset % WORD_SIZE;
    j_dst = this->emit_append_slice_scalar(j_dst, dst_lsb, j_src);
    if ((dst_lsb + length) > WORD_SIZE) {
      // flush current block
      jit_insn_store_relative(j_func_, j_vars_, dst_addr + dst_idx * sizeof(block_type), j_dst);
      ++dst_idx;
      // copy remaining bits into next block
      auto j_rem = this->emit_constant(WORD_SIZE - dst_lsb, jit_type_uint);
      j_dst = jit_insn_ushr(j_func_, j_src, j_rem);
    }
    if ((dst_lsb + length) == WORD_SIZE
     || (dst_offset + length) == dst_width) {
      // flush current block
      jit_insn_store_relative(j_func_, j_vars_, dst_addr + dst_idx * sizeof(block_type), j_dst);
    }
    return j_dst;
  }

  jit_value_t emit_append_slice_scalar(jit_value_t j_dst,
                                       uint32_t dst_offset,
                                       jit_value_t j_src) {
    if (0 == dst_offset)
      return j_src;

    assert(j_dst != nullptr);
    assert(get_value_size(j_dst) == get_value_size(j_src));

    if (jit_value_is_constant(j_src)) {
      auto src = this->get_constant_value(j_src);
      if (0 == src)
        return j_dst;
      src <<= dst_offset;
      if (jit_value_is_constant(j_dst)) {
        auto dst = this->get_constant_value(j_dst);
        return this->emit_constant(src | dst, jit_value_get_type(j_src));
      } else {
        auto j_tmp = this->emit_constant(src, jit_value_get_type(j_src));
        return jit_insn_or(j_func_, j_tmp, j_dst);
      }
    }

    auto j_dst_lsb = this->emit_constant(dst_offset, jit_type_uint);
    auto j_src_s = jit_insn_shl(j_func_, j_src, j_dst_lsb);

    if (jit_value_is_constant(j_dst)
    &&  0 == this->get_constant_value(j_dst)) {
      return j_src_s;
    }

    return jit_insn_or(j_func_, j_src_s, j_dst);
  }

  void emit_clear_extra_bits(lnodeimpl* node) {
    __source_location();
    uint32_t dst_width = node->size();
    assert(dst_width <= WORD_SIZE);
    auto j_type = to_native_type(dst_width);
    auto native_size = to_native_size(dst_width);
    uint32_t extra_bits = dst_width % native_size;
    if (0 == extra_bits)
      return;
    auto j_dst = scalar_map_.at(node->id());
    auto j_mask = this->emit_constant(~(WORD_MAX << extra_bits), j_type);
    auto j_and = jit_insn_and(j_func_, j_dst, j_mask);
    scalar_map_[node->id()] = j_and;
  }

  jit_value_t emit_store_address(lnodeimpl* node, uint32_t offset = 0) {
    auto dst_addr = addr_map_.at(node->id()) + offset;
    return jit_insn_add_relative(j_func_, j_vars_, dst_addr);
  }


  jit_value_t emit_load_address(lnodeimpl* node, uint32_t offset = 0) {
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

  jit_value_t emit_load_scalar_relative(lnodeimpl* node, uint32_t offset, jit_type_t j_type) {
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

  jit_value_t emit_load_scalar_elem(lnodeimpl* node, uint32_t index, jit_type_t j_type) {
    auto nbytes = jit_type_get_size(j_type);
    return this->emit_load_scalar_relative(node, index * nbytes, j_type);
  }

  void emit_memcpy(jit_value_t j_dst_ptr, jit_value_t j_src_ptr, uint32_t length) {
    auto j_length = this->emit_constant(length, jit_type_uint);
    jit_insn_memcpy(j_func_, j_dst_ptr, j_src_ptr, j_length);
  }

  jit_value_t emit_sign_ext(jit_value_t j_value, uint32_t width) {
    auto j_type = jit_value_get_type(j_value);
    auto j_stype = to_signed_type(j_type);
    auto value_size = get_type_size(j_type);
    assert(value_size >= width);
    if (value_size == width) {
      return this->emit_cast(j_value, j_stype);
    }
    if (is_value_size(width)) {
      auto j_otype = to_signed_type(to_value_type(width));
      auto j_tmp = this->emit_cast(j_value, j_otype);
      return this->emit_cast(j_tmp, j_stype);
    } else {
      auto j_mask1 = this->emit_constant(WORD_MAX >> (value_size - width), j_type);
      auto j_mask2 = this->emit_constant(1ull << (width - 1), j_type);
      auto j_tmp1 = jit_insn_and(j_func_, j_value, j_mask1);
      auto j_tmp2 = jit_insn_xor(j_func_, j_tmp1, j_mask2);
      auto j_tmp3 = jit_insn_sub(j_func_, j_tmp2, j_mask2);
      return this->emit_cast(j_tmp3, j_stype);
    }
  }

  jit_value_t emit_blend(jit_value_t j_mask, jit_value_t j_false, jit_value_t j_true) {
    auto j_tmp1 = jit_insn_xor(j_func_, j_false, j_true);
    auto j_tmp2 = jit_insn_and(j_func_, j_tmp1, j_mask);
    return jit_insn_xor(j_func_, j_tmp2, j_false);
  }

  jit_value_t emit_address_of(jit_value_t j_value, jit_type_t j_type) {
    auto from_kind = jit_type_get_kind(jit_value_get_type(j_value));
    auto to_kind = jit_type_get_kind(j_type);
    if (from_kind == to_kind) {
      return jit_insn_address_of(j_func_, j_value);
    }
    auto j_tmp = jit_value_create(j_func_, j_type);
    jit_insn_store(j_func_, j_tmp, j_value);
    return jit_insn_address_of(j_func_, j_tmp);
  }

  jit_value_t emit_cast(jit_value_t j_value, jit_type_t to_type) {
    auto from_kind = jit_type_get_kind(jit_value_get_type(j_value));
    auto to_kind = jit_type_get_kind(to_type);
    if (from_kind == to_kind)
      return j_value;    
    if (jit_value_is_constant(j_value)) {
      auto value = this->get_constant_value(j_value);
      return this->emit_constant(value, to_type);
    } else {
      auto j_ret = jit_value_create(j_func_, to_type);
      jit_insn_store(j_func_, j_ret, j_value);
      return j_ret;
    }
  }

  void emit_range_check(jit_value_t j_value, uint32_t start, uint32_t end) {
    auto j_start = this->emit_constant(start, jit_type_uint);
    auto j_end = this->emit_constant(end, jit_type_uint);
    auto j_check1 = jit_insn_ge(j_func_, j_value, j_start);
    auto j_check2 = jit_insn_lt(j_func_, j_value, j_end);
    auto j_check = jit_insn_and(j_func_, j_check1, j_check2);
    jit_label_t l_skip = jit_label_undefined;
    jit_insn_branch_if(j_func_, j_check, &l_skip);
    jit_insn_return(j_func_, j_one_); // return 1
    jit_insn_label(j_func_, &l_skip);
  }

  jit_value_t emit_constant(long value, jit_type_t j_type) {
    auto nbytes = jit_type_get_size(j_type);
    if (nbytes <= 4) {
      return jit_value_create_nint_constant(j_func_, j_type, value);
    } else if (nbytes <= 8) {
      return jit_value_create_long_constant(j_func_, j_type, value);
    } else {
      std::abort();
    }
  }

  long get_constant_value(jit_value_t j_value) {
    assert(jit_value_is_constant(j_value));
    auto size = get_value_size(j_value);
    if (size <= 32) {
      uint32_t value = jit_value_get_nint_constant(j_value);
      auto j_type = jit_value_get_type(j_value);
      if (is_signed_type(j_type)) {
        auto nbytes = jit_type_get_size(j_type);
        switch (nbytes) {
        case 1:
          return static_cast<int8_t>(value);
        case 2:
          return static_cast<int16_t>(value);
        case 4:
          return static_cast<int32_t>(value);
        default:
          std::abort();
        }
      }
      return value;
    } else if (size <= 64) {
      return jit_value_get_long_constant(j_value);
    } else {
      std::abort();
    }
  }

#ifndef NDEBUG
  void emit_watch(jit_value_t j_value, const char* name) {
    // setup arguments
    auto j_arg0 = this->emit_cast(j_value, jit_type_ulong);

    auto name_len = strlen(name) + 1;
    memcpy(sim_ctx_->state.dbg + dbg_off_, name, name_len);
    auto j_arg1 = jit_insn_add_relative(j_func_, j_dbg_, dbg_off_);
    dbg_off_ += name_len;

    // call native function
    jit_type_t params[] = {jit_type_ulong, jit_type_void_ptr};
    jit_type_t j_sig = jit_type_create_signature(jit_abi_cdecl,
                                                 jit_type_void,
                                                 params,
                                                 __countof(params),
                                                 1);
    jit_value_t args[] = {j_arg0, j_arg1};
    jit_insn_call_native(j_func_,
                         "ext_watch",
                         (void*)ext_watch,
                         j_sig,
                         args,
                         __countof(args),
                         JIT_CALL_NOTHROW);
  }
#endif

  sim_ctx_t*      sim_ctx_;
  alloc_map_t     addr_map_;
  var_map_t       scalar_map_;
  jit_label_t     j_bypass_;
  bypass_set_t    bypass_nodes_;
  bool            bypass_enable_;
  jit_type_t      word_type_;
  jit_function_t  j_func_;
  jit_value_t     j_vars_;
  jit_value_t     j_ports_;  
#ifndef NDEBUG
  jit_value_t     j_dbg_;
  uint32_t        dbg_off_;
#endif
  jit_value_t     j_zero_;
  jit_value_t     j_one_;
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
    switch (node->type()) {
    case type_lit:
    case type_proxy:
    case type_input:
    case type_output:
    case type_sel:
    case type_cd:
    case type_reg:
    case type_mem:
    case type_marport:
    case type_msrport:
    case type_mwport:
    case type_time:
    case type_assert:
    case type_print:
    case type_tap:
      break;
    case type_alu: {
      auto alu = reinterpret_cast<aluimpl*>(node);
      switch (alu->op()) {
      case ch_op::eq:
      case ch_op::ne:
      case ch_op::lt:
      case ch_op::gt:
      case ch_op::le:
      case ch_op::ge:
        break;

      case ch_op::notl:
      case ch_op::andl:
      case ch_op::orl:
        if (!is_scalar(alu))
          return error_out("invalid alu size");
        break;
      case ch_op::inv:
        if (!is_scalar(alu))
          return error_out("invalid alu size");
        break;
      case ch_op::andb:
      case ch_op::orb:
      case ch_op::xorb:
        if (!is_scalar(alu) && -1 != alu->should_resize_opds())
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
        if (!is_scalar(alu))
          return error_out("invalid alu size");
        break;

      case ch_op::neg:
      case ch_op::add:
      case ch_op::sub:
        if (!is_scalar(alu))
          return error_out("invalid alu size");
        break;

      case ch_op::mult:
      case ch_op::div:
      case ch_op::mod:
        if (!is_scalar(alu))
          return error_out("invalid alu size");
        break;

      case ch_op::pad:
        if (!is_scalar(alu))
          return error_out("invalid alu size");
        break;
      default:
        std::abort();
        break;
      }
    } break;

    case type_udfc:
    case type_udfs:
      return error_out("invalid node type");
    default:
      std::abort();
    }
  }
  return true;
}

}

#endif
