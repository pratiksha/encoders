#include "encoding-tree.h"
#include "sample-utils.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <memory>
#include <vector>

using namespace std;

static double epsilon = std::numeric_limits<double>::epsilon();

bool fuzzy_geq( double lhs, double rhs ) {
  return (lhs >= (rhs - epsilon));
}

void print_vec( vector<double> & dist ) {
  for ( auto x : dist ) cout << x << ", ";
  cout << endl;
}

vector<vector<double>> enumerate_dists( vector<double> dist, double step,
                                double maxval, double rem ) {
  vector<vector<double>> ret;
  
  if ( dist.size() == 0 ) {
    ret.emplace_back( dist );
    return ret;
  }

  if ( dist.size() == 1 ) {
    if ( dist[0] - epsilon <= 0 ) {
      ret.emplace_back( dist );
      return ret;
    }

    if ( fuzzy_geq(rem, dist[0]) and (dist[0] <= maxval) ) {
      ret.emplace_back( dist );
      return ret;
    } else {
      return ret;
    }
  }

  while ( dist[0] - maxval > epsilon ) {
    dist[0] -= step;
    dist[1] += step;
  }

  while ( dist[0] >= 0 ) {
    vector<double> tmp( dist.begin() + 1, dist.end() );
    auto suffixes = enumerate_dists( tmp, step, dist[0], rem-dist[0] );
    for ( auto x : suffixes ) {
      x.insert( x.begin(), dist[0] );
      ret.push_back( x );
    }

    dist[0] -= step;
    dist[1] += step;
  }

  return ret;
}

int main() {
  vector<double> start_dist;
  start_dist.push_back(1.0);
  for ( int i = 0; i < 9; i++ ) {
    start_dist.push_back(0.0);
  }
  auto ret = enumerate_dists( start_dist, 0.02, 1.0, 1.0 );

  for ( auto & dist : ret ) {
    shared_ptr<EncodingTree> htree = EncodingTree::construct_huffman( dist );
    shared_ptr<EncodingTree> sftree = EncodingTree::construct_sf( dist );
    auto h_cws = htree->codewords();
    auto sf_cws = sftree->codewords();
    if ( h_cws[0].second.size() > sf_cws[0].second.size() ) {
      print_vec(dist);
      cout << h_cws[0].second.size() << " " << sf_cws[0].second.size() << endl;
      cout << htree->expected_length() << " " << sftree->expected_length() << endl;
    }
  }
}