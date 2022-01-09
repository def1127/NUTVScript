#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "InterpreterFunctions.h"

void exclaim(std::vector<std::string> code, int& line, std::vector<std::string> varNames, std::vector<int> varVals) { //code to enable the "Exclaim" command
	
	std::vector<std::string> words{};
	getWords(code[line], words);

	if (words.size() > 2) {
		words.erase(words.begin(), words.begin() + 2);
	}

	for (int i = 0; i < words.size(); i++) {
		if (!(words[i].at(0) == '%')) {
			if (words.size() > 1) {
				if (!(words[i].at(0) == '/' && words[i].at(1) == '%')) {
					std::cout << words[i] << " ";
				}
				else {
					words[i].erase(words[i].begin());
					std::cout << words[i] << " ";
				}
			}
			else {
				std::cout << words[i] << " ";
			}
		}
		else {
			words[i].erase(words[i].begin()); //get rid of the percent sign
				//find the variable need.

			std::cout << varVals[findVar(varNames, words[i], code, line)] << " ";

		}
	}
	std::cout << std::endl;
}