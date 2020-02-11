#include <iostream>
#include <string>

template <typename T>
struct srcinfo_arg {
  srcinfo_arg(const T& p_data, const char* p_name = __builtin_VARNAME()) 
    : data(p_data)
    , name(p_name) 
  {}  

  const T& data;
  std::string name;
};

template <typename T>
class Object {
public:
  Object(const char* name = __builtin_VARNAME()) 
    : data_(0)
    , name_(name) 
  {}  

  Object(const T& data, const char* name = __builtin_VARNAME()) 
    : data_(data)
    , name_(name)
  {}

  Object(const Object& other, const char* name = __builtin_VARNAME()) 
    : data_(other.data_)
    , name_(name)
  {}

  auto& name() const {
    return name_;
  }

  auto& data() const {
    return data_;
  }

  Object copy(const char* name = __builtin_VARNAME()) {
    return Object(data_, name);
  }  

  Object& operator=(const Object& other) {
    data_ = other.data_;    
    return *this;
  }

  friend Object operator+(Object lhs, const Object& rhs) {
    return Object(lhs.data() + rhs.data(), lhs.name().c_str());
  }

  friend Object operator-(const srcinfo_arg<Object>& lhs, const Object& rhs) {
    return Object(lhs.data.data() + rhs.data(), lhs.name.c_str());
  }

  friend Object operator*(const Object& lhs, const Object& rhs) {
    return Object(lhs.data() + rhs.data());
  }

private:
  std::string name_;
  T data_;
};

class src_info {
public:
  src_info(const char* name) 
    : name_(name)
  {}

  auto& name() const {
    return name_;
  }

private:
  std::string name_;
};

#define CUR_SRC_INFO src_info(__builtin_VARNAME())
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

  ObjectX& operator=(const ObjectX& other) {
    data_ = other.data_;    
    return *this;
  }

  auto& sinfo() const {
    return sinfo_;
  }

  auto& name() const {
    return sinfo_.name();
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
auto foo(const T& data, const char* name = __builtin_VARNAME()) {
  return Object<T>(data, name);
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
  std::cout << "program1=" << obj0.name() << ", " << obj1.name() << ", " << obj2.name() << ", " 
            << obj3.name() << ", " << obj4.obj_data.name() << ", " << obj4.qq.name() << std::endl;
}

template <typename T>
void program2() {      
  ObjectX<int> qq[2];
  ObjectX<int> obj5, obj6;  
  auto obj7 = obj0.copy();
  auto obj8 = obj1.copy();
  auto obj9 = foo<T>(9);
  auto obj10 = fooX<T>(10);
  auto obj11 = obj0 + obj7;
  auto obj12 = obj1 + obj8;
  std::cout << "program2=" << qq[1].name() << ", " << obj5.name() << ", " << obj6.name() << ", " << obj7.name() << ", " 
            << obj8.name() << ", " << obj9.name() << ", " << obj10.name() << ", " << obj11.name() << ", " << obj12.name() << std::endl;
}

int main() {
  program1();
  program2<int>();
  return 0;
}