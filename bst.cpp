/* Author: Allison Delgado
   Class: CS 163 Spring 2021
   bst.cpp contains all member functions used
   to create a binary search tree. This BST holds
   nodes where the data is a type of C++ syntax.

   Last updated: May 17, 2021
 */

#include <iostream>
#include <cstring>
#include "bst.h"

/* the constructor initializes the root to null as well
   as its fields like left and right*/
bst::bst(){
  root = NULL;
  root->left = NULL;
  root->right = NULL;
}

/* the destructor deallocates all dynamically allocated data
   by traversing the entire tree and removing all nodes. */
bst::~bst(){
  if(!root) return;
  
}

/* a wrapper function to insert data. it is passed in arguments from main,
   creates a new node, then calls the other add function which sorts it
   into the tree. returns 1 for success and 0 for failure. */
int bst::insert(char* name, char* desc, char* example, char* efficiency){
  node* new_node = new node;

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
  insert(root, new_node);
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
  display_all(root, 0);
  return 1;
}

/* a recursive function to display all the nodes in the tree.
   it prints the tree sideways by first checking the right side,
   then the left side. returns 1 if successful and 0 if the root is null.
   Credits given: I've taken CS 163 before (at my highschool last term),
   and this is the same algorithm we were taught, so credit to Mr. Galbraith. */
int bst::display_all(node* current, int depth){
  if(!root) return 0;

  //right side
  display_all(current->right, depth + 1);

  //spacing
  for(int i = 0; i < depth; i++){
    std::cout << "        ";
  }
  std::cout << current->name << std::endl;
  std::cout << current->desc << std::endl;
  std::cout << current->example << std::endl;
  std::cout << current->efficiency << std::endl;

  //left side
  display_all(current->left, depth + 1);  
  return 1;
}

int bst::retrieve(char* name){

  return 0;
}

int bst::retrieve(node* current, char* name){

  return 0;
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
