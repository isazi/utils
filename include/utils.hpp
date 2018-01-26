///
/// \file utils.hpp
/// \brief Collection of simple utilities.
///
/// All simple utilities contained in isa::utils.
///

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

///
/// \fn std::string * replace(std::string * src, const std::string & placeholder, const std::string & item, bool deleteSrc = false)
/// \brief Replace all of the placeholder occurrences in the source string with some value.
///
/// @param src Pointer to the string to modify
/// @param placeholder The placeholder to replace in the input string
/// @param item The content to replace the placeholder with
/// @param deleteSrc Enable freeing of source string
/// @return A pointer to the generate string
///
std::string * replace(std::string * src, const std::string & placeholder, const std::string & item, bool deleteSrc = false);
///
/// \fn template<typename OldType, typename NewType> NewType castToType(const OldType item)
/// \brief Casts the value of a variable from OldType to NewType.
/// This function is intended mainly to convert the value of a string to a numeric type, and it should not be used if more precise casting is possible,
/// such as between numeric types, because precision is not preserved.
///
/// @param item The variable to cast
/// @return The casted value
///
template<typename OldType, typename NewType> NewType castToType(const OldType item);
///
/// \fn template<typename FloatingPointType> bool same(const FloatingPointType result, const FloatingPointType expected, const double error = 1.0e-06)
/// \brief Compare two floating point numbers.
///
/// @param result The number to compare
/// @param expected The expected value to compare with
/// @param error The maximum absolute error between the two numbers
/// @return The value true if the two numbers are the same, false otherwise
///
template<typename FloatingPointType> bool same(const FloatingPointType result, const FloatingPointType expected, const double error = 1.0e-06);
///
/// \fn void bigEndianToLittleEndian(char * value)
/// \brief Change the endianness of a 32 bits variable from big to little, in place.
///
/// @param value A pointer to the variable to modify
///
void bigEndianToLittleEndian(char * value);
///
/// \fn std::uint64_t pad(const std::uint64_t x, const unsigned int padding)
/// \brief Pad the value of a variable to the closest, larger or equal, multiple of a provided padding factor.
///
/// @param x Variable to pad
/// @param padding Padding factor
/// @return Padded value
///
std::uint64_t pad(const std::uint64_t x, const unsigned int padding);
///
/// \fn template<typename Type> std::uint8_t getBit(const Type bitmap, const std::uint8_t bit)
/// \brief Read a specific bit in a variable.
///
/// @param bitmap The input bit field
/// @param bit The position of the bit to access
/// @return The value of the requested bit in the input
///
template<typename Type> std::uint8_t getBit(const Type bitmap, const std::uint8_t bit);
///
/// \fn template<typename Type> void setBit(Type & bitmap, const std::uint8_t newBit, const std::uint8_t bit)
/// \brief Write a specific bit in a variable.
///
/// @param bitmap The input bit field
/// @param newBit The value to write
/// @param bit The position of the bit to set
///
template<typename Type> void setBit(Type & bitmap, const std::uint8_t newBit, const std::uint8_t bit);
///
/// \fn template<typename NumericType> double tera(const NumericType x)
/// \brief Divide the value of the input by 10^12.
///
/// @param x The input value
/// @return The value of the input divided by 10^12
///
template<typename NumericType> double tera(const NumericType x);
///
/// \fn template<typename NumericType> double giga(const NumericType x)
/// \brief Divide the value of the input by 10^9.
///
/// @param x The input value
/// @return The value of the input divided by 10^9
///
template<typename NumericType> double giga(const NumericType x);
///
/// \fn template<typename NumericType> double mega(const NumericType x)
/// \brief Divide the value of the input by 10^6.
///
/// @param x The input value
/// @return The value of the input divided by 10^6
///
template<typename NumericType> double mega(const NumericType x);
///
/// \fn template<typename NumericType> double kilo(const NumericType x)
/// \brief Divide the value of the input by 10^3.
///
/// @param x The input value
/// @return The value of the input divided by 10^3
///
template<typename NumericType> double kilo(const NumericType x);
///
/// \fn template<typename NumericType> double tebi(const NumericType x)
/// \brief Divide the value of the input by 2^40.
///
/// @param x The input value
/// @return The value of the input divided by 2^40
///
template<typename NumericType> double tebi(const NumericType x);
///
/// \fn template<typename NumericType> double gibi(const NumericType x)
/// \brief Divide the value of the input by 2^30.
///
/// @param x The input value
/// @return The value of the input divided by 2^30
///
template<typename NumericType> double gibi(const NumericType x);
///
/// \fn template<typename NumericType> double mebi(const NumericType x)
/// \brief Divide the value of the input by 2^20.
///
/// @param x The input value
/// @return The value of the input divided by 2^20
///
template<typename NumericType> double mebi(const NumericType x);
///
/// \fn template<typename NumericType> double kibi(const NumericType x)
/// \brief Divide the value of the input by 2^10.
///
/// @param x The input value
/// @return The value of the input divided by 2^10
///
template<typename NumericType> double kibi(const NumericType x);


template<typename OldType, typename NewType> NewType castToType(const OldType item) {
  NewType castedValue;

  std::stringstream converter;
  converter << item;
  converter >> castedValue;

  return castedValue;
}

template<typename FloatingPointType> inline bool same(const FloatingPointType result, const FloatingPointType expected, const double error) {
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

template<typename Type> inline std::uint8_t getBit(const Type bitmap, const std::uint8_t bit) {
  return static_cast<std::uint8_t>((bitmap >> bit) & 1);
}

template<typename Type> inline void setBit(Type & bitmap, const std::uint8_t newBit, const std::uint8_t bit) {
  bitmap ^= (-newBit ^ bitmap) & (1 << bit);
}

template<typename NumericType> inline double tera(const NumericType x) {
  return x / 1000000000000.0;
}

template<typename NumericType> inline double giga(const NumericType x) {
  return x / 1000000000.0;
}

template<typename NumericType> inline double mega(const NumericType x) {
  return x / 1000000.0;
}

template<typename NumericType> inline double kilo(const NumericType x) {
  return x / 1000.0;
}

template<typename NumericType> inline double tebi(const NumericType x) {
  return x / 1099511627776.0;
}

template<typename NumericType> inline double gibi(const NumericType x) {
  return x / 1073741824.0;
}

template<typename NumericType> inline double mebi(const NumericType x) {
  return x / 1048576.0;
}

template<typename NumericType> inline double kibi(const NumericType x) {
  return x / 1024.0;
}

} // utils
} // isa

