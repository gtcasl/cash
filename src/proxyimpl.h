#pragma once

#include "lnodeimpl.h"

namespace cash {
namespace internal {

class proxyimpl : public lnodeimpl {
public:

  struct range_t {
    uint32_t src_idx;
    uint32_t dst_offset;
    uint32_t src_offset;
    uint32_t src_length;

    bool operator==(const range_t& rhs) const {
      return this->src_idx == rhs.src_idx
          && this->dst_offset == rhs.dst_offset
          && this->src_offset == rhs.src_offset
          && this->src_length == rhs.src_length;
    }

    bool operator!=(const range_t& rhs) const {
      return !(*this == rhs);
    }
  };

  proxyimpl(context* ctx, uint32_t size);
  proxyimpl(const lnode& src);
  proxyimpl(const lnode& src, uint32_t offset, uint32_t length);

  const std::vector<range_t>& get_ranges() const {
    return ranges_;
  }
  
  void add_source(uint32_t dst_offset,
                  const lnode& src,
                  uint32_t src_offset,
                  uint32_t src_length);

  std::vector<lnode>::iterator erase_source(std::vector<lnode>::iterator iter);

  lnodeimpl* get_slice(uint32_t offset, uint32_t length);

  std::vector<std::pair<uint32_t, uint32_t>> get_update_slices(uint32_t offset, uint32_t length);

  const bitvector& eval(ch_cycle t) override;
  void print(std::ostream& out, uint32_t level) const override;
  void print_vl(std::ostream& out) const override;
  
private:

  std::vector<range_t> ranges_; 
  ch_cycle ctime_;
};

}
}
