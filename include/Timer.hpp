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

#include <chrono>

#include "Stats.hpp"


#pragma once

namespace isa {
namespace utils {

class Timer {
public:
  Timer();

  void start();
  void stop();
  void reset();

  unsigned int getNrRuns() const;
  double getTotalTime() const;
  double getLastRunTime() const;
  double getAverageTime() const;
  double getStandardDeviation() const;
  double getCoefficientOfVariation() const;

private:
  Stats< double > stats;
  std::chrono::high_resolution_clock::time_point starting;
  double totalTime;
  double time;
};

// Implementations

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
  return stats.getMean();
}

inline double Timer::getStandardDeviation() const {
  return stats.getStandardDeviation();
}

inline double Timer::getCoefficientOfVariation() const {
  return stats.getCoefficientOfVariation();
}

} // utils
} // isa

