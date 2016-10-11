#pragma once

#include "snode.h"

namespace chdl_internal {

class snodeimpl : public refcounted {
public:
  snodeimpl(uint32_t size);
  snodeimpl(const std::string& value);
  snodeimpl(const std::initializer_list<uint32_t>& value, uint32_t size);
  ~snodeimpl();  
  
  uint32_t get_id() const {
    return m_id;
  }
  
  void assign(uint32_t start, snodeimpl* src, uint32_t offset, uint32_t length);

  bitvector::const_reference operator[](uint32_t idx) const {
    this->sync_sources();
    return m_value[idx];
  }
  
  bitvector::reference operator[](uint32_t idx) {
    ++m_changeid;
    this->sync_sources();
    return m_value[idx];
  }
  
  bool to_bool() const {
    this->sync_sources();
    return m_value.to_bool();
  } 
  
  uint32_t read(uint32_t idx) const {
    this->sync_sources();
    return m_value.get_word(idx);
  }
  
  void write(uint32_t idx, uint32_t value) {
    this->sync_sources();
    m_value.set_word(idx, value);
    ++m_changeid;
  }
  
  const bitvector& read() const {
    this->sync_sources();
    return m_value;
  }
  
  void write(const bitvector& value) {
    assert(m_srcs.size() == 0);
    m_value = value;
    ++m_changeid;
  }
  
  uint32_t get_size() const {
    return m_value.get_size();
  }
  
  operator const bitvector&() const { 
    this->sync_sources();
    return m_value; 
  }
  
protected:
  
  void sync_sources() const;
  
  struct source_t {
    snodeimpl* node;
    uint32_t start;    
    uint32_t offset;    
    uint32_t length;
    uint64_t changeid;
  };
  
  mutable std::vector<source_t> m_srcs;
  mutable bitvector m_value;
  mutable uint64_t m_changeid;
  uint32_t m_id;
};

}
