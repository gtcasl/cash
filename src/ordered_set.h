#pragma once

#include "common.h"

namespace ch {
namespace internal {

template<class Key, class Allocator = std::allocator<Key>>
class ordered_set {
protected:

  std::list<Key> list_;
  std::unordered_map<Key, typename std::list<Key>::iterator> map_;

public:

  using value_type = typename std::list<Key>::value_type;
  using size_type = typename std::list<Key>::size_type;
  using difference_type = typename std::list<Key>::difference_type;
  using allocator_type = typename std::list<Key>::allocator_type;
  using reference = typename std::list<Key>::reference;
  using const_reference = typename std::list<Key>::const_reference;
  using pointer = typename std::list<Key>::pointer;
  using const_pointer = typename std::list<Key>::const_pointer;
  using iterator = typename std::list<Key>::iterator;
  using const_iterator = typename std::list<Key>::const_iterator;
  using reverse_iterator = typename std::list<Key>::reverse_iterator;
  using const_reverse_iterator = typename std::list<Key>::const_reverse_iterator;

  explicit ordered_set(const allocator_type& alloc = allocator_type())
    : list_(alloc)
    , map_(alloc)
  {}

  template <class InputIterator>
  ordered_set(InputIterator first, InputIterator last,
              const allocator_type& alloc = allocator_type())
    : ordered_set(alloc) {
    this->insert(first, last);
  }

  ordered_set(const ordered_set& other)
    : list_(other.list_)
    , map_(other.map_)
  {}

  ordered_set(const ordered_set& other, const allocator_type& alloc)
    : list_(other.list_, alloc)
    , map_(other.map_, alloc)
  {}

  ordered_set(ordered_set&& other)
    : list_(std::move(other.list_))
    , map_(std::move(other.map_))
  {}

  ordered_set(ordered_set&& other, const allocator_type& alloc)
    : list_(std::move(other.list_), alloc)
    , map_(std::move(other.map_), alloc)
  {}

  ordered_set(std::initializer_list<value_type> il,
              const allocator_type& alloc = allocator_type())
    : ordered_set(alloc) {
    this->insert(il);
  }

  ordered_set& operator=(const ordered_set& other) {
    list_ = other.list_;
    map_ = other.map_;
    return *this;
  }

  ordered_set& operator=(ordered_set&& other) {
    list_ = std::move(other.list_);
    map_ = std::move(other.map_);
    return *this;
  }

  ordered_set& operator=(std::initializer_list<value_type> il) {
    this->insert(il);
    return *this;
  }

  iterator begin() noexcept {
    return list_.begin();
  }

  const_iterator cbegin() const noexcept {
    return list_.begin();
  }

  iterator end() noexcept {
    return list_.end();
  }

  const_iterator cend() const noexcept {
    return list_.end();
  }

  reverse_iterator rbegin() noexcept {
    return list_.rbegin();
  }

  const_reverse_iterator crbegin() const noexcept {
    return list_.rbegin();
  }

  reverse_iterator rend() noexcept {
    return list_.rend();
  }

  const_reverse_iterator rcend() const noexcept {
    return list_.rend();
  }

  bool empty() const noexcept {
    return list_.empty();
  }

  size_type size() const noexcept {
    return list_.size();
  }

  size_type max_size() const noexcept {
    return list_.max_size();
  }

  iterator insert(const_iterator position, const value_type& val) {
    auto it = map_.find(val);
    if (it != map_.end()) {
      return it->second;
    }
    auto it2 = list_.insert(position, val);
    map_.emplace(val, it2);
    return it2;
  }

  std::pair<iterator, bool> insert(const value_type& val) {
    auto old_size = list_.size();
    auto ret = this->insert(list_.end(), val);
    return std::make_pair(ret, list_.size() != old_size);
  }

  template <class InputIterator>
  void insert(InputIterator first, InputIterator last) {
    for (auto it = first; it != last;) {
      this->insert(*it++);
    }
  }

  void insert(std::initializer_list<value_type> il) {
    for (auto& v : il) {
      this->insert(v);
    }
  }

  iterator erase(const_iterator position) {
    map_.erase(*position);
    auto next = list_.erase(position);
    return next;
  }

  size_type erase(const value_type& val) {
    auto it = map_.find(val);
    if (it == map_.end()) {
      return 0;
    }
    this->erase(it->second);
    return 1;
  }

  iterator erase(const_iterator first, const_iterator last) {
    iterator ret = list_.end();
    for (auto it = first; it != last;) {
      ret = this->erase(it++);
    }
    return ret;
  }

  void swap(ordered_set& other) {
    list_.swap(other.list_);
    map_.swap(other.map_);
  }

  void clear() noexcept {
    list_.clear();
    map_.clear();
  }

  const_iterator find(const value_type& val) const {
    auto it = map_.find(val);
    if (it == map_.end()) {
      return list_.end();
    }
    return it->second;
  }

  iterator find(const value_type& val) {
    auto it = map_.find(val);
    if (it == map_.end()) {
      return list_.end();
    }
    return it->second;
  }

  size_type count(const value_type& val) const {
    return map_.count(val);
  }

  allocator_type get_allocator() const noexcept {
    return list_.get_allocator();
  }
};

}}
