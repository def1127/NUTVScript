#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "InterpreterFunctions.h"

char delimiter = ' '; //space character

void setVars(std::vector<std::string> &code, std::vector<int> &varVals, std::vector<std::string> &varNames) {
	std::string str;

	for (int i = 0; i < code.size(); i++) {//iterate through the program line by line

		std::vector<std::string> words{};
		str = code[i];
		std::stringstream sstream(code[i]); //put the line of code into a string stream
		std::string word;

		do { //erase the string stream word by word in to a vector of words
			word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());
			words.push_back(word);
		} while (std::getline(sstream, word, delimiter));

		if (!(words.size() == 1 && words[0] == "")) { //checks that the words vector has at least two words in it, and deletes the empty first word if so
			words.erase(words.begin());
		}

		if (words[0] == "Enter") { //if it detects the word "Enter" the keyphrase for declaring a variable
			if (!(words.size() == 4)) { //check that the format is "Enter [name] = [val]"
				std::cout << "Error: Variable declared improperly on line " << i + 1 << std::endl; //give an error for wrong variables
				std::exit(0);
			}
			varNames.push_back(words[1]); //add the variable name and value to the vector
			varVals.push_back(std::stoi(words[3]));
		}
	}
}

void setFuncs(std::vector<std::string> &code, std::vector<std::string> &funcNames, std::vector<int> &funcLines) {
	std::string str;

	for (int i = 0; i < code.size(); i++) {//iterate through the program line by line

		std::vector<std::string> words{};
		str = code[i];
		std::stringstream sstream(code[i]); //put the line of code into a string stream
		std::string word;

		do { //erase the string stream word by word in to a vector of words
			word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());
			words.push_back(word);
		} while (std::getline(sstream, word, delimiter));

		if (!(words.size() == 1 && words[0] == "")) { //checks that the words vector has at least two words in it, and deletes the empty first word if so
			words.erase(words.begin());
		}

		if (words[0] == "Scene") { //if it detects the word "Scene" the keyphrase for declaring a function
			if (!(words.size() == 2)) { //check that the format is "Scene: [name]"
				std::cout << "Error: Scene declared improperly on line " << i + 1 << std::endl; //give an error for wrong function declaration
				std::exit(0);
			}
			funcNames.push_back(words[1]); //add the variable name and value to the vector
			funcLines.push_back(i);
		}
	}
}

bool checkHeader(std::string filename, std::vector<std::string>& code) {
	std::string str = code[0];
	if (str.rfind(filename, 0) == 0) {
		str = code[1];
		if (str.rfind("Written By:", 0) == 0) {
			return true;
		}
	}
	return false;
}