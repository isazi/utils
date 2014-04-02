// Copyright 2013 Alessio Sclocco <a.sclocco@vu.nl>
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

#include <ctime>
#include <string>
using std::string;
#include <chrono>
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::high_resolution_clock;

#include <Stats.hpp>


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

	inline unsigned int getNrRuns() const;
	inline double getTotalTime() const;
	inline double getLastRunTime() const;
	inline double getAverageTime() const;
	inline double getStdDev() const;

private:
	Stats< double > stats;
	string name;
	high_resolution_clock::time_point starting;
	double totalTime;
	double time;
};


// Implementation

Timer::Timer(string name) : stats(Stats< double >()), name(name), starting(high_resolution_clock::time_point()), totalTime(0.0), time(0.0) {}

void Timer::start() {
	starting = high_resolution_clock::now();
}

void Timer::stop() {
	time = (duration_cast< duration< double > >(high_resolution_clock::now() - starting)).count();
	totalTime += time;
	stats.addElement(time);
}

void Timer::reset() {
	starting = high_resolution_clock::time_point();
	totalTime = 0.0;
	time = 0.0;
}

inline unsigned int Timer::getNrRuns() const {
	return stats.getNrElements();
}

inline double Timer::getTotalTime() const {
	return totalTime;
}

inline double Timer::getLastRunTime() const {
	return time;
}

inline double Timer::getAverageTime() const {
	return stats.getAverage();
}

inline double Timer::getStdDev() const {
	return stats.getStdDev();
}

} // utils
} // isa

#endif // TIMER_HPP

