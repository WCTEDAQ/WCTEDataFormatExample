#ifndef BIT_FUNCTIONS_H
#define BIT_FUNCTIONS_H

#include <cstdint>

// When start and end are compile-time constants, these functions compile into
// efficient code. Make them templates?
inline uint64_t bits(const uint8_t* data, int start, int end) __attribute__((always_inline));
inline uint64_t bits(uint64_t value, int start, int end) __attribute__((always_inline));
inline void set_bits(uint8_t* data, int start, int end, uint64_t value) __attribute__((always_inline));
inline uint64_t set_bits(uint64_t value, int start, int end, uint64_t bits) __attribute__((always_inline));

// Treats data as a little-endian number and extracts bits [start:end]
// (inclusive) from it
inline uint64_t bits(const uint8_t* data, int start, int end) {
  int is = start / 8; // index of the start byte
  int bs = start % 8; // first bit in the start byte
  int ie = end   / 8; // index of the end byte
  int be = end   % 8; // last bit in the ending byte
  unsigned x = data[ie] & 0xFF >> 7 - be;
  if (ie == is) return x >> bs;
  for (int i = ie; --i > is;) x = x << 8 | data[i];
  return x << 8 - bs | data[is] >> bs;
};

// Treats data as a little-endian number and sets bits [start:end] (inclusive)
// to value
// XXX: gcc-13.2.1 doesn't want to inline this function without the declaration above.
inline void set_bits(uint8_t* data, int start, int end, uint64_t value) {
  int is = start / 8;
  int bs = start % 8;
  int ie = end   / 8;
  int be = end   % 8;

  value <<= bs;
  if (ie == is) {
    uint8_t mask = ~(0xFF << (be + 1 - bs)) << bs;
    data[ie] = data[ie] & ~mask | value & mask;
  } else {
    data[is] = data[is] & 0xFF >> 8 - bs | value;
    for (int i = is + 1; i < ie; ++i) {
      value >>= 8;
      data[i] = value;
    };
    uint8_t mask = 0xFF >> 7 - be;
    data[ie] = value >> 8 & mask | data[ie] & ~mask;
  };
};

// Extracts bits [start:end] (inclusive) from value
inline uint64_t bits(uint64_t value, int start, int end) {
  return (value & (1ULL << end + 1) - 1) >> start;
};

// Sets bits [start:end] (inclusive) in value to bits
inline uint64_t set_bits(uint64_t value, int start, int end, uint64_t bits) {
  uint64_t mask = ~(~1ULL << end - start) << start;
  return value & ~mask | bits << start & mask;
};

#endif
