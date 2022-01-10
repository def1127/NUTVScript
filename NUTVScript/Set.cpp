#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include "InterpreterFunctions.h"

void set(std::vector<std::string> code, int& line, std::map<std::string, int>& variables) {

	std::vector<std::string> words{};
	getWords(code[line], words);

	if ((words.size() == 7 && words[0] == "")) { //checks that the words vector has at least 6 words in it, and deletes the empty first word if so
		words.erase(words.begin(), words.begin() + 2);
	}

	if ((words.size() == 5 && words[0] == "")) { //checks that the words vector has at least 4 words in it, and deletes the empty first word if so
		words.erase(words.begin(), words.begin() + 2);
	}

	if (words.size() == 3) { //this checks for the case were set var = var2 or set var = number

		if (variables.count(words[0]) && variables.count(words[2])) {

			variables[words[0]] = variables[words[2]];

		}

	}

	if (!((words.size() == 5) && words[1] == "=" && (words[3] == "+" || words[3] == "-"))) { //check that there are the proper number of words and that there is an equals sign and a +/-
		std::cout << "Error, set command callled incorrectly \"" << code[line] << "\". Proper syntax is 'set [var1] = [var2] [+/-] [var3]'" << std::endl;
		line = (int)code.size() - 2;
		return; //set the last line of the program to cause it to gracefully crash
	}

	//find the 3 variables needed.
	//need to check if words 2 or 4 are numbers or text so you can set numbers if you don't want them as variables


	if (variables.count(words[0]) && variables.count(words[2]) && variables.count(words[4])) {

		if (words[3] == "+") {
			variables[words[0]] = variables[words[2]] + variables[words[4]];

		}
		else if (words[3] == "-") {
			variables[words[0]] = variables[words[2]] - variables[words[4]];
		}
		else {
			std::cout << "Error: Invalid set command \"" << code[line] << "\". Proper syntax is 'set [var1] = [var2] [+/-] [var3]" << std::endl; //a catch error if something goes wrong
			line = (int)code.size() - 2;
			return; //set the last line of the program to cause it to gracefully crash
		}

	}

}