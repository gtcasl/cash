#include "snodeimpl.h"
#include "ioimpl.h"
#include "bus.h"

using namespace std;
using namespace cash::detail;

static uint32_t generate_id() {
  static uint32_t s_id(0);
  return ++s_id;
}

snodeimpl::snodeimpl(uint32_t size) 
  : id_(generate_id())
  , value_(size)
  , changeid_(0) 
  , owner_(nullptr)
{}

snodeimpl::snodeimpl(const bitvector& value)
  : id_(generate_id())
  , value_(value)
  , changeid_(1) // value_ has been set
  , owner_(nullptr)
{}

snodeimpl::~snodeimpl() {
  assert(nullptr == owner_);
  for (auto& src : srcs_) {
    assert(src.node);
    src.node->release();
  }
}

void snodeimpl::assign(uint32_t start, snodeimpl* src, uint32_t offset, uint32_t length) {
  assert(src != nullptr && this != src);    
  
  uint32_t n = srcs_.size();
  if (n > 0) {
    uint32_t i = 0;
    for (; length && i < n; ++i) {
      source_t& curr = srcs_[i];
      uint32_t src_end  = start + length;
      uint32_t curr_end = curr.start + curr.length;
      
      source_t new_src = { src, start, offset, length, 0 };
      
      // do ranges intersect?
      if ((start < curr_end && src_end > curr.start)) {
        if (start <= curr.start && src_end >= curr_end) {
          // source fully overlaps
          uint32_t len = curr_end - start;
          new_src.length = len;
          src->acquire();
          curr.node->release();          
          curr = new_src;
          
          start  += len;        
          offset += len;        
          length -= len;  
        } else if (start < curr.start) {
          // source intersets left
          uint32_t overlap = src_end - curr.start;
          curr.start  += overlap;
          curr.offset += overlap;
          curr.length -= overlap;
          
          src->acquire();
          srcs_.insert(srcs_.begin() + i, new_src);
          ++n;
          
          length = 0;  
        } else if (src_end > curr_end) {
          // source intersets right
          uint32_t overlap = curr_end - start;
          curr.length -= overlap;
          
          new_src.length = overlap;
          
          ++i;
          src->acquire();
          srcs_.insert(srcs_.begin() + i, new_src); 
          ++n;       
          
          start  += overlap;
          offset += overlap;
          length -= overlap;
        } else {
          // source fully included          
          uint32_t delta = src_end - curr.start;
          source_t curr_after(curr);          
          curr_after.length -= delta;
          curr_after.start  += delta;
          curr_after.offset += delta;
          
          src->acquire();
          curr.length -= (curr_end - start);
          if (curr.length > 0) {
            ++i;
            srcs_.insert(srcs_.begin() + i, 1, new_src);
            ++n;
          } else {
            curr = new_src;
          }          
          
          if (curr_after.length) {                              
            srcs_.insert(srcs_.begin() + (i+1), 1, curr_after); 
            ++n;
          }         
          length = 0;
        }
      } else if (i+1 == n || src_end <= srcs_[i+1].start) {
        // no overlap with current and next
        i += (curr_end <= start) ? 1 : 0;
        src->acquire();
        srcs_.insert(srcs_.begin() + i, new_src);   
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
    assert(0 == length);
    if (i < n) {
      // try merging inserted node on the right
      this->merge_left(i);
    }
  } else {
    src->acquire();
    srcs_.push_back({ src, start, offset, length, 0 });
  }
}

void snodeimpl::merge_left(uint32_t idx) {
  assert(idx > 0);
  if (srcs_[idx-1].node == srcs_[idx].node && 
      (srcs_[idx-1].start + srcs_[idx-1].length) == srcs_[idx].start &&
      srcs_[idx].offset == srcs_[idx-1].offset + srcs_[idx-1].length) {
    srcs_[idx].node->release();
    srcs_[idx-1].length += srcs_[idx].length;
    srcs_.erase(srcs_.begin() + idx);
  }      
}

uint64_t snodeimpl::sync_sources() const {
  if (!srcs_.empty()) {  
    int changed = 0;
    for (source_t& src : srcs_) {
      uint64_t changeid = src.node->sync_sources();
      if (src.changeid != changeid) {
        src.changeid = changeid;
        value_.copy(src.start, src.node->read(), src.offset, src.length);      
        changed = 1;
      }
    }
    changeid_ += changed;
  }
  return changeid_;
}

///////////////////////////////////////////////////////////////////////////////

snode::snode(const snode& rhs) : impl_(nullptr) {
  this->assign(rhs.impl_); 
}

snode::snode(snode&& rhs) : impl_(nullptr) {  
  this->move(rhs);
}

snode::snode(snodeimpl* impl) : impl_(nullptr) {
  this->assign(impl);
}

snode::snode(const data_type& data) : impl_(nullptr) {
  uint32_t dst_offset = 0;
  for (auto& d : data) {
    this->assign(dst_offset, d.src, d.offset, d.length, data.get_size());
    dst_offset += d.length;
  }
}

snode::snode(const bitvector& value) : impl_(nullptr) {
  this->assign(new snodeimpl(value), true);
}

snode::~snode() {
  if (impl_) {
    impl_->set_owner(nullptr);
    impl_->release();
    impl_ = nullptr;
  }
}

snode& snode::operator=(const snode& rhs) {
  this->assign(rhs.impl_);
  return *this;
}

snode& snode::operator=(snode&& rhs) {
  this->move(rhs);
  return *this;
}

bool snode::operator==(const snode& rhs) const {
  return (impl_->get_value() == rhs.impl_->get_value());
}

bool snode::operator<(const snode& rhs) const {
  return (impl_->get_value() < rhs.impl_->get_value());
}

uint32_t snode::get_size() const {
  return impl_ ? impl_->get_size() : 0;
}

snodeimpl* snode::get_impl() const {
  assert(impl_);
  return impl_;
}

const snode& snode::ensureInitialized(uint32_t size) const {
  if (nullptr == impl_) {
    impl_ = new snodeimpl(size);
    impl_->acquire();
  }
  assert(impl_->get_size() == size);
  return *this;
}

void snode::move(snode& rhs) {  
  assert(impl_ != rhs.impl_);
  impl_ = rhs.impl_;
  rhs.impl_ = nullptr;
}

void snode::assign(const bitvector& value) {
  this->assign(new snodeimpl(value), true);
}

void snode::assign(snodeimpl* impl, bool is_owner) {  
  assert(impl && impl_ != impl);
  impl->acquire();
  if (is_owner)
    impl->set_owner(this);
  if (impl_) {
    impl_->set_owner(nullptr);
    impl_->release();
  }
  impl_ = impl;
}

uint32_t snode::read(uint32_t idx) const {
  assert(impl_);
  return impl_->read(idx);
}

void snode::write(uint32_t idx, uint32_t value) {
  assert(impl_);
  assert(impl_->get_owner() == this);
  impl_->write(idx, value);
}

void snode::read(uint8_t* out, uint32_t sizeInBytes) const {
  impl_->read(out, sizeInBytes);
}

void snode::write(const uint8_t* in, uint32_t sizeInBytes) {
  impl_->write(in, sizeInBytes);
}

void snode::read_data(data_type& inout, uint32_t offset, uint32_t length, uint32_t size) const {
  assert((offset + length) <= size);
  this->ensureInitialized(size);
  inout.push({impl_, offset, length});
}

void snode::write_data(uint32_t dst_offset, const data_type& in, uint32_t src_offset, uint32_t src_length, uint32_t size) {
  assert(in.num_nodes() >= 1);
  assert((dst_offset + src_length) <= size);
  for (auto& d : in) {
    if (src_offset < d.length) {
      size_t len = std::min(d.length - src_offset, src_length);
      this->assign(dst_offset, d.src, d.offset + src_offset, len, size);
      src_length -= len;
      if (0 == src_length)
        return;
      dst_offset += len;                
      src_offset = d.length;
    }
    src_offset -= d.length;
  }
}

void snode::assign(uint32_t dst_offset, snodeimpl* src, uint32_t src_offset, uint32_t src_length, uint32_t size) {
  assert((dst_offset + src_length) <= size);
  // check if full replacement
  if (size == src_length && size == src->get_size()) {
    assert(0 == dst_offset && 0 == src_offset);
    this->assign(src);
  } else {
    // partial assignment
    this->ensureInitialized(size);
    if (impl_->get_owner() != this)
      this->clone(); // clone the data if not owned
    impl_->assign(dst_offset, src, src_offset, src_length);
  }  
}

void snode::clone() {
  // create a new snodeimpl() with impl_ as source node and make current
  snodeimpl* const impl = impl_;
  impl_ = nullptr;
  this->ensureInitialized(impl->get_size());
  impl_->assign(0, impl, 0, impl->get_size());
  impl->release();
}

std::ostream& cash::detail::operator<<(std::ostream& os, const snode& node) {
  return os << node.get_impl()->get_value();
}
