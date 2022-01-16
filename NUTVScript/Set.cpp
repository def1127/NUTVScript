#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include "InterpreterFunctions.h"

void set(std::vector<std::string> code, int& line, std::map<std::string, int>& variables) {
	std::vector<std::string> words{};
	getWords(code[line], words);

	if ((words.size() == 7 && words[0].empty())) { //checks that the words vector has at least 6 words in it, and deletes the empty first word if so
		words.erase(words.begin(), words.begin() + 2);
	}
	else if ((words.size() == 5 && words[0].empty())) { //checks that the words vector has at least 4 words in it, and deletes the empty first word if so
		words.erase(words.begin(), words.begin() + 2);
	}
	else if ((words.size() == 4 && words[0].empty())) {
		words.erase(words.begin(), words.begin() + 2);
	}

	if (words.size() == 3) { //this checks for the case were set var = var2 or set var = number
		if (variables.contains(words[0]) && variables.contains(words[2])) {
			variables[words[0]] = variables[words[2]];
			return;
		}
	}
	else if (words.size() == 2) {
		if (words[1] == "++" && variables.contains(words[0])) {
			variables[words[0]]++;
			return;
		}
		else if (words[1] == "--" && variables.contains(words[0])) {
			variables[words[0]]--;
			return;
		}
	}
	else if (!((words.size() == 5) && words[1] == "=" && (words[3] == "+" || words[3] == "-" || words[3] == "*" || words[3] == "/"))) { //check that there are the proper number of words and that there is an equals sign and a +/-
		std::cout << "Error, set command called incorrectly \"" << code[line] << "\". Proper syntax is 'set [var1] = [var2] [+/-] [var3]'" << std::endl;
		line = static_cast<int>(code.size()) - 2;
		return; //set the last line of the program to cause it to gracefully crash
	}

	//find the 3 variables needed.
	int varb;
	int varc;

	if (is_number(words[2])) { //check if it is a number or variable and store data appropriately
		varb = std::stoi(words[2]);
	}
	else {
		if (variables.contains(words[2])) {
			varb = variables[words[2]];
		}
		else {
			std::cout << "Variable " << words[2] << " could not be found." << std::endl;
			line = static_cast<int>(code.size()) - 2;
		}
	}

	if (is_number(words[4])) {
		varc = std::stoi(words[4]);
	}
	else {
		if (variables.contains(words[4])) {
			varc = variables[words[4]];
		}
		else {
			std::cout << "Variable " << words[4] << " could not be found." << std::endl;
			line = static_cast<int>(code.size()) - 2;
		}
	}

	if (variables.contains(words[0])) {
		if (words[3] == "+") {
			variables[words[0]] = varb + varc;
		}
		else if (words[3] == "-") {
			variables[words[0]] = varb - varc;
		}
		else if (words[3] == "*")
		{
			variables[words[0]] = varb * varc;
		}
		else if (words[3] == "/")
		{
			variables[words[0]] = static_cast<int>(varb / varc);
		}
	}
	else {
		std::cout << "Error: Invalid set command \"" << code[line] << "\". Proper syntax is 'set [var1] = [var2] [+/-] [var3]" << std::endl; //a catch error if something goes wrong
		line = static_cast<int>(code.size()) - 2;
		return; //set the last line of the program to cause it to gracefully crash
	}
}