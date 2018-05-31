#include "printimpl.h"
#include "context.h"
#include "logic.h"

using namespace ch::internal;

enum class fmttype {
  Int,
  Float,
  String,
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
        out->type = fmttype::Int;
        break;
      case 'f':
        out->type = fmttype::Float;
        break;
      case 's':
        out->type = fmttype::String;
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

printimpl::printimpl(context* ctx,
                     const std::string& format,
                     const std::initializer_list<lnode>& args)
  : ioimpl(ctx, type_print, 0)
  , format_(format)
  , predicated_(false) {
  if (ctx_->conditional_enabled(this)) {
    auto pred = ctx_->create_predicate();
    if (pred) {
      srcs_.emplace_back(pred);
      predicated_ = true;
    }
  }
  for (auto arg : args) {
    srcs_.emplace_back(arg);
  }
}

void printimpl::eval() {
  if (predicated_ && 0 == srcs_[0].data().word(0))
    return;
  if (format_ != "") {
    strbuf_.clear();
    for (const char *str = format_.c_str(); *str != '\0'; ++str) {
      if (*str == '{') {
        fmtinfo_t fmt;
        str = parse_format_index(&fmt, str);
        uint32_t args_offset_ = predicated_ ? 1 : 0;
        auto& src = srcs_[args_offset_ + fmt.index];
        switch (fmt.type) {
        case fmttype::Int:
          strbuf_ << src.data();
          break;
        case fmttype::Float:
          strbuf_ << bitcast<float>(src.data().word(0));
          break;
        case fmttype::String:
          strbuf_ << ctx_->enum_to_string(src);
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

void printimpl::print(std::ostream& out, uint32_t level) const {
  out << "#" << id_ << " <- " << this->type();
  uint32_t n = srcs_.size();
  if (n > 0) {
    out << "(";
    uint32_t i = 0;
    if (predicated_) {
      out << "pred=" << srcs_[i++].id();
    }
    for (; i < n; ++i) {
      if (i > 0)
        out << ", ";
      out << "#" << srcs_[i].id();
    }
    out << ")";
  }
  if (level == 2) {
    out << " = " << value_;
  }
}

///////////////////////////////////////////////////////////////////////////////

static int getFormatMaxIndex(const char* format) {
  int max_index = -1;
  for (const char *str = format; *str != '\0'; ++str) {
    if (*str == '{') {
      fmtinfo_t fmt;
      str = parse_format_index(&fmt, str);
      max_index = std::max(fmt.index, max_index);
    }
  }
  return max_index;
}

void ch::internal::createPrintNode(
    const std::string& format,
    const std::initializer_list<lnode>& args) {
  // printing is only enabled in debug mode
  if (0 == platform::self().dbg_level())
    return;

  // check format
  auto max_index = getFormatMaxIndex(format.c_str());
  CH_CHECK(max_index < (int)args.size(), "print format index out of range");

  // create print node
  ctx_curr()->create_node<printimpl>(format, args);
}
