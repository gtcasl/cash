#pragma once

namespace chdl_internal {

std::string fstring(const char* format, ...);

void DbgPrint(int level, const char *format, ...);

void dump_stack_trace(FILE* out, unsigned int max_frames = 32);

#ifdef NDEBUG
  #define CHDL_ABORT(msg, ...) \
    do { \
      fprintf(stderr, "error: " msg "\n", ##__VA_ARGS__); \
      std::abort(); \
    } while (false)
  #define DBG(level, format, ...)
#else
  #define CHDL_ABORT(msg, ...) \
    do { \
      chdl_internal::dump_stack_trace(stdout); \
      fprintf(stderr, "\nerror: " msg " (%s:%d:%s)\n", ##__VA_ARGS__, __FILE__, __LINE__, __FUNCTION__); \
      std::abort(); \
    } while (false)
  #define DBG(level, format, ...) \
    do { \
      DbgPrint(level, "DBG: " format, ##__VA_ARGS__); \
    } while (false)
#endif

#define CHDL_CHECK(x, msg, ...) \
  do { \
    if (!(x)) { \
      CHDL_ABORT(msg, ##__VA_ARGS__); \
    } \
  } while (false)

#define TODO(x) \
  CHDL_ABORT(#x);

#define CHDL_COUNTOF(a) (sizeof(a) / sizeof(a[0]))
#define CHDL_MAX(a,b) (((a) > (b)) ? (a) : (b))

#define CHDL_OUT(...) std::tuple<__VA_ARGS__>
#define CHDL_RET(...) return std::make_tuple(__VA_ARGS__)
#define CHDL_TIE(...) std::forward_as_tuple(__VA_ARGS__)

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
    ++m_refcount;
  }

  void release() const {
    assert(m_refcount > 0);
    if (--m_refcount <= 0)
      delete this;
  }
  
  long get_refcount() const {
    return m_refcount;
  }
  
protected:
  
  refcounted() : m_refcount(0) {}
  virtual ~refcounted() {}
  
private:
  
  mutable long m_refcount;
  
  template <typename T> friend class refcounted_ptr;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class refcounted_ptr {
public:
  
  refcounted_ptr() : m_ptr(nullptr) {}
  
  ~refcounted_ptr() {
    if (m_ptr)
      m_ptr->release();
  }
  
  refcounted_ptr(const refcounted_ptr& rhs) : refcounted_ptr(rhs.m_ptr) {}
  
  refcounted_ptr(refcounted_ptr&& rhs) {
    m_ptr = rhs.m_ptr;
    rhs.m_ptr == nullptr;
  }
  
  refcounted_ptr& operator=(const refcounted_ptr& rhs) {
    if (rhs.m_ptr)
      rhs.m_ptr->acquire();
    if (m_ptr)
      m_ptr->release();
    m_ptr = rhs.m_ptr;
    return *this;
  }
  
  refcounted_ptr& operator=(refcounted_ptr&& rhs) {
    if (rhs.m_ptr)
      rhs.m_ptr->release();
    m_ptr = rhs.m_ptr;
    rhs.m_ptr == nullptr;
  }
  
  T& operator*() const {
    return *m_ptr;
  }
  
  T* operator->() const {
    return m_ptr;
  }
  
  T* get() const {
    return m_ptr;
  }
  
  T* release() const {
    T* ret(m_ptr);
    if (ret)
     ret->release();    
    m_ptr = nullptr;
    return ret;
  }
  
  bool is_unique() const {
    return m_ptr ? (m_ptr->get_refcount() == 1) : false;
  }
  
  unsigned get_use_count() const {
    return m_ptr ? (m_ptr->get_refcount() == 1) : false;
  }
  
  void reset(T* ptr = nullptr) {
    if (ptr)
      ptr->acquire();
    if (m_ptr)
      m_ptr->release();
    m_ptr = ptr;    
    return *this;
  }
  
  bool operator==(const refcounted_ptr& rhs) const {
    return (m_ptr == rhs.m_ptr);
  }
  
  bool operator==(const T* rhs) const {
    return (m_ptr == rhs);
  }
  
  operator bool() const {
    return this->get_use_count() != 0;
  }
  
protected:    
  
  refcounted_ptr(refcounted* ptr) : m_ptr(ptr) {
    if (ptr)
      ptr->acquire();
  }
  
  refcounted* m_ptr;
  
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
    scope_exit(const std::function<void()>& f) : m_f(f) {}
    ~scope_exit() { m_f(); }
    // force stack only allocation!
    static void *operator new   (size_t) = delete;
    static void *operator new[] (size_t) = delete;
protected:
    std::function<void()> m_f;
};

///////////////////////////////////////////////////////////////////////////////

// is power of two number ?
constexpr bool IS_POW2(unsigned value) { 
  return value && !(value & (value - 1)); 
}

// return log2
constexpr unsigned LOG2(unsigned x) {
  return (x <= 1) ? 0 : (LOG2(x >> 1) + 1);
}

// return ceil of log2
constexpr unsigned CLOG2(unsigned x) {
  return IS_POW2(x) ? LOG2(x) : (LOG2(x) + 1);
}

template <class D, class S>
D bit_cast(const S& src) {
  union merged_t {
    S src;
    D dst;    
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
