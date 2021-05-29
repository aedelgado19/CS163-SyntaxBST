/* Author: Allison Delgado
   Class: CS 163 Spring 2021
   bst.cpp contains all member functions used
   to create a binary search tree. This BST holds
   nodes where the data is a type of C++ syntax.
   All functions are done recursively, meaning that
   the main class will only call a wrapper function
   which will then call the recursive version of that 
   function.

   Last updated: May 27, 2021
 */

#include <iostream>
#include <cstring>
#include "bst.h"

/* the constructor initializes the root to null. There are no
   other private data members so nothing else needs to be initialized*/
bst::bst(){
  root = NULL;
}

/* the destructor deallocates all dynamically allocated data
   and calls the delete_all function to recursively delete all nodes */
bst::~bst(){
  std::cout << "here" << std::endl;
  if(!root) return;
  delete_all(root);
}

node::~node(){
  delete [] name;
  delete [] desc;
  delete [] example;
  delete [] efficiency;
}

/* a helper function to deallocate all noeds in the BST. It is
   called by the destructor since the destructor can't have parameters 
   and recursion does need parameters, so this is a separate function. */
int bst::delete_all(node*& current){
  std::cout << "hi" << std::endl;
  if(!root) return 0;
  if(current){
    delete_all(current->left);
    delete_all(current->right);
    delete [] current->name;
    delete [] current->desc;
    delete [] current->example;
    delete [] current->efficiency;
    delete current;
  }
  root = NULL;
  return 1;
}


/* a wrapper function to insert data. it is passed in arguments from main,
   creates a new node, then calls the other add function which sorts it
   into the tree. returns 1 for success and 0 for failure. */
int bst::insert(char* name, char* desc, char* example, char* efficiency){
  node* new_node = new node;

  //if any of the fields were not provided correctly
  if(!name || !desc || !example || !efficiency){
    return 0;
  }
  
  //allocate space
  new_node->name = new char[180];
  new_node->desc = new char[500];
  new_node->example = new char[500];
  new_node->efficiency = new char[500];
  strcpy(new_node->name, name);
  strcpy(new_node->desc, desc);
  strcpy(new_node->example, example);
  strcpy(new_node->efficiency, efficiency);

  //call recursive function
  int success = insert(root, new_node);
  if(success == 0){
    return 0;
  }
  return 1;
}

/* a private recursive function to insert data. it is called by the wrapper function
   above. new data is always inserted as a leaf, so the function goes left if 
   the node is smaller than the current, and right if it is larger. returns 0 if the 
   node was not passed in correctly, and a 1 if successful. */
int bst::insert(node* current, node* to_add){

  //if root doesn't exist
  if(!root){
    root = to_add;
    to_add->left = NULL;
    to_add->right = NULL;
    return 0;
  }

  //check right
  if(strcmp(current->name, to_add->name) < 0){
    if(!current->right){
      current->right = to_add;
      return 1;
    }
    insert(current->right, to_add);
  }

  //check left
  if(strcmp(current->name, to_add->name) > 0){
    if(!current->left){
      current->left = to_add;
      return 1;
    }
    insert(current->left, to_add);
  }
  return 0;
}

/* A wrapper function that calls the recursive display_all() function
   requires no parametes since it uses the private data member root.
   returns 0 if root does not exist, and 1 if successful. */
int bst::display_all(){
  if(!root) return 0;
  std::cout << "Tree hierarchy: " << std::endl;
  std::cout << "Note: it's printed sideways (leftmost node is the root)" << std::endl;
  display_all(root, 0);
  std::cout << "Information for each node: " << std::endl;
  display_info(root);
  return 1;
}

/* a recursive function to display all the nodes in the tree.
   it prints the tree sideways by first checking the right side,
   then the left side. returns 1 if successful and 0 if the root is null.
   Credits given: I've taken CS 163 before (at my highschool last term),
   and this is the algorithm we used, so credit to Mr. Galbraith. */
void bst::display_all(node* current, int depth){
  if(!current) return;

  //right side
  display_all(current->right, depth + 1);

  //spacing
  for(int i = 0; i < depth; i++){
    std::cout << "      ";
  }
  std::cout << current->name << std::endl;

  //left side
  display_all(current->left, depth + 1);  
}

/* a helper function to display the information for each node in the tree.
   it prints out the right side first then the left. */
void bst::display_info(node* current){
  if(!current) return;

  //right side
  display_info(current->right);

  //print info
  std::cout << "NAME: " << current->name << std::endl;
  std::cout << "     description: " << current->desc << std::endl;
  std::cout << "     example: " << current->example << std::endl;
  std::cout << "     note about efficiency: " << current->efficiency << std::endl;
  std::cout << "     left child: ";

  //if the left child exists print out the left's name
  if(current->left){
    std::cout << current->left->name << std::endl;
  } else {
    std::cout << "NULL" << std::endl;
  }
  std::cout << "     right child: ";

  //if the right child exists print out the right's name
  if(current->right){
    std::cout << current->right->name << std::endl;
  } else {
    std::cout << "NULL" << std::endl;
  }

  //left side
  display_info(current->left);
}

/* a function to retrieve based on a passed in name. The found 
   information is returned by a reference in the arguments. */
int bst::retrieve(char* name, char*& desc, char*& example, char*& efficiency, bool & found){
  int success = retrieve(root, name, desc, example, efficiency, found);
  if(success == 0){
    return 0;
  }
  return 1;
}

/* this function walks through the whole tree to find a matching name.
   if it finds it, it will supply what it found back through the arguments.
   otherwise, it will return 0 if it could not be found. */
int bst::retrieve(node* current, char* name, char*& d, char *& ex, char *& ef, bool& found){
  if(!root) return 0;

  //right side
  if(strcmp(current->name, name) < 0){
    if(current->right == NULL){
      return 0; //that number isn't in the tree
    }
    retrieve(current->right, name, d, ex, ef, found);
  }

  //left side
  if(strcmp(current->name, name) > 0){
    if(current->left == NULL){
      return 0; //that number isn't in the tree
    }
    retrieve(current->left, name, d, ex, ef, found);
  }

  //found a match
  if(strcmp(current->name, name) == 0){
    strcpy(d, current->desc);
    strcpy(ex, current->example);
    strcpy(ef, current->efficiency);
    found = true;
    return 1;
  }
  return 0;
}

/* remove_by_name is passed in a char pointer from main, and calls
   the matching recursive function for it. if the name is null,
   it returns a 0 to indicate function failure */
int bst::remove_by_name(char* name){
  if(!name) return 0;
  bool found = false;
  root = remove_by_name(root, name, found);
  if(found == true){
    return 1;
  }
  return 0;
}

/* this function is the recursive version of a removal. It is passed in
   the root to start with, and the name of the node to delete. */
node* bst::remove_by_name(node*& current, char* name, bool& found){
  if(!current) return current;
  
  //check left side first
  if(strcmp(current->name, name) > 0){
    current->left = remove_by_name(current->left, name, found);
  }

  //right side
  else if(strcmp(current->name, name) < 0){
    current->right = remove_by_name(current->right, name, found);
  }

  //otherwise, you found the node to be deleted
  else {
    //no children
    if(!current->left && !current->right){
      found = true;
      return NULL;
    }
    
    //left is null
    if(!current->left){
      node* hold = current->right;
      delete current;
      found = true;
      return hold;
    }
    //right is null
    if(!current->right){
      node* hold = current->left;
      delete current;
      found = true;
      return hold;
    }

    //has 2 children
    if(current->right && current->left){
      found = true;
      node* ios = current;
      //find inorder successor (go right, then furthest left)
      find_smallest(current->right, ios);
      
      strcpy(current->name, ios->name);
      strcpy(current->desc, ios->desc);
      strcpy(current->example, ios->example);
      strcpy(current->efficiency, ios->efficiency);

      //now delete the ios
      current->right = remove_by_name(current->right, ios->name, found);
    }
  }
  return current;
}

/* helper function to find the smallest number in the left
   subtree. It is called using current->right in the 
   remove_by_name recursive function to find the inorder successor. */
void bst::find_smallest(node* current, node*& to_return){
  if(current && current->left){
    find_smallest(current->left, to_return);
  }
  if(!current->left){
    to_return = current;
    return;
  }
}

/* a wrapper function to return the height of the tree. Calls
   the recursive version of the function */
int bst::get_height(){
  if(!root) return 0;
  int left = 0;
  int right = 0;
  int to_return = get_height(root, left, right);
  return to_return;
}

/* a function to recursively find the height of the tree.
   It starts by calling itself on the left subtree, then the
   right subtree, and returns the larger amount (in case it is
   a skewed tree. the left and right height are also saved through
   the argument list (they are used in the efficiency function)*/
int bst::get_height(node* current, int& left, int& right){
  if(!current) return 0;

  //save left subtree's height
  left = get_height(current->left, left, right);

  //save the right subtree's height
  right = get_height(current->right, left, right);

  //pick the larger number in case the tree is skewed one way
  if(right > left){
    return right + 1;
  } else { //left
    return left + 1;
  }
}

/* a function to determine how efficient the tree is.
   Worst case scenario is when the amount of nodes matches
   the height (meaning it's like a LLL). */
int bst::efficiency(){
  //first count all the nodes
  int amount = count_nodes(root);
  int left = 0;
  int right = 0;
  int height = get_height(root, left, right);

  //first pass: worst case scenario
  if(amount == height){
    return 2;
  }

  //check if perfectly balanced (same # of nodes in left as right)
  bool balanced = check_balance(root);
  bool full = is_full(root);
  if(balanced == true || full == true){
    return 1;
  }
  return 0;
}

/* a helper function to count the amount of nodes in the tree.
   It returns 1 + the left subtree call + the right subtree call */
int bst::count_nodes(node* current){
  if(!current) return 0;
  return 1 + count_nodes(current->left) + count_nodes(current->right);
}

/* a helper function to determine if the tree is balanced:
   Uses absolute value differences after finding the height
   of each subtree.*/
bool bst::check_balance(node* current){
  if(!current) return false;

  int left = 0;
  int right = 0;
  //get the heights of left and right thru argument list
  get_height(root, left, right);
  
  //if absolute difference btwn height of left and right < 1, it's balanced
  if(abs(left - right) < 1){
    return true;
  }
  return false;
}

/* a helper function to see if the tree is full.
   All nodes in a full BST  have 0 or 2 child nodes.*/
bool bst::is_full(node* current){
  if(!current) return true;

  //leaf
  if(!current->left && !current->right) return true;

  //"full" node
  if(current->left && current->right){
    //also check its subtrees (otherwise it only checks one node)
    if(is_full(current->left) == true && is_full(current->right) == true){
      return true;
    }
  }
  return false;
}

/* a wrapper function that calls the recursive version to display all syntaxes
   within a given range (lower and upper are the bounds). If the arguments weren't
   passed in correctly, it will return 0. Same if the root does not exist. It 
   will then (if it passed those checks) call the recursive function, and return
   what the recursive function returns */
int bst::display_syntax(char lower, char upper){
  if(!lower || !upper) return 0;
  if(!root) return 0;

  bool found = false;
  display_syntax(root, lower, upper, found);
  if(found == false){
    return 0; //could not find any matching syntax
  }
  return 1;
}

/* a recursive function to display all syntaxes within a given range (lower -> upper).
   It traverses the tree, and if the node's name that it finds is within the range,
   it will display its information. */
void bst::display_syntax(node* current, char lower, char upper, bool& found){
  if(!current) return;
  
  //right side
  display_syntax(current->right, lower, upper, found);

  //print info
  if(((int) lower <= (int) current->name[0]) && ((int) upper >= (int) current->name[0])){
    found = true;
    std::cout << "NAME: " << current->name << std::endl;
    std::cout << "     description: " << current->desc << std::endl;
    std::cout << "     example: " << current->example << std::endl;
    std::cout << "     note about efficiency: " << current->efficiency << std::endl;
    std::cout << "     left child: ";

    //if the left child exists print out the left's name
    if(current->left){
      std::cout << current->left->name << std::endl;
    } else {
      std::cout << "NULL" << std::endl;
    }
    std::cout << "     right child: ";

    //if the right child exists print out the right's name
    if(current->right){
      std::cout << current->right->name << std::endl;
    } else {
      std::cout << "NULL" << std::endl;
    }
  }
  //left side
  display_syntax(current->left, lower, upper, found);
}
