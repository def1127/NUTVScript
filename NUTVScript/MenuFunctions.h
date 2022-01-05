#pragma once
#include <iostream>

void printMenu(); //prints the opening menu
void getUserInput(); //Gets user input and calls other functions based on input
void ls(); //Lists all files in the active directory
void run(std::string fileName); //runs the interpreter
void help(); //prints out the list of all valid commands
void man(std::string command); //prints out detailed information about the specified command