#include "encoding-tree.h"
#include "sample-utils.h"

#include <algorithm>
#include <iostream>
#include <queue>
#include <memory>
#include <vector>
#include <utility>

using namespace std;

struct tree_ptr_gt {
  bool operator() (const std::shared_ptr<EncodingTree>&a,const std::shared_ptr<EncodingTree>&b) const {
    if (a != nullptr and b != nullptr) {
      return *a > *b;
    }
    return false;
  }
};

shared_ptr<EncodingTree> EncodingTree::construct_huffman( vector<double> dist ) {
  if ( dist.empty() ) return nullptr;
  
  if ( dist.size() == 1 ) return make_shared<EncodingTree>( true, dist[0] );

  priority_queue<shared_ptr<EncodingTree>, vector<shared_ptr<EncodingTree>>, tree_ptr_gt> pq;
  for ( unsigned int i = 0; i < dist.size(); i++ ) {
    pq.push( make_shared<EncodingTree>( true, dist[i] ) );
  }
  
  while ( pq.size() > 1 ) {
    auto c1 = pq.top();
    pq.pop();
    auto c2 = pq.top();
    pq.pop();
    if ( c1->value_ > c2->value_ ) {
      pq.push( make_shared<EncodingTree>( c1, c2 ) );
    } else {
      pq.push( make_shared<EncodingTree>( c2, c1 ) );
    }
  }

  return pq.top();
}

shared_ptr<EncodingTree> EncodingTree::construct_sf( vector<double> dist ) {
  if ( dist.empty() ) return nullptr;
  
  if ( dist.size() == 1 ) return make_shared<EncodingTree>( true, dist[0] );

  auto split = SampleUtils::split_even( dist );
  auto ch1 = construct_sf( split.first );
  auto ch2 = construct_sf( split.second );
  
  return make_shared<EncodingTree>( ch1, ch2 );
}

double EncodingTree::expected_length() {
  auto cws = codewords();
  vector<pair<double, double>> lengths;
  for ( auto & c : cws ) lengths.emplace_back( c.first, c.second.size() );
  return SampleUtils::mean( lengths );
}

vector<pair<double, string>> EncodingTree::codewords() {
  vector<pair<double, string>> ret;
  if ( is_leaf_ ) {
    ret.emplace_back( value_, "" );
    return ret;
  }

  auto left_words = left_->codewords();
  auto right_words = right_->codewords();
  for ( auto & x : left_words ) {
    ret.emplace_back( x.first, "0" + x.second );
  }
  for ( auto & x : right_words ) {
    ret.emplace_back( x.first, "1" + x.second );
  }

  sort( ret.begin(), ret.end(), std::greater<pair<double, string>>() );
  return ret;
}

string EncodingTree::str() {
  if ( is_leaf_ ) return to_string( value_ );
  return left_->str() + " " + right_->str();
}