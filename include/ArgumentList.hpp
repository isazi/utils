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
#include <list>
#include <typeinfo>

#include <utils.hpp>


#ifndef ARGUMENT_LIST_HPP
#define ARGUMENT_LIST_HPP

namespace isa {
namespace utils {

// Exception: no items in the command line
class EmptyCommandLine : public std::exception {};
// Exception: requested switch not present
class SwitchNotFound : public std::exception {
public:
  SwitchNotFound(std::string option);
  ~SwitchNotFound() throw ();

  const char *what() const throw ();

private:
  std::string option;
};


// ArgumentList class
class ArgumentList {
public:
	ArgumentList(int argc, char * argv[]);
	~ArgumentList();

  std::string getName();
	template< typename T > T getFirst() throw(EmptyCommandLine);
	bool getSwitch(const std::string & option) throw(EmptyCommandLine);
	template< typename T > T getSwitchArgument(const std::string & option) throw(EmptyCommandLine, SwitchNotFound);

private:
  std::list< std::string > args;
  std::string name;
};


// Implementations

SwitchNotFound::SwitchNotFound(std::string option) : option(option) {}

const char * SwitchNotFound::what() throw() {
  return ("Switch \"" + option + "\" not found.").c_str();
}

ArgumentList::ArgumentList(int argc, char * argv[]) {
  name = std::string(argv[0]);

  for ( unsigned int i = 1; i < argc; i++ ) {
    args.push_back(std::string(argv[1]));
  }
}

std::string ArgumentList::getName() {
	return name;
}

template< typename T > T ArgumentList::getFirst() throw(EmptyCommandLine) {
	if ( args.empty() ) {
		throw EmptyCommandLine();
	}

  std::string temp = args.front();
	args.pop_front();
	return castToType< std::string, T >(temp);
}


bool ArgumentList::getSwitch(const std::string & option) throw(EmptyCommandLine) {
	if ( args.empty() ) {
		return false;
	}

	for ( std::list< std::string >::iterator s = args.begin(); s != args.end(); ++s ) {
		if ( option.compare(*s) == 0 ) {
			args.erase(s);
			return true;
		}
	}

	return false;
}


template< class T > T ArgumentList::getSwitchArgument(const std::string & option) throw(EmptyCommandLine, SwitchNotFound) {
	if ( args.empty() ) {
		throw EmptyCommandLine();
	}

	for ( std::list< std::string >::iterator s = args.begin(); s != args.end(); ++s ) {
		if ( option.compare(*s) == 0 ) {
      std::string temp = *(++s);
			T retVal = castToType< std::string, T >(temp);

			args.erase(s);
			args.erase(--s);
			return retVal;
		}
	}

	throw SwitchNotFound(option);
}

} // utils
} // isa

#endif // ARGUMENT_LIST_HPP

