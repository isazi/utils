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
#include <list>
#include <iterator>
#include <exception>
#include <typeinfo>

#include "utils.hpp"


#pragma once

namespace isa {
namespace utils {

// Exception: no items in the command line
class EmptyCommandLine : public std::exception {};
// Exception: requested switch not present
class SwitchNotFound : public std::exception {
public:
  explicit SwitchNotFound(const std::string & option);
  ~SwitchNotFound() noexcept; 

  const char * what() const noexcept;

private:
  std::string errorMessage;
};


// ArgumentList class
class ArgumentList {
public:
  ArgumentList(int argc, char * argv[]);
  ~ArgumentList();

  std::string getName();
  template<typename T> T getFirst();
  bool getSwitch(const std::string & option);
  template<typename T> T getSwitchArgument(const std::string & option);

private:
  std::list<std::string> args;
  std::string name;
};


// Implementations

template<typename T> T ArgumentList::getFirst() {
  if ( args.empty() ) {
    throw EmptyCommandLine();
  }

  std::string temp = args.front();
  args.pop_front();
  return isa::utils::castToType<std::string, T>(temp);
}

template<class T> T ArgumentList::getSwitchArgument(const std::string & option) {
  if ( args.empty() ) {
    throw EmptyCommandLine();
  }
  T retVal;

  for ( auto item = args.begin(); item != args.end(); ++item ) {
    auto next = item;

    if ( option.compare(*item) == 0 ) {
      std::advance(next, 1);
      if ( next == args.end() ) {
        throw SwitchNotFound(option);
      }
      retVal = isa::utils::castToType<std::string, T>(*next);
      std::advance(next, 1);
      args.erase(item, next);
      return retVal;
    }
  }

  throw SwitchNotFound(option);
}

inline std::string ArgumentList::getName() {
  return name;
}

} // utils
} // isa

