#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#include <boost/random/variate_generator.hpp>
#include <cmath>
#include <map>
#include <vector>
#include <unordered_set>

#include "counter.cc"
#include "random.h"
#include "sample-utils.h"

using namespace std;

static boost::random::uniform_real_distribution<double> uniform( 0, 1 );

vector<double> SampleUtils::normalize( vector<int> counts ) {
  double sum = 0;
  for ( int c : counts ) {
    sum += c;
  }

  vector<double> ret;
  for ( int c : counts ) {
    ret.push_back( c / sum );
  }
  return ret;
}

vector<double> SampleUtils::normalize( vector<double> counts ) {
  double sum = 0;
  for ( double c : counts ) {
    sum += c;
  }

  vector<double> ret;
  for ( int c : counts ) {
    ret.push_back( c / sum );
  }
  return ret;
}

double SampleUtils::counts_entropy( vector<int> counts ) {
  double ent = 0;
  auto normalized = normalize( counts );
  for ( auto v : normalized ) {
    ent += v * log(v);
  }
  return -ent;
}

int SampleUtils::uniform_int( int range ) {
  boost::random::uniform_int_distribution<> rand( 0, range );
  return rand( Random::global_PRNG() );
}