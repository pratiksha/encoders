#include "shannon-fano.h"
#include "huffman.h"

#include <iostream>
#include <memory>
#include <vector>

using namespace std;

int main() {
  vector<double> test( {15, 7, 6, 6, 5} );
  shared_ptr<HuffmanTree> tree = HuffmanTree::construct_tree( test );

  cout << tree->str() << endl;
}