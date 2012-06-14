/*
 * Copyright (C) 2011
 * Alessio Sclocco <a.sclocco@vu.nl>
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
		string toRet = "OpenCL error: " + message;
		return toRet.c_str();
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
		string toRet = "Switch \"" + opt + "\" not found.";
		return toRet.c_str();
	}

private:
	string opt;
};


class AllocationError : public exception {
public:
	AllocationError(string name) : name(name) {}
	~AllocationError() throw () {}

	const char *what() const throw () {
		string toRet = "Cannot allocate memory for " + name + ".";
		return toRet.c_str();
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

