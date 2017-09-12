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
    
  select_t(const lnode& pred, const lnode& value) {
    impl_.push(pred, value);
  }

  template <typename V,
            CH_REQUIRES(is_cast_convertible<V, ch_bit<N>>::value)>
  select_t<N>& operator()(const ch_bitbase<1>& pred, const V& value) {
    impl_.push(get_lnode(pred), get_lnode<V, N>(value));
    return *this;
  }
  
  template <typename V,
            CH_REQUIRES(is_cast_convertible<V, ch_bit<N>>::value)>
  const auto operator()(const V& value) {
    return make_bit<N>(impl_.eval(get_lnode<V, N>(value)));
  }
  
protected:
  
  select_impl impl_;
};

template <unsigned K, unsigned N>
class select_case_t {
public:

  select_case_t(const lnode& key, const lnode& pred, const lnode& value) : impl_(key) {
    impl_.push(pred, value);
  }

  template <typename P, typename V,
            CH_REQUIRES(is_cast_convertible<P, ch_bit<K>>::value),
            CH_REQUIRES(is_cast_convertible<V, ch_bit<N>>::value)>
  select_case_t& operator()(const P& pred, const V& value) {
    impl_.push(get_lnode<P, K>(pred), get_lnode<V, N>(value));
    return *this;
  }

  template <typename V,
            CH_REQUIRES(is_cast_convertible<V, ch_bit<N>>::value)>
  const auto operator()(const V& value) {
    return make_bit<N>(impl_.eval(get_lnode<V, N>(value)));
  }

protected:

  select_impl impl_;
};

template <unsigned K>
class select_key_t {
public:

  select_key_t(const lnode& key) : key_(key) {}

  template <typename P, typename V,
            CH_REQUIRES(is_cast_convertible<P, ch_bit<K>>::value),
            CH_REQUIRES(is_cast_convertible<V, ch_bit<V::bitcount>>::value)>
  auto operator()(const P& pred, const V& value) {
    return select_case_t<K, V::bitcount>(key_, get_lnode<P, K>(pred), get_lnode(value));
  }
  
protected:
  
  lnode key_;
};

template <unsigned K, unsigned N>
class select_key2_t {
public:

  select_key2_t(const lnode& key) : key_(key) {}

  template <typename P, typename V,
            CH_REQUIRES(is_cast_convertible<P, ch_bit<K>>::value),
            CH_REQUIRES(is_cast_convertible<V, ch_bit<N>>::value)>
  auto operator()(const P& pred, const V& value) {
    return select_case_t<K, N>(key_, get_lnode<P, K>(pred), get_lnode<V, N>(value));
  }

protected:

  lnode key_;
};

template <typename V,
          CH_REQUIRES(is_cast_convertible<V, ch_bit<V::bitcount>>::value)>
auto ch_select(const ch_bitbase<1>& pred, const V& value) {
  return select_t<V::bitcount>(get_lnode(pred), get_lnode(value));
}

template <unsigned N, typename V,
          CH_REQUIRES(is_cast_convertible<V, ch_bit<N>>::value)>
auto ch_select(const ch_bitbase<1>& pred, const V& value) {
  return select_t<N>(get_lnode(pred), get_lnode<V, N>(value));
}

template <typename K,
          CH_REQUIRES(is_cast_convertible<K, ch_bit<K::bitcount>>::value)>
auto ch_select(const K& key) {
  return select_key_t<K::bitcount>(get_lnode(key));
}

template <unsigned N, typename K,
          CH_REQUIRES(is_cast_convertible<K, ch_bit<K::bitcount>>::value)>
auto ch_select(const K& key) {
  return select_key2_t<K::bitcount, N>(get_lnode(key));
}

template <typename U, typename V,
          CH_REQUIRES(deduce_bitcount<U, V>::value != 0),
          CH_REQUIRES(is_cast_convertible<U, ch_bit<deduce_bitcount<U, V>::value>>::value),
          CH_REQUIRES(is_cast_convertible<V, ch_bit<deduce_bitcount<U, V>::value>>::value)>
const auto ch_select(const ch_bitbase<1>& pred, const U& _true, const V& _false) {
  return make_bit<deduce_bitcount<U, V>::value>(
        createSelectNode(get_lnode(pred),
                         get_lnode<U, deduce_bitcount<U, V>::value>(_true),
                         get_lnode<V, deduce_bitcount<U, V>::value>(_false)));
}

template <unsigned N, typename U, typename V,
          CH_REQUIRES(is_cast_convertible<U, ch_bit<N>>::value),
          CH_REQUIRES(is_cast_convertible<V, ch_bit<N>>::value)>
const auto ch_select(const ch_bitbase<1>& pred, const U& _true, const V& _false) {
  return make_bit<N>(
        createSelectNode(get_lnode(pred),
                         get_lnode<U, N>(_true),
                         get_lnode<V, N>(_false)));
}

template <typename U, typename V,
          CH_REQUIRES(deduce_bitcount<U, V>::value != 0),
          CH_REQUIRES(is_cast_convertible<U, ch_bit<deduce_bitcount<U, V>::value>>::value),
          CH_REQUIRES(is_cast_convertible<V, ch_bit<deduce_bitcount<U, V>::value>>::value)>
const auto ch_min(const U& lhs, const V& rhs) {
  return ch_select(lhs < rhs, lhs, rhs);
}

template <typename U, typename V,
          CH_REQUIRES(deduce_bitcount<U, V>::value != 0),
          CH_REQUIRES(is_cast_convertible<U, ch_bit<deduce_bitcount<U, V>::value>>::value),
          CH_REQUIRES(is_cast_convertible<V, ch_bit<deduce_bitcount<U, V>::value>>::value)>
const auto ch_max(const U& lhs, const V& rhs) {
  return ch_select(lhs > rhs, lhs, rhs);
}

}
}
