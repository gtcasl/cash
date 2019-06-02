#ifndef NLIBJIT

#include "simjit.h"
#include "bindimpl.h"
#include "litimpl.h"
#include "cdimpl.h"
#include "regimpl.h"
#include "memimpl.h"
#include "ioimpl.h"
#include "selectimpl.h"
#include "proxyimpl.h"
#include "memimpl.h"
#include "opimpl.h"
#include "assertimpl.h"
#include "printimpl.h"
#include "timeimpl.h"
#include "udfimpl.h"
#if defined(LLVMJIT)
  #include "llvmjit.h"
#elif defined(LIBJIT)
  #include "libjit.h"
#endif
#include "compile.h"

namespace ch::internal::simjit {

using alloc_map_t  = std::unordered_map<uint32_t, uint32_t>;
using var_map_t    = std::unordered_map<uint32_t, jit_value_t>;
using label_map_t  = std::unordered_map<uint32_t, jit_label_t>;
using bypass_set_t = std::unordered_set<uint32_t>;

static constexpr uint32_t WORD_SIZE = bitwidth_v<block_type>;
static constexpr uint32_t WORD_LOGSIZE = log2floor(WORD_SIZE);
static constexpr uint32_t WORD_MASK = WORD_SIZE - 1;
static constexpr block_type WORD_MAX = std::numeric_limits<block_type>::max();
static constexpr uint32_t INLINE_THRESHOLD = 8;

///////////////////////////////////////////////////////////////////////////////

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

#define __op_call_relational(fname, ...) \
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
    return this->emit_op_call_relational(pfn, #fname, __VA_ARGS__); \
  }()

#define __op_call_logical(fname, ...) \
  this->emit_op_call_relational(reinterpret_cast<void*>(fname<block_type>), #fname, __VA_ARGS__)

#define __op_call_bitwise(fname, ...) \
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
  this->emit_op_call_bitwise(pfn, #fname, __VA_ARGS__)

#define __op_call_reduce(fname, ...) \
  [&]()->jit_value_t { \
    auto pfn = reinterpret_cast<void*>(fname<block_type>); \
    return this->emit_op_call_relational(pfn, #fname, __VA_ARGS__); \
  }()

#define __op_call_shl(fname, ...) \
  auto pfn = reinterpret_cast<void*>(fname<block_type>); \
  this->emit_op_call_shift(pfn, #fname, __VA_ARGS__)

#define __op_call_shr(fname, ...) \
  auto pfn = is_signed ? fname<true, block_type> : fname<false, block_type>; \
  auto pfn_name = is_signed ? stringf("%s<true, block_type>",#fname) : stringf("%s<false, block_type>",#fname); \
  this->emit_op_call_shift(reinterpret_cast<void*>(pfn), pfn_name.c_str(), __VA_ARGS__)

#define __op_call_arithmetic(fname, ...) \
  __op_call_bitwise(fname, __VA_ARGS__)

#define __op_call_arithmetic2(fname, ...) \
  auto pfn = is_signed ? fname<true, block_type> : fname<false, block_type>; \
  this->emit_op_call_bitwise(reinterpret_cast<void*>(pfn), #fname, __VA_ARGS__)

///////////////////////////////////////////////////////////////////////////////

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
  auto bytes = ceildiv(size, 8);
  switch (bytes) {
  case 0:
    return jit_type_void;
  case 1:
    return jit_type_int8;
  case 2:
    return jit_type_int16;
  case 3:
  case 4:
    return jit_type_int32;
  default:
    return jit_type_int64;
  }
}


static uint32_t to_native_size(uint32_t size) {
  auto bytes = ceildiv(size, 8);
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
  auto native_size = to_native_size(size);
  return to_value_type(native_size);
}

static uint32_t to_native_or_word_size(uint32_t size) {
  auto native_size = to_native_size(size);
  if (native_size <= WORD_SIZE)
    return native_size;
  return WORD_SIZE;
}

static jit_type_t to_native_or_word_type(uint32_t size) {
  auto native_size = to_native_size(size);
  if (native_size <= WORD_SIZE)
    return to_value_type(native_size);
  return to_value_type(WORD_SIZE);
}

static uint32_t get_type_size(jit_type_t j_type) {
  auto nbytes = jit_type_get_size(j_type);
  return nbytes * 8;
}

static uint32_t get_value_size(jit_value_t j_value) {
  auto j_type = jit_value_get_type(j_value);
  return get_type_size(j_type);
}

[[maybe_unused]] static bool is_native_type(jit_type_t j_type) {
  auto kind = jit_type_get_kind(j_type);
  switch (kind) {
  case JIT_TYPE_INT32:
  case JIT_TYPE_INT64:
    return true;
  default:
    return false;
  }
}

#ifndef NDEBUG
extern "C" void ext_watch(uint64_t value, char* name) {
  auto oldflags = std::cout.flags();
  std::cout.setf(std::ios_base::hex, std::ios_base::basefield);
  std::cout << "WATCH:" << name << " = " << value << std::endl;
  std::cout.flags(oldflags);
}
#define __watch(x) this->emit_watch(x, #x)
#endif

extern "C" void ext_copy_vector(block_type* dst,
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



static void error_handler(int error_code) {
  switch (error_code) {
  case 1:
    std::cerr << "memory access out of bounds." << std::endl;
    break;
  }
  std::abort();
}

class Compiler;

void init_sdata(const Compiler* cp, sdata_type* data, lnodeimpl* node);

///////////////////////////////////////////////////////////////////////////////

class SrcLogger {
public:
  SrcLogger(jit_function_t func, const char* fname, const char* vname = nullptr) : func_(func) {
    auto name = fname;
    if (vname) {
      auto tmp = stringf("%s @var=%s", fname, vname);
      auto tmp2 = new char[tmp.length() + 1]();
      strncpy(tmp2, tmp.c_str(), tmp.length());
      name = tmp2;
    }
    jit_insn_set_marker(func_, name);
  }
  ~SrcLogger() {
    jit_insn_set_marker(func_, "");
  }
private:
  jit_function_t func_;
};

///////////////////////////////////////////////////////////////////////////////

struct udf_data_t {
  udf_iface* udf;

  static uint32_t size(udfimpl*) {
    return sizeof(udf_data_t);
  }

  void init(udfimpl* node) {
    udf = node->udf();
  }
};

extern "C" void udf_data_eval(udf_data_t* self) {
  self->udf->eval();
}

extern "C" void udf_data_reset(udf_data_t* self) {
  self->udf->reset();
}

///////////////////////////////////////////////////////////////////////////////

typedef const char* (*enum_string_cb)(uint32_t value);

struct print_data_t {
  char* format;
  enum_string_cb* enum_strings;
  sdata_type* srcs;

  static uint32_t size(printimpl* node) {
    auto num_srcs = node->num_srcs() + (node->has_pred() ? -1 : 0);
    uint32_t size = sizeof(print_data_t);
    size += node->format().size() + 1; // format
    size += node->enum_strings().size() * sizeof(enum_string_cb); // enum_strings
    size += num_srcs * sizeof(sdata_type); // src_values
    return size;
  }

  void init(printimpl* node, const Compiler* cp) {
    auto buf = reinterpret_cast<uint8_t*>(this) + sizeof(print_data_t);

    auto fmt_len = node->format().size() + 1;
    format = reinterpret_cast<char*>(buf);
    memcpy(format, node->format().c_str(), fmt_len);
    buf += fmt_len;

    enum_strings = reinterpret_cast<enum_string_cb*>(buf);
    for (uint32_t i = 0, n = node->enum_strings().size(); i < n; ++i) {
      enum_strings[i] = node->enum_string(i);
    }
    buf += node->enum_strings().size() * sizeof(enum_string_cb);

    srcs = reinterpret_cast<sdata_type*>(buf);
    uint32_t pred = node->has_pred() ? 1 : 0;
    for (uint32_t i = 0, n = node->num_srcs() - pred; i < n; ++i) {
      init_sdata(cp, &srcs[i], node->src(i + pred).impl());
    }
  }
};

extern "C" void print_data_eval(print_data_t* self) {
  std::stringstream strbuf;
  fmtparser parser;
  for (const char *str = self->format; *str != '\0'; ++str) {
    if (*str == '{') {
      fmtinfo_t fmt;
      str = parser.parse(&fmt, str);
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
}

///////////////////////////////////////////////////////////////////////////////

struct assert_data_t {
  char* msg;
  char* file;
  int line;
  sdata_type time;

  static uint32_t size(assertimpl* node) {
    uint32_t size = sizeof(assert_data_t);
    size += node->msg().size() + 1; // msg
    size += node->sloc().file().size() + 1; // file
    return size;
  }

  void init(assertimpl* node, const Compiler* cp) {
    auto buf = reinterpret_cast<uint8_t*>(this) + sizeof(print_data_t);

    auto msg_len = node->msg().size() + 1;
    msg = reinterpret_cast<char*>(buf);
    memcpy(msg, node->msg().c_str(), msg_len);
    buf += msg_len;

    auto file_len = node->sloc().file().size() + 1;
    file = reinterpret_cast<char*>(buf);
    memcpy(file, node->sloc().file().c_str(), file_len);
    buf += file_len;

    line = node->sloc().line();

    init_sdata(cp, &time, node->time().impl());
  }
};

extern "C" void assert_data_eval(assert_data_t* self) {
  fprintf(stderr, "assertion failure at tick %ld, %s (%s:%d)\n",
          static_cast<uint64_t>(self->time), self->msg, self->file, self->line);
  std::abort();
}

///////////////////////////////////////////////////////////////////////////////

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
  sim_ctx_t()
  #ifdef JIT_BACKEND_INTERP
    : j_func(nullptr) {
  #else
    : entry(nullptr) {
  #endif
    j_ctx = jit_context_create();
  }

  ~sim_ctx_t() {
    if (j_ctx) {
      jit_context_destroy(j_ctx);
    }
  }

  sim_state_t state;
#ifdef JIT_BACKEND_INTERP
  jit_function_t j_func;
#else
  pfn_entry entry;
#endif
  jit_context_t j_ctx;  
};

///////////////////////////////////////////////////////////////////////////////

class Compiler {
private:

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

  sim_ctx_t*      sim_ctx_;
  alloc_map_t     addr_map_;
  var_map_t       input_map_;
  var_map_t       scalar_map_;
  var_map_t       pointer_map_;
  jit_label_t     l_bypass_;
  bypass_set_t    bypass_nodes_;
  bool            bypass_enable_;
  sblock_t        sblock_;
  jit_type_t      word_type_;
  jit_function_t  j_func_;
  jit_value_t     j_vars_;
  jit_value_t     j_ports_;
  uint32_t        vars_size_;
  uint32_t        ports_size_;
#ifndef NDEBUG
  jit_value_t     j_dbg_;
  uint32_t        dbg_off_;
#endif

  friend void init_sdata(const Compiler* Cp, sdata_type* data, lnodeimpl* node);

  void create_function() {
    jit_type_t params[1] = {jit_type_ptr};
    auto j_sig = jit_type_create_signature(jit_abi_cdecl, jit_type_int32, params, 1, 1);
    j_func_ = jit_function_create(sim_ctx_->j_ctx, j_sig);
    jit_type_free(j_sig);
    auto j_state = jit_value_get_param(j_func_, 0);
    j_vars_ = jit_insn_load_relative(j_func_, j_state, offsetof(sim_state_t, vars), jit_type_ptr);
    j_ports_ = jit_insn_load_relative(j_func_, j_state, offsetof(sim_state_t, ports), jit_type_ptr);
  #ifndef NDEBUG
    j_dbg_ = jit_insn_load_relative(j_func_, j_state, offsetof(sim_state_t, dbg), jit_type_ptr);
  #endif
  }

  void emit_node(litimpl* node) {
    __source_info();

    auto dst_width = node->size();
    if (dst_width <= WORD_SIZE) {
      auto j_ntype = to_native_type(dst_width);
      auto j_value = this->emit_constant(node->value().word(0), j_ntype);
      scalar_map_[node->id()] = j_value;
    }
  }

  void emit_node(proxyimpl* node) {
    __source_info();
    auto dst_width = node->size();
    auto j_ntype = to_native_type(dst_width);
    if (dst_width <= WORD_SIZE) {
      if (node->is_identity()) {
        auto j_src = scalar_map_[node->src(0).id()];
        auto j_res = jit_insn_load(j_func_, j_src);
        scalar_map_[node->id()] = this->emit_cast(j_res, j_ntype);
      } else {
        jit_value_t j_tmp = nullptr;
        for (auto& range : node->ranges()) {
          auto& src = node->src(range.src_idx);
          auto j_src = this->emit_load_slice_scalar(src.impl(), range.src_offset, range.length);
          j_tmp = this->emit_append_slice_scalar(j_tmp, range.dst_offset, j_src, j_ntype);
        }
        scalar_map_[node->id()] = this->emit_cast(j_tmp, j_ntype);
      }
    } else {
      auto dst_addr = this->get_pointer_address(node);
      jit_value_t j_tmp = nullptr;
      for (auto& range : node->ranges()) {
        auto& src = node->src(range.src_idx);
        auto it = scalar_map_.find(src.id());
        if (it != scalar_map_.end()) {
          auto j_src = this->emit_load_slice_scalar(src.impl(), range.src_offset, range.length);
          j_tmp = this->emit_append_slice_vector(
                j_tmp, dst_addr, range.dst_offset, dst_width, j_src, range.length);
        } else {
          auto src_addr = this->get_pointer_address(src.impl());
          j_tmp = this->emit_append_slice_vector(
                j_tmp, dst_addr, range.dst_offset, dst_width, src_addr, range.src_offset, range.length);
        }
      }
    }
  }

  void emit_node_input(ioportimpl* node) {
    __source_info_ex(node->name().c_str());
    auto dst_width = node->size();
    auto j_xtype = to_native_or_word_type(dst_width);
    auto addr = addr_map_.at(node->id());
    auto j_src_ptr = jit_insn_load_relative(j_func_, j_ports_, addr * sizeof(block_type*), jit_type_ptr);
    if (dst_width <= WORD_SIZE) {
      auto j_ntype = to_native_type(dst_width);
      auto j_value = jit_insn_load_relative(j_func_, j_src_ptr, 0, j_xtype);
      scalar_map_[node->id()] = this->emit_cast(j_value, j_ntype);
    } else {
      input_map_[node->id()] = j_src_ptr;
    }
  }

  void emit_node_output(ioportimpl* node) {
    __source_info_ex(node->name().c_str());
    auto dst_width = node->size();
    auto j_xtype = to_native_or_word_type(dst_width);
    auto addr = addr_map_.at(node->id());
    auto j_dst_ptr = jit_insn_load_relative(j_func_, j_ports_, addr * sizeof(block_type*), jit_type_ptr);
    if (dst_width <= WORD_SIZE) {
      auto j_src_value = scalar_map_.at(node->src(0).id());
      auto j_src_value_x = this->emit_cast(j_src_value, j_xtype);
      jit_insn_store_relative(j_func_, j_dst_ptr, 0, j_src_value_x);
    } else {
      auto j_src_ptr = this->emit_pointer_address(node->src(0).impl());
      this->emit_memcpy(j_dst_ptr, j_src_ptr, ceildiv(dst_width, 8));
    }
  }

  void emit_node(opimpl* node) {
    __source_info();

    struct auto_store_addr_t {
      Compiler*   Cp;
      lnodeimpl*  node;
      jit_value_t ptr;
      jit_value_t bkstore;

      auto_store_addr_t(Compiler* compiler, lnodeimpl* node) : Cp(compiler), node(node) {
        if (node->size() <= WORD_SIZE) {
          bkstore = jit_value_create(Cp->j_func_, Cp->word_type_);
          auto j_zero = Cp->emit_constant(0, Cp->word_type_);
          jit_insn_store(Cp->j_func_, bkstore, j_zero);
          ptr = Cp->emit_address_of(bkstore, Cp->word_type_);
        } else {
          bkstore = nullptr;
          ptr = Cp->emit_pointer_address(node);
        }
      }

      ~auto_store_addr_t() {
        if (bkstore) {
          auto j_ntype = to_native_type(node->size());
          Cp->scalar_map_[node->id()] = Cp->emit_cast(bkstore, j_ntype);
        }
      }
    };

    auto dst_width = node->size();
    auto j_ntype = to_native_type(dst_width);
    auto native_size = to_native_size(dst_width);
    auto is_signed = node->is_signed();

    auto is_scalar = (dst_width <= bitwidth_v<block_type>);
    if (node->num_srcs() > 0) {
      is_scalar &= (node->src(0).size() <= bitwidth_v<block_type>);
      if (CH_OP_CLASS(node->op()) != op_flags::shift
       && node->num_srcs() > 1) {
        is_scalar &= (node->src(1).size() <= bitwidth_v<block_type>);
      }
    }

    auto need_resize = node->should_resize_opds();
    auto j_src0 = this->emit_op_operand(node, 0, is_scalar, need_resize);
    auto j_src1 = this->emit_op_operand(node, 1, is_scalar, need_resize);

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
        auto j_dst = is_signed ? jit_insn_slt(j_func_, j_src0_s, j_src1_s) : jit_insn_ult(j_func_, j_src0_s, j_src1_s);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
      } else {
        auto j_dst = __op_call_relational(bv_lt_vector, j_src0, node->src(0).size(), j_src1, node->src(1).size());
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
      }
      break;
    case ch_op::gt:
      if (is_scalar) {
        auto j_src0_s = is_signed ? this->emit_sign_ext(j_src0, node->src(0).size()) : j_src0;
        auto j_src1_s = is_signed ? this->emit_sign_ext(j_src1, node->src(1).size()) : j_src1;
        auto j_dst = is_signed ? jit_insn_sgt(j_func_, j_src0_s, j_src1_s) : jit_insn_ugt(j_func_, j_src0_s, j_src1_s);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
      } else {
        auto j_dst = __op_call_relational(bv_lt_vector, j_src1, node->src(1).size(), j_src0, node->src(0).size());
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
      }
      break;
    case ch_op::le:
      if (is_scalar) {
        auto j_src0_s = is_signed ? this->emit_sign_ext(j_src0, node->src(0).size()) : j_src0;
        auto j_src1_s = is_signed ? this->emit_sign_ext(j_src1, node->src(1).size()) : j_src1;
        auto j_dst = is_signed ? jit_insn_sle(j_func_, j_src0_s, j_src1_s) : jit_insn_ule(j_func_, j_src0_s, j_src1_s);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
      } else {
        auto j_dst = __op_call_relational(bv_lt_vector, j_src1, node->src(1).size(), j_src0, node->src(0).size());
        auto j_dst_n = jit_insn_not(j_func_, j_dst);
        scalar_map_[node->id()] = this->emit_cast(j_dst_n, j_ntype);
      }
      break;
    case ch_op::ge:
      if (is_scalar) {
        auto j_src0_s = is_signed ? this->emit_sign_ext(j_src0, node->src(0).size()) : j_src0;
        auto j_src1_s = is_signed ? this->emit_sign_ext(j_src1, node->src(1).size()) : j_src1;
        auto j_dst = is_signed ? jit_insn_sge(j_func_, j_src0_s, j_src1_s) : jit_insn_uge(j_func_, j_src0_s, j_src1_s);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
      } else {
        auto j_dst = __op_call_relational(bv_lt_vector, j_src0, node->src(0).size(), j_src1, node->src(1).size());
        auto j_dst_n = jit_insn_not(j_func_, j_dst);
        scalar_map_[node->id()] = this->emit_cast(j_dst_n, j_ntype);
      }
      break;

    case ch_op::notl:
      if (is_scalar) {
        auto j_zero = this->emit_constant(0, j_ntype);
        auto j_dst = jit_insn_eq(j_func_, j_src0, j_zero);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
      } else {
        auto j_dst = __op_call_logical(bv_notl_vector, j_src0, node->src(0).size());
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
        auto j_dst = __op_call_logical(bv_andl_vector, j_src0, node->src(0).size(), j_src1, node->src(1).size());
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
        auto j_dst = __op_call_logical(bv_orl_vector, j_src0, node->src(0).size(), j_src1, node->src(1).size());
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
        __op_call_bitwise(bv_inv_vector, auto_dst.ptr, dst_width, j_src0, node->src(0).size());
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
          __op_call_bitwise(bv_and_vector, auto_dst.ptr, dst_width, j_src0, node->src(0).size(), j_src1, node->src(1).size());
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
          __op_call_bitwise(bv_or_vector, auto_dst.ptr, dst_width, j_src0, node->src(0).size(), j_src1, node->src(1).size());
        } else {
          auto dst_addr = addr_map_.at(node->id());
          auto num_words = ceildiv(dst_width, WORD_SIZE);
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
          __op_call_bitwise(bv_xor_vector, auto_dst.ptr, dst_width, j_src0, node->src(0).size(), j_src1, node->src(1).size());
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
        auto j_dst = __op_call_reduce(bv_andr_vector, j_src0, node->src(0).size());
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
      }
      break;
    case ch_op::orr:
      if (is_scalar) {
        auto j_dst = jit_insn_to_bool(j_func_, j_src0);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
        this->emit_clear_extra_bits(node);
      } else {
        auto j_dst = __op_call_reduce(bv_orr_vector, j_src0, node->src(0).size());
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
      }
      break;
    case ch_op::xorr:
      if (is_scalar) {
        auto j_dst = this->emit_xorr_scalar(j_src0, node->src(0).size());
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
        this->emit_clear_extra_bits(node);
      } else {
        auto j_dst = __op_call_reduce(bv_xorr_vector, j_src0, node->src(0).size());
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
      }
      break;

    case ch_op::shl:
      if (is_scalar) {
        jit_label_t l_else(jit_label_undefined);
        jit_label_t l_exit(jit_label_undefined);
        auto j_dst = jit_value_create(j_func_, j_ntype);
        scalar_map_[node->id()] = j_dst;
        auto j_max = this->emit_constant(native_size, j_ntype);
        auto j_zero = this->emit_constant(0, j_ntype);
        auto j_overflow = jit_insn_uge(j_func_, j_src1, j_max);
        jit_insn_branch_if(j_func_, j_overflow, &l_else);
        auto j_src0_n = this->emit_cast(j_src0, j_ntype);
        auto j_tmp = jit_insn_shl(j_func_, j_src0_n, j_src1);
        jit_insn_store(j_func_, j_dst, j_tmp);
        jit_insn_branch(j_func_, &l_exit);
        jit_insn_label(j_func_, &l_else);
        jit_insn_store(j_func_, j_dst, j_zero);
        jit_insn_label(j_func_, &l_exit);
        this->emit_clear_extra_bits(node);
      } else {
        auto_store_addr_t auto_dst(this, node);
        __op_call_shl(bv_shl_vector, auto_dst.ptr, dst_width, j_src0, node->src(0).size(), j_src1);
      }
      break;
    case ch_op::shr:
      if (is_scalar) {
        jit_label_t l_else(jit_label_undefined);
        jit_label_t l_exit(jit_label_undefined);
        auto j_dst = jit_value_create(j_func_, j_ntype);
        scalar_map_[node->id()] = j_dst;
        if (is_signed) {
          auto j_src0_x = (dst_width > node->src(0).size()) ? this->emit_cast(j_src0, j_ntype) : j_src0;
          auto j_src0_s = this->emit_sign_ext(j_src0_x, node->src(0).size());
          auto src0_type = jit_value_get_type(j_src0_s);
          auto src0_size = get_value_size(j_src0_s);
          auto j_max = this->emit_constant(src0_size, src0_type);
          auto j_overflow = jit_insn_uge(j_func_, j_src1, j_max);
          jit_insn_branch_if(j_func_, j_overflow, &l_else);
          auto j_tmp1 = jit_insn_sshr(j_func_, j_src0_s, j_src1);
          jit_insn_store(j_func_, j_dst, j_tmp1);
          jit_insn_branch(j_func_, &l_exit);
          jit_insn_label(j_func_, &l_else);
          auto j_maxM1 = this->emit_constant(src0_size - 1, src0_type);
          auto j_tmp2 = jit_insn_sshr(j_func_, j_src0_s, j_maxM1);
          jit_insn_store(j_func_, j_dst, j_tmp2);
          jit_insn_label(j_func_, &l_exit);
          this->emit_clear_extra_bits(node);
        } else {
          auto src0_type = jit_value_get_type(j_src0);
          auto src0_size = get_value_size(j_src0);
          auto j_max = this->emit_constant(src0_size, src0_type);
          auto j_zero = this->emit_constant(0, j_ntype);
          auto j_overflow = jit_insn_uge(j_func_, j_src1, j_max);
          jit_insn_branch_if(j_func_, j_overflow, &l_else);
          auto j_tmp = jit_insn_ushr(j_func_, j_src0, j_src1);
          jit_insn_store(j_func_, j_dst, j_tmp);
          jit_insn_branch(j_func_, &l_exit);
          jit_insn_label(j_func_, &l_else);
          jit_insn_store(j_func_, j_dst, j_zero);
          jit_insn_label(j_func_, &l_exit);
        }
      } else {
        auto_store_addr_t auto_dst(this, node);
        __op_call_shr(bv_shr_vector, auto_dst.ptr, dst_width, j_src0, node->src(0).size(), j_src1);
      }
      break;

    case ch_op::neg:
      if (is_scalar) {
        auto j_dst = jit_insn_neg(j_func_, j_src0);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
        this->emit_clear_extra_bits(node);
      } else {
        auto_store_addr_t auto_dst(this, node);
        __op_call_arithmetic(bv_neg_vector, auto_dst.ptr, dst_width, j_src0, node->src(0).size());
      }
      break;
    case ch_op::add:
      if (is_scalar) {
        auto j_dst = jit_insn_add(j_func_, j_src0, j_src1);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
        this->emit_clear_extra_bits(node);
      } else {
        auto_store_addr_t auto_dst(this, node);
        __op_call_arithmetic(bv_add_vector, auto_dst.ptr, dst_width, j_src0, node->src(0).size(), j_src1, node->src(1).size());
      }
      break;
    case ch_op::sub:
      if (is_scalar) {
        auto j_dst = jit_insn_sub(j_func_, j_src0, j_src1);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
        this->emit_clear_extra_bits(node);
      } else {
        auto_store_addr_t auto_dst(this, node);
        __op_call_arithmetic(bv_sub_vector, auto_dst.ptr, dst_width, j_src0, node->src(0).size(), j_src1, node->src(1).size());
      }
      break;

    case ch_op::mul:
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
        __op_call_arithmetic2(bv_mul_vector, auto_dst.ptr, dst_width, j_src0, node->src(0).size(), j_src1, node->src(1).size());
      }
      break;
    case ch_op::div:
      if (is_scalar) {
        auto j_src0_s = is_signed ? this->emit_sign_ext(j_src0, node->src(0).size()) : j_src0;
        auto j_src1_s = is_signed ? this->emit_sign_ext(j_src1, node->src(1).size()) : j_src1;
        auto j_dst = is_signed ? jit_insn_sdiv(j_func_, j_src0_s, j_src1_s) : jit_insn_udiv(j_func_, j_src0_s, j_src1_s);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
        this->emit_clear_extra_bits(node);
      } else {
        auto_store_addr_t auto_dst(this, node);
        __op_call_arithmetic2(bv_div_vector, auto_dst.ptr, dst_width, j_src0, node->src(0).size(), j_src1, node->src(1).size());
      }
      break;
    case ch_op::mod:
      if (is_scalar) {
        auto j_src0_s = is_signed ? this->emit_sign_ext(j_src0, node->src(0).size()) : j_src0;
        auto j_src1_s = is_signed ? this->emit_sign_ext(j_src1, node->src(1).size()) : j_src1;
        auto j_dst = is_signed ? jit_insn_srem(j_func_, j_src0_s, j_src1_s) : jit_insn_urem(j_func_, j_src0_s, j_src1_s);
        scalar_map_[node->id()] = this->emit_cast(j_dst, j_ntype);
        this->emit_clear_extra_bits(node);
      } else {
        auto_store_addr_t auto_dst(this, node);
        __op_call_arithmetic2(bv_mod_vector, auto_dst.ptr, dst_width, j_src0, node->src(0).size(), j_src1, node->src(1).size());
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
        __op_call_arithmetic2(bv_pad_vector, auto_dst.ptr, dst_width, j_src0, node->src(0).size());
      }
      break;
    default:
      std::abort();
      break;
    }
  }

  jit_value_t emit_op_operand(opimpl* node,
                               uint32_t opd,
                               bool is_scalar,
                               bool need_resize) {
    __source_info();
    if (opd >= node->num_srcs())
      return nullptr;
    auto src = node->src(opd).impl();    
    if (is_scalar) {
      auto it = scalar_map_.find(src->id());
      if (it != scalar_map_.end()) {
        auto j_value = scalar_map_.at(src->id());
        auto is_signed = node->is_signed();
        if (need_resize && is_signed) {
          j_value = this->emit_sign_ext(j_value, src->size());
        }
        return j_value;
      } else {
        assert(op_flags::shift == CH_OP_CLASS(node->op()));
        return this->emit_load_scalar_relative(src, 0, jit_type_int32);
      }
    } else {
      auto it = scalar_map_.find(src->id());
      if (it != scalar_map_.end()) {
        if (op_flags::shift == CH_OP_CLASS(node->op())
         && 1 == opd) {
          return this->emit_cast(it->second, jit_type_int32);
        } else {
          return this->emit_address_of(it->second, word_type_);
        }
      } else {
        if (op_flags::shift == CH_OP_CLASS(node->op())
         && 1 == opd) {
          return this->emit_load_scalar_relative(src, 0, jit_type_int32);
        } else {
          return this->emit_pointer_address(src);
        }
      }
    }
  }

  jit_value_t emit_op_call_relational(void* pfn,
                                       const char* name,
                                       jit_value_t j_in,
                                       uint32_t in_size) {
    __source_info();

    // setup arguments
    auto j_in_size = this->emit_constant(in_size, jit_type_int32);

    // call native function
    jit_type_t params[] = {jit_type_ptr, jit_type_int32};
    auto j_sig = jit_type_create_signature(jit_abi_cdecl,
                                           jit_type_int32,
                                           params,
                                           __countof(params),
                                           1);
    jit_value_t args[] = {j_in, j_in_size};
    auto ret = jit_insn_call_native(j_func_,
                                    name,
                                    pfn,
                                    j_sig,
                                    args,
                                    __countof(args),
                                    JIT_CALL_NOTHROW);
    jit_type_free(j_sig);
    return ret;
  }

  jit_value_t emit_op_call_relational(void* pfn,
                                       const char* name,
                                       jit_value_t j_lhs,
                                       uint32_t lhs_size,
                                       jit_value_t j_rhs,
                                       uint32_t rhs_size) {
    __source_info();

    // setup arguments
    auto j_lhs_size = this->emit_constant(lhs_size, jit_type_int32);
    auto j_rhs_size = this->emit_constant(rhs_size, jit_type_int32);

    // call native function
    jit_type_t params[] = {jit_type_ptr, jit_type_int32,
                           jit_type_ptr, jit_type_int32};
    auto j_sig = jit_type_create_signature(jit_abi_cdecl,
                                           jit_type_int32,
                                           params,
                                           __countof(params),
                                           1);
    jit_value_t args[] = {j_lhs, j_lhs_size, j_rhs, j_rhs_size};
    auto ret = jit_insn_call_native(j_func_,
                                    name,
                                    pfn,
                                    j_sig,
                                    args,
                                    __countof(args),
                                    JIT_CALL_NOTHROW);
    jit_type_free(j_sig);
    return ret;
  }

  void emit_op_call_bitwise(void* pfn,
                            const char* name,
                            jit_value_t j_out,
                            uint32_t out_size,
                            jit_value_t j_in,
                            uint32_t in_size) {
    __source_info();

    // setup arguments
    auto j_out_size = this->emit_constant(out_size, jit_type_int32);
    auto j_in_size = this->emit_constant(in_size, jit_type_int32);

    // call native function
    jit_type_t params[] = {jit_type_ptr, jit_type_int32,
                           jit_type_ptr, jit_type_int32};
    auto j_sig = jit_type_create_signature(jit_abi_cdecl,
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
    jit_type_free(j_sig);
  }

  void emit_op_call_bitwise(void* pfn,
                            const char* name,
                            jit_value_t j_out,
                            uint32_t out_size,
                            jit_value_t j_lhs,
                            uint32_t lhs_size,
                            jit_value_t j_rhs,
                            uint32_t rhs_size) {
    __source_info();

    // setup arguments
    auto j_out_size = this->emit_constant(out_size, jit_type_int32);
    auto j_lhs_size = this->emit_constant(lhs_size, jit_type_int32);
    auto j_rhs_size = this->emit_constant(rhs_size, jit_type_int32);

    // call native function
    jit_type_t params[] = {jit_type_ptr, jit_type_int32,
                           jit_type_ptr, jit_type_int32,
                           jit_type_ptr, jit_type_int32};
    auto j_sig = jit_type_create_signature(jit_abi_cdecl,
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
    jit_type_free(j_sig);
  }

  void emit_op_call_shift(void* pfn,
                           const char* name,
                           jit_value_t j_out,
                           uint32_t out_size,
                           jit_value_t j_lhs,
                           uint32_t lhs_size,
                           jit_value_t j_rhs) {
    __source_info();

    // setup arguments
    auto j_out_size = this->emit_constant(out_size, jit_type_int32);
    auto j_lhs_size = this->emit_constant(lhs_size, jit_type_int32);
    assert(32 == get_value_size(j_rhs));

    // call native function
    jit_type_t params[] = {jit_type_ptr, jit_type_int32,
                           jit_type_ptr, jit_type_int32,
                           jit_type_int32};
    auto j_sig = jit_type_create_signature(jit_abi_cdecl,
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
    jit_type_free(j_sig);
  }

  bool optimize_select(selectimpl* node) {
    //--
    if (0 != (platform::self().cflags() & cflags::disable_swo))
      return false;

    //--
    auto dst_width = node->size();
    bool is_scalar = (dst_width <= WORD_SIZE);
    auto key_size = node->key().size();
    auto is_switch = node->has_key() && (key_size <= 32);
    if (!is_switch)
      return false;
    auto j_ntype = to_native_type(dst_width);
    int32_t l = node->num_srcs() - 1;
    int32_t start = is_switch ? 1 : 0;
    jit_value_t j_dst = nullptr;
    if (is_scalar) {
      j_dst = jit_value_create(j_func_, j_ntype);
      scalar_map_[node->id()] = j_dst;
    }

    // analyze the select node
    bool is_constant = (type_lit == node->src(l).impl()->type());
    auto pred_min = std::numeric_limits<int64_t>::max();
    auto pred_max = std::numeric_limits<int64_t>::min();
    int64_t pred_delta = 0;
    int64_t i_pred_prev = 0;
    for (int32_t i = start; i < l; i += 2) {
      auto j_pred = scalar_map_.at(node->src(i+0).id());
      if (is_switch) {
        auto pred_value = jit_value_get_int_constant(j_pred);
        pred_delta += (i != start) ? (pred_value - i_pred_prev) : 0;
        pred_min = std::min(pred_value, pred_min);
        pred_max = std::max(pred_value, pred_max);
        i_pred_prev = pred_value;
      }
      auto value = node->src(i+1).impl();
      is_constant &= (type_lit == value->type());
    }

    auto distance = (pred_max - pred_min) + 1;
    if (is_switch
     && l > 3*2+1
     && is_constant
     && distance * dst_width <= WORD_SIZE) {
      //
      // short switch tables
      //
      jit_label_t l_default(jit_label_undefined);
      jit_label_t l_exit(jit_label_undefined);
      auto max_cases = (1ll << key_size);
      bool is_inclusive = (max_cases * dst_width <= WORD_SIZE);

      if (!is_inclusive) {
        auto j_key = scalar_map_.at(node->key().id());
        auto j_max = this->emit_constant(pred_max, jit_type_int32);
        auto j_pred = jit_insn_ugt(j_func_, j_key, j_max);
        if (pred_min) {
          auto j_min = this->emit_constant(pred_min, jit_type_int32);
          auto j_tmp = jit_insn_ult(j_func_, j_key, j_min);
          j_pred = jit_insn_or(j_func_, j_pred, j_tmp);
        }
        jit_insn_branch_if(j_func_, j_pred, &l_default);
      }

      block_type table(0);
      int32_t k = start;
      int32_t length = is_inclusive ? max_cases : distance;
      int32_t offset = is_inclusive ? 0 : pred_min;
      auto j_def_value = scalar_map_.at(node->src(l).id());
      auto def_value = jit_value_get_int_constant(j_def_value);

      for (int i = 0; i < length; ++i) {
        bool found = false;
        for (int32_t j = k; j < l; j += 2) {
          auto j_pred = scalar_map_.at(node->src(j+0).id());
          auto pred_value = jit_value_get_int_constant(j_pred);
          if (pred_value == offset + i) {
            auto j_src = scalar_map_.at(node->src(j+1).id());
            auto src_value = jit_value_get_int_constant(j_src);
            table |= src_value << (i * dst_width);
            found  = true;
            k += 2;
            break;
          }
        }
        if (!found) {
          table |= def_value << (i * dst_width);
        }
      }

      auto j_ttype = to_native_or_word_type(length * dst_width);
      auto j_table = this->emit_constant(table, j_ttype);
      auto j_key = scalar_map_.at(node->key().id());

      if (!is_inclusive && pred_min) {
        auto j_min = this->emit_constant(pred_min, jit_type_int32);
        j_key = jit_insn_sub(j_func_, j_key, j_min);
      }

      jit_value_t j_shift;
      if (ispow2(dst_width)) {
        auto j_destW = this->emit_constant(log2floor(dst_width), j_ttype);
        j_shift = jit_insn_shl(j_func_, j_key, j_destW);
      } else {
        auto j_destW = this->emit_constant(dst_width, j_ttype);
        j_shift = jit_insn_mul(j_func_, j_key, j_destW);
      }

      auto j_tmp1 = jit_insn_ushr(j_func_, j_table, j_shift);
      auto j_mask = this->emit_constant((1ull << dst_width)-1, j_ttype);
      auto j_tmp2 = jit_insn_and(j_func_, j_tmp1, j_mask);
      jit_insn_store(j_func_, j_dst, j_tmp2);

      if (!is_inclusive) {
        jit_insn_branch(j_func_, &l_exit);

        // emit 'default' block
        jit_insn_label(j_func_, &l_default);
        auto j_src = scalar_map_.at(node->src(l).id());
        jit_insn_store(j_func_, j_dst, j_src);

        jit_insn_label(j_func_, &l_exit);
      }
      return true;
    }

    return false;
  }

  void emit_node(selectimpl* node) {
    __source_info();

    auto status = optimize_select(node);
    if (status)
      return;

    uint32_t dst_width = node->size();
    bool is_scalar = (dst_width <= WORD_SIZE);
    auto j_ntype = to_native_type(dst_width);
    auto l = node->num_srcs() - 1;

    jit_value_t j_dst = nullptr;
    if (is_scalar) {
      j_dst = jit_value_create(j_func_, j_ntype);
      scalar_map_[node->id()] = j_dst;
    }

    if (node->has_key()) {
      // lower switch statements
      auto key_size = node->key().size();
      if (is_scalar && (key_size <= WORD_SIZE)) {
        auto j_key = scalar_map_.at(node->key().id());
        std::vector<jit_value_t> preds(l/2), values(l/2);
        for (uint32_t i = 1; i < l; i += 2) {
          preds[i/2] = scalar_map_.at(node->src(i+0).id());
          values[i/2] = scalar_map_.at(node->src(i+1).id());
        }
        auto def_value = scalar_map_.at(node->src(l).id());
        auto j_tmp = jit_insn_switch(j_func_, j_key, preds.data(), values.data(), l/2, def_value);
        scalar_map_[node->id()] = j_tmp;
      } else {
        std::vector<jit_label_t> labels(l/2, jit_label_undefined);
        std::unordered_map<uint32_t, uint32_t> unique_values;
        jit_label_t l_exit(jit_label_undefined);

        // emit jump tests
        for (uint32_t i = 1; i < l; i += 2) {
          auto label = &labels.at(i/2);
          auto src = node->src(i+1).impl();
          auto it = unique_values.find(src->id());
          if (it != unique_values.end()) {
            label = &labels.at(it->second);
          } else {
            unique_values[src->id()] = i/2;
          }
          if (key_size <= WORD_SIZE) {
            auto j_key = scalar_map_.at(node->key().id());
            auto j_val = scalar_map_.at(node->src(i).id());
            auto j_pred = jit_insn_eq(j_func_, j_key, j_val);
            jit_insn_branch_if(j_func_, j_pred, label);
          } else {
            auto j_key_ptr = this->emit_pointer_address(node->key().impl());
            auto j_val_ptr = this->emit_pointer_address(node->src(i).impl());
            auto j_pred = this->emit_eq_vector(j_key_ptr, key_size, j_val_ptr, key_size, false);
            jit_insn_branch_if(j_func_, j_pred, label);
          }
        }

        // emit 'default' block
        if (is_scalar) {
          auto j_src = scalar_map_.at(node->src(l).id());
          jit_insn_store(j_func_, j_dst, j_src);
        } else {
          auto j_dst_ptr = this->emit_pointer_address(node);
          auto j_src_ptr = this->emit_pointer_address(node->src(l).impl());
          this->emit_memcpy(j_dst_ptr, j_src_ptr, ceildiv(dst_width, 8));
        }
        jit_insn_branch(j_func_, &l_exit);

        // emit 'case' blocks
        for (uint32_t i = 1; i < l; i += 2) {
          auto src = node->src(i+1).impl();
          auto k = unique_values[src->id()];
          if (k != i/2)
            continue;
          jit_insn_label(j_func_, &labels.at(i/2));
          if (is_scalar) {
            auto j_src = scalar_map_.at(src->id());
            jit_insn_store(j_func_, j_dst, j_src);
          } else {
            auto j_dst_ptr = this->emit_pointer_address(node);
            auto j_src_ptr = this->emit_pointer_address(src);
            this->emit_memcpy(j_dst_ptr, j_src_ptr, ceildiv(dst_width, 8));
          }
          if (i != l-1) {
            jit_insn_branch(j_func_, &l_exit);
          }
        }

        // exit
        jit_insn_label(j_func_, &l_exit);
      }
    } else {      
      if (is_scalar && l == 2) {
        // emit ternary operator
        auto j_pred  = scalar_map_.at(node->src(0).id());
        auto j_true  = scalar_map_.at(node->src(1).id());
        auto j_false = scalar_map_.at(node->src(2).id());
        auto j_tmp = jit_insn_select(j_func_, j_pred, j_true, j_false);
        scalar_map_[node->id()] = j_tmp;
      } else {
        // lower conditional branches
        std::vector<jit_label_t> labels(l/2, jit_label_undefined);
        jit_label_t l_exit(jit_label_undefined);

        // emit jump tests
        for (uint32_t i = 0; i < l; i += 2) {
          auto j_pred = scalar_map_.at(node->src(i).id());
          jit_insn_branch_if(j_func_, j_pred, &labels.at(i/2));
        }

        // emit 'else' block
        if (is_scalar) {
          auto j_src = scalar_map_.at(node->src(l).id());
          jit_insn_store(j_func_, j_dst, j_src);
        } else {
          auto j_dst_ptr = this->emit_pointer_address(node);
          auto j_src_ptr = this->emit_pointer_address(node->src(l).impl());
          this->emit_memcpy(j_dst_ptr, j_src_ptr, ceildiv(dst_width, 8));
        }
        jit_insn_branch(j_func_, &l_exit);

        // emit 'if' blocks
        for (uint32_t i = 0; i < l; i += 2) {
          auto src = node->src(i+1).impl();
          jit_insn_label(j_func_, &labels.at(i/2));
          if (is_scalar) {
            auto j_src = scalar_map_.at(src->id());
            jit_insn_store(j_func_, j_dst, j_src);
          } else {
            auto j_dst_ptr = this->emit_pointer_address(node);
            auto j_src_ptr = this->emit_pointer_address(src);
            this->emit_memcpy(j_dst_ptr, j_src_ptr, ceildiv(dst_width, 8));
          }
          if (i != l-1) {
            jit_insn_branch(j_func_, &l_exit);
          }
        }

        // exit
        jit_insn_label(j_func_, &l_exit);
      }
    }
  }

  void emit_node(cdimpl* node) {
    __source_info();

    auto j_clk = scalar_map_.at(node->src(0).id());
    auto addr = addr_map_.at(node->id());
    auto j_prev_clk = jit_insn_load_relative(j_func_, j_vars_, addr, jit_type_int32);
    auto j_clk_changed = jit_insn_xor(j_func_, j_clk, j_prev_clk);
    jit_value_t j_changed ;

    if (node->pos_edge()) {
      j_changed = jit_insn_and(j_func_, j_clk_changed, j_clk);
    } else {
      auto j_clk_n = jit_insn_not(j_func_, j_clk);
      j_changed = jit_insn_and(j_func_, j_clk_changed, j_clk_n);
    }

    jit_insn_store_relative(j_func_, j_vars_, addr, j_clk);

    auto bypass_enable = (1 == node->ctx()->cdomains().size())
                       && 0 == (platform::self().cflags() & cflags::disable_cpb)
      && ch::internal::compiler::build_bypass_list(bypass_nodes_, node->ctx(), node->id());
    if (bypass_enable) {      
      jit_label_t l_skip(jit_label_undefined);
      jit_insn_branch_if_not(j_func_, j_changed, &l_skip);
      l_bypass_ = l_skip;
      bypass_enable_ = true;
    } else {
      scalar_map_[node->id()] = j_changed;
      bypass_enable_ = false;
    }
  }

  void resolve_branch(lnodeimpl* node) {
    if (sblock_.cd
     && ((0 != (platform::self().cflags() & cflags::disable_snc)
      || (nullptr == node)
      || !is_snode_type(node->type())
      || get_snode_cd(node) != sblock_.cd
      || get_snode_reset(node) != sblock_.reset))) {
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

    jit_label_t l_exit(jit_label_undefined);

    // emit clock domain
    bool merged_cd_enable = false;
    if (!bypass_enable_) {
      if (!sblock_.reset) {
        auto it = sblock_.nodes.begin();
        auto end = sblock_.nodes.end();
        auto enable = get_snode_enable(*it++);
        if (enable) {
          merged_cd_enable = true;
          while (it != end) {
            if (get_snode_enable(*it++) != enable) {
              merged_cd_enable = false;
              break;
            }
          }
        }
      }
      if (!merged_cd_enable) {
        auto j_cd = scalar_map_.at(sblock_.cd->id());
        jit_insn_branch_if_not(j_func_, j_cd, &l_exit);
      }
    }

    if (sblock_.reset) {
      // emit reset nodes
      jit_label_t l_skip(jit_label_undefined);
      auto j_reset = scalar_map_.at(sblock_.reset->id());
      jit_insn_branch_if_not(j_func_, j_reset, &l_skip);

      for (auto node : sblock_.nodes) {
        switch (node->type()) {
        case type_reg:
          this->emit_snode_init(reinterpret_cast<regimpl*>(node));
          break;
        case type_udfs:
          this->emit_snode_init(reinterpret_cast<udfsimpl*>(node));
          break;
        default:
          break;
        }
      }

      jit_insn_branch(j_func_, &l_exit);
      jit_insn_label(j_func_, &l_skip);
    }

    {
      // emit enable nodes
      jit_label_t l_skip(jit_label_undefined);
      lnodeimpl* cur_enable = nullptr;
      for (auto node : sblock_.nodes) {
        auto enable = get_snode_enable(node);
        if (enable != cur_enable) {
          if (cur_enable) {
            jit_insn_label(j_func_, &l_skip);
            l_skip = jit_label_undefined;
          };
          if (enable) {
            auto j_enable = scalar_map_.at(enable->id());
            if (merged_cd_enable) {
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
      if (l_skip != jit_label_undefined) {
        jit_insn_label(j_func_, &l_skip);
      };
    }
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

    auto dst_width = node->size();
    auto j_xtype = to_native_or_word_type(dst_width);
    auto is_scalar = (dst_width <= WORD_SIZE);
    auto dst_addr = addr_map_.at(node->id());

    jit_value_t j_dst = nullptr;
    jit_value_t j_init_data = nullptr;

    if (is_scalar) {
      j_dst = scalar_map_.at(node->id());
      j_init_data = scalar_map_.at(node->init_data().id());
    }

    if (node->is_pipe()) {
      auto pipe_length = node->length() - 1;
      auto pipe_width = pipe_length * dst_width;
      auto j_pipe_xtype = to_native_or_word_type(pipe_width);
      auto j_pipe_ntype = to_native_type(pipe_width);
      uint32_t pipe_addr = dst_addr + __align_word_size(dst_width);
      auto is_pipe_scalar = (pipe_width <= WORD_SIZE);
      if (is_pipe_scalar) {
        assert(is_scalar);
        // reset dst register
        auto j_init_data_x = this->emit_cast(j_init_data, j_xtype);
        jit_insn_store_relative(j_func_, j_vars_, dst_addr, j_init_data_x);
        jit_insn_store(j_func_, j_dst, j_init_data);

        // reset pipe registers
        auto j_init_data_p = this->emit_cast(j_init_data, j_pipe_ntype);
        jit_value_t j_tmp = nullptr;
        for (uint32_t i = 0; i < pipe_length; ++i) {
          j_tmp = this->emit_append_slice_scalar(j_tmp, i * dst_width, j_init_data_p, j_pipe_ntype);
        }
        auto j_tmp_x = this->emit_cast(j_tmp, j_pipe_xtype);
        jit_insn_store_relative(j_func_, j_vars_, pipe_addr, j_tmp_x);
      } else {
        if (is_scalar) {
          // reset dst register          
          auto j_init_data_x = this->emit_cast(j_init_data, j_xtype);
          jit_insn_store_relative(j_func_, j_vars_, dst_addr, j_init_data_x);
          jit_insn_store(j_func_, j_dst, j_init_data);

          // reset pipe registers
          if (node->length() <= INLINE_THRESHOLD
           || jit_value_is_constant(j_init_data)) {
            auto j_init_data_w = this->emit_cast(j_init_data, word_type_);
            jit_value_t j_tmp = nullptr;
            for (uint32_t i = 0; i < pipe_length; ++i) {
              j_tmp = this->emit_append_slice_vector(
                    j_tmp, memaddr_t{j_vars_, pipe_addr}, i * dst_width, pipe_width, j_init_data_w, dst_width);
            }
          } else {
            jit_label_t l_loop(jit_label_undefined);
            jit_label_t l_exit(jit_label_undefined);
            auto j_pipe_ptr = jit_insn_add_relative(j_func_, j_vars_, pipe_addr);
            auto j_index = jit_value_create(j_func_, jit_type_int32);
            auto j_lengthM1 = this->emit_constant(pipe_length - 1, jit_type_int32);
            jit_insn_store(j_func_, j_index, j_lengthM1);
            jit_insn_label(j_func_, &l_loop);
            this->emit_store_array_scalar(j_pipe_ptr, pipe_width, j_index, j_init_data, dst_width);
            jit_insn_branch_if_not(j_func_, j_index, &l_exit);
            auto j_one = this->emit_constant(1, jit_type_int32);
            auto j_sub = jit_insn_sub(j_func_, j_index, j_one);
            jit_insn_store(j_func_, j_index, j_sub);
            jit_insn_branch(j_func_, &l_loop);
            jit_insn_label(j_func_, &l_exit);
          }
        } else {
          // reset dst register
          auto j_dst_ptr = jit_insn_add_relative(j_func_, j_vars_, dst_addr);
          auto j_init_ptr = this->emit_pointer_address(node->init_data().impl());
          this->emit_memcpy(j_dst_ptr, j_init_ptr, ceildiv(dst_width, 8));

          // reset pipe registers
          auto j_pipe_ptr = jit_insn_add_relative(j_func_, j_vars_, pipe_addr);
          if (node->length() <= INLINE_THRESHOLD) {
            for (uint32_t i = 0; i < pipe_length; ++i) {
              this->emit_copy_vector(j_pipe_ptr, i * dst_width, j_init_ptr, 0, dst_width);
            }
          } else {
            jit_label_t l_loop(jit_label_undefined);
            jit_label_t l_exit(jit_label_undefined);
            auto j_index = jit_value_create(j_func_, jit_type_int32);
            auto j_lengthM1 = this->emit_constant(pipe_length - 1, jit_type_int32);
            jit_insn_store(j_func_, j_index, j_lengthM1);
            jit_insn_label(j_func_, &l_loop);
            this->emit_store_array_vector(j_pipe_ptr, j_index, j_init_data, dst_width);
            jit_insn_branch_if_not(j_func_, j_index, &l_exit);
            auto j_one = this->emit_constant(1, jit_type_int32);
            auto j_sub = jit_insn_sub(j_func_, j_index, j_one);
            jit_insn_store(j_func_, j_index, j_sub);
            jit_insn_branch(j_func_, &l_loop);
            jit_insn_label(j_func_, &l_exit);
          }
        }
      }
    } else {
      if (is_scalar) {
        auto j_init_data_x = this->emit_cast(j_init_data, j_xtype);
        jit_insn_store_relative(j_func_, j_vars_, dst_addr, j_init_data_x);
        jit_insn_store(j_func_, j_dst, j_init_data);
      } else {
        auto j_dst_ptr = jit_insn_add_relative(j_func_, j_vars_, dst_addr);
        auto j_init_ptr = this->emit_pointer_address(node->init_data().impl());
        this->emit_memcpy(j_dst_ptr, j_init_ptr, ceildiv(dst_width, 8));
      }
    }
  }

  void emit_snode_value(regimpl* node) {
    __source_info();

    auto dst_width = node->size();
    auto j_xtype = to_native_or_word_type(dst_width);
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
      auto pipe_length = node->length() - 1;
      auto pipe_width = pipe_length * dst_width;
      auto pipe_addr = dst_addr + __align_word_size(dst_width);
      auto is_pipe_scalar = (pipe_width <= WORD_SIZE);

      if (is_pipe_scalar) {
        assert(is_scalar);
        auto j_pipe_xtype = to_native_or_word_type(pipe_width);
        auto j_pipe_ntype = to_native_type(pipe_width);
        if (pipe_width == dst_width) {
          // dst <- pipe
          auto j_pipe = jit_insn_load_relative(j_func_, j_vars_, pipe_addr, j_xtype);
          jit_insn_store_relative(j_func_, j_vars_, dst_addr, j_pipe);
          auto j_pipe_n = this->emit_cast(j_pipe, j_ntype);
          jit_insn_store(j_func_, j_dst, j_pipe_n);

          // pipe <- next
          auto j_next_x = this->emit_cast(j_next, j_xtype);
          jit_insn_store_relative(j_func_, j_vars_, pipe_addr, j_next_x);
        } else {
          // dst <- pipe[0]
          auto j_pipe = jit_insn_load_relative(j_func_, j_vars_, pipe_addr, j_pipe_xtype);
          auto j_pipe_0 = this->emit_scalar_slice(j_pipe, 0, dst_width);
          auto j_pipe_0_n = this->emit_cast(j_pipe_0, j_ntype);
          auto j_pipe_0_x = this->emit_cast(j_pipe_0_n, j_xtype);
          jit_insn_store_relative(j_func_, j_vars_, dst_addr, j_pipe_0_x);
          jit_insn_store(j_func_, j_dst, j_pipe_0_n);

          // pipe >>= dst_width
          auto j_shift = this->emit_constant(dst_width, jit_type_int32);
          auto j_pipe_s = jit_insn_ushr(j_func_, j_pipe, j_shift);

          // pipe[n-1] <- next
          auto j_shfn1  = this->emit_constant((pipe_length - 1) * dst_width, jit_type_int32);
          auto j_next_p = this->emit_cast(j_next, j_pipe_ntype);
          auto j_next_s = jit_insn_shl(j_func_, j_next_p, j_shfn1);
          auto j_or     = jit_insn_or(j_func_, j_next_s, j_pipe_s);
          auto j_or_v   = this->emit_cast(j_or, j_pipe_xtype);
          jit_insn_store_relative(j_func_, j_vars_, pipe_addr, j_or_v);
        }
      } else {
        if (pipe_width == dst_width) {
          // dst <- pipe
          auto j_pipe_ptr = jit_insn_add_relative(j_func_, j_vars_, pipe_addr);
          auto j_dst_ptr = jit_insn_add_relative(j_func_, j_vars_, dst_addr);
          this->emit_memcpy(j_dst_ptr, j_pipe_ptr, ceildiv(dst_width, 8));

          // pipe <- next
          auto j_next_ptr = this->emit_pointer_address(node->next().impl());
          this->emit_memcpy(j_pipe_ptr, j_next_ptr, ceildiv(dst_width, 8));
        } else {
          // load pipe index
          auto pipe_index_addr = pipe_addr + __align_word_size(pipe_width);
          auto j_pipe_index = jit_insn_load_relative(j_func_, j_vars_, pipe_index_addr, jit_type_int32);
          auto j_pipe_ptr = jit_insn_add_relative(j_func_, j_vars_, pipe_addr);

          if (is_scalar) {
            // pop pipe data
            auto j_data = this->emit_load_array_scalar(j_pipe_ptr, pipe_width, j_pipe_index, dst_width);
            auto j_data_n = this->emit_cast(j_data, j_ntype);
            auto j_data_x = this->emit_cast(j_data_n, j_xtype);
            jit_insn_store_relative(j_func_, j_vars_, dst_addr, j_data_x);
            jit_insn_store(j_func_, j_dst, j_data_n);

            // push next data
            this->emit_store_array_scalar(j_pipe_ptr, pipe_width, j_pipe_index, j_next, dst_width);
          } else {
            // pop pipe data
            auto j_dst_ptr = jit_insn_add_relative(j_func_, j_vars_, dst_addr);
            this->emit_load_array_vector(j_dst_ptr, dst_width, j_pipe_ptr, j_pipe_index);

            // push next data
            auto j_next_ptr = this->emit_pointer_address(node->next().impl());
            this->emit_store_array_vector(j_pipe_ptr, j_pipe_index, j_next_ptr, dst_width);
          }

          // advance pipe index
          auto j_max = this->emit_constant(pipe_length - 1, jit_type_int32);
          auto j_one = this->emit_constant(1, jit_type_int32);
          auto j_sub = jit_insn_sub(j_func_, j_pipe_index, j_one);
          auto j_min = jit_insn_umin(j_func_, j_sub, j_max);
          jit_insn_store_relative(j_func_, j_vars_, pipe_index_addr, j_min);
        }
      }
    } else {
      if (is_scalar) {
        auto j_next_x = this->emit_cast(j_next, j_xtype);
        jit_insn_store_relative(j_func_, j_vars_, dst_addr, j_next_x);
        jit_insn_store(j_func_, j_dst, j_next);        
      } else {
        auto j_dst_ptr = jit_insn_add_relative(j_func_, j_vars_, dst_addr);
        auto j_next_ptr = this->emit_pointer_address(node->next().impl());
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
    auto j_array_ptr = this->emit_pointer_address(node->mem());
    auto array_width = node->mem()->size();

    if (is_scalar) {
      auto j_src = this->emit_load_array_scalar(j_array_ptr, array_width, j_src_addr, dst_width);
      scalar_map_[node->id()] = this->emit_cast(j_src, j_ntype);
    } else {
       auto j_dst_ptr = this->emit_pointer_address(node);
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

    auto j_src_addr = scalar_map_.at(node->addr().id());
  #ifndef NDEBUG
    this->emit_range_check(j_src_addr, 0, node->mem()->num_items());
  #endif
    auto j_array_ptr = this->emit_pointer_address(node->mem());
    auto array_width = node->mem()->size();

    if (is_scalar) {
      auto dst_addr = addr_map_.at(node->id());
      auto j_dst = scalar_map_.at(node->id());
      auto j_xtype = to_native_or_word_type(dst_width);
      auto j_ntype = to_native_type(dst_width);
      auto j_src = this->emit_load_array_scalar(j_array_ptr, array_width, j_src_addr, dst_width);      
      auto j_src_n = this->emit_cast(j_src, j_ntype);
      auto j_src_x = this->emit_cast(j_src_n, j_xtype);
      jit_insn_store_relative(j_func_, j_vars_, dst_addr, j_src_x);
      jit_insn_store(j_func_, j_dst, j_src_n);
    } else {
       auto j_dst_ptr = this->emit_pointer_address(node);
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
    auto j_array_ptr = this->emit_pointer_address(node->mem());
    auto array_width = node->mem()->size();

    if (is_scalar) {
      auto j_wdata = scalar_map_.at(node->wdata().id());
      this->emit_store_array_scalar(j_array_ptr, array_width, j_dst_addr, j_wdata, data_width);
    } else {
      auto j_wdata_ptr = this->emit_pointer_address(node->wdata().impl());
      this->emit_store_array_vector(j_array_ptr, j_dst_addr, j_wdata_ptr, data_width);
    }
  }

  void emit_node(timeimpl* node) {
    __source_info();

    auto dst_width = node->size();
    bool is_scalar = (dst_width <= WORD_SIZE);
    auto j_xtype = to_native_or_word_type(dst_width);

    auto addr = addr_map_.at(node->id());
    jit_value_t j_value;
    if (is_scalar) {
      j_value = scalar_map_.at(node->id());
    } else {
      j_value = jit_insn_load_relative(j_func_, j_vars_, addr, j_xtype);
    }
    auto j_one = this->emit_constant(1, j_xtype);
    auto j_incr = jit_insn_add(j_func_, j_value, j_one);
    auto j_incr_x = this->emit_cast(j_incr, j_xtype);
    jit_insn_store_relative(j_func_, j_vars_, addr, j_incr_x);
  }

  void emit_node(printimpl* node) {
    __source_info();

    jit_label_t l_exit(jit_label_undefined);

    auto predicated = node->has_pred();
    if (predicated) {
      auto j_pred = scalar_map_.at(node->pred().id());
      jit_insn_branch_if_not(j_func_, j_pred, &l_exit);
    }

    auto addr = addr_map_.at(node->id());
    auto j_data_ptr = jit_insn_add_relative(j_func_, j_vars_, addr);

    // copy scalar arguments
    uint32_t src_idx = 0;
    for (uint32_t i = (node->has_pred() ? 1 : 0), n = node->num_srcs(); i < n; ++i) {
      auto src = node->src(i).impl();
      auto it = scalar_map_.find(src->id());
      if (it != scalar_map_.end()
       && 0 == addr_map_.count(src->id())) {
        auto srcs_ptr = jit_insn_load_relative(j_func_,
                                               j_vars_,
                                               addr + offsetof(print_data_t, srcs),
                                               jit_type_ptr);
        auto j_src = this->emit_address_of(it->second, word_type_);
        jit_insn_store_relative(j_func_, srcs_ptr, src_idx * sizeof(sdata_type), j_src);
      }
      ++src_idx;
    }

    // call native function
    jit_type_t params[] = {jit_type_ptr};
    auto j_sig = jit_type_create_signature(jit_abi_cdecl,
                                           jit_type_void,
                                           params,
                                           __countof(params),
                                           1);
    jit_value_t args[] = {j_data_ptr};
    jit_insn_call_native(j_func_,
                         "print_data_eval",
                         (void*)print_data_eval,
                         j_sig,
                         args,
                         __countof(args),
                         JIT_CALL_NOTHROW);
    jit_type_free(j_sig);

    if (l_exit != jit_label_undefined) {
      jit_insn_label(j_func_, &l_exit);
    }
  }

  void emit_node(assertimpl* node) {
    __source_info();

    jit_label_t l_exit(jit_label_undefined);

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
    if (it != scalar_map_.end()
     && 0 == addr_map_.count(node->time().id())) {
      auto time_ptr = jit_insn_load_relative(j_func_,
                                             j_vars_,
                                             addr + offsetof(assert_data_t, time),
                                             jit_type_ptr);
      auto j_time = this->emit_address_of(it->second, word_type_);
      jit_insn_store_relative(j_func_, time_ptr, 0, j_time);
    }

    // call native function
    jit_type_t params[] = {jit_type_ptr};
    auto j_sig = jit_type_create_signature(jit_abi_cdecl,
                                           jit_type_void,
                                           params,
                                           __countof(params),
                                           1);
    jit_value_t args[] = {j_data_ptr};
    jit_insn_call_native(j_func_,
                         "assert_data_eval",
                         (void*)assert_data_eval,
                         j_sig,
                         args,
                         __countof(args),
                         JIT_CALL_NOTHROW);
    jit_type_free(j_sig);

    if (l_exit != jit_label_undefined) {
      jit_insn_label(j_func_, &l_exit);
    }
  }

  void emit_node(udfimpl* node) {
    __source_info();

    auto addr = addr_map_.at(node->id());
    auto j_data_ptr = jit_insn_add_relative(j_func_, j_vars_, addr);

    // call native function
    jit_type_t params[] = {jit_type_ptr};
    auto j_sig = jit_type_create_signature(jit_abi_cdecl,
                                           jit_type_void,
                                           params,
                                           __countof(params),
                                           1);
    jit_value_t args[] = {j_data_ptr};
    jit_insn_call_native(j_func_,
                         "udf_data_eval",
                         (void*)udf_data_eval,
                         j_sig,
                         args,
                         __countof(args),
                         JIT_CALL_NOTHROW);
    jit_type_free(j_sig);
  }

  void emit_node(udfsimpl* node) {
    sblock_.cd = node->cd().impl();
    sblock_.reset = get_snode_reset(node);
    sblock_.nodes.push_back(node);
  }

  void emit_snode_value(udfimpl* node) {
    emit_node(node);
  }

  void emit_snode_init(udfimpl* node) {
    __source_info();

    auto addr = addr_map_.at(node->id());
    auto j_data_ptr = jit_insn_add_relative(j_func_, j_vars_, addr);

    // call native function
    jit_type_t params[] = {jit_type_ptr};
    auto j_sig = jit_type_create_signature(jit_abi_cdecl,
                                           jit_type_void,
                                           params,
                                           __countof(params),
                                           1);
    jit_value_t args[] = {j_data_ptr};
    jit_insn_call_native(j_func_,
                         "udf_data_reset",
                         (void*)udf_data_reset,
                         j_sig,
                         args,
                         __countof(args),
                         JIT_CALL_NOTHROW);
    jit_type_free(j_sig);
  }

  /////////////////////////////////////////////////////////////////////////////

  void allocate_nodes(const std::vector<lnodeimpl*>& eval_list) {
    std::vector<const_alloc_t> constants;
    uint32_t consts_size = 0;
    uint32_t var_addr = 0;    
    uint32_t port_addr = 0;

    for (auto node : eval_list) {
      auto dst_width = node->size();
      auto type = node->type();
      switch (type) {
      case type_lit: {
        auto lit =  reinterpret_cast<litimpl*>(node);
        consts_size += alloc_constant(lit, constants);
      } break;
      case type_input:
      case type_output:
      case type_tap:
      case type_udfin:
      case type_udfout:
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
          auto pipe_width = (reg->length() - 1) * reg->size();
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
        auto u = reinterpret_cast<udfimpl*>(node);
        var_addr += __align_word_size(udf_data_t::size(u) * 8);
      } break;      
      case type_op:
      case type_sel:
      case type_proxy:
      case type_marport:
      case type_mwport:
        // only allocate nodes with size bigger than WORD_SIZE bits
        if (dst_width > WORD_SIZE) {
          addr_map_[node->id()] = var_addr;
          var_addr += __align_word_size(dst_width);
        }
        break;
      default:
        std::abort();
      }
    }

    auto vars_size = var_addr + consts_size;
    if (vars_size) {
      sim_ctx_->state.vars = new uint8_t[vars_size];
      vars_size_= vars_size;
      if (consts_size) {
        this->init_constants(constants, var_addr, consts_size);
      }
    }

    if (port_addr) {
      sim_ctx_->state.ports = new block_type*[port_addr];
      ports_size_ = port_addr;
    }

  #ifndef NDEBUG
    sim_ctx_->state.dbg = new char[4096];
  #endif

    this->init_variables(eval_list);
  }

  uint32_t alloc_constant(litimpl* lit, std::vector<const_alloc_t>& constants) {
    auto dst_width = lit->size();
    if (dst_width <= WORD_SIZE)
      return 0;

    uint32_t total_words = 0;
    auto num_words = ceildiv(dst_width, WORD_SIZE);
    bool found = false;

    // allocate literals with size bigger than WORD_SIZE bits
    for (auto& constant : constants) {
      if (constant.size >= num_words) {
        auto width = num_words * WORD_SIZE;
        if (bv_eq<false, block_type, ClearBitAccessor<block_type>>(
              constant.data, width, lit->value().words(), width)) {
          constant.nodes.push_back(lit->id());
          found = true;
          break;
        }
      } else {
        uint32_t width = constant.size * WORD_SIZE;
        if (bv_eq<false, block_type, ClearBitAccessor<block_type>>(
              constant.data, width, lit->value().words(), width)) {
          auto buf = reinterpret_cast<block_type*>(
                std::realloc(constant.data, num_words * sizeof(block_type)));
          std::copy_n(lit->value().words(), num_words, buf);
          total_words += (num_words - constant.size);
          constant.data = buf;
          constant.size = num_words;
          constant.nodes.push_back(lit->id());
          found = true;
          break;
        }
      }
    }

    if (!found) {
      auto buf = reinterpret_cast<block_type*>(std::malloc(num_words * sizeof(block_type)));
      std::copy_n(lit->value().words(), num_words, buf);
      constants.emplace_back(buf, num_words, lit->id());
      total_words += num_words;
    }

    return total_words * sizeof(block_type);
  }

  void init_variables(const std::vector<lnodeimpl*>& eval_list) {
    for (auto node : eval_list) {
      auto dst_width = node->size();
      auto j_xtype = to_native_or_word_type(dst_width);
      auto j_ntype = to_native_type(dst_width);
      auto type = node->type();

      switch (type) {
      case type_lit:
        if (dst_width > WORD_SIZE) {
          this->calc_pointer_address(node);
        }
        break;
      case type_input:
      case type_output:
      case type_tap:
      case type_udfin:
      case type_udfout: {
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
          __source_info();
          // preload scalar value
          auto j_var = jit_value_create(j_func_, j_ntype);
          auto addr = addr_map_.at(node->id());
          auto j_dst = jit_insn_load_relative(j_func_, j_vars_, addr, j_xtype);
          auto j_dst_n = this->emit_cast(j_dst, j_ntype);
          jit_insn_store(j_func_, j_var, j_dst_n);
          scalar_map_[node->id()] = j_var;
        }
        this->calc_pointer_address(node);
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
        this->calc_pointer_address(node);
      } break;
      case type_msrport: {
        auto addr = addr_map_.at(node->id());
        bv_init(reinterpret_cast<block_type*>(sim_ctx_->state.vars + addr), dst_width);
        if (dst_width <= WORD_SIZE) {
          __source_info();
          // preload scalar value
          auto j_var = jit_value_create(j_func_, j_ntype);
          auto j_dst = jit_insn_load_relative(j_func_, j_vars_, addr, j_xtype);
          auto j_dst_n = this->emit_cast(j_dst, j_ntype);
          jit_insn_store(j_func_, j_var, j_dst_n);
          scalar_map_[node->id()] = j_var;
        }
        this->calc_pointer_address(node);
      } break;
      case type_time: {
        auto addr = addr_map_.at(node->id());
        bv_reset(reinterpret_cast<block_type*>(sim_ctx_->state.vars + addr), dst_width);        
        if (dst_width <= WORD_SIZE) {
          __source_info();
          // preload scalar value
          auto j_dst = jit_insn_load_relative(j_func_, j_vars_, addr, j_xtype);
          scalar_map_[node->id()] = j_dst;
        }
        this->calc_pointer_address(node);
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
        auto u = reinterpret_cast<udfimpl*>(node);
        reinterpret_cast<udf_data_t*>(sim_ctx_->state.vars + addr)->init(u);
      } break;
      case type_op:
      case type_sel:
      case type_proxy:
      case type_marport:
      case type_mwport:
        if (dst_width > WORD_SIZE) {
          auto addr = addr_map_.at(node->id());
          bv_init(reinterpret_cast<block_type*>(sim_ctx_->state.vars + addr), dst_width);
          this->calc_pointer_address(node);
        }
        break;
      default:
        std::abort();
      }
    }
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
      j_ret = __op_call_relational(bv_eq_vector, j_lhs, lhs_size, j_rhs, rhs_size);
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
      auto j_shift = this->emit_constant(i, jit_type_int32);
      auto j_tmp = jit_insn_ushr(j_func_, j_ret, j_shift);
      j_ret = jit_insn_xor(j_func_, j_ret, j_tmp);
    }
    auto j_one = this->emit_constant(1, jit_type_int32);
    return jit_insn_and(j_func_, j_ret, j_one);
  }

  jit_value_t emit_scalar_slice(jit_value_t j_value,
                                uint32_t offset,
                                uint32_t length) {
    __source_info();
    assert(length <= WORD_SIZE);
    assert(offset < WORD_SIZE);

    jit_value_t j_src = j_value;
    if (offset) {
      auto j_offset = this->emit_constant(offset, jit_type_int32);
      j_src = jit_insn_ushr(j_func_, j_value, j_offset);
    }
    int clamp = get_value_size(j_src) - length;
    if (clamp) {
      assert(clamp > 0);
      auto j_vtype = jit_value_get_type(j_src);
      auto mask = std::numeric_limits<uint64_t>::max() >> (64 - length);
      auto j_mask = this->emit_constant(mask, j_vtype);
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
      auto j_vtype = to_value_type(src_end8);
      auto j_src_value = jit_insn_load_relative(j_func_, src_ptr.base, src_ptr.offset + (offset / 8), j_vtype);
      return this->emit_scalar_slice(j_src_value, src_lsb8, length);
    } else {
      auto src_idx = offset / WORD_SIZE;
      auto src_lsb = offset % WORD_SIZE;
      auto j_xtype = to_native_or_word_type(length);
      auto j_src_lsb = this->emit_constant(src_lsb, jit_type_int32);
      auto j_src_value0 = jit_insn_load_relative(j_func_, src_ptr.base, src_ptr.offset + src_idx * sizeof(block_type), j_xtype);
      auto j_src_value0_s = jit_insn_ushr(j_func_, j_src_value0, j_src_lsb);
      auto j_src_value1 = jit_insn_load_relative(j_func_, src_ptr.base, src_ptr.offset + (src_idx + 1) * sizeof(block_type), j_xtype);
      auto j_rem = this->emit_constant(get_value_size(j_src_value1) - src_lsb, jit_type_int32);
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

    auto src_width = node->size();
    if (src_width <= WORD_SIZE) {
      auto j_src_value = scalar_map_.at(node->id());
      if (src_width != length) {
        return this->emit_scalar_slice(j_src_value, offset, length);
      } else {
        return j_src_value;
      }
    } else {
      auto src_ptr = this->get_pointer_address(node);
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
    if (0 == (length % 8)
     && (is_value_size(length)
      || array_width > WORD_SIZE)) {
      if (is_value_size(length)) {
        auto j_vtype = to_value_type(length);
        j_src = jit_insn_load_elem(j_func_, j_array_ptr, j_index, j_vtype);
      } else {
        assert(array_width > WORD_SIZE);
        auto j_xtype = to_native_or_word_type(length);
        auto xsize = to_native_or_word_size(length);
        auto j_ovf = this->emit_constant(xsize - length, jit_type_int32);
        auto j_ovf_b = this->emit_constant((xsize - length) / 8, jit_type_int32);
        auto j_data_size = this->emit_constant(length / 8, jit_type_int32);
        auto j_offset = jit_insn_mul(j_func_, j_index, j_data_size);
        auto j_offset_d = jit_insn_sub(j_func_, j_offset, j_ovf_b);
        auto j_addr = jit_insn_load_elem_address(j_func_, j_array_ptr, j_offset_d, jit_type_int8);
        auto j_tmp = jit_insn_load_relative(j_func_, j_addr, 0, j_xtype);
        j_src = jit_insn_ushr(j_func_, j_tmp, j_ovf);
      }
    } else {
      auto j_data_width = this->emit_constant(length, jit_type_int32);
      auto j_src_offset = jit_insn_mul(j_func_, j_index, j_data_width);
      if (array_width <= WORD_SIZE) {
        auto j_xtype = to_native_or_word_type(array_width);
        auto j_value = jit_insn_load_relative(j_func_, j_array_ptr, 0, j_xtype);
        j_src = jit_insn_ushr(j_func_, j_value, j_src_offset);
      } else {
        auto j_xtype = to_native_or_word_type(length);
        auto xsize = to_native_or_word_size(length);
        auto j_block_logsize = this->emit_constant(log2floor(xsize), jit_type_int32);
        auto j_block_mask = this->emit_constant(xsize - 1, jit_type_int32);
        auto j_src_idx = jit_insn_ushr(j_func_, j_src_offset, j_block_logsize);
        auto j_src_lsb = jit_insn_and(j_func_, j_src_offset, j_block_mask);

        auto j_src_ptr = jit_insn_load_elem_address(j_func_, j_array_ptr, j_src_idx, j_xtype);
        auto j_src_value0 = jit_insn_load_relative(j_func_, j_src_ptr, 0, j_xtype);

        auto j_src_0 = jit_insn_ushr(j_func_, j_src_value0, j_src_lsb);
        j_src = jit_value_create(j_func_, j_xtype);
        jit_insn_store(j_func_, j_src, j_src_0);

        jit_label_t l_skip(jit_label_undefined);
        auto j_src_rem = this->emit_constant(xsize - length, jit_type_int32);
        auto j_src_inclusive = jit_insn_ule(j_func_, j_src_lsb, j_src_rem);
        jit_insn_branch_if(j_func_, j_src_inclusive, &l_skip);

        auto j_src_value1 = jit_insn_load_relative(j_func_, j_src_ptr, sizeof(block_type), j_xtype);
        auto j_block_size = this->emit_constant(xsize, jit_type_int32);
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

    if (0 == (length % 8)
     && (is_value_size(length)
      || array_width > WORD_SIZE)) {
      if (is_value_size(length)) {
        auto j_vtype = to_value_type(length);
        auto j_data_v = this->emit_cast(j_data, j_vtype);
        jit_insn_store_elem(j_func_, j_array_ptr, j_index, j_data_v);
      } else {
        assert(array_width > WORD_SIZE);
        auto j_xtype = to_native_or_word_type(length);
        auto xsize = to_native_or_word_size(length);
        auto mask = std::numeric_limits<uint64_t>::max() >> (64 - length);
        auto j_mask = this->emit_constant(mask << (xsize - length), j_xtype);
        auto j_ovf = this->emit_constant(xsize - length, jit_type_int32);
        auto j_ovf_b = this->emit_constant((xsize - length) / 8, jit_type_int32);
        auto j_data_size = this->emit_constant(length / 8, jit_type_int32);
        auto j_offset = jit_insn_mul(j_func_, j_index, j_data_size);
        auto j_offset_d = jit_insn_sub(j_func_, j_offset, j_ovf_b);
        auto j_addr = jit_insn_load_elem_address(j_func_, j_array_ptr, j_offset_d, jit_type_int8);
        auto j_dst = jit_insn_load_relative(j_func_, j_addr, 0, j_xtype);
        auto j_data_s = jit_insn_shl(j_func_, j_data, j_ovf);
        auto j_dst_new = this->emit_blend(j_mask, j_dst, j_data_s);
        auto j_dst_new_x = this->emit_cast(j_dst_new, j_xtype);
        jit_insn_store_relative(j_func_, j_addr, 0, j_dst_new_x);
      }
    } else {
      auto j_data_width = this->emit_constant(length, jit_type_int32);
      auto j_dst_offset = jit_insn_mul(j_func_, j_index, j_data_width);

      if (array_width <= WORD_SIZE) {
        auto j_xtype = to_native_or_word_type(array_width);
        auto mask = std::numeric_limits<uint64_t>::max() >> (64 - length);
        auto j_mask = this->emit_constant(mask, j_xtype);
        auto j_dst = jit_insn_load_relative(j_func_, j_array_ptr, 0, j_xtype);
        auto j_mask_s = jit_insn_shl(j_func_, j_mask, j_dst_offset);
        auto j_data_n = this->emit_cast(j_data, j_xtype);
        auto j_data_s = jit_insn_shl(j_func_, j_data_n, j_dst_offset);
        auto j_dst_new = this->emit_blend(j_mask_s, j_dst, j_data_s);
        auto j_dst_new_x = this->emit_cast(j_dst_new, j_xtype);
        jit_insn_store_relative(j_func_, j_array_ptr, 0, j_dst_new_x);
      } else {
        auto j_xtype = to_native_or_word_type(length);
        auto xsize = to_native_or_word_size(length);
        auto j_block_logsize = this->emit_constant(log2floor(xsize), jit_type_int32);
        auto j_block_mask = this->emit_constant(xsize - 1, jit_type_int32);
        auto mask = std::numeric_limits<uint64_t>::max() >> (64 - length);
        auto j_mask = this->emit_constant(mask, j_xtype);
        auto j_data_w = this->emit_cast(j_data, j_xtype);
        auto j_dst_idx = jit_insn_ushr(j_func_, j_dst_offset, j_block_logsize);
        auto j_dst_lsb = jit_insn_and(j_func_, j_dst_offset, j_block_mask);

        auto j_dst_ptr = jit_insn_load_elem_address(j_func_, j_array_ptr, j_dst_idx, j_xtype);
        auto j_dst_value0 = jit_insn_load_relative(j_func_, j_dst_ptr, 0, j_xtype);
        auto j_mask0_s = jit_insn_shl(j_func_, j_mask, j_dst_lsb);
        auto j_data0_s = jit_insn_shl(j_func_, j_data_w, j_dst_lsb);
        auto j_dst0 = this->emit_blend(j_mask0_s, j_dst_value0, j_data0_s);
        auto j_dst0_x = this->emit_cast(j_dst0, j_xtype);
        jit_insn_store_relative(j_func_, j_dst_ptr, 0, j_dst0_x);

        jit_label_t l_skip(jit_label_undefined);
        auto j_dst_rem = this->emit_constant(xsize - length, jit_type_int32);
        auto j_single_block = jit_insn_ule(j_func_, j_dst_lsb, j_dst_rem);

        jit_insn_branch_if(j_func_, j_single_block, &l_skip);
        auto j_dst_value1 = jit_insn_load_relative(j_func_, j_dst_ptr, sizeof(block_type), j_xtype);
        auto j_mask1 = jit_insn_not(j_func_, j_mask0_s);
        auto j_mask1_s = jit_insn_ushr(j_func_, j_mask1, j_dst_rem);
        auto j_data1_s = jit_insn_ushr(j_func_, j_data_w, j_dst_rem);
        auto j_dst1 = this->emit_blend(j_mask1_s, j_dst_value1, j_data1_s);
        auto j_dst1_x = this->emit_cast(j_dst1, j_xtype);
        jit_insn_store_relative(j_func_, j_dst_ptr, sizeof(block_type), j_dst1_x);

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
      auto j_size = this->emit_constant(dst_width / 8, jit_type_int32);
      auto j_src_offset = jit_insn_mul(j_func_, j_index, j_size);
      auto j_src_ptr = jit_insn_load_elem_address(j_func_, j_array_ptr, j_src_offset, jit_type_int8);
      this->emit_memcpy(j_dst_ptr, j_src_ptr, dst_width / 8);
    } else {
      auto j_src_width = this->emit_constant(dst_width, jit_type_int32);
      auto j_src_offset = jit_insn_mul(j_func_, j_index, j_src_width);
      auto j_zero = this->emit_constant(0, jit_type_int32);
      this->emit_copy_vector(j_dst_ptr, j_zero, j_array_ptr, j_src_offset, dst_width);
    }
  }

  void emit_store_array_vector(jit_value_t j_array_ptr,
                               jit_value_t j_index,
                               jit_value_t j_src_ptr,
                               uint32_t src_width) {
    __source_info();

    if (0 == (src_width % 8)) {
      auto j_size = this->emit_constant(src_width / 8, jit_type_int32);
      auto j_dst_offset = jit_insn_mul(j_func_, j_index, j_size);
      auto j_dst_ptr = jit_insn_load_elem_address(j_func_, j_array_ptr, j_dst_offset, jit_type_int8);
      this->emit_memcpy(j_dst_ptr, j_src_ptr, src_width / 8);
    } else {
      auto j_dst_width = this->emit_constant(src_width, jit_type_int32);
      auto j_dst_offset = jit_insn_mul(j_func_, j_index, j_dst_width);
      auto j_zero = this->emit_constant(0, jit_type_int32);
      this->emit_copy_vector(j_array_ptr, j_dst_offset, j_src_ptr, j_zero, src_width);
    }
  }

  void emit_copy_scalar(jit_value_t j_dst_ptr,
                        uint32_t dst_offset,
                        jit_value_t j_src,
                        uint32_t src_offset,
                        uint32_t length) {
    __source_info();
    assert(length <= WORD_SIZE);

    auto j_xtype = to_native_or_word_type(length);
    auto j_ntype = to_native_type(length);

    auto w_dst_idx = dst_offset / WORD_SIZE;
    auto w_dst_lsb = dst_offset % WORD_SIZE;

    block_type mask0 = (WORD_MAX >> (WORD_SIZE - length)) << w_dst_lsb;
    block_type mask1 = block_type(~mask0) >> (WORD_SIZE - length);

    auto j_src_offset = this->emit_constant(src_offset, jit_type_int32);
    auto j_dst_lsb = this->emit_constant(w_dst_lsb, jit_type_int32);
    auto j_src_s = jit_insn_ushr(j_func_, j_src, j_src_offset);
    auto j_src_n = this->emit_cast(j_src_s, j_ntype);
    auto j_src_0 = jit_insn_shl(j_func_, j_src_n, j_dst_lsb);
    auto j_dst_0 = jit_insn_load_relative(j_func_, j_dst_ptr, w_dst_idx * sizeof(block_type), j_xtype);
    auto j_mask0 = this->emit_constant(mask0, j_ntype);
    auto j_blend0 = this->emit_blend(j_mask0, j_dst_0, j_src_0);
    auto j_blend0_x = this->emit_cast(j_blend0, j_xtype);
    jit_insn_store_relative(j_func_, j_dst_ptr, w_dst_idx * sizeof(block_type), j_blend0_x);
    if (w_dst_lsb > (WORD_SIZE - length)) {
      auto j_dst_1 = jit_insn_load_relative(j_func_, j_dst_ptr, (w_dst_idx + 1) * sizeof(block_type), j_xtype);
      auto j_rem = this->emit_constant(WORD_SIZE - w_dst_lsb, jit_type_int32);
      auto j_src_1 = jit_insn_ushr(j_func_, j_src_n, j_rem);
      auto j_mask1 = this->emit_constant(mask1, j_ntype);
      auto j_blend1 = this->emit_blend(j_mask1, j_dst_1, j_src_1);
      auto j_blend1_x = this->emit_cast(j_blend1, j_xtype);
      jit_insn_store_relative(j_func_, j_dst_ptr, (w_dst_idx + 1) * sizeof(block_type), j_blend1_x);
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
      auto rem = length % 8;
      if (rem) {
        auto offset = length / 8;
        auto j_src_value = jit_insn_load_relative(j_func_, j_src_ptr8, offset, jit_type_int8);
        auto j_dst_value = jit_insn_load_relative(j_func_, j_dst_ptr8, offset, jit_type_int8);
        auto j_mask = this->emit_constant(0xff << rem, jit_type_int32);
        auto j_dst = this->emit_blend(j_mask, j_src_value, j_dst_value);
        auto j_dst_b = this->emit_cast(j_dst, jit_type_int8);
        jit_insn_store_relative(j_func_, j_dst_ptr8, offset, j_dst_b);
      }
    } else {
      auto j_dst_offset = this->emit_constant(dst_offset, jit_type_int32);
      auto j_src_offset = this->emit_constant(src_offset, jit_type_int32);
      this->emit_copy_vector(j_dst_ptr, j_dst_offset, j_src_ptr, j_src_offset, length);
    }
  }

  void emit_copy_vector(jit_value_t j_dst_ptr,
                        jit_value_t j_dst_offset,
                        jit_value_t j_src_ptr,
                        jit_value_t j_src_offset,
                        uint32_t length) {
    __source_info();

    auto j_length = this->emit_constant(length, jit_type_int32);

    // call native function
    jit_type_t params[] = {jit_type_ptr, jit_type_int32, jit_type_ptr, jit_type_int32, jit_type_int32};
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
    jit_type_free(j_sig);
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
      auto j_rem = this->emit_constant(WORD_SIZE - dst_lsb, jit_type_int32);
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
        auto j_dst_offset = this->emit_constant(dst_addr.offset * 8 + dst_offset, jit_type_int32);
        auto j_src_offset = this->emit_constant(src_addr.offset * 8 + src_offset, jit_type_int32);
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

    auto j_dst_lsb = this->emit_constant(dst_offset, jit_type_int32);
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

    auto dst_width = node->size();
    assert(dst_width <= WORD_SIZE);
    auto native_size = to_native_size(dst_width);
    auto rem = dst_width % native_size;
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

  memaddr_t get_pointer_address(lnodeimpl* node) {
    switch (node->type()) {
    case type_input:
      return memaddr_t{input_map_.at(node->id()), 0};
    default:
      return memaddr_t{j_vars_, addr_map_.at(node->id())};
    }
  }

  void calc_pointer_address(lnodeimpl* node) {
    auto maddr = this->get_pointer_address(node);
    if (0 == maddr.offset)
      return;

    auto j_dst = jit_insn_add_relative(j_func_, maddr.base, maddr.offset);
    pointer_map_[node->id()] = j_dst;
  }

  jit_value_t emit_pointer_address(lnodeimpl* node) {
    auto maddr = this->get_pointer_address(node);
    if (0 == maddr.offset)
      return maddr.base;

    auto it = pointer_map_.find(node->id());
    if (it != pointer_map_.end())
      return it->second;

    return jit_insn_add_relative(j_func_, maddr.base, maddr.offset);
  }

  jit_value_t emit_load_scalar_relative(lnodeimpl* node, uint32_t offset, jit_type_t j_type) {
    auto maddr = this->get_pointer_address(node);
    return jit_insn_load_relative(j_func_, maddr.base, maddr.offset + offset, j_type);
  }

  jit_value_t emit_load_scalar_elem(lnodeimpl* node, uint32_t index, jit_type_t j_type) {
    auto nbytes = jit_type_get_size(j_type);
    return this->emit_load_scalar_relative(node, index * nbytes, j_type);
  }

  void emit_memcpy(jit_value_t j_dst_ptr, jit_value_t j_src_ptr, uint32_t length) {
    auto j_length = this->emit_constant(length, jit_type_int32);
    jit_insn_memcpy(j_func_, j_dst_ptr, j_src_ptr, j_length);
  }

  jit_value_t emit_sign_ext(jit_value_t j_value, uint32_t width) {
    auto j_type = jit_value_get_type(j_value);
    auto value_size = get_type_size(j_type);
    assert(value_size >= width);
    if (value_size == width)
      return j_value;
    if (is_value_size(width)) {
      auto j_otype = to_value_type(width);
      auto j_tmp = jit_insn_convert(j_func_, j_value, j_otype, 0);
      return jit_insn_sext(j_func_, j_tmp, j_type);
    }
    auto j_mask = this->emit_constant(1ull << (width - 1), j_type);
    auto j_tmp1 = jit_insn_xor(j_func_, j_value, j_mask);
    return jit_insn_sub(j_func_, j_tmp1, j_mask);
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
    return jit_insn_convert(j_func_, j_value, to_type, 0);
  }

  void emit_range_check(jit_value_t j_value, uint32_t start, uint32_t end) {
    auto j_start = this->emit_constant(start, jit_type_int32);
    auto j_end = this->emit_constant(end, jit_type_int32);
    auto j_one = this->emit_constant(1, jit_type_int32);
    auto j_check1 = jit_insn_uge(j_func_, j_value, j_start);
    auto j_check2 = jit_insn_ult(j_func_, j_value, j_end);
    auto j_check = jit_insn_and(j_func_, j_check1, j_check2);
    jit_label_t l_skip(jit_label_undefined);
    jit_insn_branch_if(j_func_, j_check, &l_skip);
    jit_insn_return(j_func_, j_one);
    jit_insn_label(j_func_, &l_skip);
  }

  jit_value_t emit_constant(long value, jit_type_t j_type) {
    return jit_value_create_int_constant(j_func_, value, j_type);
  }

  long get_constant_value(jit_value_t j_value) {
    assert(jit_value_is_constant(j_value));
    return jit_value_get_int_constant(j_value);
  }

#ifndef NDEBUG
  void emit_watch(jit_value_t j_value, const char* name) {
    // setup arguments
    auto j_arg0 = this->emit_cast(j_value, jit_type_int64);

    auto name_len = strlen(name) + 1;
    memcpy(sim_ctx_->state.dbg + dbg_off_, name, name_len);
    auto j_arg1 = jit_insn_add_relative(j_func_, j_dbg_, dbg_off_);
    dbg_off_ += name_len;

    // call native function
    jit_type_t params[] = {jit_type_int64, jit_type_ptr};
    auto j_sig = jit_type_create_signature(jit_abi_cdecl,
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
    jit_type_free(j_sig);
  }
#endif

public:

  Compiler(sim_ctx_t* ctx)
    : sim_ctx_(ctx)
    , l_bypass_(jit_label_undefined)
    , bypass_enable_(false)
    , word_type_(to_value_type(WORD_SIZE))
    , vars_size_(0)
    , ports_size_(0)
  #ifndef NDEBUG
    , dbg_off_(0)
  #endif
  {}

  ~Compiler() {}

  void build(const std::vector<lnodeimpl*>& eval_list) {
    // begin build
    jit_context_build_start(sim_ctx_->j_ctx);

    // create JIT function
    this->create_function();

    // allocate objects
    this->allocate_nodes(eval_list);

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
      case type_udfout:
        this->emit_node_input(reinterpret_cast<ioportimpl*>(node));
        break;
      case type_output:
      case type_tap:
      case type_udfin:
        this->emit_node_output(reinterpret_cast<ioportimpl*>(node));
        break;
      case type_op:
        this->emit_node(reinterpret_cast<opimpl*>(node));
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
      default:
        std::abort();
      case type_mem:
        break;
      }
    }

    // create bypass label
    this->resolve_branch(nullptr);

    // return 0
    auto j_zero = this->emit_constant(0, jit_type_int32);
    jit_insn_return(j_func_, j_zero);

    // dump JIT assembly code
    if (platform::self().cflags() & cflags::dump_jit) {
      auto file = fopen("simjit.ast", "w");
      jit_dump_ast(file, j_func_, "simjit");
      fclose(file);
    }

    // compile function
    if (!jit_function_compile(j_func_))
      exit(1);

    // end build
    jit_context_build_end(sim_ctx_->j_ctx);

    // dump JIT assembly code
    if (platform::self().cflags() & cflags::dump_asm) {
      auto file = fopen("simjit.asm", "w");
      jit_dump_asm(file, j_func_, "simjit");
      fclose(file);
    }

  #ifdef JIT_BACKEND_INTERP
    sim_ctx_->j_func = j_func_;
  #else
    // get closure
    sim_ctx_->entry = reinterpret_cast<pfn_entry>(jit_function_to_closure(j_func_));
  #endif
  }
};

///////////////////////////////////////////////////////////////////////////////

void init_sdata(const Compiler* Cp, sdata_type* data, lnodeimpl* node) {
  block_type* value = nullptr;
  auto it = Cp->addr_map_.find(node->id());
  if (it != Cp->addr_map_.end()) {
    auto addr = it->second;
    switch (node->type()) {
    case type_input:
    case type_udfout:
      assert(addr < Cp->ports_size_);
      value = Cp->sim_ctx_->state.ports[addr];
      break;
    default:
      assert(addr < Cp->vars_size_);
      value = reinterpret_cast<block_type*>(Cp->sim_ctx_->state.vars + addr);
      break;
    }
  }
  data->emplace(value, node->size());
}

///////////////////////////////////////////////////////////////////////////////

driver::driver() {
  sim_ctx_ = new sim_ctx_t();
}

driver::~driver() {
  delete sim_ctx_;
}

void driver::initialize(const std::vector<lnodeimpl*>& eval_list) {
  Compiler compiler(sim_ctx_);
  compiler.build(eval_list);
}

void driver::eval() {
  int ret;
#ifdef JIT_BACKEND_INTERP
  void* arg = &sim_ctx_->state;
  void* args[1] = {&arg};
  jit_int j_ret;
  jit_function_apply(sim_ctx_->j_func, args, &j_ret);
  ret = static_cast<int>(j_ret);
#else
  ret = (sim_ctx_->entry)(&sim_ctx_->state);
#endif
  if (ret) {
    error_handler(ret);
  }
}

}

#endif
