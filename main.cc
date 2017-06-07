#include "encoding-tree.h"

#include <iostream>
#include <memory>
#include <vector>

using namespace std;

int main() {
  vector<double> test( {15, 7, 6, 6, 5} );
  shared_ptr<EncodingTree> tree = EncodingTree::construct_huffman( test );

  cout << tree->str() << endl;
}