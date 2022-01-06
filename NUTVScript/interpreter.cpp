#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

#include "InterpreterFunctions.h"
#include "interpreter.h"

std::vector<std::string> code; //store the user's program as a vector of strings globally.

std::vector<int> varVals; //store the variable values
std::vector<std::string> varNames; //store the variable names

std::vector<int> funcLines; //store the lines that functions start on
std::vector<std::string> funcNames; //store the function names

int line; //store the current line number
int prevFuncLine; //stores the line the program was running before starting a new function

bool checkHeader(std::string filename); //declare the function

char delimiter = ' '; //space character

void run(std::string filename) {
	
	std::ifstream file;
	std::string path = "/Users/defdo/source/repos/NUTVScript/x64/Debug\\"; //this navigates the program to the active directory

	path.append(filename);

	file.open(path); //opens the file the user specified

	if (file.fail()) { //if it fails, notfiy the user
		std::cout << "\nThe program [" << filename << "] was not found!" << std::endl;
		return;
	}
	else { //tell us that it opens okay and loads the file into a vector
		std::cout << "File opened okay!" << std::endl;

		std::string line;

		while (std::getline(file, line)) { //read lines in to the vector
			std::istringstream iss(line);
			code.push_back(line);
		}

//		for (int i = 0; i < code.size(); i++) { //print out the vector DEBUGGING CODE
//			std::cout << code[i] << std::endl;
//		}

		if (!checkHeader(filename)) {
			std::cout << "Error: invalid file header, please correct." << std::endl;
		}
		else {
			std::cout << "Header is okay!" << std::endl; //DEBUGGING CODE
		}

		setVars();

		for (int i = 0; i < varNames.size(); i++) { //DEBUGGING CODE
			std::cout << varNames[i] << " is set to " << varVals[i] << std::endl;
		}

		setFuncs();

		for (int i = 0; i < funcLines.size(); i++) { //DEBUGGING CODE
			std::cout << funcNames[i] << " starts on line " << funcLines[i]+1 << std::endl;
		}

	}

	file.close(); //close the file

}

bool checkHeader(std::string filename) {
	std::string str = code[0];
	if (str.rfind(filename, 0) == 0) {
		str = code[1];
		if (str.rfind("Written By:", 0) == 0) {
			return true;
		}
	}
	return false;
}

std::string readLine() {
	return "return";
}

void setVars(){
	std::string str;

	for (int i = 0; i < code.size(); i++) {//iterate through the program line by line
		
		std::vector<std::string> words{};
		str = code[i];
		std::stringstream sstream(code[i]); //put the line of code into a string stream
		std::string word;

		do { //erase the string stream word by word in to a vector of words
			word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());
			words.push_back(word);
		} while (std::getline(sstream,word,delimiter));
		
		if (!(words.size() == 1 && words[0] == "")) { //checks that the words vector has at least two words in it, and deletes the empty first word if so
			words.erase(words.begin());
		}

		if (words[0] == "Enter") { //if it detects the word "Enter" the keyphrase for declaring a variable
			if (!(words.size() == 4)) { //check that the format is "Enter [name] = [val]"
				std::cout << "Error: Variable declared improperly on line " << i+1 << std::endl; //give an error for wrong variables
				std::exit(0);
			}
			varNames.push_back(words[1]); //add the variable name and value to the vector
			varVals.push_back(std::stoi(words[3]));
		}
	}
}

void setFuncs(){
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
				std::cout << "Error: Scene declared improperly on line " << i+1 << std::endl; //give an error for wrong function declaration
				std::exit(0);
			}
			funcNames.push_back(words[1]); //add the variable name and value to the vector
			funcLines.push_back(i);
		}
	}
}
