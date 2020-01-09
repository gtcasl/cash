#pragma once

#include "nodelist.h"

namespace ch {
namespace internal {

class node_list_view {
private:

  using difference_type	= std::ptrdiff_t;
  using value_type = lnodeimpl*;
  using pointer = value_type*;
  using reference = value_type&;

  using container_type = node_list*;
  using container_iterator = node_list::iterator;

public:

  class const_iterator {
  public:
    using difference_type	= std::ptrdiff_t;
    using value_type = lnodeimpl*;
    using pointer = value_type*;
    using reference = value_type&;
    using iterator_category = std::forward_iterator_tag;

    const_iterator(const const_iterator& other)
      : containers_(other.containers_)
      , container_idx_(other.container_idx_)
      , iterator_(other.iterator_)
    {}

    const_iterator& operator=(const const_iterator& other) {
      containers_ = other.containers_;
      container_idx_ = other.container_idx_;
      iterator_ = other.iterator_;
      return *this;
    }

    bool operator==(const const_iterator& other) const {
      return (containers_ == other.containers_)
          && (container_idx_ == other.container_idx_)
          && (iterator_ == other.iterator_);
    }

    bool operator!=(const const_iterator& other) const {
      return !(*this == other);
    }

    lnodeimpl* operator*() const {
      return *iterator_;
    }

    const_iterator& operator++() {
      ++iterator_;
      this->check_end_of_container();
      return *this;
    }

    const_iterator operator++(int) {
      const_iterator ret(*this);
      this->operator++();
      return ret;
    }

  private:

    const_iterator(const std::vector<container_type>* containers,
                   size_t container_idx,
                   const container_iterator& iterator)
      : containers_(containers)
      , container_idx_(container_idx)
      , iterator_(iterator) {
      this->check_end_of_container();
    }

    void check_end_of_container() {
      auto container = (*containers_)[container_idx_];
      while (iterator_ == container->end()
          && container_idx_ < containers_->size()-1) {
        container = (*containers_)[++container_idx_];
        iterator_ = container->begin();
      }
    }

    const std::vector<container_type>* containers_;
    size_t container_idx_;
    container_iterator iterator_;

    friend class node_list_view;
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

    iterator(const std::vector<container_type>* containers,
             size_t container_idx,
             const container_iterator& iterator)
      : const_iterator(containers, container_idx, iterator)
    {}

    friend class node_list_view;
  };

  template <typename... Containers>
  node_list_view(Containers... containers) : containers_({containers...}) {}

  iterator erase(const iterator& it) {
    auto container_idx = it.container_idx_;
    auto next_it = containers_.at(container_idx)->erase(it.iterator_);
    return iterator(&containers_, container_idx, next_it);
  }

  auto begin() const {
    return const_iterator(&containers_, 0, containers_[0]->begin());
  }

  auto end() const {
    auto last_index = containers_.size() - 1;
    return const_iterator(&containers_, last_index, containers_[last_index]->end());
  }

  auto begin() {
    return iterator(&containers_, 0, containers_[0]->begin());
  }

  auto end() {
    auto last_index = containers_.size() - 1;
    return iterator(&containers_, last_index, containers_[last_index]->end());
  }

  auto size() const {
    size_t size = 0;
    for (auto container : containers_) {
      size += container->size();
    }
    return size;
  }

  bool empty() const {
    return (0 == this->size());
  }

private:

  std::vector<container_type> containers_;
};

}}
