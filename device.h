#pragma once

#include <functional>
#include "bitv.h"
#include "bus.h"

namespace chdl_internal {

class context;

template <typename T>
struct to_value_type {
  typedef T value;
};

template <unsigned N>
struct to_value_type< ch_bitbase<N> > {
  typedef ch_bitv<N> value;
};

class ioport_arg {
public:
  ~ioport_arg() {}

protected:    
  
  template <typename T>
  ioport_arg(T& arg) : m_node(arg) {}

  ch_node& m_node;
  friend class ch_device;
};

class bus_arg {
public:
  ~bus_arg() {}

protected:
  
  template <typename T>
  bus_arg(const T& arg) : m_impl(arg) {}

  busimpl* m_impl;
  friend class ch_device;
};

context* ctx_enter();
void ctx_exit();

class ch_device {
public:
  template <typename... Args>  
  ch_device(void (*func)(Args...)) {
    m_ctx = ctx_enter();
    {
      std::tuple<typename to_value_type<typename std::remove_const<
          typename std::remove_reference<Args>::type >::type>::value...> args;       
      this->load(func, args);
      this->compile();
    }
    ctx_exit();
  }
  
  template <typename Ret, typename... Args>  
  ch_device(Ret (*func)(Args...)) {
    m_ctx = ctx_enter();
    {
      std::tuple<typename to_value_type<typename std::remove_const<
          typename std::remove_reference<Args>::type >::type>::value...> args; 
      this->load(func, args);
      this->compile();
    }
    ctx_exit();
  }
  
  template <typename T, typename... Args>  
  ch_device(const T* obj, void (T::*func)(Args...) const) {
    m_ctx = ctx_enter();
    {
      std::tuple<typename to_value_type<typename std::remove_const<
          typename std::remove_reference<Args>::type >::type>::value...> args; 
      this->load(obj, func, args);
      this->compile();
    }
    ctx_exit();
  }
  
  template <typename T, typename Ret, typename... Args>  
  ch_device(const T* obj, Ret (T::*func)(Args...) const) {
    m_ctx = ctx_enter();
    {
      std::tuple<typename to_value_type<typename std::remove_const<
          typename std::remove_reference<Args>::type >::type>::value...> args; 
      this->load(obj, func, args); 
      this->compile();
    }
    ctx_exit();
  }
  
  ~ch_device();
  
  template<typename... Args>
  void bind(Args&&... args) {
    this->bind({bus_arg(std::forward<Args>(args))...});
  }
  
  template<typename Ret, typename... Args>
  void bind(Ret& ret, Args&&... args) {
    this->bind({bus_arg(ret), bus_arg(std::forward<Args>(args))...});
  }
  
  void toVerilog(const std::string& module_name, std::ostream& out);  
  
protected:
 
  template<typename ...Args1, typename ...Args2, size_t ...I>
  void load_impl(void (*func)(Args1...), std::tuple<Args2...>& args, index_sequence<I...>) {
    auto ioports = {ioport_arg(std::get<I>(args))...};
    func(std::get<I>(args)...);
    this->register_io(ioports);
  }
  
  template <typename ...Args1, typename ...Args2>
  void load(void (*func)(Args1...), std::tuple<Args2...>& args) {
      this->load_impl(func, args, make_index_sequence<sizeof...(Args2)>());
  }
  
  template<typename Ret, typename ...Args1, typename ...Args2, size_t ...I>
  void load_impl(Ret (*func)(Args1...), std::tuple<Args2...>& args, index_sequence<I...>) {
    Ret ret;
    auto ioports = {ioport_arg(ret), ioport_arg(std::get<I>(args))...};
    ret = func(std::get<I>(args)...);
    this->register_io(ioports);
  }
  
  template <typename Ret, typename ...Args1, typename ...Args2>
  void load(Ret (*func)(Args1...), std::tuple<Args2...>& args) {
      this->load_impl(func, args, make_index_sequence<sizeof...(Args2)>());
  }
  
  template<typename T, typename ...Args1, typename ...Args2, size_t ...I>
  void load_impl(const T* obj, void (T::*func)(Args1...) const, std::tuple<Args2...>& args, index_sequence<I...>) {
    auto ioports = {ioport_arg(std::get<I>(args))...};
    (obj->*func)(std::get<I>(args)...);
    this->register_io(ioports);
  }
  
  template <typename T, typename ...Args1, typename ...Args2>
  void load(const T* obj, void (T::*func)(Args1...) const, std::tuple<Args2...>& args) {
      this->load_impl(obj, func, args, make_index_sequence<sizeof...(Args2)>());
  }
  
  template<typename T, typename Ret, typename ...Args1, typename ...Args2, size_t ...I>
  void load_impl(const T* obj, Ret (T::*func)(Args1...) const, std::tuple<Args2...>& args, index_sequence<I...>) {
    Ret ret;
    auto ioports = {ioport_arg(ret), ioport_arg(std::get<I>(args))...};
    ret = (obj->*func)(std::get<I>(args)...);
    this->register_io(ioports);
  }
  
  template <typename T, typename Ret, typename ...Args1, typename ...Args2>
  void load(const T* obj, Ret (T::*func)(Args1...) const, std::tuple<Args2...>& args) {
    this->load_impl(obj, func, args, make_index_sequence<sizeof...(Args2)>());
  }
  
  void register_io(const std::vector<ioport_arg>& ioports);

  void compile();
  
  void bind(const std::vector<bus_arg>& args);
  
  context* m_ctx;
};

}
