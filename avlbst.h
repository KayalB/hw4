#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int getBalance () const;
    void setBalance (int balance);
    void updateBalance(int diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO

    void printSpecificNode(int directions[]) const;

protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void insert_fix (AVLNode<Key,Value>* n2,  AVLNode<Key,Value>* n1); // TODO
    // void removeFix(AVLNode<Key,Value>* n2,  int diff); // TODO

    void rotateRight(AVLNode<Key,Value>* grandparent);
    void rotateLeft(AVLNode<Key,Value>* grandparent);
    AVLNode<Key, Value>* getPredecessor(AVLNode<Key, Value>* current); // TODO


};



template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::getPredecessor(AVLNode<Key, Value>* current){
    if (current == nullptr){
      return nullptr;
    }

    AVLNode<Key, Value>* temp = current;
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





template<typename Key, typename Value>
void AVLTree<Key, Value>::printSpecificNode(int directions[]) const
{
    int direction = directions[0];
    AVLNode<Key, Value>* temp = static_cast<AVLNode<Key, Value>*>(this->root_);
    int i = 0;
    while(direction != 0){
      if(direction == 1){
        temp = temp->getRight();
      }
      else{
        temp = temp->getLeft();
      }
      i++;
      direction = directions[i];
    }
    std::cout << "Balanace of Key: " << temp->getKey() << " is " << temp->getBalance() << endl;
    std::cout << "\n";
}












/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &newpair)
{
    // TODO
  // cout << "INSERTING " << newpair.first << endl;
  // this->printRoot(this->root_);

  if(this->root_ == nullptr){
    this->root_ = new AVLNode<Key, Value>(newpair.first, newpair.second, nullptr);
    return;
  }  

  // cout << "LEFT HEIGHT: " << getSubtreeHeight(this->root_->getLeft(), 0) << endl;
  // cout << "RIGHT HEIGHT: " << getSubtreeHeight(this->root_->getRight(), 0) << endl;

  AVLNode<Key, Value>* temp = static_cast<AVLNode<Key, Value>*>(this->root_);
    // cout << "========= ROOT BALANCE: " << temp->getBalance() << " ==========" << endl;

  while(true){
    // If it finds a key thats the same
    if(temp->getKey() == newpair.first){
      // Overwrite it and exit
      temp->setValue(newpair.second);
      return;
    }
    // If its greater than the current node
    if(newpair.first > temp->getKey()){
      // If it has a right child, go to the right
      if(temp->getRight() != nullptr){
        temp = temp->getRight();
      }
      // If it doesnt have a right child
      else{
        AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(newpair.first, newpair.second, temp);
        temp->setRight(newNode);
        break;
      }
    }
    // If its less than the current node
    if(newpair.first < temp->getKey()){
      // If it has a left child, go to the left
      if(temp->getLeft() != nullptr){
        temp = temp->getLeft();
      }
      // If it doesnt have a left child
      else{
        AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(newpair.first, newpair.second, temp);
        temp->setLeft(newNode);
        break;
      }
    }
  }

  if(temp->getBalance() == -1 || temp->getBalance() == 1){
    temp->setBalance(0);
    return;
  }
  if(temp->getBalance() == 0){
    if(newpair.first < temp->getKey()){
      temp->updateBalance(-1);
      insert_fix(temp, temp->getLeft());
    }
    else{
      temp->updateBalance(1);
      insert_fix(temp, temp->getRight());
    }
  }



  // if(getSubtreeHeight(this->root_->getLeft(), 0) > getSubtreeHeight(this->root_->getRight(), 0) + 1){
  //   insert_fix(temp->getLeft(), temp->getLeft()->getLeft());
  // }
  // if(getSubtreeHeight(this->root_->getRight(), 0) > getSubtreeHeight(this->root_->getLeft(), 0) + 1){
  //   insert_fix(temp->getRight(), temp->getLeft()->getRight());
  // }

  // cout << "LEFT HEIGHT: " << getSubtreeHeight(this->root_->getLeft(), 0) << endl;
  // cout << "RIGHT HEIGHT: " << getSubtreeHeight(this->root_->getRight(), 0) << endl;

}

template<class Key, class Value>
void AVLTree<Key, Value>::insert_fix(AVLNode<Key,Value>* parent, AVLNode<Key,Value>* child){
  if(parent == nullptr){
    return;
  }
  if(parent->getParent() == nullptr){
    return;
  }
  AVLNode<Key,Value>* grandparent = parent->getParent();
  //If its to the left
  int direction = 0;
  if(grandparent->getLeft() == parent){
      direction = -1;
  }
  else{
      direction = 1;
  }
  grandparent->updateBalance(direction);

  if(grandparent->getBalance() == 0){
      return;
  }
  else if (grandparent->getBalance() == -1 || grandparent->getBalance() == 1){
      insert_fix(grandparent, parent);
  }
  else{
      if((grandparent->getLeft() == parent && parent->getLeft() == child) || (grandparent->getRight() == parent && parent->getRight() == child)){
        if(parent->getRight() == child){
            rotateLeft(grandparent);
        }
        else{
            rotateRight(grandparent);
        }
      parent->setBalance(0);
      grandparent->setBalance(0);
      }
      else{
        if(grandparent->getLeft() == parent){
            rotateLeft(parent);
            rotateRight(grandparent);
        }
        else{
            rotateRight(parent);
            rotateLeft(grandparent);
        }
        if(direction == -1){
            if(child->getBalance() == -1){
                parent->setBalance(0);
                grandparent->setBalance(1);
                child->setBalance(0);
            }
            else if(child->getBalance() == 0){
                parent->setBalance(0);
                grandparent->setBalance(0);
                child->setBalance(0);
            }
            else if(child->getBalance() == 1){
                parent->setBalance(-1);
                grandparent->setBalance(0);
                child->setBalance(0);
            }
        }
        else{
            if(child->getBalance() == 1){
                parent->setBalance(0);
                grandparent->setBalance(-1);
                child->setBalance(0);
            }
            else if(child->getBalance() == 0){
                parent->setBalance(0);
                grandparent->setBalance(0);
                child->setBalance(0);
            }
            else if(child->getBalance() == -1){
                parent->setBalance(1);
                grandparent->setBalance(0);
                child->setBalance(0);
            }
        }
      }
  }  
}



template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key,Value>* grandparent){
  // cout << "ROTATE RIGHT IS GETTING CALLED" << endl;
  // cout << "------------------------------" << endl << endl;
  //     this->printRoot(this->root_);
  // cout << endl << endl << "------------------------------";

  AVLNode<Key, Value>* parent  = grandparent->getLeft();
  // cout << "PARENT PRE: " << parent->getKey() << endl;
  parent->setParent(grandparent->getParent());
  // if grandparent isnt the root
    // cout << "=====   3    =====" << endl;

  if(grandparent->getParent() != nullptr){
      // cout << "=====   4    =====" << endl;

    // If grandparent is a left child
    if(grandparent->getParent()->getLeft() == grandparent){
        // cout << "=====   5    =====" << endl;

      grandparent->getParent()->setLeft(parent);
    }
    // Otherwise, it must be a right child
    else{
        // cout << "=====   6    =====" << endl;

      grandparent->getParent()->setRight(parent);
    }
      // cout << "=====   7    =====" << endl;

  }
  else{
    this->root_ = parent;
  }


  grandparent->setLeft(parent->getRight());
  if(parent->getRight() != nullptr){
    parent->getRight()->setParent(grandparent);
  }

  parent->setRight(grandparent);

  grandparent->setParent(parent);
  // cout << endl << "Parent: " << parent->getKey() << endl;
  // cout << endl << "Root: " << this->root_->getKey() << endl;

  // cout << endl << "Left: " << this->root_->getLeft()->getKey() << endl;
  // cout << endl << "Right: " << parent->getRight()->getKey() << endl;

  // cout << "------------------------------" << endl << endl;
  //     this->printRoot(this->root_);
  // cout << endl << endl << "------------------------------";
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key,Value>* grandparent){

  AVLNode<Key, Value>* parent  = grandparent->getRight();
  parent->setParent(grandparent->getParent());
  // if grandparent isnt the root
  if(grandparent->getParent() != nullptr){
    // If grandparent is a left child
    if(grandparent->getParent()->getLeft() == grandparent){
      grandparent->getParent()->setLeft(parent);
    }
    // Otherwise, it must be a right child
    else{
      grandparent->getParent()->setRight(parent);
    }
  }
  else{
    this->root_ = parent;
  }
  
  grandparent->setRight(parent->getLeft());
  if(parent->getLeft() != nullptr){
    parent->getLeft()->setParent(grandparent);
  }
  parent->setLeft(grandparent);
  grandparent->setParent(parent);

}




/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
    AVLNode<Key, Value>* temp = static_cast<AVLNode<Key, Value>*>(this->root_);
    // find the node
    while (true) {
        if (temp == NULL){
            return;
        } 
        if (key == temp->getKey()) {
            break;
        }
        if (key < temp->getKey()) {
            temp = temp->getLeft();
        }
        else {
            temp = temp->getRight();
        }
    }
    bool blank = true;
    if(this->recursiveBalancedCall(this->root_, &blank) >= 3){
        return;
    }
    // while(this->root_ == temp){
    if(temp->getParent() == nullptr){
        if(temp->getLeft() == nullptr && temp->getRight() == nullptr){
            delete temp;
            this->root_ = nullptr;
        }
        else if(temp->getLeft() != nullptr && temp->getRight() != nullptr){
            this->root_ = temp->getLeft();
            temp->getLeft()->setRight(temp->getRight());
            temp->getLeft()->setParent(nullptr);
            delete temp;
        }
        else if(temp->getLeft() != nullptr){
            this->root_ = temp->getLeft();
            temp->getLeft()->setParent(nullptr);
            delete temp;
        }
        else if(temp->getRight() != nullptr){
            this->root_ = temp->getLeft();
            temp->getLeft()->setParent(nullptr);
            delete temp;
        // }
        }
    }
    else{
        if(temp->getLeft() == nullptr && temp->getRight() == nullptr){
            if(temp == temp->getParent()->getLeft()){
                temp->getParent()->setLeft(nullptr);
            }
            else{
                temp->getParent()->setRight(nullptr);
            }
            delete temp;
        }
        else if(temp->getLeft() != nullptr && temp->getRight() != nullptr){
            temp->getLeft()->setRight(temp->getRight());
            temp->getLeft()->setParent(temp->getParent());
            if(temp == temp->getParent()->getLeft()){
                temp->getParent()->setLeft(temp->getLeft());
            }
            else{
                temp->getParent()->setRight(temp->getLeft());
            }
            delete temp;
        }
        else if(temp->getLeft() != nullptr){
            temp->getLeft()->setParent(temp->getParent());
            if(temp == temp->getParent()->getLeft()){
                temp->getParent()->setLeft(temp->getLeft());
            }
            else{
                temp->getParent()->setRight(temp->getLeft());
            }
            delete temp;
        }
        else if(temp->getRight() != nullptr){
            temp->getLeft()->setParent(temp->getParent());
            if(temp == temp->getParent()->getLeft()){
                temp->getParent()->setLeft(temp->getRight());
            }
            else{
                temp->getParent()->setRight(temp->getRight());
            }
            delete temp;
        // }
        }
    }


}







template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif


