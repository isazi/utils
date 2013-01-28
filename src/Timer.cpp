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

#include <Timer.hpp>

#include <cmath>
#include <ctime>
using std::sqrt;
using std::clock;

namespace isa {
namespace utils {

Timer::Timer() : starting(0), nrRuns(0), totalTime(0.0), time(0.0), average(0.0), variance(0.0) {}

void Timer::start() {
	starting = clock();
}

void Timer::stop() {
	time = (starting - static_cast< double >(clock())) / CLOCKS_PER_SEC;
	totalTime += time;
	nrRuns++;
	starting = 0;
	
	if ( nrRuns == 1 ) {
		average = time;
		variance = 0.0;
	}
	else {
		double oldAverage = average;
		double oldVariance = variance;

		average = oldAverage + ((time - oldAverage) / nrRuns);
		variance = oldVariance + ((time - oldAverage) * (time - average));
	}
}

void Timer::reset() {
	starting = 0;
	nrRuns = 0;
	totalTime = 0.0;
	time = 0.0;
	average = 0.0;
	variance = 0.0;
}

inline double Timer::getTotalTime() const {
	return totalTime;
}

inline double Timer::getLastRunTime() const {
	return time;
}

inline double Timer::getAverageTime() const {
	return average;
}

inline double Timer::getStdDev() const {
	return sqrt(variance / nrRuns);
}

} // utils
} // isa

