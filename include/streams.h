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

  void write(const lnode& node);

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
    CH_API_ENTRY(1);
    reinterpret_cast<base&>(*this) << value;
    return *this;
  }

  ch_ostream& operator<<(char value) {
    CH_API_ENTRY(1);
    reinterpret_cast<base&>(*this) << value;
    return *this;
  }

  ch_ostream& operator<<(unsigned char value) {
    CH_API_ENTRY(1);
    reinterpret_cast<base&>(*this) << value;
    return *this;
  }

  ch_ostream& operator<<(short value) {
    CH_API_ENTRY(1);
    reinterpret_cast<base&>(*this) << value;
    return *this;
  }

  ch_ostream& operator<<(unsigned short value) {
    CH_API_ENTRY(1);
    reinterpret_cast<base&>(*this) << value;
    return *this;
  }

  ch_ostream& operator<<(int value) {
    CH_API_ENTRY(1);
    reinterpret_cast<base&>(*this) << value;
    return *this;
  }

  ch_ostream& operator<<(unsigned int value) {
    CH_API_ENTRY(1);
    reinterpret_cast<base&>(*this) << value;
    return *this;
  }

  ch_ostream& operator<<(long value) {
    CH_API_ENTRY(1);
    reinterpret_cast<base&>(*this) << value;
    return *this;
  }

  ch_ostream& operator<<(unsigned long value) {
    CH_API_ENTRY(1);
    reinterpret_cast<base&>(*this) << value;
    return *this;
  }

  ch_ostream& operator<<(long long value) {
    CH_API_ENTRY(1);
    reinterpret_cast<base&>(*this) << value;
    return *this;
  }

  ch_ostream& operator<<(unsigned long long value) {
    CH_API_ENTRY(1);
    reinterpret_cast<base&>(*this) << value;
    return *this;
  }

  ch_ostream& operator<<(float value) {
    CH_API_ENTRY(1);
    reinterpret_cast<base&>(*this) << value;
    return *this;
  }

  ch_ostream& operator<<(double value) {
    CH_API_ENTRY(1);
    reinterpret_cast<base&>(*this) << value;
    return *this;
  }

  ch_ostream& operator<<(long double value) {
    CH_API_ENTRY(1);
    reinterpret_cast<base&>(*this) << value;
    return *this;
  }

  ch_ostream& operator<<(const char* value) {
    CH_API_ENTRY(1);
    reinterpret_cast<base&>(*this) << value;
    return *this;
  }

  ch_ostream& operator<<(const lnode& value) {
    CH_API_ENTRY(1);
    buf_.write(value);
    return *this;
  }

  ch_ostream& operator<<(std::basic_streambuf<char>* sb) {
    CH_API_ENTRY(1);
    base::operator<<(sb);
    return *this;
  }

  ch_ostream& operator<<(std::ios_base& (*func)(std::ios_base&)) {
    CH_API_ENTRY(1);
    base::operator<<(func);
    return *this;
  }

  ch_ostream& operator<<(std::basic_ios<char>& (*func)(std::basic_ios<char>&)) {
    CH_API_ENTRY(1);
    base::operator<<(func);
    return *this;
  }

  ch_ostream& operator<<(std::basic_ostream<char>& (*func)(std::basic_ostream<char>&)) {
    CH_API_ENTRY(1);
    base::operator<<(func);
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
