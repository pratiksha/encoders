#include "counter.h"

using namespace std;

template <class Key, class Hash>
bool Counter<Key, Hash>::contains( Key k ) {
  auto it = counts_.find( k );
  if ( it != counts_.end() ) return true;
  return false;
}

template <class Key, class Hash>
void Counter<Key, Hash>::add( Key k ) {
  if ( contains( k ) ) {
    counts_[k] = counts_[k] + 1;
  } else {
    counts_[k] = 1;
  }
  total_ += 1;
}

template <class Key, class Hash>
int Counter<Key, Hash>::get( Key k ) {
  if ( contains ( k ) ) {
    return counts_[k];
  }
  
  return -1;
}

template <class Key, class Hash>
vector<pair<Key, int>> Counter<Key, Hash>::counts() {
  vector<pair<Key, int>> ret;
  for ( auto kv : counts_ ) {
    ret.emplace_back( kv );
  }
  return ret;
}

template <class Key, class Hash>
vector<Key> Counter<Key, Hash>::keys() {
  vector<Key> ret;
  for ( auto kv : counts_ ) {
    ret.push_back( kv.first );
  }
  return ret;
}

template <class Key, class Hash>
vector<int> Counter<Key, Hash>::values() {
  vector<int> ret;
  for ( auto kv : counts_ ) {
    ret.push_back( kv.second );
  }
  return ret;
}

template <class Key, class Hash>
vector<pair<Key, double>> Counter<Key, Hash>::normalized_counts() {
  vector<pair<Key, double>> ret;
  for ( auto kv : counts_ ) {
    ret.emplace_back( kv.first, kv.second / total_ );
  }
  return ret;
}