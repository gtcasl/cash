#pragma once

#include "ioport.h"

namespace ch {
namespace internal {

class udf_iface;

enum class udf_verilog { header, declaration, body };

void createUDFNode(const std::string& name, 
                   bool is_seq, 
                   udf_iface* udf,
                   const source_info& srcinfo);

///////////////////////////////////////////////////////////////////////////////

class udf_vostream : public std::ostream {
public:
  udf_vostream(std::streambuf* sbuf) : std::ostream(sbuf) {}

  template <typename T>
  udf_vostream& operator<<(T&& obj) {
    if constexpr (is_system_type_v<T>) {
      auto name = system_accessor::to_verilog(std::forward<T>(obj));
      reinterpret_cast<std::ostream&>(*this) << name;
    } else {
      reinterpret_cast<std::ostream&>(*this) << std::forward<T>(obj);
    }
    return *this;
  }

  udf_vostream& operator<<(std::ostream&(*pf)(std::ostream&)) {
    reinterpret_cast<std::ostream&>(*this) << pf;
    return *this;
  }
};

///////////////////////////////////////////////////////////////////////////////

class udf_iface: public refcounted {
public:

  udf_iface();

  virtual ~udf_iface();

  virtual void eval() = 0;

  virtual void reset() = 0;

  virtual bool to_verilog(udf_vostream&, udf_verilog) = 0;
};

///////////////////////////////////////////////////////////////////////////////

template<typename T>
using detect_reset_t = decltype(std::declval<T&>().reset());

template<typename T>
using detect_to_verilog_t = decltype(std::declval<T&>().to_verilog(
  std::declval<udf_vostream&>(), std::declval<udf_verilog&>()));

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class udf_wrapper : public udf_iface {
public:
  template <typename... Args>
  udf_wrapper(Args&&... args) 
    : udf_(std::forward<Args>(args)...) 
  {}

  void eval() override {
    udf_.eval();
  }

  void reset() override {
    if constexpr (is_detected_v<detect_reset_t, T>) {
      udf_.reset();
    }
  }

  bool to_verilog(udf_vostream& out, udf_verilog mode) override {
    if constexpr (is_detected_v<detect_to_verilog_t, T>) {
      return udf_.to_verilog(out, mode);
    } else {
      CH_UNUSED(out, mode);
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
  using traits = udf_traits<T, false>;
  typename traits::io_type io;

  ch_udf_comb(CH_SRC_INFO)
    : io(create(new udf_wrapper<T>(), srcinfo)->io(), srcinfo)
  {}

#define CH_UDF_GEN_TMPL(a, i, x) typename Arg##i
#define CH_UDF_GEN_TYPE(a, i, x) Arg##i
#define CH_UDF_GEN_DECL(a, i, x) Arg##i&& arg##i
#define CH_UDF_GEN_ARG(a, i, x)  std::forward<Arg##i>(arg##i)
#define CH_UDF_GEN(...) \
  template <CH_FOR_EACH(CH_UDF_GEN_TMPL, , CH_SEP_COMMA, __VA_ARGS__), \
            CH_REQUIRE(std::is_constructible_v<T, CH_FOR_EACH(CH_UDF_GEN_TYPE, , CH_SEP_COMMA, __VA_ARGS__)> \
                    && !std::is_same_v<remove_cv_ref_t<Arg0>, ch_udf_comb>)> \
  ch_udf_comb(CH_FOR_EACH(CH_UDF_GEN_DECL, , CH_SEP_COMMA, __VA_ARGS__), CH_SRC_INFO) \
    : io(create(new udf_wrapper<T>(CH_FOR_EACH(CH_UDF_GEN_ARG, , CH_SEP_COMMA, __VA_ARGS__)), srcinfo)->io(), srcinfo) \
  {}
CH_VA_ARGS_MAP(CH_UDF_GEN)
#undef CH_UDF_GEN_TMPL
#undef CH_UDF_GEN_TYPE
#undef CH_UDF_GEN_DECL
#undef CH_UDF_GEN_ARG
#undef CH_UDF_GEN

  ch_udf_comb(ch_udf_comb& other)
    : io(other.io)
  {}

  ch_udf_comb(ch_udf_comb&& other)
    : io(std::move(other.io))
  {}

protected:

  static auto create(udf_wrapper<T>* obj, const source_info& srcinfo) {
    createUDFNode(idname<T>(), false, obj, srcinfo);
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
  using traits = udf_traits<T, true>;
  typename traits::io_type io;

  ch_udf_seq(CH_SRC_INFO)
    : io(create(new udf_wrapper<T>(), srcinfo)->io(), srcinfo)
  {}

#define CH_UDF_GEN_TMPL(a, i, x) typename Arg##i
#define CH_UDF_GEN_TYPE(a, i, x) Arg##i
#define CH_UDF_GEN_DECL(a, i, x) Arg##i&& arg##i
#define CH_UDF_GEN_ARG(a, i, x)  std::forward<Arg##i>(arg##i)
#define CH_UDF_GEN(...) \
  template <CH_FOR_EACH(CH_UDF_GEN_TMPL, , CH_SEP_COMMA, __VA_ARGS__), \
            CH_REQUIRE(std::is_constructible_v<T, CH_FOR_EACH(CH_UDF_GEN_TYPE, , CH_SEP_COMMA, __VA_ARGS__)> \
                    && !std::is_same_v<remove_cv_ref_t<Arg0>, ch_udf_seq>)> \
  ch_udf_seq(CH_FOR_EACH(CH_UDF_GEN_DECL, , CH_SEP_COMMA, __VA_ARGS__), CH_SRC_INFO) \
    : io(create(new udf_wrapper<T>(CH_FOR_EACH(CH_UDF_GEN_ARG, , CH_SEP_COMMA, __VA_ARGS__)), srcinfo)->io(), srcinfo) \
  {}
CH_VA_ARGS_MAP(CH_UDF_GEN)
#undef CH_UDF_GEN_TMPL
#undef CH_UDF_GEN_TYPE
#undef CH_UDF_GEN_DECL
#undef CH_UDF_GEN_ARG
#undef CH_UDF_GEN

  ch_udf_seq(ch_udf_seq& other)
    : io(other.io)
  {}

  ch_udf_seq(ch_udf_seq&& other)
    : io(std::move(other.io))
  {}

protected:

  static auto create(udf_wrapper<T>* obj, const source_info& srcinfo) {
    createUDFNode(idname<T>(), true, obj, srcinfo);
    return obj;
  }

  ch_udf_seq(const ch_udf_seq& other) = delete;

  ch_udf_seq& operator=(const ch_udf_seq& other) = delete;

  ch_udf_seq& operator=(ch_udf_seq&& other) = delete;
};

}}
