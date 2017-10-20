#pragma once

#include <string>
#include <functional>
#include <unordered_map>
#include <assert.h>

namespace ch {
namespace internal {

std::string fstring(const char* format, ...);

void dbprint(int level, const char* format, ...);

void dump_stack_trace(FILE* out, unsigned int max_frames = 32);

std::string identifier_from_typeid(const std::string& name);

///////////////////////////////////////////////////////////////////////////////

class unique_name {
public:
  unique_name() {}

  std::string get(const std::string& name);

private:
  std::unordered_map<std::string, unsigned> dups_;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
struct is_integral_or_enum : std::integral_constant<bool,
  std::is_integral<T>::value ||
  std::is_enum<T>::value>
{};

///////////////////////////////////////////////////////////////////////////////

template <bool Pred>
using is_true = std::conditional_t<Pred, std::true_type, std::false_type>;

template <bool Pred>
using is_false = std::conditional_t<Pred, std::false_type, std::true_type>;

///////////////////////////////////////////////////////////////////////////////

template <bool... B>
struct conjunction {};

template <bool Head, bool... Tail>
struct conjunction<Head, Tail...>
    : std::integral_constant<bool, Head && conjunction<Tail...>::value>{};

template <bool B>
struct conjunction<B> : std::integral_constant<bool, B> {};

///////////////////////////////////////////////////////////////////////////////

template <typename To, typename From>
using is_cast_convertible = std::is_constructible<To, From>;

template <typename To, typename... Froms>
using are_all_cast_convertible = conjunction<is_cast_convertible<To, Froms>::value...>;

///////////////////////////////////////////////////////////////////////////////

template<typename A, typename B = A, typename = void>
struct is_equality_comparable : std::false_type {};

template<typename A, typename B>
struct is_equality_comparable<A, B,
    std::enable_if_t<
      true,
      decltype(std::declval<A&>() == std::declval<B&>(), (void)0)
    >> : std::true_type {};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
using identity_t = T;

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
    if (0 == --refcount_)
      delete this;
    return refcount_;
  }
  
  long get_refcount() const {
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
  
  refcounted_ptr(const refcounted_ptr& rhs) : refcounted_ptr(rhs.ptr_) {}
  
  refcounted_ptr(refcounted_ptr&& rhs) {
    ptr_ = rhs.ptr_;
    rhs.ptr_ == nullptr;
  }
  
  refcounted_ptr& operator=(const refcounted_ptr& rhs) {
    if (rhs.ptr_)
      rhs.ptr_->acquire();
    if (ptr_)
      ptr_->release();
    ptr_ = rhs.ptr_;
    return *this;
  }
  
  refcounted_ptr& operator=(refcounted_ptr&& rhs) {
    if (rhs.ptr_)
      rhs.ptr_->release();
    ptr_ = rhs.ptr_;
    rhs.ptr_ == nullptr;
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
    return ptr_ ? (ptr_->get_refcount() == 1) : false;
  }
  
  unsigned get_use_count() const {
    return ptr_ ? (ptr_->get_refcount() == 1) : false;
  }
  
  void reset(T* ptr = nullptr) {
    if (ptr)
      ptr->acquire();
    if (ptr_)
      ptr_->release();
    ptr_ = ptr;    
    return *this;
  }
  
  bool operator==(const refcounted_ptr& rhs) const {
    return (ptr_ == rhs.ptr_);
  }
  
  bool operator==(const T* rhs) const {
    return (ptr_ == rhs);
  }
  
  operator bool() const {
    return this->get_use_count() != 0;
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
  explicit basic_auto_indent(std::basic_ostream<CharT, Traits>& out, int indent = 4)
    : out_(out)
    , indent_(indent)
    , add_indent_(true) {
    buf_ = out.rdbuf();
    out.rdbuf(this);
  }
  ~basic_auto_indent() {
    out_.rdbuf(buf_);
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

template <class CharT, class Traits = std::char_traits<CharT>>
class basic_auto_separator {
public:
  basic_auto_separator(const std::basic_string<CharT, Traits>& sep)
    : sep_(sep)
    , enabled_(false)
  {}
  const auto& data() const {
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

template<typename T> struct static_print;
// usage: static_print<type>();

///////////////////////////////////////////////////////////////////////////////

// is power of two number ?
constexpr bool ispow2(unsigned value) { 
  return value && !(value & (value - 1)); 
}

// return ilog2
constexpr unsigned ilog2(unsigned x) {
  return (x <= 1) ? 0 : (ilog2(x >> 1) + 1);
}

// return ceil of log2
constexpr unsigned log2ceil(unsigned x) {
  return ispow2(x) ? ilog2(x) : (ilog2(x) + 1);
}

template <typename Dst, typename Src>
const auto bitcast(const Src& src) {
  union merged_t { Src src; Dst dst; };
  merged_t m;
  m.dst = 0;
  m.src = src;
  return m.dst;  
}

constexpr uint32_t clz(uint32_t value) {
  return __builtin_clz(value);
}

constexpr uint32_t ctz(uint32_t value) {
  return __builtin_ctz(value);
}

constexpr uint32_t rotl(uint32_t value, uint32_t shift, uint32_t width) {
  assert(shift < width);
  return  (value << shift) | (value >> (width - shift));
}

constexpr uint32_t rotr(uint32_t value, uint32_t shift, uint32_t width) {
  assert(shift < width);
  return (value >> shift) | (value << (width  - shift));
}

}
}

#ifdef NDEBUG
  #define CH_ABORT(msg, ...) \
    do { \
      fprintf(stderr, "ERROR: " msg "\n", ##__VA_ARGS__); \
      std::abort(); \
    } while (false)

  #define DBG(level, format, ...)
#else
  #define CH_ABORT(msg, ...) \
    do { \
      ch::internal::dump_stack_trace(stdout); \
      fprintf(stderr, "ERROR: " msg " (" __FILE__ ":" CH_STRINGIZE(__LINE__) ")\n", ##__VA_ARGS__); \
      std::abort(); \
    } while (false)

  #define DBG(level, format, ...) \
    dbprint(level, "DBG: " format, ##__VA_ARGS__)
#endif

#define CH_CHECK(x, msg, ...) \
  do { \
    if (!(x)) { \
      CH_ABORT("assertion `" CH_STRINGIZE(x) "' failed, " msg, ##__VA_ARGS__); \
    } \
  } while (false)

#define CH_DEF_SFINAE_CHECK(type_name, predicate) \
  template<typename T, typename Enable = void> \
  struct type_name : std::false_type {}; \
  template<typename T> \
  struct type_name<T, typename std::enable_if_t<predicate>> : std::true_type {}

#define CH_VOID_T typename = void

#define CH_REQUIRES(...) typename = std::enable_if_t<(__VA_ARGS__)>

#define CH_UNUSED(...) ch::internal::unused(__VA_ARGS__)

#define CH_TODO() CH_ABORT("Not yet implemented");

#define CH_COUNTOF(a) (sizeof(a) / sizeof(a[0]))
#define CH_MAX(a,b) (((a) > (b)) ? (a) : (b))
#define CH_CEILDIV(a, b) (((a) + (b) - 1) / b)
#define CH_BLEND(m, a, b)  (a) ^ (((a) ^ (b)) & (m)) // 0->a, 1->b
