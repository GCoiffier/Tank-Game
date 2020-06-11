#include "Utils.hpp"

using namespace std;

/* ------ Path functions ------ */

string getexepath() {
  char result[ PATH_MAX ];
  ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
  return std::string( result, (count > 0) ? count : 0 );
}

string getcwd() {
  char result[ PATH_MAX ];
  ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
  string r = string( result, (count > 0) ? count : 0 );
  size_t found = r.find_last_of("/\\");
  return r.substr(0,found);
}

/* ------ Sound functions ------ */
