#ifndef COUNTER_H
#define COUNTER_H

#include <unordered_map>
#include <vector>
#include <utility>

template <class Key, class Hash>
class Counter {
 private:
  std::unordered_map< Key, int, Hash > counts_;
  double total_;
  
 public:
 Counter()
   : counts_(),
    total_(0)
    {};

  bool contains( Key k );
  void add( Key k );
  int get( Key k );
  std::vector<Key> keys();
  std::vector<int> values();
  std::vector<std::pair<Key, int>> counts();
  std::vector<std::pair<Key, double>> normalized_counts();
};

#endif // COUNTER_H