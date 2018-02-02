// Copyright 2015 Alessio Sclocco <alessio@sclocco.eu>
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

std::string * replace(std::string * src, const std::string & placeholder, const std::string & item, bool deleteSrc) {
	auto * newString = new std::string();
	size_t position = 0;
	size_t oldPosition = 0;

	while ( (position = src->find(placeholder, position)) < std::string::npos ) {
		newString->append(src->substr(oldPosition, position - oldPosition));
		newString->append(item);
		position += placeholder.length();
		oldPosition = position;
	}
	newString->append(src->substr(oldPosition));

	if ( deleteSrc ) {
		delete src;
	}

	return newString;
}

} // utils
} // isa

