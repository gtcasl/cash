#pragma once

#include "bit.h"

namespace ch {
namespace internal {

class select_impl {
public:
  
  select_impl(const source_info& srcinfo) 
    : srcinfo_(srcinfo) 
    {}

  select_impl(const lnode& key, const source_info& srcinfo) 
    : key_(key)
    , srcinfo_(srcinfo) 
  {}

  select_impl(select_impl& other) 
    : stmts_(std::move(other.stmts_))
    , key_(std::move(other.key_))
    , srcinfo_(std::move(other.srcinfo_)) 
  {}

  auto operator=(select_impl&& other) {
    stmts_   = std::move(other.stmts_);
    key_     = std::move(other.key_);
    srcinfo_ = std::move(other.srcinfo_);
    return *this;
  }
  
  void push(const lnode& pred, const lnode& value) {
    stmts_.emplace_back(pred, value);
  }
  
  lnode emit(const lnode& def_value);

  const auto& srcinfo() const {
    return srcinfo_;
  }

protected:

  select_impl(const select_impl& other);

  auto operator=(const select_impl& other);

  std::vector<std::pair<lnode, lnode>> stmts_;
  lnode key_;
  source_info srcinfo_;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class select_t {
public:    
  select_t(const lnode& pred, 
           const lnode& value, 
           const source_info& srcinfo) 
    : impl_(srcinfo) {
    impl_.push(pred, value);
  }

  select_t(select_t& other) 
    : impl_(std::move(other.impl_)) 
  {}

  auto operator=(select_t&& other) {
    impl_ = std::move(other.impl_);
    return *this;
  }

  template <typename V, typename P>
  select_t<T>& operator()(const P& pred, const V& value) {
    static_assert(std::is_constructible_v<T, V>, "invalid type");    
    static_assert(is_bitbase_v<P>, "invalid type");
    static_assert(ch_width_v<P> == 1, "invalid size");
    impl_.push(get_lnode(pred), to_lnode<T>(value, impl_.srcinfo()));
    return *this;
  }
  
  template <typename V>
  auto operator()(const V& def_value) {
    static_assert(std::is_constructible_v<T, V>, "invalid type");    
    return make_logic_type<T>(impl_.emit(to_lnode<T>(def_value, impl_.srcinfo())));
  }
  
protected:

  select_t(const select_t& other);

  auto operator=(const select_t& other);

  select_impl impl_;
};

template <typename K, typename V>
class case_t {
public:
  case_t(const lnode& key, 
         const lnode& pred, 
         const lnode& value, 
         const source_info& srcinfo)
    : impl_(key, srcinfo) {
    impl_.push(pred, value);
  }

  case_t(case_t& other) 
    : impl_(std::move(other.impl_)) 
  {}

  auto operator=(case_t&& other) {
    impl_ = std::move(other.impl_);
    return *this;
  }

  template <typename T, typename P>
  case_t& operator()(const P& pred, const T& value) {    
    static_assert(std::is_constructible_v<V, T>, "invalid type");
    static_assert(is_equality_comparable_v<P, K>, "invalid type");
    auto lpred = to_lnode<K>(pred, impl_.srcinfo());
    auto lvalue = to_lnode<V>(value, impl_.srcinfo());
    impl_.push(lpred, lvalue);
    return *this;
  }

  template <typename T>
  auto operator()(const T& def_value) {
    static_assert(std::is_constructible_v<V, T>, "invalid type");
    auto lvalue = to_lnode<V>(def_value, impl_.srcinfo());
    return make_logic_type<V>(impl_.emit(lvalue));
  }
  
protected:

  case_t(const case_t& other);

  auto operator=(const case_t& other);
  
  select_impl impl_;
};

///////////////////////////////////////////////////////////////////////////////

template <typename R, typename T, typename P>
auto ch_sel(const P& pred, const T& value, CH_SRC_INFO) {
  static_assert(is_logic_type_v<R>, "invalid type");
  static_assert(std::is_constructible_v<R, T>, "invalid type");
  static_assert(is_bitbase_v<P>, "invalid type");
  static_assert(ch_width_v<P> == 1, "invalid size");
  return select_t<R>(get_lnode(pred), to_lnode<R>(value, srcinfo), srcinfo);
}

template <typename T, typename P>
auto ch_sel(const P& pred, const T& value, CH_SRC_INFO) {
  static_assert(is_logic_type_v<P>, "invalid type");
  return ch_sel<ch_logic_t<T>, T, P>(pred, value, srcinfo);
}

template <typename R, typename U, typename V, typename P>
auto ch_sel(const P& pred, const U& _true, const V& _false, CH_SRC_INFO) {
  return ch_sel<R, U, P>(pred, _true, srcinfo)(_false);
}

template <typename U, typename V, typename P>
auto ch_sel(const P& pred, const U& _true, const V& _false, CH_SRC_INFO) {
  static_assert(ch_width_v<deduce_type_t<true, U, V>> != 0, "invalid type");
  return ch_sel<ch_logic_t<deduce_first_type_t<U, V>>, U, V, P>(pred, _true, _false, srcinfo);
}

///////////////////////////////////////////////////////////////////////////////

template <typename R, typename V, typename K, typename P>
auto ch_case(const K& key, const P& pred, const V& value, CH_SRC_INFO) {
  static_assert(std::is_constructible_v<R, V>, "invalid type");
  static_assert(is_logic_type_v<K>, "invalid type");
  static_assert(!is_logic_type_v<P>, "invalid type");
  static_assert(is_equality_comparable_v<P, K>, "invalid type");
  return case_t<ch_logic_t<K>, R>(get_lnode(key),
                      to_lnode<ch_logic_t<K>>(pred, srcinfo),
                      to_lnode<R>(value, srcinfo),
                      srcinfo);
}

template <typename V, typename K, typename P>
auto ch_case(const K& key, const P& pred, const V& value, CH_SRC_INFO) {
  static_assert(is_data_type_v<V>, "invalid type");
  return ch_case<ch_logic_t<V>, V, K, P>(key, pred, value, srcinfo);
}

}
}
