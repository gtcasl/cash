#include "proxyimpl.h"
#include "context.h"

using namespace cash::internal;

proxyimpl::proxyimpl(context* ctx, uint32_t size) 
  : lnodeimpl(op_proxy, ctx, size)
  , ctime_(~0ull) 
{}

proxyimpl::proxyimpl(const lnode& src)
  : lnodeimpl(op_proxy, src.get_ctx(), src.get_size())
  , ctime_(~0ull)  {
  this->add_source(0, src, 0, src.get_size());
}

proxyimpl::proxyimpl(const lnode& src, uint32_t offset, uint32_t length)
  : lnodeimpl(op_proxy, src.get_ctx(), length)
  , ctime_(~0ull)  {
  this->add_source(0, src, offset, length);
}

void proxyimpl::add_source(uint32_t dst_offset,
                           const lnode& src,
                           uint32_t src_offset,
                           uint32_t length) {
  assert(this != src.get_impl());
  assert(length != 0);
  assert(dst_offset + length <= value_.get_size());
  assert(src_offset + length <= src.get_size());

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
  
  auto merge_prev_range = [&](uint32_t idx)->bool {
    assert(idx > 0);
    if (ranges_[idx-1].src_idx == ranges_[idx].src_idx
     && (ranges_[idx-1].dst_offset + ranges_[idx-1].length) == ranges_[idx].dst_offset
     && ranges_[idx].src_offset == ranges_[idx-1].src_offset + ranges_[idx-1].length) {
      ranges_[idx-1].length += ranges_[idx].length;
      ranges_.erase(ranges_.begin() + idx);
      return true;
    }
    return false;
  };

  uint32_t n = ranges_.size();
  if (0 == n) {
    // insert the first entry
    ranges_.push_back({new_srcidx, dst_offset, src_offset, length});
  } else {
    // find the slot to insert source node,
    // split existing nodes if needed
    std::set<uint32_t> deleted; // use ordered set for index ordering
    uint32_t i = 0;
    for (; length && i < n; ++i) {
      range_t& curr = ranges_[i];
      uint32_t curr_end = curr.dst_offset + curr.length;
      uint32_t src_end  = dst_offset + length;
      range_t new_range{new_srcidx, dst_offset, src_offset, length};
      
      // do ranges overlap?
      if (dst_offset < curr_end && src_end > curr.dst_offset) {
        if (dst_offset <= curr.dst_offset && src_end >= curr_end) {
          // source fully overlaps, replace current node
          uint32_t delta = curr_end - dst_offset;
          new_range.length = delta;
          if (new_range != curr) {
            deleted.emplace(curr.src_idx);
            curr = new_range;
          }
          dst_offset += delta;
          src_offset += delta;
          length -= delta;
        } else if (dst_offset < curr.dst_offset) {
          // source overlaps on the left,
          // replace left size of the current node
          uint32_t delta = src_end - curr.dst_offset;
          curr.dst_offset += delta;
          curr.src_offset += delta;
          curr.length -= delta;

          ranges_.insert(ranges_.begin() + i, new_range);
          ++n;

          length = 0;
        } else if (src_end > curr_end) {
          // source overlaps on the right,
          // replace right size of the current node
          uint32_t delta = curr_end - dst_offset;
          curr.length -= delta;
          
          new_range.length = delta;
          
          ++i; 
          ranges_.insert(ranges_.begin() + i, new_range);
          ++n;       
          
          dst_offset += delta;
          src_offset += delta;
          length -= delta;
        } else {
          // source fully included,
          // we need to split current node into two chunks
          uint32_t delta = src_end - curr.dst_offset;
          range_t curr_after(curr);          
          curr_after.length -= delta;
          curr_after.dst_offset += delta;
          curr_after.src_offset += delta;
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
          length = 0;
        }
      } else if (i+1 == n || src_end <= ranges_[i+1].dst_offset) {
        // no overlap with current and next
        i += (curr_end <= dst_offset) ? 1 : 0;
        ranges_.insert(ranges_.begin() + i, new_range);       
        ++n;
        
        length = 0;
      } else {
        // no overlap with current,
        // skip merge if no update took place
        continue;
      } 
      
      if (i > 0) {
        // try merging with previous range
        if (merge_prev_range(i)) {
          --i;
          --n;
        }
      }       
    }

    assert(0 == length);
    if (i < n) {
      // try merging with previous range
      merge_prev_range(i);
    }
    
    // cleanup deleted nodes
    // tranverse the set in reverse order to process higher indices first
    for (auto it = deleted.rbegin(), end = deleted.rend(); it != end; ++it) {
      uint32_t idx = *it;
      bool in_use = false;
      // ensure that it is not in use
      for (const range_t& r : ranges_) {
        if (r.src_idx == idx) {
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
    if (ranges_[i].src_idx == idx) {
      ranges_.erase(ranges_.begin() + i);
      --i;
      --n;
    } else
    if (ranges_[i].src_idx > idx) {
      ranges_[i].src_idx -= 1;
    }
  }

  return next;
}

lnodeimpl* proxyimpl::get_slice(uint32_t offset, uint32_t length) {
  assert(length <= value_.get_size());

  // check for matching source
  if (1 == ranges_.size()) {
    auto& range = ranges_[0];
    if (range.length == length
     && range.src_offset == 0
     && range.dst_offset == offset
     && srcs_[range.src_idx].get_size() == length) {
      return srcs_[range.src_idx].get_impl();
    }
  }

  // return new slice
  auto proxy = new proxyimpl(ctx_, length);
  for (auto& r : ranges_) {
    uint32_t r_end = r.dst_offset + r.length;
    uint32_t src_end = offset + length;
    if (offset < r_end && src_end > r.dst_offset) {
      uint32_t sub_start = std::max(offset, r.dst_offset);
      uint32_t sub_end = std::min(src_end, r_end);
      uint32_t dst_offset = sub_start - offset;
      uint32_t src_offset = r.src_offset + (sub_start - r.dst_offset);
      proxy->add_source(dst_offset, srcs_[r.src_idx], src_offset, sub_end - sub_start);
    }
  }

  return proxy;
}

std::vector<std::pair<uint32_t, uint32_t>>
proxyimpl::get_update_slices(uint32_t offset, uint32_t length) {
  std::vector<std::pair<uint32_t, uint32_t>> ret;

  uint32_t n = ranges_.size();
  if (0 == n) {
    ret.emplace_back(offset, length);
  } else {
    uint32_t i = 0;
    for (; length && i < n; ++i) {
      range_t& curr = ranges_[i];
      uint32_t curr_end = curr.dst_offset + curr.length;
      uint32_t src_end  = offset + length;

      // do ranges overlap?
      if (offset < curr_end && src_end > curr.dst_offset) {
        if (offset <= curr.dst_offset && src_end >= curr_end) {
          // source fully overlaps
          uint32_t delta = curr_end - offset;
          ret.emplace_back(offset, delta);
          offset += delta;
          length -= delta;
        } else if (offset < curr.dst_offset) {
          // source overlaps on the left
          uint32_t delta = curr.dst_offset - offset;
          ret.emplace_back(offset, delta);
          length -= delta;
          offset += delta;
        } else if (src_end > curr_end) {
          // source overlaps on the right
          uint32_t delta = curr_end - offset;
          ret.emplace_back(offset, delta);
          offset += delta;
          length -= delta;
        } else {
          // source fully included,
          ret.emplace_back(offset, length);
          length = 0;
        }
      } else if (i+1 == n || src_end <= ranges_[i+1].dst_offset) {
        // no overlap with current and next
        ret.emplace_back(offset, length);
        length = 0;
      } else {
        // no overlap with current
        continue;
      }
    }
    assert(0 == length);
  }

  return ret;
}

const bitvector& proxyimpl::eval(ch_cycle t) {
  if (ctime_ != t) {  
    ctime_ = t;    
    for (const range_t& range : ranges_) {
      const bitvector& bits = srcs_[range.src_idx].eval(t);
      value_.copy(range.dst_offset, bits, range.src_offset, range.length);
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
    if (s != range.dst_offset) {
      s = range.dst_offset;
      out << range.dst_offset << ":";
    }
    s += range.length;
    out << "#" << srcs_[range.src_idx].get_id() << "{" << range.src_offset;
    if (range.length > 1)
      out << "-" << range.src_offset + (range.length - 1);
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
