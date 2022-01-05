#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

#include "InterpreterFunctions.h"

void run(std::string filename) {
	
	std::ifstream file;
	std::string path = "/Users/defdo/source/repos/NUTVScript/x64/Debug\\"; //this navigates the program to the active directory

	path.append(filename);

	file.open(path); //opens the file the user specified

	if (file.fail()) { //if it fails, notfiy the user
		std::cout << "\nThe program [" << filename << "] was not found!" << std::endl;
		return;
	}
	else { //tell us that it opens okay
		std::cout << "File opened okay!" << std::endl;
	}

	file.close(); //close the file

//	if (!checkHeader()) {
//		std::cout << "Could not parse file, invalid header." << std::endl;
//	}

//	bool error = false;
//	std::string line;


//	while(!error) {
//		std::getline(file, line);
//		std::istringstream stream(line);
//	}

}

bool checkHeader() {



}

std::string readLine() {

}