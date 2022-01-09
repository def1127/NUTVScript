#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "InterpreterFunctions.h"

char delim = ' '; //space character

void getWords(std::string line, std::vector<std::string>& words) {
	std::string word;

	std::stringstream sstream(line); //put the line of code into a string stream

	do { //erase the string stream word by word in to a vector of words
		word.erase(std::remove_if(word.begin(), word.end(), isspace), word.end());
		words.push_back(word);
	} while (std::getline(sstream, word, delim));

}

int findVar(std::vector<std::string> varNames, std::string strToMatch, std::vector<std::string> code, int& line) {

	for (int j = 0; j < varNames.size(); j++) { //iterate through the variables vector to find the index of the variable selected
		if (varNames[j] == strToMatch) {
			return j;
			break;
		}
		else if (j == varNames.size() - 1) {
			std::cout << "\nError: variable " << strToMatch << " not found, check that all variables have already been declared." << std::endl;
			line = (int)code.size() - 2;
			return 0; //set the last line of the program to cause it to gracefully crash
		}
	}

}

bool is_number(const std::string& s) {
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}