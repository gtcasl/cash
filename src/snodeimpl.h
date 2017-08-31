#pragma once

#include "snode.h"

namespace cash {
namespace internal {

class snodeimpl : public refcounted {
public:
  explicit snodeimpl(uint32_t size);
  explicit snodeimpl(const bitvector& value);
  ~snodeimpl();  
  
  uint32_t get_id() const {
    return id_;
  }
  
  const snode* get_owner() const {
    return owner_;
  }
  
  void set_owner(const snode* owner) {
    owner_ = owner;
  }

  void add_source(uint32_t dst_offset,
                  snodeimpl* src,
                  uint32_t src_offset,
                  uint32_t src_length);

  void clear_sources(uint32_t offset, uint32_t length);

  bool get_bit(uint32_t idx) const {
    this->sync_sources();
    return value_[idx];
  }
  
  void set_bit(uint32_t idx, bool value) {
    this->sync_sources();
    value_[idx] = value;
    ++changeid_;
  }
  
  uint32_t get_word(uint32_t idx) const {
    this->sync_sources();
    return value_.get_word(idx);
  }
  
  void set_word(uint32_t idx, uint32_t value) {
    this->sync_sources();
    value_.set_word(idx, value);
    ++changeid_;
  }
  
  void read(uint8_t* out, uint32_t sizeInBytes, uint32_t offset, uint32_t size) const {
    this->sync_sources();
    value_.read(out, sizeInBytes, offset, size);
  }
  
  void write(const uint8_t* in, uint32_t sizeInBytes, uint32_t offset, uint32_t size) {
    this->sync_sources();
    value_.write(in, sizeInBytes, offset, size);
    ++changeid_;
  }

  const bitvector& get_value() const {
    this->sync_sources();
    return value_;
  }

  void set_value(const bitvector& value) {
    assert(0 == srcs_.size());
    value_ = value;
    ++changeid_;
  }

  uint32_t get_size() const {
    return value_.get_size();
  }
  
protected:

  uint64_t sync_sources() const;
  
  struct source_t {
    snodeimpl* node;
    uint32_t dst_offset;
    uint32_t src_offset;
    uint32_t src_length;
    mutable uint64_t changeid;

    bool operator==(const source_t& rhs) const {
      return this->node == rhs.node
          && this->dst_offset == rhs.dst_offset
          && this->src_offset == rhs.src_offset
          && this->src_length == rhs.src_length;
    }

    bool operator!=(const source_t& rhs) const {
      return !(*this == rhs);
    }
  };
  
  uint32_t id_;
  const snode* owner_;
  std::vector<source_t> srcs_;
  mutable bitvector value_;
  mutable uint64_t  changeid_;  
};

}
}
