#pragma once

#include "port.h"

namespace cash {
namespace internal {

class deviceimpl;

class ch_device {
public:

  ch_device();
  virtual ~ch_device();

  ch_device(const ch_device& device);

  ch_device& operator=(const ch_device& device);
  
  template <unsigned N> 
  const auto get_tap(const std::string& name) {
    return make_bus<N>(this->get_tap(name, N));
  }
  
  void to_verilog(const std::string& module_name, std::ostream& out);  
  
  void dump_stats(std::ostream& out);
    
protected:

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

template <typename F>
class function_device : public ch_device {
public:

  function_device() : function_(nullptr) {}

  function_device(const F& function) {
    function_ = new F(function);
  }

  ~function_device() {
    delete function_;
  }

  auto operator()() {
    return function_device_impl<typename F::result_type>::bind(this);
  }

  template <typename Arg0, typename... Args,
            CH_REQUIRES(are_bus_convertible<Arg0, Args...>::value)>
  auto operator()(const Arg0& arg0, const Args&... args) {
    return function_device_impl<typename F::result_type>::bind(this, arg0, args...);
  }

protected:

  template<typename... Args, size_t... I>
  auto invoke(const std::tuple<Args...>& args, std::index_sequence<I...>) {
    return (*function_)(std::get<I>(args)...);
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

  F* function_;

  template <typename Ret> friend struct function_device_impl;
};

template <typename F>
class Callable {
public:
  using function_type = typename function_traits<F>::type;
  using result_type = typename function_type::result_type;

  template <typename... Ts>
  Callable(const Ts&... args) {
    functor_ = new F(args...);
  }

  template <typename... Ts>
  result_type operator()(Ts&& ...args) const {
    return functor_->operator()(std::forward<Ts>(args)...);
  }

  ~Callable() {
    delete functor_;
  }

protected:
  F* functor_;
};

template <typename F>
class functor_device : public function_device<Callable<F>> {
public:
  using base = function_device<Callable<F>>;
  using base::function_;

  template <typename... Ts>
  functor_device(const Ts&... args) {
    this->begin_context();
    function_ = new Callable<F>(args...);
    this->end_context();
  }
};

template <typename M>
class module_device : public ch_device {
public:

  template <typename... Ts>
  module_device(const Ts&... args) {
    this->begin_context();
    module_ = new M(args...);
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

  M* module_;
};

template <typename F, typename... Ts>
auto ch_function(Ts&&... args) {
  return functor_device<F>(args...);
}

template <typename F>
auto ch_function(const F& func) {
  return function_device<typename function_traits<F>::type>(func);
}

template <typename Ret, typename... Ts>
auto ch_function(Ret (*func)(Ts...)) {
  return function_device<std::function<Ret(Ts...)>>(std::function<Ret(Ts...)>(func));
}

template <typename C, typename... Ts,
          CH_REQUIRES(std::is_class<C>::value)>
auto ch_module(Ts&&... args) {
  return module_device<C>(args...);
}

}
}
