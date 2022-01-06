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

		if (!checkHeader(filename, code)) {
			std::cout << "Error: invalid file header, please correct." << std::endl;
			return;
		}
		else {
			std::cout << "Header is okay!" << std::endl; //DEBUGGING CODE
		}

		code.erase(code.begin(), code.begin()+2);

		setVars(code, varVals, varNames);

//		for (int i = 0; i < varNames.size(); i++) { //DEBUGGING CODE
//			std::cout << varNames[i] << " is set to " << varVals[i] << std::endl;
//		}

		setFuncs(code, funcNames, funcLines);

//		for (int i = 0; i < funcLines.size(); i++) { //DEBUGGING CODE
//			std::cout << funcNames[i] << " starts on line " << funcLines[i]+1 << std::endl;
//		}

	}

	std::cout << "Ready to start running code!" << std::endl;



	file.close(); //close the file

}

std::string readLine() {
	return "return";
}