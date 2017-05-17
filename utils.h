#pragma once

namespace cash_internal {

std::string fstring(const char* format, ...);

void dbprint(int level, const char *format, ...);

void dump_stack_trace(FILE* out, unsigned int max_frames = 32);

#ifdef NDEBUG
  #define CH_ABORT(msg, ...) \
    do { \
      fprintf(stderr, "error: " msg "\n", ##__VA_ARGS__); \
      std::abort(); \
    } while (0)

  #define DBG(level, format, ...)
#else
  #define CH_ABORT(msg, ...) \
    do { \
      cash_internal::dump_stack_trace(stdout); \
      fprintf(stderr, "ERROR: " msg " (%s:%d:%s)\n", ##__VA_ARGS__, __FILE__, __LINE__, __FUNCTION__); \
      std::abort(); \
    } while (0)

  #define DBG(level, format, ...) \
    dbprint(level, "DBG: " format, ##__VA_ARGS__)
#endif

#define CH_CHECK(x, msg, ...) \
  if (!(x)) CH_ABORT(msg, ##__VA_ARGS__)

#define TODO(x) CH_ABORT(#x);

#define CH_COUNTOF(a) (sizeof(a) / sizeof(a[0]))
#define CH_MAX(a,b) (((a) > (b)) ? (a) : (b))

#define CH_OUT(...) std::tuple<__VA_ARGS__>
#define CH_RET(...) return std::make_tuple(__VA_ARGS__)
#define CH_TIE(...) std::forward_as_tuple(__VA_ARGS__)

///////////////////////////////////////////////////////////////////////////////

template <size_t ...I>
struct index_sequence {};

template <size_t N, size_t ...I>
struct make_index_sequence : public make_index_sequence<N - 1, N - 1, I...> {};

template <size_t ...I>
struct make_index_sequence<0, I...> : public index_sequence<I...> {};

template <typename T>
struct identity {
  using type = T;
};

///////////////////////////////////////////////////////////////////////////////

template <typename Function>
struct function_traits : public function_traits<decltype(&Function::operator())> {};

template <typename Class, typename Ret, typename ...Args>
struct function_traits<Ret(Class::*)(Args...) const> {
    using function = const std::function<Ret(Args...)>;
};

template <typename Function>
typename function_traits<Function>::function to_function(const Function& func) {
    return static_cast<typename function_traits<Function>::function>(func);
}

///////////////////////////////////////////////////////////////////////////////

class refcounted {
public:
  
  void acquire() const {
    ++refcount_;
  }

  void release() const {
    assert(refcount_ > 0);
    if (--refcount_ <= 0)
      delete this;
  }
  
  long get_refcount() const {
    return refcount_;
  }
  
protected:
  
  refcounted() : refcount_(0) {}
  virtual ~refcounted() {}
  
private:
  
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
  
  template <typename T_, typename ...Args>
  friend refcounted_ptr<T_> make_ptr(const Args&... args);
};

template <typename T, typename ...Args>
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

// is power of two number ?
constexpr bool ispow2(unsigned value) { 
  return value && !(value & (value - 1)); 
}

// return log2
constexpr unsigned ilog2(unsigned x) {
  return (x <= 1) ? 0 : (ilog2(x >> 1) + 1);
}

// return ceil of log2
constexpr unsigned ilog2ceil(unsigned x) {
  return ispow2(x) ? ilog2(x) : (ilog2(x) + 1);
}

template <class Dst, class Src>
Dst bit_cast(const Src& src) {
  union merged_t {
    Src src;
    Dst dst;
  };
  merged_t m;
  m.dst = 0;
  m.src = src;
  return m.dst;  
}

inline uint32_t countLeadingZeros(uint32_t value) {
  uint32_t count;
  if (value == 0) return 32; 
  for (count = 0; ((value & 0x80000000) == 0); ++count, value <<= 1);
  return count;
}

inline uint32_t countTrailingZeros(uint32_t value) {
  uint32_t count;
  if (value == 0) return 32;
  value = (value ^ (value - 1)) >> 1;  // Set x's trailing 0s to 1s and zero rest
  for (count = 0; value; ++count, value >>= 1);
  return count; 
}

inline uint32_t rotl(uint32_t value, uint32_t shift, uint32_t width) {
  assert(shift < width);
  return  (value << shift) | (value >> (width - shift));
}

inline uint32_t rotr(uint32_t value, uint32_t shift, uint32_t width) {
  assert(shift < width);
  return (value >> shift) | (value << (width  - shift));
}

}
