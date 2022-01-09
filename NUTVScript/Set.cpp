#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "InterpreterFunctions.h"

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
		varVals[vara] = varVals[varb] + varVals[varc];
	}
	else if (words[3] == "-") {
		varVals[vara] = varVals[varb] - varVals[varc];
	}
	else {
		std::cout << "Error: Invalid set command \"" << code[line] << "\". Proper syntax is 'set [var1] = [var2] [+/-] [var3]" << std::endl; //a catch error if something goes wrong
		line = (int)code.size() - 2;
		return; //set the last line of the program to cause it to gracefully crash
	}


}
