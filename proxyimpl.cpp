#include "proxyimpl.h"
#include "context.h"

using namespace std;
using namespace cash_internal;

proxyimpl::proxyimpl(context* ctx, uint32_t size) 
  : lnodeimpl(op_proxy, ctx, size)
  , ctime_(~0ull) 
{}

void proxyimpl::add_node(uint32_t start, const lnode& src, uint32_t offset, uint32_t length, bool resize) {    
  // add new source
  uint32_t new_srcidx = -1;
  for (uint32_t i = 0, n = srcs_.size(); i < n; ++i) {
    if (srcs_[i].get_id() == src.get_id()) {
      new_srcidx = i;
      break;
    }
  }
  if (new_srcidx == -1) {
    new_srcidx = srcs_.size();    
    srcs_.emplace_back(src);    
  }
  
  uint32_t n = ranges_.size();
  if (n > 0) {    
    set<uint32_t> deleted;    
    uint32_t i = 0;
    for (; length && i < n; ++i) {
      range_t& curr = ranges_[i];      
      lnodeimpl* curr_impl = srcs_[curr.srcidx].get_impl();
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
          ranges_.insert(ranges_.begin() + i, new_range);
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
            ranges_.insert(ranges_.begin() + i, 1, new_range);
            ++n;
          } else {
            curr = new_range;
          }          
          
          if (curr_after.length) {                              
            ranges_.insert(ranges_.begin() + (i+1), 1, curr_after); 
            ++n;
          }         
          length = 0;
        }
      } else if (i+1 == n || src_end <= ranges_[i+1].start) {
        // no overlap with current and next
        i += (curr_end <= start) ? 1 : 0;
        ranges_.insert(ranges_.begin() + i, new_range);       
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
      for (uint32_t i = 0, n = ranges_.size(); i < n; ++i) {
        if (ranges_[i].srcidx == srcidx) {
          in_use = true;
          break;
        }          
      }      
      if (!in_use) {
        // remove src     
        srcs_.erase(srcs_.begin() + srcidx);
        
        // update references due to vector resizing
        for (uint32_t i = 0, n = ranges_.size(); i < n; ++i) {
          range_t& r = ranges_[i];
          if (r.srcidx > srcidx) {
            r.srcidx -= 1;
          }
        }
      }
    }    
  } else {
    ranges_.push_back({ new_srcidx, start, offset, length });
  }
}

void proxyimpl::merge_left(uint32_t idx) {
  assert(idx > 0);
  if (ranges_[idx-1].srcidx == ranges_[idx].srcidx && 
      (ranges_[idx-1].start + ranges_[idx-1].length) == ranges_[idx].start &&
      ranges_[idx].offset == ranges_[idx-1].offset + ranges_[idx-1].length) {
    ranges_[idx-1].length += ranges_[idx].length;
    ranges_.erase(ranges_.begin() + idx);
  }      
}

const bitvector& proxyimpl::eval(ch_cycle t) {
  if (ctime_ != t) {  
    ctime_ = t;    
    for (const range_t& range : ranges_) {
      const bitvector& bits = srcs_[range.srcidx].eval(t);    
      value_.copy(range.start, bits, range.offset, range.length);
    }
  }  
  return value_;
}

void proxyimpl::print(std::ostream& out) const {
  out << "#" << id_ << " <- " << this->get_name() << value_.get_size();
  out << "(";
  for (uint32_t i = 0, s = 0, n = ranges_.size(); i < n; ++i) {
    const range_t& range = ranges_[i];
    if (i > 0)
      out << ", ";
    if (s != range.start) {
      s = range.start;
      out << range.start << ":";  
    }
    s += range.length;
    out << "#" << srcs_[range.srcidx].get_id() << "{" << range.offset;
    if (range.length > 1)
      out << "-" << range.offset + (range.length - 1);
    out << "}";
  }
  out << ")";
}

void proxyimpl::print_vl(std::ostream& out) const {
  TODO("Not yet implemented!");
}
