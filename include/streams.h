#pragma once

#include "lnode.h"

namespace ch {
namespace internal {

class ch_streambuf : public std::stringbuf {
public:
  using base = std::stringbuf;

  ch_streambuf() {}

  ch_streambuf(ch_streambuf&& other)
    : base(std::move(other))
    , nodes_(std::move(other.nodes_))
  {}

  ch_streambuf& operator=(ch_streambuf&& other) {
    base::operator=(std::move(other));
    nodes_ = std::move(other.nodes_);
    return *this;
  }

  void swap(ch_streambuf& other) {
    base::swap(other);
    std::swap(nodes_, other.nodes_);
  }

private:

  int sync() override;

  void write(const lnode& node, char format);

  std::vector<lnode> nodes_;

  ch_streambuf(const ch_streambuf&) = delete;

  ch_streambuf& operator=(const ch_streambuf&) = delete;

  friend class ch_ostream;
};

///////////////////////////////////////////////////////////////////////////////

class ch_ostream : public std::basic_ostream<char> {
public:
  using base = std::basic_ostream<char>;

  ch_ostream() : base(&buf_) {}

  ch_ostream(ch_ostream&& other)
    : base(std::move(other))
    , buf_(std::move(other.buf_)) {
    base::set_rdbuf(&buf_);
  }

  ch_ostream& operator=(ch_ostream&& other) {
    base::operator=(std::move(other));
    buf_ = std::move(other.buf_);
    return *this;
  }

  void swap(ch_ostream& other) {
    base::swap(other);
    buf_.swap(other.buf_);
  }

  ch_streambuf* rdbuf() const {
    return const_cast<ch_streambuf*>(&buf_);
  }

  ch_ostream& operator<<(bool value) {
  #ifndef NDEBUG
    CH_API_ENTRY(1);
    reinterpret_cast<base&>(*this) << value;
  #else
    CH_UNUSED(value);
  #endif
    return *this;
  }

  ch_ostream& operator<<(char value) {
  #ifndef NDEBUG
    CH_API_ENTRY(1);
    reinterpret_cast<base&>(*this) << value;
  #else
    CH_UNUSED(value);
  #endif
    return *this;
  }

  ch_ostream& operator<<(unsigned char value) {
  #ifndef NDEBUG
    CH_API_ENTRY(1);
    reinterpret_cast<base&>(*this) << value;
  #else
    CH_UNUSED(value);
  #endif
    return *this;
  }

  ch_ostream& operator<<(short value) {
  #ifndef NDEBUG
    CH_API_ENTRY(1);
    reinterpret_cast<base&>(*this) << value;
  #else
    CH_UNUSED(value);
  #endif
    return *this;
  }

  ch_ostream& operator<<(unsigned short value) {
  #ifndef NDEBUG
    CH_API_ENTRY(1);
    reinterpret_cast<base&>(*this) << value;
  #else
    CH_UNUSED(value);
  #endif
    return *this;
  }

  ch_ostream& operator<<(int value) {
  #ifndef NDEBUG
    CH_API_ENTRY(1);
    reinterpret_cast<base&>(*this) << value;
  #else
    CH_UNUSED(value);
  #endif
    return *this;
  }

  ch_ostream& operator<<(unsigned int value) {
  #ifndef NDEBUG
    CH_API_ENTRY(1);
    reinterpret_cast<base&>(*this) << value;
  #else
    CH_UNUSED(value);
  #endif
    return *this;
  }

  ch_ostream& operator<<(long value) {
  #ifndef NDEBUG
    CH_API_ENTRY(1);
    reinterpret_cast<base&>(*this) << value;
  #else
    CH_UNUSED(value);
  #endif
    return *this;
  }

  ch_ostream& operator<<(unsigned long value) {
  #ifndef NDEBUG
    CH_API_ENTRY(1);
    reinterpret_cast<base&>(*this) << value;
  #else
    CH_UNUSED(value);
  #endif
    return *this;
  }

  ch_ostream& operator<<(long long value) {
  #ifndef NDEBUG
    CH_API_ENTRY(1);
    reinterpret_cast<base&>(*this) << value;
  #else
    CH_UNUSED(value);
  #endif
    return *this;
  }

  ch_ostream& operator<<(unsigned long long value) {
  #ifndef NDEBUG
    CH_API_ENTRY(1);
    reinterpret_cast<base&>(*this) << value;    
  #else
    CH_UNUSED(value);
  #endif
    return *this;
  }

  ch_ostream& operator<<(float value) {
  #ifndef NDEBUG
    CH_API_ENTRY(1);
    reinterpret_cast<base&>(*this) << value;    
  #else
    CH_UNUSED(value);
  #endif
    return *this;
  }

  ch_ostream& operator<<(double value) {
  #ifndef NDEBUG
    CH_API_ENTRY(1);
    reinterpret_cast<base&>(*this) << value;
  #else
    CH_UNUSED(value);
  #endif
    return *this;
  }

  ch_ostream& operator<<(long double value) {
  #ifndef NDEBUG
    CH_API_ENTRY(1);
    reinterpret_cast<base&>(*this) << value;
  #else
    CH_UNUSED(value);
  #endif
    return *this;
  }

  ch_ostream& operator<<(const char* value) {
  #ifndef NDEBUG
    CH_API_ENTRY(1);
    auto tok = strpbrk(value, "{}");
    if (tok) {
      // escape special characters
      std::string s(value);
      size_t pos = 0;
      while ((pos = s.find_first_of("{}", pos)) != std::string::npos) {
        s.insert(pos, 1, '\\');
        pos += 2;
      }
      reinterpret_cast<base&>(*this) << s;
    } else {
      reinterpret_cast<base&>(*this) << value;
    }
  #else
    CH_UNUSED(value);
  #endif
    return *this;
  }

  ch_ostream& operator<<(std::basic_streambuf<char>* sb) {
  #ifndef NDEBUG
    CH_API_ENTRY(1);
    base::operator<<(sb);
  #else
    CH_UNUSED(sb);
  #endif
    return *this;
  }

  ch_ostream& operator<<(std::ios_base& (*func)(std::ios_base&)) {
  #ifndef NDEBUG
    CH_API_ENTRY(1);
    base::operator<<(func);
  #else
    CH_UNUSED(func);
  #endif
    return *this;
  }

  ch_ostream& operator<<(std::basic_ios<char>& (*func)(std::basic_ios<char>&)) {
  #ifndef NDEBUG
    CH_API_ENTRY(1);
    base::operator<<(func);
  #else
    CH_UNUSED(func);
  #endif
    return *this;
  }

  ch_ostream& operator<<(std::basic_ostream<char>& (*func)(std::basic_ostream<char>&)) {
  #ifndef NDEBUG
    CH_API_ENTRY(1);
    base::operator<<(func);
  #else
    CH_UNUSED(func);
  #endif
    return *this;
  }

  ch_ostream& write(const lnode& value, char format) {
  #ifndef NDEBUG
    CH_API_ENTRY(1);
    buf_.write(value, format);
  #else
    CH_UNUSED(value, format);
  #endif
    return *this;
  }

private:

  ch_ostream(const ch_ostream&) = delete;

  ch_ostream& operator=(const ch_ostream&) = delete;

  ch_streambuf buf_;

  friend class ch_cout_stream;
};

///////////////////////////////////////////////////////////////////////////////

extern ch_ostream ch_cout;

}
}
