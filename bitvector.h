#pragma once

namespace chdl_internal {

class bitvector {
public:
  
  enum { 
    WORD_SIZE_LOG = 5, 
    WORD_SIZE     = 1 << WORD_SIZE_LOG,
    WORD_MASK     = WORD_SIZE - 1,
  };
  
  bitvector() : m_words(nullptr), m_size(0) {}
  
  bitvector(uint32_t size) : m_size(size) {
    uint32_t num_words = (size + WORD_MASK) >> WORD_SIZE_LOG;
    m_words = new uint32_t[num_words];
  }
  
  ~bitvector() {
    delete [] m_words;
  }
  
  bool get_bit(uint32_t idx) const {
    uint32_t widx = idx >> WORD_SIZE_LOG;
    uint32_t wbit = idx & WORD_MASK;
    uint32_t mask = 1 << wbit;
    return m_words[widx] & mask;
  }
  
  void set_bit(uint32_t idx, bool value ) {
    uint32_t widx = idx >> WORD_SIZE_LOG;
    uint32_t wbit = idx & WORD_MASK;
    uint32_t mask = 1 << wbit;
    if (value)
      m_words[widx] |= mask;
    else
      m_words[widx] &= ~mask;
  }
  
  uint32_t get_word(uint32_t widx) const {
    return m_words[widx];
  }
  
  void set_word(uint32_t widx, uint32_t word) {
    m_words[widx] = word;
  }
  
  uint32_t get_num_words() const {
    return (m_size + WORD_MASK) >> WORD_SIZE_LOG;;
  }
  
  uint32_t get_size() const {
    return m_size;
  }
  
  void copy(uint32_t dst_offset, const bitvector& src, uint32_t src_offset, uint32_t src_length) {
    uint32_t src_widx = src_offset >> WORD_SIZE_LOG;
    uint32_t src_wbit = src_offset & WORD_MASK;
    uint32_t src_bits = src.m_words[src_widx];
    
    uint32_t dst_widx = dst_offset >> WORD_SIZE_LOG;
    uint32_t dst_wbit = dst_offset & WORD_MASK;
    uint32_t* dst_bits = &m_words[dst_widx];
    
    while (src_length--) {
      uint32_t src_mask = 1 << src_wbit;
      uint32_t dst_mask = 1 << dst_wbit;
      if (src_bits & src_mask) {
        *dst_bits |= dst_mask;
      } else {
        *dst_bits &= ~dst_mask;
      }      
      if (++src_wbit == WORD_SIZE) {        
        src_bits = src.m_words[++src_widx];
        src_wbit = 0;
      }      
      if (++dst_wbit == WORD_SIZE) {        
        dst_bits = &m_words[++dst_widx];
        dst_wbit = 0;
      }
    }    
  }
  
protected:
  
  uint32_t* m_words;
  uint32_t m_size;
};

}
