// Copyright 2010 Alessio Sclocco <alessio@sclocco.eu>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <string>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <cinttypes>

#pragma once

namespace isa {
namespace utils {

// Replace all occurrences of "placeholder" in string "src" with the value of "item"
std::string * replace(std::string * src, const std::string & placeholder, const std::string & item, bool deleteSrc = false);
// Casts value from N to T
template<typename N, typename T> T castToType(const N value);
// Compare two numbers
template<typename T> bool same(const T result, const T expected, const double error = 1.0e-06);
// Modify (in place) the endianness of a 32 bits value
void bigEndianToLittleEndian(char * value);
// Pad x to be a multiple of padding
std::uint64_t pad(const std::uint64_t x, const unsigned int padding);
// Bit operations
template<typename T> std::uint8_t getBit(const T value, const std::uint8_t bit);
template<typename T> void setBit(T & bitmap, const std::uint8_t newBit, const std::uint8_t bit);
// Divide x by 10^12
double tera(const std::uint64_t x);
// Divide x by 10^9
double giga(const std::uint64_t x);
// Divide x by 10^6
double mega(const std::uint64_t x);
// Divide x by 10^3
double kilo(const std::uint64_t x);
// Divide x by 2^40
double tebi(const std::uint64_t x);
// Divide x by 2^30
double gibi(const std::uint64_t x);
// Divide x by 2^20
double mebi(const std::uint64_t x);
// Divide x by 2^10
double kibi(const std::uint64_t x);


template<typename N, typename T> T castToType(const N value) {
  T castedValue;

  std::stringstream converter;
  converter << value;
  converter >> castedValue;

  return castedValue;
}

template<typename T> inline bool same(const T result, const T expected, const double error) {
  return std::abs(result - expected) < error;
}

// Implementation from http://stackoverflow.com/questions/2782725/converting-float-values-from-big-endian-to-little-endian
inline void bigEndianToLittleEndian(char * value) {
	unsigned int bitmap = *(reinterpret_cast<unsigned int *>(value));

	bitmap = ((bitmap >> 8) & 0x00ff00ff) | ((bitmap << 8) & 0xff00ff00);
	bitmap = ((bitmap >> 16) & 0x0000ffff) | ((bitmap << 16) & 0xffff0000);

	*value = bitmap;
}

inline std::uint64_t pad(const std::uint64_t x, const unsigned int padding) {
  if ( (x % padding) == 0 ) {
    return x;
  } else {
    return static_cast<std::uint64_t>(padding * std::ceil(x / static_cast<double>(padding)));
  }
}

template<typename T> inline std::uint8_t getBit(const T value, const std::uint8_t bit) {
  return static_cast<std::uint8_t>((value >> bit) & 1);
}

template<typename T> inline void setBit(T & bitmap, const std::uint8_t newBit, const std::uint8_t bit) {
  bitmap ^= (-newBit ^ bitmap) & (1 << bit);
}

inline double tera(const std::uint64_t x) {
  return x / 1000000000000.0;
}

inline double giga(const std::uint64_t x) {
  return x / 1000000000.0;
}

inline double mega(const std::uint64_t x) {
  return x / 1000000.0;
}

inline double kilo(const std::uint64_t x) {
  return x / 1000.0;
}

inline double tebi(const std::uint64_t x) {
  return x / 1099511627776.0;
}

inline double gibi(const std::uint64_t x) {
  return x / 1073741824.0;
}

inline double mebi(const std::uint64_t x) {
  return x / 1048576.0;
}

inline double kibi(const std::uint64_t x) {
  return x / 1024.0;
}

} // utils
} // isa

