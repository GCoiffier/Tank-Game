#include <SFML/Graphics.hpp>
#include <string>
#include <limits.h>
#include <unistd.h>

/* ------ Path functions ------ */

std::string getexepath();
// Absolute path of the executable

std::string getcwd();
// Current Worling directory
