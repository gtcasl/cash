#pragma once

#include <string>
#include <sstream>
#include <functional>
#include <unordered_map>
#include <assert.h>

namespace ch {
namespace internal {

namespace detail {
template <unsigned N>
struct requires_t {
  enum class type {};
};
}

#define CH_REQUIRE(...) std::enable_if_t<(__VA_ARGS__), typename ch::internal::detail::requires_t<0>::type>* = nullptr

std::string stringf(const char* format, ...);

std::vector<std::string> split(const std::string& str, char delimiter);

void dbprint(int level, const char* format, ...);

std::string demanged_typeid(const std::string& name);

std::string identifier_from_string(const std::string& name);

std::string identifier_from_typeid(const std::string& name, bool no_args);

int char2int(char x, int base);

///////////////////////////////////////////////////////////////////////////////

template <typename T>
std::string idname(bool no_args = false) {
  return identifier_from_typeid(typeid(T).name(), no_args);
}

///////////////////////////////////////////////////////////////////////////////

template<typename T>
static constexpr unsigned bitwidth_v = std::numeric_limits<T>::digits + std::is_signed_v<T>;

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

class sstreamf {
public:
  sstreamf() {}
  ~sstreamf() {}

  template <typename T>
  sstreamf& operator<<(const T& value) {
    ss_ << value;
    return *this;
  }

  auto str() const { 
    return ss_.str(); 
  }
  
  operator std::string() const { 
    return ss_.str(); 
  }

private:
  std::stringstream ss_;
  sstreamf(const sstreamf&);
  sstreamf& operator=(const sstreamf&);
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
using remove_cv_ref_t = std::remove_cv_t<std::remove_reference_t<T>>;

///////////////////////////////////////////////////////////////////////////////

template <bool B>
inline constexpr bool bool_constant_v = std::bool_constant<B>::value;

///////////////////////////////////////////////////////////////////////////////

template <typename To, typename... Froms>
inline constexpr bool is_fold_constructible_v = 
    std::conjunction_v<std::is_constructible<To, Froms>...>;

///////////////////////////////////////////////////////////////////////////////

namespace detail {
template <typename To, typename From>
struct is_explicitly_constructible_impl : std::bool_constant<
    (std::is_constructible_v<To, From> && !std::is_convertible_v<From, To>)> {};
}

template<typename To, typename From>
inline constexpr bool is_explicitly_constructible_v = 
    detail::is_explicitly_constructible_impl<To, From>::value;

///////////////////////////////////////////////////////////////////////////////

namespace detail {
template <typename To, typename From>
struct is_implicitly_constructible_impl : std::bool_constant<
    (std::is_constructible_v<To, From> && std::is_convertible_v<From, To>)> {};
}

template<typename To, typename From>
inline constexpr bool is_implicitly_constructible_v = 
    detail::is_implicitly_constructible_impl<To, From>::value;

///////////////////////////////////////////////////////////////////////////////

namespace detail {
template <typename To, typename From>
struct is_strictly_constructible_impl : std::bool_constant<
    (is_implicitly_constructible_impl<To, From>::value && !std::is_base_of_v<To, From>)> {};
}

template<typename To, typename From>
inline constexpr bool is_strictly_constructible_v = 
    detail::is_strictly_constructible_impl<To, From>::value;

///////////////////////////////////////////////////////////////////////////////

namespace detail {
template<typename A, typename B, typename = void>
struct is_equality_comparable_impl : std::false_type {};

template<typename A, typename B>
struct is_equality_comparable_impl<A, B,
    std::enable_if_t<
      true,
      decltype(std::declval<A&>() == std::declval<B&>(), (void)0)
    >> : std::true_type {};
}

template<typename A, typename B = A>
inline constexpr bool is_equality_comparable_v = 
    detail::is_equality_comparable_impl<A, B>::value;

///////////////////////////////////////////////////////////////////////////////

namespace detail {
template<typename A, typename B, typename = void>
struct is_lessthan_comparable_impl : std::false_type {};

template<typename A, typename B>
struct is_lessthan_comparable_impl<A, B,
    std::enable_if_t<
      true,
      decltype(std::declval<A&>() < std::declval<B&>(), (void)0)
    >> : std::true_type {};
}

template<typename A, typename B = A>
inline constexpr bool is_lessthan_comparable_v = 
    detail::is_lessthan_comparable_impl<A, B>::value;

///////////////////////////////////////////////////////////////////////////////

namespace detail {
template<typename T>
struct identity_impl {
  typedef T type;
};
}

template<typename T>
using identity_t = typename detail::identity_impl<T>::type;

struct empty_t {};

template <typename...>
using void_t = void;

///////////////////////////////////////////////////////////////////////////////

namespace detail {
template <typename T>
struct to_function_impl : public to_function_impl<decltype(&T::operator())> {};

template <typename Class, typename Ret, typename... Args>
struct to_function_impl<Ret(Class::*)(Args...) const> {
  using type = const std::function<Ret(Args...)>;
};
}

template <typename T>
using to_function_t = typename detail::to_function_impl<T>::type;

///////////////////////////////////////////////////////////////////////////////

namespace detail {
template <typename Func, typename Arg>
void for_each_impl(const Func& func, Arg&& arg) {
  func(std::forward<Arg>(arg));
}

template <typename Func, typename Arg0, typename... Args>
void for_each_impl(const Func& func, Arg0&& arg0, Args&&... args) {
  func(std::forward<Arg0>(arg0));
  for_each_impl(func, std::forward<Args>(args)...);
}
}

template <typename F, typename... Args>
void for_each(const F& func, Args&&... args) {
  detail::for_each_impl(func, std::forward<Args>(args)...);
}

///////////////////////////////////////////////////////////////////////////////

namespace detail {
template <typename Func, typename Arg>
void for_each_reverse_impl(const Func& func, Arg&& arg) {
  func(std::forward<Arg>(arg));
}

template <typename Func, typename Arg0, typename... Args>
void for_each_reverse_impl(const Func& func, Arg0&& arg0, Args&&... args) {
  for_each_reverse_impl(func, std::forward<Args>(args)...);
  func(std::forward<Arg0>(arg0));
}
}

template <typename Func, typename... Args>
void for_each_reverse(const Func& func, Args&&... args) {
  detail::for_each_reverse_impl(func, std::forward<Args>(args)...);
}

///////////////////////////////////////////////////////////////////////////////

namespace detail {
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
}

template <std::size_t N, typename T>
constexpr auto make_array_n(T&& value) {
  return detail::make_array_n_impl(std::forward<T>(value), std::integral_constant<std::size_t, N>{});
}

///////////////////////////////////////////////////////////////////////////////

namespace detail {
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
}

template <std::size_t N, typename T>
constexpr auto make_list_n(T&& value) {
    return detail::make_list_n_impl(std::forward<T>(value), std::integral_constant<std::size_t, N>{});
}

///////////////////////////////////////////////////////////////////////////////

namespace detail {
template <typename Func, auto Step, typename T, T Start, T ...Is>
constexpr void static_for_impl(Func&& func, std::integer_sequence<T, Is...>) {
  (func(std::integral_constant<T, Start + Is * Step>{}), ...);
}
}

template <auto Stop, typename Func>
constexpr void static_for(Func&& func) {
  static_assert(Stop > 0, "invalid size");
  using type_t = decltype(Stop);
  detail::static_for_impl<Func, 1, type_t, 0>(
    std::forward<Func>(func), std::make_integer_sequence<type_t, (Stop - 0)>{}
  );
}

template <auto Start, auto Stop, typename Func>
constexpr void static_for(Func&& func) {
  static_assert((Stop - Start) > 0, "invalid size");
  using type_t = std::common_type_t<decltype(Start), decltype(Stop)>;
  detail::static_for_impl<Func, 1, type_t, Start>(
    std::forward<Func>(func), std::make_integer_sequence<type_t, (Stop - Start)>{}
  );
}

template <auto Start, auto Stop, auto Step, typename Func>
constexpr void static_for(Func&& func) {
  static_assert(((Stop - Start) / Step) > 0, "invalid size");
  using type_t = std::common_type_t<decltype(Start), decltype(Stop)>;
  detail::static_for_impl<Func, Step, type_t, Start>(
    std::forward<Func>(func), std::make_integer_sequence<type_t, (Stop - Start) / Step>{}
  );
}

///////////////////////////////////////////////////////////////////////////////

namespace detail {
template <typename T>
struct static_print_impl {};
}

template <typename T>
auto static_print() {
  return detail::static_print_impl<T>::value;
}

template <size_t N>
auto static_print() {
  return detail::static_print_impl<std::integral_constant<size_t, N>>::value;
}

///////////////////////////////////////////////////////////////////////////////

namespace detail {
struct nonesuch {
  ~nonesuch() = delete;
  nonesuch(nonesuch const&) = delete;
  void operator=(nonesuch const&) = delete;
};

template <class Default, class Void, template<class...> class Op, class... Args>
struct detector {
  using value_t = std::false_type;
  using type = Default;
};

template <class Default, template<class...> class Op, class... Args>
struct detector<Default, std::void_t<Op<Args...>>, Op, Args...> {
  using value_t = std::true_type;
  using type = Op<Args...>;
};
}

template <template<class...> class Op, class... Args>
using detected_t = typename detail::detector<detail::nonesuch, void, Op, Args...>::type;

template <class Default, template<class...> class Op, class... Args>
using detected_or_t = typename detail::detector<Default, void, Op, Args...>::type;

template<template<class...> class Op, class... Args>
constexpr bool is_detected_v = detail::detector<detail::nonesuch, void, Op, Args...>::value_t::value;

///////////////////////////////////////////////////////////////////////////////

template <typename... Args>
constexpr bool is_common_type_v = is_detected_v<std::common_type_t, Args...>;

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
  
  refcounted();
  virtual ~refcounted();
  
  mutable long refcount_;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class refcounted_ptr {
protected:

  struct managed_obj_t : refcounted {
    template <typename... Args>
    managed_obj_t(Args&&... args) : obj(std::forward<Args>(args)...) {}
    T obj;
  };

  managed_obj_t* ptr_;

public:
  
  refcounted_ptr() : ptr_(nullptr) {}
  
  ~refcounted_ptr() {
    if (ptr_)
      ptr_->release();
  }
  
  refcounted_ptr(const refcounted_ptr& other) : refcounted_ptr() {
    this->operator=(other);
  }
  
  refcounted_ptr(refcounted_ptr&& other) : refcounted_ptr() {
    this->operator=(std::move(other));
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
    ptr_ = other.ptr_;
    other.ptr_ == nullptr;
    return *this;
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
  
  uint32_t use_count() const {
    return ptr_ ? ptr_->refcount() : 0;
  }
  
  void reset(T* ptr) {
    if (ptr)
      ptr->acquire();
    if (ptr_)
      ptr_->release();
    ptr_ = ptr;
  }
  
  bool operator==(const refcounted_ptr& other) const {
    return (ptr_ == other.ptr_);
  }
  
  bool operator==(const T* other) const {
    return (ptr_ == other);
  }
  
  operator bool() const {
    return (ptr_ != nullptr);
  }

  template <typename... Args>
  static auto make(Args&&... args) {
    refcounted_ptr sp;
    sp.ptr_ = new managed_obj_t(std::forward<Args>(args)...);
    sp.ptr_->acquire();
    return sp;
  }
};

///////////////////////////////////////////////////////////////////////////////

template <class T>
class smart_ptr {
public:
    smart_ptr(T* ptr = nullptr) : ptr_(ptr), next_(nullptr) {}

    smart_ptr(const smart_ptr& other) : smart_ptr() {
      this->operator=(other);
    }

    ~smart_ptr() {
      this->release();
    }

    smart_ptr& operator=(const smart_ptr& other) {
      this->release();
      if (other.ptr_) {
        ptr_ = other.ptr_;
        auto otherNext = other.next_;
        other.next_ = this;
        next_ = otherNext ? otherNext : &other;
      }
      return *this;
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

    uint32_t use_count() const {
      if (nullptr == ptr_)
        return 0;
      if (nullptr == next_)
        return 1;
      uint32_t count = 1;
      auto entry = next_;
      while (entry != this) {
        ++count;
        entry = entry->next_;
      }
      return count;
    }

    void reset(T* ptr) {
      this->release();
      ptr_ = ptr;
    }

    void reset_all(T* ptr) {
      auto entry = next_;
      if (entry) {
        if (ptr) {
          while (entry != this) {
            entry->ptr_ = ptr;
            entry = entry->next_;
          }
        } else {
          while (entry != this) {
            auto next = entry->next_;
            const_cast<smart_ptr*>(entry)->reset(ptr);
            entry = next;
          }
        }
      }
      delete ptr_;
      ptr_ = ptr;
    }

    void reset_all(const smart_ptr& other) {
      this->reset_all(other.ptr_);
      // merge lists
      auto otherNext = other.next_ ? other.next_ : &other;
      other.next_ = this;
      auto entry = next_;
      if (entry) {
        while (entry->next_ != this) {
          entry = entry->next_;
        }
        entry->next_ = otherNext;
      } else {
        next_ = otherNext;
      }
    }

    bool operator==(const smart_ptr& other) const {
      return (ptr_ == other.ptr_);
    }

    bool operator==(const T* other) const {
      return (ptr_ == other);
    }

    operator bool() const {
      return (ptr_ != nullptr);
    }

    template <typename... Args>
    static auto make(Args&&... args) {
      return smart_ptr(new T(std::forward<Args>(args)...));
    }

protected:

    void release() {
      if (nullptr == ptr_)
        return;
      auto entry = next_;
      if (entry) {
        while (entry->next_ != this) {
          entry = entry->next_;
        }
        if (entry == entry->next_->next_) {
          entry->next_ = nullptr; // single entry
        } else {
          entry->next_ = next_; // multiple entries
        }
        next_ = nullptr;
      } else {
        delete ptr_;
      }
      ptr_ = nullptr;
    }

    mutable T* ptr_;
    mutable const smart_ptr<T>* next_;
};

///////////////////////////////////////////////////////////////////////////////

class source_info {
public:
  explicit source_info(const char* varinfo = nullptr)   
    : line_(0)
    , column_(0) {
    if (varinfo && *varinfo) {
      std::istringstream iss(varinfo);
      std::vector<std::string> tokens;
      std::string token;
      while (std::getline(iss, token, ':')) {
        tokens.push_back(token);
      }
      assert(4 == tokens.size());
      name_   = tokens[0];
      file_   = tokens[1];
      line_   = std::stoi(tokens[2]);
      column_ = std::stoi(tokens[3]);
    }   
     
  }
  explicit source_info(const char* file, int line, int column)
    : file_(file)
    , line_(line)
    , column_(column)
  {}

  source_info(const source_info& other)
    : name_(other.name_)
    , file_(other.file_)
    , line_(other.line_)
  {}

  source_info(source_info&& other)
    : name_(std::move(other.name_))
    , file_(std::move(other.file_))
    , line_(std::move(other.line_))
  {}

  source_info& operator=(const source_info& other) {
    name_ = other.name_;
    file_ = other.file_;
    line_ = other.line_;
    return *this;
  }

  source_info& operator=(source_info&& other) {
    name_ = std::move(other.name_);
    file_ = std::move(other.file_);
    line_ = std::move(other.line_);
    return *this;
  }

  const std::string& name() const {
    return name_;
  }

  const std::string& file() const {
    return file_;
  }

  int line() const {
    return line_;
  }

  int column() const {
    return column_;
  }

  bool empty() const {
    return file_.empty();
  }

private:

  friend std::ostream& operator<<(std::ostream& out, const source_info& sloc) {
    out << sloc.file() << ":" << sloc.line();
    return out;
  }

  std::string name_;
  std::string file_;
  int line_;
  int column_;
};

#if defined(__builtin_VARINFO)
  #define CH_CUR_SLOC ch::internal::source_info(__builtin_VARINFO())
#elif defined(__builtin_FILE) && defined(__builtin_FILE) && defined(__builtin_COLUMN)
  #define CH_CUR_SLOC ch::internal::source_info(__builtin_FILE(), __builtin_LINE(), __builtin_COLUMN())
#elif defined(__builtin_FILE) && defined(__builtin_FILE)
  #define CH_CUR_SLOC ch::internal::source_info(__builtin_FILE(), __builtin_LINE(), 0)
#else
  #define CH_CUR_SLOC ch::internal::source_info(__FILE__, __LINE__, 0)
#endif

#define CH_SLOC const ch::internal::source_info& sloc = CH_CUR_SLOC

template <typename T>
struct sloc_proxy {
  sloc_proxy(const T& p_data, const source_info& p_sloc = CH_CUR_SLOC) 
    : data(p_data)
    , sloc(p_sloc) 
  {}  
  
  template <typename U,
            CH_REQUIRE(std::is_convertible_v<U, T>)>
  sloc_proxy(const sloc_proxy<U>& other) 
    : data(other.data)
    , sloc(other.sloc) 
  {}

  const T& data;
  source_info sloc;
};

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
  scope_exit(const std::function<void()>& func) : func_(func) {}
  ~scope_exit() { func_(); }
  // force stack only allocation!
  static void *operator new   (size_t) = delete;
  static void *operator new[] (size_t) = delete;
protected:
  std::function<void()> func_;
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

/// ///////////////////////////////////////////////////////////////////////////

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
constexpr unsigned log2up(T value) {
  static_assert(std::is_integral_v<T>, "invalid type");
  return std::max<T>(1, log2ceil(value));
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
          CH_REQUIRE(!std::is_same_v<R, T>)>
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

template <typename T, typename U>
constexpr T roundup(T a, U b) {
  return b * ceildiv(a, b);
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
  assert(bitwidth_v<U> >= width);
  assert(0 == (value & ~(0xffffffffffffffff >> (64 - width))));
  auto m = U(1) << (width - 1);
  return std::make_signed_t<T>((value ^ m) - m);
}

///////////////////////////////////////////////////////////////////////////////

template <typename... Args>
void unused(Args&&...) {}

}
}

///////////////////////////////////////////////////////////////////////////////

#define CH_UNUSED(...) ch::internal::unused(__VA_ARGS__)

#define CH_CHECK(pred, ...) \
  do { \
    if (!(pred)) { \
      throw std::runtime_error(ch::internal::sstreamf() \
                  << "assertion `" CH_STRINGIZE(pred) \
                  << "` failed, " << ch::internal::stringf(__VA_ARGS__)); \
    } \
  } while (false)

#ifdef NDEBUG
  #define CH_ABORT(...) \
    do { \
      fprintf(stderr, "ERROR: "); \
      fprintf(stderr, __VA_ARGS__); \
      std::abort(); \
    } while (false)

  #define CH_DBGCHECK(pred, ...) CH_UNUSED(pred)
  #define CH_DBG(level, ...)
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
  inline constexpr bool type_name##_v = type_name##_impl<std::decay_t<T>>::value

#define CH_TODO() CH_ABORT("Not yet implemented");
