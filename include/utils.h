#pragma once

#include <string>
#include <functional>
#include <unordered_map>
#include <assert.h>

namespace ch {
namespace internal {

template <unsigned N>
struct requires_enum {
  enum class type {};
};

#define CH_REQUIRE_0(...) std::enable_if_t<(__VA_ARGS__), typename ch::internal::requires_enum<0>::type>* = nullptr
#define CH_REQUIRE_1(...) std::enable_if_t<(__VA_ARGS__), typename ch::internal::requires_enum<1>::type>* = nullptr
#define CH_REQUIRE_2(...) std::enable_if_t<(__VA_ARGS__), typename ch::internal::requires_enum<2>::type>* = nullptr
#define CH_REQUIRE_3(...) std::enable_if_t<(__VA_ARGS__), typename ch::internal::requires_enum<3>::type>* = nullptr

std::string stringf(const char* format, ...);

void dbprint(int level, const char* format, ...);

std::string identifier_from_string(const std::string& name);

std::string identifier_from_typeid(const std::string& name);

int char2int(char x, int base);

///////////////////////////////////////////////////////////////////////////////

template<typename T>
static constexpr unsigned bitwidth_v = std::numeric_limits<T>::digits + std::is_signed_v<T>;

///////////////////////////////////////////////////////////////////////////////

template <typename F, typename Arg>
void for_each_impl(const F& f, Arg&& arg) {
  f(std::forward<Arg>(arg));
}

template <typename F, typename Arg0, typename... Args>
void for_each_impl(const F& f, Arg0&& arg0, Args&&... args) {
  f(std::forward<Arg0>(arg0));
  for_each_impl(f, std::forward<Args>(args)...);
}

template <typename F, typename... Args>
void for_each(const F& f, Args&&... args) {
  for_each_impl(f, std::forward<Args>(args)...);
}

///////////////////////////////////////////////////////////////////////////////

template <typename F, typename Arg>
void for_each_reverse_impl(const F& f, Arg&& arg) {
  f(std::forward<Arg>(arg));
}

template <typename F, typename Arg0, typename... Args>
void for_each_reverse_impl(const F& f, Arg0&& arg0, Args&&... args) {
  for_each_reverse_impl(f, std::forward<Args>(args)...);
  f(std::forward<Arg0>(arg0));
}

template <typename F, typename... Args>
void for_each_reverse(const F& f, Args&&... args) {
  for_each_reverse_impl(f, std::forward<Args>(args)...);
}

///////////////////////////////////////////////////////////////////////////////

template <typename T, std::size_t... Is>
constexpr auto make_array_n_impl(T&& value, std::index_sequence<Is...>) {
  return std::array<std::decay_t<T>, sizeof...(Is) + 1>{
    std::forward<T>(value), (static_cast<void>(Is), value)...
  };
}

template <typename T>
constexpr auto make_array_n_impl(T&&, std::integral_constant<std::size_t, 0>) {
  return std::array<std::decay_t<T>, 0>{};
}

template <typename T, std::size_t N>
constexpr auto make_array_n_impl(T&& value, std::integral_constant<std::size_t, N>) {
  return make_array_n_impl(std::forward<T>(value), std::make_index_sequence<N - 1>{});
}

template <std::size_t N, typename T>
constexpr auto make_array_n(T&& value) {
  return make_array_n_impl(std::forward<T>(value), std::integral_constant<std::size_t, N>{});
}

///////////////////////////////////////////////////////////////////////////////

template <typename T, std::size_t... Is>
constexpr std::initializer_list<T> make_list_n_impl(T&& value, std::index_sequence<Is...>) {
    return {std::forward<T>(value), (static_cast<void>(Is), value)...};
}

template <typename T>
constexpr std::initializer_list<T> make_list_n_impl(T&&, std::integral_constant<std::size_t, 0>) {
    return {};
}

template <typename T, std::size_t N>
constexpr auto make_list_n_impl(T&& value, std::integral_constant<std::size_t, N>) {
    return make_list_n_impl(std::forward<T>(value), std::make_index_sequence<N - 1>{});
}

template <std::size_t N, typename T>
constexpr auto make_list_n(T&& value) {
    return make_list_n_impl(std::forward<T>(value), std::integral_constant<std::size_t, N>{});
}

///////////////////////////////////////////////////////////////////////////////

constexpr inline std::size_t hash_combine(std::size_t hash1, std::size_t hash2) {
  return hash1 ^ (hash2 * 0x9e3779b9 + (hash1 << 6) + (hash1 >> 2));
}

///////////////////////////////////////////////////////////////////////////////

template <typename T, typename S = std::size_t, typename H = std::hash<T>>
class dup_tracker {
public:
  using value_type = T;
  using size_type  = S;
  using hash_type  = H;

  auto insert(const T& obj) {
    return instances_[obj]++;
  }

  auto count(const T& obj) const {
    auto it = instances_.find(obj);
    if (it != instances_.end()) {
      return it->second;
    }
    return 0;
  }

  bool exists(const T& obj) const {
    return instances_.count(obj);
  }

private:
  std::unordered_map<T, S, H> instances_;
};

///////////////////////////////////////////////////////////////////////////////

template <bool B>
inline constexpr bool bool_constant_v = std::bool_constant<B>::value;

///////////////////////////////////////////////////////////////////////////////

template <typename To, typename... Froms>
inline constexpr bool are_all_constructible_v = std::conjunction_v<std::is_constructible<To, Froms>...>;

///////////////////////////////////////////////////////////////////////////////

template<typename A, typename B, typename = void>
struct is_equality_comparable : std::false_type {};

template<typename A, typename B>
struct is_equality_comparable<A, B,
    std::enable_if_t<
      true,
      decltype(std::declval<A&>() == std::declval<B&>(), (void)0)
    >> : std::true_type {};

template<typename A, typename B>
inline constexpr bool is_equality_comparable_v = is_equality_comparable<A, B>::value;

///////////////////////////////////////////////////////////////////////////////

//template <typename T>
//using identity_t = T;

template<typename T>
struct identity_impl {
  typedef T type;
};

template<typename T>
using identity_t = typename identity_impl<T>::type;

struct empty_base {};

template <typename...>
using void_t = void;

///////////////////////////////////////////////////////////////////////////////

template <typename T>
struct to_function : public to_function<decltype(&T::operator())> {};

template <typename Class, typename Ret, typename... Args>
struct to_function<Ret(Class::*)(Args...) const> {
  using type = const std::function<Ret(Args...)>;
};

template <typename T>
using to_function_t = typename to_function<T>::type;

///////////////////////////////////////////////////////////////////////////////

template <typename From, typename To>
struct reference_cast {
  using type = To;
};

template <typename To>
struct reference_cast<To, To> {
  using type = const To&;
};

///////////////////////////////////////////////////////////////////////////////

class refcounted {
public:
  
  long acquire() const {
    return ++refcount_;
  }

  long release() const {
    assert(refcount_ > 0);
    long refcount = --refcount_;
    if (0 == refcount) {
      delete this;
    }
    return refcount;
  }
  
  long refcount() const {
    return refcount_;
  }
  
protected:
  
  refcounted() : refcount_(0) {}
  virtual ~refcounted() {}
  
protected:
  
  mutable long refcount_;
  
  template <typename T> friend class refcounted_ptr;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class refcounted_ptr {
public:
  
  refcounted_ptr() : ptr_(nullptr) {}
  
  ~refcounted_ptr() {
    if (ptr_)
      ptr_->release();
  }
  
  refcounted_ptr(const refcounted_ptr& other) : refcounted_ptr(other.ptr_) {}
  
  refcounted_ptr(refcounted_ptr&& other) {
    ptr_ = other.ptr_;
    other.ptr_ == nullptr;
  }
  
  refcounted_ptr& operator=(const refcounted_ptr& other) {
    if (other.ptr_)
      other.ptr_->acquire();
    if (ptr_)
      ptr_->release();
    ptr_ = other.ptr_;
    return *this;
  }
  
  refcounted_ptr& operator=(refcounted_ptr&& other) {
    if (other.ptr_)
      other.ptr_->release();
    ptr_ = other.ptr_;
    other.ptr_ == nullptr;
  }
  
  T& operator*() const {
    return *ptr_;
  }
  
  T* operator->() const {
    return ptr_;
  }
  
  T* get() const {
    return ptr_;
  }
  
  T* release() const {
    T* ret(ptr_);
    if (ret)
     ret->release();    
    ptr_ = nullptr;
    return ret;
  }
  
  bool is_unique() const {
    return ptr_ ? (ptr_->refcount() == 1) : false;
  }
  
  uint32_t use_count() const {
    return ptr_ ? (ptr_->refcount() == 1) : false;
  }
  
  void reset(T* ptr = nullptr) {
    if (ptr)
      ptr->acquire();
    if (ptr_)
      ptr_->release();
    ptr_ = ptr;    
    return *this;
  }
  
  bool operator==(const refcounted_ptr& other) const {
    return (ptr_ == other.ptr_);
  }
  
  bool operator==(const T* other) const {
    return (ptr_ == other);
  }
  
  operator bool() const {
    return this->use_count() != 0;
  }
  
protected:    
  
  refcounted_ptr(refcounted* ptr) : ptr_(ptr) {
    if (ptr)
      ptr->acquire();
  }
  
  refcounted* ptr_;
  
  template <typename T_, typename... Args>
  friend refcounted_ptr<T_> make_ptr(const Args&... args);
};

template <typename T, typename... Args>
refcounted_ptr<T> make_ptr(const Args&... args) {
  return refcounted_ptr<T>(new T(args...));
} 

///////////////////////////////////////////////////////////////////////////////

template<class InputIt, class T>
typename std::iterator_traits<InputIt>::difference_type
find_distance(InputIt first, InputIt last, const T& value) {
  typename std::iterator_traits<InputIt>::difference_type index = 0;
  for (;first != last; ++first, ++index) {
    if (*first == value) {
      return index;
    }
  }
  return -1;
}

///////////////////////////////////////////////////////////////////////////////

class scope_exit {
public:
  scope_exit(const std::function<void()>& f) : f_(f) {}
  ~scope_exit() { f_(); }
  // force stack only allocation!
  static void *operator new   (size_t) = delete;
  static void *operator new[] (size_t) = delete;
protected:
  std::function<void()> f_;
};

///////////////////////////////////////////////////////////////////////////////

template <class CharT, class Traits = std::char_traits<CharT>>
class basic_auto_indent : public std::basic_streambuf<CharT, Traits> {
public:
  explicit basic_auto_indent(std::basic_ostream<CharT, Traits>& out, int indent = 2)
    : out_(out)
    , indent_(indent)
    , add_indent_(true) {
    buf_ = out.rdbuf();
    out.rdbuf(this);
  }
  ~basic_auto_indent() {
    out_.rdbuf(buf_);
  }
  void push() {
    indent_ *= 2;
  }
  void pop() {
    assert(indent_ > 0);
    indent_ /= 2;
  }
protected:
  virtual int overflow(int ch) override {
    if (add_indent_ && ch != '\n') {
      for (int n = indent_; n--;) {
        buf_->sputc(' ');
      }
    }
    add_indent_ = (ch == '\n');
    return buf_->sputc(ch);
  }
  std::basic_ostream<CharT, Traits>&   out_;
  int indent_;
  std::basic_streambuf<CharT, Traits>* buf_;
  bool add_indent_;
};

using auto_indent = basic_auto_indent<char>;

///////////////////////////////////////////////////////////////////////////////

template <class CharT, class Traits = std::char_traits<CharT>>
class basic_auto_separator {
public:
  basic_auto_separator(const std::basic_string<CharT, Traits>& sep)
    : sep_(sep)
    , enabled_(false)
  {}
  auto& data() const {
    const auto& ret = enabled_ ? sep_ : empty_;
    enabled_ = true;
    return ret;
  }
protected:
  std::basic_string<CharT, Traits> sep_;
  std::basic_string<CharT, Traits> empty_;
  mutable bool enabled_;

  friend std::ostream& operator<<(std::ostream& out, const basic_auto_separator& sep) {
    return out << sep.data();
  }
};

using auto_separator = basic_auto_separator<char>;

///////////////////////////////////////////////////////////////////////////////

template <typename... Args>
void unused(Args&&...) {}

///////////////////////////////////////////////////////////////////////////////

template <class Func, typename T, T Start, T ...Is>
constexpr void static_for_impl(Func &&f, std::integer_sequence<T, Is...>) {
  (f(std::integral_constant<T, Start + Is>{} ),... );
}

template <auto Start, auto End, class Func>
constexpr void static_for(Func &&f) {
  using type_t = std::common_type_t<decltype(Start), decltype(End)>;
  static_for_impl<Func, type_t, Start>(
    std::forward<Func>(f), std::make_integer_sequence<type_t, (End - Start)>{});
}

///////////////////////////////////////////////////////////////////////////////

template <typename Dst, typename Src>
Dst bit_cast(const Src& src) {
  union merged_t { Src src; Dst dst; };
  merged_t m;
  m.dst = 0;
  m.src = src;
  return m.dst;  
}

template <typename T = uint32_t>
constexpr unsigned count_leading_zeros(T value) {
  static_assert(std::is_integral_v<T>, "invalid type");
  if (value) {
    if constexpr (bitwidth_v<T> <= 32) {
      return __builtin_clz(value) - (32 - bitwidth_v<T>);
    } else {
      return __builtin_clzll(value) - (64 - bitwidth_v<T>);
    }
  }
  return bitwidth_v<T>;
}

template <typename T = uint32_t>
constexpr unsigned count_trailing_zeros(T value) {
  static_assert(std::is_integral_v<T>, "invalid type");
  if (value) {
    if constexpr (bitwidth_v<T> <= 32) {
      return __builtin_ctz(value);
    } else {
      return __builtin_ctzll(value);
    }
  }
  return bitwidth_v<T>;
}

template <typename T = uint32_t>
constexpr bool ispow2(T value) {
  static_assert(std::is_integral_v<T>, "invalid type");
  return value && !(value & (value - 1));
}

template <typename T = uint32_t>
constexpr unsigned log2ceil(T value) {
  static_assert(std::is_integral_v<T>, "invalid type");
  return bitwidth_v<T> - count_leading_zeros(value - 1);
}

template <typename T = uint32_t>
constexpr unsigned log2floor(T value) {
  static_assert(std::is_integral_v<T>, "invalid type");
  return bitwidth_v<T> - count_leading_zeros(value) - 1;
}

template <typename T = uint32_t>
constexpr unsigned ceil2(T value) {
  return bitwidth_v<T> - count_leading_zeros<T>(value);
}

template <typename R, typename T, typename U,
          CH_REQUIRE_0(!std::is_same_v<R, T>)>
constexpr R ceildiv(T a, U b) {
  static_assert(std::is_integral_v<R>, "invalid type");
  static_assert(std::is_integral_v<T>, "invalid type");
  static_assert(std::is_integral_v<U>, "invalid type");
  return R((a + b - 1) / b);
}

template <typename T, typename U>
constexpr T ceildiv(T a, U b) {
  static_assert(std::is_integral_v<T>, "invalid type");
  static_assert(std::is_integral_v<U>, "invalid type");
  return T((a + b - 1) / b);
}

template <typename T = uint32_t>
constexpr T blend(T mask, T a, T b) {
  static_assert(std::is_integral_v<T>, "invalid type");
  return a ^ ((a ^ b) & mask); // = m ? b : a
}

template <typename T = uint32_t>
constexpr T rotl(T value, uint32_t shift, uint32_t width) {
  static_assert(std::is_integral_v<T>, "invalid type");
  if (shift >= width)
    shift = shift % width;
  return  (value << shift) | (value >> (width - shift));
}

template <typename T = uint32_t>
constexpr T rotr(T value, uint32_t shift, uint32_t width) {
  static_assert(std::is_integral_v<T>, "invalid type");
  if (shift > width)
    shift = shift % width;
  return (value >> shift) | (value << (width  - shift));
}

template <typename T>
auto sign_ext(T value, unsigned width) {
  static_assert(std::is_integral_v<T>, "invalid type");
  using U = std::make_unsigned_t<T>;
  static constexpr U WORD_MAX  = std::numeric_limits<U>::max();
  assert(bitwidth_v<U> >= width);
  U k = WORD_MAX >> (bitwidth_v<U> - width);
  U n = value & k;
  U m = U(1) << (width - 1);
  return std::make_signed_t<T>((n ^ m) - m);
}

}
}

#define CH_CHECK(pred, ...) \
  do { \
    if (!(pred)) { \
      fprintf(stderr, "ERROR: assertion `" CH_STRINGIZE(pred) "' failed, "); \
      fprintf(stderr, __VA_ARGS__); \
      fprintf(stderr, " (" __FILE__ ":" CH_STRINGIZE(__LINE__) ")\n"); \
      std::abort(); \
    } \
  } while (false)

#ifdef NDEBUG
  #define CH_ABORT(...) \
    do { \
      fprintf(stderr, "ERROR: "); \
      fprintf(stderr, __VA_ARGS__); \
      std::abort(); \
    } while (false)

  #define CH_DBGCHECK(pred, ...) CH_UNUSED(pred, __VA_ARGS__)
  #define CH_DBG(level, format, ...) CH_UNUSED(level, format, __VA_ARGS__)
#else
  #define CH_ABORT(...) \
    do { \
      fprintf(stderr, "ERROR: "); \
      fprintf(stderr, __VA_ARGS__); \
      fprintf(stderr, " (" __FILE__ ":" CH_STRINGIZE(__LINE__) ")\n"); \
      std::abort(); \
    } while (false)

  #define CH_DBGCHECK CH_CHECK
  #define CH_DBG(level, ...) ch::internal::dbprint(level, __VA_ARGS__)
#endif

#define CH_DEF_SFINAE_CHECK(type_name, predicate) \
  template<typename T, typename Enable = void> \
  struct type_name##_impl : std::false_type {}; \
  template<typename T> \
  struct type_name##_impl<T, std::enable_if_t<(predicate)>> : std::true_type {}; \
  template <typename T> \
  inline constexpr bool type_name##_v = type_name##_impl<T>::value

#define CH_UNUSED(...) ch::internal::unused(__VA_ARGS__)

#define CH_TODO() CH_ABORT("Not yet implemented");
