#include "printimpl.h"
#include "context.h"
#include "bit.h"

using namespace std;
using namespace chdl_internal;

static int parse_format_index(const char** str) {
  assert(str);

  const char* curr = *str;
  
  // check starting bracket
  assert(*curr == '{');
  
  ++curr; // advance to next char
  
  // parse index value
  const char *str_idx_end = curr;
  uint32_t index = strtoul(curr, (char**)&str_idx_end, 0);
  if (str_idx_end == curr || errno == ERANGE) {
    CHDL_ABORT("print format invalid index value");
    return -1;
  }
  
  // advance pointer
  curr = str_idx_end;
  
  // check terminating bracket
  if (*curr == '\0' || *curr != '}') {
    CHDL_ABORT("print format missing terminating index bracket");
    return -1;
  }
  
  *str = curr;
  return index;
}

printimpl::printimpl(context* ctx, lnodeimpl* cond, const std::string& format, 
                     const std::initializer_list<lnodeimpl*>& args) 
  : ioimpl("print", ctx, 1)
  , m_format(format)
  , m_args_offset(0)
  , m_ctime(~0ull) {
  if (cond) {
    m_srcs.emplace_back(cond);
    m_args_offset = 1;
  }
  for (auto arg : args) {
    m_srcs.emplace_back(arg);
  }
  m_strbuf.setf(std::ios_base::hex); // enable hex formatting
}

const bitvector& printimpl::eval(ch_cycle t) {
  if (m_ctime != t) {
    m_ctime = t;    
    if (m_args_offset == 0 
     || m_srcs[0].eval(t)[0]) {
      m_strbuf.clear();
      for (const char *str = m_format.c_str(); *str != '\0'; ++str) {
        if (*str == '{') {
          int index = parse_format_index(&str);      
          m_strbuf << m_srcs[m_args_offset + index].eval(t);
        } else {
          m_strbuf.put(*str);
        }
      }
      std::cout << m_strbuf.rdbuf() << std::endl;
    }
  }
  return m_value;
}

// LCOV_EXCL_START
void printimpl::print_vl(std::ostream& out) const {
  TODO("Not yet implemented!");
}
// LCOV_EXCL_END

///////////////////////////////////////////////////////////////////////////////

void chdl_internal::createPrintNode(lnodeimpl* cond, const std::string& format, 
                     const std::initializer_list<lnodeimpl*>& args) {
  // check format
  int max_index = -1;
  for (const char *str = format.c_str(); *str != '\0'; ++str) {
    if (*str == '{') {
      max_index = max(parse_format_index(&str), max_index);      
    }
  }
  CHDL_CHECK(max_index < (int)args.size(), "print format index out of range");
  context* ctx = ctx_curr();
  ctx->register_gtap(new printimpl(ctx, cond, format, args));
}
