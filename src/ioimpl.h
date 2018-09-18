#pragma once

#include "lnodeimpl.h"

namespace ch {
namespace internal {

class ioimpl : public lnodeimpl {
protected:

  ioimpl(context* ctx,
         lnodetype type,
         uint32_t size,
         const source_location& sloc,
         const std::string& name = "");

  friend class context;
};

///////////////////////////////////////////////////////////////////////////////

class ioportimpl : public ioimpl {
public:

  const bitvector& value() const {
    return value_;
  }

  bitvector& value() {
    return value_;
  }

  bool is_bind() const {
    return !binding_.empty();
  }

  void bind(const lnode& binding) {
    binding_ = binding;
  }

  const lnode& binding() const {
    return binding_;
  }

protected:

  ioportimpl(context* ctx,
             lnodetype type,
             uint32_t size,
             const source_location& sloc,
             const std::string& name = "");

  bitvector value_;
  lnode binding_;

  friend class context;
};

///////////////////////////////////////////////////////////////////////////////

class inputimpl : public ioportimpl {
public:

  void print(std::ostream& out) const override;
  
protected:

  inputimpl(context* ctx,
            uint32_t size,
            const std::string& name,
            const source_location& sloc);

  ~inputimpl();  

  friend class context;
};

///////////////////////////////////////////////////////////////////////////////

class outputimpl : public ioportimpl {
public:

  void print(std::ostream& out) const override;
  
protected:

  outputimpl(context* ctx,
             const lnode& src,
             const std::string& name,
             const source_location& sloc);

  ~outputimpl();

  friend class context;
};

///////////////////////////////////////////////////////////////////////////////

class tapimpl : public ioportimpl {
public:

  const lnode& target() const {
    return srcs_[0];
  }

  void print(std::ostream& out) const override;

protected:

  tapimpl(context* ctx,
          const lnode& src,
          const std::string& name,
          const source_location& sloc);

  ~tapimpl();

  friend class context;
};

}
}
