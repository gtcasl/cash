#pragma once

#include "lnodeimpl.h"

namespace ch {
namespace internal {

class node_list {
private:

  using difference_type	= std::ptrdiff_t;
  using value_type = lnodeimpl*;
  using pointer = value_type*;
  using reference = value_type&;

public:

  class const_iterator {
  public:
    using difference_type	= std::ptrdiff_t;
    using value_type = lnodeimpl*;
    using pointer = value_type*;
    using reference = value_type&;
    using iterator_category = std::forward_iterator_tag;

    const_iterator(const const_iterator& other) : node_(other.node_) {}

    const_iterator& operator=(const const_iterator& other) {
      node_ = other.node_;
      return *this;
    }

    bool operator==(const const_iterator& other) const {
      return (node_ == other.node_);
    }

    bool operator!=(const const_iterator& other) const {
      return !(*this == other);
    }

    lnodeimpl* operator*() const {
      return node_;
    }

    const_iterator& operator++() {
      node_ = node_->next_;
      return *this;
    }

    const_iterator operator++(int) {
      const_iterator ret(*this);
      this->operator++();
      return ret;
    }

  private:

    const_iterator(lnodeimpl* node) : node_(node) {}

    lnodeimpl* node_;

    friend class node_list;
  };

  class iterator : public const_iterator {
  public:
    using base = const_iterator;

    iterator(const iterator& other) : base(other) {}

    iterator(const const_iterator& other) : base(other) {}

    auto operator*() const {
      return base::operator*();
    }

    iterator& operator++() {
      base::operator++();
      return *this;
    }

    iterator operator++(int) {
      iterator ret(*this);
      base::operator++();
      return ret;
    }

  protected:

    iterator(lnodeimpl* node) : const_iterator(node) {}

    friend class const_iterator;
    friend class node_list;
  };

  node_list() : head_(nullptr), tail_(nullptr), size_(0) {}

  void push_back(lnodeimpl* node);

  iterator erase(const iterator& it);

  void remove(lnodeimpl* node) {
    this->erase(std::find(this->begin(), this->end(), node));
  }

  lnodeimpl* front() const {
    return head_;
  }

  lnodeimpl* back() const {
    return tail_;
  }

  const_iterator begin() const {
    return const_iterator(head_);
  }

  const_iterator end() const {
    return const_iterator(nullptr);
  }

  iterator begin() {
    return iterator(head_);
  }

  iterator end() {
    return iterator(nullptr);
  }

  size_t size() const {
    return size_;
  }

  bool empty() const {
    return (0 == size_);
  }

private:

  lnodeimpl* head_;
  lnodeimpl* tail_;
  size_t size_;
};

}}
