#include <SFML/Graphics.hpp>
#include "Tank.hpp"
#include <cmath>
#include <cstdlib>

class AdvancedAI : public Tank {
public:
    AdvancedAI(const std::string &tank_name,
               const std::string &canon_name,
               float pos_x, float pos_y,
               float target_x, float target_y,
               int hp, bool is_plus);
};
