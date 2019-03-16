#pragma once

#include "logic.h"

namespace ch {
namespace internal {

using udf_output = sdata_type;
using udf_inputs = const sdata_type*;
class udf_base;

refcounted* lookupUDF(const std::type_index& signature, bool has_args);

refcounted* createUDF(const std::type_index& signature,
                      bool has_args,
                      const std::string& name,
                      bool is_seq,
                      uint32_t output_size,
                      const std::initializer_list<uint32_t>& inputs_size,
                      udf_base* udf);

lnodeimpl* createUDFNode(refcounted* handle, const std::vector<lnode>& inputs);

///////////////////////////////////////////////////////////////////////////////

template <bool Seq, typename Output_, typename... Inputs_>
struct udf_traits {
  static constexpr int type = traits_udf;
  static constexpr bool is_seq = Seq;
  using Output = Output_;
  using Inputs = std::tuple<Inputs_...>;
};

template <typename T, std::size_t... Is>
static constexpr auto udf_inputs_size_impl(std::index_sequence<Is...>) {
  return std::initializer_list<uint32_t>{(ch_width_v<std::tuple_element_t<Is, T>>)...};
}

template <typename T>
static constexpr auto udf_inputs_size() {
   return udf_inputs_size_impl<T>(std::make_index_sequence<std::tuple_size_v<T>>{});
}

template <typename T>
inline constexpr bool is_udf_traits_v = bool_constant_v<(T::type == traits_udf)>;

CH_DEF_SFINAE_CHECK(is_udf_type, is_udf_traits_v<typename std::decay_t<T>::traits>);

///////////////////////////////////////////////////////////////////////////////

class udf_base : public refcounted {
public:

  udf_base() {}
  virtual ~udf_base() {}

  virtual void eval(udf_output&, const udf_inputs&) = 0;

  virtual void init_verilog(std::ostream& out) = 0;

  virtual void to_verilog(std::ostream& out) = 0;
};

///////////////////////////////////////////////////////////////////////////////

template <typename Output, typename... Inputs>
class udf_comb : public udf_base {
public:

  using traits = udf_traits<false, Output, Inputs...>;

  void init_verilog(std::ostream&) override {}

  void to_verilog(std::ostream&) override {}
};

///////////////////////////////////////////////////////////////////////////////

template <typename Output, typename... Inputs>
class udf_seq : public udf_base {
public:

  using traits = udf_traits<true, Output, Inputs...>;

  void init_verilog(std::ostream&) override {}

  void to_verilog(std::ostream&) override {}
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class ch_udf {
public:
  static_assert(is_udf_type_v<T>, "invalid type");

  template <typename... Args>
  ch_udf(Args&&... args) {
    handle_ = lookupUDF(std::type_index(typeid(T)), (sizeof...(Args) != 0));
    if (handle_ == nullptr) {
      auto udf = new T(std::forward<Args>(args)...);
      handle_ = createUDF(std::type_index(typeid(T)),
                          (sizeof...(Args) != 0),
                          idname<T>(),
                          T::traits::is_seq,
                          ch_width_v<typename T::traits::Output>,
                          udf_inputs_size<typename T::traits::Inputs>(),
                          udf);
    }
    handle_->acquire();
  }

  ~ch_udf() {
    handle_->release();
  }

  template <typename... Args>
  auto operator()(const Args&... args) const {
    static_assert(sizeof...(Args) == std::tuple_size_v<typename T::traits::Inputs>, "number of inputs mismatch");
    CH_SOURCE_LOCATION(1);
    return this->call<Args...>(args..., std::make_index_sequence<sizeof...(Args)>{});
  }

protected:

  template <typename... Args, std::size_t... Is>
  auto call(const Args&... args, std::index_sequence<Is...>) const {
    static_assert((std::is_convertible_v<Args, std::tuple_element_t<Is, typename T::traits::Inputs>> && ...), "invalid input type");
    auto node = createUDFNode(handle_, {to_lnode<std::tuple_element_t<Is, typename T::traits::Inputs>>(args)...});
    return make_type<typename T::traits::Output>(node);
  }

  refcounted* handle_;
};

}}
