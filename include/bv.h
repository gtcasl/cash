#pragma once

#include "common.h"

namespace ch {
namespace internal {

template <typename T>
bool bv_is_neg_scalar(const T* in, uint32_t size) {
  auto mask = T(1) << (size - 1);
  return (in[0] & mask) != 0;
}

template <typename T>
bool bv_is_neg_vector(const T* in, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  uint32_t index = (size - 1);
  uint32_t widx  = index / WORD_SIZE;
  uint32_t wbit  = index % WORD_SIZE;
  auto mask = T(1) << wbit;
  return (in[widx] & mask) != 0;
}

template <typename T>
bool bv_is_neg(const T* in, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  if (size <= WORD_SIZE) {
    return bv_is_neg_scalar(in, size);
  } else {
    return bv_is_neg_vector(in, size);
  }
}

template <typename T>
void bv_clear_extra_bits(T* dst, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;
  static constexpr T        WORD_MAX  = std::numeric_limits<T>::max();

  uint32_t extra_bits = size % WORD_SIZE;
  if (extra_bits) {
    dst[size / WORD_SIZE] &= ~(WORD_MAX << extra_bits);
  }
}

template <typename U, typename T,
          CH_REQUIRE_0(std::is_integral_v<U>)>
void bv_assign_scalar(T* dst, U value) {
  dst[0] = value;
}

template <typename U, typename T,
          CH_REQUIRE_0(std::is_integral_v<U> && std::is_unsigned_v<U>)>
void bv_assign_vector(T* dst, uint32_t size, U value) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  uint32_t num_words = ceildiv(size, WORD_SIZE);
  if constexpr (bitwidth_v<U> <= WORD_SIZE) {
    dst[0] = value;
    std::fill_n(dst + 1, num_words - 1, 0);
  } else {
    if (0 == value) {
      std::fill_n(dst, num_words, 0);
      return;
    }
    auto len = std::min<uint32_t>(num_words, bitwidth_v<U> / WORD_SIZE);
    std::copy_n(reinterpret_cast<const T*>(&value), len, dst);
    std::fill_n(dst + len, num_words - len, 0);
  }
}

template <typename U, typename T,
          CH_REQUIRE_0(std::is_integral_v<U> && std::is_signed_v<U>)>
void bv_assign_vector(T* dst, uint32_t size, U value) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;
  static constexpr T        WORD_MAX  = std::numeric_limits<T>::max();

  uint32_t num_words = ceildiv(size, WORD_SIZE);
  T ext_value  = ((value >= 0) ? 0 : WORD_MAX);
  if constexpr (bitwidth_v<U> <= WORD_SIZE) {
    dst[0] = value;
    std::fill_n(dst + 1, num_words - 1, ext_value);
  } else {
    auto len = std::min<uint32_t>(num_words, bitwidth_v<U> / WORD_SIZE);
    std::copy_n(reinterpret_cast<const T*>(&value), len, dst);
    std::fill_n(dst + len, num_words - len, ext_value);
  }
}

template <typename U, typename T,
          CH_REQUIRE_0(std::is_integral_v<U> && std::is_unsigned_v<U>)>
void bv_assign(T* dst, uint32_t size, U value) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;
  if constexpr (std::numeric_limits<U>::digits > 1) {
    CH_CHECK(log2ceil(value + 1) <= size, "value out of range");
  }
  if (size <= WORD_SIZE) {
    bv_assign_scalar(dst, value);
  } else {
    bv_assign_vector(dst, size, value);
  }
}

template <typename U, typename T,
          CH_REQUIRE_0(std::is_integral_v<U> && std::is_signed_v<U>)>
void bv_assign(T* dst, uint32_t size, U value) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;
  static_assert(std::numeric_limits<U>::digits > 1, "inavlid size");

  if (value >= 0) {
    auto u_value = std::make_unsigned_t<U>(value);
    if constexpr (std::numeric_limits<U>::digits > 1) {
      CH_CHECK(log2ceil(u_value + 1) <= size, "value out of range");
    }
    if (size <= WORD_SIZE) {
      bv_assign_scalar(dst, u_value);
    } else {
      bv_assign_vector(dst, size, u_value);
    }
  } else {
    CH_CHECK(1 + log2ceil(~value + 1) <= size, "value out of range");
    if (size <= WORD_SIZE) {
      bv_assign_scalar(dst, value);
    } else {
      bv_assign_vector(dst, size, value);
    }
    bv_clear_extra_bits(dst, size);
  }
}

inline int string_literal_base(const char* value, int len) {
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

inline int string_literal_size(const char* value, int log_base, int len) {
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
void bv_assign(T* dst, uint32_t size, const std::string& value) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  size_t len = value.length();
  CH_CHECK(len >= 3, "invalid string format");

  const char* buf = value.c_str();
  int base = string_literal_base(buf, len);

  len -= 2; // remove base postfix
  if (16 == base && value[0] == '0' && len > 1 && value[1] == 'x') {
    buf += 2; // remove hex prefix
    len -= 2;
  }

  uint32_t log_base = log2ceil(base);

  uint32_t str_size = string_literal_size(buf, log_base, len);
  CH_CHECK(str_size >= 0, "invalid string size");
  CH_CHECK(size >= str_size, "value out of range");

  // clear remaining words
  uint32_t num_words = ceildiv(size, WORD_SIZE);
  uint32_t src_num_words = ceildiv(str_size, WORD_SIZE);
  if (src_num_words < num_words) {
    std::fill_n(dst + src_num_words, num_words - src_num_words, 0x0);
  }

  // write the value
  T w(0);
  T* d = dst;
  for (int32_t i = len - 1, j = 0; i >= 0; --i) {
    char chr = buf[i];
    if (chr == '\'')
      continue; // skip separator character
    T v = char2int(chr, base);
    w |= v << j;
    j += log_base;
    if (j >= int32_t(WORD_SIZE)) {
      *d++ = w;
      j -= WORD_SIZE;
      w = v >> (log_base - j);
    }
  }

  if (w) {
    *d = w;
  }
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

template <bool is_signed, typename T>
void bv_pad_scalar(T* out, uint32_t out_size, const T* in, uint32_t in_size) {
  if constexpr (is_signed) {
    out[0] = sign_ext(in[0], in_size);
    bv_clear_extra_bits(out, out_size);
  } else {
    CH_UNUSED(out_size, in_size);
    out[0] = in[0];
  }
}

template <bool is_signed, typename T>
void bv_pad_vector(T* out, uint32_t out_size, const T* in, uint32_t in_size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  uint32_t in_num_words = ceildiv(in_size, WORD_SIZE);
  uint32_t out_num_words = ceildiv(out_size, WORD_SIZE);

  if constexpr (is_signed) {
    static constexpr T WORD_MAX  = std::numeric_limits<T>::max();
    auto is_neg = bv_is_neg_vector(in, in_size);
    if (is_neg) {
      uint32_t msb = in_size - 1;
      uint32_t msb_blk_idx = msb / WORD_SIZE;
      uint32_t msb_blk_rem = msb % WORD_SIZE;
      auto msb_blk = in[msb_blk_idx];
      std::copy_n(in, in_num_words, out);
      out[msb_blk_idx] = msb_blk | (WORD_MAX << msb_blk_rem);
      std::fill(out + in_num_words, out + out_num_words, WORD_MAX);
      bv_clear_extra_bits(out, out_size);
    } else {
      std::copy_n(in, in_num_words, out);
      std::fill(out + in_num_words, out + out_num_words, 0);
    }
  } else {
    std::copy_n(in, in_num_words, out);
    std::fill(out + in_num_words, out + out_num_words, 0);
  }
}

template <bool is_signed, typename T>
void bv_pad(T* out, uint32_t out_size, const T* in, uint32_t in_size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;
  assert(out_size >= in_size);

  if (out_size <= WORD_SIZE) {
    bv_pad_scalar<is_signed>(out, out_size, in, in_size);
  } else {
    bv_pad_vector<is_signed>(out, out_size, in, in_size);
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
  static constexpr T        WORD_MAX  = std::numeric_limits<T>::max();

  uint32_t dst_end       = w_dst_begin_rem + length - 1;
  uint32_t w_dst_end_rem = dst_end % WORD_SIZE;

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
  uint32_t w_dst_end_rem = dst_end % WORD_SIZE;

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
  static constexpr T        WORD_MAX  = std::numeric_limits<T>::max();

  uint32_t src_end       = w_src_begin_rem + length - 1;
  uint32_t w_src_end_idx = (src_end / WORD_SIZE);
  uint32_t dst_end       = w_dst_begin_rem + length - 1;
  uint32_t w_dst_end_idx = (dst_end / WORD_SIZE);
  uint32_t w_dst_end_rem = dst_end % WORD_SIZE;

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
  uint32_t w_dst_end_rem = dst_end % WORD_SIZE;

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
  uint32_t w_dst_end_rem = dst_end % WORD_SIZE;

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

  if ((dst_offset + length) <= WORD_SIZE
   && (src_offset + length) <= WORD_SIZE) {
    bv_copy_scalar(dst, dst_offset, src, src_offset, length);
    return;
  }

  uint32_t w_dst_begin_idx = dst_offset / WORD_SIZE;
  uint32_t w_dst_begin_rem = dst_offset % WORD_SIZE;
  auto w_dst               = dst + w_dst_begin_idx;
  uint32_t w_src_begin_idx = src_offset / WORD_SIZE;
  uint32_t w_src_begin_rem = src_offset % WORD_SIZE;
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
  uint32_t w_dst_end_rem = dst_end % WORD_SIZE;

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

  uint32_t src_end       = w_src_begin_rem + dst_size - 1;
  uint32_t w_src_end_idx = (src_end / WORD_SIZE);
  uint32_t dst_end       = dst_size - 1;
  uint32_t w_dst_end_idx = (dst_end / WORD_SIZE);
  uint32_t w_dst_end_rem = dst_end % WORD_SIZE;

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

  if (src_offset + dst_size <= WORD_SIZE) {
    bv_slice_scalar(dst, dst_size, src, src_offset);
    return;
  }

  uint32_t w_src_begin_idx = src_offset / WORD_SIZE;
  uint32_t w_src_begin_rem = src_offset % WORD_SIZE;
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
bool bv_eq_scalar(const T* lhs, const T* rhs) {
  return (lhs[0] == rhs[0]);
}

template <typename T>
bool bv_eq_vector(const T* lhs, const T* rhs, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  uint32_t num_words = ceildiv(size, WORD_SIZE);
  for (uint32_t i = 0; i < num_words; ++i) {
    if (lhs[i] != rhs[i])
      return false;
  }
  return true;
}

template <typename T>
bool bv_eq(const T* lhs, const T* rhs, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;
  if (size <= WORD_SIZE) {
    return bv_eq_scalar<T>(lhs, rhs);
  } else {
    return bv_eq_vector<T>(lhs, rhs, size);
  }
}

template <bool is_signed, typename T>
bool bv_lt_scalar(const T* lhs, const T* rhs, uint32_t size) {
  if constexpr (is_signed) {
    // compare most signicant bits
    bool lhs_is_neg = bv_is_neg_scalar(lhs, size);
    bool rhs_is_neg = bv_is_neg_scalar(rhs, size);
    if (lhs_is_neg != rhs_is_neg)
      return lhs_is_neg;
    return (lhs[0] < rhs[0]);
  } else {
    CH_UNUSED(size);
    return (lhs[0] < rhs[0]);
  }
}

template <bool is_signed, typename T>
bool bv_lt_vector(const T* lhs, const T* rhs, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  if constexpr (is_signed) {
    // compare most signicant bits
    bool lhs_is_neg = bv_is_neg_vector(lhs, size);
    bool rhs_is_neg = bv_is_neg_vector(rhs, size);
    if (lhs_is_neg != rhs_is_neg)
      return lhs_is_neg;
  }

  // same-sign words comparison
  uint32_t num_words = ceildiv(size, WORD_SIZE);
  for (int32_t i = num_words - 1; i >= 0; --i) {
    if (lhs[i] != rhs[i])
      return (lhs[i] < rhs[i]);
  }

  return false;
}

template <bool is_signed, typename T>
bool bv_lt(const T* lhs, const T* rhs, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  if (size <= WORD_SIZE) {
    return bv_lt_scalar<is_signed>(lhs, rhs, size);
  } else {
    return bv_lt_vector<is_signed>(lhs, rhs, size);
  }
}

template <typename T>
void bv_inv_scalar(T* out, const T* in, uint32_t size) {
  out[0] = ~in[0];
  bv_clear_extra_bits(out, size);
}

template <typename T>
void bv_inv_vector(T* out, const T* in, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  uint32_t num_words = ceildiv(size, WORD_SIZE);
  for (uint32_t i = 0; i < num_words; ++i) {
    out[i] = ~in[i];
  }
  bv_clear_extra_bits(out, size);
}

template <typename T>
void bv_inv(T* out, const T* in, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  if (size <= WORD_SIZE) {
    return bv_inv_scalar<T>(out, in, size);
  } else {
    return bv_inv_vector<T>(out, in, size);
  }
}

template <typename T>
void bv_and_scalar(T* out, const T* lhs, const T* rhs) {
  out[0] = lhs[0] & rhs[0];
}

template <typename T>
void bv_and_vector(T* out, const T* lhs, const T* rhs, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  uint32_t num_words = ceildiv(size, WORD_SIZE);
  for (uint32_t i = 0; i < num_words; ++i) {
    out[i] = lhs[i] & rhs[i];
  }
}

template <typename T>
void bv_and(T* out, const T* lhs, const T* rhs, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  if (size <= WORD_SIZE) {
    return bv_and_scalar<T>(out, lhs, rhs);
  } else {
    return bv_and_vector<T>(out, lhs, rhs, size);
  }
}

template <typename T>
void bv_or_scalar(T* out, const T* lhs, const T* rhs) {
  out[0] = lhs[0] | rhs[0];
}

template <typename T>
void bv_or_vector(T* out, const T* lhs, const T* rhs, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  uint32_t num_words = ceildiv(size, WORD_SIZE);
  for (uint32_t i = 0; i < num_words; ++i) {
    out[i] = lhs[i] | rhs[i];
  }
}

template <typename T>
void bv_or(T* out, const T* lhs, const T* rhs, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  if (size <= WORD_SIZE) {
    return bv_or_scalar<T>(out, lhs, rhs);
  } else {
    return bv_or_vector<T>(out, lhs, rhs, size);
  }
}

template <typename T>
void bv_xor_scalar(T* out, const T* lhs, const T* rhs) {
  out[0] = lhs[0] ^ rhs[0];
}

template <typename T>
void bv_xor_vector(T* out, const T* lhs, const T* rhs, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  uint32_t num_words = ceildiv(size, WORD_SIZE);
  for (uint32_t i = 0; i < num_words; ++i) {
    out[i] = lhs[i] ^ rhs[i];
  }
}

template <typename T>
void bv_xor(T* out, const T* lhs, const T* rhs, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  if (size <= WORD_SIZE) {
    return bv_xor_scalar<T>(out, lhs, rhs);
  } else {
    return bv_xor_vector<T>(out, lhs, rhs, size);
  }
}

template <typename T>
bool bv_andr_scalar(const T* in, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;
  static constexpr T WORD_MAX = std::numeric_limits<T>::max();
  auto max = WORD_MAX >> (WORD_SIZE - size);
  return (in[0] == max);
}

template <typename T>
bool bv_andr_vector(const T* in, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;
  static constexpr T WORD_MAX = std::numeric_limits<T>::max();
  uint32_t num_words = ceildiv(size, WORD_SIZE);

  auto rem = size % WORD_SIZE;
  auto max = WORD_MAX >> ((WORD_SIZE - rem) % WORD_SIZE);
  int32_t i = num_words - 1;
  if (in[i--] != max)
      return false;
  for (; i >= 0; --i) {
    if (in[i] != WORD_MAX)
      return false;
  }
  return true;
}

template <typename T>
bool bv_andr(const T* in, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  if (size <= WORD_SIZE) {
    return bv_andr_scalar<T>(in, size);
  } else {
    return bv_andr_vector<T>(in, size);
  }
}

template <typename T>
bool bv_orr_scalar(const T* in) {
  return in[0];
}

template <typename T>
bool bv_orr_vector(const T* in, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  uint32_t num_words = ceildiv(size, WORD_SIZE);
  for (uint32_t i = 0; i < num_words; ++i) {
    if (in[i])
      return true;
  }
  return false;
}

template <typename T>
bool bv_orr(const T* in, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  if (size <= WORD_SIZE) {
    return bv_orr_scalar<T>(in);
  } else {
    return bv_orr_vector<T>(in, size);
  }
}

template <typename T>
bool bv_xorr_scalar(const T* in) {
  bool ret = false;
  T tmp = in[0];
  while (tmp) {
    ret ^= tmp & 0x1;
    tmp >>= 1;
  }
  return ret;
}

template <typename T>
bool bv_xorr_vector(const T* in, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  uint32_t num_words = ceildiv(size, WORD_SIZE);

  T tmp = in[0];
  for (uint32_t i = 1; i < num_words; ++i) {
    tmp ^= in[i];
  }
  bool ret = false;
  while (tmp) {
    ret ^= tmp & 0x1;
    tmp >>= 1;
  }
  return ret;
}

template <typename T>
bool bv_xorr(const T* in, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  if (size <= WORD_SIZE) {
    return bv_xorr_scalar<T>(in);
  } else {
    return bv_xorr_vector<T>(in, size);
  }
}

template <typename T>
void bv_shl_scalar(T* out, uint32_t out_size, const T* in, uint64_t dist) {
  out[0] = in[0] << dist;
  bv_clear_extra_bits(out, out_size);
}

template <typename T>
void bv_shl_vector(T* out, uint32_t out_size,
                   const T* in, uint32_t in_size,
                   uint64_t dist) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;
  assert(out_size >= in_size);

  int32_t in_num_words  = ceildiv(in_size, WORD_SIZE);
  int32_t out_num_words = ceildiv(out_size, WORD_SIZE);

  auto shift_words = std::min(ceildiv<int32_t>(dist, WORD_SIZE), out_num_words);
  uint32_t shift_bits = dist % WORD_SIZE;
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
  bv_clear_extra_bits(out, out_size);
}

template <typename T>
void bv_shl(T* out, uint32_t out_size,
            const T* in, uint32_t in_size,
            uint64_t dist) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;
  assert(out_size >= in_size);

  if (out_size <= WORD_SIZE) {
    bv_shl_scalar(out, out_size, in, dist);
  } else {
    bv_shl_vector(out, out_size, in, in_size, dist);
  }
}

template <bool is_signed, typename T>
void bv_shr_scalar(T* out, uint32_t out_size, const T* in, uint32_t in_size, uint64_t dist) {
  if constexpr (is_signed) {
    auto value = sign_ext(in[0], in_size);
    out[0] = value >> dist;
    bv_clear_extra_bits(out, out_size);
  }  else {
    CH_UNUSED(out_size, in_size);
    out[0] = in[0] >> dist;
  }
}

template <bool is_signed, typename T>
void bv_shr_vector(T* out, uint32_t out_size,
                   const T* in, uint32_t in_size,
                   uint64_t dist) {

  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;
  static constexpr T        WORD_MAX  = std::numeric_limits<T>::max();
  assert(out_size <= in_size);

  uint32_t in_num_words  = ceildiv(in_size, WORD_SIZE);
  uint32_t out_num_words = ceildiv(out_size, WORD_SIZE);

  uint32_t shift_words = std::min(ceildiv<uint32_t>(dist, WORD_SIZE), in_num_words);
  uint32_t rem_words = in_num_words - shift_words;
  uint32_t shift_bits = dist % WORD_SIZE;

  T ext = (is_signed && bv_is_neg_vector(in, in_size)) ? WORD_MAX : 0;
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

  if constexpr (is_signed) {
    bv_clear_extra_bits(out, out_size);
  }
}

template <bool is_signed, typename T>
void bv_shr(T* out, uint32_t out_size,
            const T* in, uint32_t in_size,
            uint64_t dist) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;
  assert(out_size <= in_size);

  if (in_size <= WORD_SIZE) {
    bv_shr_scalar<is_signed>(out, out_size, in, in_size, dist);
  } else {
    bv_shr_vector<is_signed>(out, out_size, in, in_size, dist);
  }
}

template <typename T>
void bv_add_scalar(T* out, const T* lhs, const T* rhs, uint32_t size) {
  out[0] = lhs[0] + rhs[0];
  bv_clear_extra_bits(out, size);
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
  bv_clear_extra_bits(out, size);
}

template <typename T>
void bv_add(T* out, const T* lhs, const T* rhs, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  if (size <= WORD_SIZE) {
    bv_add_scalar(out, lhs, rhs,  size);
  } else {
    bv_add_vector(out, lhs, rhs, size);
  }  
}

template <typename T>
void bv_sub_scalar(T* out, const T* lhs, const T* rhs, uint32_t size) {
  out[0] = lhs[0] - rhs[0];
  bv_clear_extra_bits(out, size);
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
  bv_clear_extra_bits(out, size);
}

template <typename T>
void bv_sub(T* out, const T* lhs, const T* rhs, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  if (size <= WORD_SIZE) {
    bv_sub_scalar(out, lhs, rhs, size);
  } else {
    bv_sub_vector(out, lhs, rhs, size);
  }
}

template <typename T>
void bv_neg_scalar(T* out, const T* in, uint32_t size) {
  out[0] = -in[0];
  bv_clear_extra_bits(out, size);
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
  bv_clear_extra_bits(out, size);
}

template <typename T>
void bv_neg(T* out, const T* in, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  if (size <= WORD_SIZE) {
    bv_neg_scalar(out, in, size);
  } else {
    bv_neg_vector(out, in, size);
  }
}

template <typename T>
void bv_abs_scalar(T* out, const T* in, uint32_t size) {
  if (bv_is_neg_scalar(in, size)) {
    bv_neg_scalar(out, in, size);
  } else {
    bv_copy_scalar(out, in, size);
  }
}

template <typename T>
void bv_abs_vector(T* out, const T* in, uint32_t size) {
  if (bv_is_neg_vector(in, size)) {
    bv_neg_vector(out, in, size);
  } else {
    bv_copy(out, in, size);
  }
}

template <typename T>
void bv_umult(T* out, uint32_t out_size,
              const T* lhs, uint32_t lhs_size,
              const T* rhs, uint32_t rhs_size) {
  using xword_t = std::conditional_t<sizeof(T) == 1, uint8_t,
                    std::conditional_t<sizeof(T) == 2, uint16_t, uint32_t>>;
  using yword_t = std::conditional_t<sizeof(T) == 1, uint16_t,
                     std::conditional_t<sizeof(T) == 2, uint32_t, uint64_t>>;
  assert(out_size <= lhs_size + rhs_size);
  static constexpr uint32_t XWORD_SIZE = bitwidth_v<xword_t>;

  auto u = reinterpret_cast<const xword_t*>(lhs);
  auto v = reinterpret_cast<const xword_t*>(rhs);
  auto w = reinterpret_cast<xword_t*>(out);

  auto m = ceildiv<int>(lhs_size, XWORD_SIZE);
  auto n = ceildiv<int>(rhs_size, XWORD_SIZE);
  auto p = ceildiv<int>(out_size, XWORD_SIZE);

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
  bv_clear_extra_bits(out, out_size);
}

template <bool is_signed, typename T>
void bv_mult_scalar(T* out, uint32_t out_size,
                    const T* lhs, uint32_t lhs_size,
                    const T* rhs, uint32_t rhs_size) {
  if constexpr (is_signed) {
    auto u = sign_ext(lhs[0], lhs_size);
    auto v = sign_ext(rhs[0], rhs_size);
    out[0] = u * v;
  } else {
    CH_UNUSED(lhs_size, rhs_size);
    out[0] = lhs[0] * rhs[0];
  }
  bv_clear_extra_bits(out, out_size);
}

template <bool is_signed, typename T>
void bv_mult_vector(T* out, uint32_t out_size,
                    const T* lhs, uint32_t lhs_size,
                    const T* rhs, uint32_t rhs_size) {
  if constexpr (is_signed) {
    static constexpr uint32_t WORD_SIZE  = bitwidth_v<T>;

    const T *u(lhs), *v(rhs);
    std::vector<T> uv, vv;

    if (lhs_size < out_size && bv_is_neg(u, lhs_size)) {
      uv.resize(ceildiv<uint32_t>(out_size, WORD_SIZE));
      bv_pad<true>(uv.data(), out_size, u, lhs_size);
      u = uv.data();
      lhs_size = out_size;
    }

    if (rhs_size < out_size && bv_is_neg(v, rhs_size)) {
      vv.resize(ceildiv<uint32_t>(out_size, WORD_SIZE));
      bv_pad<true>(vv.data(), out_size, v, rhs_size);
      v = vv.data();
      rhs_size = out_size;
    }

    bv_umult(out, out_size, u, lhs_size, v, rhs_size);
  } else {
    bv_umult(out, out_size, lhs, lhs_size, rhs, rhs_size);
  }
}

template <bool is_signed, typename T>
void bv_mult(T* out, uint32_t out_size,
             const T* lhs, uint32_t lhs_size,
             const T* rhs, uint32_t rhs_size) {
  static constexpr uint32_t WORD_SIZE  = bitwidth_v<T>;
  assert(out_size <= lhs_size + rhs_size);

  if (out_size <= WORD_SIZE
   && lhs_size <= WORD_SIZE
   && rhs_size <= WORD_SIZE) {
    bv_mult_scalar<is_signed>(out, out_size, lhs, lhs_size, rhs, rhs_size);
  } else {
    bv_mult_vector<is_signed>(out, out_size, lhs, lhs_size, rhs, rhs_size);
  }
}

template <typename T>
void bv_udiv(T* quot, uint32_t quot_size,
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

  if (0 == n) {
    CH_ABORT("divide by zero");
  }

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

  if (rn) {
    // unnormalize remainder
    for (int i = 0; i < std::min(n, rn); ++i) {
      r[i] = (un[i] >> s) | (un[i + 1] << (XWORD_SIZE - s));
    }
  }
}

template <bool is_signed, typename T>
void bv_div_scalar(T* out, uint32_t out_size,
                   const T* lhs, uint32_t lhs_size,
                   const T* rhs, uint32_t rhs_size) {
  if constexpr (is_signed) {
    auto u = sign_ext(lhs[0], lhs_size);
    auto v = sign_ext(rhs[0], rhs_size);
    out[0] = u / v;
  } else {
    CH_UNUSED(lhs_size, rhs_size);
    out[0] = lhs[0] / rhs[0];
  }
  bv_clear_extra_bits(out, out_size);
}

template <bool is_signed, typename T>
void bv_div_vector(T* out, uint32_t out_size,
                   const T* lhs, uint32_t lhs_size,
                   const T* rhs, uint32_t rhs_size) {
  if constexpr (is_signed) {
    static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

    const T *u(lhs), *v(rhs);
    std::vector<T> uv, vv;

    if (bv_is_neg(u, lhs_size)) {
      uv.resize(ceildiv<uint32_t>(lhs_size, WORD_SIZE));
      bv_neg_vector(uv.data(), u, lhs_size);
      u = uv.data();
    }

    if (bv_is_neg(v, rhs_size)) {
      vv.resize(ceildiv<uint32_t>(rhs_size, WORD_SIZE));
      bv_neg_vector(vv.data(), v, rhs_size);
      v = vv.data();
    }

    T* r = nullptr;
    bv_udiv(out, out_size, r, 0, u, lhs_size, v, rhs_size);
    if (bv_is_neg_vector(lhs, lhs_size) ^ bv_is_neg_vector(rhs, rhs_size)) {
      bv_neg_vector(out, out, out_size);
    }
  } else {
    T* r = nullptr;
    bv_udiv(out, out_size, r, 0, lhs, lhs_size, rhs, rhs_size);
  }
  bv_clear_extra_bits(out, out_size);
}

template <bool is_signed, typename T>
void bv_div(T* out, uint32_t out_size,
            const T* lhs, uint32_t lhs_size,
            const T* rhs, uint32_t rhs_size) {
  static constexpr uint32_t WORD_SIZE  = bitwidth_v<T>;

  if (out_size <= WORD_SIZE
   && lhs_size <= WORD_SIZE
   && rhs_size <= WORD_SIZE) {
    bv_div_scalar<is_signed>(out, out_size, lhs, lhs_size, rhs, rhs_size);
  } else {
    bv_div_vector<is_signed>(out, out_size, lhs, lhs_size, rhs, rhs_size);
  }
}

template <bool is_signed, typename T>
void bv_mod_scalar(T* out, uint32_t out_size,
                   const T* lhs, uint32_t lhs_size,
                   const T* rhs, uint32_t rhs_size) {
  if constexpr (is_signed) {
    auto u = sign_ext(lhs[0], lhs_size);
    auto v = sign_ext(rhs[0], rhs_size);
    out[0] = u % v;
  } else {
    CH_UNUSED(lhs_size, rhs_size);
    out[0] = lhs[0] % rhs[0];
  }
  bv_clear_extra_bits(out, out_size);
}

template <bool is_signed, typename T>
void bv_mod_vector(T* out, uint32_t out_size,
                   const T* lhs, uint32_t lhs_size,
                   const T* rhs, uint32_t rhs_size) {
  if constexpr (is_signed) {
    static constexpr uint32_t WORD_SIZE  = bitwidth_v<T>;

    const T *u(lhs), *v(rhs);
    std::vector<T> uv, vv;

    if (bv_is_neg(u, lhs_size)) {
      uv.resize(ceildiv<uint32_t>(lhs_size, WORD_SIZE));
      bv_neg_vector(uv.data(), u, lhs_size);
      u = uv.data();
    }

    if (bv_is_neg(v, rhs_size)) {
      vv.resize(ceildiv<uint32_t>(rhs_size, WORD_SIZE));
      bv_neg_vector(vv.data(), v, rhs_size);
      v = vv.data();
    }

    T* q = nullptr;
    bv_udiv(q, 0, out, out_size, u, lhs_size, v, rhs_size);
    if (bv_is_neg_vector(lhs, lhs_size)) {
      bv_neg_vector(out, out, out_size);
    }
  } else {
    T* q = nullptr;
    bv_udiv(q, 0, out, out_size, lhs, lhs_size, rhs, rhs_size);
  }
  bv_clear_extra_bits(out, out_size);
}

template <bool is_signed, typename T>
void bv_mod(T* out, uint32_t out_size,
            const T* lhs, uint32_t lhs_size,
            const T* rhs, uint32_t rhs_size) {
  static constexpr uint32_t WORD_SIZE  = bitwidth_v<T>;

  if (out_size <= WORD_SIZE
   && lhs_size <= WORD_SIZE
   && rhs_size <= WORD_SIZE) {
    bv_mod_scalar<is_signed>(out, out_size, lhs, lhs_size, rhs, rhs_size);
  } else {
    bv_mod_vector<is_signed>(out, out_size, lhs, lhs_size, rhs, rhs_size);
  }
}

}
}
