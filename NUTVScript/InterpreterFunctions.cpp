#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "InterpreterFunctions.h"

char delim = ' '; //space character

void getWords(const std::string& line, std::vector<std::string>& words) {
	std::string word;

	std::stringstream sstream(line); //put the line of code into a string stream

	do { //erase the string stream word by word in to a vector of words
		std::erase_if(word, isspace);
		words.push_back(word);
	} while (std::getline(sstream, word, delim));
}

bool is_number(const std::string& s) {
	auto it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}