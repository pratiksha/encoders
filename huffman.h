#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <memory>
#include <string>
#include <vector>

class HuffmanTree {
private:
  std::shared_ptr<HuffmanTree> left_;
  std::shared_ptr<HuffmanTree> right_;

  bool is_leaf_;
  double value_;
  
public:
 HuffmanTree( bool is_leaf, double leaf_value ) :
  left_(),
    right_(),
    is_leaf_( is_leaf ),
    value_( leaf_value )
    {};

 HuffmanTree( std::shared_ptr<HuffmanTree> left,
              std::shared_ptr<HuffmanTree> right ) :
  left_( left ),
    right_( right ),
    is_leaf_( false ),
    value_( left->value() + right->value() )
    {};

  double value() { return value_; }
  
  bool operator==( const HuffmanTree & other ) {
    if ( is_leaf_ ) return value_ == other.value_;

    return ( value_ == other.value_ and
             left_ == other.left_ and
             right_ == other.right_ );
  }

  bool operator<( const HuffmanTree & other ) {
    return value_ < other.value_;
  }

  std::string str();

  static std::shared_ptr<HuffmanTree> construct_tree( std::vector<double> dist );
};

#endif // HUFFMAN_H