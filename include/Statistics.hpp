///
/// \file Statistics.hpp
/// \brief 
///
/// Statistics class.
///

// Copyright 2014 Alessio Sclocco <alessio@sclocco.eu>
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

#include <cmath>
#include <limits>

#pragma once

namespace isa {
namespace utils {

///
/// \class Statistics
/// \brief Object to compute statistics of discrete samples.
///
template<typename T> class Statistics {
public:
  ///
  /// \fn Statistics()
  /// \brief Constructor.
  ///
  Statistics();

  ///
  /// \fn void addElement(T element)
  /// \brief Add a new sample to the running statistics.
  ///
  /// @param element The new sample to add to the running statistics
  ///
  void addElement(T element);
  ///
  /// \fn inline void reset()
  /// \brief Reset the internal state of the running statistics.
  ///
  /// This method completely resets the internal state of the running statistics.
  ///
  inline void reset();

  ///
  /// \fn inline std::uint64_t getNrElements() const
  /// \brief Retrieve the number of samples added to the running statistics.
  ///
  /// @return The number of previously added samples
  ///
  inline std::uint64_t getNrElements() const;
  ///
  /// \fn inline double getMean() const
  /// \brief Retrieve the mean of the added samples.
  ///
  /// @return The mean of the previously added samples
  ///
  inline double getMean() const;
  ///
  /// \fn inline double getHarmonicMean() const
  /// \brief Retrieve the harmonic mean of the added samples.
  ///
  /// @return The harmonic mean of the previously added samples
  ///
  inline double getHarmonicMean() const;
  ///
  /// \fn inline double getVariance() const
  /// \brief Retrieve the variance of the added samples.
  ///
  /// @return The variance of the previously added samples
  ///
  inline double getVariance() const;
  ///
  /// \fn inline double getStandardDeviation() const
  /// \brief Retrieve the standard deviation of the added samples.
  ///
  /// @return The standard deviation of the previously added samples
  ///
  inline double getStandardDeviation() const;
  ///
  /// \fn inline double getCoefficientOfVariation() const
  /// \brief Retrieve the coefficient of variation of the added samples.
  ///
  /// The coefficient of variation is defined as the standard deviation divided by the mean.
  ///
  /// @return The coefficient of variation of the previously added samples
  ///
  inline double getCoefficientOfVariation() const;
  ///
  /// \fn inline double getRootMeanSquare() const
  /// \brief Retrieve the root mean square of the added samples.
  ///
  /// The root mean square is defined as the square root of the mean of the squares.
  ///
  /// @return The root mean square of the previously added samples
  ///
  inline double getRootMeanSquare() const;
  ///
  /// \fn inline T getMin() const
  /// \brief Retrieve the minimum of the added samples.
  ///
  /// @return The minimum of the previously added samples
  ///
  inline T getMin() const;
  ///
  /// \fn inline T getMax() const
  /// \brief Retrieve the maximum of the added samples.
  ///
  /// @return The maximum of the previously added samples
  ///
  inline T getMax() const;

private:
  std::uint64_t nrElements;
  double mean;
  double harmonicMean;
  double variance;
  double rms;
  T min;
  T max;
};

template<typename T> Statistics<T>::Statistics() : nrElements(0), mean(0.0), harmonicMean(0.0), variance(0.0), rms(0.0), min(std::numeric_limits<T>::max()), max(std::numeric_limits<T>::min()) {}

template<typename T> void Statistics<T>::addElement(T element) {
    double oldMean = mean;

  nrElements++;

  if ( nrElements == 1 ) {
    mean = static_cast<double>(element);
    harmonicMean = static_cast<double>(1.0 / element);
    rms = static_cast<double>(element * element);
    min = element;
    max = element;
    return;
  }
  mean = oldMean + ((element - oldMean) / nrElements);
  harmonicMean += static_cast<double>(1.0 / element);
  variance += (element - oldMean) * (element - mean);
  rms += static_cast<double>(element * element);

  if ( element < min ) {
    min = element;
  } else if ( element > max ) {
    max = element;
  }
}

template<typename T> inline void Statistics<T>::reset() {
  nrElements = 0;
  mean = 0.0;
  harmonicMean = 0.0;
  variance = 0.0;
  rms = 0.0;
  min = std::numeric_limits<T>::max();
  max = std::numeric_limits<T>::min();
}

template<typename T> inline std::uint64_t Statistics<T>::getNrElements() const {
  return nrElements;
}

template<typename T> inline double Statistics<T>::getMean() const {
  return mean;
}

template<typename T> inline double Statistics<T>::getHarmonicMean() const {
  if ( nrElements > 0 ) {
    return nrElements / harmonicMean;
  } else {
    return 0.0;
  }
}

template<typename T> inline double Statistics<T>::getVariance() const {
  if ( nrElements > 1 ) {
    return variance / (nrElements - 1);
  } else {
    return 0.0;
  }
}

template<typename T> inline double Statistics<T>::getStandardDeviation() const {
  return std::sqrt(this->getVariance());
}

template<typename T> inline double Statistics<T>::getCoefficientOfVariation() const {
  return this->getStandardDeviation() / this->getMean();
}

template<typename T> inline double Statistics<T>::getRootMeanSquare() const {
  return std::sqrt(rms / nrElements);
}

template<typename T> inline T Statistics<T>::getMin() const {
  return min;
}

template<typename T> inline T Statistics<T>::getMax() const {
  return max;
}

} // utils
} // isa

