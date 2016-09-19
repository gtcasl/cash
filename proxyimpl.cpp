#include "proxyimpl.h"
#include "context.h"

using namespace std;
using namespace chdl_internal;

proxyimpl::proxyimpl(const ch_node& node) 
  : nodeimpl(node.get_ctx(), node.get_size())
  , m_ctime(~0ull) {
  m_srcs.emplace_back(node);
  m_ranges.push_back({0, 0, m_value.get_size()});    
}

proxyimpl::~proxyimpl() {
  //--
}

void proxyimpl::add_src(uint32_t dst_offset, const ch_node& src, uint32_t src_offset, uint32_t src_length) {  
  uint32_t src_idx = -1;
  uint32_t offset  = 0;  
  set<uint32_t> deleted;
  
  unsigned src_end = dst_offset + src_length;
  
  // update sources
  for (uint32_t i = 0, n = m_srcs.size(); i < n; ++i) {
    if (m_srcs[i].get_id() == src.get_id()) {
      src_idx = i;
      break;
    }
  }
  if (src_idx == -1) {
    src_idx = m_srcs.size();    
    m_srcs.push_back(src);    
  }
  
  uint32_t start = 0; 
  
  // skip non-intersecting ranges  
  for (uint32_t n = m_ranges.size(); start < n; ++start) {
    range_t& r = m_ranges[start];        
    if (offset + r.length > dst_offset)      
      break;
    offset += r.length;
  }
  
  uint32_t start_offset = offset;
  uint32_t end = start;
        
  // skip overlapped ranges    
  for (uint32_t n = m_ranges.size(); end < n; ++end) {
    range_t& r = m_ranges[end];
    if (offset + r.length > src_end)
      break;        
    offset += r.length;
  }
  
  uint32_t delta = src_end - offset;
  
  if (dst_offset > start_offset) {
    // split range start       
    ++start; ++end;    
    range_t r_new = {src_idx, src_offset, src_length};
    m_ranges.insert(m_ranges.begin() + start, r_new);   
    
    // split range end
    if (end == start && delta > 0) {     
      ++end;
      range_t r_new = m_ranges[start-1];      
      r_new.offset += delta;
      r_new.length -= delta;
      m_ranges.insert(m_ranges.begin() + end, r_new); 
      delta = 0;
    }
      
    // update first partition length
    m_ranges[start-1].length = delta - src_length;
  } else {                   
    // split range end
    if (end == start && delta > 0) {      
      ++end;      
      range_t r_new = m_ranges[start];
      r_new.offset += delta;
      r_new.length -= delta;
      m_ranges.insert(m_ranges.begin() + end, r_new);
      delta = 0;
    } else {
      range_t& r = m_ranges[start];
      deleted.insert(r.src);
    }
    
    // reuse start range
    range_t& r = m_ranges[start];
    r.src    = src_idx;
    r.offset = src_offset;
    r.length = src_length;
  }
  
  if (end > start && delta > 0) {    
    // resize last range
    range_t& r = m_ranges[end];
    r.offset += delta;
    r.length -= delta;
  } 

  // remove overlapped ranges
  for (uint32_t i = end - 1; i > start; --i) {
    range_t& r = m_ranges[i];
    if (r.src != src_idx)    
      deleted.insert(r.src);     
    m_ranges.erase(m_ranges.begin() + i);
  }
  
  // delete replaced src's
  for (auto src : deleted) {
    bool found = false;
    for (uint32_t i = 0, n = m_ranges.size(); i < n; ++i) {
      if (m_ranges[i].src == src) {
        found = true;
        break;
      }          
    }      
    if (!found) {
      // remove src      
      m_srcs.erase(m_srcs.begin() + src);
      
      // update references
      for (uint32_t i = 0, n = m_ranges.size(); i < n; ++i) {
        range_t& r = m_ranges[i];
        if (r.src > src) {
          r.src -= 1;
        }
      }
    }
  }
}

const bitvector& proxyimpl::eval(ch_cycle t) {
  if (m_ctime != t) {  
    m_ctime = t;
    
    uint32_t offset = 0;
    for (auto& range : m_ranges) {
      const bitvector& bits = m_srcs[range.src].eval(t);    
      m_value.copy(offset, bits, range.offset, range.length);
      offset += range.length;
    }
  }  
  return m_value;
}

void proxyimpl::print(std::ostream& out) const {
  TODO();
}

void proxyimpl::print_vl(std::ostream& out) const {
  TODO();
}
