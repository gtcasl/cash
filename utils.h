#pragma once

namespace chdl_internal {

#ifdef NDEBUG
  #define CHDL_ABORT(...) do { \
      fprintf(stderr, "error: "); \
      fprintf(stderr, ##__VA_ARGS__); \
      fprintf(stderr, "\n"); \
      std::abort(); \
    } while (0)
#else
  #define CHDL_ABORT(...) do { \
      fprintf(stderr, "\nerror: "); \
      fprintf(stderr, ##__VA_ARGS__); \
      fprintf(stderr, " (%s:%d:%s)", __FILE__, __LINE__, __FUNCTION__); \
      fprintf(stderr, "\n"); \
      std::abort(); \
    } while (0)
#endif

#define TODO() \
  CHDL_ABORT("Not yet implemented!");

#define CHDL_COUNTOF(a) (sizeof(a) / sizeof(a[0])) 

#define CHDL_MAX(a,b) (((a) > (b)) ? (a) : (b))

std::string fstring(const char* format, ...);

///////////////////////////////////////////////////////////////////////////////

template <size_t ...I>
struct index_sequence {};

template <size_t N, size_t ...I>
struct make_index_sequence : public make_index_sequence<N - 1, N - 1, I...> {};

template <size_t ...I>
struct make_index_sequence<0, I...> : public index_sequence<I...> {};

template <typename T>
struct identity {
  typedef T type;
};

///////////////////////////////////////////////////////////////////////////////

template <typename Function>
struct function_traits : public function_traits<decltype(&Function::operator())> {};

template <typename Class, typename Ret, typename... Args>
struct function_traits<Ret(Class::*)(Args...) const> {
    typedef const std::function<Ret(Args...)> function;
};

template <typename Function>
typename function_traits<Function>::function to_function(const Function& func) {
    return static_cast<typename function_traits<Function>::function>(func);
}

///////////////////////////////////////////////////////////////////////////////

class refcounted {
public:
  void add_ref() const {
    ++m_refcount;
  }

  void release() const {
    if (0 == --m_refcount)
      delete this;
  }
  
  long get_refcount() const {
    return m_refcount;
  }
    
protected:
  refcounted() : m_refcount(1) {}
  virtual ~refcounted() {}
    
private:  
  mutable long m_refcount;
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

}
