#pragma once

#include "bit.h"

namespace cash {
namespace internal {

lnodeimpl* createSelectNode(const lnode& pred, const lnode& a, const lnode& b);

class select_impl {
public:
  
  ~select_impl() {}

  select_impl() {}

  select_impl(const lnode& key) : key_(key) {}
  
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
    
  select_t<N>& operator()(const ch_bitbase<1>& pred, const ch_bitbase<N>& value) {
    impl_.push(get_node(pred), get_node(value));
    return *this;
  }
  
  select_t<N>& operator()(const ch_bitbase<1>& pred, const ch_bit<N>& value) {
    impl_.push(get_node(pred), get_node(value));
    return *this;
  }
  
  const auto operator()(const ch_bitbase<N>& value) {
    return make_bit<N>(impl_.eval(get_node(value)));
  }
  
  const auto operator()(const ch_bit<N>& value) {
    return make_bit<N>(impl_.eval(get_node(value)));
  }
  
protected:
  
  select_t(const ch_bitbase<1>& pred, const ch_bitbase<N>& value) {
    impl_.push(get_node(pred), get_node(value));
  }

  select_impl impl_;
  
  template <unsigned N_>
  friend select_t<N_> ch_select(const ch_bitbase<1>& pred, const ch_bitbase<N_>& value);
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
    
    case_t& operator()(const ch_bitbase<K>& pred, const ch_bitbase<N>& value) {
      impl_.push(get_node(pred), get_node(value));
      return *this;
    }
    
    case_t& operator()(const ch_bitbase<K>& pred, const ch_bit<N>& value) {
      impl_.push(get_node(pred), get_node(value));
      return *this;
    }
    
    case_t& operator()(const ch_bit<K>& pred, const ch_bitbase<N>& value) {
      impl_.push(get_node(pred), get_node(value));
      return *this;
    }
    
    case_t& operator()(const ch_bit<K>& pred, const ch_bit<N>& value) {
      impl_.push(get_node(pred), get_node(value));
      return *this;
    }
    
    const auto operator()(const ch_bitbase<N>& value) {
      return make_bit<N>(impl_.eval(get_node(value)));
    }
    
    const auto operator()(const ch_bit<N>& value) {
      return make_bit<N>(impl_.eval(get_node(value)));
    }
    
  protected:
    
    select_impl impl_;
  };

  template <unsigned N>
  auto operator()(const ch_bitbase<K>& pred, const ch_bitbase<N>& value) {
    return case_t<N>(key_, get_node(pred), get_node(value));
  }
  
  template <unsigned N>
  auto operator()(const ch_bitbase<K>& pred, const ch_bit<N>& value) {
    return case_t<N>(key_, get_node(pred), get_node(value));
  }
  
  template <unsigned N>
  auto operator()(const ch_bit<K>& pred, const ch_bitbase<N>& value) {
    return case_t<N>(key_, get_node(pred), get_node(value));
  }
  
  template <unsigned N>
  auto operator()(const ch_bit<K>& pred, const ch_bit<N>& value) {
    return case_t<N>(key_, get_node(pred), get_node(value));
  }
  
protected:
  
  lnode key_;
  
  select_key_t(const ch_bitbase<K>& key) : key_(get_node(key)) {}

  template <unsigned K_> friend select_key_t<K_> ch_select(const ch_bitbase<K_>& key);
};

template <unsigned N>
select_t<N> ch_select(const ch_bitbase<1>& pred, const ch_bitbase<N>& value) {
  return select_t<N>(pred, value);
}

template <unsigned N> 
select_t<N> ch_select(const ch_bitbase<1>& pred, const ch_bit<N>& value) {
  return ch_select(pred, reinterpret_cast<const ch_bitbase<N>&>(value));
}

template <unsigned K>
select_key_t<K> ch_select(const ch_bitbase<K>& key) {
  return select_key_t<K>(key);
}

template <unsigned N>
const auto ch_select(const ch_bitbase<1>& pred,
                     const ch_bitbase<N>& _true,
                     const ch_bitbase<N>& _false) {
  return make_bit<N>(createSelectNode(get_node(pred),
                                      get_node(_true),
                                      get_node(_false)));
}

template <unsigned N>
const auto ch_select(const ch_bitbase<1>& pred,
                    const ch_bitbase<N>& _true,
                    const ch_bit<N>& _false) {
  return make_bit<N>(createSelectNode(get_node(pred),
                                      get_node(_true),
                                      get_node(_false)));
}

template <unsigned N>
const auto ch_select(const ch_bitbase<1>& pred,
                    const ch_bit<N>& _true,
                    const ch_bitbase<N>& _false) {
  return make_bit<N>(createSelectNode(get_node(pred),
                                      get_node(_true),
                                      get_node(_false)));
}

template <unsigned N>
const auto ch_select(const ch_bitbase<1>& pred,
                    const ch_bit<N>& _true,
                    const ch_bit<N>& _false) {
  return make_bit<N>(createSelectNode(get_node(pred),
                                    get_node(_true),
                                    get_node(_false)));
}

template <unsigned N> 
const auto ch_min(const ch_bitbase<N>& lhs, const ch_bitbase<N>& rhs) {
  return ch_select<N>(lhs < rhs, lhs, rhs);
}

template <unsigned N> 
const auto ch_min(const ch_bitbase<N>& lhs, const ch_bit<N>& rhs) {
  return ch_select<N>(lhs < rhs, lhs, rhs);
}

template <unsigned N> 
const auto ch_min(const ch_bit<N>& lhs, const ch_bitbase<N>& rhs) {
  return ch_select<N>(lhs < rhs, lhs, rhs);
}

template <unsigned N> 
const auto ch_min(const ch_bit<N>& lhs, const ch_bit<N>& rhs) {
  return ch_select<N>(lhs < rhs, lhs, rhs);
}

template <unsigned N> 
const auto ch_max(const ch_bitbase<N>& lhs, const ch_bitbase<N>& rhs) {
  return ch_select<N>(lhs > rhs, lhs, rhs);
}

template <unsigned N> 
const auto ch_max(const ch_bitbase<N>& lhs, const ch_bit<N>& rhs) {
  return ch_select<N>(lhs > rhs, lhs, rhs);
}

template <unsigned N> 
const auto ch_max(const ch_bit<N>& lhs, const ch_bitbase<N>& rhs) {
  return ch_select<N>(lhs > rhs, lhs, rhs);
}

template <unsigned N> 
const auto ch_max(const ch_bit<N>& lhs, const ch_bit<N>& rhs) {
  return ch_select<N>(lhs > rhs, lhs, rhs);
}

}
}
