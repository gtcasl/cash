#pragma once

#include "struct.h"

namespace ch {
namespace internal {

lnodeimpl* createInputNode(const std::string& name, uint32_t size);

lnodeimpl* createOutputNode(const std::string& name, const lnode& src);

void bindInput(const lnode& input, const lnode& src);

void registerIOMap(const nodelist& data);

template <typename T>
void registerIOMap(const T& node) {
  nodelist data(T::bitcount, true);
  ch::internal::read_data(node, data, 0, T::bitcount);
  registerIOMap(data);
}

template <bool input, bool output>
class port {
public:
  static constexpr bool is_input = input;
  static constexpr bool is_output = output;

  port(const std::string& inout_name) : name_(inout_name) {}

  const std::string& get_name() const {
    return name_;
  }

protected:
  std::string name_;
};

template <typename T>
class ch_in;

template <typename T>
class ch_out;

template <typename T>
class ch_in : public T::const_type, public port<true, false> {
public:
  using base = typename T::const_type;
  using value_type = T;
  using const_type = typename T::const_type;
  using flip_type = ch_out<T>;

  ch_in(const std::string& name = "io") : port(name) {
    input_ = createInputNode(name, base::bitcount);
    nodelist data(base::bitcount, true);
    data.push(input_);
    this->write_data(0, data, 0, base::bitcount);
    registerIOMap(*this);
  }

  ch_in(const ch_in& in) : base(in), port(in.get_name()) {}
  ch_in(ch_in&& in) : base(std::move(in)), port(std::move(in)) {}

  template <typename U,
            CH_REQUIRES(is_cast_convertible<U, T>::value)>
  void operator()(const ch_in<U>& in) const {
    bindInput(input_, get_lnode(in));
  }

  template <typename U,
            CH_REQUIRES(is_cast_convertible<U, T>::value)>
  void operator()(const ch_out<U>& out) const {
    bindInput(input_, get_lnode(out));
  }

  void operator()(const ch_bitbase<T::bitcount>& value) const {
    bindInput(input_, get_lnode(value));
  }

  template <typename U,
            CH_REQUIRES(is_cast_convertible<U, T>::value)>
  void operator()(const U& value) const {
    bindInput(input_, get_lnode<U, base::bitcount>(value));
  }

protected:

  lnode input_;

  ch_in& operator=(const ch_in&) = delete;
  ch_in& operator=(ch_in&&) = delete;
};

template <typename T>
class ch_out : public T, public port<false, true> {
public:
  using base = T;
  using base::operator=;
  using value_type = T;
  using const_type = typename T::const_type;
  using flip_type = ch_in<T>;

  ch_out(const std::string& name = "io") : port(name) {
    output_ = createOutputNode(name, get_lnode(*this));
    registerIOMap(*this);
  }

  ch_out(const ch_out& out) : base(out), port(out.get_name()) {}
  ch_out(ch_out&& out) : base(std::move(out)), port(std::move(out)) {}

  template <typename U,
            CH_REQUIRES(is_cast_convertible<U, T>::value)>
  void operator()(ch_out<U>& out) const {
    out = make_type<U>(output_);
  }

  template <typename U,
            CH_REQUIRES(is_cast_convertible<T, U>::value)>
  void operator()(ch_in<U>& in) const {
    in(make_type<U>(output_));
  }

  template <typename U,
            CH_REQUIRES(is_cast_convertible<T, U>::value)>
  void operator()(U& value) const {
    value = make_type<U>(output_);
  }

protected:

  lnode output_;

  ch_out& operator=(const ch_out&) = delete;
  ch_out& operator=(ch_out&&) = delete;

  template <typename U> friend class ch_in;
};

#define CH_INOUT_FIELD(i, x) \
  CH_PAIR_L(x) CH_PAIR_R(x)

#define CH_INOUT_FLIP_FIELD(i, x) \
  typename CH_PAIR_L(x)::flip_type CH_PAIR_R(x)

#define CH_INOUT_CTOR_APPLY(i, x) \
  CH_PAIR_R(x)(ch::internal::fstring("%s_%s", this->get_name().c_str(), CH_STRINGIZE(CH_PAIR_R(x))))

#define CH_INOUT_BIND_APPLY(i, x) \
  this->CH_PAIR_R(x)(__rhs__.CH_PAIR_R(x))

#define CH_INOUT_BIND_FIELD_ARGS(i, x) \
  __T##i&& CH_CONCAT(_,CH_PAIR_R(x))

#define CH_INOUT_BIND_FIELD_APPLY(i, x) \
  this->CH_PAIR_R(x)(std::forward<__T##i>(CH_CONCAT(_,CH_PAIR_R(x))))

#define CH_INOUT_IMPL(inout_name, ...) \
  class inout_name : public ch::internal::port<true, true> { \
  private: \
    class __flip_type__ : public ch::internal::port<true, true> { \
    private: \
      __flip_type__& operator=(const __flip_type__&) = delete; \
    public: \
      static constexpr unsigned bitcount = CH_STRUCT_SIZE(__VA_ARGS__); \
      using base = ch::internal::port<true, true>; \
      using flip_type = inout_name; \
      __flip_type__(const std::string& name = "io") : CH_FOR_EACH(CH_INOUT_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__), port(name) {} \
      __flip_type__(const __flip_type__& __rhs__) : CH_FOR_EACH(CH_STRUCT_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__), port(__rhs__.get_name()) {} \
      __flip_type__(__flip_type__&& __rhs__) : CH_FOR_EACH(CH_STRUCT_MOVE_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__), port(std::move(__rhs__)) {} \
      void operator()(__flip_type__& __rhs__) const { \
        CH_FOR_EACH(CH_INOUT_BIND_APPLY, CH_SEP_SEMICOLON, __VA_ARGS__); \
      } \
      template <CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_TMPL, CH_SEP_COMMA, __VA_ARGS__)> \
      void operator()(CH_FOR_EACH(CH_INOUT_BIND_FIELD_ARGS, CH_SEP_COMMA, __VA_ARGS__)) const { \
        CH_FOR_EACH(CH_INOUT_BIND_FIELD_APPLY, CH_SEP_SEMICOLON, __VA_ARGS__); \
      } \
      CH_FOR_EACH(CH_INOUT_FLIP_FIELD, CH_SEP_SEMICOLON, __VA_ARGS__); \
    }; \
    inout_name& operator=(const inout_name&) = delete; \
  public: \
    static constexpr unsigned bitcount = CH_STRUCT_SIZE(__VA_ARGS__); \
    using base = ch::internal::port<true, true>; \
    using flip_type  = __flip_type__; \
    inout_name(const std::string& name = "io") : CH_FOR_EACH(CH_INOUT_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__), port(name) {} \
    inout_name(const inout_name& __rhs__) : CH_FOR_EACH(CH_STRUCT_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__), port(__rhs__.get_name()) {} \
    inout_name(inout_name&& __rhs__) : CH_FOR_EACH(CH_STRUCT_MOVE_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__), port(std::move(__rhs__)) {} \
    void operator()(inout_name& __rhs__) const { \
      CH_FOR_EACH(CH_INOUT_BIND_APPLY, CH_SEP_SEMICOLON, __VA_ARGS__); \
    } \
    template <CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_TMPL, CH_SEP_COMMA, __VA_ARGS__)> \
    void operator()(CH_FOR_EACH(CH_INOUT_BIND_FIELD_ARGS, CH_SEP_COMMA, __VA_ARGS__)) const { \
      CH_FOR_EACH(CH_INOUT_BIND_FIELD_APPLY, CH_SEP_SEMICOLON, __VA_ARGS__); \
    } \
    CH_FOR_EACH(CH_INOUT_FIELD, CH_SEP_SEMICOLON, __VA_ARGS__); \
  }

#define CH_INOUT(name, body) \
  CH_INOUT_IMPL(name, CH_REM body)

#define CH_IO(...) \
  CH_INOUT_IMPL(io_type, __VA_ARGS__); \
  io_type io
}
}
