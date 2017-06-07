#include "encoding-tree.h"
#include "sample-utils.h"

#include <iostream>
#include <memory>
#include <vector>

using namespace std;

int main() {
  vector<double> test( {15, 7, 6, 6, 5} );
  shared_ptr<EncodingTree> tree = EncodingTree::construct_huffman( test );

  auto codewords = tree->codewords();
  for ( auto & x : codewords ) {
    cout << x.first << "\t" << x.second << endl;
  }
  cout << tree->expected_length() << endl;
}