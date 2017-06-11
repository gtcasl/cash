#pragma once

#include "snode.h"

namespace cash {
namespace detail {

class snodeimpl : public refcounted {
public:
  snodeimpl(uint32_t size);
  snodeimpl(const bitvector& value);
  ~snodeimpl();  
  
  uint32_t get_id() const {
    return id_;
  }
  
  const snode* get_owner() const {
    return owner_;
  }
  
  void set_owner(const snode* owner) {
    assert(nullptr == owner || nullptr == owner_);
    owner_ = owner;
  }

  void add_source(uint32_t dst_offset,
                  snodeimpl* src,
                  uint32_t src_offset,
                  uint32_t src_length);

  void clear_sources(uint32_t offset, uint32_t length);

  bitvector::const_reference operator[](uint32_t idx) const {
    this->sync_sources();
    return value_[idx];
  }
  
  bitvector::reference operator[](uint32_t idx) {
    ++changeid_;
    this->sync_sources();
    return value_[idx];
  }
  
  uint32_t read(uint32_t idx) const {
    this->sync_sources();
    return value_.get_word(idx);
  }
  
  void write(uint32_t idx, uint32_t value) {
    this->sync_sources();
    value_.set_word(idx, value);
    ++changeid_;
  }
  
  void read(uint8_t* out, uint32_t offset, uint32_t size) const {
    this->sync_sources();
    value_.read(out, offset, size);
  }
  
  void write(const uint8_t* in, uint32_t offset, uint32_t size) {
    this->sync_sources();
    value_.write(in, offset, size);
    ++changeid_;
  }
  
  const bitvector& read() const {
    this->sync_sources();
    return value_;
  }
  
  void write(const bitvector& value) {
    assert(0 == srcs_.size());
    value_ = value;
    ++changeid_;
  }

  const bitvector& get_value() const {
    this->sync_sources();
    return value_;
  }

  uint32_t get_size() const {
    return value_.get_size();
  }
  
protected:

  uint64_t sync_sources() const;
  
  void merge_left(uint32_t idx);
  
  struct source_t {
    snodeimpl* node;
    uint32_t start;    
    uint32_t offset;    
    uint32_t length;
    mutable uint64_t changeid;
  };
  
  uint32_t id_;
  const snode* owner_;
  std::vector<source_t> srcs_;
  mutable bitvector value_;
  mutable uint64_t  changeid_;  
};

}
}
