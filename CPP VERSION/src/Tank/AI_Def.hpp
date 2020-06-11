#include <SFML/Graphics.hpp>
#include <vector>
#include "AI_Player.hpp"
#include "AI_advanced.hpp"

/* Implements IA that are loaded in the game. Relies on AI_Player.hpp to get behavior */

class YellowAI : public StillAI {
public:
    YellowAI(float pos_x, float pos_y, float target_x, float target_y);
};

class YellowPlusAI : public StillAI {
public:
    YellowPlusAI(float pos_x, float pos_y, float target_x, float target_y);
};

class BlueAI : public PathAI {
public:
    BlueAI(float pos_x, float pos_y, float target_x, float target_y,
           std::vector<sf::Vector2f> &points_list);
};

class BluePlusAI : public PathAI {
public:
    BluePlusAI(float pos_x, float pos_y, float target_x, float target_y,
           std::vector<sf::Vector2f> &points_list);
};

class PurpleAI : public PathAI {
public:
    PurpleAI(float pos_x, float pos_y, float target_x, float target_y,
           std::vector<sf::Vector2f> &points_list);
};

class PurplePlusAI : public PathAI {
public:
    PurplePlusAI(float pos_x, float pos_y, float target_x, float target_y,
           std::vector<sf::Vector2f> &points_list);
};

class RedAI : public RushAI {
public:
    RedAI(float pos_x, float pos_y, float target_x, float target_y);
};

class RedPlusAI : public RushAI{
public:
    RedPlusAI(float pos_x, float pos_y, float target_x, float target_y);
};

class SpawnerSimple : public Spawner {
public:
    SpawnerSimple(float pos_x, float pos_y);
};

class SpawnerPlus : public Spawner {
public:
    SpawnerPlus(float pos_x, float pos_y);
};


class DarkIA : public AdvancedAI {
public:
    DarkIA(float pos_x, float pos_y, float target_x, float target_y);
};

class DarkPlusIA : public AdvancedAI {
public:
    DarkPlusIA(float pos_x, float pos_y, float target_x, float target_y);
};
