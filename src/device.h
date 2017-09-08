#pragma once

#include "bit.h"
#include "bus.h"

namespace cash {
namespace internal {

class deviceimpl;

class ch_device {
public:
  
  template <typename Function, typename ...Args>  
  ch_device(const Function& func, Args&&... args) : ch_device() {
    this->init(to_function(func), args...);   
  }
  
  template <typename FuncRet, typename ...FuncArgs, typename ...Args>  
  ch_device(FuncRet (*func)(FuncArgs...), Args&&... args) : ch_device() {
    this->init(std::function<FuncRet(FuncArgs...)>(func), args...);
  }
  
  ~ch_device();
  
  template <unsigned N> 
  const auto get_tap(const std::string& name) {
    return make_bus<N>(this->get_tap(name, N));
  }
  
  void to_verilog(const std::string& module_name, std::ostream& out);  
  
  void dump_stats(std::ostream& out);
    
protected:
  
  template <typename T>
  struct to_value_type {
    using value = T;
  };
  
  template <unsigned N>
  struct to_value_type<ch_bitbase<N>> {
    using value = ch_bit<N>;
  };
  
  template <typename T>
  struct output_size {
    static const size_t value = 1;
  };
  
  template <typename ...OutputArgs>
  struct output_size<std::tuple<OutputArgs...>> {
    static const size_t value = sizeof...(OutputArgs);
  };
  
  template <bool Enable, size_t I>
  struct bind_output_impl {};
  
  template <size_t I>
  struct bind_output_impl<false, I> {
    template <typename ...OutputArgs, typename Arg>
    static void bind(const ch_device& dev, const std::tuple<OutputArgs...>& outputs, Arg&& arg) {
      CH_UNUSED(dev, outputs, arg);
      // do nothing!
    }
  };
  
  template <size_t I>
  struct bind_output_impl<true, I> {
    template <typename ...OutputArgs, typename Arg>
    static void bind(const ch_device& dev, const std::tuple<OutputArgs...>& outputs, Arg&& arg) {
      std::forward<Arg>(arg) = dev.bind_output(std::get<sizeof...(OutputArgs)-I>(outputs));
    }
  };
  
  template <size_t I>
  struct bind_outputs_impl {
    template <typename ...OutputArgs, typename Arg, typename ...Args>
    static void bind(const ch_device& dev, const std::tuple<OutputArgs...>& outputs, Arg&& arg, Args&&... args) {
      bind_output_impl<(I <= sizeof...(OutputArgs)), I>::bind(dev, outputs, arg);
      bind_outputs_impl<I-1>::bind(dev, outputs, args...);
    }
  };
  
  template <size_t I>
  struct bind_outputs_impl2 {
    template <typename Ret, typename Arg, typename ...Args>
    static void bind(const ch_device& dev, const Ret& output, Arg&& arg, Args&&... args) {
      bind_outputs_impl2<I-1>::bind(dev, output, args...);
    }
  };
  
  template <size_t I>
  struct bind_inputs_impl {
    template <typename ...InputArgs, typename Arg, typename ...Args>
    static void bind(const ch_device& dev, std::tuple<InputArgs...>& inputs, Arg&& arg, Args&&... args) {
      std::get<sizeof...(InputArgs)-I>(inputs) = dev.bind_input(std::forward<Arg>(arg));
      bind_inputs_impl<I-1>::bind(dev, inputs, args...);
    }
  };
  
  template<typename FuncRet, typename ...FuncArgs, typename ...Args, size_t ...I>
  FuncRet load_impl(std::function<FuncRet(FuncArgs...)> func, std::tuple<Args...>& args, std::index_sequence<I...>) {
    return func(std::get<I>(args)...);
  }
  
  template <typename FuncRet, typename ...FuncArgs, typename ...Args>
  void init(const std::function<FuncRet(FuncArgs...)>& func, Args&&... args) {    
    static_assert(sizeof...(FuncArgs) + output_size<FuncRet>::value == sizeof...(Args), "number of arguments mismatch");
    this->begin_context();
    {
      std::tuple<typename to_value_type<typename std::remove_const<
          typename std::remove_reference<FuncArgs>::type>::type>::value...> func_args;
      this->bind_inputs(func_args, args...);
      FuncRet ret(this->load_impl(func, func_args, std::index_sequence_for<FuncArgs...>()));
      this->bind_outputs(ret, args...);
    }
    this->end_context();
  }
  
  template <typename ...InputArgs, typename ...Args>
  void bind_inputs(std::tuple<InputArgs...>& inputs, Args&&... args) {
    bind_inputs_impl<sizeof...(InputArgs)>::bind(*this, inputs, args...);
  }
  
  template <typename ...OutputArgs, typename ...Args>
  void bind_outputs(const std::tuple<OutputArgs...>& outputs, Args&&... args) {
    bind_outputs_impl<sizeof...(Args)>::bind(*this, outputs, args...);
  }
  
  template <typename Ret, typename ...Args>
  void bind_outputs(const Ret& output, Args&&... args) {
    bind_outputs_impl2<sizeof...(Args)>::bind(*this, output, args...);
  }

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
  
  lnodeimpl* bind_input(const snode& bus) const;
  
  snodeimpl* bind_output(const lnode& output) const;
  
  snodeimpl* get_tap(const std::string& name, uint32_t size) const;

  deviceimpl* impl_;

  friend class simulatorimpl;
};

template <>
struct ch_device::bind_inputs_impl<1> {
  template <typename ...InputArgs, typename Arg, typename ...Args>
  static void bind(const ch_device& dev, std::tuple<InputArgs...>& inputs, Arg&& arg, Args&&... args) {
    std::get<sizeof...(InputArgs)-1>(inputs) = dev.bind_input(std::forward<Arg>(arg));
  }
  
  template <typename ...InputArgs, typename Arg>
  static void bind(const ch_device& dev, std::tuple<InputArgs...>& inputs, Arg&& arg) {
    std::get<sizeof...(InputArgs)-1>(inputs) = dev.bind_input(std::forward<Arg>(arg));
  }
};

template <>
struct ch_device::bind_inputs_impl<0> {
  template <typename ...InputArgs, typename ...Args>
  static void bind(const ch_device& dev, std::tuple<InputArgs...>& inputs, Args&&... args) {
    // no inputs!
  }
};

template <>
struct ch_device::bind_outputs_impl<1> {  
  template <typename ...OutputArgs, typename Arg>
  static void bind(const ch_device& dev, const std::tuple<OutputArgs...>& outputs, Arg&& arg) {
    bind_output_impl<true, 1>::bind(dev, outputs, arg);
  }
};

template <>
struct ch_device::bind_outputs_impl<0> {
  template <typename ...OutputArgs, typename Arg, typename ...Args>
  static void bind(const ch_device& dev, const std::tuple<OutputArgs...>& outputs, Args&&... args) {
    // no inputs!
  }
};

template <>
struct ch_device::bind_outputs_impl2<1> {
  template <typename Ret, typename Arg, typename ...Args>
  static void bind(const ch_device& dev, const Ret& output, Arg&& arg) {
    std::forward<Arg>(arg) = dev.bind_output(output);
  }
};

template <>
struct ch_device::bind_outputs_impl2<0> {
  template <typename Ret, typename Arg, typename ...Args>
  static void bind(const ch_device& dev, const Ret& output, Args&&... args) {
    // no inputs!
  }
};

}
}
