#pragma once

#include "lnode.h"
#include "snode.h"

namespace chdl_internal {

class ioimpl;

class snodeimpl : public refcounted {
public:
  snodeimpl(uint32_t size);
  snodeimpl(ioimpl* output);
  snodeimpl(const std::string& value);
  snodeimpl(const std::initializer_list<uint32_t>& value, uint32_t size);
  ~snodeimpl();  
  
  uint32_t get_id() const {
    return m_id;
  }
  
  void assign(uint32_t start, snodeimpl* src, uint32_t offset, uint32_t length);

  const bitvector& eval(ch_cycle t);
   
  bitvector::const_reference operator[](uint32_t idx) const {
    return m_value[idx];
  }
  
  bitvector::reference operator[](uint32_t idx) {
    return m_value[idx];
  }
  
  uint32_t read(uint32_t idx) const {
    return m_value.get_word(idx);
  }
  
  void write(uint32_t idx, uint32_t value) {
    m_value.set_word(idx, value);
  }
  
  uint32_t get_size() const {
    return m_value.get_size();
  }
  
  context* get_ctx() const;
  
  operator const bitvector&() const { 
    return m_value; 
  }
  
protected:
  
  struct source_t {
    snodeimpl* node;
    uint32_t start;    
    uint32_t offset;    
    uint32_t length;
  };
  
  std::vector<source_t> m_srcs;
  ioimpl*   m_output;
  bitvector m_value;
  ch_cycle  m_ctime;
  uint32_t  m_id;
};

}
