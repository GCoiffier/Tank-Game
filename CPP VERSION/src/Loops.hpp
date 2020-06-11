#ifndef DEF_LOOPS
#define DEF_LOOPS

#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "obstacles.hpp"
#include "Level.hpp"
#include "Importation.hpp"
#include "Utilities/Utils_classes.hpp"

void options_menu();

void selection_menu(sf::RenderWindow &app);

bool pause_menu(Background &bg, Level &level, Player &p,  sf::RenderWindow &app);

bool dead_menu(Background &bg, Level &level, Player &p, sf::RenderWindow &app);

bool level_loop(int n, bool custom, bool start, bool from_selection, sf::RenderWindow &app);

#endif
