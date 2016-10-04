#pragma once

#include "bitv.h"
#include "bus.h"

namespace chdl_internal {

class context;

context* ctx_begin();
void ctx_end();

class ch_device {
public:
  
  template <typename Function, typename ...Args>  
  ch_device(const Function& func, const Args&... args) {
    m_ctx = ctx_begin();
    this->load(to_function(func), args...);
    this->compile();
    ctx_end();
  }
  
  template <typename FuncRet, typename ...FuncArgs, typename ...Args>  
  ch_device(FuncRet (*func)(FuncArgs...), const Args&... args) {
    m_ctx = ctx_begin();
    this->load(std::function<FuncRet(FuncArgs...)>(func), args...);
    this->compile();
    ctx_end();
  }
  
  virtual ~ch_device();
  
  void toVerilog(const std::string& module_name, std::ostream& out);  
  
protected:
  
  template <typename T>
  struct to_value_type {
    typedef T value;
  };
  
  template <unsigned N>
  struct to_value_type< ch_bitbase<N> > {
    typedef ch_bitv<N> value;
  };
  
  template <typename T>
  struct output_size {};
  
  template <typename ...OutputArgs>
  struct output_size< std::tuple<OutputArgs...> > {
    static const size_t value = sizeof...(OutputArgs);
  };
  
  template <unsigned N>
  struct output_size< ch_bitv<N> > {
    static const size_t value = 1;
  };
  
  template <bool Enable, size_t I>
  struct bind_output_impl {};
  
  template <size_t I>
  struct bind_output_impl<false, I> {
    template <typename ...OutputArgs, typename Arg>
    static void bind(const ch_device& dev, const std::tuple<OutputArgs...>& outputs, const Arg& arg) {
      // do nothing!
    }
  };
  
  template <size_t I>
  struct bind_output_impl<true, I> {
    template <typename ...OutputArgs, typename Arg>
    static void bind(const ch_device& dev, const std::tuple<OutputArgs...>& outputs, const Arg& arg) {
      dev.bind_output(I-1, std::get<sizeof...(OutputArgs)-I>(outputs), arg);
    }
  };
  
  template <size_t I>
  struct bind_outputs_impl {
    template <typename ...OutputArgs, typename Arg, typename ...Args>
    static void bind(const ch_device& dev, const std::tuple<OutputArgs...>& outputs, const Arg& arg, const Args&... args) {
      bind_output_impl<(I <= sizeof...(OutputArgs)), I>::bind(dev, outputs, arg);
      bind_outputs_impl<I-1>::bind(dev, outputs, args...);
    }
  };
  
  template <size_t I>
  struct bind_outputs_impl2 {
    template <typename Ret, typename Arg, typename ...Args>
    static void bind(const ch_device& dev, const Ret& output, const Arg& arg, const Args&... args) {
      bind_outputs_impl2<I-1>::bind(dev, output, args...);
    }
  };
  
  template <size_t I>
  struct bind_inputs_impl {
    template <typename ...InputArgs, typename Arg, typename ...Args>
    static void bind(const ch_device& dev, const std::tuple<InputArgs...>& inputs, const Arg& arg, const Args&... args) {
      dev.bind_input(I-1, std::get<sizeof...(InputArgs)-I>(inputs), arg);
      bind_inputs_impl<I-1>::bind(dev, inputs, args...);
    }
  };
  
  template<typename FuncRet, typename ...FuncArgs, typename ...Args, size_t ...I>
  FuncRet load_impl(std::function<FuncRet(FuncArgs...)> func, std::tuple<Args...>& args, index_sequence<I...>) {
    return func(std::get<I>(args)...);
  }
  
  template <typename FuncRet, typename ...FuncArgs, typename ...Args>
  void load(const std::function<FuncRet(FuncArgs...)>& func, const Args&... args) {
    static_assert(sizeof...(FuncArgs) + output_size<FuncRet>::value == sizeof...(Args), "number of arguments mismatch!");
    std::tuple<typename to_value_type<typename std::remove_const<
          typename std::remove_reference<FuncArgs>::type >::type>::value...> func_args;
    this->bind_inputs(func_args, args...);
    FuncRet ret(this->load_impl(func, func_args, make_index_sequence<sizeof...(FuncArgs)>()));
    this->bind_outputs(ret, args...);
  }
  
  template <typename ...InputArgs, typename ...Args>
  void bind_inputs(const std::tuple<InputArgs...>& inputs, const Args&... args) {
    bind_inputs_impl<sizeof...(InputArgs)>::bind(*this, inputs, args...);
  }
  
  template <typename ...OutputArgs, typename ...Args>
  void bind_outputs(const std::tuple<OutputArgs...>& outputs, const Args&... args) {
    bind_outputs_impl<sizeof...(Args)>::bind(*this, outputs, args...);
  }
  
  template <typename Ret, typename ...Args>
  void bind_outputs(const Ret& output, const Args&... args) {
    bind_outputs_impl2<sizeof...(Args)>::bind(*this, output, args...);
  }

  template <unsigned N>
  void bind_input(unsigned index, const ch_bitbase<N>& input, const ch_busbase<N>& bus) const {
    this->bind_input(index, static_cast<lnode>(input), static_cast<snode>(bus));
  }
  
  template <unsigned N>
  void bind_output(unsigned index, const ch_bitbase<N>& output, const ch_busbase<N>& bus) const {
    this->bind_output(index, static_cast<lnode>(output), static_cast<snode>(bus));
  }
  
  void bind_input(unsigned index, const lnode& input, const snode& bus) const;
  
  void bind_output(unsigned index, const lnode& output, const snode& bus) const;
  
  void compile();
  
  context* m_ctx;
};

template <>
struct ch_device::bind_inputs_impl<1> {
  template <typename ...InputArgs, typename Arg, typename ...Args>
  static void bind(const ch_device& dev, const std::tuple<InputArgs...>& inputs, const Arg& arg, const Args&... args) {
    dev.bind_input(0, std::get<sizeof...(InputArgs)-1>(inputs), arg);
  }
  
  template <typename ...InputArgs, typename Arg>
  static void bind(const ch_device& dev, const std::tuple<InputArgs...>& inputs, const Arg& arg) {
    dev.bind_input(0, std::get<sizeof...(InputArgs)-1>(inputs), arg);
  }
};

template <>
struct ch_device::bind_inputs_impl<0> {
  template <typename ...InputArgs, typename ...Args>
  static void bind(const ch_device& dev, const std::tuple<InputArgs...>& inputs, const Args&... args) {
    // no inputs!
  }
};

template <>
struct ch_device::bind_outputs_impl<1> {  
  template <typename ...OutputArgs, typename Arg>
  static void bind(const ch_device& dev, const std::tuple<OutputArgs...>& outputs, const Arg& arg) {
    bind_output_impl<true, 1>::bind(dev, outputs, arg);
  }
};

template <>
struct ch_device::bind_outputs_impl<0> {
  template <typename ...OutputArgs, typename Arg, typename ...Args>
  static void bind(const ch_device& dev, const std::tuple<OutputArgs...>& outputs, const Args&... args) {
    // no inputs!
  }
};

template <>
struct ch_device::bind_outputs_impl2<1> {
  template <typename Ret, typename Arg, typename ...Args>
  static void bind(const ch_device& dev, const Ret& output, const Arg& arg) {
    dev.bind_output(0, output, arg);
  }
};

template <>
struct ch_device::bind_outputs_impl2<0> {
  template <typename Ret, typename Arg, typename ...Args>
  static void bind(const ch_device& dev, const Ret& output, const Args&... args) {
    // no inputs!
  }
};

}
