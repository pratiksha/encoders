#include "encoding-tree.h"
#include "sample-utils.h"

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

vector<double> random_dist() {
  vector<double> ret;
  int start = 1000;

  while ( start > 0 ) {
    auto next = SampleUtils::uniform_int( 1, start );
    ret.push_back( next );
    start -= next;
  }

  return ret;
}

int main() {
  for ( int i = 0; i < 10000; i++ ) {
    auto dist = random_dist();
    sort( dist.begin(), dist.end(), greater<double>() );
    shared_ptr<EncodingTree> htree = EncodingTree::construct_huffman( dist );
    shared_ptr<EncodingTree> sftree = EncodingTree::construct_sf( dist );
    if ( htree->expected_length() != sftree->expected_length() ) {
      auto h_cws = htree->codewords();
      auto sf_cws = sftree->codewords();
      cout << (h_cws[0].second.size() > sf_cws[0].second.size()) << " " << h_cws[0].second.size() << " " << sf_cws[0].second.size() << endl;
      cout << endl;
    }
  }
}