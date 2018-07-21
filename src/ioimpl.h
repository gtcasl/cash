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
         const std::string& name = "")
    : lnodeimpl(ctx, type, size, sloc, name)
  {}

  ~ioimpl() {}

  friend class context;
};

class inputimpl : public ioimpl {
public:

  const lnode& input() const {
    return input_;
  }

  void bind(const lnode& input);

  void initialize() override;

  void eval() override;
  
  void print(std::ostream& out, uint32_t level) const override;
  
protected:

  inputimpl(context* ctx,
            uint32_t size,
            const std::string& name,
            const source_location& sloc);

  ~inputimpl();

  lnode input_;

  uint32_t* words_;

  friend class context;
};

class outputimpl : public ioimpl {
public:

  void write(uint32_t dst_offset,
             const lnode& src,
             uint32_t src_offset,
             uint32_t length,
             const source_location& sloc) override;

  void initialize() override;

  void eval() override;
  
  void print(std::ostream& out, uint32_t level) const override;
  
protected:

  outputimpl(context* ctx,
             uint32_t size,
             const std::string& name,
             const source_location& sloc);

  ~outputimpl();

  uint32_t* words_;

  friend class context;
};

class tapimpl : public ioimpl {
public:

  const lnode& target() const {
    return srcs_[0];
  }

  void initialize() override;

  void eval() override;
  
  void print(std::ostream& out, uint32_t level) const override;

protected:

  tapimpl(context* ctx,
          const lnode& src,
          const std::string& name,
          const source_location& sloc);

  ~tapimpl();

  uint32_t* words_;

  friend class context;
};

}
}
