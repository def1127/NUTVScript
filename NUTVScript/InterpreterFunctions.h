#pragma once

void exclaim(std::vector<std::string> code, int& line, std::vector<std::string> varNames, std::vector<int> varVals);
void set(std::vector<std::string> code, int &line, std::vector<int>& varVals, std::vector<std::string>& varNames);
int jumpCut(std::vector<std::string> code, int line);
