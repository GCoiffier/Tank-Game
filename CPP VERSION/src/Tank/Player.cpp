#include "AI_Player.hpp"

Player::Player(float pos_x, float pos_y) :
    Tank("tank_corps_regular.png", "canon_regular.png", pos_x, pos_y, 1) {}

Player::Player(sf::Vector2f pos) :
    Tank("tank_corps_regular.png", "canon_regular.png", pos.x, pos.y, 1) {}

void Player::fire(float target_x, float target_y, std::list<Bullet> &bullets){
    nb_bullets++;
    // Attention à prendre en compte les dimensions du tank qui tire le boulet
    bullets.emplace_back(pos.x, pos.y, get_bullet_angle(target_x, target_y));
}
