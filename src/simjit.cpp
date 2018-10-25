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

namespace ch::internal::simjit {

using alloc_map_t = std::unordered_map<uint32_t, uint32_t>;
using var_map_t   = std::unordered_map<uint32_t, jit_value_t>;
using label_map_t = std::unordered_map<uint32_t, jit_label_t>;

#define __align_block(...) ((((__VA_ARGS__) + bitwidth_v<block_type> - 1) / bitwidth_v<block_type>) * sizeof(block_type))

struct sim_state_t {
  block_type*  consts;
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
    delete [] state.consts;
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

  compiler(sim_ctx_t* ctx) : sim_ctx_(ctx) {}

  ~compiler() {}

  void build(const std::vector<lnodeimpl*>& eval_list) {
    //--
    auto ctx = eval_list.back()->ctx();

    // begin build
    jit_context_build_start(sim_ctx_->jit);

    // create JIT function
    this->create_function();

    // allocate memory objects
    this->alloc_constants(ctx);
    this->alloc_variables(ctx);

    // create input nodes
    this->create_inputs(ctx);

    // lower all nodes
    for (auto node : eval_list) {
      switch (node->type()) {
      case type_proxy:
        this->create_node(reinterpret_cast<proxyimpl*>(node));
        break;
      case type_alu:
        this->create_node(reinterpret_cast<aluimpl*>(node));
        break;
      case type_sel:
        break;
      case type_cd:
        break;
      case type_reg:
        break;
      case type_marport:
        break;
      case type_msrport:
        break;
      case type_mwport:
        break;
      case type_assert:
        break;
      case type_time:
        break;
      case type_print:
        break;
      case type_udfc:
        break;
      case type_udfs:
        break;
      default:
        break;
      }
    }

    // create output nodes
    this->create_outputs(ctx);

    // compile function
    jit_function_compile(jf_);

    // end build
    jit_context_build_end(sim_ctx_->jit);

    // dump JIT assembly code
    jit_dump_function(stdout, jf_, "simjit");

    // get closure
    sim_ctx_->entry = reinterpret_cast<pfn_entry>(jit_function_to_closure(jf_));
  }

private:

  struct const_alloc_t {
    const_alloc_t(block_type* data, uint32_t size)
      : data(data)
      , size(size)
    {}

    block_type* data;
    uint32_t    size;
    std::vector<uint32_t> nodes;
  };

  struct proxy_range_t {
    union {
      uint64_t    var_data;
      block_type* ptr_data;
    };
    uint32_t length;
    uint8_t  dst_offset;
    uint8_t  src_offset;
    bool     is_scalar;
  };

  void create_function() {
    jit_type_t params[1] = {jit_type_void_ptr};
    auto sig = jit_type_create_signature(jit_abi_cdecl, jit_type_void, params, 1, 1);
    jf_ = jit_function_create(sim_ctx_->jit, sig);
    auto j_state = jit_value_get_param(jf_, 0);
    j_vars_    = jit_insn_load_relative(jf_, j_state, offsetof(sim_state_t, vars), jit_type_void_ptr);
    j_inputs_  = jit_insn_load_relative(jf_, j_state, offsetof(sim_state_t, inputs), jit_type_void_ptr);
    j_outputs_ = jit_insn_load_relative(jf_, j_state, offsetof(sim_state_t, outputs), jit_type_void_ptr);
  }

  void create_node(proxyimpl* node) {
    this->create_node_label(node);
    bool is_scalar = (node->size() <= 64);
    if (is_scalar) {
      // inline code
      auto j_dst = jit_value_create(jf_, jit_type_ulong);
      var_map_[node->id()] = j_dst;
      for (uint i = 0, n = node->ranges().size(); i < n; ++i) {
        auto& range = node->range(i);
        auto& src = node->src(range.src_idx);
        if (src.size() <= 64) {
          auto j_src_value = var_map_.at(src.id());
          auto j_src_offset = jit_value_create_nint_constant(jf_, jit_type_uint, range.src_offset);
          auto j_rem  = jit_value_create_nint_constant(jf_, jit_type_uint, 64 - node->size());
          auto j_tmp1 = jit_insn_ushr(jf_, j_src_value, j_src_offset);
          auto j_tmp2 = jit_insn_shl(jf_, j_tmp1, j_rem);
          auto j_tmp3 = jit_insn_ushr(jf_, j_tmp2, j_rem);
          if (0 == i) {
            jit_insn_store(jf_, j_dst, j_tmp3);
          } else {
            auto j_tmp4 = jit_insn_or(jf_, j_dst, j_tmp3);
            jit_insn_store(jf_, j_dst, j_tmp4);
          }
        } else {
          //--
          CH_TODO();
        }
      }
    } else {
      // function call
      CH_TODO();
    }
  }

  void create_node(aluimpl* node) {
    this->create_node_label(node);
    switch (node->op()) {
    case ch_op::add:
      if (node->size() <= 64) {
        auto j_src0 = var_map_.at(node->src(0).id());
        auto j_src1 = var_map_.at(node->src(1).id());
        auto j_tmp  = jit_insn_add(jf_, j_src0, j_src1);
        var_map_[node->id()] = j_tmp;
      } else {
        //--
        CH_TODO();
      }
      break;
    case ch_op::pad:
      if (node->size() <= 64) {
        if (node->is_signed()) {
          CH_TODO();
        } else {
          auto j_src = var_map_.at(node->src(0).id());
          var_map_[node->id()] = j_src;
        }
      } else {
        //--
        CH_TODO();
      }
      break;
    default:
      CH_TODO();
      break;
    }
  }

  void alloc_constants(context* ctx) {
    std::vector<const_alloc_t> constants;

    uint32_t total_words = 0;
    for (auto lit : ctx->literals()) {
      // only allocate literals with size bigger than 64 bits
      if (lit->size() <= 64)
        continue;
      auto num_words = ceildiv<uint32_t>(lit->size(), bitwidth_v<block_type>);
      bool found = false;
      for (auto& constant : constants) {
        if (constant.size >= num_words) {
          if (bv_eq(constant.data, lit->value().words(), num_words * bitwidth_v<block_type>)) {
            constant.nodes.push_back(lit->id());
            found = true;
            break;
          }
        } else
        if (bv_eq(constant.data, lit->value().words(), constant.size * bitwidth_v<block_type>)) {
          auto buf = reinterpret_cast<block_type*>(realloc(constant.data, num_words * sizeof(block_type)));
          std::copy_n(lit->value().words(), num_words, buf);
          total_words += (num_words - constant.size);
          constant.data = buf;
          constant.size = num_words;
          constant.nodes.push_back(lit->id());
          found = true;
          break;
        }
      }
      if (!found) {
        auto buf = reinterpret_cast<block_type*>(malloc(num_words * sizeof(block_type)));
        std::copy_n(lit->value().words(), num_words, buf);
        constants.emplace_back(buf, num_words);
        total_words += num_words;
      }
    }
    if (total_words) {
      auto buf = new block_type[total_words];
      sim_ctx_->state.consts = buf;

      uint32_t addr = 0;
      for (auto& constant : constants) {
        std::copy_n(constant.data, constant.size, buf);
        buf += constant.size;
        for (auto node_id : constant.nodes) {
          alloc_map_[node_id] = addr;
        }
        addr += constant.size * sizeof(block_type);
      }
      assert(addr == total_words * sizeof(block_type));
    }
  }

  void alloc_variables(context* ctx) {
    uint32_t addr = 0;

    for (auto node : ctx->nodes()) {
      auto type = node->type();
      if (type_reg == type
       || type_mem == type
       || type_udfs == type
       || type_lit == type)
        continue;
      // only allocate nodes with size bigger than 64 bits
      if (node->size() <= 64)
        continue;
      alloc_map_[node->id()] = addr;
      addr += __align_block(node->size());
      addr += this->alloc_call_params(node);
    }

    for (auto node : ctx->regs()) {
      alloc_map_[node->id()] = addr;
      addr += __align_block(node->size());
    }

    for (auto node : ctx->mems()) {
      alloc_map_[node->id()] = addr;
      addr += __align_block(node->size());
    }

    for (auto node : ctx->udfs()) {
      if (type_udfs != node->type())
        continue;
      alloc_map_[node->id()] = addr;
      addr += __align_block(node->size());
    }

    if (addr) {
      sim_ctx_->state.vars = new uint8_t[addr];
    }
  }

  uint32_t alloc_call_params(lnodeimpl* node) {
    uint32_t size = 0;
    switch (node->type()) {
    case type_proxy: {
      auto proxy = reinterpret_cast<proxyimpl*>(node);
      size += proxy->ranges().size() * sizeof(proxy_range_t);
    } break;
    default:
      break;
    }
    return size;
  }

  void create_inputs(context* ctx) {
    auto load_input = [&](ioportimpl* node, uint32_t index) {
      this->create_node_label(node);
      if (node->size() <= 64) {
        auto j_src_ptr = jit_insn_load_relative(jf_, j_inputs_, index * sizeof(block_type*), jit_type_void_ptr);
        auto j_src_value = jit_insn_load_relative(jf_, j_src_ptr, 0, jit_type_ulong);
        var_map_[node->id()] = j_src_value;
      } else {
        //--
        CH_TODO();
      }
    };
    sim_ctx_->state.inputs = new block_type*[ctx->inputs().size()];
    uint32_t index =  0;
    for (auto node : ctx->inputs()) {
      sim_ctx_->state.inputs[index] = node->value()->words();
      load_input(node, index++);
    }
  }

  void create_outputs(context* ctx) {
    auto store_output = [&](ioportimpl* node, uint32_t index) {
      this->create_node_label(node);
      if (node->size() <= 64) {
        auto j_dst_ptr = jit_insn_load_relative(jf_, j_outputs_, index * sizeof(block_type*), jit_type_void_ptr);
        auto j_src_value = var_map_.at(node->src(0).id());
        jit_insn_store_relative(jf_, j_dst_ptr, 0, j_src_value);
      } else {
        //--
        CH_TODO();
      }
    };
    sim_ctx_->state.outputs = new block_type*[ctx->outputs().size() + ctx->taps().size()];
    uint32_t index =  0;    
    for (auto node : ctx->outputs()) {
      sim_ctx_->state.outputs[index] = node->value()->words();
      store_output(node, index++);
    }    
    for (auto node : ctx->taps()) {
      sim_ctx_->state.outputs[index] = node->value()->words();
      store_output(node, index++);
    }
  }

  void create_node_label(lnodeimpl* node) {
    jit_label_t label(jit_label_undefined);
    jit_insn_label(jf_, &label);
    label_map_[node->id()] = label;
  }

  alloc_map_t     alloc_map_;
  var_map_t       var_map_;
  label_map_t     label_map_;
  jit_function_t  jf_;
  jit_value_t     j_vars_;
  jit_value_t     j_inputs_;
  jit_value_t     j_outputs_;
  sim_ctx_t*      sim_ctx_;
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

}

#endif
