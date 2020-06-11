#include "AI_Player.hpp"

StillAI::StillAI(const std::string &tank_name,
                 const std::string &canon_name,
                 float pos_x, float pos_y,
                 float target_x, float target_y,
                 int hp, bool plus) :
    Tank(tank_name, canon_name ,pos_x, pos_y, target_x, target_y, hp){
    _init_trigger();
    time_counter = 0;
    enhanced = plus;
}

StillAI::~StillAI() {}

void StillAI::_init_trigger() {
    time_trigger = 20+(rand()%300);
}

bool StillAI::spot_target(float target_x, float target_y,
                          std::vector<Obstacle> &walls,
                          boost::ptr_vector<Tank> &AI_group,
                          sf::RenderWindow &bliton) {
    float angle = get_bullet_angle(target_x, target_y);
    Bullet fake_bullet(pos.x- 32*cos(angle), pos.y + 32*sin(angle), angle);
    sf::FloatRect testRect(0,0,30,30);
    testRect.left = target_x-15;
    testRect.top =  target_y-15;
    while (not testRect.intersects(fake_bullet.get_rect())) {
        fake_bullet.update(bliton,false); //true to see the trajectory for debug
        for (auto& x : AI_group) {
            if (&x != this and fake_bullet.get_rect().intersects(x.get_rect()))
                return false;
        }
        for (const auto& x : walls) {
            if (fake_bullet.get_rect().intersects(x.get_rect()))
                return false;
        }
    }
    return true;
}


void StillAI::generate_1new_bullet(float target_x, float target_y, std::list<Bullet> &bullets){
    bullets.emplace_back(pos.x , pos.y, get_bullet_angle(target_x, target_y));
}

void StillAI::generate_3new_bullets(float target_x, float target_y, std::list<Bullet> &bullets) {
    float delta = 12*M_PI/180; // angular gap between bullets in Radians
    float angle = get_bullet_angle(target_x,target_y);
    bullets.emplace_back(pos.x, pos.y, angle);
    bullets.emplace_back(pos.x, pos.y, angle+delta);
    bullets.emplace_back(pos.x, pos.y, angle-delta);
}


void StillAI::fire(float target_x, float target_y, std::list<Bullet> &bullets) {
    if (is_plus())
        generate_3new_bullets(target_x, target_y, bullets);
    else
        generate_1new_bullet(target_x, target_y, bullets);
}

void StillAI::update(float target_x, float target_y,
            std::vector<Obstacle> &walls,
            std::vector<Obstacle> &pits,
            std::list<Bullet> &bullets,
            boost::ptr_vector<Tank> &AI_group,
            std::array<std::array<int,32>,21> &map,
            bool in_menu,
            sf::RenderWindow &bliton) {
    if ((not in_menu) and is_alive()) {
        if (time_counter > time_trigger and not in_menu) {
            _init_trigger();
            time_counter = 0;
            if (spot_target(target_x, target_y, walls, AI_group, bliton))
                fire(target_x, target_y, bullets);
        }
        time_counter++;
    }
    Tank::update(target_x, target_y, walls, pits, bullets, AI_group, map, in_menu, bliton);
}
