/**
 * Implementation of a binary search tree.
 *
 * Name: Ajay Nair
 * Email: ajnair@ucsd.edu
 */
#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <iostream>
using namespace std;

template<typename Data>
class BST {

  protected:

    /** Pointer to the root of this BST, or 0 if the BST is empty */
    BSTNode<Data>* root;

    /** Number of Data items stored in this BST. */
    unsigned int isize;

    /** Height of this BST. */
    unsigned int iheight;

  public:

    /** define iterator as an aliased typename for BSTIterator<Data>. */
    typedef BSTIterator<Data> iterator;

    /** Default constructor.
     * Initialize an empty BST.
     */
    BST() : root(0), isize(0), iheight(0) {  }


    /** Default destructor.
     * Delete every node in this BST.
     */
    virtual ~BST() {
      deleteAll(this->root);
    }

    /** Given a reference to a Data item, insert a copy of it in this BST.
     *  Return  true if the item was added to this BST
     *  as a result of this call to insert,
     *  false if an item equal to this one was already in this BST.
     *  Note: This function should use only the '<' operator when comparing
     *  Data items. (should not use ==, >, <=, >=)  For the reasoning
     *  behind this, see the assignment writeup.
     */
    virtual bool insert(const Data& item) {
      if(!root) {
        this->root = new BSTNode<Data>(item);
        isize++;
        return true;
      }

      BSTNode<Data>* cur = this->root;
      bool leftTraverse;
      int curHeight = 0;
      while((leftTraverse = item < cur->data) || cur->data < item) {
        curHeight++;
        if(leftTraverse) {
          if(!cur->left) {
            cur->left = new BSTNode<Data>(item);
            cur->left->parent = cur;
            this->isize++;
            if(curHeight > this->iheight) {
              this->iheight = curHeight;
            }
            return true;
          }
          cur = cur->left;
        }
        else {
          if(!cur->right) {
            cur->right = new BSTNode<Data>(item);
            cur->right->parent = cur;
            this->isize++;
            if(curHeight > this->iheight) {
              this->iheight = curHeight;
            }
            return true;
          }
          cur = cur->right;
        }
      }
      return false;
    }


    /** Find a Data item in the BST.
     *  Return an iterator pointing to the item, or pointing past
     *  the last node in the BST if not found.
     *  Note: This function should use only the '<' operator when comparing
     *  Data items. (should not use ==, >, <=, >=).  For the reasoning
     *  behind this, see the assignment writeup.
     */
    virtual iterator find(const Data& item) const {
      if(this->isize == 0) {
        return this->end();
      }

      BSTNode<Data>* cur = root;
      while(cur) {
        if(item < cur->data) {
          cur = cur->left;
        }
        else if(cur->data < item) {
          cur = cur->right;
        }
        else {
          return BST<Data>::iterator(cur);
        }
      }

      return this->end();
    }


    /** Return the number of items currently in the BST.
    */
    unsigned int size() const {
      return this->isize;
    }

    /** Return the height of the BST.
     * The height of an empty tree is -1 and the height of a tree
     * with only one node is 0.
     */
    unsigned int height() const {
      return this->iheight;
    }


    /** Return true if the BST is empty, else false.
    */
    bool empty() const {
      return this->isize == 0;
    }

    /** Return an iterator pointing to the first item in the BST (not the root).
    */
    iterator begin() const {
      return BST<Data>::iterator(first(this->root));
    }

    /** Return an iterator pointing past the last item in the BST.
    */
    iterator end() const {
      return BST<Data>::iterator(0);
    }


    /** Inorder traverse BST, print out the data of each node in ascending order.
     * Implementing inorder and deleteAll base on the pseudo code is an easy way to get started.
     * Pseudo Code:
     * if current node is null: return;
     * recursively traverse left sub-tree
     * print current node data
     * recursively traverse right sub-tree
     */
    void inorder() const {
      inorderRecurse(this->root);
    }


  private:

    /** Find the first element of the BST
    */ 
    static BSTNode<Data>* first(BSTNode<Data>* root) {
      if(!root) {
        return nullptr;
      }

      BSTNode<Data>* cur = root;
      while(cur->left) {
        cur = cur->left;
      }
      return cur;
    }

    /** do a postorder traversal, deleting nodes
    */
    static void deleteAll(BSTNode<Data>* n) {
      /* Pseudo Code:
         if current node is null: return;
         recursively delete left sub-tree
         recursively delete right sub-tree
         delete current node
         */
      if(!n) {
        return;
      }
      deleteAll(n->left);
      deleteAll(n->right);
      delete n;
    }

    static void inorderRecurse(BSTNode<Data>* n) {
      if(!n) {
        return;
      }
      inorderRecurse(n->left);
      cout << n->data << endl;
      inorderRecurse(n->right);
    }
};


#endif //BST_HPP
