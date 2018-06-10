#pragma once

#include "logic.h"

namespace ch {
namespace internal {

class udf_iface : public refcounted {
public:
  udf_iface(uint32_t delta,
            bool init,
            bool enable,
            uint32_t output_size,
            const std::initializer_list<uint32_t>& inputs_sizes)
    : delta_(delta)
    , init_(init)
    , enable_(enable)
    , output_size_(output_size)
    , inputs_size_(inputs_sizes)
  {}

  virtual ~udf_iface() {}

  uint32_t delta() const {
    return delta_;
  }

  bool init() const {
    return init_;
  }

  bool enable() const {
    return enable_;
  }

  uint32_t output_size() const {
    return output_size_;
  }

  const std::vector<uint32_t>& inputs_sizes() const {
    return inputs_size_;
  }

  virtual void initialize() = 0;

  virtual void reset(bitvector*, const std::vector<const bitvector*>&) = 0;

  virtual void eval(bitvector*, const std::vector<const bitvector*>&) = 0;

  virtual void init_verilog(std::ostream& out) = 0;

  virtual void to_verilog(std::ostream& out) = 0;

private:

  uint32_t delta_;
  bool init_;
  bool enable_;
  uint32_t output_size_;
  std::vector<uint32_t> inputs_size_;
};

template <uint32_t Delta, bool Init, bool Enable, typename Output_, typename... Inputs_>
struct udf_traits {
  static constexpr uint32_t delta  = Delta;
  static constexpr bool has_init   = Init;
  static constexpr bool has_enable = Enable;
  using Output = Output_;
  using Inputs = std::tuple<Inputs_...>;
};

template <typename Output, typename... Inputs>
class udf_comb : public udf_iface {
public:
  using traits = udf_traits<0, false, false, Output, Inputs...>;

  udf_comb() : udf_iface(0, false, false, width_v<Output>, {width_v<Inputs>...}) {}

  void initialize() override {}

  void reset(bitvector*, const std::vector<const bitvector*>&) override {}

  void init_verilog(std::ostream&) override {}

  void to_verilog(std::ostream&) override {}
};

template <uint32_t Delta, bool Init, bool Enable, typename Output, typename... Inputs>
class udf_seq : public udf_iface {
public:
  static_assert(Delta != 0, "invalid delta value");
  using traits = udf_traits<Delta, Init, Enable, Output, Inputs...>;

  udf_seq() : udf_iface(Delta, Init, Enable, width_v<Output>, {width_v<Inputs>...}) {}

  void initialize() override {}

  void reset(bitvector*, const std::vector<const bitvector*>&) override {}

  void init_verilog(std::ostream&) override {}

  void to_verilog(std::ostream&) override {}
};

udf_iface* lookupUDF(const std::type_index& signature);

udf_iface* registerUDF(const std::type_index& signature, udf_iface* udf);

lnodeimpl* createUDFNode(udf_iface* udf,
                         const std::initializer_list<lnode>& inputs,
                         const source_location& sloc);

template <typename T>
udf_iface* get_udf() {
  auto signature = std::type_index(typeid(T));
  auto udf = lookupUDF(signature);
  if (nullptr == udf) {
    udf = registerUDF(signature, new T());
  }
  return udf;
}

template <typename T, typename... Args>
auto ch_udf(Args&& ...args) {
  static_assert(sizeof...(Args) >= std::tuple_size_v<typename T::traits::Inputs>, "number of inputs mismatch");
  auto node = createUDFNode(get_udf<T>(), {get_lnode(args)...}, source_location());
  return make_type<typename T::traits::Output>(node);
}

}}
