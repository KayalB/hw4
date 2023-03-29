#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

using namespace std;
/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO

    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;


    void printSpecificNode() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.
    void clearHelper(Node<Key, Value>* current); //TODO



    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    static Node<Key, Value>* successor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.




    int recursiveBalancedCall(Node<Key, Value>* current, bool* failed) const; //TODO

protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
: current_(ptr)
{
    // TODO
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
: current_(nullptr)
{
    // TODO
}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::iterator::operator==
(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // for(iterator)
    return this->current_ == rhs.current_;
    //  && this->getValue() == rhs->getValue();
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::iterator::operator!=
(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return !(this->current_ == rhs.current_);

}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{

    // TODO
    current_ = successor(current_);
    return *this;

}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
: root_(nullptr)
{
    // TODO
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
    clear();
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{


  Node<Key, Value>* newNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, nullptr);
  Node<Key, Value>* temp = this->root_;
  if(this->root_ == nullptr){
    this->root_ = newNode;
    return;
  }  



  while(temp != nullptr){
    if(newNode->getKey() < temp->getKey()){
      if(temp->getLeft() == nullptr){
        temp->setLeft(newNode);
        newNode->setParent(temp);
        return;
      }
    temp = temp->getLeft();
    }
    else if(temp->getKey() < newNode->getKey()){
      // cout << "---   1   ---" << endl;
      // cout << "INSERTING " << keyValuePair.first << endl;
      // cout << temp->getKey() << endl;
      // cout << "Past Priting temp->getKey()" << endl;
      // this->printRoot(this->root_);
      // cout << "---   2  ---" << endl;
      if(temp->getRight() == nullptr){
        temp->setRight(newNode);
        newNode->setParent(temp);
        return;
      }
    temp = temp->getRight();
    }
    else{
      temp->setValue(keyValuePair.second);
      delete newNode;
      return;
    }
  }




    

}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO
    /******
    void remove(const Key& key) : This function will remove the node with the 
    specified key from the tree. There is no guarantee the tree is balanced 
    before or after the removal. If the key is not already in the tree, this function 
    will do nothing. If the node to be removed has two children, swap with its 
    predecessor (not its successor) in the BST removal algorithm. If the node to 
    be removed has exactly one child, you can promote the child. You may NOT just 
    swap key,value pairs. You must swap the actual nodes by changing pointers, but 
    we have given you a helper function to do this in the BST class: swapNode(). 
    Runtime of removal should be O(h).
    ******/
    // cout << "---------" << endl;
    // this->printRoot(this->root_);
    // cout << "Node to delete: " << key << endl;
    // cout << "---------" << endl;

    if(root_ == nullptr){
        return;
    }
    Node<Key, Value>* temp = root_;
    // if(internalFind(temp->getKey()) == nullptr){
    //     return;
    // }

    while(true){
        if(temp == nullptr){
          return;
        }
        if(temp->getKey() == key){
            break;
        }
        if(temp->getKey() > key){
            temp = temp->getRight();
        }
        else{
            temp = temp->getLeft();
        }
    }
    // If it has no children
    if(temp->getLeft() == nullptr && temp->getRight() == nullptr){
      // if root is the only one, we need to set it equal to null
        if(root_ == temp){
          delete temp;
          root_ = nullptr;
        }
        else {delete temp;}
        return;
    }
    // If it only has 1 child to the right
    if(temp->getLeft() == nullptr){

        //Set the child's parent to temp's parent
        temp->getRight()->setParent(temp->getParent());
        
        // If Temp is the root
        if(temp->getParent() == nullptr){
          root_ = temp->getRight();
        }
        // If temp is a left child
        else if(temp->getParent()->getLeft() == temp){

            // Set the parent's left to the child
            temp->getParent()->setLeft(temp->getRight());

        }
        // If temp is a right child
        else{
            // Set the parent's right to the child
            temp->getParent()->setRight(temp->getRight());

        }

        delete temp;

        return;
    }
    // If it only has 1 child to the left
    else if (temp->getRight() == nullptr){

        //Set the child's parent to temp's parent
        temp->getLeft()->setParent(temp->getParent());
        // If Temp is the root
        if(temp->getParent() == nullptr){
          root_ = temp->getLeft();
        }

        // If temp is a right child
        else if(temp->getParent()->getRight() == temp){

            // Set the parent's Right to the child
            temp->getParent()->setRight(temp->getLeft());

        }
        // If temp is a left child
        else{
            // Set the parent's left to the child
            temp->getParent()->setLeft(temp->getLeft());

        }


        delete temp;
        return;
    }
    //If it has 2 nodes
    else{
        // cout << "1" << endl;
        cout << predecessor(temp)->getKey() << endl;
        nodeSwap(temp, predecessor(temp));
        // cout << "NODES Have Been Swapped" << endl;
        // cout << "Root: " << root_->getKey() << endl;
        // cout << "Left: " << root_->getLeft()->getKey() << endl;
        // cout << "Right: " << root_->getRight()->getKey() << endl;
        // this->printRoot(this->root_);

        if(temp->getLeft() == nullptr && temp->getRight() == nullptr){
          // cout << "?" << endl;
          if(temp->getParent()->getLeft() == temp){
            temp->getParent()->setLeft(nullptr);
          }
          else{
            temp->getParent()->setRight(nullptr);
          }
          delete temp;
          this->printRoot(this->root_);
          cout << "!" << endl;
          return;
        }

        if(temp->getLeft() == nullptr){

        //Set the child's parent to temp's parent
        temp->getRight()->setParent(temp->getParent());
        
        // If Temp is the root
        if(temp->getParent() == nullptr){
          root_ = temp->getRight();
        }
        // If temp is a left child
        else if(temp->getParent()->getLeft() == temp){
                          cout << "5" << endl;


            // Set the parent's left to the child
            temp->getParent()->setLeft(temp->getRight());

        }
        // If temp is a right child
        else{
                          cout << "6" << endl;

            // Set the parent's right to the child
            temp->getParent()->setRight(temp->getRight());

        }
                cout << "9" << endl;

        delete temp;

        return;
    }
    // If it only has 1 child to the left
    else if (temp->getRight() == nullptr){
                cout << "3" << endl;

        //Set the child's parent to temp's parent
        temp->getLeft()->setParent(temp->getParent());
        // If Temp is the root
        if(temp->getParent() == nullptr){
          root_ = temp->getLeft();
        }

        // If temp is a right child
        else if(temp->getParent()->getRight() == temp){

            // Set the parent's Right to the child
            temp->getParent()->setRight(temp->getLeft());

        }
        // If temp is a left child
        else{
            // Set the parent's left to the child
            temp->getParent()->setLeft(temp->getLeft());

        }


        delete temp;
        return;
    }
    }




}



template<class Key, class Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO

    /******
    If left child exists, predecessor is the right most node of the left subtree

    Else walk up the ancestor chain until you traverse the first right child pointer (find
    the first node who is a right child of his 25 parent...that parent is the predecessor)

    If you get to the root w/o finding a node who is a right child, there is no predecessor
    ******/

    if (current == nullptr){
      return nullptr;
    }

    Node<Key, Value>* temp = current;
    // If left child Exists
    if(temp->getLeft() != nullptr){
      // Go left one
      temp = temp->getLeft();
      // Keep going right
      while(temp->getRight() != nullptr){
        temp = temp->getRight();
      }
      // Return rightmost child
      return temp;
    }

    // If no left child
    if(current->getLeft() == nullptr){
      bool turned = false;
      // While We are not at the root
      while(temp->getParent() != nullptr){
        // If it is a left child
        if(temp == temp->getParent()->getLeft()){
          // Go Up
          temp = temp->getParent();
        }
        // If it is a right child
        else{
          // Signify that we found it
          turned = true;
          break;
        }
      }
      if(turned){
        // getParent bcause it was stil a child
        return temp->getParent();
      }
      // If we got to the head and we never found a right child
      else{
        return nullptr;
      }
    }
    return nullptr;


}





template<class Key, class Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current)
{
    // TODO

    /******
    If left child exists, predecessor is the right most node of the left subtree

    Else walk up the ancestor chain until you traverse the first right child pointer (find
    the first node who is a right child of his 25 parent...that parent is the predecessor)

    If you get to the root w/o finding a node who is a right child, there is no predecessor
    ******/

    if (current == nullptr){
      return nullptr;
    }

    Node<Key, Value>* temp = current;
    // If right child Exists
    if(temp->getRight() != nullptr){
      // Go right one
      temp = temp->getRight();
      // Keep going left
      while(temp->getLeft() != nullptr){
        temp = temp->getLeft();
      }
      // Return leftmost child
      return temp;
    }

    // If no right child
    if(current->getRight() == nullptr){
      bool turned = false;
      // While We are not at the root
      while(temp->getParent() != nullptr){
        // If it is a right child
        if(temp == temp->getParent()->getRight()){
          // Go Up
          temp = temp->getParent();
        }
        // If it is a Left child
        else{
          // Signify that we found it
          turned = true;
          break;
        }
      }
      if(turned){
        // getParent bcause it was stil a child
        return temp->getParent();
      }
      // If we got to the head and we never found a right child
      else{
        return nullptr;
      }
    }
    return nullptr;
}



/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
  clearHelper(root_);   
  root_ = nullptr; 
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clearHelper(Node<Key, Value>* current){
  if(current == nullptr){
    return;
  }
  clearHelper(current->getLeft());
  clearHelper(current->getRight());

  delete current;
  
}



/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
    Node<Key, Value>* temp = root_;
    if(temp == nullptr){
      return nullptr;
    }

    while(temp->getLeft() != nullptr){
      temp = temp->getLeft();
    }

    return temp;

}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    Node<Key, Value>* temp = root_;
    if(temp == nullptr){
      return nullptr;
    }
    while(temp != nullptr){
      if(key < temp->getKey()){
        temp = temp->getLeft();
      }
      else if (key > temp->getKey()){
        temp = temp->getRight();
      }
      else{
        return temp;
      }
    }
    return nullptr;
}
/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
    if(root_ == nullptr){
        return true;
    }
    if(root_->getLeft() == nullptr && root_->getRight() == nullptr){
        return true;
    }
    bool passed = true;
    int temp = recursiveBalancedCall(root_, &passed);
    if(1 == 0){
        cout << temp << endl;
    }
    return passed;
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::recursiveBalancedCall(Node<Key, Value>* current, bool* passed) const
{
    // TODO
    if(current == nullptr){
        return 0;
    }

    int leftDepth = recursiveBalancedCall(current->getLeft(), passed);
    int rightDepth = recursiveBalancedCall(current->getRight(), passed);

    if(*passed == false){
        return 1;
    }

    if(leftDepth - rightDepth > 1 || leftDepth - rightDepth < -1){
        *passed = false;
    }

    if(leftDepth > rightDepth){
        return 1 + leftDepth;
    }
    return 1 + rightDepth;
}




template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif



