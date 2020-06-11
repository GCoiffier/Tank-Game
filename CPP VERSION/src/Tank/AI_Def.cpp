#include "AI_Def.hpp"

YellowAI::YellowAI(float pos_x, float pos_y, float target_x, float target_y) :
    StillAI("tank_corps_yellow.png", "canon_yellow.png",
            pos_x, pos_y, target_x, target_y, 1 , false) {}

YellowPlusAI::YellowPlusAI(float pos_x, float pos_y, float target_x, float target_y) :
    StillAI("tank_corps_yellowPlus.png", "canon_yellowPlus.png",
            pos_x, pos_y, target_x, target_y, 1 , true) {}

BlueAI::BlueAI(float pos_x, float pos_y, float target_x, float target_y,
           std::vector<sf::Vector2f> &points_list) :
    PathAI("tank_corps_blue.png", "canon_blue.png",
            pos_x, pos_y, target_x, target_y, points_list, 1 , false) {}

BluePlusAI::BluePlusAI(float pos_x, float pos_y, float target_x, float target_y,
           std::vector<sf::Vector2f> &points_list) :
    PathAI("tank_corps_blue.png", "canon_bluePlus.png",
            pos_x, pos_y, target_x, target_y, points_list, 1 , true) {}

PurpleAI::PurpleAI(float pos_x, float pos_y, float target_x, float target_y,
           std::vector<sf::Vector2f> &points_list) :
    PathAI("tank_corps_purple.png", "canon_purple.png",
            pos_x, pos_y, target_x, target_y, points_list, 3 , false) {}

PurplePlusAI::PurplePlusAI(float pos_x, float pos_y, float target_x, float target_y,
                            std::vector<sf::Vector2f> &points_list) :
     PathAI("tank_corps_purple.png", "canon_purplePlus.png",
             pos_x, pos_y, target_x, target_y, points_list, 3 , true) {}


RedAI::RedAI(float pos_x, float pos_y, float target_x, float target_y) :
    RushAI("tank_corps_red.png", "canon_red.png",
     pos_x, pos_y, target_x, target_y,-1,  1 , false) {}


RedPlusAI::RedPlusAI(float pos_x, float pos_y, float target_x, float target_y) :
    RushAI("tank_corps_red.png", "canon_redPlus.png",
     pos_x, pos_y, target_x, target_y, -1, 1 , true) {}

SpawnerSimple::SpawnerSimple(float pos_x, float pos_y) :
    Spawner( "spawner.png", pos_x, pos_y, 1, false) {}

SpawnerPlus::SpawnerPlus(float pos_x, float pos_y) :
    Spawner( "spawnerPlus.png", pos_x, pos_y, 3, true) {}

DarkIA::DarkIA(float pos_x, float pos_y, float target_x, float target_y) :
    AdvancedAI("tank_corps_dark.png" , "canon_dark.png", pos_x, pos_y, target_x, target_y, 1, false) {}

DarkPlusIA::DarkPlusIA(float pos_x, float pos_y, float target_x, float target_y) :
    AdvancedAI("tank_corps_dark.png" , "canon_darkPlus.png", pos_x, pos_y, target_x, target_y, 1, true) {}
