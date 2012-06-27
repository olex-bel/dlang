#include <cstdlib>
#include <limits>
#include <errno.h>
#include "strutil.h"

using std::string;
using std::numeric_limits;

string trim(const string& str)
{
  char space[] = " \t\n\v\f\r";

  size_t start = str.find_first_not_of(space);
  size_t end = str.find_last_not_of(space);

  if ( start == string::npos )
    return string();

  return str.substr(start, end-start+1);
}

bool str2int32(int32_t &i, const string &str, int base)
{
  const char* s = str.c_str(); 
  char *end;
  long  l;
  
  errno = 0;
    
  l = strtol(s, &end, base);

  if (errno == ERANGE || l > numeric_limits<int32_t>::max() || l < numeric_limits<int32_t>::min()) {
    return false;
  }

  if (*s == '\0' || *end != '\0') {
    return false;
  }

  i = l;
  return true;
}

bool str2double(double &i, const string &str)
{
  const char* s = str.c_str(); 
  char *end;
  double  l;
  
  errno = 0;
    
  l = strtod(s, &end);

  if (errno == ERANGE ) {
    return false;
  }

  if (*s == '\0' || *end != '\0') {
    return false;
  }

  i = l;
  return true;
}
