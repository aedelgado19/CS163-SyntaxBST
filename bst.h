/* Author: Allison Delgado
   Class: CS 163 Spring 2021
   bst.h is the header file for bst.cpp. 
   It contains all function prototypes necessary 
   for the ADT. This data structure is a binary
   search tree where each node is a different 
   type of advanced C++ syntax.

   Last updated: May 17, 2021
 */

struct node {
  char* name;
  char* desc;
  char* example;
  char* efficiency;
  node* left;
  node* right;
};

//all int return types return 1 for success
//and 0 for failure
class bst {
 public:
  //task 1: constructor and destructor
  bst();
  ~bst();

  //task 2: insert a new item and display all
  int insert(char* name, char* desc, char* example, char* efficiency);
  int display_all();

  //task 3: retrieve a matching item by the name
  int retrieve(char* name);

  //task 4: remove an item by the name of the concept
  int remove_by_name(char* name);

  //task 5: get the height of the tree
  int get_height();

  //task 6: determine how efficient the tree is
  int efficiency();
  
  //task 7: display a range of syntax concepts
  int display_syntax();
  
 private:
  node* root;

  //recursive functions:
  int insert(node* current);
  int display_all(node* current);
  int retrieve(node* current, char* name);
  int remove_by_name(node* current, char* name);
  int get_height(node* current);
  int efficiency(node* current);
  int display_syntax(node* current);
				  
}