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

  template <unsigned N>
  const auto bind_input(const ch_busbase<N>& bus) const {
    return make_bit<N>(this->bind_input(get_snode(bus)));
  }

  template <unsigned N>
  const auto bind_output(const ch_bitbase<N>& output) const {
    return make_bus<N>(this->bind_output(get_lnode(output)));
  }

  ch_device();

  void begin_context();

  void end_context();

  void compile();
  
  lnodeimpl* bind_input(const snode& bus) const;
  
  snodeimpl* bind_output(const lnode& output) const;
  
  snodeimpl* get_tap(const std::string& name, uint32_t size) const;

  deviceimpl* impl_;

  friend class simulatorimpl;
};

///////////////////////////////////////////////////////////////////////////////

template <typename Function>
class function_device : public ch_device {
public:

  function_device(const Function& func) : function_(func) {}

  auto operator()() {
    return this->bind();
  }

  template <typename Arg0, typename... Args,
            CH_REQUIRES(is_bus_convertible<Arg0, Args...>::value)>
  auto operator()(const Arg0& arg0, const Args&... args) {
    return this->bind(arg0, args...);
  }

  ~function_device() {}

protected:

  template <typename T>
  struct to_bus_type {
    using type = ch_bus<T::bitcount>;
  };

  template <typename... Ts>
  struct to_bus_type<std::tuple<Ts...>> {
    using type = std::tuple<ch_bus<Ts::bitcount>...>;
  };

  template <typename... Args>
  auto bind(const Args&... args) {
    typename to_bus_type<typename Function::result_type>::type ret;
    this->begin_context();
    {
      std::tuple<ch_bit<std::decay<Args>::type::bitcount>...> func_args;
      this->bind_inputs(func_args, args...);
      auto func_ret = this->invoke(func_args, std::index_sequence_for<Args...>());
      this->bind_outputs(func_ret, ret);
      this->compile();
    }
    this->end_context();
    return ret;
  }

  template<typename... Args, size_t... I>
  auto invoke(const std::tuple<Args...>& args, std::index_sequence<I...>) {
    return function_(std::get<I>(args)...);
  }

  template <typename... FuncArgs, typename Arg, typename... Args>
  void bind_inputs(std::tuple<FuncArgs...>& funcArgs, const Arg& arg, const Args&... args) {
    std::get<(sizeof...(FuncArgs) - 1 - sizeof...(Args))>(funcArgs) = this->bind_input(arg);
    this->bind_inputs(funcArgs, args...);
  }

  template <typename... FuncArgs, typename Arg>
  void bind_inputs(std::tuple<FuncArgs...>& funcArgs, const Arg& arg) {
    std::get<(sizeof...(FuncArgs) - 1)>(funcArgs) = this->bind_input(arg);
  }

  template <typename... FuncArgs>
  void bind_inputs(std::tuple<FuncArgs...>& funcArgs) {
    CH_UNUSED(funcArgs);
    // function has no input argument
  }

  template <typename... FuncRets, typename... Rets>
  void bind_outputs(const std::tuple<FuncRets...>& funcRets, std::tuple<Rets...>& rets) {
    this->bind_outputs(funcRets, rets, std::index_sequence_for<Rets...>());
  }

  template <typename FuncRet, typename Ret>
  void bind_outputs(const FuncRet& funcRet, Ret& ret) {
    ret = this->bind_output(funcRet);
  }

  template <typename... FuncRets, typename... Rets, size_t... I>
  void bind_outputs(const std::tuple<FuncRets...>& funcRets,
                    std::tuple<Rets...>& rets,
                    std::index_sequence<I...>) {
    this->bind_outputs(funcRets, std::get<I>(rets)...);
  }

  template <typename... FuncRets, typename Ret>
  void bind_outputs(const std::tuple<FuncRets...>& funcRets, Ret& ret) {
    ret = this->bind_output(std::get<(sizeof...(FuncRets) - 1)>(funcRets));
  }

  template <typename... FuncRets, typename Ret, typename... Rets>
  void bind_outputs(const std::tuple<FuncRets...>& funcRets, Ret& ret, Rets&... rets) {
    ret = this->bind_output(std::get<(sizeof...(FuncRets) - 1 - sizeof...(Rets))>(funcRets));
    this->bind_outputs(funcRets, rets...);
  }

  Function function_;
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

  auto operator()() {
    return this->bind();
  }

  template <typename Arg0, typename... Args,
            CH_REQUIRES(is_bus_convertible<Arg0, Args...>::value)>
  auto operator()(const Arg0&& arg0, const Args&&... args) {
    return this->bind(std::forward<Arg0>(arg0), std::forward<Args>(args)...);
  }

protected:

  template <typename... Args>
  void bind(const Args&... args) {
    this->begin_context();
    {
      std::tuple<ch_bit<std::decay<Args>::type::bitcount>...> func_args;
      this->invoke(func_args, std::index_sequence_for<Args...>());
      this->bind_io(func_args, std::forward<Args>(args)...);
      this->compile();
    }
    this->end_context();
  }

  template<typename... Args, size_t... I>
  void invoke(std::tuple<Args...>& args, std::index_sequence<I...>) {
    module_->io(std::get<I>(args)...);
  }

  template <typename... FuncArgs, typename... Args>
  void bind_io(std::tuple<FuncArgs...>& func_args, Args&&... args) {
    //--
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
