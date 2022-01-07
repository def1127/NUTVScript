#pragma once

void setVars(std::vector<std::string>& code, std::vector<int>& varVals, std::vector<std::string>& varNames);
bool checkHeader(std::string filename, std::vector<std::string>& code);
bool is_number(const std::string& s);
