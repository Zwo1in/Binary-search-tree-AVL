#ifndef AVL_TREE_
#define AVL_TREE_

// Maciej Zwoliński
// 21 / 05 / 2018

// My implementation of an AVl binary search tree
// An avl is a tree that automatically keeps balance
// so for each node the difference of heights of left and right subtrees cannot differ more done 1

// While creating this I supported myself with this guy's channel
// https://www.youtube.com/user/RobEdwardsSDSU 


#include <iostream>
#include "bst_excepts.hpp"
#include "bst_node.hpp"

namespace bst {
    // Avl class
    template< class var >
    class Avl {
        Node< var >* root;
        int size;

        // recursive methods not accessible from outsiade of the class
        // rotations
        void rightRotate( Node< var >& );
        void leftRotate( Node< var >& );
        void leftRightRotate( Node< var >& );
        void rightLeftRotate( Node< var >& );
        // checking height of a subtree
        int height( Node< var >* );
        // rebalancing method
        void rebalance( Node< var >& );
        // checking tree's balance
        void balanceCheck( Node< var >& );
        // adding an element to the subtree
        void add( Node< var >&, unsigned int, var);
        // removing an element
        void remove( Node< var >* );
        // free tree's memory
        void empty( Node< var >* );

    public:
        Avl();
        ~Avl();

        // returns size
        int getSize();
        // returns true if empty
        bool isEmpty();
        // returns root
        Node< var >* getRoot();
        // returns tree height
        int height();
        // adds node to the tree
        void add( unsigned int, var );
        // removes node of given key from the tree
        Node< var > remove( unsigned int );
        // returns pointer to node of given key
        Node< var >* find( unsigned int );
        // free tree's memory
        void empty();
    };
}

template< class var >
bst::Avl< var >::Avl() { 
    root = nullptr; size = 0; 
}

template< class var >
bst::Avl< var >::~Avl() { 
    empty(); 
}

// Right rotation
// Needed if after adding or removing node, there are too much nodes in the left child's left subtree
// Rotates left child over the current node clockwise
template< class var >
void bst::Avl< var >::rightRotate( bst::Node< var >& node ) {
    // tmp pointer to the left child
    auto tmp = node.getLeft();

    // set tmp's right child as a node left child
    node.setLeft( tmp -> getRight() );
    if ( tmp -> getRight() != nullptr )
        tmp -> getRight() -> setParent( &node );

    // setting tmp as a new child of nodes parent
    tmp -> setParent( node.getParent() );
    if ( node.getParent() != nullptr ) {
        if ( node.getParent() -> getLeft() != nullptr ) {
            if ( *( node.getParent() -> getLeft() ) == node )
                node.getParent() -> setLeft( tmp );
            else
                node.getParent() -> setRight( tmp );
        } else
            node.getParent() -> setRight( tmp );
    } else
        root = tmp;

    // setting node as a new tmp's right child
    tmp -> setRight( &node );
    node.setParent( tmp );
}

// Left rotation
// Needed if after adding or removing node, there are too much nodes in the right child's right subtree
// Rotates right child over the current node counterclockwise
template< class var >
void bst::Avl< var >::leftRotate( bst::Node< var >& node ) {
    // tmp pointer to the right child
    auto tmp = node.getRight();

    // set tmp's left child as a node right child
    node.setRight( tmp -> getLeft() );
    if ( tmp -> getLeft() != nullptr )
        tmp -> getLeft() -> setParent( &node );

    // setting tmp as a new child of nodes parent
    tmp -> setParent( node.getParent() );
    if ( node.getParent() != nullptr ) {
        if ( node.getParent() -> getLeft() != nullptr ) {
            if ( *( node.getParent() -> getLeft() ) == node )
                node.getParent() -> setLeft( tmp );
            else
                node.getParent() -> setRight( tmp );
        } else
            node.getParent() -> setRight( tmp );
    } else
        root = tmp;

    // setting node as a new tmp's right child
    tmp -> setLeft( &node );
    node.setParent( tmp );
}

// Left -> Right rotation
// Needed if after adding or removing node, there are too much nodes in the left child's right subtree
// results in rotating right child of node's left child, over node's left child counterclockwise
// and then rotates the new left son over the node clockwise
template< class var >
void bst::Avl< var >::leftRightRotate( bst::Node< var >& node ) {
    leftRotate( *node.getLeft() );
    rightRotate( node );
}

// Right -> Left rotation
// Needed if after adding or removing node, there are too much nodes in the right child's left subtree
// results in rotating left child of node's right child, over node's right child clockwise
// and then rotates the new right son over the node counterclockwise
template< class var >
void bst::Avl< var >::rightLeftRotate( bst::Node< var >& node ) {
    rightRotate( *node.getRight() );
    leftRotate( node );
}

// returns height of the highest node's subtree
// it calls itself recursively for both child and returns 0 if find the end
// then it goes back, chooses highest of the both subtrees and returns it incremented
template< class var >
int bst::Avl< var >::height( bst::Node< var >* node ) {
    if ( node == nullptr )
        return 0;
    int leftHeight = height( node -> getLeft() )+1;
    int rightHeight = height( node -> getRight() )+1;

    if( leftHeight > rightHeight )
        return leftHeight;
    else
        return rightHeight;
}

// the function that chooses which rotation is needed
template< class var >
void bst::Avl< var >::rebalance( bst::Node< var >& node ) {
    if ( height( node.getLeft() ) < height( node.getRight() ) ) {
        if ( height( node.getRight() -> getRight() ) > height( node.getRight() -> getLeft() ) )
            leftRotate( node );
        else 
            rightLeftRotate( node );
    } else {
        if ( height( node.getLeft() -> getLeft() ) > height( node.getLeft() -> getRight() ) )
            rightRotate( node );
        else 
            leftRightRotate( node );
    }
}

// recursive method of balance checking for node's subtrees
template< class var >
void bst::Avl< var >::balanceCheck( bst::Node< var >& node ) {
    if ( ( height( node.getLeft() ) - height( node.getRight() ) < -1 ) ||
        ( height( node.getLeft() ) - height( node.getRight() ) > 1 ) )
        rebalance( node );
    else if ( node.getParent() != nullptr )
        return balanceCheck( *node.getParent() );
}

// This method checks if the key can be added to the node recursively
// after adding a node it checks the balance
// throws an except if the key already exists
template< class var >
void bst::Avl< var >::add( bst::Node< var >& node, unsigned int key, var value ) {
    if ( node.getKey() == key )
        throw Exceptions(3);
    auto newNode = new Node< var >( key, value );
    if ( key > node.getKey() ) {
        if ( node.getRight() == nullptr ) {
            node.setRight( newNode );
            newNode -> setParent( &node );
        }
        else {
            delete newNode;
            return add( *node.getRight(), key, value );
        }
    } else {
        if ( node.getLeft() == nullptr ) {
            node.setLeft( newNode );
            newNode -> setParent( &node );
        }
        else {
            delete newNode;
            return add( *node.getLeft(), key, value );
        }
    }
    balanceCheck( *newNode );
    size++;
}

// removing given node from tree
// it differs depending on node's children amount
// it automaticaly checks the balance
template< class var >
void bst::Avl< var >::remove( bst::Node< var >* node ) {
    if ( node -> getRight() != nullptr && node -> getLeft() != nullptr ) {
        // tmp pointer for the previous node from in order traversal
        auto tmp = node -> getLeft();
        while ( tmp -> getRight() != nullptr )
            tmp = tmp -> getRight();
        
        node -> setKey( tmp -> getKey() );
        node -> setValue( tmp -> getValue() );
        // delete the tmp and check for balance

        // case 1: while loop hasn't iterated even once
        if ( tmp == node -> getLeft() ) {
            if ( tmp -> getLeft() != nullptr ) {
                node -> setLeft( tmp -> getLeft() );
                tmp -> getLeft() -> setParent( node );
                balanceCheck( *tmp -> getLeft() );
            } else { 
                node -> setLeft( nullptr );
                balanceCheck( *node );
            }
        }
        // case 2: while loop has iterated at least once
        if ( tmp -> getLeft() != nullptr ) {
            tmp -> getLeft() -> setParent( tmp -> getParent() );
            tmp -> getParent() -> setRight( tmp -> getLeft() );
            balanceCheck( *tmp -> getLeft() );
        } else  {
            tmp -> getParent() -> setRight( nullptr );
            balanceCheck( *tmp -> getParent() );
        }
        delete tmp;
    
    // if node had 1 child 
    } else if ( node -> getRight() != nullptr || node -> getLeft() != nullptr ) {
        auto tmp = ( node -> getRight() != nullptr ) ? node -> getRight() : node -> getLeft();
        tmp -> setParent( node -> getParent() );
        if ( node -> getParent() != nullptr ) {
            if ( node -> getParent() -> getKey() < node -> getKey() ) 
                node -> getParent() -> setRight( tmp );
            else
                node -> getParent() -> setLeft( tmp );
        } else
            root = tmp;
        balanceCheck( *tmp );
        delete node;
    // deleting node without children
    } else {
        if ( node -> getParent() != nullptr ) {
            if ( node -> getParent() -> getKey() < node -> getKey() ) 
                node -> getParent() -> setRight( nullptr );
            else
                node -> getParent() -> setLeft( nullptr );
        } else
            root = nullptr;
        balanceCheck( *node -> getParent() );
        delete node;
    }
    size --;
}

// function empties tree in a pre order traversal
template< class var >
void bst::Avl< var >::empty( bst::Node< var >* node ) {
    if ( node == nullptr ) 
        return;
    if ( node -> getLeft() != nullptr ) {
        empty( node -> getLeft() );
    }
    if ( node -> getRight() != nullptr ) {
        empty( node -> getRight() );
    }
    if ( node -> getParent() != nullptr ) {
        if ( node -> getParent() -> getKey() < node -> getKey() ) 
            node -> getParent() -> setRight( nullptr );
        else
            node -> getParent() -> setLeft( nullptr );
    }
    delete node;
    size --;
}

template< class var >
int bst::Avl< var >::getSize() { 
    return size; 
}

template< class var >
bool bst::Avl< var >::isEmpty() { 
    return size? false : true; 
}

template< class var >
bst::Node< var >* bst::Avl< var >::getRoot() { 
    return root; 
}

// the function returns height of the tree + 1 
template< class var >
int bst::Avl< var >::height() {
    if ( root == nullptr )
        return 0;
    else 
        return height( root ) -1;
}

template< class var >
void bst::Avl< var >::add( unsigned int key, var value ) {
    if( root == nullptr ) {
        auto newNode = new Node< var >( key, value );
        root = newNode;
        size++;
    }
    else 
        return add( *root, key, value );
}

template< class var >
bst::Node< var > bst::Avl< var >::remove( unsigned int key ) {
    if ( ! isEmpty() ) {
        auto tmp = find( key );
        remove( tmp );
        return *tmp;
    } else
        throw Exceptions(1);
}

// function finds a node of the given key and returns pointer to it
template< class var >
bst::Node< var >* bst::Avl< var >::find( unsigned int key ) {
    if ( ! isEmpty() ) {
        auto tmp = root;
        while ( tmp != nullptr ) {
            if ( tmp -> getKey() == key )
                return tmp;
            else if ( tmp -> getKey() < key )
                tmp = tmp -> getRight();
            else
                tmp = tmp -> getLeft();
        }
        throw Exceptions(2); 
    } else 
        throw Exceptions(1);
}

template< class var >
void bst::Avl< var >::empty() {
    empty( root );
    root = nullptr;
}

#endif