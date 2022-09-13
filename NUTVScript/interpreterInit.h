#pragma once
#include <map>
void setVars(const std::vector<std::string>& code, std::map<std::string, int>& variables, std::string filename);
bool checkHeader(const std::string& filename, std::vector<std::string>& code);
void correctVars(const std::vector <std::string>& code, std::map<std::string, int>& variables, std::string filename);