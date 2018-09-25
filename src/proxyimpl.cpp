#include "proxyimpl.h"
#include "context.h"
#include "logic.h"

using namespace ch::internal;

interval_t interval_t::intersection(const interval_t& other) const {
  interval_t ret{0, 0};
  if (!overlaps(other))
    return ret;
  if (other.start <= this->start && other.end >= this->end) {
    // rhs fully overlaps lhs
    ret = *this;
  } else if (other.start < this->start) {
    // rhs overlaps on the left
    ret.start = this->start;
    ret.end = other.end;
  } else if (other.end > this->end) {
    // rhs overlaps on the right,
    ret.start = other.start;
    ret.end = this->end;
  } else {
    // rhs fully included
    ret = other;
  }
  return ret;
}

///////////////////////////////////////////////////////////////////////////////

proxyimpl::proxyimpl(context* ctx,
                     uint32_t size,
                     const source_location& sloc,
                     const std::string& name,
                     uint32_t var_id)
  : lnodeimpl(ctx, type_proxy, size, sloc, name, var_id)
{}

proxyimpl::proxyimpl(context* ctx,
                     const lnode& src,
                     const source_location& sloc,
                     const std::string& name,
                     uint32_t var_id)
  : lnodeimpl(ctx, type_proxy, src.size(), sloc, name, var_id) {
  this->add_source(0, src, 0, src.size());
}

proxyimpl::proxyimpl(context* ctx,
                     const lnode& src,
                     uint32_t offset,
                     uint32_t length,
                     const source_location& sloc,
                     const std::string& name,
                     uint32_t var_id)
  : lnodeimpl(ctx, type_proxy, length, sloc, name, var_id) {
  this->add_source(0, src, offset, length);
}

void proxyimpl::add_source(uint32_t dst_offset,
                           const lnode& src,
                           uint32_t src_offset,
                           uint32_t length) {
  assert(!src.empty());
  assert(this != src.impl());  
  assert(length != 0);
  assert(dst_offset + length <= size_);
  assert(src_offset + length <= src.size());

  // update source location
  if (sloc_.empty()) {
    sloc_ = src.sloc();
  }

  // add new source
  uint32_t new_srcidx = srcs_.size();
  for (uint32_t i = 0, n = srcs_.size(); i < n; ++i) {
    if (srcs_[i].id() == src.id()) {
      new_srcidx = i;
      break;
    }
  }

  if (new_srcidx == srcs_.size()) {
    new_srcidx = this->add_src(src);
  }

  uint32_t n = ranges_.size();
  if (0 == n) {
    // insert the first entry
    ranges_.push_back({new_srcidx, dst_offset, src_offset, length});
  } else {
    // find the slot to insert source node,
    // split existing nodes if needed
    std::set<uint32_t> deleted; // use ordered set for index ordering
    uint32_t i = 0;
    for (; length != 0 && i < n; ++i) {
      auto& curr = ranges_[i];
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
        
        length = 0; // no need to continue
      } else {
        // no overlap with current,
        // skip merge if no update took place
        continue;
      } 
      
      if (i > 0) {
        // try merging with previous range
        if (this->merge_adjacent_ranges(i)) {
          --i;
          --n;
        }
      }       
    }

    assert(0 == length);
    if (i < n) {
      // try merging with previous range
      this->merge_adjacent_ranges(i);
    }
    
    // cleanup deleted nodes
    // tranverse the set in reverse order to process higher indices first
    for (auto it = deleted.rbegin(), end = deleted.rend(); it != end; ++it) {
      uint32_t idx = *it;
      bool in_use = false;
      // ensure that it is not in use
      for (auto& r : ranges_) {
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

bool proxyimpl::merge_adjacent_ranges(uint32_t index) {
  if (index != 0
   && ranges_[index-1].src_idx == ranges_[index].src_idx
   && (ranges_[index-1].dst_offset + ranges_[index-1].length) == ranges_[index].dst_offset
   && ranges_[index].src_offset == ranges_[index-1].src_offset + ranges_[index-1].length) {
    ranges_[index-1].length += ranges_[index].length;
    ranges_.erase(ranges_.begin() + index);
    return true;
  }
  return false;
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

void proxyimpl::write(uint32_t dst_offset,
                      const lnode& src,
                      uint32_t src_offset,
                      uint32_t length,
                      const source_location& sloc) {
  assert(!src.empty());
  assert(size() > dst_offset);
  assert(size() >= dst_offset + length);
  if (ctx_->conditional_enabled(this)) {
    auto src_impl = src.impl();
    if (src_offset != 0 || src.size() != length) {
      src_impl = ctx_->create_node<proxyimpl>(src, src_offset, length, sloc);
    }
    ctx_->conditional_assign(this, dst_offset, length, src_impl, sloc);
  } else {
    this->add_source(dst_offset, src, src_offset, length);
  }
}

bool proxyimpl::equals(const lnodeimpl& other) const {
  if (lnodeimpl::equals(other)) {
    auto _other = reinterpret_cast<const proxyimpl&>(other);
    return (this->ranges_ == _other.ranges_);
  }
  return false;
}

std::size_t proxyimpl::hash() const {
  hash_t ret;
  ret.fields.type = this->type();
  ret.fields.size = this->size();
  auto n = this->srcs().size();  
  if (n > 0) {
    ret.fields.arg0 = this->src(0).id();
    if (n > 1) {
      ret.fields.arg1 = this->src(1).id();
      if (n > 2) {
        ret.fields.op = this->src(2).id();
      }
    }
  }
  return ret.value;
}

lnodeimpl* proxyimpl::slice(uint32_t offset,
                            uint32_t length,
                            const source_location& sloc) {
  assert(length <= size_);

  // return the nested node if the offset/size match
  for (auto& range : ranges_) {
    if (range.length == length
     && range.dst_offset == offset
     && range.src_offset == 0
     && srcs_[range.src_idx].size() == length) {
      return srcs_[range.src_idx].impl();
    }
  }

  // return new slice
  auto proxy = ctx_->create_node<proxyimpl>(length, sloc, name_, var_id_);
  for (auto& range : ranges_) {
    uint32_t r_end = range.dst_offset + range.length;
    uint32_t src_end = offset + length;
    if (offset < r_end && src_end > range.dst_offset) {
      uint32_t sub_start = std::max(offset, range.dst_offset);
      uint32_t sub_end = std::min(src_end, r_end);
      uint32_t dst_offset = sub_start - offset;
      uint32_t src_offset = range.src_offset + (sub_start - range.dst_offset);
      proxy->add_source(dst_offset, srcs_[range.src_idx], src_offset, sub_end - sub_start);
    }
  }

  return proxy;
}

void proxyimpl::print(std::ostream& out) const {
  out << "#" << id_ << " <- " << this->type() << size_;
  out << "(";
  uint32_t s(0);
  auto_separator sep(", ");
  for (auto& range : ranges_) {
    out << sep;
    if (s != range.dst_offset) {
      s = range.dst_offset;
      out << range.dst_offset << ":";
    }
    s += range.length;
    auto& src = srcs_[range.src_idx];
    out << "#" << src.id();
    if (range.length < src.size()) {
      out << "[" << range.src_offset;
      if (range.length > 1) {
        out << "-" << range.src_offset + (range.length - 1);
      }
      out << "]";
    }
  }
  out << ")";
}

///////////////////////////////////////////////////////////////////////////////

refimpl::refimpl(
    context* ctx,
    const lnode& src,
    uint32_t offset,
    uint32_t length,
    const source_location& sloc,
    const std::string& name,
    uint32_t var_id)
  : proxyimpl(ctx, src, offset, length, sloc, name, var_id)
{}

void refimpl::write(
    uint32_t dst_offset,
    const lnode& src,
    uint32_t src_offset,
    uint32_t length,
    const source_location& sloc) {
  assert(1 == srcs_.size());
  assert(0 == ranges_[0].dst_offset);
  assert(length <= ranges_[0].length);
  srcs_[0].impl()->write(
      ranges_[0].src_offset + dst_offset,
      src,
      src_offset,
      length,
      sloc);
}

///////////////////////////////////////////////////////////////////////////////

lnodeimpl* ch::internal::createRotateNode(
    const lnode& next,
    uint32_t dist,
    bool right,
    const source_location& sloc) {
  auto N = next.size();
  auto mod = dist % N;
  auto ret = next.impl()->ctx()->create_node<proxyimpl>(N, sloc);
  if (right) {
    ret->add_source(0, next, mod, N - mod);
    ret->add_source(N - mod, next, 0, mod);
  } else {
    ret->add_source(0, next, N - mod, mod);
    ret->add_source(mod, next, 0, N - mod);
  }
  return ret;
}

lnodeimpl* ch::internal::createShuffleNode(
    const lnode& in,
    const std::vector<unsigned>& indices,
    const source_location& sloc) {
  auto ret = in.impl()->ctx()->create_node<proxyimpl>(in.size(), sloc);
  auto stride = in.size() / indices.size();
  CH_CHECK(stride * indices.size() == in.size(), "invalid size");
  for (unsigned i = 0, n = indices.size(); i < n; ++i) {
    auto j = indices[n - 1 - i];
    CH_CHECK(j < n, "invalid index");
    ret->add_source(i * stride, in, j * stride, stride);
  }
  return ret;
}
