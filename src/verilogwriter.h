#pragma once

#include "common.h"
#include "traits.h"

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
class ioimpl;
class cdimpl;
class udfimpl;
class udfsimpl;
class tapimpl;
class source_location;
enum class ch_op;

class verilogwriter {
public:

  verilogwriter(context* ctx);

  ~verilogwriter();

  void print(std::ostream& out, std::unordered_set<std::string_view>& visited);

protected:

  bool is_inline_subscript(lnodeimpl* node) const;

  void print_header(std::ostream& out);

  void print_body(std::ostream& out);

  void print_footer(std::ostream& out);

  void print_port(std::ostream& out, ioimpl* node);

  bool print_decl(std::ostream& out,
                  lnodeimpl* node,
                  std::unordered_set<uint32_t>& visited,
                  lnodeimpl* ref = nullptr);

  bool print_binding(std::ostream& out, bindimpl* node);

  bool print_bindport(std::ostream& out, bindportimpl* node);

  bool print_logic(std::ostream& out, lnodeimpl* node);

  bool print_proxy(std::ostream& out, proxyimpl* node);

  void print_proxy_value(std::ostream& out, proxyimpl* node);

  bool print_alu(std::ostream& out, aluimpl* node);

  bool print_zext(std::ostream& out, aluimpl* node);

  bool print_sext(std::ostream& out, aluimpl* node);

  bool print_select(std::ostream& out, selectimpl* node);

  bool print_reg(std::ostream& out, regimpl* node);

  bool print_cdomain(std::ostream& out, cdimpl* cd);

  bool print_mem(std::ostream& out, memimpl* node);

  bool print_udf(std::ostream& out, udfimpl* node);

  bool print_tap(std::ostream& out, tapimpl* node);

  void print_name(std::ostream& out,
                  lnodeimpl* node,
                  bool force = false);

  void print_type(std::ostream& out, lnodeimpl* node);

  void print_value(std::ostream& out,
                   const sdata_type& value,
                   bool skip_zeros = false,
                   uint32_t offset = 0,
                   uint32_t size = 0,
                   bool digit_only = false);

  void print_operator(std::ostream& out, ch_op op);

  void print_sloc(std::ostream& out, const source_location& sloc);

  context* ctx_;
  std::unordered_map<uint32_t, std::unordered_set<lnodeimpl*>> uses_;
};

}
}
