#pragma once

#include "snode.h"

namespace cash_internal {

class snodeimpl : public refcounted {
public:
  snodeimpl(uint32_t size);
  snodeimpl(const bitvector& value);
  ~snodeimpl();  
  
  uint32_t get_id() const {
    return id_;
  }
  
  snode* get_owner() const {
    return owner_;
  }
  
  void set_owner(snode* node) {
    owner_ = node;
  }
  
  void assign(uint32_t start, snodeimpl* src, uint32_t offset, uint32_t length);

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
  
  void read(uint8_t* out, uint32_t sizeInBytes) const {
    this->sync_sources();
    value_.read(out, sizeInBytes);
  }
  
  void write(const uint8_t* in, uint32_t sizeInBytes) {
    this->sync_sources();
    value_.write(in, sizeInBytes);
    ++changeid_;
  }
  
  const bitvector& read() const {
    this->sync_sources();
    return value_;
  }
  
  void write(const bitvector& value) {
    assert(srcs_.size() == 0);
    value_ = value;
    ++changeid_;
  }
  
  uint32_t get_size() const {
    return value_.get_size();
  }
  
  const bitvector& get_value() const { 
    this->sync_sources();
    return value_;
  }
  
  bitvector& get_value() {
    this->sync_sources();
    return value_;
  }
  
protected:
  
  uint64_t sync_sources() const;
  
  void merge_left(uint32_t idx);
  
  struct source_t {
    snodeimpl* node;
    uint32_t start;    
    uint32_t offset;    
    uint32_t length;
    uint64_t changeid;
  };
  
  mutable std::vector<source_t> srcs_;
  mutable bitvector value_;
  mutable uint64_t  changeid_;
  snode* owner_;
  uint32_t id_;
};

}
