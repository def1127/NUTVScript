#pragma once

void getWords(std::stringstream& sstream, std::vector<std::string> &words);
int findVar(std::vector<std::string> varNames, std::string strToMatch, std::vector<std::string> code, int& line);