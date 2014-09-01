// Copyright 2011 Alessio Sclocco <a.sclocco@vu.nl>
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
#include <exception>
using std::exception;

#include <utils.hpp>


#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

namespace isa {

namespace Exceptions {

class OpenCLError : public exception {
public:
	OpenCLError(string message) : message(message) {}
	~OpenCLError() throw () {}

	const char *what() const throw () {
		return message.c_str();
	}

private:
	string message;
};


class EmptyCommandLine : public exception {
public:
	const char *what() const throw () {
		return "Empty command line.";
	}
};


class SwitchNotFound : public exception {
public:
	SwitchNotFound(string opt) : opt(opt) {}
	~SwitchNotFound() throw () {}

	const char *what() const throw () {
		return ("Switch \"" + opt + "\" not found.").c_str();
	}

private:
	string opt;
};


class AllocationError : public exception {
public:
	AllocationError(string name) : name(name) {}
	~AllocationError() throw () {}

	const char *what() const throw () {
		return ("Cannot allocate memory for " + name + ".").c_str();
	}

private:
	string name;
};


class InvalidStartingPoint : public exception {
public:
	const char *what() const throw () {
		return "Starting point must be less or equal than the period.";
	}
};

} // Exceptions
} // isa

#endif // EXCEPTIONS_HPP

