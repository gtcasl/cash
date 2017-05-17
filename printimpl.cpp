#include "printimpl.h"
#include "context.h"
#include "bit.h"

using namespace std;
using namespace chdl_internal;

enum class fmttype {
  Int,
  Float,
};

struct fmtinfo_t {
  int index;
  fmttype type;
};

static const char* parse_format_index(fmtinfo_t* out, const char* str) {
  assert(str);
  
  // check starting bracket
  assert(*str == '{');
  
  ++str; // advance to next char
  
  // parse index value
  const char *str_idx_end = str;
  out->index = strtoul(str, (char**)&str_idx_end, 0);
  if (str_idx_end == str || errno == ERANGE) {
    CHDL_ABORT("print format invalid index value");
    return str;
  }
  
  // advance pointer
  str = str_idx_end;
  
  // check type info
  out->type = fmttype::Int;
  if (*str == ':') {
    ++str; // advance pointer
    if (*str != '\0') {
      switch (*str) {
      case 'i':
      case 'd':
      case 'x':
        out->type = fmttype::Int;
        break;
      case 'f':
      case 'F':
      case 'g':
        out->type = fmttype::Float;
        break;
      }
      ++str; // advance pointer
    }    
  }
  
  // check terminating bracket
  if (*str == '\0' || *str != '}') {
    CHDL_ABORT("print format missing terminating index bracket");
    return str;
  }
  
  return str;
}

printimpl::printimpl(context* ctx, lnodeimpl* cond, const std::string& format, 
                     const std::initializer_list<lnodeimpl*>& args) 
  : ioimpl(op_print, ctx, 0)
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
}

const bitvector& printimpl::eval(ch_cycle t) {
  if (m_ctime != t) {
    m_ctime = t;    
    if (m_args_offset == 0 
     || m_srcs[0].eval(t)[0]) {
      if (m_format != "") {
        m_strbuf.clear();
        for (const char *str = m_format.c_str(); *str != '\0'; ++str) {
          if (*str == '{') {
            fmtinfo_t fmt;
            str = parse_format_index(&fmt, str);      
            switch (fmt.type) {
            case fmttype::Int:
              m_strbuf << m_srcs[m_args_offset + fmt.index].eval(t);
              break;
            case fmttype::Float: {
                uint32_t value = m_srcs[m_args_offset + fmt.index].eval(t).get_word(0);
                float valuef = *(const float*)&value;
                m_strbuf << valuef;
              }
              break;
            }            
          } else {
            m_strbuf.put(*str);
          }
        }
        std::cout << m_strbuf.rdbuf();
      }
      std::cout << std::endl;
    }
  }
  return m_value;
}

void printimpl::print_vl(std::ostream& out) const {
  TODO("Not yet implemented!");
}

///////////////////////////////////////////////////////////////////////////////

void chdl_internal::createPrintNode(lnodeimpl* cond, const std::string& format, 
                     const std::initializer_list<lnodeimpl*>& args) {
  // printing is only enabled in debug mode
  if (platform::self().get_dbg_level() == 0)
    return;
  
  // check format
  int max_index = -1;
  for (const char *str = format.c_str(); *str != '\0'; ++str) {
    if (*str == '{') {
      fmtinfo_t fmt;
      str = parse_format_index(&fmt, str);
      max_index = max(fmt.index, max_index);      
    }
  }
  CHDL_CHECK(max_index < (int)args.size(), "print format index out of range");
  context* ctx = ctx_curr();
  new printimpl(ctx, cond, format, args);
}
