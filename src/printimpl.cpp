#include "printimpl.h"
#include "context.h"
#include "logic.h"

using namespace ch::internal;

fmtparser::fmtparser() : index_(0) {}

const char* fmtparser::parse(fmtinfo_t* out, const char* str) {
  assert(str);
  
  // check starting bracket
  assert(*str == '{');
  
  ++str; // advance to next char

  // skip leading spaces
  while (isspace(*str)) {
    ++str;
  }

  // parse index value
  const char *str_idx_end = str;
  if (*str == ':' || *str == '}') {
    out->index = index_;
  } else {
    out->index = strtoul(str, (char**)&str_idx_end, 0);
    if (str_idx_end == str || errno == ERANGE) {
      CH_ABORT("print format invalid index value");
      return str;
    }
  }
  index_ = out->index + 1;
  
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
      case 'e':
        out->type = fmttype::Enum;
        break;
      default:
        CH_ABORT("invalid print argument type: %c", *str);
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
                     const std::vector<lnode>& args,
                     const std::vector<enum_string_cb>& enum_strings,
                     const source_location& sloc)
  : ioimpl(ctx, type_print, 0, sloc, "")
  , enum_strings_(enum_strings)
  , format_(format)
  , pred_idx_(-1) {
  if (ctx_->conditional_enabled(this)) {
    auto pred = ctx_->create_predicate(sloc);
    if (pred) {
      pred_idx_ = this->add_src(pred);
    }
  }

  for (auto arg : args) {
    this->add_src(arg);
  }
}

printimpl::printimpl(context* ctx,
                     const std::string& format,
                     const std::vector<lnode>& args,
                     const std::vector<enum_string_cb>& enum_strings,
                     lnodeimpl* pred,
                     const source_location& sloc)
  : ioimpl(ctx, type_print, 0, sloc, "")
  , enum_strings_(enum_strings)
  , format_(format)
  , pred_idx_(-1) {
  if (pred) {
    pred_idx_ = this->add_src(pred);
  }
  for (auto arg : args) {
    this->add_src(arg);
  }
}

lnodeimpl* printimpl::clone(context* ctx, const clone_map& cloned_nodes) const {
  lnodeimpl* pred = nullptr;
  if (this->has_pred()) {
    pred = cloned_nodes.at(this->pred().id());
  }
  std::vector<lnode> args;
  for (uint32_t i = pred_idx_ + 1; i < this->srcs().size(); ++i) {
    auto& src = cloned_nodes.at(this->src(i).id());
    args.emplace_back(src);
  }
  return ctx->create_node<printimpl>(format_, args, enum_strings_, pred, sloc_);
}

void printimpl::print(std::ostream& out) const {
  out << "#" << id_ << " <- " << this->type();
  uint32_t n = this->srcs().size();
  if (n > 0) {
    out << "(";
    uint32_t i = 0;
    if (this->has_pred()) {
      out << "pred=" << this->src(i++).id();
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

static int getFormatMaxIndex(const char* format) {
  int max_index = -1;
  fmtparser parser;
  for (const char *str = format; *str != '\0'; ++str) {
    if (*str == '{') {
      fmtinfo_t fmt;
      str = parser.parse(&fmt, str);
      max_index = std::max(fmt.index, max_index);
    }
  }
  return max_index;
}

void ch::internal::createPrintNode(
    const std::string& format,
    const std::vector<lnode>& args) {
  // printing is only enabled in debug mode
  if (0 == platform::self().dbg_level())
    return;

  // check format
  auto max_index = getFormatMaxIndex(format.c_str());
  CH_CHECK(max_index < (int)args.size(), "print format index out of range");

  // create print node
  std::vector<enum_string_cb> enum_strings;
  for (auto arg : args) {
    auto cb = arg.impl()->ctx()->enum_to_string(arg.id());
    enum_strings.emplace_back(cb);
  }
  auto sloc = get_source_location();
  ctx_curr()->create_node<printimpl>(format, args, enum_strings, sloc);
}
