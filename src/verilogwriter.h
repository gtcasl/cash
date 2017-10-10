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
class latchimpl;
class memimpl;
class callimpl;
class bitvector;
class cdomain;

class verilogwriter {
public:
  verilogwriter(std::ostream& out);
  ~verilogwriter();

  void print(context* ctx);

protected:

  bool print_impl(context* ctx);

  void print_header(context* ctx);

  void print_body(context* ctx);

  void print_footer(context* ctx);

  void print_port(lnodeimpl* node);

  bool print_decl(lnodeimpl* node);

  bool print_call(callimpl* call);

  bool print_logic(lnodeimpl* node);

  void print_name(lnodeimpl* node);

  void print_type(lnodeimpl* node);

  void print_value(const bitvector& value);

  void print_proxy(proxyimpl* node);

  void print_alu(aluimpl* node);

  void print_rotate(aluimpl* node, bool right_dir);

  void print_mux(aluimpl* node);

  void print_fmult(aluimpl* node);

  void print_fadd(aluimpl* node);

  void print_operator(ch_alu_op op);

  void print_select(selectimpl* node);

  void print_reg(regimpl* node);

  void print_cdomain(cdomain* cd);

  void print_mem(memimpl* node);

  std::ostream& out_;
};

}
}
