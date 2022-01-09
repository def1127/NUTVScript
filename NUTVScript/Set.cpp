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

	if ((words.size() == 5 && words[0] == "")) { //checks that the words vector has at least 4 words in it, and deletes the empty first word if so
		words.erase(words.begin(), words.begin() + 2);
	}

	if (words.size() == 3) { //this checks for the case were set var = var2 or set var = number
		int vara = findVar(varNames, words[0], code, line);
		if (is_number(words[2])) {
			//word 2 is a number
			varVals[vara] = std::stoi(words[2]);
			return;
		}
		else {
			//it is not a number
			int varb = findVar(varNames, words[2], code, line);
			varVals[vara] = varVals[varb];
			return;
		}
	}

	if (!((words.size() == 5) && words[1] == "=" && (words[3] == "+" || words[3] == "-"))) { //check that there are the proper number of words and that there is an equals sign and a +/-
		std::cout << "Error, set command callled incorrectly \"" << code[line] << "\". Proper syntax is 'set [var1] = [var2] [+/-] [var3]'" << std::endl;
		line = (int)code.size() - 2;
		return; //set the last line of the program to cause it to gracefully crash
	}

	//find the 3 variables needed.
	//need to check if words 2 or 4 are numbers or text so you can set numbers if you don't want them as variables
	int vara = findVar(varNames, words[0], code, line); //store the INDEX of a

	int varb, varc;

	if (is_number(words[2])) {
		//word 2 is a number
		varb = std::stoi(words[2]); //STORE THE VALUE OF THE NUMBER
	}
	else {
		//it is not a number
		varb = varVals[findVar(varNames, words[2], code, line)]; //STORE THE INDEX OF THE VARIABLE
	}

	if (is_number(words[4])) {
		//word 4 is a number
		varc = std::stoi(words[4]); //STORE THE VALUE OF THE NUMBER
	}
	else {
		//it is not a number
		varc = varVals[findVar(varNames, words[4], code, line)]; //STORE THE INDEX OF THE VARIABLE
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
		line = (int)code.size() - 2;
		return; //set the last line of the program to cause it to gracefully crash
	}


}
