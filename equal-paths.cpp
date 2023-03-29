#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)
#include <iostream>

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
int depth(Node * root, int currDepth){
  if (root == nullptr){
    return currDepth;
  }

  int leftDepth = depth(root->left, currDepth + 1);
  int rightDepth = depth(root->right, currDepth + 1);

  if(leftDepth > rightDepth){
    return leftDepth;
  }
  return rightDepth;

}


bool equalPaths(Node * root)
{
  if(root == nullptr){
    return true;
  }
  if(root->left == nullptr && root->right == nullptr){
    return true;
  }
  if(root->left == nullptr && !depth(root->right, -1)){
    return true;
  }
  if(!depth(root->left, -1) && root->right == nullptr){
    return true;
  }
  if(depth(root->left, 0) == depth(root->right, 0)){
    return true;
  }

  return false;

}



