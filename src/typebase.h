#pragma once

#include "common.h"
#include "bitvector.h"

namespace cash {
namespace internal {

template <typename T>
struct data_traits;

template <typename T>
struct traits {
  static constexpr unsigned bitcount = 0;
};

template <typename T>
struct is_scalar : std::false_type {};

#define CH_DEF_SCALAR(scalar) \
  template <> struct is_scalar<scalar> : std::true_type {};
CH_DEF_SCALAR(bool)
CH_DEF_SCALAR(char)
CH_DEF_SCALAR(int8_t)
CH_DEF_SCALAR(uint8_t)
CH_DEF_SCALAR(int16_t)
CH_DEF_SCALAR(uint16_t)
CH_DEF_SCALAR(int32_t)
CH_DEF_SCALAR(uint32_t)
CH_DEF_SCALAR(int64_t)
CH_DEF_SCALAR(uint64_t)
#undef CH_DEF_SCALAR_TRAITS

///////////////////////////////////////////////////////////////////////////////

struct empty_type {};

template <typename T0, typename T1>
struct deduce_type_helper2 {
  using D0 = typename std::decay<T0>::type;
  using D1 = typename std::decay<T1>::type;
  using type = typename std::conditional<
    (traits<D0>::bitcount != 0) && (traits<D1>::bitcount != 0),
    typename std::conditional<(traits<D0>::bitcount != traits<D1>::bitcount), empty_type, D0>::type,
    typename std::conditional<(traits<D0>::bitcount != 0), D0, D1>::type>::type;
};

template <typename T0, typename... Ts>
struct deduce_type_helper;

template <typename T0, typename T1>
struct deduce_type_helper<T0, T1> {
  using type = typename deduce_type_helper2<T0, T1>::type;
};

template <typename T0, typename T1, typename... Ts>
struct deduce_type_helper<T0, T1, Ts...> {
  using type = typename deduce_type_helper<typename deduce_type_helper2<T0, T1>::type, Ts...>::type;
};

template <typename T0, typename T1, typename... Ts>
struct deduce_type {
  using type = typename deduce_type_helper<T0, T1, Ts...>::type;
  static constexpr unsigned bitcount = traits<type>::bitcount;
};

template <typename T0, typename T1>
struct deduce_first_type {
  using D0 = typename std::decay<T0>::type;
  using D1 = typename std::decay<T1>::type;
  using type = typename std::conditional<(traits<D0>::bitcount != 0), D0, D1>::type;
  static constexpr unsigned bitcount = traits<type>::bitcount;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class nodelist {
public:
  using value_type = T;

  nodelist(uint32_t capacity) : capacity_(capacity), size_(0) {}

  nodelist(uint32_t capacity, const T& src, uint32_t offset, uint32_t length)
    : nodelist(capacity) {
    this->push(src, offset, length);
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

  void push(const T& src, uint32_t offset, uint32_t length) {
    slices_.emplace_back(slice_t{src, offset, length});
    size_ += length;
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

  struct slice_t {
    const T& src;
    uint32_t offset;
    uint32_t length;
  };

  std::vector<slice_t> slices_;
  uint32_t capacity_;    
  uint32_t size_;
};

///////////////////////////////////////////////////////////////////////////////

template <typename Derived>
class typebase;

template <typename Derived>
void read_data(const typebase<Derived>& node,
               nodelist<typename traits<Derived>::data_type>& inout,
               size_t offset,
               size_t length);

template <typename Derived>
void write_data(typebase<Derived>& node,
                size_t dst_offset,
                const nodelist<typename traits<Derived>::data_type>& in,
                size_t src_offset,
                size_t length);

template <typename Derived>
class typebase {
public:
  using data_type = typename traits<Derived>::data_type;

  const Derived* self() const {
    return static_cast<const Derived*>(this);
  }

  Derived* self() {
    return static_cast<Derived*>(this);
  }

protected:

  template <typename OtherDerived,
            CH_REQUIRES(traits<OtherDerived>::bitcount == traits<Derived>::bitcount)>
  Derived& assign(const typebase<OtherDerived>& rhs) {
    auto N = traits<Derived>::bitcount;
    nodelist<data_type> data(N);
    cash::internal::read_data(rhs, data, 0, N);
    self()->write_data(0, data, 0, N);
    return *self();
  }

  template <typename T,
            CH_REQUIRES(is_scalar<T>::value)>
  Derived& assign(const T& rhs) { \
    auto N = traits<Derived>::bitcount;
    data_type node(bitvector(N, rhs)); \
    self()->write_data(0, {N, node, 0 , N}, 0, N); \
    return *self(); \
  }

  void read_data(nodelist<data_type>& inout, size_t offset, size_t length) const {
    self()->read_data(inout, offset, length);
  }

  void write_data(size_t dst_offset, const nodelist<data_type>& in, size_t src_offset, size_t length) {
    self()->write_data(dst_offset, in, src_offset, length);
  }

  template <typename T> friend void read_data(const typebase<T>& node,
                                              nodelist<typename traits<T>::data_type>& inout,
                                              size_t offset,
                                              size_t length);

  template <typename T> friend void write_data(typebase<T>& node,
                                               size_t dst_offset,
                                               const nodelist<typename traits<T>::data_type>& in,
                                               size_t src_offset,
                                               size_t length);
};

template <typename Derived>
void read_data(const typebase<Derived>& node,
               nodelist<typename traits<Derived>::data_type>& inout,
               size_t offset,
               size_t length) {
  node.read_data(inout, offset, length);
}

template <typename Derived>
void write_data(typebase<Derived>& node,
                size_t dst_offset,
                const nodelist<typename traits<Derived>::data_type>& in,
                size_t src_offset,
                size_t length) {
  node.write_data(dst_offset, in, src_offset, length);
}

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N>
class const_sliceref;

template <typename T, unsigned N>
struct traits < const_sliceref<T, N> > {
  static constexpr unsigned bitcount = N;
  static constexpr bool readonly = true;
  using data_type  = typename traits<T>::data_type;
};

template <typename T, unsigned N>
class const_sliceref : public data_traits< typename traits<T>::data_type >:: template base_type< const_sliceref<T, N> > {
public:
  static_assert(N <= traits<T>::bitcount, "invalid slice size");  
  using data_type = typename traits<T>::data_type;
  template <typename U> using base_type = typename data_traits<data_type>:: template base_type<U>;

  const_sliceref(const T&& container, size_t start = 0)
    : container_(std::move(const_cast<T&&>(container)))
    , start_(start) {
    CH_CHECK(start + N <= traits<T>::bitcount, "invalid slice range");
  }

  template <typename U>
  const_sliceref(const base_type<U>& container, size_t start = 0) {
    CH_CHECK(start + N <= traits<T>::bitcount, "invalid slice range");
    nodelist<data_type> data(N);
    cash::internal::read_data(container, data, start, N);
    container_ = std::move(data_traits<data_type>:: template make_type<T>(data));
    start_ = 0;
  }

  const auto operator[](size_t index) & {
    return const_sliceref<T, 1>(std::move(container_), start_ + index);
  }

  const auto operator[](size_t index) const & {
    return const_sliceref<T, 1>(std::move(container_), start_ + index);
  }

  const auto operator[](size_t index) const && {
    return const_sliceref<T, 1>(std::move(container_), start_ + index);
  }

  template <unsigned M>
  const auto slice(size_t index = 0) & {
    return const_sliceref<T, M>(std::move(container_), start_ + index);
  }

  template <unsigned M>
  const auto slice(size_t index = 0) const & {
    return const_sliceref<T, M>(std::move(container_), start_ + index);
  }

  template <unsigned M>
  const auto slice(size_t index = 0) const && {
    return const_sliceref<T, M>(std::move(container_), start_ + index);
  }

  template <unsigned M>
  const auto aslice(size_t index = 0) & {
    return const_sliceref<T, M>(std::move(container_), start_ + index * M);
  }

  template <unsigned M>
  const auto aslice(size_t index = 0) const & {
    return const_sliceref<T, M>(std::move(container_), start_ + index * M);
  }

  template <unsigned M>
  const auto aslice(size_t index = 0) const && {
    return const_sliceref<T, M>(std::move(container_), start_ + index * M);
  }

protected:

  void read_data(nodelist<data_type>& inout, size_t offset, size_t length) const {
    CH_CHECK(offset + length <= N, "invalid read range");
    cash::internal::read_data(container_, inout, start_ + offset, length);
  }

  void write_data(size_t dst_offset, const nodelist<data_type>& in, size_t src_offset, size_t length) {
    CH_CHECK(dst_offset + length <= N, "invalid write range");
    cash::internal::write_data(container_, start_ + dst_offset, in, src_offset, length);
  }

  T container_;
  size_t start_;

  template <typename U> friend class typebase;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N>
class sliceref;

template <typename T, unsigned N>
struct traits < sliceref<T, N> > {
  static constexpr unsigned bitcount = N;
  static constexpr bool readonly = false;
  using data_type  = typename traits<T>::data_type;
};

template <typename T, unsigned N>
class sliceref : public data_traits< typename traits<T>::data_type >:: template base_type< sliceref<T, N> > {
public:
  static_assert(N <= traits<T>::bitcount, "invalid slice size");
  using base = typename data_traits< typename traits<T>::data_type >:: template base_type< sliceref<T, N> >;
  using base::operator=;
  using data_type = typename traits<T>::data_type;

  sliceref(const T& container, size_t start = 0)
    : container_(const_cast<T&>(container))
    , start_(start) {
    CH_CHECK(start + N <= traits<T>::bitcount, "invalid slice range");
  }

  const auto operator[](size_t index) const {
    return sliceref<T, 1>(container_, start_ + index);
  }

  auto operator[](size_t index) {
    return sliceref<T, 1>(container_, start_ + index);
  }

  template <unsigned M>
  const auto slice(size_t index = 0) const {
    return sliceref<T, M>(container_, start_ + index);
  }

  template <unsigned M>
  auto slice(size_t index = 0) {
    return sliceref<T, M>(container_, start_ + index);
  }

  template <unsigned M>
  const auto aslice(size_t index = 0) const {
    return sliceref<T, M>(container_, start_ + index * M);
  }

  template <unsigned M>
  auto aslice(size_t index = 0) {
    return sliceref<T, M>(container_, start_ + index * M);
  }

protected:

  void read_data(nodelist<data_type>& inout, size_t offset, size_t length) const {
    CH_CHECK(offset + length <= N, "invalid read range");
    cash::internal::read_data(container_, inout, start_ + offset, length);
  }

  void write_data(size_t dst_offset, const nodelist<data_type>& in, size_t src_offset, size_t length) {
    CH_CHECK(dst_offset + length <= N, "invalid write range");
    cash::internal::write_data(container_, start_ + dst_offset, in, src_offset, length);
  }

  T& container_;
  size_t start_;

  template <typename U> friend class typebase;
};

///////////////////////////////////////////////////////////////////////////////

template <typename... Ts>
struct concat_info;

template <typename T>
struct concat_info<T> {
  static constexpr unsigned bitcount = traits<T>::bitcount;
  using data_type = typename traits<T>::data_type;
};

template <typename T0, typename... Ts>
struct concat_info<T0, Ts...> {
    static constexpr unsigned bitcount = traits<T0>::bitcount + concat_info<Ts...>::bitcount;
    using data_type = typename traits<T0>::data_type;
};

template <typename... Ts>
class concatref;

template <typename... Ts>
struct traits < concatref<Ts...> > {
  static constexpr unsigned bitcount = concat_info<Ts...>::bitcount;
  static constexpr bool readonly = false;
  using data_type = typename concat_info<Ts...>::data_type;
};

template <typename... Ts>
class concatref : public data_traits< typename concat_info<Ts...>::data_type >:: template base_type< concatref<Ts...> > {
public:
  using base = typename data_traits< typename concat_info<Ts...>::data_type >:: template base_type< concatref<Ts...> >;
  using base::operator=;
  using data_type = typename base::data_type;

  concatref(Ts&... args) : args_(args...) {}

protected:

  concatref(concatref&&) = default;
  concatref& operator=(concatref&&) = default;

  void read_data(nodelist<data_type>& inout, size_t offset, size_t length) const {
    CH_CHECK(offset + length <= concat_info<Ts...>::bitcount, "invalid read range");
    this->read_data(inout, offset, length, args_, std::index_sequence_for<Ts...>());
  }

  void write_data(size_t dst_offset, const nodelist<data_type>& in, size_t src_offset, size_t length) {
    CH_CHECK(dst_offset + length <= concat_info<Ts...>::bitcount, "invalid write range");
    this->write_data(dst_offset, in, src_offset, length, args_, std::index_sequence_for<Ts...>());
  }

  template <size_t... I>
  void read_data(nodelist<data_type>& inout, size_t offset, size_t length, const std::tuple<Ts&...>& args, std::index_sequence<I...>) const {
    this->read_data(inout, offset, length, std::get<sizeof...(Ts) - 1 - I>(args)...);
  }

  template <size_t... I>
  void write_data(size_t dst_offset, const nodelist<data_type>& in, size_t src_offset, size_t length, std::tuple<Ts&...>& args, std::index_sequence<I...>) {
    this->write_data(dst_offset, in, src_offset, length, std::get<sizeof...(Ts) - 1 - I>(args)...);
  }

  template <typename U>
  void read_data(nodelist<data_type>& inout, size_t offset, size_t length, U& arg) const {
    size_t len = std::min<size_t>(length, U::bitcount);
    cash::internal::read_data(arg, inout, offset, len);
  }

  template <typename U0, typename... Us>
  void read_data(nodelist<data_type>& inout, size_t offset, size_t length, U0& arg0, Us&... args) const {
    if (offset < traits<U0>::bitcount) {
      size_t len = std::min<size_t>(length, traits<U0>::bitcount);
      cash::internal::read_data(arg0, inout, offset, len);
      offset += len;
      length -= len;
    }
    if (length > 0) {
      this->read_data(inout, offset - traits<U0>::bitcount, length, args...);
    }
  }

  template <typename U>
  void write_data(size_t dst_offset, const nodelist<data_type>& in, size_t src_offset, size_t length, U& arg) {
    size_t len = std::min<size_t>(length, traits<U>::bitcount);
    cash::internal::write_data(arg, dst_offset, in, src_offset, len);
  }

  template <typename U0, typename... Us>
  void write_data(size_t dst_offset, const nodelist<data_type>& in, size_t src_offset, size_t length, U0& arg0, Us&... args) {
    if (dst_offset < traits<U0>::bitcount) {
      size_t len = std::min<size_t>(length, traits<U0>::bitcount);
      cash::internal::write_data(arg0, dst_offset, in, src_offset, len);
      dst_offset += len;
      src_offset += len;
      length -= len;
    }
    if (length > 0) {
      this->write_data(dst_offset - traits<U0>::bitcount, in, src_offset, length, args...);
    }
  }

  std::tuple<Ts&...> args_;

  template <typename... Ts2, typename> friend concatref<Ts2...> ch_tie(Ts2&... args);
  template <typename U> friend class typebase;
};

}
}
