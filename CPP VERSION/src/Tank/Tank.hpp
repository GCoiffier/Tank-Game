#ifndef DEF_TANK
#define DEF_TANK

extern int TANK_ID;

#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include <utility>
#include <list>
#include <boost/ptr_container/ptr_vector.hpp>
#include <iostream>
#include "Bullet.hpp"
#include "../obstacles.hpp"

class Tank {
/* Tank: the tank used by the player and the AI's.
    Consists of a Body and a Canon.  */
public:

    Tank(const std::string &tank_name, const std::string &canon_name, float pos_x, float pos_y, int hp);
    Tank(const std::string &tank_name, const std::string &canon_name, float pos_x, float pos_y, float target_x, float target_y, int hp);
    virtual ~Tank();

    bool is_alive() const;
    bool set_alive(bool a);
    void get_dmg();

    sf::FloatRect get_rect() const;

    /* Movement logic */
    void moveright();
    void moveleft();
    void moveup();
    void movedown();
    void stophorizontal();
    void stopvertical();
    void stop();
    void move(bool right, bool left, bool up, bool down);
    /* Makes one move for the tank in one of the 8 directions possible */

    void collide_with(std::vector<Obstacle> &obs);

    void set_goal_angle(float angle);

    /* Bullet logic  */
    float get_bullet_angle(float target_x, float target_y);
    /* calcule l'angle de la trajectoire du nouveau boulet.
    (target_x,target_y) représente la position de la cible */

    /* Display */
    void draw(sf::RenderWindow &bliton);
    virtual void update(float target_x, float target_y,
                        std::vector<Obstacle> &walls,
                        std::vector<Obstacle> &pits,
                        std::list<Bullet> &bullets,
                        boost::ptr_vector<Tank> &AI_group,
                        std::array<std::array<int,32>,21> &map,
                        bool in_menu,
                        sf::RenderWindow &bliton);
    int id;

    sf::Vector2f pos;

protected:
    void _update_body_angle();
    void _rotate_canon(float target_x, float target_y);
    sf::Sprite bodySprite;
    sf::Sprite canonSprite;
    sf::Sprite deadSprite;
    sf::Vector2f target_pos;
    float movepos[2] = {0,0};
    float angle = 0; // angles en DEGRES
    float goal_angle = 0; // angles en DEGRES
    const float rotation_step = 15; // angles en DEGRES
    const float speed = 1;
    bool alive;
    int hp = 1;
};

#endif
