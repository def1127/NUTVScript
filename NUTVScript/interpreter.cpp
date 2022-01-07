#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

#include "InterpreterFunctions.h"
#include "interpreter.h"
#include "interpreterInit.h"

std::vector<std::string> code; //store the user's program as a vector of strings globally.

std::vector<int> varVals; //store the variable values
std::vector<std::string> varNames; //store the variable names

std::vector<int> funcLines; //store the lines that functions start on
std::vector<std::string> funcNames; //store the function names

void run(std::string filename) {
	
	std::ifstream file;
	std::string path = "/Users/defdo/source/repos/NUTVScript/x64/Debug\\"; //this navigates the program to the active directory

	bool done = false; //has the program finished?
	int line; //store the current line number
	int prevFuncLine; //stores the line the program was running before starting a new function

	path.append(filename);

	file.open(path); //opens the file the user specified

	if (file.fail()) { //if it fails, notfiy the user
		std::cout << "\nThe program [" << filename << "] was not found!" << std::endl;
		return;
	}
	else { //tell us that it opens okay and loads the file into a vector
		std::cout << "File opened okay!" << std::endl;

		std::string line;
		
		//clear the code vector before writing to it
		code.erase(code.begin(), code.end());

		while (std::getline(file, line)) { //read lines in to the vector
			std::istringstream iss(line);
			code.push_back(line);
		}
		//clear all vectors in case there is anything left over.
		varNames.erase(varNames.begin(), varNames.end());
		varVals.erase(varVals.begin(), varVals.end());
		funcLines.erase(funcLines.begin(), funcLines.end());
		funcNames.erase(funcNames.begin(), funcNames.end());

		if (!checkHeader(filename, code)) {
			std::cout << "Error: invalid file header, please correct." << std::endl;
			return;
		}
		else {
			std::cout << "Header is okay!" << std::endl; //DEBUGGING CODE
		}

		code.erase(code.begin(), code.begin()+2); //this messes up with the line number error codes.

		/*
		Could insert a section to iterate through and remove lines with comments, would save processing time later
		Also could remove all "Enter" commands since variables are global and all are stored when the program initializes
		*/

		setVars(code, varVals, varNames);

		//setFuncs(code, funcNames, funcLines);

		std::cout << "Ready to start running code!" << std::endl;

		while (!done) {
			std::string str;
			for (int i = 0; i < code.size(); i++) {//iterate through the program line by line

				std::vector<std::string> words{};
				str = code[i];
				std::stringstream sstream(code[i]); //put the line of code into a string stream
				std::string word;

				do { //erase the string stream word by word in to a vector of words
					word.erase(std::remove_if(word.begin(), word.end(), isspace), word.end());
					words.push_back(word);
				} while (std::getline(sstream, word, ' '));
				if (!(words.size() == 1)) {
					if (words[1] == "Cut!") {
						done = true;
						break;
					}
					else if (words[1] == "Exclaim") {
						exclaim(code, i);
					}
					else if (words[1] == "Set") {
						set(code, i, varVals, varNames);
					}
					else if (words[1] == "#") {
						continue;
					}
					else if (words[1] == "Scene:") {
						continue;
					}
					else if (words[1] == "Jumpcut:") {
						i = jumpCut(code, i) - 1;
					}
					else {
						if (words.size() == 1) {
							continue;
						}
						else {
							std::cout << "Error: Invalid command on line " << i << "." << std::endl; //reports an error because the line hasn't been deleted.
						}
					}
				}
			}
		}

	}

	file.close(); //close the file

}

std::string readLine() {
	return "return";
}