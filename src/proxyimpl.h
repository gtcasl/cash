#pragma once

#include "lnodeimpl.h"

namespace ch {
namespace internal {

class proxyimpl : public lnodeimpl {
public:

  struct range_t {
    uint32_t src_idx;
    uint32_t dst_offset;
    uint32_t src_offset;
    uint32_t length;

    bool operator==(const range_t& other) const {
      return this->src_idx    == other.src_idx
          && this->dst_offset == other.dst_offset
          && this->src_offset == other.src_offset
          && this->length     == other.length;
    }

    bool operator!=(const range_t& other) const {
      return !(*this == other);
    }
  };

  bool is_identity() const {
    return (1 == ranges_.size())
        && (srcs_[0].size() == value_.size());
  }

  const std::vector<range_t>& ranges() const {
    return ranges_;
  }
  
  void add_source(uint32_t dst_offset,
                  const lnode& src,
                  uint32_t src_offset = 0,
                  uint32_t length = 0);

  std::vector<lnode>::iterator erase_source(std::vector<lnode>::iterator iter);

  void write(uint32_t dst_offset,
             const lnode& src,
             uint32_t src_offset,
             uint32_t length,
             const source_location& sloc) override;

  bool equals(const lnodeimpl& other) const override;

  std::size_t hash() const override;

  lnodeimpl* slice(uint32_t offset,
                   uint32_t length,
                   const source_location& sloc) override;

  void eval() override;

  void print(std::ostream& out, uint32_t level) const override;
  
protected:

  proxyimpl(context* ctx,
            uint32_t size,
            const source_location& sloc,
            const std::string& name = "",
            uint32_t var_id = 0);

  proxyimpl(context* ctx,
            const lnode& src,
            uint32_t offset,
            uint32_t length,
            const source_location& sloc,
            const std::string& name = "",
            uint32_t var_id = 0);

  ~proxyimpl() {}

  std::vector<range_t> ranges_;

  friend class context;
};

///////////////////////////////////////////////////////////////////////////////

class refimpl : public proxyimpl {
public:

  void write(uint32_t dst_offset,
             const lnode& src,
             uint32_t src_offset,
             uint32_t length,
             const source_location& sloc) override;

protected:

  refimpl(context* ctx,
          const lnode& src,
          uint32_t offset,
          uint32_t length,
          const source_location& sloc,
          const std::string& name = "",
          uint32_t var_id = 0);

  friend class context;
};

}
}
