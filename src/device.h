#pragma once

#include "port.h"

namespace cash {
namespace internal {

class deviceimpl;

class ch_device {
public:
  
  ~ch_device();
  
  template <unsigned N> 
  const auto get_tap(const std::string& name) {
    return make_bus<N>(this->get_tap(name, N));
  }
  
  void to_verilog(const std::string& module_name, std::ostream& out);  
  
  void dump_stats(std::ostream& out);
    
protected:

  ch_device();

  void begin_context();

  void end_context();

  void compile();
  
  snodeimpl* get_tap(const std::string& name, uint32_t size) const;

  deviceimpl* impl_;

  friend class simulatorimpl;
};

///////////////////////////////////////////////////////////////////////////////

template <typename Ret>
struct function_device_impl {
  template <typename Device, typename... Args>
  static auto bind(Device* dev, const Args&... args) {
    ch_bus<Ret::bitcount> ret;
    dev->begin_context();
    {
      std::tuple<ch_bit<std::decay<Args>::type::bitcount>...> func_args;
      dev->bind_inputs(func_args, args...);
      auto func_ret = dev->invoke(func_args, std::index_sequence_for<Args...>());
      dev->bind_outputs(func_ret, ret);
      dev->compile();
    }
    dev->end_context();
    return ret;
  }
};

template <typename... Rets>
struct function_device_impl< std::tuple<Rets...> > {
  template <typename Device, typename... Args>
  static auto bind(Device* dev, const Args&... args) {
    std::tuple<ch_bus<Rets::bitcount>...> ret;
    dev->begin_context();
    {
      std::tuple<ch_bit<std::decay<Args>::type::bitcount>...> func_args;
      dev->bind_inputs(func_args, args...);
      auto func_ret = dev->invoke(func_args, std::index_sequence_for<Args...>());
      dev->bind_outputs(func_ret, ret);
      dev->compile();
    }
    dev->end_context();
    return ret;
  }
};

template <>
struct function_device_impl<void> {
  template <typename Device, typename... Args>
  static void bind(Device* dev, const Args&... args) {
    dev->begin_context();
    {
      std::tuple<ch_bit<std::decay<Args>::type::bitcount>...> func_args;
      dev->bind_inputs(func_args, args...);
      dev->invoke(func_args, std::index_sequence_for<Args...>());
      dev->compile();
    }
    dev->end_context();
  }
};

template <typename Function>
class function_device : public ch_device {
public:

  function_device(const Function& func) : function_(func) {}

  auto operator()() {
    return function_device_impl<typename Function::result_type>::bind(this);
  }

  template <typename Arg0, typename... Args,
            CH_REQUIRES(are_bus_convertible<Arg0, Args...>::value)>
  auto operator()(const Arg0& arg0, const Args&... args) {
    return function_device_impl<typename Function::result_type>::bind(this, arg0, args...);
  }

  ~function_device() {}

protected:

  template<typename... Args, size_t... I>
  auto invoke(const std::tuple<Args...>& args, std::index_sequence<I...>) {
    return function_(std::get<I>(args)...);
  }

  template <typename... FuncArgs, typename Arg, typename... Args>
  void bind_inputs(std::tuple<FuncArgs...>& funcArgs, const Arg& arg, const Args&... args) {
    std::get<(sizeof...(FuncArgs) - 1 - sizeof...(Args))>(funcArgs) = ch_input(arg);
    this->bind_inputs(funcArgs, args...);
  }

  template <typename... FuncArgs, typename Arg>
  void bind_inputs(std::tuple<FuncArgs...>& funcArgs, const Arg& arg) {
    std::get<(sizeof...(FuncArgs) - 1)>(funcArgs) = ch_input(arg);
  }

  template <typename... FuncArgs>
  void bind_inputs(std::tuple<FuncArgs...>& funcArgs) {
    CH_UNUSED(funcArgs);
    // no input argument
  }

  template <typename... FuncRets, typename... Rets>
  void bind_outputs(const std::tuple<FuncRets...>& funcRets, std::tuple<Rets...>& rets) {
    this->bind_outputs(funcRets, rets, std::index_sequence_for<Rets...>());
  }

  template <typename FuncRet, typename Ret>
  void bind_outputs(const FuncRet& funcRet, Ret& ret) {
    ret = ch_output(funcRet);
  }

  template <typename... FuncRets, typename... Rets, size_t... I>
  void bind_outputs(const std::tuple<FuncRets...>& funcRets,
                    std::tuple<Rets...>& rets,
                    std::index_sequence<I...>) {
    this->bind_outputs(funcRets, std::get<I>(rets)...);
  }

  template <typename... FuncRets, typename Ret>
  void bind_outputs(const std::tuple<FuncRets...>& funcRets, Ret& ret) {
    ret = ch_output(std::get<(sizeof...(FuncRets) - 1)>(funcRets));
  }

  template <typename... FuncRets, typename Ret, typename... Rets>
  void bind_outputs(const std::tuple<FuncRets...>& funcRets, Ret& ret, Rets&... rets) {
    ret = ch_output(std::get<(sizeof...(FuncRets) - 1 - sizeof...(Rets))>(funcRets));
    this->bind_outputs(funcRets, rets...);
  }

  Function function_;

  template <typename Ret> friend struct function_device_impl;
};

template <typename T>
class module_device : public ch_device {
public:

  template <typename... Args>
  module_device(const Args&... args) {
    this->begin_context();
    module_ = new T(args...);
    this->end_context();
  }

  ~module_device() {
    delete module_;
  }

  void operator()() {
    this->bind();
  }

  template <typename Arg0, typename... Args,
            CH_REQUIRES(are_bus_convertible<Arg0, Args...>::value)>
  void operator()(Arg0&& arg0, Args&&... args) {
    this->bind(arg0, args...);
  }

protected:

  void bind() {
    this->begin_context();
    this->compile();
    this->end_context();
  }

  template <typename... Args,
            CH_REQUIRES(sizeof...(Args) != 0)>
  void bind(Args&&... args) {
    this->begin_context();
    module_->io(args...);
    this->compile();
    this->end_context();
  }

  T* module_;
};

template <typename Function>
auto ch_function(const Function& func) {
  return function_device<typename function_traits<Function>::type>(func);
}

template <typename Ret, typename... Args>
auto ch_function(Ret (*func)(Args...)) {
  return function_device<std::function<Ret(Args...)>>(std::function<Ret(Args...)>(func));
}

template <typename Class, typename... Args>
auto ch_module(Args&&... args) {
  return module_device<Class>(args...);
}

}
}
