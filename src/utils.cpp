// Copyright 2015 Alessio Sclocco <a.sclocco@vu.nl>
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

#include <utils.hpp>

namespace isa {
namespace utils {

std::string * replace(std::string * src, std::string placeholder, std::string & value, bool deleteSrc) {
	std::string *toRet = new std::string();
	size_t pos = 0;
	size_t oldPos = 0;

	while ( (pos = src->find(placeholder, pos)) < std::string::npos ) {
		toRet->append(src->substr(oldPos, pos - oldPos));
		toRet->append(value);
		pos += placeholder.length();
		oldPos = pos;
	}
	toRet->append(src->substr(oldPos));

	if ( deleteSrc ) {
		delete src;
	}

	return toRet;
}

void bigEndianToLittleEndian(char * value) {
	unsigned int bitMap = *(reinterpret_cast< unsigned int * >(value));

	bitMap = ((bitMap >> 8) & 0x00ff00ff) | ((bitMap << 8) & 0xff00ff00);
	bitMap = ((bitMap >> 16) & 0x0000ffff) | ((bitMap << 16) & 0xffff0000);

	*value = bitMap;
}

} // utils
} // isa

