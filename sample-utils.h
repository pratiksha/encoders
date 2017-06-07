#ifndef SAMPLE_UTILS_H
#define SAMPLE_UTILS_H

#include <utility>
#include <vector>

#include "random.h"

namespace SampleUtils {
  std::vector<double> normalize( std::vector<int> counts );
  std::vector<double> normalize( std::vector<double> counts );
  double counts_entropy( std::vector<int> counts );
  double mean( std::vector<std::pair<double, double>> dist );
  
  int uniform_int( int range );

  /* assumes dist is sorted */
  std::pair<std::vector<double>, std::vector<double>> split_even( std::vector<double> dist );
}

#endif // SAMPLE_UTILS_H