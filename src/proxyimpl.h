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

    bool operator==(const range_t& rhs) const {
      return this->src_idx    == rhs.src_idx
          && this->dst_offset == rhs.dst_offset
          && this->src_offset == rhs.src_offset
          && this->length     == rhs.length;
    }

    bool operator!=(const range_t& rhs) const {
      return !(*this == rhs);
    }
  };

  bool is_identity() const {
    return (1 == ranges_.size())
        && (srcs_[0].get_size() == value_.get_size());
  }

  const std::vector<range_t>& get_ranges() const {
    return ranges_;
  }
  
  void add_source(uint32_t dst_offset,
                  const lnode& src,
                  uint32_t src_offset,
                  uint32_t length);

  void add_source(uint32_t dst_offset,
                  const lnode& src,
                  uint32_t src_offset = 0) {
    this->add_source(dst_offset, src, src_offset, src.get_size());
  }

  std::vector<lnode>::iterator erase_source(std::vector<lnode>::iterator iter);

  lnodeimpl* get_slice(uint32_t offset, uint32_t length);

  std::vector<std::pair<uint32_t, uint32_t>> get_update_slices(uint32_t offset, uint32_t length);

  const bitvector& eval(ch_tick t) override;

  void print(std::ostream& out, uint32_t level) const override;
  
protected:
  proxyimpl(context* ctx, uint32_t size);
  proxyimpl(context* ctx, const lnode& src);
  proxyimpl(context* ctx, const lnode& src, uint32_t offset, uint32_t length);
  ~proxyimpl() {}

  std::vector<range_t> ranges_; 
  ch_tick tick_;

  friend class context;
};

}
}
