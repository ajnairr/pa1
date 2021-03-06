/**
 * Implementation of a node object that make up a binary search tree.
 *
 * Name: Ajay Nair
 * Email: ajnair@ucsd.edu
 */
#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iostream>
#include <iomanip>
using namespace std;

template<typename Data>
class BSTNode {

  public:

    /** Constructor.  Initialize a BSTNode with the given Data item, no
     *  parent, and no children.
     */
    BSTNode(const Data & d):left(nullptr), right(nullptr), parent(nullptr),
                            data(d) {}

    BSTNode<Data>* left;
    BSTNode<Data>* right;
    BSTNode<Data>* parent;
    Data const data;   // the const Data in this node.

    /** Return the successor of this BSTNode in a BST, or 0 if none.
     *  PRECONDITION: this BSTNode is a node in a BST.
     *  POSTCONDITION:  the BST is unchanged.
     *  RETURNS: the BSTNode that is the successor of this BSTNode, or 0 if 
     *  there is none.
     */
    BSTNode<Data>* successor() {
      BSTNode<Data>* cur = this;

      if(!cur->right) {
        while(cur->parent) {
          if(cur->parent->left == cur) {
            return cur->parent;
          }
          cur = cur->parent;
        }
        return 0;
      }

      cur = cur->right;
      while(cur->left) {
        cur = cur->left;
      }
      return cur;
    }
};

/** Overload operator<< to print a BSTNode's fields to an ostream. */
template <typename Data>
ostream & operator<<(ostream& stm, const BSTNode<Data> & n) {
  stm << '[';
  stm << setw(10) << &n;                 // address of the BSTNode
  stm << "; p:" << setw(10) << n.parent; // address of its parent
  stm << "; l:" << setw(10) << n.left;   // address of its left child
  stm << "; r:" << setw(10) << n.right;  // address of its right child
  stm << "; d:" << n.data;               // its data field
  stm << ']';
  return stm;
}

#endif // BSTNODE_HPP
