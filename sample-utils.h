#ifndef SAMPLE_UTILS_H
#define SAMPLE_UTILS_H

#include <vector>

#include "random.h"

namespace SampleUtils {
  std::vector<double> normalize( std::vector<int> counts );
  std::vector<double> normalize( std::vector<double> counts );
  double counts_entropy( std::vector<int> counts );

  int uniform_int( int range );
}

#endif // SAMPLE_UTILS_H