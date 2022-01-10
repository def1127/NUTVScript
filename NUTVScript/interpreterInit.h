#pragma once
#include <map>
void setVars(std::vector<std::string>& code, std::map<std::string, int>& variables);
bool checkHeader(std::string filename, std::vector<std::string>& code);