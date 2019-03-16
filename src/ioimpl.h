#pragma once

#include "lnodeimpl.h"
#include "ioport.h"

namespace ch {
namespace internal {

class bindportimpl;

class ioimpl : public lnodeimpl {
protected:

  ioimpl(context* ctx,
         lnodetype type,
         uint32_t size,
         const source_location& sloc,
         const std::string& name);

  friend class context;
};

///////////////////////////////////////////////////////////////////////////////

class ioportimpl : public ioimpl {
public:

  const io_value_t& value() const {
    return value_;
  }

protected:

  ioportimpl(context* ctx,
             lnodetype type,
             uint32_t size,
             const io_value_t& value,
             const source_location& sloc,
             const std::string& name);

  io_value_t value_;

  friend class context;
};

///////////////////////////////////////////////////////////////////////////////

class inputimpl : public ioportimpl {
public:

  lnodeimpl* clone(context* ctx, const clone_map& cloned_nodes) const override;

  bool has_bindport() const {
    return !bindports_.empty();
  }

  void add_bindport(bindportimpl* bindport) {
    bindports_.push_back(bindport);
  }

  const auto bindports() const {
    return bindports_;
  }

  void print(std::ostream& out) const override;
  
protected:

  inputimpl(context* ctx,
            uint32_t size,
            const io_value_t& value,
            const std::string& name,
            const source_location& sloc);

  ~inputimpl();  

  std::vector<bindportimpl*> bindports_;

  friend class context;
};

///////////////////////////////////////////////////////////////////////////////

class outputimpl : public ioportimpl {
public:

  lnodeimpl* clone(context* ctx, const clone_map& cloned_nodes) const override;

  void print(std::ostream& out) const override;
  
protected:

  outputimpl(context* ctx,
             const lnode& src,
             const io_value_t& value,
             const std::string& name,
             const source_location& sloc);

  ~outputimpl();

  friend class context;
};

///////////////////////////////////////////////////////////////////////////////

class tapimpl : public ioportimpl {
public:

  const lnode& target() const {
    return this->src(0);
  }

  lnodeimpl* clone(context* ctx, const clone_map& cloned_nodes) const override;

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
