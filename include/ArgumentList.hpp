/*
 * Copyright (C) 2010
 * Alessio Sclocco <alessio@sclocco.eu>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
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
#include <list>
using std::list;
#include <typeinfo>

#include <utils.hpp>
#include <Exceptions.hpp>
using isa::Exceptions::EmptyCommandLine;
using isa::Exceptions::SwitchNotFound;


#ifndef ARGUMENT_LIST_HPP
#define ARGUMENT_LIST_HPP

namespace isa {

namespace utils {

class ArgumentList {
public:
	ArgumentList(int argc, char *argv[]);
	~ArgumentList();

	string getName();
	template< typename T > T getFirst() throw(EmptyCommandLine);
	bool getSwitch(const string opt) throw(EmptyCommandLine);
	template< typename T > T getSwitchArgument(const string opt) throw(EmptyCommandLine, SwitchNotFound);

private:
	list< string > args;
	string name;
};


// Implementations

ArgumentList::ArgumentList(int argc, char *argv[]) {
	name = string(argv[0]);

	for ( int i(1); i < argc; i++ ) {
		string temp = string(argv[i]);
		args.push_back(temp);
	}
}


ArgumentList::~ArgumentList() {
}


string ArgumentList::getName() {
	return name;
}


template< typename T > T ArgumentList::getFirst() throw(EmptyCommandLine) {
	if ( args.empty() ) {
		throw EmptyCommandLine();
	}

	string temp = args.front();
	args.pop_front();
	return castToType< string, T >(temp);
}


bool ArgumentList::getSwitch(const string opt) throw(EmptyCommandLine) {
	if ( args.empty() ) {
		return false;
	}

	for ( list< string >::iterator s = args.begin(); s != args.end(); s++ ) {
		if ( opt.compare(*s) == 0 ) {
			args.erase(s);
			return true;
		}
	}

	return false;
}


template< class T > T ArgumentList::getSwitchArgument(const string opt) throw(EmptyCommandLine, SwitchNotFound) {
	T retVal;
	
	if ( args.empty() ) {
		throw EmptyCommandLine();
	}

	for ( list< string >::iterator s = args.begin(); s != args.end(); s++ ) {
		if ( opt.compare(*s) == 0 ) {
			string temp = *(++s);
			retVal = castToType< string, T >(temp);

			args.erase(s);
			args.erase(--s);
			return retVal;
		}
	}

	throw SwitchNotFound(opt);
}

} // utils
} // isa

#endif // ARGUMENT_LIST_HPP

