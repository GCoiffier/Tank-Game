#ifndef DEF_LEVEL
#define DEF_LEVEL

#include <SFML/Graphics.hpp>
#include <vector>
#include <boost/ptr_container/ptr_vector.hpp>
#include <utility>
#include <array>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Importation.hpp"
#include "obstacles.hpp"
#include "Tank/Tank.hpp"
#include "Tank/AI_Def.hpp"
#include "Utilities/Utils.hpp"

class Level {
    /* The level class contains every information needed to run a level.
        The constructor reads what it needs from the txt file of the level
        and builds every object. These objects (AI, walls,...) are
        then stored into std::vector
    */
    public:
        Level(int n, bool custom);
        void debug();
        std::array<std::array<int,32>,21> map;
        std::vector<Obstacle> walls_group;
        std::vector<Obstacle> pits_group;
        sf::Vector2f pos_player;
        std::vector<std::vector<sf::Vector2f>> trajectories;
        boost::ptr_vector<Tank> AI_group;
        boost::ptr_vector<Spawner> all_spawners;
        std::list<Bullet> bullets_group;
};



#endif
