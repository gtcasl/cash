#pragma once

#include "context.h"
#include "ioimpl.h"

namespace ch {
namespace internal {

enum class fmttype {
  Int,
  Float,
  Enum,
};

struct fmtinfo_t {
  int index;
  fmttype type;
};

const char* parse_format_index(fmtinfo_t* out, const char* str);

class printimpl : public ioimpl {
public:

  const std::string& format() const {
    return format_;
  }

  bool has_pred() const {
    return (pred_idx_ != -1);
  }

  auto& pred() const {
    return srcs_[pred_idx_];
  }

  auto& enum_strings() const {
    return enum_strings_;
  }

  virtual lnodeimpl* clone(context* ctx, const clone_map& cloned_nodes) override;

  void print(std::ostream& out) const override;

protected:

  printimpl(context* ctx,
            const std::string& format,
            const std::vector<lnode>& args,
            const std::vector<enum_string_cb>& enum_strings,
            const source_location& sloc);

  printimpl(context* ctx,
            const std::string& format,
            const std::vector<lnode>& args,
            const std::vector<enum_string_cb>& enum_strings,
            lnodeimpl* pred,
            const source_location& sloc);

  std::vector<enum_string_cb> enum_strings_;
  std::string format_;
  int pred_idx_;

  friend class context;
};

}
}
