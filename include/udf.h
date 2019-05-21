#pragma once

#include "logic.h"

namespace ch {
namespace internal {

class udf_iface;

enum class udf_verilog_mode { header, declaration, body };

void createUDFNode(const std::string& name, bool is_seq, udf_iface* udf);

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

CH_DEF_SFINAE_CHECK(has_system_io, is_system_io_v<decltype(T::io)>);

template<typename T>
using detect_eval_t = decltype(std::declval<T&>().eval());

template<typename T>
using detect_reset_t = decltype(std::declval<T&>().reset());

template<typename T>
using detect_to_verilog_t = decltype(std::declval<T&>().to_verilog(
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
    if constexpr (is_detected_v<detect_to_verilog_t, T>) {
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
    createUDFNode(idname<T>(), false, obj);
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
    createUDFNode(idname<T>(), true, obj);
    return obj;
  }

  ch_udf_seq(const ch_udf_seq& other) = delete;

  ch_udf_seq& operator=(const ch_udf_seq& other) = delete;

  ch_udf_seq& operator=(ch_udf_seq&& other) = delete;
};

}}
