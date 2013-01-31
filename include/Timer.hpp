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
#include <cmath>
#include <string>
#include <chrono>
using std::string;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::high_resolution_clock;

#ifndef TIMER_HPP
#define TIMER_HPP

namespace isa {
namespace utils {

class Timer {
public:
		Timer(string name);

	void start();
	void stop();
	void reset();

	inline double getTotalTime() const;
	inline double getLastRunTime() const;
	inline double getAverageTime() const;
	inline double getStdDev() const;

private:
	string name;
	high_resolution_clock::time_point starting;
	unsigned int nrRuns;
	double totalTime;
	double time;
	double average;
	double variance;
};


// Implementation

Timer::Timer(string name) : name(name), starting(high_resolution_clock::time_point()), nrRuns(0), totalTime(0.0), time(0.0), average(0.0), variance(0.0) {}

void Timer::start() {
	starting = high_resolution_clock::now();
}

void Timer::stop() {
	time = (duration_cast< duration< double > >(high_resolution_clock::now() - starting)).count();
	totalTime += time;
	nrRuns++;
	
	if ( nrRuns == 1 ) {
		average = time;
		variance = 0.0;
	} else {
		double oldAverage = average;

		average = oldAverage + ((time - oldAverage) / nrRuns);
		variance += ((time - oldAverage) * (time - average));
	}
}

void Timer::reset() {
	starting = high_resolution_clock::time_point();
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

#endif // TIMER_HPP

