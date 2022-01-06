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
	if (str.rfind(filename, 0) == 0) { //iterate through line one and two and make sure that they contain the requested information
		str = code[1];
		if (str.rfind("Written By:", 0) == 0) {
			return true;
		}
	}
	return false;
}

void exclaim(std::vector<std::string> code, int line) { //code to enable the "Exclaim" command
	std::string str = code[line];
	str.erase(str.begin(),str.begin()+8); //remove the "Exclaim" word and empty space

	for (int i = 0; i < str.size(); i++) {
		std::cout << str[i];
	}

	std::cout << std::endl;

}

void set(std::vector<std::string> code, int line, std::vector<int>& varVals, std::vector<std::string>& varNames) {

	std::string str = code[line];
	str.erase(str.begin(), str.begin() + 4); //remove the "Set" word and empty space

	std::vector<std::string> words{};
	std::stringstream sstream(code[line]); //put the line of code into a string stream
	std::string word;

	do { //erase the string stream word by word in to a vector of words
		word.erase(std::remove_if(word.begin(), word.end(), isspace), word.end());
		words.push_back(word);
	} while (std::getline(sstream, word, delimiter));

	if ((words.size() == 7 && words[0] == "")) { //checks that the words vector has at least 6 words in it, and deletes the empty first word if so
		words.erase(words.begin());
		words.erase(words.begin());
	}

	if (!(words.size() == 5) && words[1] == "=" && (words[3] == "+" || words[3] == "-")) { //check that there are the proper number of words and that there is an equals sign and a +/-
		std::cout << "Error, set command incorrectly called on line " << line << ". Proper syntax is 'set [var1] = [var2] [+/-] [var3]'" << std::endl;
	}

	int vara, varb, varc;
	//find the 3 variables needed.
	for (int i = 0; i < varNames.size(); i++) { //iterate through the variables vector to find the index of the variable selected
		if (varNames[i] == words[0]) {
			vara = i;
			break;
		}
		else if (i == varNames.size() - 1) {
			std::cout << "Error, variable " << words[1] << "not found, check that all variables have already been declared." << std::endl;
		}
	}
	for (int i = 0; i < varNames.size(); i++) { //iterate through the variables vector to find the index of the variable selected
		if (varNames[i] == words[2]) {
			varb = i;
			break;
		}
		else if (i == varNames.size() - 1) {
			std::cout << "Error, variable " << words[3] << "not found, check that all variables have already been declared." << std::endl;
		}
	}
	for (int i = 0; i < varNames.size(); i++) { //iterate through the variables vector to find the index of the variable selected
		if (varNames[i] == words[4]) {
			varc = i;
			break;
		}
		else if (i == varNames.size() - 1) {
			std::cout << "Error, variable " << words[5] << "not found, check that all variables have already been declared." << std::endl;
		}
	}
	//perform the actual operations
	if (words[3] == "+") { 
		varVals[vara] = varVals[varb] + varVals[varc];
	}
	else if (words[3] == "-") {
		varVals[vara] = varVals[varb] - varVals[varc];
	}
	else {
		std::cout << "Error, in the set command on line " << line << ". Proper syntax is 'set [var1] = [var2] [+/-] [var3]'" << std::endl; //a catch error if something goes wrong
	}


}