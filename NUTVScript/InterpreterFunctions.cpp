#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "InterpreterFunctions.h"

char delim = ' '; //space character

void exclaim(std::vector<std::string> code, int &line, std::vector<std::string> varNames, std::vector<int> varVals) { //code to enable the "Exclaim" command
	std::string str = code[line];
	str.erase(str.begin(),str.begin()+8); //remove the "Exclaim" word and empty space

	std::vector<std::string> words{};
	std::stringstream sstream(code[line]); //put the line of code into a string stream
	std::string word;

	do { //erase the string stream word by word in to a vector of words
		word.erase(std::remove_if(word.begin(), word.end(), isspace), word.end());
		words.push_back(word);
	} while (std::getline(sstream, word, delim));

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
			for (int j = 0; j < varNames.size(); j++) { //iterate through the variables vector to find the index of the variable selected
				if (varNames[j] == words[i]) {
					std::cout << varVals[j] << " ";
					break;
				}
				else if (j == varNames.size() - 1) {
					std::cout << "\nError: variable " << words[i] << " not found, check that all variables have already been declared." << std::endl;
					line = code.size() - 2;
					return; //set the last line of the program to cause it to gracefully crash
				}
			}
		}
	}
	std::cout << std::endl;
}

void set(std::vector<std::string> code, int &line, std::vector<int>& varVals, std::vector<std::string>& varNames) {

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
		words.erase(words.begin(), words.begin() + 2);
	}

	if (!((words.size() == 5) && words[1] == "=" && (words[3] == "+" || words[3] == "-"))) { //check that there are the proper number of words and that there is an equals sign and a +/-
		std::cout << "Error, set command callled incorrectly \"" << code[line] << "\". Proper syntax is 'set [var1] = [var2] [+/-] [var3]'" << std::endl;
		line = code.size() - 2;		
		return; //set the last line of the program to cause it to gracefully crash
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
			line = code.size() - 2;
			return; //set the last line of the program to cause it to gracefully crash
		}
	}
	for (int i = 0; i < varNames.size(); i++) { //iterate through the variables vector to find the index of the variable selected
		if (varNames[i] == words[2]) {
			varb = varVals[i];
			break;
		}
		else if (i == varNames.size() - 1) {
			std::cout << "Error: variable " << words[2] << " not found, check that all variables have already been declared." << std::endl;
			line = code.size() - 2;
			return; //set the last line of the program to cause it to gracefully crash
		}
	}
	for (int i = 0; i < varNames.size(); i++) { //iterate through the variables vector to find the index of the variable selected
		if (varNames[i] == words[4]) {
			varc = varVals[i];
			break;
		}
		else if (i == varNames.size() - 1) {
			std::cout << "Error: variable " << words[4] << " not found, check that all variables have already been declared." << std::endl;
			line = code.size() - 2;
			return; //set the last line of the program to cause it to gracefully crash
		}
	}
	//perform the actual operations
	if (words[3] == "+") { 
		varVals[vara] = varb + varc;
	}
	else if (words[3] == "-") {
		varVals[vara] = varb - varc;
	}
	else {
		std::cout << "Error: Invalid set command \"" << code[line] << "\". Proper syntax is 'set [var1] = [var2] [+/-] [var3]" << std::endl; //a catch error if something goes wrong
		line = code.size() - 2;
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
		return code.size() - 1;
	}
	int i = 0;

	//if the current line is Perhaps, that means it is an if else statement that has failed, search for
	if (str.rfind("Perhaps", 0) == 0) {
		i = line;
		targetScene = "Break-Time";
	}

	if(line >= 0){
		for (i; i < code.size(); i++) {
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
			else if (words.size() == 1 && words[0] == targetScene) { //this line takes care of the perhaps statements
				return i;
			}
			else if (i == code.size() - 1) {
				std::cout << "Error: Scene " << targetScene << " not found." << std::endl;
				return code.size() - 1;
			}
		}

	}
}

void perhaps(std::vector<std::string> code, int& line, std::vector<int>& varVals, std::vector<std::string>& varNames) {

	std::string str = code[line];
	str.erase(str.begin(), str.begin() + 8); //remove the "Perhaps" word and empty space

	std::vector<std::string> words{};
	std::stringstream sstream(str); //put the line of code into a string stream
	std::string word;

	do { //erase the string stream word by word in to a vector of words
		word.erase(std::remove_if(word.begin(), word.end(), isspace), word.end());
		words.push_back(word);
	} while (std::getline(sstream, word, delim));

	if ((words.size() == 4 && words[0] == "")) { //checks that the words vector has at least 5 words in it, and deletes the empty first word if so
		words.erase(words.begin());
	}

	//logic

	if (words.size() != 3 && !(words[1] == ">" || words[1] == "=" || words[1] == "<")) {
		std::cout << "Error with line " << code[line] << ". Perhaphs command called incorrectly, proper syntax is 'Perhaps var [>/=/<] var'" << std::endl;
		line = code.size() - 2;
		return;
	}
	//the size is 3 and the condition is in the middle, now search for the vars to perform the operation.
	int vara, varb;

	//find the 2 variables needed.
	for (int i = 0; i < varNames.size(); i++) { //iterate through the variables vector to find the index of the variable selected
		if (varNames[i] == words[0]) {
			vara = varVals[i];
			break;
		}
		else if (i == varNames.size() - 1) {
			std::cout << "Error: variable " << words[0] << " not found, check that all variables have already been declared." << std::endl;
			line = code.size() - 2;
			return; //set the last line of the program to cause it to gracefully crash
		}
	}
	for (int i = 0; i < varNames.size(); i++) { //iterate through the variables vector to find the index of the variable selected
		if (varNames[i] == words[2]) {
			varb = varVals[i];
			break;
		}
		else if (i == varNames.size() - 1) {
			std::cout << "Error: variable " << words[2] << " not found, check that all variables have already been declared." << std::endl;
			line = code.size() - 2;
			return; //set the last line of the program to cause it to gracefully crash
		}
	}

	//now figure out what the condition is and whether or not it is true

	if (words[1] == "<") {
		if (vara < varb) {
			return; //keep interpreting
		}
		else {
			line = jumpCut(code, line);
		}
	}
	else if (words[1] == ">") {
		if (vara > varb) {
			return;
		}
		else {
			line = jumpCut(code, line);
		}
	}
	else if (words[1] == "=") {
		if (vara == varb) {
			return;
		}
		else {
			line = jumpCut(code, line);
		}
	}
	else {
		std::cout << "Error with line " << code[line] << ". Perhaphs command called incorrectly, proper syntax is 'Perhaps var [>/=/<] var'" << std::endl; //this is a catch error that should never be triggered
		line = code.size() - 2;
	}



	
	return;
}