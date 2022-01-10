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

bool is_number(const std::string& s) {
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}