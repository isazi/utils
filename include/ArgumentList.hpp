///
/// \file ArgumentList.hpp
/// \brief 
///
/// ArgumentList class and related error types.
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
#include <list>
#include <iterator>
#include <exception>
#include <typeinfo>

#include "utils.hpp"

#pragma once

namespace isa {
namespace utils {

///
/// \class EmptyCommandLine
/// \extends std::exception
/// \brief Represents the condition when the command line is empty.
///
class EmptyCommandLine : public std::exception {};
///
/// \class SwitchNotFound
/// \extends std::exception
/// \brief Represents the condition when the requested command line argument has not been passed.
///
class SwitchNotFound : public std::exception {
public:
  ///
  /// \fn explicit SwitchNotFound(const std::string & option)
  /// \brief Constructor.
  ///
  /// @param option The command line argument that was not found
  ///
  explicit SwitchNotFound(const std::string & option);

  ///
  /// \fn const char * what() const
  /// \brief Provides the error message that explains the exception.
  ///
  /// @return A string containing the explanation for the raised exception
  ///
  const char * what() const;

private:
  std::string errorMessage;
};


///
/// \class ArgumentList
/// \brief Object to process and manipulate command line arguments.
///
class ArgumentList {
public:
  ///
  /// \fn ArgumentList(int argc, char * argv[])
  /// \brief Constructor.
  ///
  /// @param argc The number of items on the command line
  /// @param argv An array of strings, each of them an item in the command line
  ///
  ArgumentList(int argc, char * argv[]);

  ///
  /// \fn std::string getName() const
  /// \brief Retrieve the name of the running executable.
  ///
  /// @return A string containing the name of the running executable
  ///
  std::string getName() const;
  ///
  /// \fn template<typename T> T getFirst()
  /// \brief Retrieve the first argument still in the command line buffer.
  ///
  /// @return The first item in the command line buffer that has not been yet retrieved
  ///
  template<typename T> T getFirst();
  ///
  /// \fn bool getSwitch(const std::string & option)
  /// \brief Checks if an option is still in the command line buffer, and removes it from there if it is.
  ///
  /// @param A string containing the wanted command line option
  /// @return True if the option is found, false otherwise
  ///
  bool getSwitch(const std::string & option);
  ///
  /// \fn template<typename T> T getSwitchArgument(const std::string & option)
  /// \brief Retrieve the value passed after a specific command line option.
  ///
  /// @param A string containing the wanted command line option
  /// @return The value that follows the specified command line option
  ///
  template<typename T> T getSwitchArgument(const std::string & option);

private:
  std::list<std::string> args;
  std::string name;
};


inline std::string ArgumentList::getName() const {
  return name;
}

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

} // utils
} // isa

