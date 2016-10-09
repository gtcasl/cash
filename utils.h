#pragma once

namespace chdl_internal {

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
  
  void acquire() const {
    ++m_refcount;
  }

  void release() const {
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

}
