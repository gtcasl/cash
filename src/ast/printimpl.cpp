#include "debug.h"
#include "context.h"
#include "printimpl.h"

using namespace ch::internal;

enum class fmttype {
  Bool,
  Int,
  Float,
  Enum,
};

struct fmtinfo_t {
  fmttype type;
  int index;

  fmtinfo_t() : type(fmttype::Bool), index(-1) {}
};

static bool is_escape(const char* str) {
  return (str[0] == '\\') && (str[1] == '{' || str[1] == '}');
}

static const char* parse(fmtinfo_t* out, const char* format) {
  assert(format);

  // check starting bracket
  assert(*format == '{');

  ++format; // advance to next char

  // skip leading spaces
  while (isspace(*format)) {
    ++format;
  }

  // parse index value
  const char *str_idx_end = format;
  if (*format == ':' || *format == '}') {
    ++out->index;
  } else {
    out->index = strtoul(format, (char**)&str_idx_end, 0);
    if (str_idx_end == format || errno == ERANGE) {
      throw std::invalid_argument(sstreamf() << "print format invalid index value: " << format);
    }
  }

  // advance pointer
  format = str_idx_end;

  // check type info
  out->type = fmttype::Int;
  if (*format == ':') {
    ++format; // advance pointer
    if (*format != '\0') {
      switch (*format) {
      case 'b':
        out->type = fmttype::Bool;
        break;
      case 'i':
        out->type = fmttype::Int;
        break;
      case 'f':
        out->type = fmttype::Float;
        break;
      case 'e':
        out->type = fmttype::Enum;
        break;
      default:
        throw std::invalid_argument(sstreamf() << "invalid print argument type: " << *format);
      }
      ++format; // advance pointer
    }
  }

  // check terminating bracket
  if (*format == '\0' || *format != '}') {
    throw std::invalid_argument("print format missing terminating index bracket");
  }

  return format;
}

static int findMaxSourceIndex(const char* format) {
  int max_index = -1;
  fmtinfo_t fmt;
  for (const char *str = format; *str != '\0'; ++str) {
    if (is_escape(str)) {
      ++str;
    } else if (str[0] == '{') {
      str = parse(&fmt, str);
      max_index = std::max(fmt.index, max_index);
    }
  }
  return max_index;
}

std::string ch::internal::to_string(const char* format,
                                    const sdata_type* srcs,
                                    const enum_string_cb* enum_strings) {
  std::stringstream ss;
  fmtinfo_t fmt;

  ss << std::boolalpha;

  for (const char *str = format; *str != '\0'; ++str) {
    if (is_escape(str))
      ss.put(*(++str));
    else if (*str == '{') {
      str = parse(&fmt, str);
      auto& src = srcs[fmt.index];
      switch (fmt.type) {
      case fmttype::Bool:
        ss << static_cast<bool>(src);
        break;
      case fmttype::Int:
        ss << src;
        break;
      case fmttype::Float:
        ss << bit_cast<float>(static_cast<int>(src));
        break;
      case fmttype::Enum:
        ss << enum_strings[fmt.index](static_cast<int>(src));
       break;
      }
    } else {
      ss.put(*str);
    }
  }
  return ss.str();
}

///////////////////////////////////////////////////////////////////////////////

printimpl::printimpl(context* ctx,
                     const std::string& format,
                     const std::vector<lnode>& args,
                     const std::vector<enum_string_cb>& enum_strings,
                     const source_info& srcinfo)
  : ioimpl(ctx, type_print, 0, "", srcinfo)
  , enum_strings_(enum_strings)
  , format_(format)
  , pred_idx_(-1) {
  auto pred = ctx_->get_predicate(srcinfo);
  if (pred) {
    pred_idx_ = this->add_src(pred);
  }

  for (auto arg : args) {
    this->add_src(arg.impl());
  }
}

printimpl::printimpl(context* ctx,
                     const std::string& format,
                     const std::vector<lnode>& args,
                     const std::vector<enum_string_cb>& enum_strings,
                     lnodeimpl* pred,
                     const source_info& srcinfo)
  : ioimpl(ctx, type_print, 0, "", srcinfo)
  , enum_strings_(enum_strings)
  , format_(format)
  , pred_idx_(-1) {
  if (pred) {
    pred_idx_ = this->add_src(pred);
  }
  for (auto arg : args) {
    this->add_src(arg.impl());
  }
}

lnodeimpl* printimpl::clone(context* ctx, const clone_map& cloned_nodes) const {
  lnodeimpl* pred = nullptr;
  if (this->has_pred()) {
    pred = cloned_nodes.at(this->pred().id());
  }
  std::vector<lnode> args;
  for (uint32_t i = pred_idx_ + 1; i < this->num_srcs(); ++i) {
    auto& src = cloned_nodes.at(this->src(i).id());
    args.emplace_back(src);
  }
  return ctx->create_node<printimpl>(format_, args, enum_strings_, pred, srcinfo_);
}

void printimpl::print(std::ostream& out) const {
  out << "#" << id_ << " <- " << this->type();
  uint32_t n = this->num_srcs();
  if (n > 0) {
    out << "(";
    out << "format=\"" << format_ << "\"";
    uint32_t i = 0;
    if (this->has_pred()) {
      out << ", pred=" << this->src(i++).id();
    }
    for (; i < n; ++i) {
      if (i > 0)
        out << ", ";
      out << "#" << this->src(i).id();
    }
    out << ")";
  }
}

///////////////////////////////////////////////////////////////////////////////

void ch::internal::createPrintNode(const std::string& format,
                                   const std::vector<lnode>& args,
                                   const source_info& srcinfo) {
  // check format
  auto max_index = findMaxSourceIndex(format.c_str());
  CH_CHECK(max_index < (int)args.size(), "print format index out of range");

  // create print node
  std::vector<enum_string_cb> enum_strings;
  for (auto arg : args) {
    auto cb = arg.impl()->ctx()->enum_to_string(arg.id());
    enum_strings.emplace_back(cb);
  }
  ctx_curr()->create_node<printimpl>(format, args, enum_strings, srcinfo);
}

///////////////////////////////////////////////////////////////////////////////

ch_ostream ch::internal::ch_cout;

void ch_streambuf::write(const lnode& node, char format, const source_info& srcinfo) {
  char tmp[64];
  auto size = nodes_.size();
  nodes_.push_back(node);
  srcinfo_ = srcinfo;
  auto len = snprintf(tmp, sizeof(tmp), "{%ld:%c}", size, format);
  this->sputn(tmp, len);
}

int ch_streambuf::sync() {
  if (base::pptr() == base::pbase())
    return 0;
  auto format = base::str();
  createPrintNode(format, nodes_, srcinfo_);
  base::str("");
  nodes_.clear();
  return 0;
}
