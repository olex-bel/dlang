#ifndef STRUTIL_H
#define STRUTIL_H

#include <string>

std::string trim(const std::string& str);
bool str2int32(int32_t &i, const std::string& str, int base = 10);
bool str2double(double &i, const std::string &str);

#endif
