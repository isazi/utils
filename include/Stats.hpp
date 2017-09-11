// Copyright 2014 Alessio Sclocco <a.sclocco@vu.nl>
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

template< typename T > class Stats {
public:
  Stats();
  ~Stats();

  void addElement(T element);
  inline void reset();

  inline long long unsigned int getNrElements() const;
  inline double getMean() const;
  inline double getHarmonicMean() const;
  inline double getVariance() const;
  inline double getStandardDeviation() const;
  inline double getCoefficientOfVariation() const;
  inline double getRootMeanSquare() const;
  inline T getMin() const;
  inline T getMax() const;

private:
  long long unsigned int nrElements;
  double mean;
  double harmonicMean;
  double variance;
  double rms;
  T min;
  T max;
};

// Implementations

template< typename T > Stats< T >::Stats() : nrElements(0), mean(0.0), harmonicMean(0.0), variance(0.0), rms(0.0), min(std::numeric_limits< T >::max()), max(std::numeric_limits< T >::min()) {}

template< typename T > Stats< T >::~Stats() {}

template< typename T > void Stats< T >::addElement(T element) {
    double oldMean = mean;

  nrElements++;

  if ( nrElements == 1 ) {
    mean = static_cast< double >(element);
    harmonicMean = static_cast< double >(1.0 / element);
    rms = static_cast< double >(element * element);
    min = element;
    max = element;
    return;
  }
  mean = oldMean + ((element - oldMean) / nrElements);
  harmonicMean += static_cast< double >(1.0 / element);
  variance += (element - oldMean) * (element - mean);
  rms += static_cast< double >(element * element);

  if ( element < min ) {
    min = element;
  } else if ( element > max ) {
    max = element;
  }
}

template< typename T > inline void Stats< T >::reset() {
  nrElements = 0;
  mean = 0.0;
  harmonicMean = 0.0;
  variance = 0.0;
  rms = 0.0;
  min = std::numeric_limits< T >::max();
  max = std::numeric_limits< T >::min();
}

template< typename T > inline long long unsigned int Stats< T >::getNrElements() const {
  return nrElements;
}

template< typename T > inline double Stats< T >::getMean() const {
  return mean;
}

template< typename T > inline double Stats< T >::getHarmonicMean() const {
  if ( nrElements > 0 ) {
    return nrElements / harmonicMean;
  } else {
    return 0.0;
  }
}

template< typename T > inline double Stats< T >::getVariance() const {
  if ( nrElements > 1 ) {
    return variance / (nrElements - 1);
  } else {
    return 0.0;
  }
}

template< typename T > inline double Stats< T >::getStandardDeviation() const {
  return std::sqrt(this->getVariance());
}

template< typename T > inline double Stats< T >::getCoefficientOfVariation() const {
  return this->getStandardDeviation() / this->getMean();
}

template< typename T > inline double Stats< T >::getRootMeanSquare() const {
  return std::sqrt(rms / nrElements);
}

template< typename T > inline T Stats< T >::getMin() const {
  return min;
}

template< typename T > inline T Stats< T >::getMax() const {
  return max;
}

} // utils
} // isa

