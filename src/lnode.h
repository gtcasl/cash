#pragma once

#include "common.h"
#include "bitvector.h"

namespace ch {
namespace internal {

class lnodeimpl;
class context;

using ch_tick = uint64_t;

class nodelist;

class lnode {
public:

  lnode();

  ~lnode();

  lnode(const lnode& rhs);

  lnode(const lnode& rhs, uint32_t size);

  lnode(lnode&& rhs, uint32_t size);

  explicit lnode(uint32_t size);

  lnode(lnodeimpl* impl);

  lnode(const bitvector& value);

  lnode(const nodelist& data);

  lnode& operator=(const lnode& rhs);

  bool operator==(const lnode& rhs) const;

  bool operator<(const lnode& rhs) const;

  void clear();

  bool is_empty() const;

  void set_impl(lnodeimpl* impl);

  lnodeimpl* get_impl() const;
  
  uint32_t get_id() const;
  
  uint32_t get_size() const;
  
  context* get_ctx() const;
  
  bool ready() const;
  
  bool valid() const;
 
  const bitvector& eval(ch_tick t);  

  void assign(const lnode& rhs, uint32_t size);

  void assign(const bitvector& value);

  void move(lnode& rhs, uint32_t size);

  void read_lnode(nodelist& inout,
                 uint32_t offset,
                 uint32_t length,
                 uint32_t size) const;
  
  void write_lnode(uint32_t dst_offset,
                  const nodelist& in,
                  uint32_t src_offset,
                  uint32_t length,
                  uint32_t size);

  void read_bytes(uint32_t dst_offset,
                  void* out,
                  uint32_t out_cbsize,
                  uint32_t src_offset,
                  uint32_t length,
                  uint32_t size) const;

  void write_bytes(uint32_t dst_offset,
                   const void* in,
                   uint32_t in_cbsize,
                   uint32_t src_offset,
                   uint32_t length,
                   uint32_t size);

  const bitvector& get_value() const;

  void set_value(const bitvector& value);

  bool get_bool(unsigned i) const;

  void set_bool(unsigned i, bool value);

  lnodeimpl* clone(uint32_t size) const;

protected:

  void ensureInitialized(uint32_t size, bool initialize) const;

  void init(uint32_t dst_offset,
            const lnode& src,
            uint32_t src_offset,
            uint32_t length,
            uint32_t size);

  void assign(uint32_t dst_offset,
              const lnode& src,
              uint32_t src_offset,
              uint32_t length,
              uint32_t size);
  
  mutable lnodeimpl* impl_;
};

class nodelist {
public:
  nodelist(uint32_t capacity, bool movable)
    : capacity_(capacity)
    , size_(0)
    , movable_(movable)
  {}

  bool is_movable() const {
    return movable_;
  }

  uint32_t get_size() const {
    return size_;
  }

  uint32_t get_num_slices() const {
    return slices_.size();
  }

  bool is_identity() const {
    return (1 == slices_.size())
        && (slices_[0].src.get_size() == size_);
  }

  void push(const lnode& src, uint32_t offset, uint32_t length) {
    slices_.emplace_back(slice_t{src, offset, length});
    size_ += length;
    assert(size_ <= capacity_);
  }

  void push(const lnode& src, uint32_t offset = 0) {
    this->push(src, offset, capacity_);
  }

  auto begin() const {
    assert(size_ == capacity_);
    return slices_.begin();
  }

  auto end() const {
    return slices_.end();
  }

protected:
  struct slice_t {
    const lnode& src;
    uint32_t offset;
    uint32_t length;
  };

  std::vector<slice_t> slices_;
  uint32_t capacity_;
  uint32_t size_;
  bool movable_;
};

std::ostream& operator<<(std::ostream& out, const lnode& node);

}
}
