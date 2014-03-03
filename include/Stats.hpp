//
// Copyright (C) 2014
// Alessio Sclocco <alessio@sclocco.eu>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#include <cmath>


#ifndef STATS_HPP
#define STATS_HPP

namespace isa {
namespace utils {

template< typename T > class Stats {
public:
	Stats();
	~Stats();

	inline void addElement(T element);
	inline void reset();

	inline long long unsigned int getNrElements() const;
	inline double getAverage() const;
	inline double getVariance() const;
	inline double getStdDev() const;

private:
	long long unsigned int nrElements;
	double average;
	double variance;
};

// Implementations

template< typename T > Stats< T >::Stats() : nrElements(0), average(0.0), variance(0.0) {}

template< typename T > Stats< T >::~Stats() {}

template< typename T > inline void Stats< T >::addElement(T element) {
	double oldAverage = average;
	
	nrElements++;

	if ( nrElements == 1 ) {
		average = static_cast< double >(element);
		return;
	}
	average = oldAverage + ((element - oldAverage) / nrElements);
	variance += (element - oldAverage) * (element - average);
}

template< typename T > inline void Stats< T >::reset() {
	nrElements = 0;
	average = 0.0;
	variance = 0.0;
}

template< typename T > inline long long unsigned int Stats< T >::getNrElements() const {
	return nrElements;
}

template< typename T > inline double Stats< T >::getAverage() const {
	return average;	
}

template< typename T > inline double Stats< T >::getVariance() const {
	return variance;
}

template< typename T > inline double Stats< T >::getStdDev() const {
	return sqrt(variance / nrElements);
}

} // utils
} // isa

#endif
