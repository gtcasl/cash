#pragma once

#include "common.h"
#include "traits.h"

namespace ch {
namespace internal {

class context;
class lnodeimpl;
class litimpl;
class proxyimpl;
class opimpl;
class selectimpl;
class regimpl;
class ioimpl;
class memimpl;
class bindimpl;
class bindportimpl;
class cdimpl;
enum class ch_op;

class firrtlwriter {
public:

  firrtlwriter(context* ctx);

  ~firrtlwriter();

  void print(std::ostream& out, std::unordered_set<std::string_view>& visited);

  void print_header(std::ostream& out);

  void print_body(std::ostream& out);

  void print_footer(std::ostream& out);

  void print_port(std::ostream& out, ioimpl* node);

  bool print_decl(std::ostream& out,
                  lnodeimpl* node,
                  std::unordered_set<uint32_t>& visited);

  bool print_binding(std::ostream& out, bindimpl* node);

  bool print_bindport(std::ostream& out, bindportimpl* node);

  bool print_logic(std::ostream& out, lnodeimpl* node);

  void print_name(std::ostream& out, lnodeimpl* node, bool noinline = false);

  void print_type(std::ostream& out, lnodeimpl* node);

  void print_dtype(std::ostream& out, lnodeimpl* node);

  void print_value(std::ostream& out,
                   const sdata_type& value,
                   bool skip_zeros = false,
                   uint32_t offset = 0,
                   uint32_t size = 0);

  bool print_lit(std::ostream& out, litimpl* node);

  bool print_proxy(std::ostream& out, proxyimpl* node);

  bool print_op(std::ostream& out, opimpl* node);

  bool print_select(std::ostream& out, selectimpl* node);

  bool print_reg(std::ostream& out, regimpl* node);

  bool print_cdomain(std::ostream& out, cdimpl* cd);

  bool print_mem(std::ostream& out, memimpl* node);

  void print_operator(std::ostream& out, ch_op op);

protected:

  context* ctx_;
  uint32_t num_temps_;
  std::unordered_map<uint32_t, std::unordered_set<lnodeimpl*>> uses_;
};

}
}
