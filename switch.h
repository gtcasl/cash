#pragma once

#include "if.h"

namespace cash_internal {

class switch_impl {
public:
  
  ~switch_impl();
  
  using func_t = std::function<void ()>;
  
  void eval(lnodeimpl* cond, func_t func);
 
private: 
 
  switch_impl(lnodeimpl* key);
 
  lnodeimpl* key_;
  
  template <unsigned N> friend class switch_t;
};

template <unsigned N>
class switch_t {
public:
  
  template <typename Func>
  switch_t& case_(const ch_bitbase<N>& value, const Func& func) {
    impl_.eval(value.get_node().get_impl(), to_function(func));
    return *this;
  }
  
  template <typename Func>
  switch_t& case_(const ch_bit<N>& value, const Func& func) {    
    impl_.eval(value.get_node().get_impl(), to_function(func));
    return *this;
  }
  
  template <typename Func>
  void default_(const Func& func) {
    impl_.eval(nullptr, to_function(func));
  }
  
protected:
  
  switch_t(lnodeimpl* key) : impl_(key) {}
  
  switch_impl impl_;
    
  template <unsigned N_> 
  friend switch_t<N_> ch_switch(const ch_bitbase<N_>& key);
};

template <unsigned N> 
switch_t<N> ch_switch(const ch_bitbase<N>& key) {
  return switch_t<N>(key.get_node().get_impl());
}

#define CH_SWITCH_BODY(body)    body
#define CH_SWITCH(key)          ch_switch(key) CH_SWITCH_BODY
#define CH_CASE_BODY(value)     value })
#define CH_CASE(cond)           .case_(cond, [&](){ CH_CASE_BODY
#define CH_DEFAULT(value)       .default_([&](){ value })

}
