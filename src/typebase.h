#pragma once

#include "common.h"
#include "bitvector.h"

namespace cash {
namespace internal {

template <unsigned N>
class ch_literal {
public:
  ch_literal(const bitvector& value) : value_(value) {}
private:
  bitvector value_;
};

template <typename T>
class nodebuf {
public:

  struct slice_t {
    T src;
    uint32_t offset;
    uint32_t length;
  };

  nodebuf(uint32_t capacity)
    : capacity_(capacity)
    , size_(0)
  {}

  nodebuf(uint32_t capacity, T src, uint32_t offset, uint32_t length)
    : capacity_(capacity)
    , size_(length) {
    slices_.push_back({src, offset, length});
  }

  uint32_t get_capacity() const {
    return capacity_;
  }

  uint32_t get_size() const {
    return size_;
  }

  uint32_t get_num_slices() const {
    return slices_.size();
  }

  bool is_srccopy() const {
    return (1 == slices_.size()) && (slices_[0].src.get_size() == size_);
  }

  void push_back(const slice_t& data) {
    slices_.emplace_back(data);
    size_ += data.length;
    assert(size_ <= capacity_);
  }

  auto begin() const {
    assert(size_ == capacity_);
    return slices_.begin();
  }

  auto end() const {
    return slices_.end();
  }

private:

  std::vector<slice_t> slices_;
  uint32_t capacity_;    
  uint32_t size_;
};

template <typename T>
class typebase_itf {
public:
  virtual void read_data(T& inout, size_t offset, size_t length) const = 0;
  virtual void write_data(size_t dst_offset, const T& in, size_t src_offset, size_t length) = 0;
};

template <unsigned N, typename T> class typebase;

template <typename T>
void read_data(const T& node, typename T::data_type& inout, size_t offset, size_t length) {
  reinterpret_cast<const typebase<T::bitcount, typename T::data_type>&>(node).read_data(inout, offset, length);
}

template <typename T>
void write_data(T& node, size_t dst_offset, const typename T::data_type& in, size_t src_offset, size_t length) {
  reinterpret_cast<typebase<T::bitcount,typename T::data_type>&>(node).write_data(dst_offset, in, src_offset, length);
}

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N>
class sliceref : public typebase<N, typename T::data_type> {
public:
  static_assert(N <= T::bitcount, "invalid slice size");
  using base = typebase<N, typename T::data_type>;
  using base::operator=;
  using data_type = typename base::data_type;
  using container_type = T;

  sliceref(T& container, size_t start = 0)
    : container_(container)
    , start_(start) {
    CH_CHECK(start + N <= T::bitcount, "invalid slice range");
  }

  auto operator[](size_t index) const {
    return sliceref<base, 1>(const_cast<sliceref&>(*this), index);
  }

  template <unsigned M>
  auto slice(size_t index = 0) const {
    return sliceref<base, M>(const_cast<sliceref&>(*this), index);
  }

  template <unsigned M>
  auto aslice(size_t index = 0) const {
    return sliceref<base, M>(const_cast<sliceref&>(*this), index * M);
  }

  sliceref& operator=(const sliceref& rhs) {
    data_type data(N);
    rhs.read_data(data, 0, N);
    this->write_data(0, data, 0, N);
    return *this;
  }

protected:

  sliceref(sliceref&&) = default;
  sliceref& operator=(sliceref&&) = default;

  void read_data(data_type& inout, size_t offset, size_t length) const override {
    CH_CHECK(offset + length <= N, "invalid read range");
    cash::internal::read_data(container_, inout, start_ + offset, length);
  }

  void write_data(size_t dst_offset, const data_type& in, size_t src_offset, size_t length) override {
    CH_CHECK(dst_offset + length <= N, "invalid write range");
    cash::internal::write_data(container_, start_ + dst_offset, in, src_offset, length);
  }

  T& container_;
  size_t start_;

  template <unsigned M, typename Q> friend class typebase;
  template <typename Q, unsigned M> friend class sliceref;
};

///////////////////////////////////////////////////////////////////////////////

template <typename... Args>
struct concat_info;

template <typename Arg>
struct concat_info<Arg> {
  const static unsigned bitcount = Arg::bitcount;
  using data_type = typename Arg::data_type;
};

template <typename Arg0, typename... Args>
struct concat_info<Arg0, Args...> {
    const static unsigned bitcount = Arg0::bitcount + concat_info<Args...>::bitcount;
    using data_type = typename Arg0::data_type;
};

template<typename... Args>
class concatref : protected typebase<concat_info<Args...>::bitcount, typename concat_info<Args...>::data_type> {
public:
  using base = typebase<concat_info<Args...>::bitcount, typename concat_info<Args...>::data_type>;
  using base::operator=;
  using data_type = typename base::data_type;

  concatref(Args&... args) : args_(args...) {}

  concatref& operator=(const concatref& rhs) {
    data_type data(base::bitcount);
    rhs.read_data(data, 0, base::bitcount);
    this->write_data(0, data, 0, base::bitcount);
    return *this;
  }

protected:

  concatref(concatref&&) = default;
  concatref& operator=(concatref&&) = default;

  void read_data(data_type& inout, size_t offset, size_t length) const override {
    CH_CHECK(offset + length <= base::bitcount, "invalid read range");
    this->read_data(inout, offset, length, args_, std::index_sequence_for<Args...>());
  }

  void write_data(size_t dst_offset, const data_type& in, size_t src_offset, size_t length) override {
    CH_CHECK(dst_offset + length <= base::bitcount, "invalid write range");
    this->write_data(dst_offset, in, src_offset, length, args_, std::index_sequence_for<Args...>());
  }

  template <size_t ...I>
  void read_data(data_type& inout, size_t offset, size_t length, const std::tuple<Args&...>& args, std::index_sequence<I...>) const {
    this->read_data(inout, offset, length, std::get<sizeof...(Args) - 1 - I>(args)...);
  }

  template <size_t ...I>
  void write_data(size_t dst_offset, const data_type& in, size_t src_offset, size_t length, std::tuple<Args&...>& args, std::index_sequence<I...>) {
    this->write_data(dst_offset, in, src_offset, length, std::get<sizeof...(Args) - 1 - I>(args)...);
  }

  template <typename T0, typename... Ts>
  void read_data(data_type& inout, size_t offset, size_t length, T0& arg0, Ts&... args) const {
    if (offset < T0::bitcount) {
      size_t len = std::min<size_t>(length, T0::bitcount);
      cash::internal::read_data(arg0, inout, offset, len);
      offset += len;
      length -= len;
    }
    if (length > 0) {
      this->read_data(inout, offset - T0::bitcount, length, args...);
    }
  }

  template <typename T>
  void read_data(data_type& inout, size_t offset, size_t length, T& arg) const {
    size_t len = std::min<size_t>(length, T::bitcount);
    cash::internal::read_data(arg, inout, offset, len);
  }

  template <typename T0, typename... Ts>
  void write_data(size_t dst_offset, const data_type& in, size_t src_offset, size_t length, T0& arg0, Ts&... args) {
    if (dst_offset < T0::bitcount) {
      size_t len = std::min<size_t>(length, T0::bitcount);
      cash::internal::write_data(arg0, dst_offset, in, src_offset, len);
      dst_offset += len;
      src_offset += len;
      length -= len;
    }
    if (length > 0) {
      this->write_data(dst_offset - T0::bitcount, in, src_offset, length, args...);
    }
  }

  template <typename T>
  void write_data(size_t dst_offset, const data_type& in, size_t src_offset, size_t length, T& arg) {
    size_t len = std::min<size_t>(length, T::bitcount);
    cash::internal::write_data(arg, dst_offset, in, src_offset, len);
  }

  std::tuple<Args&...> args_;

  template <unsigned M, typename Q> friend class typebase;
  template<typename... Args2> friend concatref<Args2...> ch_tie(Args2&... args);
};

}
}
