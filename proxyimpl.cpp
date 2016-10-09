#include "proxyimpl.h"
#include "context.h"

using namespace std;
using namespace chdl_internal;

proxyimpl::proxyimpl(context* ctx, uint32_t size) 
  : lnodeimpl("proxy", ctx, size)
  , m_ctime(~0ull) {
  lnode node(new undefimpl(ctx, size));
  m_srcs.emplace_back(node);
  m_ranges.push_back({0, 0, size});    
}

proxyimpl::~proxyimpl() {
  //--
}

void proxyimpl::add_src(uint32_t dst_offset, const lnode& src, uint32_t src_offset, uint32_t src_length) {  
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
  if (delta > 0) {
    if (end > start) {
      // resize end range
      range_t& r = m_ranges[end];
      r.offset += delta;
      r.length -= delta;
    } else {
      // split curr range
      assert(end == start);
      ++end;
      range_t r_new = m_ranges[start];      
      r_new.offset += delta;
      r_new.length -= delta;
      m_ranges.insert(m_ranges.begin() + end, r_new); 
    }
  }
  
  if (dst_offset > start_offset) {
    // split curr range
    m_ranges[start].length = dst_offset - start_offset;
    ++start; ++end;    
    range_t r_new = {src_idx, src_offset, src_length};
    m_ranges.insert(m_ranges.begin() + start, r_new);    
  } else {   
    // split range end
    assert(dst_offset == start_offset);
    // replace curr range
    if (delta == 0 || end != start) {
      deleted.insert(m_ranges[start].src);       
    }
    range_t& r = m_ranges[start];
    r.src    = src_idx;
    r.offset = src_offset;
    r.length = src_length;
  }

  // remove overlapped ranges
  for (int i = end - 1; i > start; --i) {
    range_t& r = m_ranges[i];
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
  out << "#" << m_id << " <- " << m_name << m_value.get_size();
  out << "(";
  for (uint32_t i = 0, n = m_ranges.size(); i < n; ++i) {
    const range_t& range = m_ranges[i];
    if (i > 0)
      out << ", ";
    out << "#" << m_srcs[range.src].get_id() << "{" << range.offset;
    if (range.length > 1)
      out << "-" << range.offset + (range.length - 1);
    out << "}";
  }
  out << ")" << endl;
}

void proxyimpl::print_vl(std::ostream& out) const {
  TODO("Not yet implemented!");
}
