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
#include <chrono>

#include <Stats.hpp>


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

	inline unsigned int getNrRuns() const;
	inline double getTotalTime() const;
	inline double getLastRunTime() const;
	inline double getAverageTime() const;
	inline double getStandardDeviation() const;
  inline double getCoefficientOfVariation() const;

private:
  Stats< double > stats;
  std::chrono::high_resolution_clock::time_point starting;
	double totalTime;
	double time;
};

} // utils
} // isa

#endif // TIMER_HPP

