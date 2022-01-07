#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "InterpreterFunctions.h"

char delim = ' '; //space character

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
	} while (std::getline(sstream, word, delim));

	if ((words.size() == 7 && words[0] == "")) { //checks that the words vector has at least 6 words in it, and deletes the empty first word if so
		words.erase(words.begin());
		words.erase(words.begin());
	}

	if (!(words.size() == 5) && words[1] == "=" && (words[3] == "+" || words[3] == "-")) { //check that there are the proper number of words and that there is an equals sign and a +/-
		std::cout << "Error, set command callled incorrectly \"" << code[line] << "\". Proper syntax is 'set [var1] = [var2] [+/-] [var3]'" << std::endl;
	}

	int vara, varb, varc;
	//find the 3 variables needed.
	for (int i = 0; i < varNames.size(); i++) { //iterate through the variables vector to find the index of the variable selected
		if (varNames[i] == words[0]) {
			vara = i;
			break;
		}
		else if (i == varNames.size() - 1) {
			std::cout << "Error: variable " << words[0] << " not found, check that all variables have already been declared." << std::endl;
			exit(0);
		}
	}
	for (int i = 0; i < varNames.size(); i++) { //iterate through the variables vector to find the index of the variable selected
		if (varNames[i] == words[2]) {
			varb = i;
			break;
		}
		else if (i == varNames.size() - 1) {
			std::cout << "Error: variable " << words[0] << " not found, check that all variables have already been declared." << std::endl;
			exit(0);
		}
	}
	for (int i = 0; i < varNames.size(); i++) { //iterate through the variables vector to find the index of the variable selected
		if (varNames[i] == words[4]) {
			varc = i;
			break;
		}
		else if (i == varNames.size() - 1) {
			std::cout << "Error: variable " << words[0] << " not found, check that all variables have already been declared." << std::endl;
			exit(0);
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
		std::cout << "Error: Invalid set command \"" << code[line] << "\". Proper syntax is 'set [var1] = [var2] [+/-] [var3]" << std::endl; //a catch error if something goes wrong
	}


}

int jumpCut(std::vector<std::string> code, int line) {
	std::string str = code[line];
	str.erase(str.begin(), str.begin() + 9); //remove the "Jumpcut:" word and empty space

	std::string targetScene = str;

	for (int i = 0; i < code.size(); i++) {
		std::vector<std::string> words{};
		str = code[i];
		std::stringstream sstream(code[i]); //put the line of code into a string stream
		std::string word;

		do { //erase the string stream word by word in to a vector of words
			word.erase(std::remove_if(word.begin(), word.end(), isspace), word.end());
			words.push_back(word);
		} while (std::getline(sstream, word, ' '));

		if (!(words.size() == 1 && words[0] == "")) { //checks that the words vector has at least two words in it, and deletes the empty first word if so
			words.erase(words.begin());
		}

		if ((words.size() == 2) && words[0] == "Scene:" && words[1] == targetScene) { //checks if the first word is Scene and the second word on the line is the target scene
			return i;
		}
		else if (i == code.size()-1) {
			std::cout << "Error: Scene " << targetScene << " not found." << std::endl;
		}
	}
}
