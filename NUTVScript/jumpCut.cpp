#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "InterpreterFunctions.h"

int jumpCut(std::vector<std::string> code, int line) {
	std::string str = code[line];

	if (str.rfind("Jumpcut:", 0) == 0) {
		str.erase(str.begin(), str.begin() + 9); //remove the "Jumpcut:" word and empty space
	}

	std::string targetScene = str;

	if (line == -1) {
		return static_cast<int>(code.size()) - 1;
	}
	int i = 0;

	//if the current line is Perhaps, that means it is an if else statement that has failed, search for
	if (str.rfind("Perhaps", 0) == 0) {
		i = line;
		targetScene = "Break-Time";
	}

	if (line >= 0) {
		for (i; i < code.size(); i++) {
			std::vector<std::string> words{};
			getWords(code[i], words);

			if (!(words.size() == 1 && words[0].empty())) { //checks that the words vector has at least two words in it, and deletes the empty first word if so
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
				return static_cast<int>(code.size()) - 1;
			}
		}
	}
	else {
		std::cout << "Error with """ << code[line] << """ please check syntax." << std::endl;
		return static_cast<int>(code.size()) - 1;
	}
}