#include "proxyimpl.h"
#include "context.h"

using namespace std;
using namespace chdl_internal;

proxyimpl::proxyimpl(context* ctx, uint32_t size) 
  : lnodeimpl(op_proxy, ctx, size)
  , m_ctime(~0ull) 
{}

void proxyimpl::add_node(uint32_t start, lnodeimpl* src, uint32_t offset, uint32_t length, bool resize) {    
  // add new source
  uint32_t new_srcidx = -1;
  for (uint32_t i = 0, n = m_srcs.size(); i < n; ++i) {
    if (m_srcs[i].get_id() == src->get_id()) {
      new_srcidx = i;
      break;
    }
  }
  if (new_srcidx == -1) {
    new_srcidx = m_srcs.size();    
    m_srcs.emplace_back(src);    
  }
  
  uint32_t n = m_ranges.size();
  if (n > 0) {    
    set<uint32_t> deleted;    
    uint32_t i = 0;
    for (; length && i < n; ++i) {
      range_t& curr = m_ranges[i];      
      lnodeimpl* curr_impl = m_srcs[curr.srcidx].get_impl();
      uint32_t curr_end = curr.start + curr.length;     
      uint32_t src_end  = start + length;
      range_t new_range = { new_srcidx, start, offset, length };
      
      // do ranges intersect?
      if ((start < curr_end && src_end > curr.start)) {
        if (start <= curr.start && src_end >= curr_end) {
          // source fully overlaps
          deleted.emplace(curr.srcidx);                  
          uint32_t len = curr_end - start;                    
          new_range.length = len; 
          curr = new_range;           
          start  += len;        
          offset += len;        
          length -= len;        
        } else if (src_end > curr_end) {
          assert(!resize); // should not hit
          // source intersets right
          uint32_t overlap = curr_end - start;
          curr.length -= overlap;          
          
          new_range.length = overlap;
          
          ++i; 
          m_ranges.insert(m_ranges.begin() + i, new_range);
          ++n;       
          
          start  += overlap;
          offset += overlap;
          length -= overlap;
        } else {
          assert(!(start < curr.start)); // left intersections should not exit
          // source fully included          
          uint32_t delta = src_end - curr.start;
          range_t curr_after(curr);          
          curr_after.length -= delta;
          curr_after.start  += delta;
          curr_after.offset += delta;          
          curr.length -= (curr_end - start);
          
          if (resize) {
            curr_impl->get_value().resize(curr.length + curr_after.length);
            curr_after.offset = curr.length;            
          }
          
          if (curr.length > 0) {
            ++i;
            m_ranges.insert(m_ranges.begin() + i, 1, new_range);
            ++n;
          } else {
            curr = new_range;
          }          
          
          if (curr_after.length) {                              
            m_ranges.insert(m_ranges.begin() + (i+1), 1, curr_after); 
            ++n;
          }         
          length = 0;
        }
      } else if (i+1 == n || src_end <= m_ranges[i+1].start) {
        // no overlap with current and next
        i += (curr_end <= start) ? 1 : 0;
        m_ranges.insert(m_ranges.begin() + i, new_range);       
        ++n;
        
        length = 0;
      } else {
        // no overlap with current, skip merge if no update took place
        continue;
      } 
      
      if (i > 0) {
        // try merging inserted node on the left
        this->merge_left(i);
      }       
    }
    assert(length == 0);    
    if (i < n) {
      // try merging inserted node on the right
      this->merge_left(i);
    }
    
    // cleanup deleted nodes
    for (uint32_t srcidx : deleted) {
      bool in_use = false;
      // ensure that it is not in use 
      for (uint32_t i = 0, n = m_ranges.size(); i < n; ++i) {
        if (m_ranges[i].srcidx == srcidx) {
          in_use = true;
          break;
        }          
      }      
      if (!in_use) {
        // remove src     
        m_srcs.erase(m_srcs.begin() + srcidx);
        
        // update references due to vector resizing
        for (uint32_t i = 0, n = m_ranges.size(); i < n; ++i) {
          range_t& r = m_ranges[i];
          if (r.srcidx > srcidx) {
            r.srcidx -= 1;
          }
        }
      }
    }    
  } else {
    m_ranges.push_back({ new_srcidx, start, offset, length });
  }
}

void proxyimpl::merge_left(uint32_t idx) {
  assert(idx > 0);
  if (m_ranges[idx-1].srcidx == m_ranges[idx].srcidx && 
      (m_ranges[idx-1].start + m_ranges[idx-1].length) == m_ranges[idx].start &&
      m_ranges[idx].offset == m_ranges[idx-1].offset + m_ranges[idx-1].length) {
    m_ranges[idx-1].length += m_ranges[idx].length;
    m_ranges.erase(m_ranges.begin() + idx);
  }      
}

void proxyimpl::replace_undefs(uint32_t start, lnodeimpl* src, uint32_t offset, uint32_t length) {
  for (uint32_t i = 0, n = m_ranges.size(); length && i < n; ++i) {
    const range_t& curr = m_ranges[i];
    lnodeimpl* curr_impl = m_srcs[curr.srcidx].get_impl();
    uint32_t curr_end = curr.start + curr.length;     
    uint32_t src_end  = start + length;    
    if ((start < curr_end && src_end > curr.start)) {      
      if (start <= curr.start && src_end >= curr_end) {
        // source fully overlaps
        uint32_t delta = curr.start - start;        
        curr_impl->replace_undefs(curr.offset, src, offset + delta, curr.length);        
        uint32_t step = curr_end - start;
        start  += step;        
        offset += step;        
        length -= step;        
      } else if (src_end > curr_end) {
        // source intersets right
        uint32_t overlap = curr_end - start;        
        uint32_t delta = start - curr.start;
        curr_impl->replace_undefs(curr.offset + delta, src, offset, overlap);        
        start  += overlap;
        offset += overlap;
        length -= overlap;
      } else {
        assert(!(start < curr.start)); // left intersections should not exit
        // source fully included          
        uint32_t delta = start - curr.start;        
        curr_impl->replace_undefs(curr.offset + delta, src, offset, length);
        length = 0;
      }
    }
  }
}

void proxyimpl::resize(uint32_t start, uint32_t length) {  
  assert(start + length <= this->get_size());
  
  for (uint32_t i = 0, n = m_ranges.size(); length && i < n; ++i) {
    const range_t& curr = m_ranges[i];
    uint32_t src_end  = start + length;
    uint32_t curr_end = curr.start + curr.length;  
    
    if ((start < curr_end && src_end > curr.start)) {      
      if (start < curr.start) {
        // source extrudes left
        uint32_t len = curr.start - start;           
        uint32_t srcidx = m_srcs.size();
        m_ranges.insert(m_ranges.begin() + i, { srcidx, start, 0, len });
        m_srcs.emplace_back(new undefimpl(m_ctx, len));
        ++i;
        ++n;
        uint32_t overlap = curr_end - start;
        start  += overlap;       
        length -= overlap;    
      } else if (src_end > curr_end) {
        // source extrudes right
        uint32_t overlap = curr_end - start;
        start  += overlap;    
        length -= overlap;
      }
    }
  }
  if (length) {        
    uint32_t srcidx = m_srcs.size();
    m_ranges.push_back({ srcidx, start, 0, length });
    m_srcs.emplace_back(new undefimpl(m_ctx, length));   
  }
}

bool proxyimpl::includes(uint32_t start, uint32_t length) const {
  for (const range_t& curr : m_ranges) {
    uint32_t src_end  = start + length;
    uint32_t curr_end = curr.start + curr.length;   
    if ((start < curr_end && src_end > curr.start)) {      
      if (start < curr.start) {
        // source extrudes left
        return false;
      } else if (src_end > curr_end) {
        // source extrudes right
        uint32_t overlap = curr_end - start;
        start  += overlap;
        length -= overlap;
      } else {
        // source fully included        
        return true;
      }
    }
  }
  return false;
}

bool proxyimpl::is_slice() const {
  uint32_t actual_size = 0;
  for (const range_t& curr : m_ranges) {
    actual_size += curr.length;
  }
  return actual_size != this->get_size(); 
}

const bitvector& proxyimpl::eval(ch_cycle t) {
  if (m_ctime != t) {  
    m_ctime = t;
    
    for (const range_t& range : m_ranges) {
      const bitvector& bits = m_srcs[range.srcidx].eval(t);    
      m_value.copy(range.start, bits, range.offset, range.length);
    }
  }  
  return m_value;
}

void proxyimpl::print(std::ostream& out) const {
  out << "#" << m_id << " <- " << this->get_name() << m_value.get_size();
  out << "(";
  for (uint32_t i = 0, s = 0, n = m_ranges.size(); i < n; ++i) {
    const range_t& range = m_ranges[i];
    if (i > 0)
      out << ", ";
    if (s != range.start) {
      s = range.start;
      out << range.start << ":";  
    }
    s += range.length;
    out << "#" << m_srcs[range.srcidx].get_id() << "{" << range.offset;
    if (range.length > 1)
      out << "-" << range.offset + (range.length - 1);
    out << "}";
  }
  out << ")";
}

// LCOV_EXCL_START
void proxyimpl::print_vl(std::ostream& out) const {
  TODO("Not yet implemented!");
}
// LCOV_EXCL_END
