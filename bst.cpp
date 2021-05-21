/* Author: Allison Delgado
   Class: CS 163 Spring 2021
   bst.cpp contains all member functions used
   to create a binary search tree. This BST holds
   nodes where the data is a type of C++ syntax.
   All functions are done recursively, meaning that
   the main class will only call a wrapper function
   which will then call the recursive version of that 
   function.

   Last updated: May 17, 2021
 */

#include <iostream>
#include <cstring>
#include "bst.h"

/* the constructor initializes the root to null as well
   as its fields like left and right*/
bst::bst(){
  root = NULL;
}

/* the destructor deallocates all dynamically allocated data
   and calls the delete_all function to recursively delete all nodes */
bst::~bst(){
  if(!root) return;
  delete_all(root);
}

/* a helper function to deallocate all noeds in the BST. It is
   called by the destructor since the destructor can't have parameters 
   and recursion does need parameters, so this is a separate function. */
int bst::delete_all(node*& current){
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
  if(strcmp(current->name, to_add->name) > 0){
    if(!current->right){
      current->right = to_add;
      return 1;
    }
    insert(current->right, to_add);
  }

  //check left
  if(strcmp(current->name, to_add->name) < 0){
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

void bst::display_info(node* current){
  if(!current) return;

  //right side
  display_info(current->right);

  //print info
  std::cout << "NAME: " << current->name << std::endl;
  std::cout << "     description: " << current->desc << std::endl;
  std::cout << "     example: " << current->example << std::endl;
  std::cout << "     note about efficiency: " << current->efficiency << std::endl; 
  //left side
  display_info(current->left);
}

/* a function to retrieve based on a passed in name. The found 
   information is returned by a reference in the arguments. */
int bst::retrieve(char* name, char*& desc, char*& example, char*& efficiency){
  int success = retrieve(root, name, desc, example, efficiency);
  if(success == 0){
    return 0;
  }
  return 1;
}

/* this function walks through the whole tree to find a matching name.
   if it finds it, it will supply what it found back through the arguments.
   otherwise, it will return 0 if it could not be found. */
int bst::retrieve(node* current, char* name, char*& d, char *& ex, char *& ef){
  if(!root) return 0;

  //right side
  if(strcmp(current->name, name) > 0){
    if(current->right == NULL){
      return 0; //that number isn't in the tree
    }
    retrieve(current->right, name, d, ex, ef);
  }

  //left side
  if(strcmp(current->name, name) < 0){
    if(current->left == NULL){
      return 0; //that number isn't in the tree
    }
    retrieve(current->left, name, d, ex, ef);
  }

  //found a match
  if(strcmp(current->name, name) == 0){
    strcpy(d, current->desc);
    strcpy(ex, current->example);
    strcpy(ef, current->efficiency);
    return 1;
  }
  return 1;
}

int bst::remove_by_name(char* name){

  return 0;
}

int bst::remove_by_name(node* current, char* name){
  return 0;
}

int bst::get_height(){
  return 0;
}

int bst::get_height(node* current){
  return 0;
}

int bst::efficiency(){
  return 0;
}

int bst::efficiency(node* current){
  return 0;
}

int bst::display_syntax(){
  return 0;
}

int bst::display_syntax(node* current){
  return 0;
}
