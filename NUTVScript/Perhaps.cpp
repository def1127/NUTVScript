#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "InterpreterFunctions.h"
#include "jumpCut.h"

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
