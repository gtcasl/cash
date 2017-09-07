#pragma once

#include "bit.h"

namespace cash {
namespace internal {

lnodeimpl* createSelectNode(const lnode& pred, const lnode& a, const lnode& b);

class select_impl {
public:
  
  select_impl() {}

  select_impl(const lnode& key) : key_(key) {}

  ~select_impl() {}
  
  void push(const lnode& pred, const lnode& value) {
    stmts_.push({pred, value});
  }
  
  lnodeimpl* eval(const lnode& value);

protected:

  struct stmt_t {
    lnode pred;
    lnode value;
  };

  using stmts_t = std::stack<stmt_t>;

  lnode key_;
  stmts_t stmts_;
};

template <unsigned N> 
class select_t {
public:
    
  select_t(const ch_bitbase<1>& pred, const ch_bitbase<N>& value) {
    impl_.push(get_node(pred), get_node(value));
  }

  template <typename P, typename V,
            typename = typename if_convertible<P, ch_bit<1>>::type,
            typename = typename if_convertible<V, ch_bit<N>>::type>
  select_t<N>& operator()(const P& pred, const V& value) {
    impl_.push(get_node(pred), get_node(value));
    return *this;
  }
  
  template <typename V,
            typename = typename if_convertible<V, ch_bit<N>>::type>
  const auto operator()(const V& value) {
    return make_bit<N>(impl_.eval(get_node(value)));
  }
  
protected:
  
  select_impl impl_;
};

template <unsigned K>
class select_key_t {
public:

  template <unsigned N>
  class case_t {
  public:
    
    case_t(const lnode& key, const lnode& pred, const lnode& value) : impl_(key) {
      impl_.push(pred, value);
    }
    
    template <typename P, typename V,
              typename = typename if_convertible<P, ch_bit<K>>::type,
              typename = typename if_convertible<V, ch_bit<N>>::type>
    case_t& operator()(const P& pred, const V& value) {
      impl_.push(get_node(pred), get_node(value));
      return *this;
    }
    
    template <typename V,
              typename = typename if_convertible<V, ch_bit<N>>::type>
    const auto operator()(const V& value) {
      return make_bit<N>(impl_.eval(get_node(value)));
    }
    
  protected:
    
    select_impl impl_;
  };

  select_key_t(const ch_bitbase<K>& key) : key_(get_node(key)) {}

  template <typename P, typename V,
            typename = typename if_convertible<P, ch_bit<K>>::type,
            typename = typename if_convertible<V, ch_bit<V::bitcount>>::type>
  auto operator()(const P& pred, const V& value) {
    return case_t<V::bitcount>(key_, get_node(pred), get_node(value));
  }
  
protected:
  
  lnode key_;
};

template <typename P, typename V,
          typename = typename if_convertible<P, ch_bit<1>>::type,
          typename = typename if_convertible<V, ch_bit<V::bitcount>>::type>
auto ch_select(const P& pred, const V& value) {
  return select_t<V::bitcount>((typename ch_bit_cast<P, 1>::type)pred,
                               (typename ch_bit_cast<V, V::bitcount>::type)value);
}

template <typename K,
          typename = typename if_convertible<K, ch_bit<K::bitcount>>::type>
auto ch_select(const K& key) {
  return select_key_t<K::bitcount>((typename ch_bit_cast<K, K::bitcount>::type)key);
}

template <typename P, typename U, typename V,
          typename = typename if_convertible<P, ch_bit<1>>::type,
          typename = typename std::enable_if<(deduce_bitcount<U, V>::value != 0)>::type,
          typename = typename if_convertible<U, ch_bit<deduce_bitcount<U, V>::value>>::type,
          typename = typename if_convertible<V, ch_bit<deduce_bitcount<U, V>::value>>::type>
const auto ch_select(const P& pred, const U& _true, const V& _false) {
  return make_bit<deduce_bitcount<U, V>::value>(
        createSelectNode(get_node(pred),
                         get_node<U, deduce_bitcount<U, V>::value>(_true),
                         get_node<V, deduce_bitcount<U, V>::value>(_false)));
}

template <typename U, typename V,
          typename = typename std::enable_if<(deduce_bitcount<U, V>::value != 0)>::type,
          typename = typename if_convertible<U, ch_bit<deduce_bitcount<U, V>::value>>::type,
          typename = typename if_convertible<V, ch_bit<deduce_bitcount<U, V>::value>>::type>
const auto ch_min(const U& lhs, const V& rhs) {
  return ch_select(lhs < rhs, lhs, rhs);
}

template <typename U, typename V,
          typename = typename std::enable_if<(deduce_bitcount<U, V>::value != 0)>::type,
          typename = typename if_convertible<U, ch_bit<deduce_bitcount<U, V>::value>>::type,
          typename = typename if_convertible<V, ch_bit<deduce_bitcount<U, V>::value>>::type>
const auto ch_max(const U& lhs, const V& rhs) {
  return ch_select(lhs > rhs, lhs, rhs);
}

}
}
