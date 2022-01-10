#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

#include "InterpreterFunctions.h"
#include "interpreter.h"
#include "interpreterInit.h"
#include "Exclaim.h"
#include "Set.h"
#include "jumpCut.h"
#include "Perhaps.h"

std::vector<std::string> code; //store the user's program as a vector of strings globally.

std::map<std::string, int> variables;

void run(std::string filename) {

	std::ifstream file;
	std::string path = "/Users/defdo/source/repos/NUTVScript/x64/Debug\\"; //this navigates the program to the active directory

	bool done = false; //has the program finished?

	path.append(filename);

	file.open(path); //opens the file the user specified

	if (file.fail()) { //if it fails, notfiy the user
		std::cout << "\nThe program [" << filename << "] was not found!" << std::endl;
		return;
	}
	else { //loads the file into a vector

		std::string line;

		//clear the code vector before writing to it
		code.erase(code.begin(), code.end());

		while (std::getline(file, line)) { //read lines in to the vector
			std::istringstream iss(line);
			code.push_back(line);
		}
		//clear all vectors in case there is anything left over.
		variables.clear();

		if (!checkHeader(filename, code)) {
			std::cout << "Error: invalid file header, please correct." << std::endl;
			return;
		}

		code.erase(code.begin(), code.begin() + 2); 

		setVars(code, variables);

		for (int i = 0; i < code.size(); i++) {
			std::vector<std::string> words{};

			getWords(code[i], words);

			if (words.size() > 1) {
				if (words[1].rfind("#", 0) == 0) { //if it detects a comment, delete it
					code.erase(code.begin() + i);
					i = i - 1;
				}
				else if (words[1] == "Enter") { //if it detects an Enter command, delete it
					code.erase(code.begin() + i);
					i = i - 1;
				}
			}
			else {
				code.erase(code.begin() + i); //if the line is empty then erase it
				i = i - 1;
			}

		}

		code.insert(code.begin(), "Jumpcut: main"); //insert a jumpcut into the first line of the program so it will start execution at the main scene

		while (!done) {
			for (int i = 0; i < code.size(); i++) {//iterate through the program line by line

				std::vector<std::string> words{};

				getWords(code[i], words);

				if (!(words.size() == 1)) {//iterate through and check what the first word in the line is, this tells us what command to run
					if (words[1] == "Cut!") {
						done = true;
						break;
					}
					else if (words[1] == "Exclaim") {
						exclaim(code, i, variables);
					}
					else if (words[1] == "Set") {
						set(code, i, variables);
					}
					else if (words[1].rfind("#", 0) == 0) {
						continue;
					}
					else if (words[1] == "Scene:") {
						continue;
					}
					else if (words[1] == "Jumpcut:") {
						i = jumpCut(code, i) - 1; //set the line number to the jumpcut line number, subtract one because the for loop increments by one at the end
					}
					else if (words[1] == "Perhaps") {
						perhaps(code, i, variables);
					}
					else if (words[1] == "Break-Time") {
						continue;
					}
					else {
						if (words.size() == 1) {
							continue;
						}
						else {
							std::cout << "Error: Invalid command \"" << code[i] << "\"." << std::endl; //reports an error because the line hasn't been deleted.
							i = code.size() - 2; //exit interpretation
						}
					}
				}
			}
		}

	}

	file.close(); //close the file

}