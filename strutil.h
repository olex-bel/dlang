#ifndef STRUTIL_H
#define STRUTIL_H

#include <string>

std::string trim(const std::string& str);
bool str2int (int &i, const std::string& str, int base = 10);

#endif
