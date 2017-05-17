#include "printimpl.h"
#include "context.h"
#include "bit.h"

using namespace std;
using namespace cash_internal;

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
    CH_ABORT("print format invalid index value");
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
    CH_ABORT("print format missing terminating index bracket");
    return str;
  }
  
  return str;
}

printimpl::printimpl(context* ctx, lnodeimpl* cond, const std::string& format, 
                     const std::initializer_list<lnodeimpl*>& args) 
  : ioimpl(op_print, ctx, 0)
  , format_(format)
  , args_offset_(0)
  , ctime_(~0ull) {
  if (cond) {
    srcs_.emplace_back(cond);
    args_offset_ = 1;
  }
  for (auto arg : args) {
    srcs_.emplace_back(arg);
  }
}

const bitvector& printimpl::eval(ch_cycle t) {
  if (ctime_ != t) {
    ctime_ = t;    
    if (args_offset_ == 0 
     || srcs_[0].eval(t)[0]) {
      if (format_ != "") {
        strbuf_.clear();
        for (const char *str = format_.c_str(); *str != '\0'; ++str) {
          if (*str == '{') {
            fmtinfo_t fmt;
            str = parse_format_index(&fmt, str);      
            switch (fmt.type) {
            case fmttype::Int:
              strbuf_ << srcs_[args_offset_ + fmt.index].eval(t);
              break;
            case fmttype::Float: {
                uint32_t value = srcs_[args_offset_ + fmt.index].eval(t).get_word(0);
                float valuef = *(const float*)&value;
                strbuf_ << valuef;
              }
              break;
            }            
          } else {
            strbuf_.put(*str);
          }
        }
        std::cout << strbuf_.rdbuf();
      }
      std::cout << std::endl;
    }
  }
  return value_;
}

void printimpl::print_vl(std::ostream& out) const {
  TODO("Not yet implemented!");
}

///////////////////////////////////////////////////////////////////////////////

void cash_internal::createPrintNode(lnodeimpl* cond, const std::string& format, 
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
  CH_CHECK(max_index < (int)args.size(), "print format index out of range");
  context* ctx = ctx_curr();
  new printimpl(ctx, cond, format, args);
}
