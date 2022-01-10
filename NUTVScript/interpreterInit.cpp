#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>

#include "interpreterInit.h"
#include "InterpreterFunctions.h"

void setVars(std::vector<std::string>& code, std::map<std::string, int> &variables) {

	for (int i = 0; i < code.size(); i++) {//iterate through the program line by line

		std::vector<std::string> words{};

		std::string key;

		getWords(code[i], words);

		if (!(words.size() == 1 && words[0] == "")) { //checks that the words vector has at least two words in it, and deletes the empty first word if so
			words.erase(words.begin());
		}

		if (words[0] == "Enter") { //if it detects the word "Enter" the keyphrase for declaring a variable
			if (!(words.size() == 4)) { //check that the format is "Enter [name] = [val]"
				std::cout << "Error: Variable declared improperly on line " << i + 1 << std::endl; //give an error for wrong variables
				std::exit(0);
			}

			key = words[1];// store the variable name as the key.

			if (is_number(words[3])) {

				variables.insert({ key,std::stoi(words[3])});

			}
			else {
				if (variables.count(words[3])){

					variables.emplace(key, variables.find(words[3]));

				}
				else {
					std::cout << "Error with line: " << code[i] << ". Please fix variable declaration." << std::endl;
					exit(0);
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

