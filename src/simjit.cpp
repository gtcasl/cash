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
static constexpr uint32_t INLINE_THRESHOLD = 4;

struct memaddr_t {
  jit_value_t base;
  uint32_t offset;
};

struct sblock_t {
  sblock_t() {
    this->clear();
  }

  void clear() {
    cd = nullptr;
    reset = nullptr;
    nodes.clear();
  }

  lnodeimpl* cd;
  lnodeimpl* reset;
  std::vector<lnodeimpl*> nodes;
};

class SrcLogger {
public:
  SrcLogger(jit_function_t func, const char* fname, const char* vname = nullptr) : func_(func) {
    jit_insn_new_block(func);
    auto block = jit_function_get_current(func);
    auto name = fname;
    if (vname) {
      auto tmp = stringf("%s @var=%s", fname, vname);
      auto tmp2 = new char[tmp.length() + 1]();
      strncpy(tmp2, tmp.c_str(), tmp.length());
      name = tmp2;
    }
    jit_block_set_meta(block, 0, (void*)name, nullptr);
  }
  ~SrcLogger() {
    jit_insn_new_block(func_);
    auto block = jit_function_get_current(func_);
    jit_block_set_meta(block, 0, (void*)"", nullptr);
  }
private:
  jit_function_t func_;
};

#define __align_word_size(...) ((((__VA_ARGS__) + WORD_MASK) / WORD_SIZE) * sizeof(block_type))
#define __countof(arr) (sizeof(arr) / sizeof(arr[0]))

#ifndef NDEBUG
  #define __source_info() SrcLogger logger(j_func_, __PRETTY_FUNCTION__)
#else
  #define __source_info()
#endif

#ifndef NDEBUG
  #define __source_info_ex(x) SrcLogger logger(j_func_, __PRETTY_FUNCTION__, x)
#else
  #define __source_info_ex(x)
#endif

#define __alu_call_relational(fname, ...) \
  [&]()->jit_value_t { \
    void* pfn; \
    if (is_signed) { \
      if (need_resize) { \
        pfn = reinterpret_cast<void*>(fname<true, block_type, StaticBitAccessor<true, true, block_type>>); \
      } else { \
        pfn = reinterpret_cast<void*>(fname<true, block_type, StaticBitAccessor<true, false, block_type>>); \
      } \
    } else { \
      if (need_resize) { \
        pfn = reinterpret_cast<void*>(fname<false, block_type, StaticBitAccessor<false, true, block_type>>); \
      } else { \
        pfn = reinterpret_cast<void*>(fname<false, block_type, ClearBitAccessor<block_type>>); \
      } \
    } \
    return this->emit_alu_call_relational(pfn, #fname, __VA_ARGS__); \
  }()

#define __alu_call_logical(fname, ...) \
  this->emit_alu_call_relational(reinterpret_cast<void*>(fname<block_type>), #fname, __VA_ARGS__)

#define __alu_call_bitwise(fname, ...) \
  void* pfn; \
  if (is_signed) { \
    if (need_resize) { \
      pfn = reinterpret_cast<void*>(fname<true, block_type, StaticBitAccessor<true, true, block_type>>); \
    } else { \
      pfn = reinterpret_cast<void*>(fname<true, block_type, StaticBitAccessor<true, false, block_type>>); \
    } \
  } else { \
    if (need_resize) { \
      pfn = reinterpret_cast<void*>(fname<false, block_type, StaticBitAccessor<false, true, block_type>>); \
    } else { \
      pfn = reinterpret_cast<void*>(fname<false, block_type, ClearBitAccessor<block_type>>); \
    } \
  } \
  this->emit_alu_call_bitwise(pfn, #fname, __VA_ARGS__)

#define __alu_call_reduce(fname, ...) \
  [&]()->jit_value_t { \
    auto pfn = reinterpret_cast<void*>(fname<block_type>); \
    return this->emit_alu_call_relational(pfn, #fname, __VA_ARGS__); \
  }()

#define __alu_call_shl(fname, ...) \
  auto pfn = reinterpret_cast<void*>(fname<block_type>); \
  this->emit_alu_call_shift(pfn, #fname, __VA_ARGS__)

#define __alu_call_shr(fname, ...) \
  auto pfn = is_signed ? fname<true, block_type> : fname<false, block_type>; \
  this->emit_alu_call_shift(reinterpret_cast<void*>(pfn), #fname, __VA_ARGS__)

#define __alu_call_arithmetic(fname, ...) \
  __alu_call_bitwise(fname, __VA_ARGS__)

#define __alu_call_arithmetic2(fname, ...) \
  auto pfn = is_signed ? fname<true, block_type> : fname<false, block_type>; \
  this->emit_alu_call_bitwise(reinterpret_cast<void*>(pfn), #fname, __VA_ARGS__)

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

static bool is_native_type(jit_type_t j_type) {
  auto kind = jit_type_get_kind(j_type);
  switch (kind) {
  case JIT_TYPE_INT:
  case JIT_TYPE_UINT:
  case JIT_TYPE_LONG:
  case JIT_TYPE_ULONG:
    return true;
  default:
    return false;
  }
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
  std::cout << "WATCH:" << name << " = " << value << std::endl;
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
    , l_bypass_(jit_label_undefined)
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
      this->resolve_branch(node);
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
        this->emit_node(reinterpret_cast<udfcimpl*>(node));
        break;
      case type_udfs:
        this->emit_node(reinterpret_cast<udfsimpl*>(node));
        break;
      case type_mem:
        break;
      default:
        std::abort();
        break;
      }
    }

    // create bypass label
    this->resolve_branch(nullptr);

    // return 0
    jit_insn_return(j_func_, j_zero_);

    // dump JIT assembly code
    if (platform::self().cflags() & cflags::dump_jit) {
      auto file = fopen("simjit.tac", "w");
      this->dump_ast(file, "simjit");
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
    sdata_type* srcs;

    static uint32_t size(printimpl* node) {
      auto num_srcs = node->srcs().size() + (node->has_pred() ? -1 : 0);
      uint32_t size = sizeof(print_data_t);
      size += node->format().size() + 1; // format
      size += node->enum_strings().size() * sizeof(enum_string_cb); // enum_strings
      size += num_srcs * sizeof(sdata_type); // src_values
      return size;
    }

    void init(printimpl* node, const compiler* cp) {
      auto buf = reinterpret_cast<uint8_t*>(this) + sizeof(print_data_t);

      auto fmt_len = node->format().size() + 1;
      format = reinterpret_cast<char*>(buf);
      memcpy(format, node->format().c_str(), fmt_len);
      buf += fmt_len;

      enum_strings = reinterpret_cast<enum_string_cb*>(buf);
      for (uint32_t i = 0, n = node->enum_strings().size(); i < n; ++i) {
        enum_strings[i] =  node->enum_string(i);
      }
      buf += node->enum_strings().size() * sizeof(enum_string_cb);

      srcs = reinterpret_cast<sdata_type*>(buf);
      uint32_t pred = node->has_pred() ? 1 : 0;
      for (uint32_t i = 0, n = node->srcs().size() - pred; i < n; ++i) {
        cp->init_sdata(&srcs[i], node->src(i + pred).impl());
      }
    }

    static void eval(print_data_t* self) {
      std::stringstream strbuf;
      for (const char *str = self->format; *str != '\0'; ++str) {
        if (*str == '{') {
          fmtinfo_t fmt;
          str = parse_format_index(&fmt, str);
          auto& src = self->srcs[fmt.index];
          switch (fmt.type) {
          case fmttype::Int:
            strbuf << src;
           break;
          case fmttype::Float:
            strbuf << bit_cast<float>(static_cast<int>(src));
           break;
          case fmttype::Enum:
            strbuf << self->enum_strings[fmt.index](static_cast<int>(src));
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

  struct assert_data_t {
    char* msg;
    sdata_type time;
    source_location sloc;

    static uint32_t size(assertimpl* node) {
      uint32_t size = sizeof(assert_data_t);
      size += node->msg().size() + 1; // msg
      return size;
    }

    void init(assertimpl* node, const compiler* cp) {
      auto buf = reinterpret_cast<uint8_t*>(this) + sizeof(print_data_t);

      auto msg_len = node->msg().size() + 1;
      msg = reinterpret_cast<char*>(buf);
      memcpy(msg, node->msg().c_str(), msg_len);
      buf += msg_len;

      cp->init_sdata(&time, node->time().impl());

      sloc = node->sloc();
    }

    static void eval(assert_data_t* self) {
      fprintf(stderr, "assertion failure at tick %ld, %s (%s:%d)\n",
              static_cast<uint64_t>(self->time), self->msg, self->sloc.file(), self->sloc.line());
      std::abort();
    }
  };

  struct udf_data_t {
    uint32_t dst_width;
    udf_iface* udf;
    sdata_type* srcs;

    static uint32_t size(udfimpl* node) {
      auto udf = node->udf();
      uint32_t size = sizeof(udf_data_t);
      size += udf->inputs_size().size() * sizeof(sdata_type); // srcs
      return size;
    }

    void init(udfimpl* node, const compiler* cp) {
      auto buf = reinterpret_cast<uint8_t*>(this) + sizeof(udf_data_t);
      dst_width = node->size();
      udf = node->udf();
      srcs = reinterpret_cast<sdata_type*>(buf);
      for (uint32_t i = 0, n = udf->inputs_size().size(); i < n; ++i) {
        cp->init_sdata(&srcs[i], node->src(i).impl());
      }
    }

    static void eval(block_type* out, udf_data_t* self) {
      sdata_type dst;
      dst.emplace(out, self->dst_width);
      self->udf->eval(dst, self->srcs);
      dst.emplace(nullptr);
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
    __source_info();

    uint32_t dst_width = node->size();
    if (dst_width <= WORD_SIZE) {
      auto j_ntype = to_native_type(dst_width);
      auto j_value = this->emit_constant(node->value().word(0), j_ntype);
      scalar_map_[node->id()] = j_value;
    }
  }

  void emit_node(proxyimpl* node) {
    __source_info();
    uint32_t dst_width = node->size();    
    auto j_ntype = to_native_type(dst_width);
    if (dst_width <= WORD_SIZE) {      
      jit_value_t j_tmp = nullptr;
      for (auto& range : node->ranges()) {
        auto& src = node->src(range.src_idx);
        auto j_src = this->emit_load_slice_scalar(src.impl(), range.src_offset, range.length);
        j_tmp = this->emit_append_slice_scalar(j_tmp, range.dst_offset, j_src, j_ntype);
      }
      auto j_ntype = to_native_type(dst_width);
      scalar_map_[node->id()] = this->emit_cast(j_tmp, j_ntype);
    } else {
      auto dst_addr = this->get_store_address(node);
      jit_value_t j_tmp = nullptr;
      for (auto& range : node->ranges()) {
        auto& src = node->src(range.src_idx);
        auto it = scalar_map_.find(src.id());
        if (it != scalar_map_.end()) {
          auto j_src = this->emit_load_slice_scalar(src.impl(), range.src_offset, range.length);
          j_tmp = this->emit_append_slice_vector(
                j_tmp, dst_addr, range.dst_offset, dst_width, j_src, range.length);
        } else {
          auto src_addr = this->get_load_address(src.impl());
          j_tmp = this->emit_append_slice_vector(
                j_tmp, dst_addr, range.dst_offset, dst_width, src_addr, range.src_offset, range.length);
        }
      }
    }
  }

  void emit_node(inputimpl* node) {
    __source_info_ex(node->name().c_str());
    uint32_t dst_width = node->size();    
    uint32_t addr = addr_map_.at(node->id());
    auto j_ptr = jit_insn_load_relative(j_func_, j_ports_, addr * sizeof(block_type*), jit_type_void_ptr);
    if (dst_width <= WORD_SIZE) {
      auto j_vtype = to_value_type(dst_width);
      auto j_ntype = to_native_type(dst_width);
      auto j_value = jit_insn_load_relative(j_func_, j_ptr, 0, j_vtype);
      scalar_map_[node->id()] = this->emit_cast(j_value, j_ntype);
    } else {
      input_map_[node->id()] = j_ptr;
    }
  }

  void emit_node(ioportimpl* node) {
    __source_info_ex(node->name().c_str());
    uint32_t dst_width = node->size();
    uint32_t addr = addr_map_.at(node->id());
    auto j_dst_ptr = jit_insn_load_relative(j_func_, j_ports_, addr * sizeof(block_type*), jit_type_void_ptr);
    if (dst_width <= WORD_SIZE) {
      auto j_src_value = scalar_map_.at(node->src(0).id());
      auto j_src_value_w = this->emit_cast(j_src_value, word_type_);
      jit_insn_store_relative(j_func_, j_dst_ptr, 0, j_src_value_w);
    } else {
      auto j_src_ptr = this->emit_load_address(node->src(0).impl());
      this->emit_memcpy(j_dst_ptr, j_src_ptr, ceildiv(dst_width, 8));
    }
  }

  void emit_node(aluimpl* node) {
    __source_info();

    struct auto_store_addr_t {
      compiler* C;
      lnodeimpl* node;
      jit_value_t ptr;
      jit_value_t bkstore;

      auto_store_addr_t(compiler* C, lnodeimpl* node) : C(C), node(node) {
        if (node->size() <= WORD_SIZE) {
          bkstore = jit_value_create(C->j_func_, C->word_type_);
          jit_insn_store(C->j_func_, bkstore, C->j_zero_);
          ptr = C->emit_address_of(bkstore, C->word_type_);
        } else {
          bkstore = nullptr;
          ptr = C->emit_store_address(node);
        }
      }

      ~auto_store_addr_t() {
        if (bkstore) {
          auto j_ntype = to_native_type(node->size());
          C->scalar_map_[node->id()] = C->emit_cast(bkstore, j_ntype);
        }
      }
    };

    uint32_t dst_width = node->size();
    auto j_ntype = to_native_type(dst_width);
    auto native_size = to_native_size(dst_width);
    bool is_signed = node->is_signed();

    bool is_scalar = (dst_width <= bitwidth_v<block_type>);
    if (node->srcs().size() > 0) {
      is_scalar &= (node->src(0).size() <= bitwidth_v<block_type>);
      if (CH_OP_CLASS(node->op()) != op_flags::shift
       && node->srcs().size() > 1) {
        is_scalar &= (node->src(1).size() <= bitwidth_v<block_type>);
      }
    }

    auto need_resize = node->should_resize_opds();
    auto j_src0 = this->emit_alu_operand(node, 0, is_scalar, need_resize);
    auto j_src1 = this->emit_alu_operand(node, 1, is_scalar, need_resize);

    switch (node->op()) {
    case ch_op::eq:
      if (is_scalar) {
        auto j_dst = jit_insn_eq(j_func_, j_src0, j_src1);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
      } else {
        auto j_dst = this->emit_eq_vector(j_src0, node->src(0).size(), j_src1, node->src(1).size(), is_signed);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
      }
      break;
    case ch_op::ne:
      if (is_scalar) {
        auto j_dst = jit_insn_ne(j_func_, j_src0, j_src1);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
      } else {
        auto j_dst = this->emit_eq_vector(j_src0, node->src(0).size(), j_src1, node->src(1).size(), is_signed);
        auto j_dst_n = jit_insn_not(j_func_, j_dst);
        scalar_map_[node->id()] = this->emit_cast(j_dst_n, j_ntype);
      }
      break;

    case ch_op::lt:
      if (is_scalar) {
        auto j_src0_s = is_signed ? this->emit_sign_ext(j_src0, node->src(0).size()) : j_src0;
        auto j_src1_s = is_signed ? this->emit_sign_ext(j_src1, node->src(1).size()) : j_src1;
        auto j_dst = jit_insn_lt(j_func_, j_src0_s, j_src1_s);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
      } else {
        auto j_dst = __alu_call_relational(bv_lt_vector, j_src0, node->src(0).size(), j_src1, node->src(1).size());
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
      }
      break;
    case ch_op::gt:
      if (is_scalar) {
        auto j_src0_s = is_signed ? this->emit_sign_ext(j_src0, node->src(0).size()) : j_src0;
        auto j_src1_s = is_signed ? this->emit_sign_ext(j_src1, node->src(1).size()) : j_src1;
        auto j_dst = jit_insn_gt(j_func_, j_src0_s, j_src1_s);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
      } else {
        auto j_dst = __alu_call_relational(bv_lt_vector, j_src1, node->src(1).size(), j_src0, node->src(0).size());
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
      }
      break;
    case ch_op::le:
      if (is_scalar) {
        auto j_src0_s = is_signed ? this->emit_sign_ext(j_src0, node->src(0).size()) : j_src0;
        auto j_src1_s = is_signed ? this->emit_sign_ext(j_src1, node->src(1).size()) : j_src1;
        auto j_dst = jit_insn_le(j_func_, j_src0_s, j_src1_s);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
      } else {
        auto j_dst = __alu_call_relational(bv_lt_vector, j_src1, node->src(1).size(), j_src0, node->src(0).size());
        auto j_dst_n = jit_insn_not(j_func_, j_dst);
        scalar_map_[node->id()] = this->emit_cast(j_dst_n, j_ntype);
      }
      break;
    case ch_op::ge:
      if (is_scalar) {
        auto j_src0_s = is_signed ? this->emit_sign_ext(j_src0, node->src(0).size()) : j_src0;
        auto j_src1_s = is_signed ? this->emit_sign_ext(j_src1, node->src(1).size()) : j_src1;
        auto j_dst = jit_insn_ge(j_func_, j_src0_s, j_src1_s);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
      } else {
        auto j_dst = __alu_call_relational(bv_lt_vector, j_src0, node->src(0).size(), j_src1, node->src(1).size());
        auto j_dst_n = jit_insn_not(j_func_, j_dst);
        scalar_map_[node->id()] = this->emit_cast(j_dst_n, j_ntype);
      }
      break;

    case ch_op::notl:
      if (is_scalar) {
        auto j_dst = jit_insn_to_not_bool(j_func_, j_src0);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
      } else {
        auto j_dst = __alu_call_logical(bv_notl_vector, j_src0, node->src(0).size());
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
      }
      break;
    case ch_op::andl:
      if (is_scalar) {
        auto j_src0_b = (node->src(0).size() > 1) ? jit_insn_to_bool(j_func_, j_src0) : j_src0;
        auto j_src1_b = (node->src(1).size() > 1) ? jit_insn_to_bool(j_func_, j_src1) : j_src1;
        auto j_dst = jit_insn_and(j_func_, j_src0_b, j_src1_b);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
      } else {
        auto j_dst = __alu_call_logical(bv_andl_vector, j_src0, node->src(0).size(), j_src1, node->src(1).size());
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
      }
      break;
    case ch_op::orl:
      if (is_scalar) {
        auto j_src0_b = (node->src(0).size() > 1) ? jit_insn_to_bool(j_func_, j_src0) : j_src0;
        auto j_src1_b = (node->src(1).size() > 1) ? jit_insn_to_bool(j_func_, j_src1) : j_src1;
        auto j_dst = jit_insn_or(j_func_, j_src0_b, j_src1_b);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
      } else {
        auto j_dst = __alu_call_logical(bv_orl_vector, j_src0, node->src(0).size(), j_src1, node->src(1).size());
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
      }
      break;

    case ch_op::inv:
      if (is_scalar) {
        auto j_dst = jit_insn_not(j_func_, j_src0);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
        this->emit_clear_extra_bits(node);
      } else {
        auto_store_addr_t auto_dst(this, node);
        __alu_call_bitwise(bv_inv_vector, auto_dst.ptr, dst_width, j_src0, node->src(0).size());
      }      
      break;
    case ch_op::andb:
      if (is_scalar) {
        auto j_dst = jit_insn_and(j_func_, j_src0, j_src1);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
      } else {
        if (need_resize
         || dst_width > INLINE_THRESHOLD * WORD_SIZE) {
          auto_store_addr_t auto_dst(this, node);
          __alu_call_bitwise(bv_and_vector, auto_dst.ptr, dst_width, j_src0, node->src(0).size(), j_src1, node->src(1).size());
        } else {
          auto dst_addr = addr_map_.at(node->id());
          uint32_t num_words = ceildiv(dst_width, WORD_SIZE);
          for (uint32_t i = 0; i < num_words; ++i) {
            auto j_src0 = this->emit_load_scalar_elem(node->src(0).impl(), i, word_type_);
            auto j_src1 = this->emit_load_scalar_elem(node->src(1).impl(), i, word_type_);
            auto j_dst  = jit_insn_and(j_func_, j_src0, j_src1);            
            auto j_dst_w = this->emit_cast(j_dst, word_type_);
            jit_insn_store_relative(j_func_, j_vars_, dst_addr + i * sizeof(block_type), j_dst_w);
          }
        }
      }
      break;
    case ch_op::orb:
      if (is_scalar) {
        auto j_dst = jit_insn_or(j_func_, j_src0, j_src1);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
      } else {
        if (need_resize
         || dst_width > INLINE_THRESHOLD * WORD_SIZE) {
          auto_store_addr_t auto_dst(this, node);
          __alu_call_bitwise(bv_or_vector, auto_dst.ptr, dst_width, j_src0, node->src(0).size(), j_src1, node->src(1).size());
        } else {
          auto dst_addr = addr_map_.at(node->id());
          uint32_t num_words = ceildiv(dst_width, WORD_SIZE);
          for (uint32_t i = 0; i < num_words; ++i) {
            auto j_src0 = this->emit_load_scalar_elem(node->src(0).impl(), i, word_type_);
            auto j_src1 = this->emit_load_scalar_elem(node->src(1).impl(), i, word_type_);
            auto j_dst  = jit_insn_or(j_func_, j_src0, j_src1);
            auto j_dst_w = this->emit_cast(j_dst, word_type_);
            jit_insn_store_relative(j_func_, j_vars_, dst_addr + i * sizeof(block_type), j_dst_w);
          }
        }
      }
      break;
    case ch_op::xorb:
      if (is_scalar) {
        auto j_dst = jit_insn_xor(j_func_, j_src0, j_src1);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
      } else {
        if (need_resize
         || dst_width > INLINE_THRESHOLD * WORD_SIZE) {
          auto_store_addr_t auto_dst(this, node);
          __alu_call_bitwise(bv_xor_vector, auto_dst.ptr, dst_width, j_src0, node->src(0).size(), j_src1, node->src(1).size());
        } else {
          auto dst_addr = addr_map_.at(node->id());
          uint32_t num_words = ceildiv(dst_width, WORD_SIZE);
          for (uint32_t i = 0; i < num_words; ++i) {
            auto j_src0 = this->emit_load_scalar_elem(node->src(0).impl(), i, word_type_);
            auto j_src1 = this->emit_load_scalar_elem(node->src(1).impl(), i, word_type_);
            auto j_dst  = jit_insn_xor(j_func_, j_src0, j_src1);
            auto j_dst_w = this->emit_cast(j_dst, word_type_);
            jit_insn_store_relative(j_func_, j_vars_, dst_addr + i * sizeof(block_type), j_dst_w);
          }
        }
      }
      break;

    case ch_op::andr:
      if (is_scalar) {
        auto j_max = this->emit_constant(WORD_MAX >> (WORD_SIZE - node->src(0).size()), j_ntype);
        auto j_dst = jit_insn_eq(j_func_, j_src0, j_max);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
        this->emit_clear_extra_bits(node);
      } else {
        auto j_dst = __alu_call_reduce(bv_andr_vector, j_src0, node->src(0).size());
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
      }
      break;
    case ch_op::orr:
      if (is_scalar) {
        auto j_dst = jit_insn_to_bool(j_func_, j_src0);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
        this->emit_clear_extra_bits(node);
      } else {
        auto j_dst = __alu_call_reduce(bv_orr_vector, j_src0, node->src(0).size());
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
      }
      break;
    case ch_op::xorr:
      if (is_scalar) {
        auto j_dst = this->emit_xorr_scalar(j_src0, node->src(0).size());
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
        this->emit_clear_extra_bits(node);
      } else {
        auto j_dst = __alu_call_reduce(bv_xorr_vector, j_src0, node->src(0).size());
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
      }
      break;

    case ch_op::shl:
      if (is_scalar) {
        jit_label_t l_else = jit_label_undefined;
        jit_label_t l_exit = jit_label_undefined;
        auto j_dst = jit_value_create(j_func_, j_ntype);
        scalar_map_[node->id()] = j_dst;
        auto j_max = this->emit_constant(native_size, j_ntype);
        auto j_overflow = jit_insn_ge(j_func_, j_src1, j_max);
        jit_insn_branch_if(j_func_, j_overflow, &l_else);
        auto j_src0_n = this->emit_cast(j_src0, j_ntype);
        auto j_tmp = jit_insn_shl(j_func_, j_src0_n, j_src1);
        jit_insn_store(j_func_, j_dst, j_tmp);
        jit_insn_branch(j_func_, &l_exit);
        jit_insn_label(j_func_, &l_else);
        jit_insn_store(j_func_, j_dst, j_zero_);
        jit_insn_label(j_func_, &l_exit);
        this->emit_clear_extra_bits(node);
      } else {
        auto_store_addr_t auto_dst(this, node);
        __alu_call_shl(bv_shl_vector, auto_dst.ptr, dst_width, j_src0, node->src(0).size(), j_src1);
      }
      break;
    case ch_op::shr:
      if (is_scalar) {
        jit_label_t l_else = jit_label_undefined;
        jit_label_t l_exit = jit_label_undefined;        
        auto j_dst = jit_value_create(j_func_, j_ntype);
        scalar_map_[node->id()] = j_dst;                
        if (is_signed) {
          auto j_src0_x = (dst_width > node->src(0).size()) ? this->emit_cast(j_src0, j_ntype) : j_src0;
          auto j_src0_s = this->emit_sign_ext(j_src0_x, node->src(0).size());
          auto src0_type = jit_value_get_type(j_src0_s);
          auto src0_size = get_value_size(j_src0_s);
          auto j_max = this->emit_constant(src0_size, src0_type);
          auto j_overflow = jit_insn_ge(j_func_, j_src1, j_max);
          jit_insn_branch_if(j_func_, j_overflow, &l_else);
          auto j_tmp1 = jit_insn_shr(j_func_, j_src0_s, j_src1);
          jit_insn_store(j_func_, j_dst, j_tmp1);
          jit_insn_branch(j_func_, &l_exit);
          jit_insn_label(j_func_, &l_else);
          auto j_maxM1 = this->emit_constant(src0_size - 1, src0_type);
          auto j_tmp2 = jit_insn_shr(j_func_, j_src0_s, j_maxM1);
          jit_insn_store(j_func_, j_dst, j_tmp2);
          jit_insn_label(j_func_, &l_exit);
          this->emit_clear_extra_bits(node);
        } else {          
          auto src0_type = jit_value_get_type(j_src0);
          auto src0_size = get_value_size(j_src0);
          auto j_max = this->emit_constant(src0_size, src0_type);
          auto j_overflow = jit_insn_ge(j_func_, j_src1, j_max);
          jit_insn_branch_if(j_func_, j_overflow, &l_else);
          auto j_tmp = jit_insn_ushr(j_func_, j_src0, j_src1);
          jit_insn_store(j_func_, j_dst, j_tmp);
          jit_insn_branch(j_func_, &l_exit);
          jit_insn_label(j_func_, &l_else);
          jit_insn_store(j_func_, j_dst, j_zero_);
          jit_insn_label(j_func_, &l_exit);
        }
      } else {
        auto_store_addr_t auto_dst(this, node);
        __alu_call_shr(bv_shr_vector, auto_dst.ptr, dst_width, j_src0, node->src(0).size(), j_src1);
      }
      break;

    case ch_op::neg:
      if (is_scalar) {
        auto j_dst = jit_insn_neg(j_func_, j_src0);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
        this->emit_clear_extra_bits(node);
      } else {
        auto_store_addr_t auto_dst(this, node);
        __alu_call_arithmetic(bv_neg_vector, auto_dst.ptr, dst_width, j_src0, node->src(0).size());
      }
      break;
    case ch_op::add:
      if (is_scalar) {
        auto j_dst = jit_insn_add(j_func_, j_src0, j_src1);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
        this->emit_clear_extra_bits(node);
      } else {
        auto_store_addr_t auto_dst(this, node);
        __alu_call_arithmetic(bv_add_vector, auto_dst.ptr, dst_width, j_src0, node->src(0).size(), j_src1, node->src(1).size());
      }
      break;
    case ch_op::sub:
      if (is_scalar) {
        auto j_dst = jit_insn_sub(j_func_, j_src0, j_src1);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
        this->emit_clear_extra_bits(node);
      } else {
        auto_store_addr_t auto_dst(this, node);
        __alu_call_arithmetic(bv_sub_vector, auto_dst.ptr, dst_width, j_src0, node->src(0).size(), j_src1, node->src(1).size());
      }
      break;

    case ch_op::mult:
      if (is_scalar) {
        auto j_src0_d = this->emit_cast(j_src0, j_ntype);
        auto j_src1_d = this->emit_cast(j_src1, j_ntype);
        auto j_src0_s = is_signed ? this->emit_sign_ext(j_src0_d, node->src(0).size()) : j_src0_d;
        auto j_src1_s = is_signed ? this->emit_sign_ext(j_src1_d, node->src(1).size()) : j_src1_d;
        auto j_dst = jit_insn_mul(j_func_, j_src0_s, j_src1_s);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
        this->emit_clear_extra_bits(node);
      } else {
        auto_store_addr_t auto_dst(this, node);
        __alu_call_arithmetic2(bv_mult_vector, auto_dst.ptr, dst_width, j_src0, node->src(0).size(), j_src1, node->src(1).size());
      }
      break;
    case ch_op::div:
      if (is_scalar) {
        auto j_src0_s = is_signed ? this->emit_sign_ext(j_src0, node->src(0).size()) : j_src0;
        auto j_src1_s = is_signed ? this->emit_sign_ext(j_src1, node->src(1).size()) : j_src1;
        auto j_dst = jit_insn_div(j_func_, j_src0_s, j_src1_s);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
        this->emit_clear_extra_bits(node);
      } else {
        auto_store_addr_t auto_dst(this, node);
        __alu_call_arithmetic2(bv_div_vector, auto_dst.ptr, dst_width, j_src0, node->src(0).size(), j_src1, node->src(1).size());
      }
      break;
    case ch_op::mod:
      if (is_scalar) {
        auto j_src0_s = is_signed ? this->emit_sign_ext(j_src0, node->src(0).size()) : j_src0;
        auto j_src1_s = is_signed ? this->emit_sign_ext(j_src1, node->src(1).size()) : j_src1;
        auto j_dst = jit_insn_rem(j_func_, j_src0_s, j_src1_s);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
        this->emit_clear_extra_bits(node);
      } else {
        auto_store_addr_t auto_dst(this, node);
        __alu_call_arithmetic2(bv_mod_vector, auto_dst.ptr, dst_width, j_src0, node->src(0).size(), j_src1, node->src(1).size());
      }
      break;

    case ch_op::pad:
      if (is_scalar) {
        if (node->is_signed()) {
          auto j_dst = this->emit_sign_ext(j_src0, node->src(0).size());
          scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
          this->emit_clear_extra_bits(node);
        } else {
          scalar_map_[node->id()]= j_src0;
        }
      } else {
        auto_store_addr_t auto_dst(this, node);
        __alu_call_arithmetic2(bv_pad_vector, auto_dst.ptr, dst_width, j_src0, node->src(0).size());
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
                               bool need_resize) {
    __source_info();
    if (opd >= node->srcs().size())
      return nullptr;
    auto src = node->src(opd).impl();
    auto is_signed = node->is_signed();
    if (is_scalar) {
      auto it = scalar_map_.find(src->id());
      if (it != scalar_map_.end()) {
        auto j_value = scalar_map_.at(src->id());
        if (need_resize && is_signed) {
          j_value = this->emit_sign_ext(j_value, src->size());
        }
        return j_value;
      } else {
        assert(op_flags::shift == CH_OP_CLASS(node->op()));
        return this->emit_load_scalar_relative(src, 0, jit_type_uint);
      }
    } else {
      auto it = scalar_map_.find(src->id());
      if (it != scalar_map_.end()) {
        if (op_flags::shift == CH_OP_CLASS(node->op())
         && 1 == opd) {
          return this->emit_cast(it->second, jit_type_uint);
        } else {
          return this->emit_address_of(it->second, word_type_);
        }
      } else {
        if (op_flags::shift == CH_OP_CLASS(node->op())
         && 1 == opd) {
          return this->emit_load_scalar_relative(src, 0, jit_type_uint);
        } else {
          return this->emit_load_address(src);
        }
      }
    }
  }

  jit_value_t emit_alu_call_relational(void* pfn,
                                       const char* name,
                                       jit_value_t j_in,
                                       uint32_t in_size) {
    __source_info();

    // setup arguments
    auto j_in_size = this->emit_constant(in_size, jit_type_uint);

    // call native function
    jit_type_t params[] = {jit_type_void_ptr, jit_type_uint};
    jit_type_t j_sig = jit_type_create_signature(jit_abi_cdecl,
                                                 jit_type_uint,
                                                 params,
                                                 __countof(params),
                                                 1);
    jit_value_t args[] = {j_in, j_in_size};
    return jit_insn_call_native(j_func_,
                                name,
                                pfn,
                                j_sig,
                                args,
                                __countof(args),
                                JIT_CALL_NOTHROW);
  }

  jit_value_t emit_alu_call_relational(void* pfn,
                                       const char* name,
                                       jit_value_t j_lhs,
                                       uint32_t lhs_size,
                                       jit_value_t j_rhs,
                                       uint32_t rhs_size) {
    __source_info();

    // setup arguments
    auto j_lhs_size = this->emit_constant(lhs_size, jit_type_uint);
    auto j_rhs_size = this->emit_constant(rhs_size, jit_type_uint);

    // call native function
    jit_type_t params[] = {jit_type_void_ptr, jit_type_uint,
                           jit_type_void_ptr, jit_type_uint};
    jit_type_t j_sig = jit_type_create_signature(jit_abi_cdecl,
                                                 jit_type_uint,
                                                 params,
                                                 __countof(params),
                                                 1);
    jit_value_t args[] = {j_lhs, j_lhs_size, j_rhs, j_rhs_size};
    return jit_insn_call_native(j_func_,
                                name,
                                pfn,
                                j_sig,
                                args,
                                __countof(args),
                                JIT_CALL_NOTHROW);
  }

  void emit_alu_call_bitwise(void* pfn,
                            const char* name,
                            jit_value_t j_out,
                            uint32_t out_size,
                            jit_value_t j_in,
                            uint32_t in_size) {
    __source_info();

    // setup arguments
    auto j_out_size = this->emit_constant(out_size, jit_type_uint);
    auto j_in_size = this->emit_constant(in_size, jit_type_uint);

    // call native function
    jit_type_t params[] = {jit_type_void_ptr, jit_type_uint,
                           jit_type_void_ptr, jit_type_uint};
    jit_type_t j_sig = jit_type_create_signature(jit_abi_cdecl,
                                                 jit_type_void,
                                                 params,
                                                 __countof(params),
                                                 1);
    jit_value_t args[] = {j_out, j_out_size, j_in, j_in_size};
    jit_insn_call_native(j_func_,
                         name,
                         pfn,
                         j_sig,
                         args,
                         __countof(args),
                         JIT_CALL_NOTHROW);
  }

  void emit_alu_call_bitwise(void* pfn,
                            const char* name,
                            jit_value_t j_out,
                            uint32_t out_size,
                            jit_value_t j_lhs,
                            uint32_t lhs_size,
                            jit_value_t j_rhs,
                            uint32_t rhs_size) {
    __source_info();

    // setup arguments
    auto j_out_size = this->emit_constant(out_size, jit_type_uint);
    auto j_lhs_size = this->emit_constant(lhs_size, jit_type_uint);
    auto j_rhs_size = this->emit_constant(rhs_size, jit_type_uint);

    // call native function
    jit_type_t params[] = {jit_type_void_ptr, jit_type_uint,
                           jit_type_void_ptr, jit_type_uint,
                           jit_type_void_ptr, jit_type_uint};
    jit_type_t j_sig = jit_type_create_signature(jit_abi_cdecl,
                                                 jit_type_void,
                                                 params,
                                                 __countof(params),
                                                 1);
    jit_value_t args[] = {j_out, j_out_size, j_lhs, j_lhs_size, j_rhs, j_rhs_size};
    jit_insn_call_native(j_func_,
                         name,
                         pfn,
                         j_sig,
                         args,
                         __countof(args),
                         JIT_CALL_NOTHROW);
  }

  void emit_alu_call_shift(void* pfn,
                           const char* name,
                           jit_value_t j_out,
                           uint32_t out_size,
                           jit_value_t j_lhs,
                           uint32_t lhs_size,
                           jit_value_t j_rhs) {
   __source_info();

   // setup arguments
   auto j_out_size = this->emit_constant(out_size, jit_type_uint);
   auto j_lhs_size = this->emit_constant(lhs_size, jit_type_uint);
   assert(32 == get_value_size(j_rhs));

   // call native function
   jit_type_t params[] = {jit_type_void_ptr, jit_type_uint,
                          jit_type_void_ptr, jit_type_uint,
                          jit_type_uint};
   jit_type_t j_sig = jit_type_create_signature(jit_abi_cdecl,
                                                jit_type_void,
                                                params,
                                                __countof(params),
                                                1);
   jit_value_t args[] = {j_out, j_out_size, j_lhs, j_lhs_size, j_rhs};
   jit_insn_call_native(j_func_,
                        name,
                        pfn,
                        j_sig,
                        args,
                        __countof(args),
                        JIT_CALL_NOTHROW);

  }

  void emit_node(selectimpl* node) {
    __source_info();

    jit_label_t l_exit = jit_label_undefined;

    uint32_t dst_width = node->size();   
    bool is_scalar = (dst_width <= WORD_SIZE);
    auto j_ntype = to_native_type(dst_width);

    jit_value_t j_dst = nullptr;
    if (is_scalar) {
      j_dst = jit_value_create(j_func_, j_ntype);
      scalar_map_[node->id()] = j_dst;
    }

    if (node->has_key()) {      
      uint32_t i = 1, l = node->srcs().size() - 1;
      for (;i < l; i += 2) {
        jit_label_t l_skip = jit_label_undefined;
        uint32_t key_size = node->key().size();
        if (key_size <= WORD_SIZE) {
          auto j_key = scalar_map_.at(node->src(0).id());
          auto j_val = scalar_map_.at(node->src(i).id());
          auto j_eq = jit_insn_eq(j_func_, j_key, j_val);
          jit_insn_branch_if_not(j_func_, j_eq, &l_skip);
        } else {
          auto j_key_ptr = this->emit_store_address(node->src(0).impl());
          auto j_val_ptr = this->emit_load_address(node->src(i).impl());
          auto j_eq = this->emit_eq_vector(j_key_ptr, key_size, j_val_ptr, key_size, false);
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
    if (l_exit != jit_label_undefined) {
      jit_insn_label(j_func_, &l_exit);
    }
  }

  void emit_node(cdimpl* node) {
    __source_info();

    auto j_clk = scalar_map_.at(node->src(0).id());
    auto addr = addr_map_.at(node->id());
    auto j_prev_clk = jit_insn_load_relative(j_func_, j_vars_, addr, jit_type_uint);
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
      jit_label_t l_skip = jit_label_undefined;
      jit_insn_branch_if_not(j_func_, j_changed, &l_skip);
      l_bypass_ = l_skip;
    } else {
      scalar_map_[node->id()] = j_changed;
    }
  }

  void resolve_branch(lnodeimpl* node) {
    if (sblock_.cd
     && ((node
       && (!is_snode_type(node->type())
        || node->type() != type_reg
        || get_snode_reset(node) != sblock_.reset))
      || !node)) {
      this->flush_sblock();
    }
     if (!bypass_enable_)
       return;
     if (node) {
       if (bypass_nodes_.count(node->id())) {
         jit_insn_label_tight(j_func_, &l_bypass_);
         bypass_enable_ = false;
       }
     } else {
       jit_insn_label_tight(j_func_, &l_bypass_);
       bypass_enable_ = false;
     }
   }

  void flush_sblock() {
    __source_info();

    jit_label_t l_exit = jit_label_undefined;

    // emit clock domain
    bool merge_cd_enable = false;
    if (!bypass_enable_) {
      if (!sblock_.reset) {
        auto it = sblock_.nodes.begin();
        auto end = sblock_.nodes.end();
        auto enable = get_snode_enable(*it++);
        if (enable) {
          merge_cd_enable = true;
          while (it != end) {
            if (get_snode_enable(*it++) != enable) {
              merge_cd_enable = false;
              break;
            }
          }
        }
      }
      if (!merge_cd_enable) {
        auto j_cd = scalar_map_.at(sblock_.cd->id());
        jit_insn_branch_if_not(j_func_, j_cd, &l_exit);
      }
    }

    if (sblock_.reset) {
      // emit reset nodes
      jit_label_t l_skip = jit_label_undefined;
      auto j_reset = scalar_map_.at(sblock_.reset->id());
      jit_insn_branch_if_not(j_func_, j_reset, &l_skip);

      for (auto node : sblock_.nodes) {
        if (node->type() != type_reg)
          continue;
        this->emit_snode_init(reinterpret_cast<regimpl*>(node));
      }

      jit_insn_branch(j_func_, &l_exit);
      jit_insn_label(j_func_, &l_skip);
    }

    // emit enable nodes
    jit_label_t l_skip = jit_label_undefined;
    lnodeimpl* cur_enable = nullptr;
    for (auto node : sblock_.nodes) {
      auto enable = get_snode_enable(node);
      if (enable != cur_enable) {
        if (cur_enable) {
          jit_insn_label(j_func_, &l_skip);
        };
        if (enable) {
          auto j_enable = scalar_map_.at(enable->id());
          if (merge_cd_enable) {
            auto j_cd = scalar_map_.at(sblock_.cd->id());
            auto j_pred = jit_insn_and(j_func_, j_cd, j_enable);
            jit_insn_branch_if_not(j_func_, j_pred, &l_skip);
          } else {
            jit_insn_branch_if_not(j_func_, j_enable, &l_skip);
          }
        }
        cur_enable = enable;
      }
      switch (node->type()) {
      case type_reg:
        this->emit_snode_value(reinterpret_cast<regimpl*>(node));
        break;
      case type_msrport:
        this->emit_snode_value(reinterpret_cast<msrportimpl*>(node));
        break;
      case type_mwport:
        this->emit_snode_value(reinterpret_cast<mwportimpl*>(node));
        break;
      case type_udfs:
        this->emit_snode_value(reinterpret_cast<udfsimpl*>(node));
        break;
      default:
        std::abort();
      }
    }
    if (cur_enable) {
      jit_insn_label(j_func_, &l_skip);
    };
    if (l_exit != jit_label_undefined) {
      jit_insn_label_tight(j_func_, &l_exit);
    }
    sblock_.clear();
  }

  void emit_node(regimpl* node) {
    sblock_.cd = node->cd().impl();
    sblock_.reset = get_snode_reset(node);
    sblock_.nodes.push_back(node);
  }

  void emit_snode_init(regimpl* node) {
    assert(node->has_init_data());

    uint32_t dst_width = node->size();
    auto j_vtype = to_value_type(dst_width);
    auto is_scalar = (dst_width <= WORD_SIZE);
    auto dst_addr = addr_map_.at(node->id());

    jit_value_t j_dst = nullptr;
    jit_value_t j_init_data = nullptr;

    if (is_scalar) {
      j_dst = scalar_map_.at(node->id());
      j_init_data = scalar_map_.at(node->init_data().id());
    }

    if (node->is_pipe()) {
      uint32_t pipe_length = node->length() - 1;
      uint32_t pipe_width = pipe_length * dst_width;
      auto j_pipe_vtype = to_value_type(pipe_width);
      auto j_pipe_ntype = to_native_type(pipe_width);
      uint32_t pipe_addr = dst_addr + __align_word_size(dst_width);
      auto is_pipe_scalar = (pipe_width <= WORD_SIZE);
      if (is_pipe_scalar) {
        assert(is_scalar);        
        // reset dst register                                
        auto j_init_data_v = this->emit_cast(j_init_data, j_vtype);
        jit_insn_store_relative(j_func_, j_vars_, dst_addr, j_init_data_v);
        jit_insn_store(j_func_, j_dst, j_init_data);

        // reset pipe registers        
        auto j_init_data_p = this->emit_cast(j_init_data, j_pipe_ntype);
        jit_value_t j_tmp = nullptr;
        for (uint32_t i = 0; i < pipe_length; ++i) {
          j_tmp = this->emit_append_slice_scalar(j_tmp, i * dst_width, j_init_data_p, j_pipe_ntype);
        }        
        auto j_tmp_v = this->emit_cast(j_tmp, j_pipe_vtype);
        jit_insn_store_relative(j_func_, j_vars_, pipe_addr, j_tmp_v);
      } else {               
        if (is_scalar) {
          // reset dst register
          jit_insn_store(j_func_, j_dst, j_init_data);
          auto j_init_data_v = this->emit_cast(j_init_data, j_vtype);
          jit_insn_store_relative(j_func_, j_vars_, dst_addr, j_init_data_v);

          // reset pipe registers          
          if (node->length() <= INLINE_THRESHOLD) {
            auto j_init_data_w = this->emit_cast(j_init_data, word_type_);
            jit_value_t j_tmp = nullptr;
            for (uint32_t i = 0; i < pipe_length; ++i) {
              j_tmp = this->emit_append_slice_vector(
                    j_tmp, memaddr_t{j_vars_, pipe_addr}, i * dst_width, pipe_width, j_init_data_w, dst_width);
            }
          } else {
            jit_label_t l_loop = jit_label_undefined;
            jit_label_t l_exit = jit_label_undefined;
            auto j_pipe_ptr = jit_insn_add_relative(j_func_, j_vars_, pipe_addr);
            auto j_index = jit_value_create(j_func_, jit_type_uint);
            auto j_lengthM1 = this->emit_constant(pipe_length - 1, jit_type_uint);
            jit_insn_store(j_func_, j_index, j_lengthM1);
            jit_insn_label(j_func_, &l_loop);
            this->emit_store_array_scalar(j_pipe_ptr, pipe_width, j_index, j_init_data, dst_width);                        
            jit_insn_branch_if_not(j_func_, j_index, &l_exit);
            auto j_sub = jit_insn_sub(j_func_, j_index, j_one_);
            jit_insn_store(j_func_, j_index, j_sub);
            jit_insn_branch(j_func_, &l_loop);
            jit_insn_label(j_func_, &l_exit);
          }
        } else {
          // reset dst register
          auto j_dst_ptr = jit_insn_add_relative(j_func_, j_vars_, dst_addr);
          auto j_init_ptr = this->emit_load_address(node->init_data().impl());
          this->emit_memcpy(j_dst_ptr, j_init_ptr, ceildiv(dst_width, 8));

          // reset pipe registers
          auto j_pipe_ptr = jit_insn_add_relative(j_func_, j_vars_, pipe_addr);
          if (node->length() <= INLINE_THRESHOLD) {
            for (uint32_t i = 0; i < pipe_length; ++i) {
              this->emit_copy_vector(j_pipe_ptr, i * dst_width, j_init_ptr, 0, dst_width);
            }
          } else {
            jit_label_t l_loop = jit_label_undefined;
            jit_label_t l_exit = jit_label_undefined;
            auto j_index = jit_value_create(j_func_, jit_type_uint);
            auto j_lengthM1 = this->emit_constant(pipe_length - 1, jit_type_uint);
            jit_insn_store(j_func_, j_index, j_lengthM1);
            jit_insn_label(j_func_, &l_loop);
            this->emit_store_array_vector(j_pipe_ptr, j_index, j_init_data, dst_width);
            jit_insn_branch_if_not(j_func_, j_index, &l_exit);
            auto j_sub = jit_insn_sub(j_func_, j_index, j_one_);
            jit_insn_store(j_func_, j_index, j_sub);
            jit_insn_branch(j_func_, &l_loop);
            jit_insn_label(j_func_, &l_exit);
          }
        }
      }
    } else {
      if (is_scalar) {         
        jit_insn_store(j_func_, j_dst, j_init_data);        
        auto j_init_data_v = this->emit_cast(j_init_data, j_vtype);
        jit_insn_store_relative(j_func_, j_vars_, dst_addr, j_init_data_v);
      } else {
        auto j_dst_ptr = jit_insn_add_relative(j_func_, j_vars_, dst_addr);
        auto j_init_ptr = this->emit_load_address(node->init_data().impl());
        this->emit_memcpy(j_dst_ptr, j_init_ptr, ceildiv(dst_width, 8));
      }
    }
  }

  void emit_snode_value(regimpl* node) {
    __source_info();

    uint32_t dst_width = node->size();
    auto j_vtype = to_value_type(dst_width);
    auto j_ntype = to_native_type(dst_width);
    auto is_scalar = (dst_width <= WORD_SIZE);
    auto dst_addr = addr_map_.at(node->id());

    jit_value_t j_dst = nullptr;
    jit_value_t j_next = nullptr;

    if (is_scalar) {
      j_dst = scalar_map_.at(node->id());
      j_next = scalar_map_.at(node->next().id());
    }

    if (node->is_pipe()) {
      uint32_t pipe_length = node->length() - 1;
      uint32_t pipe_width = pipe_length * dst_width;
      auto pipe_addr = dst_addr + __align_word_size(dst_width);
      auto is_pipe_scalar = (pipe_width <= WORD_SIZE);

      if (is_pipe_scalar) {
        assert(is_scalar);
        auto j_pipe_vtype = to_value_type(pipe_width);
        auto j_pipe_ntype = to_value_type(pipe_width);
        if (pipe_width == dst_width) {
          // dst <- pipe
          auto j_pipe = jit_insn_load_relative(j_func_, j_vars_, pipe_addr, j_vtype);
          jit_insn_store_relative(j_func_, j_vars_, dst_addr, j_pipe);
          auto j_pipe_n = this->emit_cast(j_pipe, j_ntype);
          jit_insn_store(j_func_, j_dst, j_pipe_n);

          // pipe <- next
          auto j_next_v = this->emit_cast(j_next, j_vtype);
          jit_insn_store_relative(j_func_, j_vars_, pipe_addr, j_next_v);
        } else {
          // dst <- pipe[0]
          auto j_pipe = jit_insn_load_relative(j_func_, j_vars_, pipe_addr, j_pipe_vtype);
          auto j_pipe_0 = this->emit_scalar_slice(j_pipe, 0, dst_width);
          auto j_pipe_0_v = this->emit_cast(j_pipe_0, j_vtype);
          auto j_pipe_0_n = this->emit_cast(j_pipe_0, j_ntype);
          jit_insn_store_relative(j_func_, j_vars_, dst_addr, j_pipe_0_v);
          jit_insn_store(j_func_, j_dst, j_pipe_0_n);

          // pipe >>= dst_width
          auto j_shift = this->emit_constant(dst_width, jit_type_uint);
          auto j_pipe_s = jit_insn_ushr(j_func_, j_pipe, j_shift);

          // pipe[n-1] <- next
          auto j_shfn1  = this->emit_constant((pipe_length - 1) * dst_width, jit_type_uint);
          auto j_next_p = this->emit_cast(j_next, j_pipe_ntype);
          auto j_next_s = jit_insn_shl(j_func_, j_next_p, j_shfn1);
          auto j_or     = jit_insn_or(j_func_, j_next_s, j_pipe_s);
          auto j_or_v   = this->emit_cast(j_or, j_pipe_vtype);
          jit_insn_store_relative(j_func_, j_vars_, pipe_addr, j_or_v);
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
            auto j_data = this->emit_load_array_scalar(j_pipe_ptr, pipe_width, j_pipe_index, dst_width);
            auto j_data_v = this->emit_cast(j_data, j_vtype);
            auto j_data_n = this->emit_cast(j_data, j_ntype);
            jit_insn_store_relative(j_func_, j_vars_, dst_addr, j_data_v);
            jit_insn_store(j_func_, j_dst, j_data_n);

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
          auto j_max = this->emit_constant(pipe_length - 1, jit_type_uint);
          auto j_sub = jit_insn_sub(j_func_, j_pipe_index, j_one_);
          auto j_min = jit_insn_min(j_func_, j_sub, j_max);
          jit_insn_store_relative(j_func_, j_vars_, pipe_index_addr, j_min);
        }
      }
    } else {
      if (is_scalar) {
        auto j_next_v = this->emit_cast(j_next, j_vtype);
        jit_insn_store_relative(j_func_, j_vars_, dst_addr, j_next_v);
        jit_insn_store(j_func_, j_dst, j_next);
      } else {
        auto j_dst_ptr = jit_insn_add_relative(j_func_, j_vars_, dst_addr);
        auto j_next_ptr = this->emit_load_address(node->next().impl());
        this->emit_memcpy(j_dst_ptr, j_next_ptr, ceildiv(dst_width, 8));
      }
    }
  }

  void emit_node(marportimpl* node) {
    __source_info();

    auto dst_width = node->size();
    auto j_ntype = to_native_type(dst_width);
    bool is_scalar = (dst_width <= WORD_SIZE);

    auto j_src_addr = scalar_map_.at(node->addr().id());
  #ifndef NDEBUG
    this->emit_range_check(j_src_addr, 0, node->mem()->num_items());
  #endif
    auto j_array_ptr = this->emit_load_address(node->mem());
    uint32_t array_width = node->mem()->size();

    if (is_scalar) {
      auto j_src = this->emit_load_array_scalar(j_array_ptr, array_width, j_src_addr, dst_width);
      scalar_map_[node->id()] = this->emit_cast(j_src, j_ntype);
    } else {
       auto j_dst_ptr = this->emit_store_address(node);
      this->emit_load_array_vector(j_dst_ptr, dst_width, j_array_ptr, j_src_addr);
    }
  }

  void emit_node(msrportimpl* node) {
    sblock_.cd = node->cd().impl();
    sblock_.reset = get_snode_reset(node);
    sblock_.nodes.push_back(node);
  }

  void emit_snode_value(msrportimpl* node) {
    __source_info();

    auto dst_width = node->size();    
    bool is_scalar = (dst_width <= WORD_SIZE);
    auto dst_addr = addr_map_.at(node->id());

    auto j_src_addr = scalar_map_.at(node->addr().id());
  #ifndef NDEBUG
    this->emit_range_check(j_src_addr, 0, node->mem()->num_items());
  #endif
    auto j_array_ptr = this->emit_load_address(node->mem());
    uint32_t array_width = node->mem()->size();

    if (is_scalar) {
      auto j_dst = scalar_map_.at(node->id());
      auto j_vtype = to_value_type(dst_width);
      auto j_ntype = to_native_type(dst_width);
      auto j_src = this->emit_load_array_scalar(j_array_ptr, array_width, j_src_addr, dst_width);
      auto j_src_v = this->emit_cast(j_src, j_vtype);
      auto j_src_n = this->emit_cast(j_src, j_ntype);
      jit_insn_store_relative(j_func_, j_vars_, dst_addr, j_src_v);
      jit_insn_store(j_func_, j_dst, j_src_n);
    } else {
       auto j_dst_ptr = this->emit_store_address(node);
      this->emit_load_array_vector(j_dst_ptr, dst_width, j_array_ptr, j_src_addr);
    }
  }

  void emit_node(mwportimpl* node) {
    sblock_.cd = node->cd().impl();
    sblock_.reset = get_snode_reset(node);
    sblock_.nodes.push_back(node);
  }

  void emit_snode_value(mwportimpl* node) {
    __source_info();

    auto data_width = node->mem()->data_width();
    bool is_scalar = (data_width <= WORD_SIZE);

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
  }

  void emit_node(timeimpl* node) {
    __source_info();

    auto dst_width = node->size();
    bool is_scalar = (dst_width <= WORD_SIZE);
    auto j_vtype = to_value_type(dst_width);

    auto addr = addr_map_.at(node->id());
    jit_value_t j_value;
    if (is_scalar) {
      j_value = scalar_map_.at(node->id());
    } else {
      j_value = jit_insn_load_relative(j_func_, j_vars_, addr, j_vtype);
    }
    auto j_incr = jit_insn_add(j_func_, j_value, j_one_);
    auto j_incr_v = this->emit_cast(j_incr, j_vtype);
    jit_insn_store_relative(j_func_, j_vars_, addr, j_incr_v);
  }

  void emit_node(printimpl* node) {
    __source_info();

    jit_label_t l_exit = jit_label_undefined;

    auto predicated = node->has_pred();
    if (predicated) {
      auto j_pred = scalar_map_.at(node->pred().id());
      jit_insn_branch_if_not(j_func_, j_pred, &l_exit);
    }

    auto addr = addr_map_.at(node->id());
    auto j_data_ptr = jit_insn_add_relative(j_func_, j_vars_, addr);

    // copy scalar arguments    
    uint32_t src_idx = 0;
    for (uint32_t i = (node->has_pred() ? 1 : 0), n = node->srcs().size(); i < n; ++i) {
      auto src = node->src(i).impl();
      auto it = scalar_map_.find(src->id());
      if (it != scalar_map_.end()) {
        auto srcs_ptr = jit_insn_load_relative(j_func_,
                                               j_vars_,
                                               addr + offsetof(print_data_t, srcs),
                                               jit_type_void_ptr);
        auto j_src = this->emit_address_of(it->second, word_type_);
        jit_insn_store_relative(j_func_, srcs_ptr, src_idx * sizeof(sdata_type), j_src);
      }
      ++src_idx;
    }

    // call native function    
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

    if (l_exit != jit_label_undefined) {
      jit_insn_label(j_func_, &l_exit);
    }
  }

  void emit_node(assertimpl* node) {
    __source_info();

    jit_label_t l_exit = jit_label_undefined;

    auto j_cond = scalar_map_.at(node->cond().id());
    if (node->has_pred()) {
      auto j_pred = scalar_map_.at(node->pred().id());
      auto j_pred_n = jit_insn_not(j_func_, j_pred);
      j_cond = jit_insn_or(j_func_, j_cond, j_pred_n);
    }
    jit_insn_branch_if(j_func_, j_cond, &l_exit);

    auto addr = addr_map_.at(node->id());
    auto j_data_ptr = jit_insn_add_relative(j_func_, j_vars_, addr);

    // copy scalar arguments    
    auto it = scalar_map_.find(node->time().id());
    if (it != scalar_map_.end()) {
      auto time_ptr = jit_insn_load_relative(j_func_,
                                             j_vars_,
                                             addr + offsetof(assert_data_t, time),
                                             jit_type_void_ptr);
      auto j_time = this->emit_address_of(it->second, word_type_);
      jit_insn_store_relative(j_func_, time_ptr, 0, j_time);
    }

    // call native function    
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

    if (l_exit != jit_label_undefined) {
      jit_insn_label(j_func_, &l_exit);
    }
  }

  void emit_node(udfcimpl* node) {
    __source_info();

    auto dst_width = node->size();
    auto j_ntype = to_native_type(dst_width);
    auto udf = node->udf();

    auto addr = addr_map_.at(node->id());
    auto data_addr = addr;
    jit_value_t j_dst_ptr, j_dst_tmp = nullptr;
    if (dst_width <= WORD_SIZE) {
      j_dst_tmp = jit_value_create(j_func_, word_type_);
      jit_insn_store(j_func_, j_dst_tmp, j_zero_);
      j_dst_ptr = this->emit_address_of(j_dst_tmp, word_type_);
    } else {
      j_dst_ptr = this->emit_store_address(node);
      data_addr += __align_word_size(dst_width);
    }
    auto j_data_ptr = jit_insn_add_relative(j_func_, j_vars_, data_addr);

    // copy scalar arguments
    uint32_t src_idx = 0;
    for (uint32_t i = 0, n = udf->inputs_size().size(); i < n; ++i) {
      auto src = node->src(i).impl();
      auto it = scalar_map_.find(src->id());
      if (it != scalar_map_.end()) {
        auto srcs_ptr = jit_insn_load_relative(j_func_,
                                               j_vars_,
                                               data_addr + offsetof(udf_data_t, srcs),
                                               jit_type_void_ptr);
        auto j_src = this->emit_address_of(it->second, word_type_);
        jit_insn_store_relative(j_func_, srcs_ptr, src_idx * sizeof(sdata_type), j_src);
      }
      ++src_idx;
    }

    // call native function    
    jit_type_t params[] = {jit_type_void_ptr, jit_type_void_ptr};
    jit_type_t j_sig = jit_type_create_signature(jit_abi_cdecl,
                                                 jit_type_void,
                                                 params,
                                                 __countof(params),
                                                 1);
    jit_value_t args[] = {j_dst_ptr, j_data_ptr};
    jit_insn_call_native(j_func_,
                         "udf_data_t::eval",
                         (void*)udf_data_t::eval,
                         j_sig,
                         args,
                         __countof(args),
                         JIT_CALL_NOTHROW);

    if (dst_width <= WORD_SIZE) {
      scalar_map_[node->id()] = this->emit_cast(j_dst_tmp, j_ntype);
    }
  }

  void emit_node(udfsimpl* node) {
    sblock_.cd = node->cd().impl();
    sblock_.reset = get_snode_reset(node);
    sblock_.nodes.push_back(node);
  }

  void emit_snode_value(udfsimpl* node) {
    __source_info();

    auto dst_width = node->size();    
    auto udf = node->udf();

    auto addr = addr_map_.at(node->id());
    auto data_addr = addr + __align_word_size(dst_width);
    auto j_dst_ptr = this->emit_store_address(node);
    auto j_data_ptr = jit_insn_add_relative(j_func_, j_vars_, data_addr);

    // copy scalar arguments
    uint32_t src_idx = 0;
    for (uint32_t i = 0, n = udf->inputs_size().size(); i < n; ++i) {
      auto src = node->src(i).impl();
      auto it = scalar_map_.find(src->id());
      if (it != scalar_map_.end()) {
        auto srcs_ptr = jit_insn_load_relative(j_func_,
                                               j_vars_,
                                               data_addr + offsetof(udf_data_t, srcs),
                                               jit_type_void_ptr);
        auto j_src = this->emit_address_of(it->second, word_type_);
        jit_insn_store_relative(j_func_, srcs_ptr, src_idx * sizeof(sdata_type), j_src);
      }
      ++src_idx;
    }

    // call native function
    jit_type_t params[] = {jit_type_void_ptr, jit_type_void_ptr};
    jit_type_t j_sig = jit_type_create_signature(jit_abi_cdecl,
                                                 jit_type_void,
                                                 params,
                                                 __countof(params),
                                                 1);
    jit_value_t args[] = {j_dst_ptr, j_data_ptr};
    jit_insn_call_native(j_func_,
                         "udf_data_t::eval",
                         (void*)udf_data_t::eval,
                         j_sig,
                         args,
                         __countof(args),
                         JIT_CALL_NOTHROW);

    if (dst_width <= WORD_SIZE) {
      auto j_vtype = to_value_type(dst_width);
      auto j_ntype = to_native_type(dst_width);
      auto j_dst = jit_insn_load_relative(j_func_, j_vars_, addr, j_vtype);
      scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
    }
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
        addr_map_[node->id()] = var_addr;
        var_addr += __align_word_size(dst_width);
        break;
      case type_time: {
        addr_map_[node->id()] = var_addr;
        var_addr += __align_word_size(dst_width);
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
      case type_udfc:
      case type_udfs: {
        addr_map_[node->id()] = var_addr;
        if (type_udfs == type
         || dst_width > WORD_SIZE) {          
          var_addr += __align_word_size(dst_width);
        }
        auto u = reinterpret_cast<udfimpl*>(node);
        var_addr += __align_word_size(udf_data_t::size(u) * 8);
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
      auto j_vtype = to_value_type(dst_width);
      auto j_ntype = to_native_type(dst_width);
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
            // reset pipe index
            auto pipe_index_addr = pipe_addr + __align_word_size(pipe_width);
            *reinterpret_cast<uint32_t*>(sim_ctx_->state.vars + pipe_index_addr) = 0;
          }
        }
        if (dst_width <= WORD_SIZE) {
          // preload scalar value
          __source_info();
          auto addr = addr_map_.at(node->id());
          auto j_dst = jit_insn_load_relative(j_func_, j_vars_, addr, j_vtype);
          scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);;
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
      case type_msrport: {
        auto addr = addr_map_.at(node->id());
        bv_init(reinterpret_cast<block_type*>(sim_ctx_->state.vars + addr), dst_width);
        if (dst_width <= WORD_SIZE) {
          // preload scalar value
          __source_info();
          auto j_dst = jit_insn_load_relative(j_func_, j_vars_, addr, j_vtype);
          scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);;
        }
      } break;
      case type_time: {
        auto addr = addr_map_.at(node->id());        
        bv_reset(reinterpret_cast<block_type*>(sim_ctx_->state.vars + addr), dst_width);
        if (dst_width <= WORD_SIZE) {
          // preload scalar value
          __source_info();
          auto j_dst = jit_insn_load_relative(j_func_, j_vars_, addr, j_vtype);
          scalar_map_[node->id()] = j_dst;
        }
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
      case type_udfc:
      case type_udfs: {
        auto addr = addr_map_.at(node->id());
        if (type_udfs == type
         || dst_width > WORD_SIZE) {
          bv_init(reinterpret_cast<block_type*>(sim_ctx_->state.vars + addr), dst_width);          
          if (type_udfs == type
           && dst_width <= WORD_SIZE) {
            // preload scalar value
            __source_info();
            auto j_dst = jit_insn_load_relative(j_func_, j_vars_, addr, j_vtype);
            scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);;
          }
          addr += __align_word_size(dst_width);
        }
        auto u = reinterpret_cast<udfimpl*>(node);
        reinterpret_cast<udf_data_t*>(sim_ctx_->state.vars + addr)->init(u, this);
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
    CH_DBGCHECK((addr - offset) == size, "invalid size");
  }

  void init_sdata(sdata_type* data, lnodeimpl* node) const {
    block_type* value = nullptr;
    auto it = addr_map_.find(node->id());
    if (it != addr_map_.end()) {
      auto addr = it->second;
      switch (node->type()) {
      case type_input:
        value = sim_ctx_->state.ports[addr];
        break;
      default:
        value = reinterpret_cast<block_type*>(sim_ctx_->state.vars + addr);
        break;
      }
    }
    data->emplace(value, node->size());
  }

  /////////////////////////////////////////////////////////////////////////////

  jit_value_t emit_eq_vector(jit_value_t j_lhs, uint32_t lhs_size,
                             jit_value_t j_rhs, uint32_t rhs_size,
                             bool is_signed) {
    __source_info();
    assert(lhs_size > WORD_SIZE || rhs_size > WORD_SIZE);

    jit_value_t j_ret = nullptr;
    auto need_resize = (lhs_size != rhs_size);
    if (need_resize
     || lhs_size > INLINE_THRESHOLD * WORD_SIZE) {
      j_ret = __alu_call_relational(bv_eq_vector, j_lhs, lhs_size, j_rhs, rhs_size);
    } else {
      uint32_t num_words = ceildiv(lhs_size, WORD_SIZE);
      for (uint32_t i = 0; i < num_words; ++i) {
        auto j_value1 = jit_insn_load_relative(j_func_, j_lhs, i * sizeof(block_type), word_type_);
        auto j_value2 = jit_insn_load_relative(j_func_, j_rhs, i * sizeof(block_type), word_type_);
        auto j_eq = jit_insn_eq(j_func_, j_value1, j_value2);
        j_ret = i ? jit_insn_and(j_func_, j_ret, j_eq) : j_eq;
      }
    }
    return j_ret;
  }

  jit_value_t emit_xorr_scalar(jit_value_t j_value, uint32_t width) {
    __source_info();

    auto native_width = to_native_size(width);
    jit_value_t j_ret = j_value;
    for (uint32_t i = (native_width / 2); i != 0; i /= 2) {
      auto j_shift = this->emit_constant(i, jit_type_uint);
      auto j_tmp = jit_insn_ushr(j_func_, j_ret, j_shift);
      j_ret = jit_insn_xor(j_func_, j_ret, j_tmp);
    }
    return jit_insn_and(j_func_, j_ret, j_one_);
  }

  jit_value_t emit_scalar_slice(jit_value_t j_value,
                                uint32_t offset,
                                uint32_t length) {
    __source_info();
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
      auto j_vtype = jit_value_get_type(j_src);
      auto j_mask = this->emit_constant((1ull << length) - 1, j_vtype);
      j_src = jit_insn_and(j_func_, j_src, j_mask);
    }
    return j_src;
  }

  jit_value_t emit_load_slice_scalar(memaddr_t src_ptr,
                                     uint32_t offset,
                                     uint32_t length) {
    auto src_lsb8 = offset % 8;
    auto src_end8 = src_lsb8 + length;
    if (src_end8 <= WORD_SIZE) {
      auto block_width = to_value_size(src_end8);
      auto j_vtype = to_value_type(block_width);
      auto src_idx = ceildiv(offset + length, 8) - block_width / 8;
      auto src_lsb = offset - src_idx * 8;
      auto j_src_value = jit_insn_load_relative(j_func_, src_ptr.base, src_ptr.offset + src_idx, j_vtype);
      return this->emit_scalar_slice(j_src_value, src_lsb, length);
    } else {
      auto src_idx = offset / WORD_SIZE;
      auto src_lsb = offset % WORD_SIZE;
      auto j_vtype = to_value_type(length);
      auto j_src_lsb = this->emit_constant(src_lsb, jit_type_uint);
      auto j_src_value0 = jit_insn_load_relative(j_func_, src_ptr.base, src_ptr.offset + src_idx * sizeof(block_type), j_vtype);
      auto j_src_value0_s = jit_insn_ushr(j_func_, j_src_value0, j_src_lsb);
      auto j_src_value1 = jit_insn_load_relative(j_func_, src_ptr.base, src_ptr.offset + (src_idx + 1) * sizeof(block_type), j_vtype);
      auto j_rem = this->emit_constant(get_value_size(j_src_value1) - src_lsb, jit_type_uint);
      auto j_src_value1_s = jit_insn_shl(j_func_, j_src_value1, j_rem);
      auto j_src_value = jit_insn_or(j_func_, j_src_value1_s, j_src_value0_s);
      return this->emit_scalar_slice(j_src_value, 0, length);
    }
  }

  jit_value_t emit_load_slice_scalar(lnodeimpl* node,
                                     uint32_t offset,
                                     uint32_t length) {
    __source_info();
    assert(length <= WORD_SIZE);

    uint32_t src_width = node->size();
    if (src_width <= WORD_SIZE) {
      auto j_src_value = scalar_map_.at(node->id());
      if (src_width != length) {
        return this->emit_scalar_slice(j_src_value, offset, length);
      } else {
        return j_src_value;
      }
    } else {
      auto src_ptr = this->get_load_address(node);
      return this->emit_load_slice_scalar(src_ptr, offset, length);
    }
  }

  jit_value_t emit_load_array_scalar(jit_value_t j_array_ptr,
                                     uint32_t array_width,
                                     jit_value_t j_index,
                                     uint32_t length) {
    __source_info();
    assert(length <= WORD_SIZE);

    jit_value_t j_src;
    auto j_vtype = to_value_type(length);
    if (0 == (length % 8)) {      
      if (is_value_size(length)) {
        j_src = jit_insn_load_elem(j_func_, j_array_ptr, j_index, j_vtype);
      } else {
        auto j_data_size = this->emit_constant(length / 8, jit_type_uint);
        auto j_offset = jit_insn_mul(j_func_, j_index, j_data_size);
        auto j_addr = jit_insn_load_elem_address(j_func_, j_array_ptr, j_offset, jit_type_ubyte);
        j_src = jit_insn_load_relative(j_func_, j_addr, 0, j_vtype);
      }
    } else {
      auto j_data_width = this->emit_constant(length, jit_type_uint);
      auto j_src_offset = jit_insn_mul(j_func_, j_index, j_data_width);
      if (array_width <= WORD_SIZE) {
        auto j_array_type = to_value_type(array_width);
        auto j_value = jit_insn_load_relative(j_func_, j_array_ptr, 0, j_array_type);
        j_src = jit_insn_ushr(j_func_, j_value, j_src_offset);
      } else {
        auto j_src_idx = jit_insn_ushr(j_func_, j_src_offset, j_block_logsize_);
        auto j_src_lsb = jit_insn_and(j_func_, j_src_offset, j_block_mask_);

        auto j_src_ptr = jit_insn_load_elem_address(j_func_, j_array_ptr, j_src_idx, word_type_);
        auto j_src_value0 = jit_insn_load_relative(j_func_, j_src_ptr, 0, word_type_);
        j_src = jit_insn_ushr(j_func_, j_src_value0, j_src_lsb);

        jit_label_t l_skip = jit_label_undefined;
        auto j_src_rem = this->emit_constant(WORD_SIZE - length, jit_type_uint);
        auto j_src_inclusive = jit_insn_le(j_func_, j_src_lsb, j_src_rem);
        jit_insn_branch_if(j_func_, j_src_inclusive, &l_skip);

        auto j_src_value1 = jit_insn_load_relative(j_func_, j_src_ptr, sizeof(block_type), word_type_);
        auto j_block_size = this->emit_constant(get_value_size(j_src_value1), jit_type_uint);
        auto j_rem = jit_insn_sub(j_func_, j_block_size, j_src_lsb);
        auto j_src1_s = jit_insn_shl(j_func_, j_src_value1, j_rem);
        auto j_or = jit_insn_or(j_func_, j_src, j_src1_s);
        jit_insn_store(j_func_, j_src, j_or);

        jit_insn_label(j_func_, &l_skip);
      }
    }
    return this->emit_scalar_slice(j_src, 0, length);
  }

  void emit_store_array_scalar(jit_value_t j_array_ptr,
                               uint32_t array_width,
                               jit_value_t j_index,
                               jit_value_t j_data,
                               uint32_t length) {
    __source_info();
    assert(length <= WORD_SIZE);

    auto j_vtype = to_value_type(length);
    auto j_ntype = to_native_type(length);

    if (0 == (length % 8)) {      
      if (is_value_size(length)) {
        auto j_data_v = this->emit_cast(j_data, j_vtype);
        jit_insn_store_elem(j_func_, j_array_ptr, j_index, j_data_v);
      } else {
        auto j_data_size = this->emit_constant(length / 8, jit_type_uint);
        auto j_offset = jit_insn_mul(j_func_, j_index, j_data_size);
        auto j_addr = jit_insn_load_elem_address(j_func_, j_array_ptr, j_offset, jit_type_ubyte);
        auto j_dst = jit_insn_load_relative(j_func_, j_addr, 0, j_vtype);
        auto j_mask = this->emit_constant((1ull << length) - 1, j_ntype);
        auto j_dst_new = this->emit_blend(j_mask, j_dst, j_data);
        auto j_dst_new_v = this->emit_cast(j_dst_new, j_vtype);
        jit_insn_store_relative(j_func_, j_addr, 0, j_dst_new_v);
      }
    } else {      
      auto j_data_width = this->emit_constant(length, jit_type_uint);
      auto j_dst_offset = jit_insn_mul(j_func_, j_index, j_data_width);

      if (array_width <= WORD_SIZE) {
        auto j_array_type = to_value_type(array_width);
        auto j_array_ntype = to_native_type(array_width);
        auto j_mask = this->emit_constant(WORD_MAX >> (WORD_SIZE - length), j_array_ntype);
        auto j_data_n = this->emit_cast(j_data, j_array_ntype);
        auto j_dst = jit_insn_load_relative(j_func_, j_array_ptr, 0, j_array_type);
        auto j_mask_s = jit_insn_shl(j_func_, j_mask, j_dst_offset);
        auto j_data_s = jit_insn_shl(j_func_, j_data_n, j_dst_offset);
        auto j_dst_new = this->emit_blend(j_mask_s, j_dst, j_data_s);
        auto j_dst_new_v = this->emit_cast(j_dst_new, j_array_type);
        jit_insn_store_relative(j_func_, j_array_ptr, 0, j_dst_new_v);
      } else {
        auto j_mask = this->emit_constant(WORD_MAX >> (WORD_SIZE - length), j_ntype);
        auto j_data_n = this->emit_cast(j_data, j_ntype);
        auto j_dst_idx = jit_insn_ushr(j_func_, j_dst_offset, j_block_logsize_);
        auto j_dst_lsb = jit_insn_and(j_func_, j_dst_offset, j_block_mask_);

        auto j_dst_ptr = jit_insn_load_elem_address(j_func_, j_array_ptr, j_dst_idx, word_type_);
        auto j_dst_value0 = jit_insn_load_relative(j_func_, j_dst_ptr, 0, word_type_);
        auto j_mask0_s = jit_insn_shl(j_func_, j_mask, j_dst_lsb);
        auto j_data0_s = jit_insn_shl(j_func_, j_data_n, j_dst_lsb);
        auto j_dst0 = this->emit_blend(j_mask0_s, j_dst_value0, j_data0_s);
        auto j_dst0_w = this->emit_cast(j_dst0, word_type_);
        jit_insn_store_relative(j_func_, j_dst_ptr, 0, j_dst0_w);

        jit_label_t l_skip = jit_label_undefined;
        auto j_dst_rem = this->emit_constant(WORD_SIZE - length, jit_type_uint);
        auto j_single_block = jit_insn_le(j_func_, j_dst_lsb, j_dst_rem);

        jit_insn_branch_if(j_func_, j_single_block, &l_skip);
        auto j_dst_value1 = jit_insn_load_relative(j_func_, j_dst_ptr, sizeof(block_type), word_type_);
        auto j_mask1 = jit_insn_not(j_func_, j_mask0_s);
        auto j_mask1_s = jit_insn_ushr(j_func_, j_mask1, j_dst_rem);
        auto j_data1_s = jit_insn_ushr(j_func_, j_data_n, j_dst_rem);
        auto j_dst1 = this->emit_blend(j_mask1_s, j_dst_value1, j_data1_s);
        auto j_dst1_w = this->emit_cast(j_dst1, word_type_);
        jit_insn_store_relative(j_func_, j_dst_ptr, sizeof(block_type), j_dst1_w);

        jit_insn_label(j_func_, &l_skip);        
      }
    }
  }

  void emit_load_array_vector(jit_value_t j_dst_ptr,
                              uint32_t dst_width,
                              jit_value_t j_array_ptr,
                              jit_value_t j_index) {
    __source_info();

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
    __source_info();

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
    __source_info();
    assert(length <= WORD_SIZE);

    auto j_vtype = to_value_type(length);
    auto j_ntype = to_native_type(length);

    auto w_dst_idx = dst_offset / WORD_SIZE;
    auto w_dst_lsb = dst_offset % WORD_SIZE;

    block_type mask0 = (WORD_MAX >> (WORD_SIZE - length)) << w_dst_lsb;
    block_type mask1 = block_type(~mask0) >> (WORD_SIZE - length);

    auto j_src_offset = this->emit_constant(src_offset, jit_type_uint);
    auto j_dst_lsb = this->emit_constant(w_dst_lsb, jit_type_uint);
    auto j_src_s = jit_insn_ushr(j_func_, j_src, j_src_offset);
    auto j_src_n = this->emit_cast(j_src_s, j_ntype);
    auto j_src_0 = jit_insn_shl(j_func_, j_src_n, j_dst_lsb);
    auto j_dst_0 = jit_insn_load_relative(j_func_, j_dst_ptr, w_dst_idx * sizeof(block_type), j_vtype);
    auto j_mask0 = this->emit_constant(mask0, j_ntype);
    auto j_blend0 = this->emit_blend(j_mask0, j_dst_0, j_src_0);
    auto j_blend0_v = this->emit_cast(j_blend0, j_vtype);
    jit_insn_store_relative(j_func_, j_dst_ptr, w_dst_idx * sizeof(block_type), j_blend0_v);
    if (w_dst_lsb > (WORD_SIZE - length)) {
      auto j_dst_1 = jit_insn_load_relative(j_func_, j_dst_ptr, (w_dst_idx + 1) * sizeof(block_type), j_vtype);
      auto j_rem = this->emit_constant(WORD_SIZE - w_dst_lsb, jit_type_uint);
      auto j_src_1 = jit_insn_ushr(j_func_, j_src_n, j_rem);
      auto j_mask1 = this->emit_constant(mask1, j_ntype);
      auto j_blend1 = this->emit_blend(j_mask1, j_dst_1, j_src_1);
      auto j_blend1_v = this->emit_cast(j_blend1, j_vtype);
      jit_insn_store_relative(j_func_, j_dst_ptr, (w_dst_idx + 1) * sizeof(block_type), j_blend1_v);
    }
  }

  void emit_copy_vector(jit_value_t j_dst_ptr,
                        uint32_t dst_offset,
                        jit_value_t j_src_ptr,
                        uint32_t src_offset,
                        uint32_t length) {
    __source_info();

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
        auto j_dst_b = this->emit_cast(j_dst, jit_type_ubyte);
        jit_insn_store_relative(j_func_, j_dst_ptr8, offset, j_dst_b);
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
    __source_info();

    auto j_length = this->emit_constant(length, jit_type_uint);

    // call native function
    jit_type_t params[] = {jit_type_void_ptr, jit_type_uint, jit_type_void_ptr, jit_type_uint, jit_type_uint};
    auto j_sig = jit_type_create_signature(jit_abi_cdecl,
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

  jit_value_t emit_append_slice_vector(jit_value_t j_cur,
                                       memaddr_t dst_addr,
                                       uint32_t dst_offset,
                                       uint32_t dst_width,
                                       jit_value_t j_src,
                                       uint32_t length) {
    __source_info();

    assert(dst_width > WORD_SIZE);
    auto dst_idx = dst_offset / WORD_SIZE;
    auto dst_lsb = dst_offset % WORD_SIZE;

    auto j_ntype = to_native_type(WORD_SIZE);
    j_cur = this->emit_append_slice_scalar(j_cur, dst_lsb, j_src, j_ntype);

    if ((dst_lsb + length) > WORD_SIZE) {
      // flush current block
      auto j_cur_w = this->emit_cast(j_cur, word_type_);
      jit_insn_store_relative(j_func_, dst_addr.base, dst_addr.offset + dst_idx * sizeof(block_type), j_cur_w);
      ++dst_idx;
      // copy remaining bits into next block
      auto j_rem = this->emit_constant(WORD_SIZE - dst_lsb, jit_type_uint);
      auto j_src_n = this->emit_cast(j_src, j_ntype);
      j_cur = jit_insn_ushr(j_func_, j_src_n, j_rem);
    }

    if ((dst_lsb + length) == WORD_SIZE
     || (dst_offset + length) == dst_width) {
      // flush current block
      auto j_cur_w = this->emit_cast(j_cur, word_type_);
      jit_insn_store_relative(j_func_, dst_addr.base, dst_addr.offset + dst_idx * sizeof(block_type), j_cur_w);
      j_cur = nullptr;
    }

    return j_cur;
  }

  jit_value_t emit_append_slice_vector(jit_value_t j_cur,
                                       memaddr_t dst_addr,
                                       uint32_t dst_offset,
                                       uint32_t dst_width,
                                       memaddr_t src_addr,
                                       uint32_t src_offset,
                                       uint32_t length) {
    __source_info();

    if (length <= INLINE_THRESHOLD * WORD_SIZE) {
      while (length) {
        auto l = std::min(length, WORD_SIZE);
        auto j_src = this->emit_load_slice_scalar(src_addr, src_offset, l);
        j_cur = this->emit_append_slice_vector(j_cur, dst_addr, dst_offset, dst_width, j_src, l);
        dst_offset += l;
        src_offset += l;
        length -= l;
      }
    } else {
      if (j_cur) {
        auto dst_lsb = dst_offset % WORD_SIZE;
        assert(dst_lsb);
        auto l = WORD_SIZE - dst_lsb;
        auto j_src = this->emit_load_slice_scalar(src_addr, src_offset, l);
        j_cur = this->emit_append_slice_vector(j_cur, dst_addr, dst_offset, dst_width, j_src, l);
        dst_offset += l;
        src_offset += l;
        length -= l;
      }
      assert(0 == (dst_offset % WORD_SIZE));
      assert(length > WORD_SIZE);
      auto length_w = (length / WORD_SIZE) * WORD_SIZE;
      if (0 == (src_offset % 8)) {
        auto j_dst_ptr8 = jit_insn_add_relative(j_func_, j_vars_, dst_addr.offset + dst_offset / 8);
        auto j_src_ptr8 = jit_insn_add_relative(j_func_, src_addr.base, src_addr.offset + src_offset / 8);
        this->emit_memcpy(j_dst_ptr8, j_src_ptr8, length_w / 8);
      } else {
        auto j_dst_offset = this->emit_constant(dst_addr.offset * 8 + dst_offset, jit_type_uint);
        auto j_src_offset = this->emit_constant(src_addr.offset * 8 + src_offset, jit_type_uint);
        this->emit_copy_vector(dst_addr.base, j_dst_offset, src_addr.base, j_src_offset, length_w);
      }
      dst_offset += length_w;
      src_offset += length_w;
      length -= length_w;
      if (length) {
        auto j_src = this->emit_load_slice_scalar(src_addr, src_offset, length);
        j_cur = this->emit_append_slice_vector(j_cur, dst_addr, dst_offset, dst_width, j_src, length);
      }
    }

    return j_cur;
  }

  jit_value_t emit_append_slice_scalar(jit_value_t j_cur,
                                       uint32_t dst_offset,
                                       jit_value_t j_src,
                                       jit_type_t j_ntype) {
    __source_info();

    if (nullptr == j_cur)
      return this->emit_cast(j_src, j_ntype);

    assert(is_native_type(j_ntype));
    assert(jit_type_get_kind(j_ntype) == jit_type_get_kind(jit_value_get_type(j_cur)));

    if (jit_value_is_constant(j_src)) {
      auto src = this->get_constant_value(j_src);
      if (0 == src)
        return j_cur;
      assert(dst_offset < WORD_SIZE);
      src = block_type(src) << dst_offset;
      if (jit_value_is_constant(j_cur)) {
        auto val = this->get_constant_value(j_cur);
        return this->emit_constant(src | val, j_ntype);
      } else {
        auto j_tmp = this->emit_constant(src, j_ntype);
        return jit_insn_or(j_func_, j_cur, j_tmp);
      }
    }

    auto j_dst_lsb = this->emit_constant(dst_offset, jit_type_uint);
    auto j_src_n = this->emit_cast(j_src, j_ntype);
    auto j_src_s = jit_insn_shl(j_func_, j_src_n, j_dst_lsb);

    if (jit_value_is_constant(j_cur)
    &&  0 == this->get_constant_value(j_cur)) {
      return j_src_s;
    }

    return jit_insn_or(j_func_, j_src_s, j_cur);
  }

  void emit_clear_extra_bits(lnodeimpl* node) {
    __source_info();

    uint32_t dst_width = node->size();
    assert(dst_width <= WORD_SIZE);
    auto native_size = to_native_size(dst_width);
    uint32_t rem = dst_width % native_size;
    if (0 == rem)
      return;
    auto j_ntype = to_native_type(dst_width);
    auto j_dst = scalar_map_.at(node->id());
    auto mask = ~(std::numeric_limits<uint64_t>::max() << rem);
    auto j_mask = this->emit_constant(mask, j_ntype);
    auto j_and = jit_insn_and(j_func_, j_dst, j_mask);
    scalar_map_[node->id()] = j_and;
  }

  /////////////////////////////////////////////////////////////////////////////

  memaddr_t get_store_address(lnodeimpl* node) {
    return memaddr_t{j_vars_, addr_map_.at(node->id())};
  }

  memaddr_t get_load_address(lnodeimpl* node) {
    switch (node->type()) {
    case type_input:
      return memaddr_t{input_map_.at(node->id()), 0};
    default:
      return memaddr_t{j_vars_, addr_map_.at(node->id())};
    }
  }

  jit_value_t emit_store_address(lnodeimpl* node, uint32_t offset = 0) {
    auto maddr = this->get_store_address(node);
    offset += maddr.offset;
    return offset ? jit_insn_add_relative(j_func_, maddr.base, offset) : maddr.base;
  }

  jit_value_t emit_load_address(lnodeimpl* node, uint32_t offset = 0) {
    auto maddr = this->get_load_address(node);
    offset += maddr.offset;
    return offset ? jit_insn_add_relative(j_func_, maddr.base, offset) : maddr.base;
  }

  jit_value_t emit_load_scalar_relative(lnodeimpl* node, uint32_t offset, jit_type_t j_type) {
    auto maddr = this->get_load_address(node);
    return jit_insn_load_relative(j_func_, maddr.base, maddr.offset + offset, j_type);
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
      auto j_mask = this->emit_constant(1ull << (width - 1), j_type);
      auto j_tmp1 = jit_insn_xor(j_func_, j_value, j_mask);
      auto j_tmp2 = jit_insn_sub(j_func_, j_tmp1, j_mask);
      return this->emit_cast(j_tmp2, j_stype);
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
    if (from_kind == to_kind
     && !jit_value_is_constant(j_value)) {
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

  void dump_ast(FILE *stream, const char *name) {
    fprintf(stream, "function %s(", name);

    // dump signature
    auto signature = jit_function_get_signature(j_func_);
    uint32_t num_params = jit_type_num_params(signature);
    for (uint32_t param = 0; param < num_params; ++param) {
      if (param != 0) {
        fputs(", ", stream);
      }
      auto value = jit_value_get_param(j_func_, param);
      jit_dump_value(stream, j_func_, value, 0);
      fputs(" : ", stream);
      jit_dump_type(stream, jit_type_get_param(signature, param));
    }

    fprintf(stream, ") : ");
    jit_dump_type(stream, jit_type_get_return(signature));
    putc('\n', stream);

    // dump blocks
    jit_block_t block = nullptr;
    while ((block = jit_block_next(j_func_, block)) != nullptr) {
      auto meta = jit_block_get_meta(block, 0);
      if (meta) {
        if (((char*)meta)[0] != '\0') {
          auto sinfo = (const char*)(meta);
          fprintf(stream, "# </sref %s\n", sinfo);
          if (strchr(sinfo, '@')) {
            delete sinfo; // release allocation
          }
        } else {
          fprintf(stream, "# sref/>\n");
        }
      }
      // dump label if present
      auto label = jit_block_get_label(block);
      if (label != jit_label_undefined) {
        for (;;) {
          fprintf(stream, ".L%ld:", (long) label);
          label = jit_block_get_next_label(block, label);
          if (label == jit_label_undefined) {
            fprintf(stream, "\n");
            break;
          }
          fprintf(stream, " ");
        }
      }

      // dump the instructions
      jit_insn_iter_t iter;
      jit_insn_iter_init(&iter, block);
      jit_insn_t insn = nullptr;
      while ((insn = jit_insn_iter_next(&iter)) != nullptr) {
        putc('\t', stream);
        jit_dump_insn(stream, j_func_, insn);
        putc('\n', stream);
      }
    }
    fprintf(stream, "end\n\n");
    fflush(stream);
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
  var_map_t       input_map_;
  var_map_t       scalar_map_;  
  jit_label_t     l_bypass_;
  bypass_set_t    bypass_nodes_;
  bool            bypass_enable_;
  sblock_t        sblock_;
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

}

#endif
