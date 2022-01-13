#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include "InterpreterFunctions.h"
#include "jumpCut.h"

void perhaps(std::vector<std::string> code, int& line, std::map<std::string, int>& variables) {
	std::vector<std::string> words{};
	getWords(code[line], words);

	if ((words.size() == 5 && words[0].empty())) { //checks that the words vector has at least 5 words in it, and deletes the empty first word if so
		words.erase(words.begin(), words.begin() + 2);
	}

	//logic

	if (words.size() != 3 && !(words[1] == ">" || words[1] == "=" || words[1] == "<")) {
		std::cout << "Error with line " << code[line] << ". Perhaps command called incorrectly, proper syntax is 'Perhaps var [>/=/<] var'" << std::endl;
		line = static_cast<int>(code.size()) - 2;
		return;
	}

	int var2;
	if (is_number(words[2])) {
		var2 = std::stoi(words[2]);
	}
	else {
		if (variables.contains(words[2])) {
			var2 = variables[words[2]];
		}
		else {
			std::cout << "Error with line " << code[line] << ". Perhaps command called incorrectly, proper syntax is 'Perhaps var [>/=/<] [var/int]'" << std::endl; //this is a catch error that should never be triggered
			line = static_cast<int>(code.size()) - 2;
		}
	}

	if (variables.contains(words[0])) { //if the variables exist
		if (words[1] == "<") {
			if (variables[words[0]] < var2) {
				return; //keep interpreting
			}
			else {
				line = jumpCut(code, line);
			}
		}
		else if (words[1] == ">") {
			if (variables[words[0]] > var2) {
				return;
			}
			else {
				line = jumpCut(code, line);
			}
		}
		else if (words[1] == "=") {
			if (variables[words[0]] == var2) {
				return;
			}
			else {
				line = jumpCut(code, line);
			}
		}
	}

	return;
}