#pragma once

class ch_interface {
public:  
  
  
private:
};

#define CH_INTERFACE_IMPL(name, ...) \
  class name : public ch_interface { \
  public:\
    name() {} \
  protected: \
  public:

#define CH_INTERFACE(name, body, ...) CH_INTERFACE_IMPL(name, CH_REM body) __VA_ARGS__ }

template <typename T>
class ch_port : public T {};

template <typename T>
class ch_in : public ch_port<T> {};

template <typename T>
class ch_out : public ch_port<T> {
public:
  using T::operator=;  
};

template <typename T>
class ch_io : public ch_port<T> {};

class ch_module {
public:  
};

class Adder2 : public ch_module {
public:
  ch_in<ch_bit4>  x;
  ch_in<ch_bit4>  y;
  ch_out<ch_bit4> z;
  
  Adder2() {
    z = x + y;
  }   
};
