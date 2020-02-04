#include <iostream>
#include <string>

template <typename T>
struct srcinfo_proxy {
  srcinfo_proxy(const T& p_data, const char* p_varinfo = __builtin_VARINFO()) 
    : data(p_data)
    , varinfo(p_varinfo) 
  {}  

  const T& data;
  std::string varinfo;
};

template <typename T>
class Object {
public:
  Object(const char* varinfo = __builtin_VARINFO()) 
    : data_(0)
    , varinfo_(varinfo) 
  {}  

  Object(const T& data, const char* varinfo = __builtin_VARINFO()) 
    : data_(data)
    , varinfo_(varinfo)
  {}

  Object(const Object& other, const char* varinfo = __builtin_VARINFO()) 
    : data_(other.data_)
    , varinfo_(varinfo)
  {}

  auto& varinfo() const {
    return varinfo_;
  }

  auto& data() const {
    return data_;
  }

  Object copy(const char* varinfo = __builtin_VARINFO()) {
    return Object(data_, varinfo);
  }  

  friend Object operator+(Object lhs, const Object& rhs) {
    return Object(lhs.data() + rhs.data(), lhs.varinfo().c_str());
  }

  friend Object operator-(const srcinfo_proxy<Object>& lhs, const Object& rhs) {
    return Object(lhs.data.data() + rhs.data(), lhs.varinfo.c_str());
  }

  friend Object operator*(const Object& lhs, const Object& rhs) {
    return Object(lhs.data() + rhs.data());
  }

private:
  std::string varinfo_;
  T data_;
};

class src_info {
public:
  src_info(const char* varinfo) 
    : varinfo_(varinfo)
  {}

  auto& varinfo() const {
    return varinfo_;
  }

private:
  std::string varinfo_;
};

#define CUR_SRC_INFO src_info(__builtin_VARINFO())
#define SRC_INFO const src_info& sinfo = CUR_SRC_INFO

template <typename T>
class ObjectX {
public:
  ObjectX(SRC_INFO) 
    : data_(0)
    , sinfo_(sinfo)
  {}

  ObjectX(T data, SRC_INFO) 
    : data_(data)
    , sinfo_(sinfo)
  {}

  ObjectX(const ObjectX& other, SRC_INFO) 
    : data_(other.data_)
    , sinfo_(sinfo)
  {}

  auto& sinfo() const {
    return sinfo_;
  }

  auto& varinfo() const {
    return sinfo_.varinfo();
  }

  auto& data() const {
    return data_;
  }

  auto copy(SRC_INFO) {
    return ObjectX(data_, sinfo);
  }

  friend ObjectX operator+(ObjectX lhs, const ObjectX& rhs) {
    return ObjectX(lhs.data() + rhs.data(), lhs.sinfo());
  }

private:
  T data_;
  src_info sinfo_;  
};

template <typename T>
struct Object2 {
  Object<T> obj_data;
  ObjectX<int> qq;
};

template <typename T>
auto foo(const T& data, const char* varinfo = __builtin_VARINFO()) {
  return Object<T>(data, varinfo);
}

template <typename T>
auto fooX(const T& data, const src_info& sinfo = CUR_SRC_INFO) {
  return ObjectX<T>(data, sinfo);
}

Object<int> obj0;
ObjectX<int> obj1;

void program1() {
  Object<int> obj2;       
  ObjectX<int> obj3;
  Object2<int> obj4;
  std::cout << "program1=" << obj0.varinfo() << ", " << obj1.varinfo() << ", " << obj2.varinfo() << ", " 
            << obj3.varinfo() << ", " << obj4.obj_data.varinfo() << ", " << obj4.qq.varinfo() << std::endl;
}

template <typename T>
void program2() {      
  ObjectX<int> qq[2];
  ObjectX<int> obj5, obj6;  
  auto obj7 = obj0.copy();
  auto obj8 = obj1.copy();
  auto obj9 = foo<T>(9);
  auto obj10 = fooX<T>(10);
  auto obj11 = foo<T>(9) + obj7;
  auto obj12 = obj1 + obj8;
  std::cout << "program2=" << qq[1].varinfo() << ", " << obj5.varinfo() << ", " << obj6.varinfo() << ", " << obj7.varinfo() << ", " 
            << obj8.varinfo() << ", " << obj9.varinfo() << ", " << obj10.varinfo() << ", " << obj11.varinfo() << ", " << obj12.varinfo() << std::endl;
}

int main() {
  program1();
  program2<int>();
  return 0;
}