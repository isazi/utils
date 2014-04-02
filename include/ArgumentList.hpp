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

