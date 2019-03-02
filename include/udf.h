#pragma once

#include "logic.h"

namespace ch {
namespace internal {

using udf_output = sdata_type;
using udf_inputs = const sdata_type*;

class udf_iface : public refcounted {
public:
  udf_iface(bool is_seq,
            uint32_t output_size,
            const std::initializer_list<uint32_t>& inputs_size)
    : is_seq_(is_seq)
    , output_size_(output_size)
    , inputs_size_(inputs_size)
  {}

  virtual ~udf_iface() {}

  bool is_seq() const {
    return is_seq_;
  }

  uint32_t output_size() const {
    return output_size_;
  }

  const std::vector<uint32_t>& inputs_size() const {
    return inputs_size_;
  }

  virtual void eval(udf_output&, const udf_inputs&) = 0;

  virtual void init_verilog(std::ostream& out) = 0;

  virtual void to_verilog(std::ostream& out) = 0;

private:

  bool is_seq_;
  uint32_t output_size_;
  std::vector<uint32_t> inputs_size_;
};

template <bool Seq, typename Output_, typename... Inputs_>
struct udf_traits {
  static constexpr int type = traits_udf;
  static constexpr bool is_seq = Seq;
  using Output = Output_;
  using Inputs = std::tuple<Inputs_...>;
};

template <typename T>
inline constexpr bool is_udf_traits_v = bool_constant_v<(T::type == traits_udf)>;

CH_DEF_SFINAE_CHECK(is_udf_type, is_udf_traits_v<typename std::decay_t<T>::traits>);

template <typename Output, typename... Inputs>
class udf_comb : public udf_iface {
public:
  using traits = udf_traits<false, Output, Inputs...>;

  udf_comb() : udf_iface(false, ch_width_v<Output>, {ch_width_v<Inputs>...}) {}

  void init_verilog(std::ostream&) override {}

  void to_verilog(std::ostream&) override {}
};

template <typename Output, typename... Inputs>
class udf_seq : public udf_iface {
public:
  using traits = udf_traits<true, Output, Inputs...>;

  udf_seq() : udf_iface(true, ch_width_v<Output>, {ch_width_v<Inputs>...}) {}

  void init_verilog(std::ostream&) override {}

  void to_verilog(std::ostream&) override {}
};

udf_iface* lookupUDF(const std::type_index& signature, bool has_args);

void registerUDF(const std::type_index& signature, bool has_args, udf_iface* udf);

lnodeimpl* createUDFNode(udf_iface* udf,
                         const std::vector<lnode>& inputs,
                         const source_location& sloc);

template <typename T>
class ch_udf {
public:
  static_assert(is_udf_type_v<T>, "invalid type"); \

  template <typename... Args>
  ch_udf(Args&&... args) {
    udf_ = lookupUDF(std::type_index(typeid(T)), (sizeof...(Args) != 0));
    if (udf_ == nullptr) {
      udf_ = new T(std::forward<Args>(args)...);
      registerUDF(std::type_index(typeid(T)), (sizeof...(Args) != 0), udf_);
    }
    udf_->acquire();
  }

  ~ch_udf() {
    udf_->release();
  }

#define CH_UDF_OP_TMPL(a, i, x) typename __T##i
#define CH_UDF_OP_ASSERT(a, i, x) static_assert(std::is_convertible_v<__T##i, std::tuple_element_t<i, typename T::traits::Inputs>>, "invalid type for input"#i)
#define CH_UDF_OP_DECL(a, i, x) const __T##i& arg##i
#define CH_UDF_OP_ARG(a, i, x) to_lnode<std::tuple_element_t<i, typename T::traits::Inputs>>(arg##i, sloc)
#define CH_UDF_OP(...) \
  template <CH_FOR_EACH(CH_UDF_OP_TMPL, , CH_SEP_COMMA, __VA_ARGS__)> \
  auto operator()(CH_FOR_EACH(CH_UDF_OP_DECL, , CH_SEP_COMMA, __VA_ARGS__), CH_SLOC) const { \
    static_assert(CH_NARG(__VA_ARGS__) == std::tuple_size_v<typename T::traits::Inputs>, "number of inputs mismatch"); \
    CH_FOR_EACH(CH_UDF_OP_ASSERT, , CH_SEP_SEMICOLON, __VA_ARGS__); \
    auto node = createUDFNode(udf_, {CH_FOR_EACH(CH_UDF_OP_ARG, , CH_SEP_COMMA, __VA_ARGS__)}, sloc); \
    return make_type<typename T::traits::Output>(node, sloc); \
  }
CH_VA_ARGS_MAP(CH_UDF_OP)
#undef CH_UDF_OP_TMPL
#undef CH_UDF_OP_ASSERT
#undef CH_UDF_OP_DECL
#undef CH_UDF_OP_ARG
#undef CH_UDF_OP

protected:

  udf_iface* udf_;
};

}}
