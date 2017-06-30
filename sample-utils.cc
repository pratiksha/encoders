#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#include <boost/random/variate_generator.hpp>
#include <cmath>
#include <map>
#include <limits>
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

  if ( sum == 0 ) {
    return counts;
  }

  vector<double> ret;
  for ( double c : counts ) {
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

double SampleUtils::mean( vector<pair<double, double>> dist ) {
  vector<double> ret;
  double sum = 0.0;
  double freq_sum = 0.0;
  for ( auto & x : dist ) {
    sum += (x.first * x.second);
    freq_sum += x.first;
  }
  return sum / freq_sum;
}

int SampleUtils::uniform_int( int range ) {
  boost::random::uniform_int_distribution<> rand( 0, range );
  return rand( Random::global_PRNG() );
}

int SampleUtils::uniform_int( int start, int end ) {
  boost::random::uniform_int_distribution<> rand( start, end );
  return rand( Random::global_PRNG() );
}

pair<vector<double>, vector<double>> SampleUtils::split_even( vector<double> dist ) {
  const auto & norm_dist = SampleUtils::normalize( dist );
  
  double left_sum = 0.0;
  int idx = 0;
  for ( double x : norm_dist ) {
    left_sum += x;
    idx++;
    if ( left_sum > 0.5 ) break;
  }

  if ( left_sum == 0.0 ) {
    idx = dist.size() / 2;
    return make_pair( vector<double>(dist.begin(), dist.begin() + idx),
                      vector<double>(dist.begin() + idx, dist.end()) );
  }
  
  double cmp = left_sum - norm_dist[idx-1];
  //cout << cmp << " " << left_sum << " " << idx << endl;
  if ( (1.0 - cmp - left_sum) < -numeric_limits<double>::epsilon() ) {
    /* break before idx */
    return make_pair( vector<double>(dist.begin(), dist.begin() + idx - 1),
                      vector<double>(dist.begin() + idx - 1, dist.end()) );
  } else {
    /* break after idx */
    return make_pair( vector<double>(dist.begin(), dist.begin() + idx),
                      vector<double>(dist.begin() + idx, dist.end()) );
  }
}