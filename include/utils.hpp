// Copyright 2010 Alessio Sclocco <a.sclocco@vu.nl>
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
#include <cstdint>


#pragma once

namespace isa {

namespace utils {

// Convert value into a string
template< typename T > std::string toString(T value);
template< typename T > std::string * toStringPointer(T value);

// Replace the occurrences of placeholder in src with value
std::string * replace(std::string * src, std::string placeholder, std::string & value, bool deleteSrc = false);

// Casts value from N to T
template< typename N, typename T > T castToType(N value);

// Compare two single precision floats
bool same(const float result, const float expected, const float error = 1e-6);
// Compare two double precision floats
bool same(const double result, const double expected, const double error = 1e-9);

// Divide x by 10^9
double giga(long long unsigned int x);
// Divide x by 10^6
double mega(long long unsigned int x);
// Divide x by 2^30
double gibi(long long unsigned int x);
// Divide x by 2^20
double mebi(long long unsigned int x);

// Modify the endianness of a 32 bits value
// See http://stackoverflow.com/questions/2782725/converting-float-values-from-big-endian-to-little-endian
void bigEndianToLittleEndian(char * value);

// Pad x to be a multiple of padding
long long unsigned int pad(long long unsigned int x, unsigned int padding);

// Bit operations
template< typename T > inline uint8_t getBit(const T value, const uint8_t bit);
template< typename T > inline void setBit(T & value, const uint8_t newBit, const uint8_t bit);


// Implementations

template< typename T > inline std::string toString(T value) {
  return castToType< T, std::string >(value);
}

template< typename T > inline std::string * toStringPointer(T value) {
  std::string temp = castToType< T, std::string >(value);
  return new std::string(temp);
}

template< typename N, typename T > T castToType(N value) {
  T toRet;

  std::stringstream converter;
  converter << value;
  converter >> toRet;

  return toRet;
}

inline bool same(const float result, const float expected, const float error) {
	return std::abs(result - expected) < error;
}

inline bool same(const double result, const double expected, const double error) {
	return std::abs(result - expected) < error;
}

inline double giga(long long unsigned int x) {
  return x / 1000000000.0;
}

inline double mega(long long unsigned int x) {
  return x / 1000000.0;
}

inline double gibi(long long unsigned int x) {
  return x / 1073741824.0;
}

inline double mebi(long long unsigned int x) {
  return x / 1048576.0;
}

inline long long unsigned int pad(long long unsigned int x, unsigned int padding) {
  if ( (x % padding) == 0 ) {
    return x;
  } else {
    return static_cast< long long unsigned int >(padding * std::ceil(x / static_cast< double >(padding)));
  }
}

template< typename T > inline uint8_t getBit(const T value, const uint8_t bit) {
  return static_cast< uint8_t >((value >> bit) & 1);
}

template< typename T > inline void setBit(T & value, const uint8_t newBit, const uint8_t bit) {
  value ^= (-newBit ^ value) & (1 << bit);
}

} // utils
} // isa

