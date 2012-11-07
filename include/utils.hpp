/*
 * Copyright (C) 2010
 * Alessio Sclocco <alessio@sclocco.eu>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <string>
using std::string;
#include <sstream>
using std::stringstream;
#include <cstdlib>


#ifndef UTILS_HPP
#define UTILS_HPP

namespace isa {

namespace utils {

// Convert value into a string
template< typename T > string *toString(T value);
template< typename T > inline string toStringValue(T value);

// Replace the occurrences of placeholder in src with value
string *replace(string *src, string placeholder, string value, bool deleteSrc = false);

// Casts value from N to T
template< typename N, typename T > T castToType(N value);

// Compare two single precision floats
inline bool same(const float result, const float expected);

// Divide x by 10^9
inline double giga(long long unsigned int x);

// Divide x by 2^20
inline double mebi(long long unsigned int x);

// Modify the endianness of a 32 bits number
// See http://stackoverflow.com/questions/2782725/converting-float-values-from-big-endian-to-little-endian
void changeEndianness(char *value);


// Implementations

template< typename T > string *toString(T value) {
	string temp = castToType< T, string >(value);
	return new string(temp);
}


template< typename T > inline string toStringValue(T value) {
	return castToType< T, string >(value);
}


template< typename N, typename T > T castToType(N value) {
	T toRet;
	
	stringstream converter;
	converter << value;
	converter >> toRet;

	return toRet;
}


inline bool same(const float result, const float expected) {
	return abs(result - expected) < 1e-6;
}


inline double giga(long long unsigned int x) {
	return x / 1000000000.0;
}


inline double mebi(long long unsigned int x) {
	return x / 1048576.0;
}

} // utils
} // isa

#endif // UTILS_HPP

