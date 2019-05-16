#pragma once

#include "logic.h"

namespace ch {
namespace internal {

using udf_output = sdata_type;
using udf_inputs = const sdata_type*;
class udf_base;
class udf_iface;

enum class udf_verilog_mode { header, declaration, body };

refcounted* lookupUDF(const std::type_index& signature, bool has_args);

refcounted* createUDF(const std::type_index& signature,
                      bool has_args,
                      const std::string& name,
                      bool is_seq,
                      uint32_t output_size,
                      const std::initializer_list<uint32_t>& inputs_size,
                      udf_base* udf);

lnodeimpl* createUDFNode(refcounted* handle, const std::vector<lnode>& inputs);

void registerUDF(const std::type_index& signature,
                 const std::string& name,
                 bool is_seq,
                 udf_iface* udf);

///////////////////////////////////////////////////////////////////////////////

class udf_iface: public refcounted {
public:

  udf_iface() {}
  virtual ~udf_iface() {}

  virtual void eval() = 0;

  virtual void reset() = 0;

  virtual bool to_verilog(std::ostream&, udf_verilog_mode) = 0;
};

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

  virtual bool to_verilog(std::ostream& out, udf_verilog_mode mode) = 0;
};

///////////////////////////////////////////////////////////////////////////////

template <typename Output, typename... Inputs>
class udf_comb : public udf_base {
public:

  using traits = udf_traits<false, Output, Inputs...>;

  bool to_verilog(std::ostream&, udf_verilog_mode) override { return false; }
};

///////////////////////////////////////////////////////////////////////////////

template <typename Output, typename... Inputs>
class udf_seq : public udf_base {
public:

  using traits = udf_traits<true, Output, Inputs...>;

  bool to_verilog(std::ostream&, udf_verilog_mode) override { return false; }
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

///////////////////////////////////////////////////////////////////////////////

CH_DEF_SFINAE_CHECK(has_system_io, is_system_io_v<decltype(T::io)>);

template<typename T>
using detect_eval_t = decltype(std::declval<T&>().eval());

template<typename T>
using detect_reset_t = decltype(std::declval<T&>().reset());

template<typename T>
using to_verilog = decltype(std::declval<T&>().to_verilog(
  std::declval<std::ostream&>(), std::declval<udf_verilog_mode&>()));

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class udf_wrapper : public udf_iface {
public:
  template <typename... Args>
  udf_wrapper(Args&&... args) : udf_(std::forward<Args>(args)...) {}

  void eval() override {
    udf_.eval();
  }

  void reset() override {
    if constexpr (is_detected_v<detect_reset_t, T>) {
      udf_.reset();
    }
  }

  bool to_verilog(std::ostream& out, udf_verilog_mode mode) override {
    if constexpr (is_detected_v<to_verilog, T>) {
      return udf_.to_verilog(out, mode);
    } else {
      return false;
    }
  }

  auto& io() const {
    return udf_.io;
  }

protected:
  T udf_;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class ch_udf_comb {
public:
  static_assert(has_system_io_v<T>, "missing io port");
  static_assert(is_detected_v<detect_eval_t, T>, "missing eval() method");
  using io_type = ch_flip_io<ch_logic_io<decltype(T::io)>>;

  io_type io;

  template <typename... Args>
  ch_udf_comb(Args&&... args)
    : io(this->create(std::forward<Args>(args)...)->io())
  {}

  ch_udf_comb(ch_udf_comb&& other)
    : io(std::move(other.io))
  {}

protected:

  template <typename... Args>
  auto create(Args&&... args) {
    CH_SOURCE_LOCATION(2);
    auto obj = new udf_wrapper<T>(std::forward<Args>(args)...);
    registerUDF(std::type_index(typeid(T)),
                idname<T>(),
                true,
                obj);
    return obj;
  }

  ch_udf_comb(const ch_udf_comb& other) = delete;

  ch_udf_comb& operator=(const ch_udf_comb& other) = delete;

  ch_udf_comb& operator=(ch_udf_comb&& other) = delete;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class ch_udf_seq {
public:
  static_assert(has_system_io_v<T>, "missing io port");
  static_assert(is_detected_v<detect_eval_t, T>, "missing eval() method");
  using io_type = ch_flip_io<ch_logic_io<decltype(T::io)>>;

  io_type io;

  template <typename... Args>
  ch_udf_seq(Args&&... args)
    : io(this->create(std::forward<Args>(args)...)->io())
  {}

  ch_udf_seq(ch_udf_seq&& other)
    : io(std::move(other.io))
  {}

protected:

  template <typename... Args>
  auto create(Args&&... args) {
    CH_SOURCE_LOCATION(2);
    auto obj = new udf_wrapper<T>(std::forward<Args>(args)...);
    registerUDF(std::type_index(typeid(T)),
                idname<T>(),
                true,
                obj);
    return obj;
  }

  ch_udf_seq(const ch_udf_seq& other) = delete;

  ch_udf_seq& operator=(const ch_udf_seq& other) = delete;

  ch_udf_seq& operator=(ch_udf_seq&& other) = delete;
};

}}
