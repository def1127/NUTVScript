#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>

#include "interpreterInit.h"
#include "InterpreterFunctions.h"

void setVars(const std::vector<std::string>& code, std::map<std::string, int>& variables, std::string filename) {
	for (int i = 0; i < code.size(); i++) {//iterate through the program line by line
		std::vector<std::string> words{};

		getWords(code[i], words);

		if (!(words.size() == 1 && words[0].empty())) { //checks that the words vector has at least two words in it, and deletes the empty first word if so
			words.erase(words.begin());
		}

		if (words[0] == "Enter") {
			std::string key;
			//if it detects the word "Enter" the keyphrase for declaring a variable
			if (!(words.size() == 4))
			{
				//check that the format is "Enter [name] = [val]"
				std::cout << "Error: Variable declared improperly on line " << i + 1 << std::endl;
				//give an error for wrong variables
				std::exit(0);
			}

			//set the variable name to the variable plus the file name
			words[1] = words[1] + "_" + filename;

			//check that the variable name is valid
			if (words[1].find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_.") != std::string::npos) {
				std::cout << "Error: Invalid variable name on line " << i + 1 << std::endl;
				std::exit(0);
			}
			
			//check that the variable name is not already in use
			if (variables.find(words[1]) != variables.end()) {
				std::cout << "Error: Variable already declared on line " << i + 1 << std::endl;
				std::exit(0);
			}
			
			//check that the variable value is a number
			if (words[3].find_first_not_of("0123456789") != std::string::npos) {
				std::cout << "Error: Invalid variable value on line " << i + 1 << std::endl;
				std::exit(0);
			}

			key = words[1];// store the variable name as the key.

			//store variable in map
			variables[key] = std::stoi(words[3]);
			
		}
	}
}

bool checkHeader(const std::string& filename, std::vector<std::string>& code) {
	std::string str = code[0];
	if (str.rfind(filename, 0) == 0) { //iterate through line one and two and make sure that they contain the requested information
		str = code[1];
		if (str.rfind("Written By:", 0) == 0) {
			if (code[code.size() - 1] == "Cut!") {
				return true;
			}
		}
	}
	return false;
}

//iterates through the file, finds set lines, and renames the variable
void correctVars(const std::vector <std::string>& code, std::map<std::string, int>& variables, std::string filename) {
	
	std::vector<std::string> words{};
	
	for (int i = 0; i < code.size(); i++) {

		words.clear();

		getWords(code[i], words);

		//if the first word is set
		if (words.size() > 0) {
			if (words[1] == "Set") {
				
				//renames the first variable
				words[2] = words[2] + "_" + filename;

				//check if there are other variables in the statement and set them
				//write the line back to the file after it has been adjusted
			}

		}

	}
}