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

#include <utils.hpp>

namespace isa {

namespace utils {

string *replace(string *src, string placeholder, string value, bool deleteSrc) {
	string *toRet = new string();
	size_t pos = 0;
	size_t oldPos = 0;

	while ( (pos = src->find(placeholder, pos)) < string::npos ) {
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

} // utils
} // isa

