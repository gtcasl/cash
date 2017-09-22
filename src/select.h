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

template <typename T>
class select_t {
public:
    
  select_t(const lnode& pred, const lnode& value) {
    impl_.push(pred, value);
  }

  template <typename V,
            CH_REQUIRES(is_cast_convertible<V, T>::value)>
  select_t<T>& operator()(const ch_bitbase<1>& pred, const V& value) {
    impl_.push(get_lnode(pred), get_lnode<V, T::bitcount>(value));
    return *this;
  }
  
  template <typename V,
            CH_REQUIRES(is_cast_convertible<V, T>::value)>
  const auto operator()(const V& value) {
    return make_type<T>(impl_.eval(get_lnode<V, T::bitcount>(value)));
  }
  
protected:
  
  select_impl impl_;
};

template <unsigned N>
class select2_t {
public:

  select2_t(const lnode& pred, const lnode& value) {
    impl_.push(pred, value);
  }

  template <typename V,
            CH_REQUIRES(is_bit_convertible<V, N>::value)>
  select2_t& operator()(const ch_bitbase<1>& pred, const V& value) {
    impl_.push(get_lnode(pred), get_lnode<V, N>(value));
    return *this;
  }

  template <typename V,
            CH_REQUIRES(is_bit_convertible<V, N>::value)>
  const auto operator()(const V& value) {
    return make_bit<N>(impl_.eval(get_lnode<V, N>(value)));
  }

protected:

  select_impl impl_;
};

template <unsigned K, typename T>
class select_case_t {
public:

  select_case_t(const lnode& key, const lnode& pred, const lnode& value) : impl_(key) {
    impl_.push(pred, value);
  }

  template <typename V, typename P,
            CH_REQUIRES(is_cast_convertible<V, T>::value),
            CH_REQUIRES(is_bit_convertible<P, K>::value)>
  select_case_t& operator()(const P& pred, const V& value) {
    impl_.push(get_lnode<P, K>(pred), get_lnode<V, T::bitcount>(value));
    return *this;
  }

  template <typename V,
            CH_REQUIRES(is_cast_convertible<V, T>::value)>
  const auto operator()(const V& value) {
    return make_type<T>(impl_.eval(get_lnode<V, T::bitcount>(value)));
  }

protected:

  select_impl impl_;
};

template <unsigned K, unsigned N>
class select_case2_t {
public:

  select_case2_t(const lnode& key, const lnode& pred, const lnode& value) : impl_(key) {
    impl_.push(pred, value);
  }

  template <typename V, typename P,
            CH_REQUIRES(is_bit_convertible<V, N>::value),
            CH_REQUIRES(is_bit_convertible<P, K>::value)>
  select_case2_t& operator()(const P& pred, const V& value) {
    impl_.push(get_lnode<P, K>(pred), get_lnode<V, N>(value));
    return *this;
  }

  template <typename V,
            CH_REQUIRES(is_bit_convertible<V, N>::value)>
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

  template <typename V, typename P,
            CH_REQUIRES(is_bit_convertible<V>::value),
            CH_REQUIRES(is_bit_convertible<P, K>::value)>
  auto operator()(const P& pred, const V& value) {
    return select_case_t<K, V>(key_, get_lnode<P, K>(pred), get_lnode(value));
  }
  
protected:
  
  lnode key_;
};

template <unsigned K, unsigned N>
class select_key2_t {
public:

  select_key2_t(const lnode& key) : key_(key) {}

  template <typename P, typename V,
            CH_REQUIRES(is_bit_convertible<P, K>::value),
            CH_REQUIRES(is_bit_convertible<V, N>::value)>
  auto operator()(const P& pred, const V& value) {
    return select_case2_t<K, N>(key_, get_lnode<P, K>(pred), get_lnode<V, N>(value));
  }

protected:

  lnode key_;
};

template <typename V,
          CH_REQUIRES(is_bit_convertible<V, V::bitcount>::value)>
auto ch_select(const ch_bitbase<1>& pred, const V& value) {
  return select_t<V>(get_lnode(pred), get_lnode(value));
}

template <unsigned N, typename V,
          CH_REQUIRES(is_bit_convertible<V, N>::value)>
auto ch_select(const ch_bitbase<1>& pred, const V& value) {
  return select2_t<N>(get_lnode(pred), get_lnode<V, N>(value));
}

template <typename K,
          CH_REQUIRES(is_bit_convertible<K, K::bitcount>::value)>
auto ch_select(const K& key) {
  return select_key_t<K::bitcount>(get_lnode(key));
}

template <unsigned N, typename K,
          CH_REQUIRES(is_bit_convertible<K, K::bitcount>::value)>
auto ch_select(const K& key) {
  return select_key2_t<K::bitcount, N>(get_lnode(key));
}

template <typename U, typename V,
          CH_REQUIRES(deduce_type<U, V>::bitcount != 0),
          CH_REQUIRES(is_bit_convertible<U, deduce_type<U, V>::bitcount>::value),
          CH_REQUIRES(is_bit_convertible<V, deduce_type<U, V>::bitcount>::value)>
const auto ch_select(const ch_bitbase<1>& pred, const U& _true, const V& _false) {
  return make_type<typename deduce_first_type<U, V>::type>(
        createSelectNode(get_lnode(pred),
                         get_lnode<U, deduce_type<U, V>::bitcount>(_true),
                         get_lnode<V, deduce_type<U, V>::bitcount>(_false)));
}

template <unsigned N, typename U, typename V,
          CH_REQUIRES(is_bit_convertible<U, N>::value),
          CH_REQUIRES(is_bit_convertible<V, N>::value)>
const auto ch_select(const ch_bitbase<1>& pred, const U& _true, const V& _false) {
  return make_bit<N>(
        createSelectNode(get_lnode(pred),
                         get_lnode<U, N>(_true),
                         get_lnode<V, N>(_false)));
}

template <typename U, typename V,
          CH_REQUIRES(deduce_type<U, V>::bitcount != 0),
          CH_REQUIRES(is_bit_convertible<U, deduce_type<U, V>::bitcount>::value),
          CH_REQUIRES(is_bit_convertible<V, deduce_type<U, V>::bitcount>::value)>
const auto ch_min(const U& lhs, const V& rhs) {
  return ch_select(lhs < rhs, lhs, rhs);
}

template <typename U, typename V,
          CH_REQUIRES(deduce_type<U, V>::bitcount != 0),
          CH_REQUIRES(is_bit_convertible<U, deduce_type<U, V>::bitcount>::value),
          CH_REQUIRES(is_bit_convertible<V, deduce_type<U, V>::bitcount>::value)>
const auto ch_max(const U& lhs, const V& rhs) {
  return ch_select(lhs > rhs, lhs, rhs);
}

}
}
