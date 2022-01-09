#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "interpreterInit.h"
#include "InterpreterFunctions.h"

void setVars(std::vector<std::string>& code, std::vector<int>& varVals, std::vector<std::string>& varNames) {
	std::string str;

	for (int i = 0; i < code.size(); i++) {//iterate through the program line by line

		std::vector<std::string> words{};
		str = code[i];
		std::stringstream sstream(code[i]); //put the line of code into a string stream

		getWords(sstream, words);

		if (!(words.size() == 1 && words[0] == "")) { //checks that the words vector has at least two words in it, and deletes the empty first word if so
			words.erase(words.begin());
		}

		if (words[0] == "Enter") { //if it detects the word "Enter" the keyphrase for declaring a variable
			if (!(words.size() == 4)) { //check that the format is "Enter [name] = [val]"
				std::cout << "Error: Variable declared improperly on line " << i + 1 << std::endl; //give an error for wrong variables
				std::exit(0);
			}
			varNames.push_back(words[1]); //add the variable name and value to the vector

			if (is_number(words[3])) {
				varVals.push_back(std::stoi(words[3]));
			}
			else {
				for (int j = 0; j < varNames.size(); j++) {
					if (words[3] == varNames[j]) {
						varVals.push_back(varVals[j]);
						break;
					}
					else if (j == varNames.size() - 1) {
						std::cout << "Error on line " << i << ". Variable " << words[1] << " cannot be initialized as " << words[3] << std::endl;
						exit(0);
					}
				}
			}
		}
	}
}

bool checkHeader(std::string filename, std::vector<std::string>& code) {
	std::string str = code[0];
	if (str.rfind(filename, 0) == 0) { //iterate through line one and two and make sure that they contain the requested information
		str = code[1];
		if (str.rfind("Written By:", 0) == 0) {
			if (code[code.size()-1] == "Cut!") {
				return true;
			}
		}
	}
	return false;
}

