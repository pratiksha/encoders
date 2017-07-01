#include "encoding-tree.h"
#include "sample-utils.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <memory>
#include <vector>

using namespace std;

bool fuzzy_geq( double lhs, double rhs ) {
  return (lhs >= (rhs - std::numeric_limits<double>::epsilon()));
}

/* generates skewed distributions */
vector<double> random_dist() {
  vector<double> ret;
  int start = 5000;

  while ( start > 0 ) {
    auto next = SampleUtils::uniform_int( 1, start );
    ret.push_back( next );
    start -= next;
  }

  return ret;
}

void print_vec( vector<double> & dist ) {
  for ( auto x : dist ) cout << x << ", ";
  cout << endl;
}

bool increment( double incr, double max, double start, vector<double> & dist ) {
  bool done = true;

  double allow = max;
  for ( int i = dist.size() - 1; i >= 0; i-- ) {
    if ( fuzzy_geq( dist[i], allow ) ) {
      dist[i] = start;
    } else {
      dist[i] += incr;
      done = false;
      break;
    }
    allow -= dist[i];
  }

  //print_vec(dist);
  return done;
}

void grid_search( int dist_size ) {
  double incr = 0.1;
  double start = 0.1;
  double max = 1.0;
  
  vector<double> dist;
  for ( int i = 0; i < dist_size; i++ ) {
    dist.push_back( start );
  }

  while ( true ) {
    vector<double> norm_dist = SampleUtils::normalize(dist);
    sort(norm_dist.begin(), norm_dist.end(), greater<double>());
    shared_ptr<EncodingTree> htree = EncodingTree::construct_huffman( norm_dist );
    shared_ptr<EncodingTree> sftree = EncodingTree::construct_sf( norm_dist );
    auto h_cws = htree->codewords();
    auto sf_cws = sftree->codewords();
    if ( h_cws[0].second.size() > sf_cws[0].second.size() ) {
      print_vec(norm_dist);
      cout << h_cws[0].second.size() << " " << sf_cws[0].second.size() << endl;
      cout << htree->expected_length() << " " << sftree->expected_length() << endl;
    }

    if ( increment( incr, max, start, dist ) ) break;
  }
}

void vary_max() {
  int arr_size = 100;
  for ( double i = 1; i < 1000; i++ ) {
    vector<double> dist;
    double max = 1 - i/1000;
    dist.push_back( max );
    for ( int j = 0; j < arr_size - 1; j++ ) {
      dist.push_back( (1-max) / (arr_size-1) );
    }
    
    sort( dist.begin(), dist.end(), greater<double>() );
    shared_ptr<EncodingTree> htree = EncodingTree::construct_huffman( dist );
    shared_ptr<EncodingTree> sftree = EncodingTree::construct_sf( dist );
    cout << (htree->expected_length() - sftree->expected_length() <= 0.000001) << " "
         << htree->expected_length() << " " << sftree->expected_length() << endl;
  }
}

void test_lengths() {
  for ( int i = 0; i < 10000; i++ ) {
    auto dist = random_dist();
    sort( dist.begin(), dist.end(), greater<double>() );
    shared_ptr<EncodingTree> htree = EncodingTree::construct_huffman( dist );
    shared_ptr<EncodingTree> sftree = EncodingTree::construct_sf( dist );
    auto h_cws = htree->codewords();
    auto sf_cws = sftree->codewords();
    if ( h_cws[0].second.size() > sf_cws[0].second.size() ) {
      for ( auto x : h_cws ) {
        cout << x.first << "\t" << x.second << endl;
      }
      cout << endl;
      for ( auto x : sf_cws ) {
        cout << x.first << "\t" << x.second << endl;
      }
 
      cout << endl;
      cout << h_cws[0].second.size() << " " << sf_cws[0].second.size() << endl;
      cout << htree->expected_length() << " " << sftree->expected_length() << endl;
    }
  }
}

vector<double> test_dist_1( { 190, 140, 121, 115, 113, 112, 107, 37, 32, 12, 11, 9, 1 } );
vector<double> test_dist_2( { 343, 314, 302, 26, 11, 4 } );
vector<double> test_dist_3( { 160, 152, 142, 110, 108, 92, 72, 56, 46, 26, 19, 7, 6, 3, 1 } );
vector<double> test_dist_4( { 169, 164, 139, 113, 98, 95, 81, 52, 48, 20, 19, 2 } );
vector<double> test_dist_5( { 838, 775, 705, 595, 498, 406, 379, 313, 211, 149, 55, 32, 17, 15, 12 } );

vector<double> test_dist_6( { 0.18, 	0.16, 	0.14, 	0.14, 	0.12, 	0.1, 	0.08, 	0.08 } );
vector<double> test_dist_7( { 0.18, 	0.16, 	0.14, 	0.14, 	0.1, 	0.1, 	0.1, 	0.08 } );
vector<double> test_dist_8( { 0.16, 	0.14, 	0.14, 	0.14, 	0.14, 	0.12, 	0.1, 	0.06,   } );
vector<double> test_dist_9( { 0.18, 	0.16, 	0.14, 	0.14 } );
vector<double> test_dist_10( { 0.16, 	0.14, 	0.14, 	0.14, 	0.14, 	0.1, 	0.1, 	0.08 } );
vector<double> test_dist_11( { 0.16, 	0.14, 	0.14, 	0.14, 	0.14, 	0.12, 	0.08, 	0.08 } );
vector<vector<double>> test_dists( { test_dist_1,
      // test_dist_2,
      test_dist_3,
      test_dist_4,
      test_dist_5
      } );


void testcase( vector<double> dist ) {
  vector<double> norm_dist = SampleUtils::normalize(dist);
  sort(norm_dist.begin(), norm_dist.end(), greater<double>());
  
  shared_ptr<EncodingTree> htree = EncodingTree::construct_huffman( norm_dist );
  shared_ptr<EncodingTree> sftree = EncodingTree::construct_sf( norm_dist );
  cout << "getting huffman cws..." << endl;
  auto h_cws = htree->codewords();
  cout << "done huffman cws" << endl;
  auto sf_cws = sftree->codewords();
  print_vec(norm_dist);
  cout << endl;
  //if ( h_cws[0].second.size() > sf_cws[0].second.size() ) {
    cout << h_cws[0].first << " " << sf_cws[0].first << endl;
    cout << h_cws[0].second << " " << sf_cws[0].second << endl;
    cout << h_cws[0].second.size() << " " << sf_cws[0].second.size() << endl;
    cout << htree->expected_length() << " " << sftree->expected_length() << endl;
    //}
}

void testcase_vary( vector<double> dist ) {
  for ( double i = dist[3]; i < dist[1]; i++ ) {
    dist[2] = i;
    vector<double> norm_dist = SampleUtils::normalize(dist);
    sort(norm_dist.begin(), norm_dist.end(), greater<double>());

    shared_ptr<EncodingTree> htree = EncodingTree::construct_huffman( dist );
    shared_ptr<EncodingTree> sftree = EncodingTree::construct_sf( dist );
    auto h_cws = htree->codewords();
    auto sf_cws = sftree->codewords();
    if ( h_cws[0].second.size() > sf_cws[0].second.size() ) {
      cout << i << "\t";
      for ( auto x : norm_dist ) cout << x << " ";
      cout << endl;
    }
  }
  cout << endl;
}

int main() {
  testcase( test_dist_10 ); // huffman is greater
  testcase( test_dist_11 ); // same
}