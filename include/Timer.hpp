///
/// \file Timer.hpp
/// \brief Collection of simple utilities.
///
/// This include file contains the Timer class.
///

// Copyright 2013 Alessio Sclocco <alessio@sclocco.eu>
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

#include "Statistics.hpp"

#pragma once

namespace isa {
namespace utils {

///
/// \class Timer
/// \brief Simple timer.
///
/// This class is used to measure time intervals.
///
class Timer {
public:
  ///
  /// \fn Timer()
  /// \brief Constructor.
  ///
  Timer();

  ///
  /// \fn void start()
  /// \brief Start the timer.
  ///
  void start();
  ///
  /// \fn void stop()
  /// \brief Stop the timer.
  ///
  void stop();
  ///
  /// \fn void reset()
  /// \brief Reset the internal state of the timer.
  ///
  /// This method completely resets the internal state of the timer, deleting all measured intervals.
  ///
  void reset();

  ///
  /// \fn unsigned int getNrRuns() const
  /// \brief Retrieve the number of timed intervals.
  ///
  /// @return The number of timed intervals
  ///
  unsigned int getNrRuns() const;
  ///
  /// \fn double getTotalTime() const
  /// \brief Retrieve the total measured time, in seconds.
  ///
  /// @return The total elapsed time of all timed intervals
  ///
  double getTotalTime() const;
  ///
  /// \fn double getLastRunTime() const
  /// \brief Retrieve the time of the last timed interval, in seconds.
  ///
  /// @return The elapsed time of the last timed interval
  ///
  double getLastRunTime() const;
  ///
  /// \fn double getAverageTime() const
  /// \brief Retrieve the average time between the timed intervals, in seconds.
  ///
  /// @return The average of the timed intervals
  ///
  double getAverageTime() const;
  ///
  /// \fn double getStandardDeviation() const
  /// \brief Retrieve the standard deviation between the timed intervals.
  ///
  /// @return The standard deviation between the timed intervals.
  ///
  double getStandardDeviation() const;
  ///
  /// \fn double getCoefficientOfVariation() const
  /// \brief Retrieve the coefficient of variation between the timed intervals.
  ///
  /// The coefficient of variation is defined as the standard deviation divided by the mean.
  ///
  /// @return The coefficient of variation between the timed intervals
  ///
  double getCoefficientOfVariation() const;

private:
  Statistics<double> stats;
  std::chrono::high_resolution_clock::time_point starting;
  double totalTime;
  double time;
};

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

