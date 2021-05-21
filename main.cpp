/* Author: Allison Delgado
   Class: CS 163 Spring 2021
   main.cpp acts as a testing site for the member functions
   of the bst class. It provides user input to the cpp file,
   maintaining the rules of data abstraction.

   Last updated: May 17, 2021
 */
#include <iostream>
#include <cstring>
#include "bst.h"
using namespace std;

void print_error_messages(int success, const char function_name[]);

int main(){
  int success = 0;
  bst* tree = new bst();
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
    cout << "display - display all syntaxes " << endl;
    cout << "retrieve - retrieve a matching item by name " << endl;
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
    
    if(strcmp(input, "display") == 0){
      success = tree->display_all();
      print_error_messages(success, "display");
    }

    if(strcmp(input, "retrieve") == 0){
      char* d = new char[500]; //holds description
      char* ex = new char[500]; //holds example
      char* ef = new char[500]; //holds efficiency note
      cout << "Enter the name of the syntax you would like to retrieve." << endl;
      cout << "> ";
      cin.get(name, 180);
      cin.get();
      success = tree->retrieve(name, d, ex, ef);
      if(success == 1){
	cout << "NAME: " << name << endl;
	cout << "DESCRIPTION: " << d << endl;
	cout << "EXAMPLE: " << ex << endl;
	cout << "ABOUT EFFICIENCY: " << ef << endl;
      }
      print_error_messages(success, "retrieve");
    }
  }
  
  return 0;
}

//a function to print out error messages
void print_error_messages(int success, const char function_name[]){
  if(success == 1){ //success
    if(strcmp(function_name, "add") == 0){
      cout << "Syntax added successfully." << endl;
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
  }
}
