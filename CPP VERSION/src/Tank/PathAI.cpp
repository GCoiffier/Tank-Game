#include "AI_Player.hpp"


PathAI::PathAI(const std::string &tank_name,
               const std::string &canon_name,
               float pos_x, float pos_y,
               float target_x, float target_y,
               std::vector<sf::Vector2f> &points_list,
               int chp, bool is_plus) :
       StillAI(tank_name, canon_name, pos_x, pos_y, target_x, target_y, chp, is_plus) {
           hp = chp;
           step = 0;
           path = points_list;
}

PathAI::~PathAI() {}

void PathAI::basic_move() {
    if (not path.empty()) {
        float pos_x = get_rect().left + get_rect().width/2;
        float pos_y = get_rect().top + get_rect().height/2;
        float goal_x = path[step].x;
        float goal_y = path[step].y;
        if (abs(pos_x - goal_x)>speed or abs(pos_y-goal_y)>speed) {
            stopvertical();
            if (pos_x < goal_x - speed) moveright();
            else if (pos_x > goal_x + speed) moveleft();
            else {
                stophorizontal();
                if (pos_y < goal_y - speed) movedown();
                else if (pos_y > goal_y + speed) moveup();
            }
        } else { // arrival
            step++;
            stop();
            if (step == int(path.size()))
                step = 0;
        }
    }
}

void PathAI::update(float target_x, float target_y,
            std::vector<Obstacle> &walls,
            std::vector<Obstacle> &pits,
            std::list<Bullet> &bullets,
            boost::ptr_vector<Tank> &AI_group,
            std::array<std::array<int,32>,21> &map,
            bool in_menu,
            sf::RenderWindow &bliton) {
    if (not in_menu) //deal with the path the AI must follow :
        basic_move();
    StillAI::update(target_x, target_y, walls, pits, bullets, AI_group, map, in_menu, bliton);
}
