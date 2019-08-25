#pragma once

#include "common.h"

namespace ch {
namespace internal {

template <typename T>
void bv_clear_extra_bits(T* dst, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;
  static constexpr T        WORD_MAX  = std::numeric_limits<T>::max();

  uint32_t rem = size % WORD_SIZE;
  if (rem) {
    dst[size / WORD_SIZE] &= ~(WORD_MAX << rem);
  }
}

template <typename T>
void bv_init(T* dst, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;
  static constexpr T        WORD_MAX  = std::numeric_limits<T>::max();

  uint32_t num_words = ceildiv(size, WORD_SIZE);
  std::fill_n(dst, num_words, (0xCDCDCDCDCDCDCDCD & WORD_MAX));
  bv_clear_extra_bits(dst, size);
}

template <typename T>
void bv_reset(T* dst, uint32_t size) {
 static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

 uint32_t num_words = ceildiv(size, WORD_SIZE);
 std::fill_n(dst, num_words, 0);
}

///////////////////////////////////////////////////////////////////////////////

template <typename T>
bool bv_get(const T* bv, uint32_t offset) {
  static unsigned constexpr WORD_SIZE = bitwidth_v<T>;
  auto idx = offset / WORD_SIZE;
  auto lsb = offset % WORD_SIZE;
  return (bv[idx] >> lsb) & 0x1;
}

template <typename T>
void bv_set(T* bv, uint32_t offset, bool value) {
  static unsigned constexpr WORD_SIZE = bitwidth_v<T>;
  auto idx = offset / WORD_SIZE;
  auto lsb = offset % WORD_SIZE;
  auto mask = T(1) << lsb;
  if (value) {
    bv[idx] |= mask;
  } else {
    bv[idx] &= ~mask;
  }
}

///////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////

template <typename T>
bool bv_is_zero_scalar(const T* in) {
  return (0 == in[0]);
}

template <typename T>
bool bv_is_zero_vector(const T* in, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  uint32_t num_words = ceildiv(size, WORD_SIZE);
  for (uint32_t i = 0; i < num_words; ++i) {
    if (in[i])
      return false;
  }
  return true;
}

template <typename T>
bool bv_is_zero(const T* in, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  if (size <= WORD_SIZE) {
    return bv_is_zero_scalar(in);
  } else {
    return bv_is_zero_vector(in, size);
  }
}

///////////////////////////////////////////////////////////////////////////////

template <typename T>
bool bv_is_one_scalar(const T* in) {
  return (1 == in[0]);
}

template <typename T>
bool bv_is_one_vector(const T* in, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  uint32_t num_words = ceildiv(size, WORD_SIZE);
  for (uint32_t i = num_words - 1; i > 0; --i) {
    if (in[i])
      return false;
  }
  return (1 == in[0]);
}

template <typename T>
bool bv_is_one(const T* in, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  if (size <= WORD_SIZE) {
    return bv_is_one_scalar(in);
  } else {
    return bv_is_one_vector(in, size);
  }
}

///////////////////////////////////////////////////////////////////////////////

template <typename T>
bool bv_is_ones_scalar(const T* in, uint32_t size) {
  auto max = std::numeric_limits<uint64_t>::max() >> (64 - size);
  return (max == in[0]);
}

template <typename T>
bool bv_is_ones_vector(const T* in, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  uint32_t num_words = ceildiv(size, WORD_SIZE);
  for (uint32_t i = 0; i < num_words - 1; ++i) {
    if (in[i] != std::numeric_limits<T>::max())
      return false;
  }

  auto rem = size % WORD_SIZE;
  auto max = std::numeric_limits<uint64_t>::max() >> (64 - rem);
  return (max == in[num_words - 1]);
}

template <typename T>
bool bv_is_ones(const T* in, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  if (size <= WORD_SIZE) {
    return bv_is_ones_scalar(in, size);
  } else {
    return bv_is_ones_vector(in, size);
  }
}

///////////////////////////////////////////////////////////////////////////////

template <typename T>
void bv_copy_scalar(T* out, const T* in) {
  out[0] = in[0];
}

template <typename T>
void bv_copy_vector(T* out, const T* in, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  uint32_t num_words = ceildiv(size, WORD_SIZE);
  std::copy_n(in, num_words, out);
}

template <typename T>
void bv_copy(T* out, const T* in, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  if (size <= WORD_SIZE) {
    bv_copy_scalar(out , in);
  } else {
    bv_copy_vector(out , in, size);
  }
}

///////////////////////////////////////////////////////////////////////////////

template <typename T>
void bv_copy_scalar(T* w_dst,
                    uint32_t w_dst_lsb,
                    const T* w_src,
                    uint32_t w_src_lsb,
                    uint32_t length) {
  static unsigned constexpr WORD_SIZE = bitwidth_v<T>;
  static constexpr T        WORD_MAX  = std::numeric_limits<T>::max();
  assert((w_dst_lsb + length) <= WORD_SIZE);
  assert((w_src_lsb + length) <= WORD_SIZE);

  T src_block = (w_src[0] >> w_src_lsb) << w_dst_lsb;
  T mask = (WORD_MAX >> (WORD_SIZE - length)) << w_dst_lsb;
  w_dst[0] = blend<T>(mask, w_dst[0], src_block);
}

template <typename T>
void bv_copy_vector_small(T* w_dst,
                          uint32_t w_dst_lsb,
                          const T* w_src,
                          uint32_t w_src_lsb,
                          uint32_t length) {
  static unsigned constexpr WORD_SIZE = bitwidth_v<T>;
  static constexpr T        WORD_MAX  = std::numeric_limits<T>::max();
  assert(length <= WORD_SIZE);
  assert(w_dst_lsb < WORD_SIZE);
  assert(w_src_lsb < WORD_SIZE);

  T src_block0 = w_src[0] >> w_src_lsb;
  if (w_src_lsb + length > WORD_SIZE) {
    src_block0 |= (w_src[1] << (WORD_SIZE - w_src_lsb));
  }
  T mask0 = (WORD_MAX >> (WORD_SIZE - length)) << w_dst_lsb;
  w_dst[0] = blend<T>(mask0, w_dst[0], (src_block0 << w_dst_lsb));
  if (w_dst_lsb > (WORD_SIZE - length)) {
    T src_block1 = src_block0 >> (WORD_SIZE - w_dst_lsb);
    T mask1 = T(~mask0) >> (WORD_SIZE - length);
    w_dst[1] = blend<T>(mask1, w_dst[1], src_block1);
  }
}

template <typename T>
void bv_copy_vector_aligned(T* w_dst, const T* w_src, uint32_t length) {
  static unsigned constexpr WORD_SIZE = bitwidth_v<T>;
  static constexpr unsigned WORD_MASK = WORD_SIZE - 1;
  static constexpr T        WORD_MAX  = std::numeric_limits<T>::max();
  assert(length > WORD_SIZE);

  uint32_t dst_end       = length - 1;
  uint32_t w_dst_end_idx = (dst_end / WORD_SIZE);
  uint32_t w_dst_msb     = dst_end % WORD_SIZE;

  // update aligned blocks
  if (WORD_MASK == w_dst_msb) {
    std::copy_n(w_src, w_dst_end_idx + 1, w_dst);
  } else {
    std::copy_n(w_src, w_dst_end_idx, w_dst);
    // update remining block
    T src_block = w_src[w_dst_end_idx];
    T mask = (WORD_MAX << 1) << w_dst_msb;
    w_dst[w_dst_end_idx] = blend<T>(mask, src_block, w_dst[w_dst_end_idx]);
  }
}

template <typename T>
void bv_copy_vector_aligned_dst(T* w_dst,
                                const T* w_src,
                                uint32_t w_src_lsb,
                                uint32_t length) {
  static unsigned constexpr WORD_SIZE = bitwidth_v<T>;
  static constexpr T        WORD_MAX  = std::numeric_limits<T>::max();
  assert(length > WORD_SIZE);
  assert(w_src_lsb < WORD_SIZE);

  uint32_t src_end       = w_src_lsb + length - 1;
  uint32_t w_src_end_idx = (src_end / WORD_SIZE);

  uint32_t dst_end       = length - 1;
  uint32_t w_dst_end_idx = (dst_end / WORD_SIZE);
  uint32_t w_dst_msb     = dst_end % WORD_SIZE;

  // update first block
  T src_block = *w_src++ >> w_src_lsb;
  src_block |= w_src[0] << (WORD_SIZE - w_src_lsb);
  w_dst[0] = src_block;

  // update intermediate blocks
  auto w_dst_end = (w_dst++) + w_dst_end_idx;
  while (w_dst < w_dst_end) {
    T tmp = *w_src++ >> w_src_lsb;
    *w_dst++ = tmp | (w_src[0] << (WORD_SIZE - w_src_lsb));
  }

  // update remining blocks
  src_block = w_src[0] >> w_src_lsb;
  if (w_src_end_idx > w_dst_end_idx) {
    src_block |= (w_src[1] << (WORD_SIZE - w_src_lsb));
  }
  T mask = (WORD_MAX << 1) << w_dst_msb;
  w_dst[0] = blend<T>(mask, src_block, w_dst[0]);
}

template <typename T>
void bv_copy_vector_aligned_src(T* w_dst,
                                uint32_t w_dst_lsb,
                                const T* w_src,
                                uint32_t length) {
  static unsigned constexpr WORD_SIZE = bitwidth_v<T>;
  static constexpr unsigned WORD_MASK = WORD_SIZE - 1;
  static constexpr T        WORD_MAX  = std::numeric_limits<T>::max();
  assert(length > WORD_SIZE);
  assert(w_dst_lsb < WORD_SIZE);

  uint32_t src_end       = length - 1;
  uint32_t w_src_end_idx = (src_end / WORD_SIZE);

  uint32_t dst_end       = w_dst_lsb + length - 1;
  uint32_t w_dst_end_idx = (dst_end / WORD_SIZE);
  uint32_t w_dst_msb     = dst_end % WORD_SIZE;

  // update first block
  T src_block = *w_src++;
  T mask = WORD_MAX << w_dst_lsb;
  w_dst[0] = blend<T>(mask, w_dst[0], (src_block << w_dst_lsb));

  // update intermediate blocks
  auto w_dst_end = (w_dst++) + w_src_end_idx;
  while (w_dst < w_dst_end) {
    auto tmp = *w_src++;
    *w_dst++ = (tmp << w_dst_lsb) | ((src_block >> 1) >> (WORD_MASK - w_dst_lsb));
    src_block = tmp;
  }

  // update remining blocks
  src_block = (w_src[0] << w_dst_lsb) | ((src_block >> 1) >> (WORD_MASK - w_dst_lsb));
  if (w_src_end_idx < w_dst_end_idx) {
    *w_dst++ = src_block;
    src_block = (w_src[0] >> 1) >> (WORD_MASK - w_dst_lsb);
  }
  mask = (WORD_MAX << 1) << w_dst_msb;
  w_dst[0] = blend<T>(mask, src_block, w_dst[0]);
}

template <typename T>
void bv_copy_vector_unaligned(T* w_dst,
                              uint32_t w_dst_lsb,
                              const T* w_src,
                              uint32_t w_src_lsb,
                              uint32_t length) {
  static unsigned constexpr WORD_SIZE = bitwidth_v<T>;
  static constexpr unsigned WORD_MASK = WORD_SIZE - 1;
  static constexpr T        WORD_MAX  = std::numeric_limits<T>::max();
  assert(length > WORD_SIZE);
  assert(w_dst_lsb && w_dst_lsb < WORD_SIZE);
  assert(w_src_lsb && w_src_lsb < WORD_SIZE);

  uint32_t src_end       = w_src_lsb + length - 1;
  uint32_t w_src_end_idx = (src_end / WORD_SIZE);

  uint32_t dst_end       = w_dst_lsb + length - 1;
  uint32_t w_dst_end_idx = (dst_end / WORD_SIZE);
  uint32_t w_dst_msb     = dst_end % WORD_SIZE;

  // update first block
  T src_block = *w_src++ >> w_src_lsb;
  src_block |= (w_src[0] << (WORD_SIZE - w_src_lsb));
  T mask = WORD_MAX << w_dst_lsb;
  w_dst[0] = blend<T>(mask, w_dst[0], (src_block << w_dst_lsb));

  // update intermediate blocks
  auto w_dst_end = (w_dst++) + std::min(w_src_end_idx, w_dst_end_idx);
  while (w_dst < w_dst_end) {
    T tmp = *w_src++ >> w_src_lsb;
    tmp |= (w_src[0] << (WORD_SIZE - w_src_lsb));
    *w_dst++ = (tmp << w_dst_lsb) | ((src_block >> 1) >> (WORD_MASK - w_dst_lsb));
    src_block = tmp;
  }

  // update remining blocks
  T tmp = w_src[0] >> w_src_lsb;
  if (w_src_end_idx < w_dst_end_idx) {
    src_block = (tmp << w_dst_lsb) | ((src_block >> 1) >> (WORD_MASK - w_dst_lsb));
    *w_dst++ = src_block;
    src_block = (tmp >> 1) >> (WORD_MASK - w_dst_lsb);
  } else
  if (w_src_end_idx == w_dst_end_idx) {
    src_block = (tmp << w_dst_lsb) | ((src_block >> 1) >> (WORD_MASK - w_dst_lsb));
  } else {
    src_block = (tmp | (w_src[1] << (WORD_SIZE - w_src_lsb))) << w_dst_lsb;
  }
  mask = (WORD_MAX << 1) << w_dst_msb;
  w_dst[0] = blend<T>(mask, src_block, w_dst[0]);
}

template <typename T>
void bv_copy_vector(T* w_dst, uint32_t w_dst_lsb,
                    const T* w_src, uint32_t w_src_lsb,
                    uint32_t length) {
  static unsigned constexpr WORD_SIZE = bitwidth_v<T>;
  assert(w_dst_lsb < WORD_SIZE);
  assert(w_src_lsb < WORD_SIZE);

  if (length <= WORD_SIZE) {
    bv_copy_vector_small(w_dst, w_dst_lsb, w_src, w_src_lsb, length);
  } else
  if (0 == ((w_dst_lsb % 8) | (w_src_lsb % 8))) {
    auto b_dst = reinterpret_cast<uint8_t*>(w_dst) + (w_dst_lsb / 8);
    auto b_src = reinterpret_cast<const uint8_t*>(w_src) + (w_src_lsb / 8);
    bv_copy_vector_aligned(b_dst, b_src, length);
  } else
  if (0 == w_dst_lsb) {
    bv_copy_vector_aligned_dst(w_dst, w_src, w_src_lsb, length);
  } else
  if (0 == w_src_lsb) {
    bv_copy_vector_aligned_src(w_dst, w_dst_lsb, w_src, length);
  } else {
    bv_copy_vector_unaligned(w_dst, w_dst_lsb, w_src, w_src_lsb, length);
  }
}

template <typename T>
void bv_copy(T* w_dst, uint32_t dst_offset,
             const T* w_src, uint32_t src_offset,
             uint32_t length) {
  static unsigned constexpr WORD_SIZE = bitwidth_v<T>;

  if ((dst_offset + length) <= WORD_SIZE
   && (src_offset + length) <= WORD_SIZE) {
    bv_copy_scalar(w_dst, dst_offset, w_src, src_offset, length);
  } else {
    auto w_dst_idx = dst_offset / WORD_SIZE;
    auto w_dst_lsb = dst_offset % WORD_SIZE;
    auto w_src_idx = src_offset / WORD_SIZE;
    auto w_src_lsb = src_offset % WORD_SIZE;
    bv_copy_vector(w_dst + w_dst_idx, w_dst_lsb, w_src + w_src_idx, w_src_lsb, length);
  }
}

///////////////////////////////////////////////////////////////////////////////

template <typename U, typename T,
          CH_REQUIRE(std::is_integral_v<U>)>
void bv_assign_scalar(T* dst, U value) {
  dst[0] = value;
}

template <typename U, typename T,
          CH_REQUIRE(std::is_integral_v<U> && std::is_unsigned_v<U>)>
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
          CH_REQUIRE(std::is_integral_v<U> && std::is_signed_v<U>)>
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
          CH_REQUIRE(std::is_integral_v<U> && std::is_unsigned_v<U>)>
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
          CH_REQUIRE(std::is_integral_v<U> && std::is_signed_v<U>)>
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

template <typename U, std::size_t N, typename T>
void bv_assign(T* dst, uint32_t size, const std::array<U, N>& value) {
  static_assert(std::is_integral_v<U>, "invalid array type");
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;
  for (std::size_t i = 0; i < N; ++i) {
    auto j = N - 1 - i;
    auto length = bitwidth_v<U>;
    int rem = ((i + 1) * bitwidth_v<U>) - size;
    if (rem > 0) {
      length = bitwidth_v<U> - rem;
      CH_CHECK(length < bitwidth_v<U>, "buffer out of range");
      CH_CHECK(0 == (value[j] >> length), "value out of range");
    }
    bv_copy<U>(reinterpret_cast<U*>(dst),
               i * bitwidth_v<U>,
               value.data(),
               j * bitwidth_v<U>,
               length);
  }
  auto src_num_words = ceildiv<uint32_t>(N * bitwidth_v<U>, WORD_SIZE);
  auto num_words = ceildiv(size, WORD_SIZE);
  std::fill_n(dst + src_num_words, num_words - src_num_words, 0);
}

template <typename U, typename T>
void bv_assign(T* dst, uint32_t size, const std::vector<U>& value) {
  static_assert(std::is_integral_v<U>, "invalid array type");
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;
  for (std::size_t i = 0, n = value.size(); i < n; ++i) {
    auto j = n - 1 - i;
    auto length = bitwidth_v<U>;
    int rem = ((i + 1 ) * bitwidth_v<U>) - size;
    if (rem > 0) {
      length = bitwidth_v<U> - rem;
      CH_CHECK(length < bitwidth_v<U>, "buffer out of range");
      CH_CHECK(0 == (value[j] >> length), "value out of range");
    }
    bv_copy<U>(reinterpret_cast<U*>(dst),
               i * bitwidth_v<U>,
               value.data(),
               j * bitwidth_v<U>,
               length);
  }
  auto src_num_words = ceildiv<uint32_t>(value.size() * bitwidth_v<U>, WORD_SIZE);
  auto num_words = ceildiv(size, WORD_SIZE);
  std::fill_n(dst + src_num_words, num_words - src_num_words, 0);
}

///////////////////////////////////////////////////////////////////////////////

inline int string_literal_base(const char* value, int len) {
  int base = 0;
  switch (value[len-1]) {
  case 'b':
    base = 1;
    break;
  case 'o':
    base = 3;
    break;
  case 'h':
    base = 4;
    break;
  default:
    throw std::invalid_argument("invalid binary encoding type.");
  }
  return base;
}

inline int string_literal_size(const char* value, int len, int base) {
  int size = 0;
  for (const char *cur = value, *end = value + len; cur < end;) {
    char chr = *cur++;
    if (chr == '\'' || chr == '_') // skip number separator
      continue;
    if (0 == size) {
       // calculate exact bit coverage for the first non zero character
       int v = char2int(chr, 1 << base);
       if (v) {
         size += log2ceil(v+1);
       }
    } else {
      size += base;
    }
  }
  return size;
}

template <typename T>
void bv_assign(T* dst, uint32_t size, const char* value, uint32_t length, int base) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  const char* buf = value;
  if (4 == base && value[0] == '0' && length > 1 && value[1] == 'x') {
    buf += 2; // remove hex prefix
    length -= 2;
  }

  uint32_t str_size = string_literal_size(buf, length, base);
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
  for (int32_t i = length - 1, j = 0; i >= 0; --i) {
    char chr = buf[i];
    if (chr == '\'' || chr == '_') // skip number separator
      continue;
    T v = char2int(chr, 1 << base);
    w |= v << j;
    j += base;
    if (j >= int32_t(WORD_SIZE)) {
      *d++ = w;
      j -= WORD_SIZE;
      w = v >> (base - j);
    }
  }

  if (w) {
    *d = w;
  }
}

template <typename T>
void bv_assign(T* dst, uint32_t size, const std::string& value) {
  size_t len = value.length();
  CH_CHECK(len >= 3, "invalid string size");

  const char* buf = value.c_str();
  int base = string_literal_base(buf, len);
  len -= 2; // remove base postfix
  bv_assign(dst, size, buf, len, base);
}

///////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////

template <typename T>
int bv_msb_scalar(const T* in) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  auto w = in[0];
  if (w) {
    int z = count_leading_zeros<T>(w);
    return (WORD_SIZE - 1 - z);
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
      return (WORD_SIZE - 1 - z) + i * WORD_SIZE;
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

///////////////////////////////////////////////////////////////////////////////

template <typename U, typename T>
U bv_cast(const T* in, uint32_t size) {
  static_assert(std::is_integral_v<T>, "invalid type");
  if constexpr (bitwidth_v<U> <= bitwidth_v<T>) {
    CH_UNUSED(size);
    return bit_cast<U>(in[0]);
  } else {    
    U ret(0);
    memcpy(&ret, in, ceildiv(size, 8));
    return ret;
  }
}

///////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////

template <typename T>
void bv_slice_scalar(T* w_dst, uint32_t dst_size, const T* w_src, uint32_t w_src_lsb) {
  static unsigned constexpr WORD_SIZE = bitwidth_v<T>;
  assert((w_src_lsb + dst_size) <= WORD_SIZE);

  T src_block = w_src[0] >> w_src_lsb;
  uint32_t clamp = (WORD_SIZE - dst_size);
  w_dst[0] = T(src_block << clamp) >> clamp;
}

template <typename T>
void bv_slice_vector_small(T* w_dst, uint32_t dst_size, const T* w_src, uint32_t w_src_lsb) {
  static unsigned constexpr WORD_SIZE = bitwidth_v<T>;
  assert(dst_size <= WORD_SIZE);
  assert(w_src_lsb < WORD_SIZE);

  T src_block = w_src[0] >> w_src_lsb;
  uint32_t clamp = (WORD_SIZE - dst_size);
  if (w_src_lsb > clamp) {
    src_block |= w_src[1] << (WORD_SIZE - w_src_lsb);
  }  
  w_dst[0] = T(src_block << clamp) >> clamp;
}

template <typename T>
void bv_slice_vector_aligned(T* dst, uint32_t dst_size, const T* w_src) {
  static unsigned constexpr WORD_SIZE = bitwidth_v<T>;
  static constexpr unsigned WORD_MASK = WORD_SIZE - 1;
  assert(dst_size > WORD_SIZE);

  uint32_t dst_end       = dst_size - 1;
  uint32_t w_dst_end_idx = (dst_end / WORD_SIZE);
  uint32_t w_dst_msb     = dst_end % WORD_SIZE;

  // update aligned blocks
  if (WORD_MASK == w_dst_msb) {
    std::copy_n(w_src, w_dst_end_idx + 1, dst);
  } else {
    std::copy_n(w_src, w_dst_end_idx, dst);
    // update remining block
    uint32_t clamp = (WORD_MASK - w_dst_msb);
    dst[w_dst_end_idx] = T(w_src[w_dst_end_idx] << clamp) >> clamp;
  }
}

template <typename T>
void bv_slice_vector_unaligned(T* w_dst, uint32_t dst_size, const T* w_src, uint32_t w_src_lsb) {
  static unsigned constexpr WORD_SIZE = bitwidth_v<T>;
  static constexpr unsigned WORD_MASK = WORD_SIZE - 1;
  assert(dst_size > WORD_SIZE);
  assert(w_src_lsb && w_src_lsb < WORD_SIZE);

  uint32_t src_end       = w_src_lsb + dst_size - 1;
  uint32_t w_src_end_idx = (src_end / WORD_SIZE);

  uint32_t dst_end       = dst_size - 1;
  uint32_t w_dst_end_idx = (dst_end / WORD_SIZE);
  uint32_t w_dst_msb     = dst_end % WORD_SIZE;

  // update first block
  T src_block = *w_src++ >> w_src_lsb;
  src_block |= w_src[0] << (WORD_SIZE - w_src_lsb);
  w_dst[0] = src_block;

  // update intermediate blocks
  auto w_dst_end = (w_dst++) + w_dst_end_idx;
  while (w_dst < w_dst_end) {
    T tmp = *w_src++ >> w_src_lsb;
    *w_dst++ = tmp | (w_src[0] << (WORD_SIZE - w_src_lsb));
  }

  // update remining blocks
  src_block = w_src[0] >> w_src_lsb;
  if (w_src_end_idx > w_dst_end_idx) {
    src_block |= w_src[1] << (WORD_SIZE - w_src_lsb);
  }
  uint32_t clamp = (WORD_MASK - w_dst_msb);
  w_dst[0] = T(src_block << clamp) >> clamp;
}

template <typename T>
void bv_slice_vector(T* w_dst, uint32_t dst_size, const T* w_src, uint32_t w_src_lsb) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;
  assert(w_src_lsb < WORD_SIZE);

  if (dst_size <= WORD_SIZE) {
    bv_slice_vector_small(w_dst, dst_size, w_src, w_src_lsb);
  } else
  if (0 == (w_src_lsb % 8)) {
    auto b_dst = reinterpret_cast<uint8_t*>(w_dst);
    auto b_src = reinterpret_cast<const uint8_t*>(w_src) + (w_src_lsb / 8);
    bv_slice_vector_aligned(b_dst, dst_size, b_src);
  } else {
    bv_slice_vector_unaligned(w_dst, dst_size, w_src, w_src_lsb);
  }
}

template <typename T>
void bv_slice(T* w_dst, uint32_t dst_size, const T* w_src, uint32_t src_offset) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  if (src_offset + dst_size <= WORD_SIZE) {
    bv_slice_scalar(w_dst, dst_size, w_src, src_offset);
  } else {
    auto w_src_idx = src_offset / WORD_SIZE;
    auto w_src_lsb = src_offset % WORD_SIZE;
    bv_slice_vector(w_dst, dst_size, w_src + w_src_idx, w_src_lsb);
  }
}

///////////////////////////////////////////////////////////////////////////////

template <typename T>
int bv_cmp_scalar(const T* lhs,
                  uint32_t lhs_lsb,
                  const T* rhs,
                  uint32_t rhs_lsb,
                  uint32_t length) {
  static unsigned constexpr WORD_SIZE = bitwidth_v<T>;
  assert((lhs_lsb + length) <= WORD_SIZE);
  assert((rhs_lsb + length) <= WORD_SIZE);

  uint32_t clamp = WORD_SIZE - length;
  T lhs_block = T((lhs[0] >> lhs_lsb) << clamp) >> clamp;
  T rhs_block = T((rhs[0] >> rhs_lsb) << clamp) >> clamp;
  return lhs_block - rhs_block;
}

template <typename T>
int bv_cmp_vector_small(const T* lhs, uint32_t lhs_lsb,
                        const T* rhs, uint32_t rhs_lsb,
                        uint32_t length) {
  static unsigned constexpr WORD_SIZE = bitwidth_v<T>;
  assert(length <= WORD_SIZE);
  assert(lhs_lsb < WORD_SIZE);
  assert(rhs_lsb < WORD_SIZE);

  uint32_t clamp = WORD_SIZE - length;

  T lhs_block = lhs[0] >> lhs_lsb;
  if (lhs_lsb + length > WORD_SIZE) {
    lhs_block |= (lhs[1] << (WORD_SIZE - lhs_lsb));
  }
  lhs_block = T(lhs_block << clamp) >> clamp;

  T rhs_block = rhs[0] >> rhs_lsb;
  if (rhs_lsb + length > WORD_SIZE) {
    rhs_block |= (rhs[1] << (WORD_SIZE - rhs_lsb));
  }
  rhs_block = T(rhs_block << clamp) >> clamp;

  return lhs_block - rhs_block;
}

template <typename T>
int bv_cmp_vector_aligned(const T* lhs, const T* rhs, uint32_t length) {
  static unsigned constexpr WORD_SIZE = bitwidth_v<T>;
  assert(length > WORD_SIZE);

  uint32_t wcount = length / WORD_SIZE;
  uint32_t rem    = length % WORD_SIZE;

  // update aligned blocks
  if (0 == rem) {
    return memcmp(lhs, rhs, wcount * sizeof(T));
  } else {
    auto test = memcmp(lhs, rhs, (wcount - 1) * sizeof(T));
    if (test)
      return test;
    // compare remining block
    return bv_cmp_scalar(lhs + wcount, 0, rhs + wcount, 0, rem);
  }
}

template <typename T>
int bv_cmp_vector_aligned_lhs(const T* lhs,
                              const T* rhs, uint32_t rhs_lsb,
                              uint32_t length) {
  static unsigned constexpr WORD_SIZE = bitwidth_v<T>;
  assert(length > WORD_SIZE);
  assert(rhs_lsb && rhs_lsb < WORD_SIZE);

  uint32_t wcount = length / WORD_SIZE;
  uint32_t rem    = length % WORD_SIZE;

  // compare intermediate blocks
  for (uint32_t n = wcount; n--;) {
    T lhs_block = *lhs++;
    T rhs_block = *rhs++ >> rhs_lsb;
    rhs_block |= (rhs[0] << (WORD_SIZE - rhs_lsb));
    std::make_signed_t<T> test = lhs_block - rhs_block;
    if (test)
      return (test > 0) ? 1 : -1;
  }
  if (0 == rem)
    return 0;
  // compare remining block
  return bv_cmp_vector_small(lhs, 0, rhs, rhs_lsb, rem);
}

template <typename T>
int bv_cmp_vector_aligned_rhs(const T* lhs, uint32_t lhs_lsb,
                              const T* rhs,
                              uint32_t length) {
  static unsigned constexpr WORD_SIZE = bitwidth_v<T>;
  assert(length > WORD_SIZE);
  assert(lhs_lsb && lhs_lsb < WORD_SIZE);

  uint32_t wcount = length / WORD_SIZE;
  uint32_t rem    = length % WORD_SIZE;

  // compare intermediate blocks
  for (uint32_t n = wcount; n--;) {
    T lhs_block = *lhs++ >> lhs_lsb;
    lhs_block |= (lhs[0] << (WORD_SIZE - lhs_lsb));
    T rhs_block = *rhs++;
    std::make_signed_t<T> test = lhs_block - rhs_block;
    if (test)
      return (test > 0) ? 1 : -1;
  }
  if (0 == rem)
    return 0;
  // compare remining block
  return bv_cmp_vector_small(lhs, lhs_lsb, rhs, 0, rem);
}

template <typename T>
int bv_cmp_vector_unaligned(const T* lhs, uint32_t lhs_lsb,
                            const T* rhs, uint32_t rhs_lsb,
                            uint32_t length) {
  static unsigned constexpr WORD_SIZE = bitwidth_v<T>;
  assert(length > WORD_SIZE);
  assert(lhs_lsb && lhs_lsb < WORD_SIZE);
  assert(rhs_lsb && rhs_lsb < WORD_SIZE);

  uint32_t wcount = length / WORD_SIZE;
  uint32_t rem    = length % WORD_SIZE;

  // compare intermediate blocks
  for (uint32_t n = wcount; n--;) {
    T lhs_block = *lhs++ >> lhs_lsb;
    lhs_block |= (lhs[0] << (WORD_SIZE - lhs_lsb));
    T rhs_block = *rhs++ >> rhs_lsb;
    rhs_block |= (rhs[0] << (WORD_SIZE - rhs_lsb));
    std::make_signed_t<T> test = lhs_block - rhs_block;
    if (test)
      return (test > 0) ? 1 : -1;
  }
  if (0 == rem)
    return 0;
  // compare remining block
  return bv_cmp_vector_small(lhs, lhs_lsb, rhs, rhs_lsb, rem);
}

template <typename T>
int bv_cmp_vector(const T* lhs, uint32_t lhs_lsb,
                  const T* rhs, uint32_t rhs_lsb,
                  uint32_t length) {
  static unsigned constexpr WORD_SIZE = bitwidth_v<T>;
  assert(lhs_lsb < WORD_SIZE);
  assert(rhs_lsb < WORD_SIZE);

  if (length <= WORD_SIZE) {
    return bv_cmp_vector_small(lhs, lhs_lsb, rhs, rhs_lsb, length);
  } else
  if (0 == ((lhs_lsb % 8) | (rhs_lsb % 8))) {
    auto b_lhs = reinterpret_cast<const uint8_t*>(lhs) + (lhs_lsb / 8);
    auto b_rhs = reinterpret_cast<const uint8_t*>(rhs) + (rhs_lsb / 8);
    return bv_cmp_vector_aligned(b_lhs, b_rhs, length);
  } else
  if (0 == lhs_lsb) {
    return bv_cmp_vector_aligned_lhs(lhs, rhs, rhs_lsb, length);
  } else
  if (0 == rhs_lsb) {
    return bv_cmp_vector_aligned_rhs(lhs, lhs_lsb, rhs, length);
  } else {
    return bv_cmp_vector_unaligned(lhs, lhs_lsb, rhs, rhs_lsb, length);
  }
}

template <typename T>
int bv_cmp(const T* lhs, uint32_t lhs_offset,
           const T* rhs, uint32_t rhs_offset,
           uint32_t length) {
  static unsigned constexpr WORD_SIZE = bitwidth_v<T>;

  if ((lhs_offset + length) <= WORD_SIZE
   && (rhs_offset + length) <= WORD_SIZE) {
    return bv_cmp_scalar(lhs, lhs_offset, rhs, rhs_offset, length);
  } else {
    auto lhs_idx = lhs_offset / WORD_SIZE;
    auto lhs_lsb = lhs_offset % WORD_SIZE;
    auto rhs_idx = rhs_offset / WORD_SIZE;
    auto rhs_lsb = rhs_offset % WORD_SIZE;
    return bv_cmp_vector(lhs + lhs_idx, lhs_lsb, rhs + rhs_idx, rhs_lsb, length);
  }
}

///////////////////////////////////////////////////////////////////////////////

template <typename T, bool is_resizable, bool is_signed>
class StaticBitAccessor {
public:
  StaticBitAccessor(const T* value, uint32_t size, uint32_t other_size)
    : value_(value)
    , last_value_(0)
    , last_index_(0)
    , resize_(false) {
    if constexpr (is_resizable) {
      if ((is_signed && (size % bitwidth_v<T>) != 0)
       || (size < other_size)) {
        resize_ = true;
        last_index_ = (size - 1) / bitwidth_v<T>;
        if constexpr (is_signed) {
          last_value_ = sign_ext(value[last_index_], size % bitwidth_v<T>);
        }
      }
    }
  }

  T get() const {
    if constexpr (is_resizable && is_signed) {
      return resize_ ? last_value_ : value_[0];
    } else {
      return value_[0];
    }
  }

  T get(uint32_t index) const {
    if constexpr (is_resizable) {
      if (resize_) {
        if constexpr (is_signed) {
          if (index < last_index_) {
            return value_[index];
          } else {
            if (index == last_index_) {
              return last_value_;
            } else {
              return -(last_value_ >> (bitwidth_v<T> - 1));
            }
          }
        } else {
          return (index <= last_index_) ? value_[index] : 0;
        }
      } else {
        return value_[index];
      }
    } else {
      return value_[index];
    }
  }

  bool need_resize() const {
    return resize_;
  }

private:  
  const T* value_;    
  T last_value_;
  uint32_t last_index_;
  bool resize_;
};

template <typename T> using ClearBitAccessor = StaticBitAccessor<T, false, false>;
template <typename T, bool is_signed> using DefaultBitAccessor = StaticBitAccessor<T, true, is_signed>;

///////////////////////////////////////////////////////////////////////////////

template <bool is_signed, typename T, typename BitAccessor = DefaultBitAccessor<T, is_signed>>
bool bv_eq_scalar(const T* lhs, uint32_t lhs_size, const T* rhs, uint32_t rhs_size) {
  BitAccessor arg0(lhs, lhs_size, rhs_size);
  BitAccessor arg1(rhs, rhs_size, lhs_size);
  return (arg0.get() == arg1.get());
}

template <bool is_signed, typename T, typename BitAccessor = DefaultBitAccessor<T, is_signed>>
bool bv_eq_vector(const T* lhs, uint32_t lhs_size, const T* rhs, uint32_t rhs_size) {
  BitAccessor arg0(lhs, lhs_size, rhs_size);
  BitAccessor arg1(rhs, rhs_size, lhs_size);
  auto num_words = ceildiv(std::max(lhs_size, rhs_size), bitwidth_v<T>);
  for (uint32_t i = 0; i < num_words; ++i) {
    if (arg0.get(i) != arg1.get(i))
      return false;
  }
  return true;
}

template <bool is_signed, typename T, typename BitAccessor = DefaultBitAccessor<T, is_signed>>
bool bv_eq(const T* lhs, uint32_t lhs_size, const T* rhs, uint32_t rhs_size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;
  if (lhs_size <= WORD_SIZE
   && rhs_size <= WORD_SIZE) {
    return bv_eq_scalar<is_signed, T, BitAccessor>(lhs, lhs_size, rhs, rhs_size);
  } else {
    return bv_eq_vector<is_signed, T, BitAccessor>(lhs, lhs_size, rhs, rhs_size);
  }
}

///////////////////////////////////////////////////////////////////////////////

template <bool is_signed, typename T, typename BitAccessor = DefaultBitAccessor<T, is_signed>>
bool bv_lt_scalar(const T* lhs, uint32_t lhs_size, const T* rhs, uint32_t rhs_size) {
  if constexpr (is_signed) {
    // compare most signicant bits
    bool lhs_is_neg = bv_is_neg_scalar(lhs, lhs_size);
    bool rhs_is_neg = bv_is_neg_scalar(rhs, rhs_size);
    if (lhs_is_neg != rhs_is_neg)
      return lhs_is_neg;
  }
  BitAccessor arg0(lhs, lhs_size, rhs_size);
  BitAccessor arg1(rhs, rhs_size, lhs_size);
  return (arg0.get() < arg1.get());
}

template <bool is_signed, typename T, typename BitAccessor = DefaultBitAccessor<T, is_signed>>
bool bv_lt_vector(const T* lhs, uint32_t lhs_size, const T* rhs, uint32_t rhs_size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  if constexpr (is_signed) {
    // compare most signicant bits
    bool lhs_is_neg = bv_is_neg_vector(lhs, lhs_size);
    bool rhs_is_neg = bv_is_neg_vector(rhs, rhs_size);
    if (lhs_is_neg != rhs_is_neg)
      return lhs_is_neg;
  }

  BitAccessor arg0(lhs, lhs_size, rhs_size);
  BitAccessor arg1(rhs, rhs_size, lhs_size);

  // same-sign words comparison
  uint32_t num_words = ceildiv(std::max(lhs_size, rhs_size), WORD_SIZE);
  for (int32_t i = num_words - 1; i >= 0; --i) {
    if (arg0.get(i) != arg1.get(i))
      return (arg0.get(i) < arg1.get(i));
  }

  return false;
}

template <bool is_signed, typename T, typename BitAccessor = DefaultBitAccessor<T, is_signed>>
bool bv_lt(const T* lhs, uint32_t lhs_size, const T* rhs, uint32_t rhs_size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  if (lhs_size <= WORD_SIZE
   && rhs_size <= WORD_SIZE) {
    return bv_lt_scalar<is_signed, T, BitAccessor>(lhs, lhs_size, rhs, rhs_size);
  } else {
    return bv_lt_vector<is_signed, T, BitAccessor>(lhs, lhs_size, rhs, rhs_size);
  }
}

///////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////

template <typename T>
bool bv_xorr_scalar(const T* in) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  T tmp = in[0];
  if constexpr (WORD_SIZE > 32) {
    tmp ^= tmp >> 32;
  }
  if constexpr (WORD_SIZE > 16) {
    tmp ^= tmp >> 16;
  }
  if constexpr (WORD_SIZE > 8) {
    tmp ^= tmp >> 8;
  }
  if constexpr (WORD_SIZE > 4) {
    tmp ^= tmp >> 4;
  }
  if constexpr (WORD_SIZE > 2) {
    tmp ^= tmp >> 2;
  }
  if constexpr (WORD_SIZE > 1) {
    tmp ^= tmp >> 1;
  }
  return tmp & 0x1;
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

///////////////////////////////////////////////////////////////////////////////

template <typename T>
bool bv_not_scalar(const T* in) {
  return !bv_orr_scalar(in);
}

template <typename T>
bool bv_not_vector(const T* in, uint32_t size) {
  return !bv_orr_vector(in, size);
}

template <typename T>
bool bv_not(const T* in, uint32_t size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  if (size <= WORD_SIZE) {
    return bv_not_scalar<T>(in);
  } else {
    return bv_not_vector<T>(in, size);
  }
}

///////////////////////////////////////////////////////////////////////////////

template <typename T>
bool bv_andl_scalar(const T* lhs, const T* rhs) {
  return bv_orr_scalar(lhs) && bv_orr_scalar(rhs);
}

template <typename T>
bool bv_andl_vector(const T* lhs, uint32_t lhs_size, const T* rhs, uint32_t rhs_size) {
  return bv_orr_vector(lhs, lhs_size) && bv_orr_vector(rhs, rhs_size);
}

template <typename T>
bool bv_andl(const T* lhs, uint32_t lhs_size, const T* rhs, uint32_t rhs_size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  if (lhs_size <= WORD_SIZE
   && rhs_size <= WORD_SIZE) {
    return bv_andl_scalar<T>(lhs, rhs);
  } else {
    return bv_andl_vector<T>(lhs, lhs_size, rhs, rhs_size);
  }
}

///////////////////////////////////////////////////////////////////////////////

template <typename T>
bool bv_orl_scalar(const T* lhs, const T* rhs) {
  return bv_orr_scalar(lhs) || bv_orr_scalar(rhs);
}

template <typename T>
bool bv_orl_vector(const T* lhs, uint32_t lhs_size, const T* rhs, uint32_t rhs_size) {
  return bv_orr_vector(lhs, lhs_size) || bv_orr_vector(rhs, rhs_size);
}

template <typename T>
bool bv_orl(const T* lhs, uint32_t lhs_size, const T* rhs, uint32_t rhs_size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  if (lhs_size <= WORD_SIZE
   && rhs_size <= WORD_SIZE) {
    return bv_orl_scalar<T>(lhs, rhs);
  } else {
    return bv_orl_vector<T>(lhs, lhs_size, rhs, rhs_size);
  }
}

///////////////////////////////////////////////////////////////////////////////

template <bool is_signed, typename T, typename BitAccessor = DefaultBitAccessor<T, is_signed>>
void bv_inv_scalar(T* out, uint32_t out_size, const T* in, uint32_t in_size) {
  BitAccessor arg0(in, in_size, out_size);

  out[0] = ~arg0.get();
  bv_clear_extra_bits(out, out_size);
}

template <bool is_signed, typename T, typename BitAccessor = DefaultBitAccessor<T, is_signed>>
void bv_inv_vector(T* out, uint32_t out_size, const T* in, uint32_t in_size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  BitAccessor arg0(in, in_size, out_size);

  uint32_t num_words = ceildiv(out_size, WORD_SIZE);
  for (uint32_t i = 0; i < num_words; ++i) {
    out[i] = ~arg0.get(i);
  }
  bv_clear_extra_bits(out, out_size);
}

template <bool is_signed, typename T, typename BitAccessor = DefaultBitAccessor<T, is_signed>>
void bv_inv(T* out, uint32_t out_size, const T* in, uint32_t in_size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  if (out_size <= WORD_SIZE
   && in_size <= WORD_SIZE) {
    return bv_inv_scalar<is_signed, T, BitAccessor>(out, out_size, in, in_size);
  } else {
    return bv_inv_vector<is_signed, T, BitAccessor>(out, out_size, in, in_size);
  }
}

///////////////////////////////////////////////////////////////////////////////

template <bool is_signed, typename T, typename BitAccessor = DefaultBitAccessor<T, is_signed>>
void bv_and_scalar(T* out, uint32_t out_size, const T* lhs, uint32_t lhs_size, const T* rhs, uint32_t rhs_size) {
  BitAccessor arg0(lhs, lhs_size, out_size);
  BitAccessor arg1(rhs, rhs_size, out_size);

  out[0] = arg0.get() & arg1.get();

  if constexpr (is_signed) {
    if (arg0.need_resize() || arg1.need_resize()) {
      bv_clear_extra_bits(out, out_size);
    }
  }
}

template <bool is_signed, typename T, typename BitAccessor = DefaultBitAccessor<T, is_signed>>
void bv_and_vector(T* out, uint32_t out_size, const T* lhs, uint32_t lhs_size, const T* rhs, uint32_t rhs_size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  BitAccessor arg0(lhs, lhs_size, out_size);
  BitAccessor arg1(rhs, rhs_size, out_size);

  uint32_t num_words = ceildiv(out_size, WORD_SIZE);
  for (uint32_t i = 0; i < num_words; ++i) {
    out[i] = arg0.get(i) & arg1.get(i);
  }

  if constexpr (is_signed) {
    if (arg0.need_resize() || arg1.need_resize()) {
      bv_clear_extra_bits(out, out_size);
    }
  }
}

template <bool is_signed, typename T, typename BitAccessor = DefaultBitAccessor<T, is_signed>>
void bv_and(T* out, uint32_t out_size, const T* lhs, uint32_t lhs_size, const T* rhs, uint32_t rhs_size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  if (out_size <= WORD_SIZE
   && lhs_size <= WORD_SIZE
   && rhs_size <= WORD_SIZE) {
    return bv_and_scalar<is_signed, T, BitAccessor>(out, out_size, lhs, lhs_size, rhs, rhs_size);
  } else {
    return bv_and_vector<is_signed, T, BitAccessor>(out, out_size, lhs, lhs_size, rhs, rhs_size);
  }
}

///////////////////////////////////////////////////////////////////////////////

template <bool is_signed, typename T, typename BitAccessor = DefaultBitAccessor<T, is_signed>>
void bv_or_scalar(T* out, uint32_t out_size, const T* lhs, uint32_t lhs_size, const T* rhs, uint32_t rhs_size) {
  BitAccessor arg0(lhs, lhs_size, out_size);
  BitAccessor arg1(rhs, rhs_size, out_size);

  out[0] = arg0.get() | arg1.get();

  if constexpr (is_signed) {
    if (arg0.need_resize() || arg1.need_resize()) {
      bv_clear_extra_bits(out, out_size);
    }
  }
}

template <bool is_signed, typename T, typename BitAccessor = DefaultBitAccessor<T, is_signed>>
void bv_or_vector(T* out, uint32_t out_size, const T* lhs, uint32_t lhs_size, const T* rhs, uint32_t rhs_size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  BitAccessor arg0(lhs, lhs_size, out_size);
  BitAccessor arg1(rhs, rhs_size, out_size);

  uint32_t num_words = ceildiv(out_size, WORD_SIZE);
  for (uint32_t i = 0; i < num_words; ++i) {
    out[i] = arg0.get(i) | arg1.get(i);
  }

  if constexpr (is_signed) {
    if (arg0.need_resize() || arg1.need_resize()) {
      bv_clear_extra_bits(out, out_size);
    }
  }
}

template <bool is_signed, typename T, typename BitAccessor = DefaultBitAccessor<T, is_signed>>
void bv_or(T* out, uint32_t out_size, const T* lhs, uint32_t lhs_size, const T* rhs, uint32_t rhs_size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  if (out_size <= WORD_SIZE
   && lhs_size <= WORD_SIZE
   && rhs_size <= WORD_SIZE) {
    return bv_or_scalar<is_signed, T, BitAccessor>(out, out_size, lhs, lhs_size, rhs, rhs_size);
  } else {
    return bv_or_vector<is_signed, T, BitAccessor>(out, out_size, lhs, lhs_size, rhs, rhs_size);
  }
}

///////////////////////////////////////////////////////////////////////////////

template <bool is_signed, typename T, typename BitAccessor = DefaultBitAccessor<T, is_signed>>
void bv_xor_scalar(T* out, uint32_t out_size, const T* lhs, uint32_t lhs_size, const T* rhs, uint32_t rhs_size) {
  BitAccessor arg0(lhs, lhs_size, out_size);
  BitAccessor arg1(rhs, rhs_size, out_size);

  out[0] = arg0.get() ^ arg1.get();

  if constexpr (is_signed) {
    if (arg0.need_resize() || arg1.need_resize()) {
      bv_clear_extra_bits(out, out_size);
    }
  }
}

template <bool is_signed, typename T, typename BitAccessor = DefaultBitAccessor<T, is_signed>>
void bv_xor_vector(T* out, uint32_t out_size, const T* lhs, uint32_t lhs_size, const T* rhs, uint32_t rhs_size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  BitAccessor arg0(lhs, lhs_size, out_size);
  BitAccessor arg1(rhs, rhs_size, out_size);

  uint32_t num_words = ceildiv(out_size, WORD_SIZE);
  for (uint32_t i = 0; i < num_words; ++i) {
    out[i] = arg0.get(i) ^ arg1.get(i);
  }

  if constexpr (is_signed) {
    if (arg0.need_resize() || arg1.need_resize()) {
      bv_clear_extra_bits(out, out_size);
    }
  }
}

template <bool is_signed, typename T, typename BitAccessor = DefaultBitAccessor<T, is_signed>>
void bv_xor(T* out, uint32_t out_size, const T* lhs, uint32_t lhs_size, const T* rhs, uint32_t rhs_size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  if (out_size <= WORD_SIZE
   && lhs_size <= WORD_SIZE
   && rhs_size <= WORD_SIZE) {
    return bv_xor_scalar<is_signed, T, BitAccessor>(out, out_size, lhs, lhs_size, rhs, rhs_size);
  } else {
    return bv_xor_vector<is_signed, T, BitAccessor>(out, out_size, lhs, lhs_size, rhs, rhs_size);
  }
}

///////////////////////////////////////////////////////////////////////////////

template <bool is_signed, typename T, typename BitAccessor = DefaultBitAccessor<T, is_signed>>
void bv_blend_scalar(T* out, uint32_t out_size,
                     const T* mask, uint32_t mask_size,
                     const T* lhs, uint32_t lhs_size,
                     const T* rhs, uint32_t rhs_size) {
  BitAccessor arg0(mask, mask_size, out_size);
  BitAccessor arg1(lhs, lhs_size, out_size);
  BitAccessor arg2(rhs, rhs_size, out_size);

  out[0] = arg1.get() ^ ((arg1.get() ^ arg2.get()) & arg0.get());

  if constexpr (is_signed) {
    if (arg0.need_resize() || arg1.need_resize() || arg2.need_resize()) {
      bv_clear_extra_bits(out, out_size);
    }
  }
}

template <bool is_signed, typename T, typename BitAccessor = DefaultBitAccessor<T, is_signed>>
void bv_blend_vector(T* out, uint32_t out_size,
                     const T* mask, uint32_t mask_size,
                     const T* lhs, uint32_t lhs_size,
                     const T* rhs, uint32_t rhs_size) {
  bv_xor_vector<is_signed, T, BitAccessor>(out, out_size, lhs, lhs_size, rhs, rhs_size);
  bv_and_vector<is_signed, T, BitAccessor>(out, out_size, out, out_size, mask, mask_size);
  bv_xor_vector<is_signed, T, BitAccessor>(out, out_size, out, out_size, lhs, lhs_size);
}

template <bool is_signed, typename T, typename BitAccessor = DefaultBitAccessor<T, is_signed>>
void bv_blend(T* out, uint32_t out_size,
              const T* mask, uint32_t mask_size,
              const T* lhs, uint32_t lhs_size,
              const T* rhs, uint32_t rhs_size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  if (out_size <= WORD_SIZE
   && mask_size <= WORD_SIZE
   && lhs_size <= WORD_SIZE
   && rhs_size <= WORD_SIZE) {
    return bv_blend_scalar<is_signed, T, BitAccessor>(
          out, out_size, mask, mask_size, lhs, lhs_size, rhs, rhs_size);
  } else {
    return bv_blend_vector<is_signed, T, BitAccessor>(
          out, out_size, mask, mask_size, lhs, lhs_size, rhs, rhs_size);
  }
}

///////////////////////////////////////////////////////////////////////////////

template <typename T>
void bv_shl_scalar(T* out, uint32_t out_size, const T* in, uint32_t dist) {
  out[0] = (dist < bitwidth_v<T>) ? (in[0] << dist) : 0;
  bv_clear_extra_bits(out, out_size);
}

template <typename T>
void bv_shl_vector(T* out, uint32_t out_size,
                   const T* in, uint32_t in_size,
                   uint32_t dist) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  auto in_num_words  = ceildiv<int32_t>(in_size, WORD_SIZE);
  auto out_num_words = ceildiv<int32_t>(out_size, WORD_SIZE);

  auto shift_words = ceildiv<int32_t>(dist, WORD_SIZE);
  int32_t shift_bits = dist % WORD_SIZE;

  auto m = in_num_words + shift_words;
  auto i = out_num_words - 1;
  for (; i >= m;) {
    out[i--] = 0;
  }

  if (shift_bits) {
    auto j = i + 1 - shift_words;
    T prev = (uint32_t(j) < uint32_t(in_num_words)) ? (in[j] << shift_bits) : 0;
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
            uint32_t dist) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  if (out_size <= WORD_SIZE
   && in_size <= WORD_SIZE) {
    bv_shl_scalar(out, out_size, in, dist);
  } else {
    bv_shl_vector(out, out_size, in, in_size, dist);
  }
}

///////////////////////////////////////////////////////////////////////////////

template <bool is_signed, typename T>
void bv_shr_scalar(T* out, uint32_t out_size, const T* in, uint32_t in_size, uint32_t dist) {
  if constexpr (is_signed) {    
    auto value = sign_ext<T>(in[0], in_size);
    out[0] = (dist < bitwidth_v<T>) ? (value >> dist) : (value >> (bitwidth_v<T> - 1));
    bv_clear_extra_bits(out, out_size);
  }  else {
    CH_UNUSED(out_size, in_size);
    out[0] = (dist < bitwidth_v<T>) ? (in[0] >> dist) : 0;
  }
}

template <bool is_signed, typename T>
void bv_shr_vector(T* out, uint32_t out_size,
                   const T* in, uint32_t in_size,
                   uint32_t dist) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  auto in_num_words  = ceildiv<int32_t>(in_size, WORD_SIZE);
  auto out_num_words = ceildiv<int32_t>(out_size, WORD_SIZE);

  int32_t shift_words = ceildiv<int32_t>(dist, WORD_SIZE);
  int32_t shift_bits = dist % WORD_SIZE;

  auto r =  std::min(in_num_words - shift_words, out_num_words);
  T ext = 0;
  if constexpr (is_signed) {
    ext = bv_is_neg_vector(in, in_size) ? std::numeric_limits<T>::max() : 0;
  }

  if (shift_bits) {
    T prev = (shift_words <= in_num_words) ? (in[shift_words-1] >> shift_bits) : ext;
    int32_t i = 0;
    if constexpr (is_signed) {
      if (r > 0) {
        for (; i < r - 1; ++i) {
          auto curr = in[i + shift_words];
          out[i] = (curr << (WORD_SIZE - shift_bits)) | prev;
          prev = curr >> shift_bits;
        }
        auto src = in[i + shift_words];
        auto rem = in_size % WORD_SIZE;
        auto curr = rem ? sign_ext<T>(src, rem) : src;
        out[i++] = (curr << (WORD_SIZE - shift_bits)) | prev;
        prev = curr >> shift_bits;
      }
    } else {
      for (; i < r; ++i) {
        auto curr = in[i + shift_words];
        out[i] = (curr << (WORD_SIZE - shift_bits)) | prev;
        prev = curr >> shift_bits;
      }
    }
    for (; i < out_num_words; ++i) {
      out[i] = (ext << (WORD_SIZE - shift_bits)) | prev;
      prev = ext;
    }
  } else {
    int32_t i = 0;
    if constexpr (is_signed) {
      if (r > 0) {
        for (; i < r - 1; ++i) {
          out[i] = in[i + shift_words];
        }
        auto src = in[i + shift_words];
        auto rem = in_size % WORD_SIZE;
        auto curr = rem ? sign_ext(src, rem) : src;
        out[i++] = curr;
      }
    } else {
      for (; i < r; ++i) {
        out[i] = in[i + shift_words];
      }
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
            uint32_t dist) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  if (out_size <= WORD_SIZE
   && in_size <= WORD_SIZE) {
    bv_shr_scalar<is_signed>(out, out_size, in, in_size, dist);
  } else {
    bv_shr_vector<is_signed>(out, out_size, in, in_size, dist);
  }
}

///////////////////////////////////////////////////////////////////////////////

template <bool is_signed, typename T, typename BitAccessor = DefaultBitAccessor<T, is_signed>>
void bv_neg_scalar(T* out, uint32_t out_size, const T* in, uint32_t in_size) {
  BitAccessor arg(in, in_size, out_size);

  out[0] = -arg.get();

  bv_clear_extra_bits(out, out_size);
}

template <bool is_signed, typename T, typename BitAccessor = DefaultBitAccessor<T, is_signed>>
void bv_neg_vector(T* out, uint32_t out_size, const T* in, uint32_t in_size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  BitAccessor arg(in, in_size, out_size);

  T borrow(0);
  uint32_t num_words = ceildiv(out_size, WORD_SIZE);
  for (uint32_t i = 0; i < num_words; ++i) {
    auto a = arg.get(i);
    T b = -a - borrow;
    borrow = (a != 0) || (b != 0);
    out[i] = b;
  }
  bv_clear_extra_bits(out, out_size);
}

template <bool is_signed, typename T, typename BitAccessor = DefaultBitAccessor<T, is_signed>>
void bv_neg(T* out, uint32_t out_size, const T* in, uint32_t in_size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  if (out_size <= WORD_SIZE
   && in_size <= WORD_SIZE) {
    bv_neg_scalar<is_signed, T, BitAccessor>(out, out_size, in, in_size);
  } else {
    bv_neg_vector<is_signed, T, BitAccessor>(out, out_size, in, in_size);
  }
}

///////////////////////////////////////////////////////////////////////////////

template <bool is_signed, typename T, typename BitAccessor = DefaultBitAccessor<T, is_signed>>
void bv_add_scalar(T* out, uint32_t out_size, const T* lhs, uint32_t lhs_size, const T* rhs, uint32_t rhs_size) {
  BitAccessor arg0(lhs, lhs_size, out_size);
  BitAccessor arg1(rhs, rhs_size, out_size);

  out[0] = arg0.get() + arg1.get();

  bv_clear_extra_bits(out, out_size);
}

template <bool is_signed, typename T, typename BitAccessor = DefaultBitAccessor<T, is_signed>>
void bv_add_vector(T* out, uint32_t out_size, const T* lhs, uint32_t lhs_size, const T* rhs, uint32_t rhs_size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  BitAccessor arg0(lhs, lhs_size, out_size);
  BitAccessor arg1(rhs, rhs_size, out_size);

  T carry(0);
  uint32_t num_words = ceildiv(out_size, WORD_SIZE);
  for (uint32_t i = 0; i < num_words; ++i) {
    auto a = arg0.get(i);
    auto b = arg1.get(i);
    T c = a + b;
    T d = c + carry;
    carry = (c < a) || (d < carry);
    out[i] = d;
  }
  bv_clear_extra_bits(out, out_size);
}

template <bool is_signed, typename T, typename BitAccessor = DefaultBitAccessor<T, is_signed>>
void bv_add(T* out, uint32_t out_size, const T* lhs, uint32_t lhs_size, const T* rhs, uint32_t rhs_size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  if (out_size <= WORD_SIZE
   && lhs_size <= WORD_SIZE
   && rhs_size <= WORD_SIZE) {
    bv_add_scalar<is_signed, T, BitAccessor>(out, out_size, lhs, lhs_size, rhs, rhs_size);
  } else {
    bv_add_vector<is_signed, T, BitAccessor>(out, out_size, lhs, lhs_size, rhs, rhs_size);
  }  
}

///////////////////////////////////////////////////////////////////////////////

template <bool is_signed, typename T, typename BitAccessor = DefaultBitAccessor<T, is_signed>>
void bv_sub_scalar(T* out, uint32_t out_size, const T* lhs, uint32_t lhs_size, const T* rhs, uint32_t rhs_size) {
  BitAccessor arg0(lhs, lhs_size, out_size);
  BitAccessor arg1(rhs, rhs_size, out_size);

  out[0] = arg0.get() - arg1.get();

  bv_clear_extra_bits(out, out_size);
}

template <bool is_signed, typename T, typename BitAccessor = DefaultBitAccessor<T, is_signed>>
void bv_sub_vector(T* out, uint32_t out_size, const T* lhs, uint32_t lhs_size, const T* rhs, uint32_t rhs_size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  BitAccessor arg0(lhs, lhs_size, out_size);
  BitAccessor arg1(rhs, rhs_size, out_size);

  T borrow(0);
  uint32_t num_words = ceildiv(out_size, WORD_SIZE);
  for (uint32_t i = 0; i < num_words; ++i) {
    auto a = arg0.get(i);
    auto b = arg1.get(i);
    T c = a - b;
    T d = c - borrow;
    borrow = (a < c) || (c < d);
    out[i] = d;
  }
  bv_clear_extra_bits(out, out_size);
}

template <bool is_signed, typename T, typename BitAccessor = DefaultBitAccessor<T, is_signed>>
void bv_sub(T* out, uint32_t out_size, const T* lhs, uint32_t lhs_size, const T* rhs, uint32_t rhs_size) {
  static constexpr uint32_t WORD_SIZE = bitwidth_v<T>;

  if (out_size <= WORD_SIZE
   && lhs_size <= WORD_SIZE
   && rhs_size <= WORD_SIZE) {
    bv_sub_scalar<is_signed, T, BitAccessor>(out, out_size, lhs, lhs_size, rhs, rhs_size);
  } else {
    bv_sub_vector<is_signed, T, BitAccessor>(out, out_size, lhs, lhs_size, rhs, rhs_size);
  }
}

///////////////////////////////////////////////////////////////////////////////

template <typename T>
void bv_umul(T* out, uint32_t out_size,
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
void bv_mul_scalar(T* out, uint32_t out_size,
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
void bv_mul_vector(T* out, uint32_t out_size,
                    const T* lhs, uint32_t lhs_size,
                    const T* rhs, uint32_t rhs_size) {
  if constexpr (is_signed) {
    static constexpr uint32_t WORD_SIZE  = bitwidth_v<T>;

    const T *u(lhs), *v(rhs);
    std::vector<T> uv, vv;

    uint32_t num_words = ceildiv(out_size, WORD_SIZE);

    if (lhs_size < out_size && bv_is_neg(u, lhs_size)) {
      uv.resize(num_words);
      bv_pad<true>(uv.data(), out_size, u, lhs_size);
      u = uv.data();
      lhs_size = out_size;
    }

    if (rhs_size < out_size && bv_is_neg(v, rhs_size)) {
      vv.resize(num_words);
      bv_pad<true>(vv.data(), out_size, v, rhs_size);
      v = vv.data();
      rhs_size = out_size;
    }

    bv_umul(out, out_size, u, lhs_size, v, rhs_size);
  } else {
    bv_umul(out, out_size, lhs, lhs_size, rhs, rhs_size);
  }
}

template <bool is_signed, typename T>
void bv_mul(T* out, uint32_t out_size,
             const T* lhs, uint32_t lhs_size,
             const T* rhs, uint32_t rhs_size) {
  static constexpr uint32_t WORD_SIZE  = bitwidth_v<T>;
  assert(out_size <= lhs_size + rhs_size);

  if (out_size <= WORD_SIZE
   && lhs_size <= WORD_SIZE
   && rhs_size <= WORD_SIZE) {
    bv_mul_scalar<is_signed>(out, out_size, lhs, lhs_size, rhs, rhs_size);
  } else {
    bv_mul_vector<is_signed>(out, out_size, lhs, lhs_size, rhs, rhs_size);
  }
}

///////////////////////////////////////////////////////////////////////////////

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

  auto m  = ceildiv<int>(bv_msb(lhs, lhs_size) + 1, XWORD_SIZE);
  auto n  = ceildiv<int>(bv_msb(rhs, rhs_size) + 1, XWORD_SIZE);
  auto qn = ceildiv<int>(quot_size, XWORD_SIZE);
  auto rn = ceildiv<int>(rem_size, XWORD_SIZE);

  auto u = reinterpret_cast<const xword_t*>(lhs);
  auto v = reinterpret_cast<const xword_t*>(rhs);
  auto q = reinterpret_cast<xword_t*>(quot);
  auto r = reinterpret_cast<xword_t*>(rem);

  if (0 == n) {
    throw std::runtime_error("divide by zero");
  }

  // reset the outputs
  if (qn) {
    std::fill_n(q, qn, 0);
  }
  if (rn) {
    std::fill_n(r, rn, 0);
  }

  // early exit
  if (m <= 0 || m < n) {
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

    // muliply and subtract
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
      uv.resize(ceildiv(lhs_size, WORD_SIZE));
      bv_neg_vector<is_signed, T, ClearBitAccessor<T>>(uv.data(), lhs_size, u, lhs_size);
      u = uv.data();
    }

    if (bv_is_neg(v, rhs_size)) {
      vv.resize(ceildiv(rhs_size, WORD_SIZE));
      bv_neg_vector<is_signed, T, ClearBitAccessor<T>>(vv.data(), rhs_size, v, rhs_size);
      v = vv.data();
    }

    T* r = nullptr;
    bv_udiv(out, out_size, r, 0, u, lhs_size, v, rhs_size);
    if (bv_is_neg_vector(lhs, lhs_size) ^ bv_is_neg_vector(rhs, rhs_size)) {
      bv_neg_vector<is_signed, T, ClearBitAccessor<T>>(out, out_size, out, out_size);
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

///////////////////////////////////////////////////////////////////////////////

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
      uv.resize(ceildiv(lhs_size, WORD_SIZE));
      bv_neg_vector<is_signed, T, ClearBitAccessor<T>>(uv.data(), lhs_size, u, lhs_size);
      u = uv.data();
    }

    if (bv_is_neg(v, rhs_size)) {
      vv.resize(ceildiv(rhs_size, WORD_SIZE));
      bv_neg_vector<is_signed, T, ClearBitAccessor<T>>(vv.data(), rhs_size, v, rhs_size);
      v = vv.data();
    }

    T* q = nullptr;
    bv_udiv(q, 0, out, out_size, u, lhs_size, v, rhs_size);
    if (bv_is_neg_vector(lhs, lhs_size)) {
      bv_neg_vector<is_signed, T, ClearBitAccessor<T>>(out,out_size,  out, out_size);
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
