/*
 * Copyright (C) 2013
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

#include <ctime>

#ifndef TIMER_HPP
#define TIMER_HPP

namespace isa {
namespace utils {

class Timer {
public:
	Timer();

	void start();
	void stop();
	void reset();

	inline double getTotalTime() const;
	inline double getLastRunTime() const;
	inline double getAverageTime() const;
	inline double getStdDev() const;

private:
	clock_t starting;
	unsigned int nrRuns;
	double totalTime;
	double time;
	double average;
	double variance;
};

} // utils
} // isa

#endif // TIMER_HPP

