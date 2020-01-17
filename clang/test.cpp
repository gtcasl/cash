#include <iostream>
#include <string>

const char* __builtin_VARNAME() {
  return "";
}

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

  auto name() const {
    return name_.c_str();
  }

  const auto& data() const {
    return data_;
  }

  Object copy(const char* name = __builtin_VARNAME()) {
    return Object(data_, name);
  }

  friend Object operator+(Object lhs, const Object& rhs) {
    return Object(lhs.name());
  }

private:
  std::string name_;
  T data_;
};

template <typename T>
struct Object2 {
  Object<T> obj_data;
  int qq;
};

template <typename T>
auto foo(const Object<T>& x, const char* name = __builtin_VARNAME()) {
  return Object<T>(x, name);
}

template <typename T>
void program() {
  Object2<T> obj0;
  Object<T> obj1, obj2(0);
  auto obj3 = obj1 + obj2;
  Object<T> obj4(obj1);  
  auto obj5 = foo(obj4);      
  auto obj6 = foo(obj4, "obj6"); 
  auto obj7 = obj4.copy();
  std::cout << "names=" << obj0.obj_data.name() << ", " << obj1.name() << ", " << obj2.name() << ", " << obj3.name() << ", " 
                        << obj4.name() << ", " << obj5.name() << ", " << obj6.name() << ", " << obj7.name() << std::endl;
}

#include <iostream>
#include <string>
int main() {
  program<int>();
}


