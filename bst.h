/* Author: Allison Delgado
   Class: CS 163 Spring 2021
   bst.h is the header file for bst.cpp. 
   It contains all function prototypes necessary 
   for the ADT. This data structure is a binary
   search tree where each node is a different 
   type of advanced C++ syntax.
   A node contains a name, a description, an example,
   a note about its efficiency, and its pointers (L and R).

   Last updated: May 27, 2021
 */

struct node {
  ~node();
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

  //a function called by the destructor since the destructor cannot have
  //any parameters (which is necessary for recursion)
  int delete_all(node *& current);

  //task 2: insert a new item and display all
  int insert(char* name, char* desc, char* example, char* efficiency);
  int display_all();
  
  //task 3: retrieve a matching item by the name
  int retrieve(char* name, char*& desc, char*& example, char*& efficiency, bool & found);

  //task 4: remove an item by the name of the concept
  int remove_by_name(char* name);

  //task 5: get the height of the tree
  int get_height();

  //task 6: determine how efficient the tree is
  int efficiency();
  
  //task 7: display a range of syntax concepts
  int display_syntax(char lower, char upper);
  
 private:
  node* root;

  //recursive functions:
  int insert(node* current, node* to_add);
  void display_all(node* current, int depth);
  void display_info(node* current);
  int retrieve(node* current, char* name, char*& d, char *& ex, char *&ef, bool & found);
  node* remove_by_name(node*& current, char* name, bool& found);
  void find_smallest(node* current, node*& to_return);
  int get_height(node* current, int& left, int& right);
  bool check_balance(node* current);
  bool is_full(node* current);
  int efficiency(node* current);
  int count_nodes(node* current);
  void display_syntax(node* current, char lower, char upper, bool& found);
				  
};
