#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "InterpreterFunctions.h"

char delim = ' '; //space character

void exclaim(std::vector<std::string> code, int& line, std::vector<std::string> varNames, std::vector<int> varVals) { //code to enable the "Exclaim" command
	std::string str = code[line];
	str.erase(str.begin(), str.begin() + 8); //remove the "Exclaim" word and empty space

	std::vector<std::string> words{};
	std::stringstream sstream(code[line]); //put the line of code into a string stream
	
	getWords(sstream, words);

	if (words.size() > 2) {
		words.erase(words.begin(), words.begin() + 2);
	}

	for (int i = 0; i < words.size(); i++) {
		if (!(words[i].at(0) == '%')) {
			if (words.size() > 1) {
				if (!(words[i].at(0) == '/' && words[i].at(1) == '%')) {
					std::cout << words[i] << " ";
				}
				else {
					words[i].erase(words[i].begin());
					std::cout << words[i] << " ";
				}
			}
			else {
				std::cout << words[i] << " ";
			}
		}
		else {
			words[i].erase(words[i].begin()); //get rid of the percent sign
				//find the variable need.

			std::cout << varVals[findVar(varNames, words[i], code, line)] << " ";

		}
	}
	std::cout << std::endl;
}

void set(std::vector<std::string> code, int& line, std::vector<int>& varVals, std::vector<std::string>& varNames) {

	std::string str = code[line];
	str.erase(str.begin(), str.begin() + 4); //remove the "Set" word and empty space

	std::vector<std::string> words{};
	std::stringstream sstream(code[line]); //put the line of code into a string stream
	
	getWords(sstream, words);


	if ((words.size() == 7 && words[0] == "")) { //checks that the words vector has at least 6 words in it, and deletes the empty first word if so
		words.erase(words.begin(), words.begin() + 2);
	}

	if (!((words.size() == 5) && words[1] == "=" && (words[3] == "+" || words[3] == "-"))) { //check that there are the proper number of words and that there is an equals sign and a +/-
		std::cout << "Error, set command callled incorrectly \"" << code[line] << "\". Proper syntax is 'set [var1] = [var2] [+/-] [var3]'" << std::endl;
		line = (int)code.size() - 2;
		return; //set the last line of the program to cause it to gracefully crash
	}

	//find the 3 variables needed.
	int vara = findVar(varNames, words[0], code, line);
	int varb = findVar(varNames, words[2], code, line);
	int varc = findVar(varNames, words[4], code, line);

	//perform the actual operations
	if (words[3] == "+") {
		varVals[vara] = varb + varc;
	}
	else if (words[3] == "-") {
		varVals[vara] = varb - varc;
	}
	else {
		std::cout << "Error: Invalid set command \"" << code[line] << "\". Proper syntax is 'set [var1] = [var2] [+/-] [var3]" << std::endl; //a catch error if something goes wrong
		line = (int)code.size() - 2;
		return; //set the last line of the program to cause it to gracefully crash
	}


}

int jumpCut(std::vector<std::string> code, int line) {
	std::string str = code[line];


	if (str.rfind("Jumpcut:", 0) == 0) {
		str.erase(str.begin(), str.begin() + 9); //remove the "Jumpcut:" word and empty space
	}

	std::string targetScene = str;

	if (line == -1) {
		return (int)code.size() - 1;
	}
	int i = 0;

	//if the current line is Perhaps, that means it is an if else statement that has failed, search for
	if (str.rfind("Perhaps", 0) == 0) {
		i = line;
		targetScene = "Break-Time";
	}

	if (line >= 0) {
		for (i; i < code.size(); i++) {
			std::vector<std::string> words{};
			str = code[i];
			std::stringstream sstream(code[i]); //put the line of code into a string stream

			getWords(sstream, words);

			if (!(words.size() == 1 && words[0] == "")) { //checks that the words vector has at least two words in it, and deletes the empty first word if so
				words.erase(words.begin());
			}

			if ((words.size() == 2) && words[0] == "Scene:" && words[1] == targetScene) { //checks if the first word is Scene and the second word on the line is the target scene
				return i;
			}
			else if (words.size() == 1 && words[0] == targetScene) { //this line takes care of the perhaps statements
				return i;
			}
			else if (i == code.size() - 1) {
				std::cout << "Error: Scene " << targetScene << " not found." << std::endl;
				return (int)code.size() - 1;
			}
		}

	}
	else {
		std::cout << "Error with """ << code[line] << """ please check syntax." << std::endl;
		return (int)code.size() - 1;
	}
}

void perhaps(std::vector<std::string> code, int& line, std::vector<int>& varVals, std::vector<std::string>& varNames) {

	std::string str = code[line];
	str.erase(str.begin(), str.begin() + 8); //remove the "Perhaps" word and empty space

	std::vector<std::string> words{};
	std::stringstream sstream(str); //put the line of code into a string stream

	getWords(sstream, words);

	if ((words.size() == 4 && words[0] == "")) { //checks that the words vector has at least 5 words in it, and deletes the empty first word if so
		words.erase(words.begin());
	}

	//logic

	if (words.size() != 3 && !(words[1] == ">" || words[1] == "=" || words[1] == "<")) {
		std::cout << "Error with line " << code[line] << ". Perhaphs command called incorrectly, proper syntax is 'Perhaps var [>/=/<] var'" << std::endl;
		line = (int)code.size() - 2;
		return;
	}
	//the size is 3 and the condition is in the middle, now search for the vars to perform the operation.
	int vara, varb;

	//find the 2 variables needed.
	vara = findVar(varNames, words[0], code, line);

	varb = findVar(varNames, words[2], code, line);

	//now figure out what the condition is and whether or not it is true

	if (words[1] == "<") {
		if (varVals[vara] < varVals[varb]) {
			return; //keep interpreting
		}
		else {
			line = jumpCut(code, line);
		}
	}
	else if (words[1] == ">") {
		if (varVals[vara] > varVals[varb]) {
			return;
		}
		else {
			line = jumpCut(code, line);
		}
	}
	else if (words[1] == "=") {
		if (varVals[vara] == varVals[varb]) {
			return;
		}
		else {
			line = jumpCut(code, line);
		}
	}
	else {
		std::cout << "Error with line " << code[line] << ". Perhaphs command called incorrectly, proper syntax is 'Perhaps var [>/=/<] var'" << std::endl; //this is a catch error that should never be triggered
		line = (int)code.size() - 2;
	}

	return;
}

void getWords(std::stringstream& sstream, std::vector<std::string>& words) {
	std::string word;

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