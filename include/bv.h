#pragma once

#include "common.h"

namespace ch {
namespace internal {

template <typename T>
void bv_clear_extra_bits(T* in, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;
  static constexpr uint32_t WORD_MASK = WORD_SIZE - 1;
  static constexpr T        WORD_MAX  = std::numeric_limits<T>::max();

  uint32_t extra_bits = size & WORD_MASK;
  if (extra_bits) {
    in[size / WORD_SIZE] &= ~(WORD_MAX << extra_bits);
  }
}

template <typename U, typename T,
          CH_REQUIRE_0(std::is_integral_v<U>)>
void bv_assign_scalar(T* in, U value) {
  in[0] = value;
}

template <typename U, typename T,
          CH_REQUIRE_0(std::is_integral_v<U> && std::is_unsigned_v<U>)>
void bv_assign_vector(T* in, uint32_t size, U value) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  uint32_t num_words = ceildiv(size, WORD_SIZE);
  if constexpr (bitwidth_v<U> <= WORD_SIZE) {
    in[0] = value;
    std::fill_n(in + 1, num_words - 1, 0);
  } else {
    if (0 == value) {
      std::fill_n(in, num_words, 0);
      return;
    }
    auto len = std::min<uint32_t>(num_words, bitwidth_v<U> / WORD_SIZE);
    std::copy_n(reinterpret_cast<const T*>(&value), len, in);
    std::fill_n(in + len, num_words - len, 0);
  }
}

template <typename U, typename T,
          CH_REQUIRE_0(std::is_integral_v<U> && std::is_signed_v<U>)>
void bv_assign_vector(T* in, uint32_t size, U value) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;
  static constexpr T        WORD_MAX  = std::numeric_limits<T>::max();

  uint32_t num_words = ceildiv(size, WORD_SIZE);
  T ext_value  = ((value >= 0) ? 0 : WORD_MAX);
  if constexpr (bitwidth_v<U> <= WORD_SIZE) {
    in[0] = value;
    std::fill_n(in + 1, num_words - 1, ext_value);
  } else {
    auto len = std::min<uint32_t>(num_words, bitwidth_v<U> / WORD_SIZE);
    std::copy_n(reinterpret_cast<const T*>(&value), len, in);
    std::fill_n(in + len, num_words - len, ext_value);
  }
}

template <typename U, typename T,
          CH_REQUIRE_0(std::is_integral_v<U> && std::is_unsigned_v<U>)>
void bv_assign(T* in, uint32_t size, U value) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;
  if constexpr (std::numeric_limits<U>::digits > 1) {
    CH_CHECK(log2ceil(value + 1) <= size, "value out of range");
  }
  if (size <= WORD_SIZE) {
    bv_assign_scalar(in, value);
  } else {
    bv_assign_vector(in, size, value);
  }
}

template <typename U, typename T,
          CH_REQUIRE_0(std::is_integral_v<U> && std::is_signed_v<U>)>
void bv_assign(T* in, uint32_t size, U value) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;
  static_assert(std::numeric_limits<U>::digits > 1, "inavlid size");

  if (value >= 0) {
    auto u_value = std::make_unsigned_t<U>(value);
    if constexpr (std::numeric_limits<U>::digits > 1) {
      CH_CHECK(log2ceil(u_value + 1) <= size, "value out of range");
    }
    if (size <= WORD_SIZE) {
      bv_assign_scalar(in, u_value);
    } else {
      bv_assign_vector(in, size, u_value);
    }
  } else {
    CH_CHECK(1 + log2ceil(~value + 1) <= size, "value out of range");
    if (size <= WORD_SIZE) {
      bv_assign_scalar(in, value);
    } else {
      bv_assign_vector(in, size, value);
    }
    bv_clear_extra_bits(in, size);
  }
}

inline int get_string_base(const char* value, int len) {
  int base = 0;
  switch (value[len-1]) {
  case 'b':
    base = 2;
    break;
  case 'o':
    base = 8;
    break;
  case 'h':
    base = 16;
    break;
  default:
    CH_ABORT("invalid binary format, missing encoding base type.");
  }
  return base;
}

inline int get_string_size(const char* value, int log_base, int len) {
  int size = 0;
  for (const char *cur = value, *end = value + len; cur < end;) {
    char chr = *cur++;
    if (chr == '\'')
      continue; // skip separator character
    if (0 == size) {
       // calculate exact bit coverage for the first non zero character
       int v = char2int(chr, (1 << log_base));
       if (v) {
         size += log2ceil(v+1);
       }
    } else {
      size += log_base;
    }
  }
  return size;
}

template <typename T>
void bv_assign(T* in, uint32_t size, const std::string& value) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  size_t len = value.length();
  CH_CHECK(len >= 3, "invalid string format");

  const char* buf = value.c_str();
  int base = get_string_base(buf, len);

  len -= 2; // remove base postfix
  if (16 == base && value[0] == '0' && len > 1 && value[1] == 'x') {
    buf += 2; // remove hex prefix
    len -= 2;
  }

  uint32_t log_base = log2ceil(base);

  uint32_t str_size = get_string_size(buf, log_base, len);
  CH_CHECK(str_size >= 0, "invalid string size");
  CH_CHECK(size >= str_size, "value out of range");

  // clear remaining words
  uint32_t num_words = ceildiv(size, WORD_SIZE);
  uint32_t src_num_words = ceildiv(str_size, WORD_SIZE);
  if (src_num_words < num_words) {
    std::fill_n(in + src_num_words, num_words - src_num_words, 0x0);
  }

  // write the value
  T w(0);
  T* dst = in;
  for (int32_t i = len - 1, j = 0; i >= 0; --i) {
    char chr = buf[i];
    if (chr == '\'')
      continue; // skip separator character
    T v = char2int(chr, base);
    w |= v << j;
    j += log_base;
    if (j >= int32_t(WORD_SIZE)) {
      *dst++ = w;
      j -= WORD_SIZE;
      w = v >> (log_base - j);
    }
  }

  if (w) {
    *dst = w;
  }
}

template <typename T>
bool bv_is_neg(const T* in, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;
  static constexpr uint32_t WORD_MASK = WORD_SIZE - 1;

  uint32_t index = (size - 1);
  uint32_t widx = index / WORD_SIZE;
  uint32_t wbit = index & WORD_MASK;
  auto mask = T(1) << wbit;
  return (in[widx] & mask) != 0;
}

template <typename T>
int bv_lsb_scalar(const T* in) {
  auto w = in[0];
  if (w) {
    return count_trailing_zeros<T>(w);
  }
  return -1;
}

template <typename T>
int bv_lsb_vector(const T* in, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  uint32_t num_words = ceildiv(size, WORD_SIZE);
  for (uint32_t i = 0; i < num_words; ++i) {
    auto w = in[i];
    if (w) {
      int z = count_trailing_zeros<T>(w);
      return z + i * WORD_SIZE;
    }
  }
  return -1;
}

template <typename T>
int bv_lsb(const T* in, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  if (size <= WORD_SIZE) {
    return bv_lsb_scalar(in);
  } else {
    return bv_lsb_vector(in, size);
  }
}

template <typename T>
int bv_msb_scalar(const T* in) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  auto w = in[0];
  if (w) {
    int z = count_leading_zeros<T>(w);
    return (WORD_SIZE - z);
  }
  return -1;
}

template <typename T>
int bv_msb_vector(const T* in, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  uint32_t num_words = ceildiv(size, WORD_SIZE);
  for (int32_t i = num_words - 1; i >= 0; --i) {
    auto w = in[i];
    if (w) {
      int z = count_leading_zeros<T>(w);
      return (WORD_SIZE - z) + i * WORD_SIZE;
    }
  }
  return -1;
}

template <typename T>
int bv_msb(const T* in, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  if (size <= WORD_SIZE) {
    return bv_msb_scalar(in);
  } else {
    return bv_msb_vector(in, size);
  }
}

template <typename U, typename T>
U bv_cast(const T* in, uint32_t size) {
  static_assert(std::is_integral_v<T>, "invalid type");
  CH_CHECK(bitwidth_v<U> >= size, "invalid size");
  if constexpr (bitwidth_v<U> <= bitwidth_v<T>) {
    CH_UNUSED(size);
    return bit_cast<U>(in[0]);
  } else {
    U ret(0);
    memcpy(&ret, in, ceildiv<uint32_t>(size, 8));
    return ret;
  }
}

template <typename T>
void bv_copy(T* out, const T* in, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  if (size <= WORD_SIZE) {
    out[0] = in[0];
  } else {
    uint32_t num_words = ceildiv(size, WORD_SIZE);
    std::copy_n(in, num_words, out);
  }
}

template <typename T>
void bv_copy_scalar(T* w_dst, uint32_t w_dst_begin_rem,
                    const T* w_src, uint32_t w_src_begin_rem,
                    uint32_t length) {
  static unsigned constexpr WORD_SIZE = bitwidth_v<T>;
  static constexpr T        WORD_MAX  = std::numeric_limits<T>::max();

  T src_block = (w_src[0] >> w_src_begin_rem) << w_dst_begin_rem;
  T mask = (WORD_MAX >> (WORD_SIZE - length)) << w_dst_begin_rem;
  w_dst[0] = blend<T>(mask, w_dst[0], src_block);
}

template <typename T>
void bv_copy_vector_small(T* w_dst, uint32_t w_dst_begin_rem,
                          const T* w_src, uint32_t w_src_begin_rem,
                          uint32_t length) {
  static unsigned constexpr WORD_SIZE = bitwidth_v<T>;
  static constexpr unsigned WORD_MASK = WORD_SIZE - 1;
  static constexpr T        WORD_MAX  = std::numeric_limits<T>::max();

  uint32_t dst_end       = w_dst_begin_rem + length - 1;
  uint32_t w_dst_end_rem = dst_end & WORD_MASK;

  T src_block = w_src[0] >> w_src_begin_rem;
  if (w_src_begin_rem + length > WORD_SIZE) {
    src_block |= (w_src[1] << (WORD_SIZE - w_src_begin_rem));
  }
  T mask = (WORD_MAX >> (WORD_SIZE - length)) << w_dst_begin_rem;
  w_dst[0] = blend<T>(mask, w_dst[0], (src_block << w_dst_begin_rem));
  if (w_dst_begin_rem + length > WORD_SIZE) {
    src_block >>= (WORD_SIZE - w_dst_begin_rem);
    mask = (WORD_MAX << 1) << w_dst_end_rem;
    w_dst[1] = blend<T>(mask, src_block, w_dst[1]);
  }
}

template <typename T>
void bv_copy_vector_aligned(T* w_dst, uint32_t w_dst_begin_rem,
                            const T* w_src, uint32_t length) {
  static unsigned constexpr WORD_SIZE = bitwidth_v<T>;
  static constexpr unsigned WORD_MASK = WORD_SIZE - 1;
  static constexpr T        WORD_MAX  = std::numeric_limits<T>::max();

  uint32_t dst_end       = w_dst_begin_rem + length - 1;
  uint32_t w_dst_end_idx = (dst_end / WORD_SIZE);
  uint32_t w_dst_end_rem = dst_end & WORD_MASK;

  // update aligned blocks
  if (WORD_MASK == w_dst_end_rem) {
    std::copy_n(w_src, w_dst_end_idx + 1, w_dst);
  } else {
    std::copy_n(w_src, w_dst_end_idx, w_dst);
    // update remining block
    T src_block = w_src[w_dst_end_idx];
    T mask = (WORD_MAX << 1) << w_dst_end_rem;
    w_dst[w_dst_end_idx] = blend<T>(mask, src_block, w_dst[w_dst_end_idx]);
  }
}

template <typename T>
void bv_copy_vector_aligned_dst(T* w_dst, uint32_t w_dst_begin_rem,
                                const T* w_src, uint32_t w_src_begin_rem,
                                uint32_t length) {
  static unsigned constexpr WORD_SIZE = bitwidth_v<T>;
  static constexpr unsigned WORD_MASK = WORD_SIZE - 1;
  static constexpr T        WORD_MAX  = std::numeric_limits<T>::max();

  uint32_t src_end       = w_src_begin_rem + length - 1;
  uint32_t w_src_end_idx = (src_end / WORD_SIZE);
  uint32_t dst_end       = w_dst_begin_rem + length - 1;
  uint32_t w_dst_end_idx = (dst_end / WORD_SIZE);
  uint32_t w_dst_end_rem = dst_end & WORD_MASK;

  // update first block
  T src_block = *w_src++ >> w_src_begin_rem;
  src_block |= w_src[0] << (WORD_SIZE - w_src_begin_rem);
  w_dst[0] = src_block;

  // update intermediate blocks
  auto w_dst_end = (w_dst++) + w_dst_end_idx;
  while (w_dst < w_dst_end) {
    T tmp = *w_src++ >> w_src_begin_rem;
    *w_dst++ = tmp | (w_src[0] << (WORD_SIZE - w_src_begin_rem));
  }

  // update remining blocks
  src_block = w_src[0] >> w_src_begin_rem;
  if (w_src_end_idx > w_dst_end_idx) {
    src_block |= (w_src[1] << (WORD_SIZE - w_src_begin_rem));
  }
  T mask = (WORD_MAX << 1) << w_dst_end_rem;
  w_dst[0] = blend<T>(mask, src_block, w_dst[0]);
}

template <typename T>
void bv_copy_vector_aligned_src(T* w_dst, uint32_t w_dst_begin_rem,
                                const T* w_src, uint32_t w_src_begin_rem,
                                uint32_t length) {
  static unsigned constexpr WORD_SIZE = bitwidth_v<T>;
  static constexpr unsigned WORD_MASK = WORD_SIZE - 1;
  static constexpr T        WORD_MAX  = std::numeric_limits<T>::max();

  uint32_t src_end       = w_src_begin_rem + length - 1;
  uint32_t w_src_end_idx = (src_end / WORD_SIZE);
  uint32_t dst_end       = w_dst_begin_rem + length - 1;
  uint32_t w_dst_end_idx = (dst_end / WORD_SIZE);
  uint32_t w_dst_end_rem = dst_end & WORD_MASK;

  // update first block
  T src_block = *w_src++;
  T mask = WORD_MAX << w_dst_begin_rem;
  w_dst[0] = blend<T>(mask, w_dst[0], (src_block << w_dst_begin_rem));

  // update intermediate blocks
  auto w_dst_end = (w_dst++) + w_src_end_idx;
  while (w_dst < w_dst_end) {
    auto tmp = *w_src++;
    *w_dst++ = (tmp << w_dst_begin_rem) | ((src_block >> 1) >> (WORD_MASK - w_dst_begin_rem));
    src_block = tmp;
  }

  // update remining blocks
  src_block = (w_src[0] << w_dst_begin_rem) | ((src_block >> 1) >> (WORD_MASK - w_dst_begin_rem));
  if (w_src_end_idx < w_dst_end_idx) {
    *w_dst++ = src_block;
    src_block = (w_src[0] >> 1) >> (WORD_MASK - w_dst_begin_rem);
  }
  mask = (WORD_MAX << 1) << w_dst_end_rem;
  w_dst[0] = blend<T>(mask, src_block, w_dst[0]);
}

template <typename T>
void bv_copy_vector_unaligned(T* w_dst, uint32_t w_dst_begin_rem,
                              const T* w_src, uint32_t w_src_begin_rem,
                              uint32_t length) {
  static unsigned constexpr WORD_SIZE = bitwidth_v<T>;
  static constexpr unsigned WORD_MASK = WORD_SIZE - 1;
  static constexpr T        WORD_MAX  = std::numeric_limits<T>::max();

  uint32_t src_end       = w_src_begin_rem + length - 1;
  uint32_t w_src_end_idx = (src_end / WORD_SIZE);
  uint32_t dst_end       = w_dst_begin_rem + length - 1;
  uint32_t w_dst_end_idx = (dst_end / WORD_SIZE);
  uint32_t w_dst_end_rem = dst_end & WORD_MASK;

  // update first block
  T src_block = *w_src++ >> w_src_begin_rem;
  src_block |= (w_src[0] << (WORD_SIZE - w_src_begin_rem));
  T mask = WORD_MAX << w_dst_begin_rem;
  w_dst[0] = blend<T>(mask, w_dst[0], (src_block << w_dst_begin_rem));

  // update intermediate blocks
  auto w_dst_end = (w_dst++) + std::min(w_src_end_idx, w_dst_end_idx);
  while (w_dst < w_dst_end) {
    T tmp = *w_src++ >> w_src_begin_rem;
    tmp |= (w_src[0] << (WORD_SIZE - w_src_begin_rem));
    *w_dst++ = (tmp << w_dst_begin_rem) | ((src_block >> 1) >> (WORD_MASK - w_dst_begin_rem));
    src_block = tmp;
  }

  // update remining blocks
  T tmp = w_src[0] >> w_src_begin_rem;
  if (w_src_end_idx < w_dst_end_idx) {
    src_block = (tmp << w_dst_begin_rem) | ((src_block >> 1) >> (WORD_MASK - w_dst_begin_rem));
    *w_dst++ = src_block;
    src_block = (tmp >> 1) >> (WORD_MASK - w_dst_begin_rem);
  } else
  if (w_src_end_idx == w_dst_end_idx) {
    src_block = (tmp << w_dst_begin_rem) | ((src_block >> 1) >> (WORD_MASK - w_dst_begin_rem));
  } else {
    src_block = (tmp | (w_src[1] << (WORD_SIZE - w_src_begin_rem))) << w_dst_begin_rem;
  }
  mask = (WORD_MAX << 1) << w_dst_end_rem;
  w_dst[0] = blend<T>(mask, src_block, w_dst[0]);
}

template <typename T>
void bv_copy(T* dst, uint32_t dst_offset,
             const T* src, uint32_t src_offset,
             uint32_t length) {
  static unsigned constexpr WORD_SIZE = bitwidth_v<T>;
  static constexpr unsigned WORD_MASK = WORD_SIZE - 1;

  if ((dst_offset + length) <= WORD_SIZE
   && (src_offset + length) <= WORD_SIZE) {
    bv_copy_scalar(dst, dst_offset, src, src_offset, length);
    return;
  }

  uint32_t w_dst_begin_idx = dst_offset / WORD_SIZE;
  uint32_t w_dst_begin_rem = dst_offset & WORD_MASK;
  auto w_dst               = dst + w_dst_begin_idx;
  uint32_t w_src_begin_idx = src_offset / WORD_SIZE;
  uint32_t w_src_begin_rem = src_offset & WORD_MASK;
  auto w_src               = src + w_src_begin_idx;

  if (length <= WORD_SIZE) {
    bv_copy_vector_small(w_dst, w_dst_begin_rem, w_src, w_src_begin_rem, length);
  } else
  if (0 == (w_dst_begin_rem | w_src_begin_rem)) {
    bv_copy_vector_aligned(w_dst, w_dst_begin_rem, w_src, length);
  } else
  if (0 == w_dst_begin_rem) {
    bv_copy_vector_aligned_dst(w_dst, w_dst_begin_rem, w_src, w_src_begin_rem, length);
  } else
  if (0 == w_src_begin_rem) {
    bv_copy_vector_aligned_src(w_dst, w_dst_begin_rem, w_src, w_src_begin_rem, length);
  } else {
    bv_copy_vector_unaligned(w_dst, w_dst_begin_rem, w_src, w_src_begin_rem, length);
  }
}

template <typename T>
void bv_slice_scalar(T* dst, uint32_t dst_size, const T* src, uint32_t src_offset) {
  static unsigned constexpr WORD_SIZE = bitwidth_v<T>;

  T src_block = src[0] >> src_offset;
  uint32_t rem = (WORD_SIZE - dst_size);
  dst[0] = T(src_block << rem) >> rem;
}

template <typename T>
void bv_slice_vector_small(T* dst, uint32_t dst_size, const T* w_src, uint32_t w_src_begin_rem) {
  static unsigned constexpr WORD_SIZE = bitwidth_v<T>;

  T src_block = w_src[0] >> w_src_begin_rem;
  if (w_src_begin_rem + dst_size > WORD_SIZE) {
    src_block |= w_src[1] << (WORD_SIZE - w_src_begin_rem);
  }
  uint32_t rem = (WORD_SIZE - dst_size);
  dst[0] = T(src_block << rem) >> rem;
}

template <typename T>
void bv_slice_vector_aligned(T* dst, uint32_t dst_size, const T* w_src) {
  static unsigned constexpr WORD_SIZE = bitwidth_v<T>;
  static constexpr unsigned WORD_MASK = WORD_SIZE - 1;

  uint32_t dst_end       = dst_size - 1;
  uint32_t w_dst_end_idx = (dst_end / WORD_SIZE);
  uint32_t w_dst_end_rem = dst_end & WORD_MASK;

  // update aligned blocks
  if (WORD_MASK == w_dst_end_rem) {
    std::copy_n(w_src, w_dst_end_idx + 1, dst);
  } else {
    std::copy_n(w_src, w_dst_end_idx, dst);
    // update remining block
    uint32_t rem = (WORD_SIZE - w_dst_end_rem);
    dst[w_dst_end_idx] = T(w_src[w_dst_end_idx] << rem) >> rem;
  }
}

template <typename T>
void bv_slice_vector_unaligned(T* dst, uint32_t dst_size, const T* w_src, uint32_t w_src_begin_rem) {
  static unsigned constexpr WORD_SIZE = bitwidth_v<T>;
  static constexpr unsigned WORD_MASK = WORD_SIZE - 1;

  uint32_t src_end       = w_src_begin_rem + dst_size - 1;
  uint32_t w_src_end_idx = (src_end / WORD_SIZE);
  uint32_t dst_end       = dst_size - 1;
  uint32_t w_dst_end_idx = (dst_end / WORD_SIZE);
  uint32_t w_dst_end_rem = dst_end & WORD_MASK;

  // update first block
  T src_block = *w_src++ >> w_src_begin_rem;
  src_block |= w_src[0] << (WORD_SIZE - w_src_begin_rem);
  dst[0] = src_block;

  // update intermediate blocks
  auto w_dst_end = (dst++) + w_dst_end_idx;
  while (dst < w_dst_end) {
    T tmp = *w_src++ >> w_src_begin_rem;
    *dst++ = tmp | (w_src[0] << (WORD_SIZE - w_src_begin_rem));
  }

  // update remining blocks
  src_block = w_src[0] >> w_src_begin_rem;
  if (w_src_end_idx > w_dst_end_idx) {
    src_block |= w_src[1] << (WORD_SIZE - w_src_begin_rem);
  }
  uint32_t rem = (WORD_SIZE - w_dst_end_rem);
  dst[0] = T(src_block << rem) >> rem;
}

template <typename T>
void bv_slice(T* dst, uint32_t dst_size, const T* src, uint32_t src_offset) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;
  static constexpr unsigned WORD_MASK = WORD_SIZE - 1;

  if (src_offset + dst_size <= WORD_SIZE) {
    bv_slice_scalar(dst, dst_size, src, src_offset);
    return;
  }

  uint32_t w_src_begin_idx = src_offset / WORD_SIZE;
  uint32_t w_src_begin_rem = src_offset & WORD_MASK;
  auto w_src               = src + w_src_begin_idx;

  if (dst_size <= WORD_SIZE) {
    bv_slice_vector_small(dst, dst_size, w_src, w_src_begin_rem);
  } else
  if (0 == w_src_begin_rem) {
    bv_slice_vector_aligned(dst, dst_size, w_src);
  } else {
    bv_slice_vector_unaligned(dst, dst_size, w_src, w_src_begin_rem);
  }
}

template <typename T>
bool bv_eq(const T* lhs, const T* rhs, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;
  uint32_t num_words = ceildiv(size, WORD_SIZE);

  if (lhs[0] != rhs[0])
    return false;

  for (uint32_t i = 1; i < num_words; ++i) {
    if (lhs[i] != rhs[i])
      return false;
  }

  return true;
}

template <typename T>
bool bv_ult(const T* lhs, const T* rhs, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;
  uint32_t num_words = ceildiv(size, WORD_SIZE);

  if (size <= WORD_SIZE)
    return lhs[0] < rhs[0];

  for (int32_t i = num_words - 1; i >= 0; --i) {
    if (lhs[i] < rhs[i])
      return true;
    if (lhs[i] > rhs[i])
      return false;
  }

  return false;
}

template <typename T>
bool bv_slt_scalar(const T* lhs, const T* rhs, uint32_t size) {
  auto u = sign_ext(lhs[0], size);
  auto v = sign_ext(rhs[0], size);
  return u < v;
}

template <typename T>
bool bv_slt_vector(const T* lhs, const T* rhs, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  // compare most signicant bits
  bool lhs_is_neg = bv_is_neg(lhs, size);
  bool rhs_is_neg = bv_is_neg(rhs, size);
  if (lhs_is_neg != rhs_is_neg)
    return lhs_is_neg;

  // same-sign words comparison
  uint32_t num_words = ceildiv(size, WORD_SIZE);
  for (int32_t i = num_words - 1; i >= 0; --i) {
    if (lhs[i] < rhs[i])
      return true;
    if (lhs[i] > rhs[i])
      return false;
  }

  return false;
}

template <typename T>
bool bv_slt(const T* lhs, const T* rhs, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  if (size <= WORD_SIZE) {
    return bv_slt_scalar(lhs, rhs, size);
  } else {
    return bv_slt_vector(lhs, rhs, size);
  }
}

template <typename T>
void bv_inv(T* out, const T* in, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;
  uint32_t num_words = ceildiv(size, WORD_SIZE);

  out[0] = ~in[0];
  for (uint32_t i = 1; i < num_words; ++i) {
    out[i] = ~in[i];
  }

  bv_clear_extra_bits(out, size);
}

template <typename T>
void bv_and(T* out, const T* lhs, const T* rhs, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;
  uint32_t num_words = ceildiv(size, WORD_SIZE);

  out[0] = lhs[0] & rhs[0];
  for (uint32_t i = 1; i < num_words; ++i) {
    out[i] = lhs[i] & rhs[i];
  }
}

template <typename T>
void bv_or(T* out, const T* lhs, const T* rhs, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;
  uint32_t num_words = ceildiv(size, WORD_SIZE);

  out[0] = lhs[0] | rhs[0];
  for (uint32_t i = 1; i < num_words; ++i) {
    out[i] = lhs[i] | rhs[i];
  }
}

template <typename T>
void bv_xor(T* out, const T* lhs, const T* rhs, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;
  uint32_t num_words = ceildiv(size, WORD_SIZE);

  out[0] = lhs[0] ^ rhs[0];
  for (uint32_t i = 1; i < num_words; ++i) {
    out[i] = lhs[i] ^ rhs[i];
  }
}

template <typename T>
bool bv_andr(const T* in, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;
  static constexpr uint32_t WORD_MASK = WORD_SIZE - 1;
  static constexpr T        WORD_MAX  = std::numeric_limits<T>::max();
  uint32_t num_words = ceildiv(size, WORD_SIZE);

  auto rem = size & WORD_MASK;
  auto max = WORD_MAX >> (WORD_SIZE - rem);
  for (int32_t i = num_words - 1; i >= 0; --i) {
    if (in[i] != max)
      return false;
     max = WORD_MAX;
  }
  return true;
}

template <typename T>
bool bv_orr(const T* in, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;
  uint32_t num_words = ceildiv(size, WORD_SIZE);

  if (in[0])
    return true;
  for (uint32_t i = 1; i < num_words; ++i) {
    if (in[i])
      return true;
  }
  return false;
}

template <typename T>
bool bv_xorr(const T* in, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;
  uint32_t num_words = ceildiv(size, WORD_SIZE);

  bool ret = false;
  T tmp = in[0];
  for (uint32_t i = 1; i < num_words; ++i) {
    tmp ^= in[i];
  }
  for (uint32_t i = 0, n = std::min(size, WORD_SIZE); i < n; ++i) {
    ret ^= tmp & 0x1;
    tmp >>= 1;
  }
  return ret;
}

template <typename T>
void bv_sll_scalar(T* out, const T* in, uint32_t dist) {
  out[0] = in[0] << dist;
}

template <typename T>
void bv_sll_vector(T* out, uint32_t out_size,
                   const T* in, uint32_t in_size,
                   uint32_t dist) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;
  static constexpr uint32_t WORD_MASK = WORD_SIZE - 1;

  int32_t in_num_words  = ceildiv(in_size, WORD_SIZE);
  int32_t out_num_words = ceildiv(out_size, WORD_SIZE);

  auto shift_words = std::min<int32_t>(ceildiv(dist, WORD_SIZE), out_num_words);
  uint32_t shift_bits = dist & WORD_MASK;
  int32_t m = in_num_words + shift_words;

  int32_t i = out_num_words - 1;
  for (; i >= m;) {
    out[i--] = 0;
  }

  if (shift_bits) {
    T prev = (out_num_words < m) ? (in[i + 1 - shift_words] << shift_bits) : 0;
    for (; i >= shift_words; --i) {
      auto curr = in[i - shift_words];
      out[i] = (curr >> (WORD_SIZE - shift_bits)) | prev;
      prev = curr << shift_bits;
    }
    for (; i >= 0; --i) {
      out[i] = prev;
      prev = 0;
    }
  } else {
    for (; i >= shift_words; --i) {
      out[i] = in[i - shift_words];
    }
    for (; i >= 0; --i) {
      out[i] = 0;
    }
  }
}

template <typename T>
void bv_sll(T* out, uint32_t out_size,
            const T* in, uint32_t in_size,
            uint32_t dist) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  if (out_size <= WORD_SIZE) {
    bv_sll_scalar(out, in, dist);
  } else {
    bv_sll_vector(out, out_size, in, in_size, dist);
  }
  bv_clear_extra_bits(out, out_size);
}

template <typename T>
void bv_srl_scalar(T* out, const T* in, uint32_t dist) {
  out[0] = in[0] >> dist;
}

template <typename T>
void bv_srl_vector(T* out, uint32_t out_size,
                   const T* in, uint32_t in_size,
                   uint32_t dist) {

  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;
  static constexpr uint32_t WORD_MASK = WORD_SIZE - 1;

  uint32_t in_num_words  = ceildiv(in_size, WORD_SIZE);
  uint32_t out_num_words = ceildiv(out_size, WORD_SIZE);

  uint32_t shift_words = std::min<int32_t>(ceildiv(dist, WORD_SIZE), in_num_words);
  uint32_t rem_words = in_num_words - shift_words;
  uint32_t shift_bits = dist & WORD_MASK;

  uint32_t i = 0;

  if (shift_bits) {
    T prev = in[shift_words-1] >> shift_bits;
    for (; i < rem_words; ++i) {
      auto curr = in[i + shift_words];
      out[i] = (curr << (WORD_SIZE - shift_bits)) | prev;
      prev = curr >> shift_bits;
    }
    for (; i < out_num_words; ++i) {
      out[i] = prev;
      prev = 0;
    }
  } else {
    for (; i < rem_words; ++i) {
      out[i] = in[i + shift_words];
    }
    for (; i < out_num_words; ++i) {
      out[i] = 0;
    }
  }
}

template <typename T>
void bv_srl(T* out, uint32_t out_size,
            const T* in, uint32_t in_size,
            uint32_t dist) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  if (in_size <= WORD_SIZE) {
    bv_srl_scalar(out, in, dist);
  } else {
    bv_srl_vector(out, out_size, in, in_size, dist);
  }
}

template <typename T>
void bv_sra_scalar(T* out, const T* in, uint32_t in_size, uint32_t dist) {
  auto value = sign_ext(in[0], in_size);
  out[0] = value >> dist;
}

template <typename T>
void bv_sra_vector(T* out, uint32_t out_size,
                   const T* in, uint32_t in_size,
                   uint32_t dist) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;
  static constexpr uint32_t WORD_MASK = WORD_SIZE - 1;
  static constexpr T        WORD_MAX  = std::numeric_limits<T>::max();

  uint32_t in_num_words  = ceildiv(in_size, WORD_SIZE);
  uint32_t out_num_words = ceildiv(out_size, WORD_SIZE);

  T ext = bv_is_neg(in, in_size) ? WORD_MAX : 0;
  uint32_t shift_words = std::min<int32_t>(ceildiv(dist, WORD_SIZE), in_num_words);
  uint32_t rem_words = in_num_words - shift_words;
  uint32_t shift_bits = dist & WORD_MASK;

  uint32_t i = 0;

  if (shift_bits) {
    T prev = in[shift_words-1] >> shift_bits;
    for (; i < rem_words; ++i) {
      auto curr = in[i + shift_words];
      out[i] = (curr << (WORD_SIZE - shift_bits)) | prev;
      prev = curr >> shift_bits;
    }
    for (; i < out_num_words; ++i) {
      out[i] = (ext << (WORD_SIZE - shift_bits)) | prev;
      prev = ext;
    }
  } else {
    for (; i < rem_words; ++i) {
      out[i] = in[i + shift_words];
    }
    for (; i < out_num_words; ++i) {
      out[i] = ext;
    }
  }

}

template <typename T>
void bv_sra(T* out, uint32_t out_size,
            const T* in, uint32_t in_size,
            uint32_t dist) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  if (in_size <= WORD_SIZE) {
    bv_sra_scalar(out, in, in_size, dist);
  } else {
    bv_sra_vector(out, out_size, in, in_size, dist);
  }
  bv_clear_extra_bits(out, out_size);
}

template <typename T>
void bv_add_scalar(T* out, const T* lhs, const T* rhs) {
  out[0] = lhs[0] + rhs[0];
}

template <typename T>
void bv_add_vector(T* out, const T* lhs, const T* rhs, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  T carry(0);
  uint32_t num_words = ceildiv(size, WORD_SIZE);
  for (uint32_t i = 0; i < num_words; ++i) {
    auto a = lhs[i];
    auto b = rhs[i];
    T c = a + b;
    T d = c + carry;
    carry = (c < a) || (d < carry);
    out[i] = d;
  }
}

template <typename T>
void bv_add(T* out, const T* lhs, const T* rhs, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  if (size <= WORD_SIZE) {
    bv_add_scalar(out, lhs, rhs);
  } else {
    bv_add_vector(out, lhs, rhs, size);
  }
  bv_clear_extra_bits(out, size);
}

template <typename T>
void bv_sub_scalar(T* out, const T* lhs, const T* rhs) {
  out[0] = lhs[0] - rhs[0];
}

template <typename T>
void bv_sub_vector(T* out, const T* lhs, const T* rhs, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  T borrow(0);
  uint32_t num_words = ceildiv(size, WORD_SIZE);
  for (uint32_t i = 0; i < num_words; ++i) {
    auto a = lhs[i];
    auto b = rhs[i];
    T c = a - b;
    T d = c - borrow;
    borrow = (a < c) || (c < d);
    out[i] = d;
  }
}

template <typename T>
void bv_sub(T* out, const T* lhs, const T* rhs, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  if (size <= WORD_SIZE) {
    bv_sub_scalar(out, lhs, rhs);
  } else {
    bv_sub_vector(out, lhs, rhs, size);
  }
  bv_clear_extra_bits(out, size);
}

template <typename T>
void bv_neg_scalar(T* out, const T* in) {
  out[0] = -in[0];
}

template <typename T>
void bv_neg_vector(T* out, const T* in, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  T borrow(0);
  uint32_t num_words = ceildiv(size, WORD_SIZE);
  for (uint32_t i = 0; i < num_words; ++i) {
    auto a = in[i];
    T b = -a - borrow;
    borrow = (a != 0) || (b != 0);
    out[i] = b;
  }
}

template <typename T>
void bv_neg(T* out, const T* in, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  if (size <= WORD_SIZE) {
    bv_neg_scalar(out, in);
  } else {
    bv_neg_vector(out, in, size);
  }
  bv_clear_extra_bits(out, size);
}

template <typename T>
void bv_abs(T* out, const T* in, uint32_t size) {
  if (bv_is_neg(in, size)) {
    bv_neg(out, in, size);
  } else {
    bv_copy(out, in, size);
  }
}

template <typename T>
void bv_mult_scalar(T* out, const T* lhs, const T* rhs) {
  out[0] = lhs[0] * rhs[0];
}

template <typename T>
void bv_mult_vector(T* out, uint32_t out_size,
                    const T* lhs, uint32_t lhs_size,
                    const T* rhs, uint32_t rhs_size) {
  using xword_t = std::conditional_t<sizeof(T) == 1, uint8_t,
                    std::conditional_t<sizeof(T) == 2, uint16_t, uint32_t>>;
  using yword_t = std::conditional_t<sizeof(T) == 1, uint16_t,
                     std::conditional_t<sizeof(T) == 2, uint32_t, uint64_t>>;
  assert(out_size <= lhs_size + rhs_size);
  static constexpr uint32_t XWORD_SIZE = bitwidth_v<xword_t>;

  auto m = ceildiv<int>(lhs_size, XWORD_SIZE);
  auto n = ceildiv<int>(rhs_size, XWORD_SIZE);
  auto p = ceildiv<int>(out_size, XWORD_SIZE);

  auto u = reinterpret_cast<const xword_t*>(lhs);
  auto v = reinterpret_cast<const xword_t*>(rhs);
  auto w = reinterpret_cast<xword_t*>(out);

  std::fill_n(w, p, 0);

  for (int i = 0; i < n; ++i) {
    xword_t tot(0);
    for (int j = 0, k = std::min(m, p - i); j < k; ++j) {
      auto c = yword_t(u[j]) * v[i] + w[i+j] + tot;
      tot = c >> XWORD_SIZE;
      w[i+j] = c;
    }
    if (i+m < p) {
      w[i+m] = tot;
    }
  }
}

template <typename T>
void bv_mult(T* out, uint32_t out_size,
             const T* lhs, uint32_t lhs_size,
             const T* rhs, uint32_t rhs_size) {
  static constexpr uint32_t WORD_SIZE  = bitwidth_v<T>;

  if (out_size <= WORD_SIZE) {
    assert(lhs_size <= WORD_SIZE);
    assert(rhs_size <= WORD_SIZE);
    bv_mult_scalar(out, lhs, rhs);
  } else {
    bv_mult_vector(out, out_size, lhs, lhs_size, rhs, rhs_size);
  }
  bv_clear_extra_bits(out, out_size);
}

template <typename T>
void bv_udiv_scalar(T* out, const T* lhs, const T* rhs) {
  out[0] = lhs[0] / rhs[0];
}

template <typename T>
void bv_udiv_vector(T* quot, uint32_t quot_size,
                    T* rem, uint32_t rem_size,
                    const T* lhs, uint32_t lhs_size,
                    const T* rhs, uint32_t rhs_size) {
  assert(lhs_size && rhs_size);
  using xword_t = std::conditional_t<sizeof(T) == 1, uint8_t,
                    std::conditional_t<sizeof(T) == 2, uint16_t, uint32_t>>;
  using yword_t = std::conditional_t<sizeof(T) == 1, uint16_t,
                     std::conditional_t<sizeof(T) == 2, uint32_t, uint64_t>>;
  using syword_t = std::make_signed_t<yword_t>;

  static constexpr uint32_t XWORD_SIZE = bitwidth_v<xword_t>;
  static constexpr xword_t  XWORD_MAX  = std::numeric_limits<xword_t>::max();

  auto m  = ceildiv<int>(bv_msb(lhs, lhs_size), XWORD_SIZE);
  auto n  = ceildiv<int>(bv_msb(rhs, rhs_size), XWORD_SIZE);
  auto qn = ceildiv<int>(quot_size, XWORD_SIZE);
  auto rn = ceildiv<int>(rem_size, XWORD_SIZE);

  auto u = reinterpret_cast<const xword_t*>(lhs);
  auto v = reinterpret_cast<const xword_t*>(rhs);
  auto q = reinterpret_cast<xword_t*>(quot);
  auto r = reinterpret_cast<xword_t*>(rem);

  CH_CHECK(n >= 1, "invalid size");

  // reset the outputs
  if (qn) {
    std::fill_n(q, qn, 0);
  }

  if (rn) {
    std::fill_n(r, rn, 0);
  }

  // early exit
  if (m <= 0 || m < n || u[m] < v[n]) {
    if (rn) {
      for (int i = 0; i < std::min(m, rn); ++i) {
        r[i] = u[i];
      }
    }
    return;
  }

  std::vector<xword_t> tu(2 * (m + 1), 0), tv(2 * n, 0);
  auto un = tu.data();
  auto vn = tv.data();

  // normalize
  int s = count_leading_zeros<xword_t>(v[n - 1]);
  un[m] = u[m - 1] >> (XWORD_SIZE - s);
  for (int i = m - 1; i > 0; --i) {
    un[i] = (u[i] << s) | (u[i - 1] >> (XWORD_SIZE - s));
  }
  un[0] = u[0] << s;
  for (int i = n - 1; i > 0; --i) {
    vn[i] = (v[i] << s) | (v[i - 1] >> (XWORD_SIZE - s));
  }
  vn[0] = v[0] << s;

  auto h = vn[n - 1];

  for (int j = m - n; j >= 0; --j) {
    // estimate quotient
    auto w = (yword_t(un[j + n]) << XWORD_SIZE) | un[j + n - 1];
    auto qhat = w / h;

    // multiply and subtract
    xword_t k(0);
    for (int i = 0; i < n; ++i) {
      auto p = qhat * vn[i];
      auto w = un[i + j] - k - (p & XWORD_MAX);
      k = (p >> XWORD_SIZE) - (w >> XWORD_SIZE);
      un[i + j] = w;
    }

    syword_t t(un[j + n] - k);
    un[j + n] = t;

    if (j < qn)
      q[j] = qhat;

    // overflow handling
    if (t < 0) {
      if (j < qn)
        --q[j];
      yword_t k(0);
      for (int i = 0; i < n; ++i) {
        auto w = un[i + j] + k + vn[i];
        k = (w >> XWORD_SIZE);
        un[i + j] = w;
      }
      un[j + n] += k;
    }
  }

  // unnormalize remainder
  if (rn) {
    for (int i = 0; i < std::min(n, rn); ++i) {
      r[i] = (un[i] >> s) | (un[i + 1] << (XWORD_SIZE - s));
    }
  }
}

template <typename T>
void bv_udiv(T* out, uint32_t out_size,
             const T* lhs, uint32_t lhs_size,
             const T* rhs, uint32_t rhs_size) {
  static constexpr uint32_t WORD_SIZE  = bitwidth_v<T>;
  assert(lhs_size && rhs_size && out_size);

  if (lhs_size <= WORD_SIZE
   && rhs_size <= WORD_SIZE
   && out_size <= WORD_SIZE) {
    bv_udiv_scalar(out, lhs, rhs);
  } else {
    T* r = nullptr;
    bv_udiv_vector(out, out_size, r, 0, lhs, lhs_size, rhs, rhs_size);
  }
}

template <typename T>
void bv_sdiv_scalar(T* out, uint32_t out_size,
                    const T* lhs, uint32_t lhs_size,
                    const T* rhs, uint32_t rhs_size) {
  auto u = sign_ext(lhs[0], lhs_size);
  auto v = sign_ext(rhs[0], rhs_size);
  out[0] = u / v;
  bv_clear_extra_bits(out, out_size);
}

template <typename T>
void bv_sdiv(T* out, uint32_t out_size,
             const T* lhs, uint32_t lhs_size,
             const T* rhs, uint32_t rhs_size) {
  static constexpr uint32_t WORD_SIZE  = bitwidth_v<T>;
  assert(lhs_size && rhs_size && out_size);

  if (lhs_size <= WORD_SIZE
   && rhs_size <= WORD_SIZE
   && out_size <= WORD_SIZE) {
    bv_sdiv_scalar(out, out_size, lhs, lhs_size, rhs, rhs_size);
  } else {
    std::vector<T> u(ceildiv<uint32_t>(lhs_size, WORD_SIZE));
    std::vector<T> v(ceildiv<uint32_t>(rhs_size, WORD_SIZE));
    bv_abs(u.data(), lhs, lhs_size);
    bv_abs(v.data(), rhs, rhs_size);
    T* r = nullptr;
    bv_udiv_vector(out, out_size, r, 0, u.data(), lhs_size, v.data(), rhs_size);
    if (bv_is_neg(lhs, lhs_size) ^ bv_is_neg(rhs, rhs_size)) {
      bv_neg(out, out, out_size);
    }
  }
}

template <typename T>
void bv_umod_scalar(T* out, const T* lhs, const T* rhs) {
  out[0] = lhs[0] % rhs[0];
}

template <typename T>
void bv_umod(T* out, uint32_t out_size,
             const T* lhs, uint32_t lhs_size,
             const T* rhs, uint32_t rhs_size) {
  static constexpr uint32_t WORD_SIZE  = bitwidth_v<T>;
  assert(lhs_size && rhs_size && out_size);

  if (lhs_size <= WORD_SIZE
   && rhs_size <= WORD_SIZE
   && out_size <= WORD_SIZE) {
    bv_umod_scalar(out, lhs, rhs);
  } else {
    T* q = nullptr;
    bv_udiv_vector(q, 0, out, out_size, lhs, lhs_size, rhs, rhs_size);
  }
}

template <typename T>
void bv_smod_scalar(T* out, uint32_t out_size,
                    const T* lhs, uint32_t lhs_size,
                    const T* rhs, uint32_t rhs_size) {
  auto u = sign_ext(lhs[0], lhs_size);
  auto v = sign_ext(rhs[0], rhs_size);
  out[0] = u % v;
  bv_clear_extra_bits(out, out_size);
}

template <typename T>
void bv_smod(T* out, uint32_t out_size,
             const T* lhs, uint32_t lhs_size,
             const T* rhs, uint32_t rhs_size) {
  static constexpr uint32_t WORD_SIZE  = bitwidth_v<T>;
  assert(lhs_size && rhs_size && out_size);

  if (lhs_size <= WORD_SIZE
   && rhs_size <= WORD_SIZE
   && out_size <= WORD_SIZE) {
    bv_smod_scalar(out, out_size, lhs, lhs_size, rhs, rhs_size);
  } else {
    std::vector<T> u(ceildiv<uint32_t>(lhs_size, WORD_SIZE));
    std::vector<T> v(ceildiv<uint32_t>(rhs_size, WORD_SIZE));
    bv_abs(u.data(), lhs, lhs_size);
    bv_abs(v.data(), rhs, rhs_size);
    T* q = nullptr;
    bv_udiv_vector(q, 0, out, out_size, u.data(), lhs_size, v.data(), rhs_size);
    if (bv_is_neg(lhs, lhs_size)) {
      bv_neg(out, out, out_size);
    }
  }
}

template <typename T>
void bv_zext_scalar(T* out, const T* in) {
  out[0] = in[0];
}

template <typename T>
void bv_zext_vector(T* out, uint32_t out_size, const T* in, uint32_t in_size) {
  static constexpr uint32_t WORD_SIZE  = bitwidth_v<T>;

  uint32_t in_num_words = ceildiv(in_size, WORD_SIZE);
  uint32_t out_num_words = ceildiv(out_size, WORD_SIZE);

  std::copy_n(in, in_num_words, out);
  std::fill(out + in_num_words, out + out_num_words, 0);
}

template <typename T>
void bv_zext(T* out, uint32_t out_size, const T* in, uint32_t in_size) {
  static constexpr uint32_t WORD_SIZE  = bitwidth_v<T>;
  assert(in_size <= out_size);
  if (out_size <= WORD_SIZE) {
    bv_zext_scalar(out, in);
  } else {
    bv_zext_vector(out, out_size, in , in_size);
  }
}

template <typename T>
void bv_sext_scalar(T* out, uint32_t out_size, const T* in, uint32_t in_size) {
  out[0] = sign_ext(in[0], in_size);
  bv_clear_extra_bits(out, out_size);
}

template <typename T>
void bv_sext_vector(T* out, uint32_t out_size, const T* in, uint32_t in_size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;
  static constexpr uint32_t WORD_MASK = WORD_SIZE - 1;
  static constexpr T        WORD_MAX  = std::numeric_limits<T>::max();

  uint32_t in_num_words = ceildiv(in_size, WORD_SIZE);
  uint32_t out_num_words = ceildiv(out_size, WORD_SIZE);

  auto is_neg = bv_is_neg(in, in_size);
  if (is_neg) {
    uint32_t msb = in_size - 1;
    uint32_t msb_blk_idx = msb / WORD_SIZE;
    uint32_t msb_blk_rem = msb & WORD_MASK;
    auto msb_blk = in[msb_blk_idx];
    std::copy_n(in, in_num_words, out);
    out[msb_blk_idx] = msb_blk | (WORD_MAX << msb_blk_rem);
    std::fill(out + in_num_words, out + out_num_words, WORD_MAX);
    bv_clear_extra_bits(out, out_size);
  } else {
    std::copy_n(in, in_num_words, out);
    std::fill(out + in_num_words, out + out_num_words, 0);
  }
}

template <typename T>
void bv_sext(T* out, uint32_t out_size, const T* in, uint32_t in_size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;
  assert(in_size <= out_size);

  if (out_size <= WORD_SIZE) {
    bv_sext_scalar(out, out_size, in , in_size);
  } else {
    bv_sext_vector(out, out_size, in , in_size);
  }
}

}
}
