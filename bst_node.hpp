#ifndef BST_NODE_
#define BST_NODE_

#include <iostream>

namespace bst {
    // class for nodes
    template< class var >
    class Node {
        unsigned int key;
        Node< var >* parent;
        Node< var >* left;
        Node< var >* right;
        var value;

    public:
        Node( unsigned int, var);

        // set/gets
        unsigned int getKey();
        void setKey( unsigned int );
        var getValue();
        void setValue( var );
        Node< var >* getParent();
        Node< var >* getLeft();
        Node< var >* getRight();
        void setParent( Node< var >* );
        void setLeft( Node< var >* );
        void setRight( Node< var >* );

        // overloaded operators
        bool operator== ( Node< var > );
        bool operator!= ( Node< var > );
        template< class var_ >
        friend std::ostream& operator<< ( std::ostream& , const Node< var_ >& );
    };
}

template< class var >
bst::Node< var >::Node( unsigned int key_, var value_ ) { 
    key = key_;
    value = value_;
    parent = left = right = nullptr; 
}
template< class var >
unsigned int bst::Node< var >::getKey() {
    return key;
}
template< class var >
void bst::Node< var >::setKey( unsigned int key_ ) { 
    key = key_; 
}
template< class var >
var bst::Node< var >::getValue() { 
    return value; 
}
template< class var >
void bst::Node< var >::setValue( var value_ ) { 
    value = value_; 
}
template< class var >
bst::Node< var >* bst::Node< var >::getParent() { 
    return parent;
 }
template< class var >
bst::Node< var >* bst::Node< var >::getLeft() { 
    return left; 
}
template< class var >
bst::Node< var >* bst::Node< var >::getRight() { 
    return right; 
}
template< class var >
void bst::Node< var >::setParent( bst::Node< var >* parent_ ) { 
    parent = parent_; 
}
template< class var >
void bst::Node< var >::setLeft( bst::Node< var >* left_ ) { 
    left = left_; 
}
template< class var >
void bst::Node< var >::setRight( bst::Node< var >* right_ ) { 
    right = right_; 
}
template< class var >
bool bst::Node< var >::operator== ( bst::Node< var > second ) {
    if ( ( value != second.getValue() ) ||
        ( parent != second.getParent() ) ||
        ( left != second.getLeft() ) ||
        ( right != second.getRight() ) ) 
            return false;
    else 
        return true;
}
template< class var >
bool bst::Node< var >::operator!= ( bst::Node< var > second ) {
    if ( ( value != second.getValue() ) ||
        ( parent != second.getParent() ) ||
        ( left != second.getLeft() ) ||
        ( right != second.getRight() ) ) 
            return true;
    else 
        return false;
}
namespace bst {
    template< class var >
    std::ostream& operator<< ( std::ostream& os, const bst::Node< var >& node ) {
        os << "Key: " << node.key << " Value: " << node.value << std::endl;
        return os;
    }
}

#endif