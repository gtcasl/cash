#pragma once

#include "common.h"
#include "arithm.h"

namespace ch {
namespace internal {

class context;
class lnodeimpl;
class litimpl;
class proxyimpl;
class aluimpl;
class selectimpl;
class regimpl;
class memimpl;
class bindimpl;
class bindportimpl;
class bitvector;
class cdimpl;

class verilogwriter {
public:

  verilogwriter(std::ostream& out);

  ~verilogwriter();

  void print(const std::initializer_list<context*>& contexts);

protected:

  struct module_t {
    context* ctx;
    uint32_t num_temps;
    std::unordered_map<unsigned, std::unordered_set<lnodeimpl*>> uses;

    module_t(context* p_ctx);

    bool is_inline_subscript(lnodeimpl* node) const;
  };

  bool print_module(module_t& module);

  void print_header(module_t& module);

  void print_body(module_t& module);

  void print_footer(module_t& module);

  void print_port(module_t& module, lnodeimpl* node);

  bool print_decl(module_t& module,
                  lnodeimpl* node,
                  std::unordered_set<uint32_t>& visited,
                  lnodeimpl* ref = nullptr);

  bool print_binding(module_t& module, bindimpl* node);

  bool print_bindport(module_t& module, bindportimpl* node);

  bool print_logic(module_t& module, lnodeimpl* node);

  void print_name(module_t& module, lnodeimpl* node, bool force = false);

  void print_type(lnodeimpl* node);

  void print_value(const bitvector& value,
                   bool skip_leading_zeros_enable = false,
                   unsigned offset = 0,
                   unsigned size = 0);

  void print_proxy(module_t& module, proxyimpl* node);

  void print_alu(module_t& module, aluimpl* node);

  void print_zext(module_t& module, aluimpl* node);

  void print_sext(module_t& module, aluimpl* node);

  void print_fmult(module_t& module, aluimpl* node);

  void print_fadd(module_t& module, aluimpl* node);

  void print_select(module_t& module, selectimpl* node);

  void print_reg(module_t& module, regimpl* node);

  void print_cdomain(module_t& module, cdimpl* cd);

  void print_mem(module_t& module, memimpl* node);

  void print_operator(ch_op op);

  std::ostream& out_;
  std::unordered_set<std::string_view> visited_;
};

}
}
