/* Author: Allison Delgado
   Class: CS 163 Spring 2021
   main.cpp acts as a testing site for the member functions
   of the bst class. It provides user input to the cpp file,
   maintaining the rules of data abstraction.

   Last updated: May 25, 2021
 */
#include <iostream>
#include <cstring>
#include "bst.h"
using namespace std;

void print_error_messages(int success, const char function_name[]);

int main(){
  int success = 0;
  bst* tree = new bst();
  char lower;
  char upper;
  char input[20];
  char name[180];
  char desc[500];
  char example[500];
  char efficiency[500];
  cout << " " << endl;
  cout << "***********************************" << endl;
  cout << "Welcome to C++ Syntax Tree" << endl;

  while(strcmp(input, "q") != 0){
    cout << "--------------------------------" << endl;
    cout << "valid commands are: " << endl;
    cout << "add - add a new syntax " << endl;
    cout << "d - display all syntaxes " << endl;
    cout << "ret - retrieve a matching item by name " << endl;
    cout << "rm - remove an item by name " << endl;
    cout << "h - return the height of the tree " << endl;
    cout << "e - determine how efficient the tree is " << endl;
    cout << "dr - display range of syntaxes " << endl;
    cout << "q - quit " << endl;
    cout << "> ";
    cin.get(input, 20);
    cin.get();
    cout << "--------------------------------" << endl;

    //change input to lowercase
    for(int i = 0; i < (int) strlen(input); i++){
      input[i] = tolower(input[i]);
    }

    if(strcmp(input, "add") == 0){
      cout << "Enter the name of your syntax. " << endl;
      cout << "> ";
      cin.get(name, 180);
      cin.get();
      cout << "Enter the description." << endl;
      cout << "> ";
      cin.get(desc, 500);
      cin.get();
      cout << "Enter an example of code that uses this syntax." << endl;
      cout << "> ";
      cin.get(example, 500);
      cin.get();
      cout << "Enter a short note about anything efficiency-related for this syntax." << endl;
      cout << "> ";
      cin.get(efficiency, 500);
      cin.get();
      success = tree->insert(name, desc, example, efficiency);
      print_error_messages(success, "add");
    }
    
    if(strcmp(input, "d") == 0){
      success = tree->display_all();
      print_error_messages(success, "display");
    }

    if(strcmp(input, "ret") == 0){
      char* d = new char[500]; //holds description
      char* ex = new char[500]; //holds example
      char* ef = new char[500]; //holds efficiency note
      bool found = false;
      cout << "Enter the name of the syntax you would like to retrieve." << endl;
      cout << "> ";
      cin.get(name, 180);
      cin.get();
      success = tree->retrieve(name, d, ex, ef, found);
      if(found == true){ //if they're not null
	  cout << "NAME: " << name << endl;
	  cout << "DESCRIPTION: " << d << endl;
	  cout << "EXAMPLE: " << ex << endl;
	  cout << "ABOUT EFFICIENCY: " << ef << endl;
      } else {
	print_error_messages(0, "retrieve");
      }
    }
    if(strcmp(input, "rm") == 0){
      cout << "Enter the name of the syntax you would like to remove. " << endl;
      cout << "> ";
      cin.get(name, 180);
      cin.get();
      success = tree->remove_by_name(name);
      print_error_messages(success, "remove");
    }

    if(strcmp(input, "h") == 0){
      if(tree){
	cout << "The max height of the tree is ";
	cout << tree->get_height() << endl;
      } 
    }
    if(strcmp(input, "e") == 0){
      cout << "The tree's efficiency is ";
      int efficiency = tree->efficiency();
      if(efficiency == 2){
	cout << "O(N) time" << endl;
      } else {
	cout << "O(log n) time" << endl;
      }
    }
    if(strcmp(input, "dr") == 0){
      cout << "This function displays all syntaxes in a given range (ex: A-M)" << endl;
      cout << "Please only enter a single letter. " << endl;
      cout << "Enter the lower bound of the range. " << endl;
      cout << "> ";
      cin >> lower;
      cin.get();
      cout << "Enter the upper bound of the range. " << endl;
      cout << "> ";
      cin >> upper;
      cin.get();
      success = tree->display_syntax(lower, upper);
      print_error_messages(success, "syntax");
    }
  }
  delete tree;
  return 0;
}

//a function to print out error messages
void print_error_messages(int success, const char function_name[]){
  if(success == 1){ //success
    if(strcmp(function_name, "add") == 0){
      cout << "Syntax added successfully." << endl;
      cout << " " << endl;
    }
    if(strcmp(function_name, "remove") == 0){
      cout << "Syntax removed successfully." << endl;
      cout << " " << endl;
    }
  } else { //failure
    if(strcmp(function_name, "display") == 0){
      cout << "Nothing to display." << endl;
      cout << " " << endl;
    }
    if(strcmp(function_name, "retrieve") == 0){
      cout << "Nothing to show for that term." << endl;
      cout << " " << endl;
    }
    if(strcmp(function_name, "remove") == 0){
      cout << "Could not find a matching syntax." << endl;
      cout << " " << endl;
    }
    if(strcmp(function_name, "syntax") == 0){
      cout << "Could not find anything in that range. " << endl;
      cout << " " << endl;
    }
  }
}
