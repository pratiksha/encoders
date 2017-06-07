#include "huffman.h"

#include <queue>
#include <memory>
#include <vector>
#include <utility>

using namespace std;

struct ht_ptr_lt {
  bool operator() (const std::shared_ptr<HuffmanTree>&a,const std::shared_ptr<HuffmanTree>&b) const {
    if (a != nullptr and b != nullptr) return *a < *b;
    return false;
  }
};

shared_ptr<HuffmanTree> construct_tree_large( vector<double> dist ) {
  priority_queue<shared_ptr<HuffmanTree>, vector<shared_ptr<HuffmanTree>>, ht_ptr_lt> pq;
  for ( unsigned int i = 0; i < dist.size(); i++ ) {
    pq.push( make_shared<HuffmanTree>( true, dist[i] ) );
  }
  
  while ( pq.size() > 1 ) {
    auto c1 = pq.top();
    pq.pop();
    auto c2 = pq.top();
    pq.pop();
    pq.push( make_shared<HuffmanTree>( c1, c2 ) );
  }

  return pq.top();
}

shared_ptr<HuffmanTree> HuffmanTree::construct_tree( vector<double> dist ) {
  if ( dist.empty() ) return nullptr;
  
  if ( dist.size() == 1 ) return make_shared<HuffmanTree>( true, dist[0] );
  
  if ( dist.size() == 2 ) {
    auto ch1 = make_shared<HuffmanTree>( true, dist[0] );
    auto ch2 = make_shared<HuffmanTree>( true, dist[1] );
    if ( dist[0] > dist[1] ) {
      return make_shared<HuffmanTree>( ch1, ch2 );
    } else {
      return make_shared<HuffmanTree>( ch2, ch1 );
    }
  }

  return construct_tree_large( dist );
}

string HuffmanTree::str() {
  if ( is_leaf_ ) return to_string( value_ );
  return left_->str() + " " + right_->str();  
}