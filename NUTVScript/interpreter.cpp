#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

#include "InterpreterFunctions.h"

std::vector<std::string> code; //store the user's program as a vector of strings globally.
bool checkHeader(std::string filename); //declare the function

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

		for (int i = 0; i < code.size(); i++) { //print out the vector DEBUGGING CODE
			std::cout << code[i] << std::endl;
		}

		if (!checkHeader(filename)) {
			std::cout << "Error: invalid file header, please correct." << std::endl;
		}
		else {
			std::cout << "Header is okay!" << std::endl;
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