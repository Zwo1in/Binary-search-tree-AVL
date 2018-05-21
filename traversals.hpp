#ifndef BST_TRAVERSALS_
#define BST_TRAVERSALS_

#include <iostream>
#include "bst_node.hpp"
#include "bst_excepts.hpp"

namespace bst {
    // recives pointer to root
    // Pass through the tree in given order: current node, left child, right child
    template< class var >
    void preOrder( bst::Node< var >* node ) {
        if ( node == nullptr )
            throw Exceptions(1);
        std::cout << *node << std::endl;
        if ( node -> getLeft() != nullptr )
            preOrder( node -> getLeft() );
        if ( node -> getRight() != nullptr )
            preOrder( node -> getRight() );
    }

    // recives pointer to root
    // Pass through the tree in given order: left child, current node, right child
    // returns all elements in rising order 
    template< class var >
    void inOrder( bst::Node< var >* node ) {
        if ( node == nullptr )
            throw Exceptions(1);
        if ( node -> getLeft() != nullptr )
            inOrder( node -> getLeft() );
        std::cout << *node << std::endl;
        if ( node -> getRight() != nullptr )
            inOrder( node -> getRight() );
    }

    // recives pointer to root
    // Pass through the tree in given order: left child, right child, current node
    template< class var >
    void postOrder( bst::Node< var >* node ) {
        if ( node == nullptr )
            throw Exceptions(1);
        if ( node -> getLeft() != nullptr )
            postOrder( node -> getLeft() );
        if ( node -> getRight() != nullptr )
            postOrder( node -> getRight() );
        std::cout << *node << std::endl;
    }
}

#endif