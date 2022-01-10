#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include "InterpreterFunctions.h"

void exclaim(std::vector<std::string> code, int& line, std::map<std::string, int>& variables) { //code to enable the "Exclaim" command
	
	std::vector<std::string> words{};
	getWords(code[line], words);

	if (words.size() > 2) {
		words.erase(words.begin(), words.begin() + 2);
	}

	for (int i = 0; i < words.size(); i++) { //iterate through the line
		if (!(words[i].at(0) == '%')) { //if there isn't a percent sign
			if (words.size() > 1) { //if there is more than one character
				if (!(words[i].at(0) == '/' && words[i].at(1) == '%')) { //check for the /% case
					std::cout << words[i] << " "; //print out the word
				}
				else {
					words[i].erase(words[i].begin());
					std::cout << words[i] << " "; //otherwise erase the / and print out the word
				}
			}
			else {
				std::cout << words[i] << " "; //print out the word
			}
		}
		else {
			words[i].erase(words[i].begin()); //get rid of the percent sign
				//find the variable need.

			if (variables.count(words[3])) {

				std::cout << variables[words[3]] << " ";

			}
			else {
				std::cout << "Variable " << words[3] << " could not be found." << std::endl;
			}

		}
	}
	std::cout << std::endl;
}