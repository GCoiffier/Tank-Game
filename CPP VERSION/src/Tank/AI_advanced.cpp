#ifndef DEF_AI_ADVANCED
#define DEF_AI_ADVANCED

#include "AI_advanced.hpp"

AdvancedAI::AdvancedAI(const std::string &tank_name,
                       const std::string &canon_name,
                       float pos_x, float pos_y,
                       float target_x, float target_y,
                       int hp, bool is_plus) :
    Tank(tank_name, canon_name ,pos_x, pos_y, target_x, target_y, hp){
    is_plus = is_plus;
}

#endif
