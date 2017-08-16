#include "proxyimpl.h"
#include "context.h"

using namespace std;
using namespace cash::detail;

proxyimpl::proxyimpl(context* ctx, uint32_t size) 
  : lnodeimpl(op_proxy, ctx, size)
  , ctime_(~0ull) 
{}

proxyimpl::proxyimpl(const lnode& src)
  : lnodeimpl(op_proxy, src.get_ctx(), src.get_size())
  , ctime_(~0ull)  {
  this->add_source(0, src, 0, src.get_size());
}

void proxyimpl::add_source(uint32_t dst_offset,
                           const lnode& src,
                           uint32_t src_offset,
                           uint32_t src_length) {
  // add new source
  uint32_t new_srcidx = 0xffffffff;
  for (uint32_t i = 0, n = srcs_.size(); i < n; ++i) {
    if (srcs_[i].get_id() == src.get_id()) {
      new_srcidx = i;
      break;
    }
  }

  if (0xffffffff == new_srcidx) {
    new_srcidx = srcs_.size();    
    srcs_.emplace_back(src);    
  }
  
  uint32_t n = ranges_.size();
  if (0 == n) {
    // insert the first entry
    ranges_.push_back({ new_srcidx, dst_offset, src_offset, src_length });
  } else {
    // find the slot to insert source node,
    // split existing nodes if needed
    set<uint32_t> deleted;    
    uint32_t i = 0;
    for (; src_length && i < n; ++i) {
      range_t& curr = ranges_[i];
      uint32_t curr_end = curr.start + curr.length;     
      uint32_t src_end  = dst_offset + src_length;
      range_t new_range = { new_srcidx, dst_offset, src_offset, src_length };
      
      // do ranges intersect?
      if ((dst_offset < curr_end && src_end > curr.start)) {
        if (dst_offset <= curr.start && src_end >= curr_end) {
          // source fully overlaps, replace current node
          deleted.emplace(curr.srcidx);                  
          uint32_t delta = curr_end - dst_offset;
          new_range.length = delta;
          curr = new_range;           
          dst_offset += delta;
          src_offset += delta;
          src_length -= delta;
        } else if (src_end > curr_end) {
          // source intersets on the right,
          // replace right size of the current node
          uint32_t delta = curr_end - dst_offset;
          curr.length -= delta;
          
          new_range.length = delta;
          
          ++i; 
          ranges_.insert(ranges_.begin() + i, new_range);
          ++n;       
          
          dst_offset += delta;
          src_offset += delta;
          src_length -= delta;
        } else {
          assert(dst_offset >= curr.start); // left intersections should not exit
          // source fully included,
          // we need to split current node into two chunks
          uint32_t delta = src_end - curr.start;
          range_t curr_after(curr);          
          curr_after.length -= delta;
          curr_after.start  += delta;
          curr_after.offset += delta;          
          curr.length -= (curr_end - dst_offset);
          assert(curr.length || curr_after.length);

          if (0 == curr.length) {
            // replace first chunk
            curr = new_range;
          } else {
            // insert source after first chunk
            ++i;
            ranges_.insert(ranges_.begin() + i, 1, new_range);
            ++n;
          }
          
          if (curr_after.length) {
            // insert second chunk after source
            ranges_.insert(ranges_.begin() + (i+1), 1, curr_after); 
            ++n;
          }         
          src_length = 0;
        }
      } else if (i+1 == n || src_end <= ranges_[i+1].start) {
        // no overlap with current and next
        i += (curr_end <= dst_offset) ? 1 : 0;
        ranges_.insert(ranges_.begin() + i, new_range);       
        ++n;
        
        src_length = 0;
      } else {
        // no overlap with current, skip merge if no update took place
        continue;
      } 
      
      if (i > 0) {
        // try merging inserted node on the left
        this->merge_left(i);
      }       
    }

    if (src_length) {
      // insert the remaining
      ranges_.push_back({ new_srcidx, dst_offset, src_offset, src_length });
      n = ranges_.size();
      i = n - 1;
    }

    if (i < n) {
      // try merging inserted node on the right
      this->merge_left(i);
    }
    
    // cleanup deleted nodes
    // tranverse the set in reverse order
    // to process high indices first
    for (auto iter = deleted.rbegin(), iterEnd = deleted.rend();
         iter != iterEnd; ++iter) {
      uint32_t idx = *iter;
      bool in_use = false;
      // ensure that it is not in use
      for (const range_t& r : ranges_) {
        if (r.srcidx == idx) {
          in_use = true;
          break;
        }
      }
      if (!in_use) {
        this->erase_source(srcs_.begin() + idx);
      }
    }    
  }
}

std::vector<lnode>::iterator
proxyimpl::erase_source(std::vector<lnode>::iterator iter) {
  // remove src
  auto next = srcs_.erase(iter);

  // update ranges
  uint32_t idx = iter - srcs_.begin();
  for (uint32_t i = 0, n = ranges_.size(); i < n; ++i) {
    if (ranges_[i].srcidx == idx) {
      ranges_.erase(ranges_.begin() + i);
      --i;
      --n;
    } else
    if (ranges_[i].srcidx > idx) {
      ranges_[i].srcidx -= 1;
    }
  }

  return next;
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

lnodeimpl* proxyimpl::get_slice(uint32_t offset, uint32_t length) {
  // check if empty
  if (0 == ranges_.size()) {
    return new proxyimpl(ctx_, length);
  }
  // check for matching source
  for (const range_t& r : ranges_) {
    if (r.start == offset && r.length == length) {
      return srcs_[r.srcidx].get_impl();
    }
  }
  // return new slice
  proxyimpl* slice = new proxyimpl(ctx_, length);
  slice->add_source(0, lnode(this), offset, length);
  return slice;
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

void proxyimpl::print(std::ostream& out, uint32_t level) const {
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

  if (level == 2) {
    out << " = " << value_;
  }
}

void proxyimpl::print_vl(std::ostream& out) const {
  CH_UNUSED(out);
  CH_TODO();
}
