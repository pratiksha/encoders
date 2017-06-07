#ifndef ENCODING_TREE_H
#define ENCODING_TREE_H

#include <memory>
#include <string>
#include <vector>

class EncodingTree {
 private:
  std::shared_ptr<EncodingTree> left_;
  std::shared_ptr<EncodingTree> right_;

  bool is_leaf_;
  double value_;

 public:
 EncodingTree( bool is_leaf, double leaf_value ) :
  left_(),
    right_(),
    is_leaf_( is_leaf ),
    value_( leaf_value )
    {};

 EncodingTree( std::shared_ptr<EncodingTree> left,
              std::shared_ptr<EncodingTree> right ) :
  left_( left ),
    right_( right ),
    is_leaf_( false ),
    value_( left->value() + right->value() )
    {};

  double value() { return value_; }
  
  bool operator==( const EncodingTree & other ) {
    if ( is_leaf_ ) return value_ == other.value_;

    return ( value_ == other.value_ and
             left_ == other.left_ and
             right_ == other.right_ );
  }

  bool operator<( const EncodingTree & other ) {
    return value_ < other.value_;
  }

  std::string str();
  
  static std::shared_ptr<EncodingTree> construct_huffman( std::vector<double> dist );
  static std::shared_ptr<EncodingTree> construct_sf( std::vector<double> dist );
};

#endif // ENCODING_TREE_H