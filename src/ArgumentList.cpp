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

#include <ArgumentList.hpp>

namespace isa {
namespace utils {

SwitchNotFound::SwitchNotFound(const std::string & option) {
  this->errorMessage = "ERROR: expected switch \"" + option + "\" not found";
}

SwitchNotFound::~SwitchNotFound() noexcept {}

const char * SwitchNotFound::what() const noexcept {
  return this->errorMessage.c_str();
}

ArgumentList::ArgumentList(int argc, char * argv[]) : name(std::string(argv[0])) {
  for ( int i = 1; i < argc; i++ ) {
    args.push_back(std::string(argv[i]));
  }
}

ArgumentList::~ArgumentList() {}

bool ArgumentList::getSwitch(const std::string & option) {
  if ( args.empty() ) {
    return false;
  }

  for ( auto s = args.begin(); s != args.end(); ++s ) {
    if ( option.compare(*s) == 0 ) {
      args.erase(s);
      return true;
    }
  }

  return false;
}

} // utils
} // isa

