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
  , owner_(nullptr)
  , value_(size)
  , changeid_(0)   
{}

snodeimpl::snodeimpl(const bitvector& value)
  : id_(generate_id())
  , owner_(nullptr)
  , value_(value)
  , changeid_(1) // value_ has been set  
{}

snodeimpl::~snodeimpl() {
  assert(nullptr == owner_);
  for (auto& src : srcs_) {
    assert(src.node);
    src.node->release();
  }
}

void snodeimpl::add_source(uint32_t dst_offset,
                           snodeimpl* src,
                           uint32_t src_offset,
                           uint32_t src_length) {
  assert(src != nullptr && this != src);    
  
  uint32_t n = srcs_.size();
  if (0 == n) {
    // insert the first entry
    src->acquire();
    srcs_.push_back({ src, dst_offset, src_offset, src_length, 0 });
  } else {
    // find the slot to insert source node,
    // split existing nodes if needed
    uint32_t i = 0;
    for (; src_length && i < n; ++i) {
      source_t& curr = srcs_[i];
      uint32_t src_end  = dst_offset + src_length;
      uint32_t curr_end = curr.start + curr.length;      
      source_t new_src = { src, dst_offset, src_offset, src_length, 0 };
      
      // do ranges intersect?
      if ((dst_offset < curr_end && src_end > curr.start)) {
        if (dst_offset <= curr.start && src_end >= curr_end) {
          // source fully overlaps, replace current node
          uint32_t delta = curr_end - dst_offset;
          new_src.length = delta;
          src->acquire();
          curr.node->release();          
          curr = new_src;
          
          dst_offset += delta;
          src_offset += delta;
          src_length -= delta;
        } else if (dst_offset < curr.start) {
          // source intersets on the left,
          // replace left size of the current node
          uint32_t delta = src_end - curr.start;
          curr.start  += delta;
          curr.offset += delta;
          curr.length -= delta;
          
          src->acquire();
          srcs_.insert(srcs_.begin() + i, new_src);
          ++n;
          
          src_length = 0;
        } else if (src_end > curr_end) {
          // source intersets on the right,
          // replace right size of the current node
          uint32_t delta = curr_end - dst_offset;
          curr.length -= delta;
          
          new_src.length = delta;
          
          ++i;
          src->acquire();
          srcs_.insert(srcs_.begin() + i, new_src); 
          ++n;       
          
          dst_offset += delta;
          src_offset += delta;
          src_length -= delta;
        } else {
          // source fully included,
          // we need to split current node into two chunks
          uint32_t delta = src_end - curr.start;
          source_t curr_after(curr);          
          curr_after.length -= delta;
          curr_after.start  += delta;
          curr_after.offset += delta;
          curr.length -= (curr_end - dst_offset);
          assert(curr.length || curr_after.length);
          
          src->acquire();          
          if (0 == curr.length) {
            // replace first chunk
            curr = new_src;
          } else {
            // insert source after first chunk
            ++i;
            srcs_.insert(srcs_.begin() + i, 1, new_src);
            ++n;
          }
          
          if (curr_after.length != 0) {
            // insert second chunk after source
            if (curr.length != 0)
              curr_after.node->acquire();
            srcs_.insert(srcs_.begin() + (i+1), 1, curr_after); 
            ++n;
          }         
          src_length = 0;
        }
      } else if (i+1 == n || src_end <= srcs_[i+1].start) {
        // no overlap with current and next
        i += (curr_end <= dst_offset) ? 1 : 0;
        src->acquire();
        srcs_.insert(srcs_.begin() + i, new_src);   
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
    assert(0 == src_length);
    if (i < n) {
      // try merging inserted node on the right
      this->merge_left(i);
    }
  }
}

void snodeimpl::clear_sources(uint32_t offset, uint32_t length) {
  assert(offset + length <= value_.get_size());

  // remove all sources if full overlap
  if (length == value_.get_size()) {
    for (auto& src : srcs_) {
      assert(src.node);
      src.node->release();
    }
    return;
  }

  for (uint32_t i = 0, n = srcs_.size(); length && i < n; ++i) {
    source_t& curr = srcs_[i];
    uint32_t src_end  = offset + length;
    uint32_t curr_end = curr.start + curr.length;
    // do ranges intersect?
    if ((offset < curr_end && src_end > curr.start)) {
      if (offset <= curr.start && src_end >= curr_end) {
        // source fully overlaps, remove current source
        uint32_t delta = curr_end - offset;
        curr.node->release();
        srcs_.erase(srcs_.begin() + i);
        --n;
        offset += delta;
        length -= delta;
      } else if (offset < curr.start) {
        // source intersets on the left, cut-off left size of current source
        uint32_t delta = src_end - curr.start;
        curr.start  += delta;
        curr.offset += delta;
        curr.length -= delta;
        length = 0;
      } else if (src_end > curr_end) {
        // source intersets on the right, cut-off right size of current source
        uint32_t delta = curr_end - offset;
        curr.length -= delta;
        offset += delta;
        length -= delta;
      } else {
        // source fully included,
        // we need to split current source into two chunks
        uint32_t delta = src_end - curr.start;
        source_t curr_after(curr);
        curr_after.length -= delta;
        curr_after.start  += delta;
        curr_after.offset += delta;
        curr.length -= (curr_end - offset);
        assert(curr.length || curr_after.length);

        if (0 == curr.length) {
          assert(curr_after.length != 0);
          curr = curr_after;
        } else {
          if (curr_after.length != 0) {
            srcs_.insert(srcs_.begin() + (i+1), 1, curr_after);
            ++n;
          }
        }
        length = 0;
      }
    } else if (i+1 == n || src_end <= srcs_[i+1].start) {
      // no overlap with current and next
      length = 0;
    } else {
      // no overlap with current
      continue;
    }
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
    for (const source_t& src : srcs_) {
      uint64_t changeid = src.node->sync_sources();
      if (src.changeid != changeid) {
        src.changeid = changeid;
        value_.copy(src.start, src.node->value_, src.offset, src.length);
        changed = 1;
      }
    }
    changeid_ += changed;
  }
  return changeid_;
}

///////////////////////////////////////////////////////////////////////////////

snode::snode() : impl_(nullptr)
{}

snode::snode(const snode& rhs) : impl_(nullptr)  {
  this->assign(rhs.impl_, false);
}

snode::snode(snode&& rhs) {
  this->move(rhs);
}

snode::snode(snodeimpl* impl) : impl_(nullptr) {
  this->assign(impl, true);
}

snode::snode(const snode& rhs, uint32_t size) : impl_(nullptr) {
  rhs.ensureInitialized(size);
  this->assign(rhs.impl_, false);
}

snode::snode(const data_type& data) : impl_(nullptr) {
  uint32_t dst_offset = 0;
  for (auto& d : data) {
    this->assign(dst_offset, d.src, d.offset, d.length, data.capacity(), false);
    dst_offset += d.length;
  }
}

snode::snode(const bitvector& value) : impl_(nullptr) {
  this->assign(value);
}

snode::~snode() {
  this->clear();
}

void snode::clear() {
  if (impl_) {
    if (impl_->get_owner() == this)
      impl_->set_owner(nullptr); // release ownership
    impl_->release();
    impl_ = nullptr;
  }
}

snode& snode::operator=(const snode& rhs) {
  this->assign(rhs.impl_, false);
  return *this;
}

snode& snode::operator=(snode&& rhs) {
  this->move(rhs);
  return *this;
}

bool snode::is_empty() const {
  return (impl_ != nullptr);
}

bool snode::is_equal(const snode& rhs, uint32_t size) const {
  rhs.ensureInitialized(size);
  this->ensureInitialized(size);
  return (impl_->get_value() == rhs.impl_->get_value());
}

bool snode::is_less(const snode& rhs, uint32_t size) const {
  rhs.ensureInitialized(size);
  this->ensureInitialized(size);
  return (impl_->get_value() < rhs.impl_->get_value());
}

uint32_t snode::get_size() const {
  return impl_ ? impl_->get_size() : 0;
}

uint32_t snode::get_id() const {
  return impl_ ? impl_->get_id() : 0;
}

snodeimpl* snode::get_impl() const {
  assert(impl_);
  return impl_;
}

const bitvector& snode::get_value() const {
  assert(impl_);
  return impl_->get_value();
}

bitvector::const_reference snode::operator[](uint32_t idx) const {
  assert(impl_);
  return impl_->operator [](idx);
}

bitvector::reference snode::operator[](uint32_t idx) {
  assert(impl_);
  return impl_->operator [](idx);
}

void snode::move(snode& rhs) {
  impl_ = rhs.impl_;
  if (impl_->get_owner() == &rhs)
    impl_->set_owner(this); // transfer ownership
  rhs.impl_ = nullptr;
}

void snode::clone(bool keep_data) {
  // create a new snodeimpl() with impl_ as source node and make current
  snodeimpl* const impl = impl_;
  impl_ = nullptr;
  this->ensureInitialized(impl->get_size());
  if (keep_data) {
    impl_->add_source(0, impl, 0, impl->get_size());
  }
  impl->release();
}

void snode::ensureInitialized(uint32_t size) const {
  if (nullptr == impl_) {
    impl_ = new snodeimpl(size);
    impl_->acquire();
    impl_->set_owner(this);
  }
  assert(impl_->get_size() == size);
}

void snode::assign(const snode& rhs, uint32_t size) {
  rhs.ensureInitialized(size);
  this->assign(rhs.impl_, false);
}

void snode::assign(const bitvector& value) {
  if (nullptr == impl_) {
    this->ensureInitialized(value.get_size());
  } else {
    if (impl_->get_owner() != this) {
      this->clone(false);
    } else {
      impl_->clear_sources(0, value.get_size());
    }
  }
  impl_->set_value(value);
}

void snode::assign(snodeimpl* impl, bool is_owner) {  
  assert(impl && impl_ != impl);
  // add redirection if my implementation is shared
  if (impl_
   && impl_->get_owner() == this
   && impl_->get_refcount() > 1) {
    impl_->add_source(0, impl, 0, impl->get_size());
  } else {
    impl->acquire();
    if (is_owner)
      impl->set_owner(this);
    if (impl_)
      this->clear();
    impl_ = impl;
  }
}

void snode::assign(uint32_t dst_offset,
                   const snode& src,
                   uint32_t src_offset,
                   uint32_t src_length,
                   uint32_t size,
                   bool is_owner) {
   assert((dst_offset + src_length) <= size);
   // check if full replacement
   if (size == src_length && size == src.get_size()) {
     assert(0 == dst_offset && 0 == src_offset);
     this->assign(src.impl_, is_owner);
   } else {
     // partial assignment
     this->ensureInitialized(size);
     if (impl_->get_owner() != this)
       this->clone(true);
     impl_->add_source(dst_offset, src.impl_, src_offset, src_length);
   }
 }

uint32_t snode::read(uint32_t idx, uint32_t size) const {
  this->ensureInitialized(size);
  return impl_->read(idx);
}

void snode::write(uint32_t idx, uint32_t value, uint32_t size) {
  this->ensureInitialized(size);
  if (impl_->get_owner() != this)
    this->clone(true);
  impl_->clear_sources(idx * 32, 32);
  impl_->write(idx, value);
}

void snode::read(uint8_t* out,
                 uint32_t offset,
                 uint32_t length,
                 uint32_t size) const {
  this->ensureInitialized(size);
  impl_->read(out, offset, length);
}

void snode::write(const uint8_t* in,
                  uint32_t offset,
                  uint32_t length,
                  uint32_t size) {
  this->ensureInitialized(size);
  if (impl_->get_owner() != this)
    this->clone(true);
  impl_->clear_sources(offset, length);
  impl_->write(in, offset, length);
}

void snode::read_data(data_type& inout,
                      uint32_t offset,
                      uint32_t length,
                      uint32_t size) const {
  assert((offset + length) <= size);
  this->ensureInitialized(size);
  inout.push_back({*this, offset, length});
}

void snode::write_data(uint32_t dst_offset,
                       const data_type& in,
                       uint32_t src_offset,
                       uint32_t src_length,
                       uint32_t size) {
  assert((dst_offset + src_length) <= size);
  for (auto& d : in) {
    if (src_offset < d.length) {
      size_t len = std::min(d.length - src_offset, src_length);
      this->assign(dst_offset, d.src, d.offset + src_offset, len, size, false);
      src_length -= len;
      if (0 == src_length)
        return;
      dst_offset += len;                
      src_offset = d.length;
    }
    src_offset -= d.length;
  }
}

std::ostream& cash::detail::operator<<(std::ostream& os, const snode& node) {
  return os << node.get_value();
}
