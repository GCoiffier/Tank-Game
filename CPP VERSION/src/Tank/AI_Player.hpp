#ifndef DEF_AI
#define DEF_AI

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <algorithm>
#include <boost/ptr_container/ptr_vector.hpp>
#include <list>
#include <cmath>
#include <cstdlib>
#include <queue>
#include <stack>
#include <array>
#include <iostream>
#include "Tank.hpp"
#include "../obstacles.hpp"

/* Implement the behavior of some basic IA */

class Player : public Tank {
    public:
        Player(float pos_x, float pos_y);
        Player(sf::Vector2f pos);
        void fire(float target_x, float target_y, std::list<Bullet> &bullets);
        int nb_bullets = 0;
        const int max_bullet = 4;

};

class StillAI : public Tank {
    public:
        StillAI(const std::string &tank_name,
                const std::string &canon_name,
                float pos_x, float pos_y,
                float target_x, float target_y,
                int hp, bool plus);
        virtual ~StillAI();

        bool is_plus() {
            return enhanced;
        }

        bool spot_target(float target_x, float target_y, std::vector<Obstacle> &walls, boost::ptr_vector<Tank> &AI_group, sf::RenderWindow &bliton);
        /* Raycasting principle : shoot a virtual bullet. If it ends up on a
           wall, return False (the player is not on sight).
           Else, it arrives on 'target_pos' and return True (the player is on
           sight and a bullet can be shot). */

        void generate_1new_bullet(float target_x, float target_y, std::list<Bullet> &bullets);
        /* fire one bullet in the direction of the target. For normal IA*/

        void generate_3new_bullets(float target_x, float target_y, std::list<Bullet> &bullets);
        /* fire three bullets in a cone in the direction of the target. For plussified IA*/

        void fire(float target_x, float target_y, std::list<Bullet> &bullets);
        /* fire bullet. Calls generate1 or generate3 depending on IA type */

        virtual void update(float target_x, float target_y,
                    std::vector<Obstacle> &walls,
                    std::vector<Obstacle> &pits,
                    std::list<Bullet> &bullets,
                    boost::ptr_vector<Tank> &AI_group,
                    std::array<std::array<int,32>,21> &map,
                    bool in_menu,
                    sf::RenderWindow &bliton);

    protected:
        void _init_trigger();
        int time_trigger;
        int time_counter;
        bool enhanced;
};

class PathAI : public StillAI {
    public:
        PathAI(const std::string &tank_name,
               const std::string &canon_name,
               float pos_x, float pos_y,
               float target_x, float target_y,
               std::vector<sf::Vector2f> &points_list,
               int hp, bool is_plus);
        virtual ~PathAI();

        void basic_move();

        void update(float target_x, float target_y,
                    std::vector<Obstacle> &walls,
                    std::vector<Obstacle> &pits,
                    std::list<Bullet> &bullets,
                    boost::ptr_vector<Tank> &AI_group,
                    std::array<std::array<int,32>,21> &map,
                    bool in_menu,
                    sf::RenderWindow &bliton);

    protected:
        int step;
        std::vector<sf::Vector2f> path;
};


class RushAI : public StillAI {
    public:
        RushAI(const std::string &tank_name,
               const std::string &canon_name,
               float pos_x, float pos_y,
               float target_x, float target_y,
               int id_spawn, int hp, bool is_plus);

        void get_new_path(float target_x, float target_y,
                    std::vector<Obstacle> &walls,
                    std::vector<Obstacle> &pits,
                    std::array<std::array<int,32>,21> &map);
        /* A* algorithm : shortest path to get to the target's position*/

        void basic_move();
        /* goes one step in the path */

        void update(float target_x, float target_y,
                    std::vector<Obstacle> &walls,
                    std::vector<Obstacle> &pits,
                    std::list<Bullet> &bullets,
                    boost::ptr_vector<Tank> &AI_group,
                    std::array<std::array<int,32>,21> &map,
                    bool in_menu,
                    sf::RenderWindow &bliton);

        sf::Vector2i get_cell();

    protected:
        int idspawn = -1;
        int path_timer = 0;
        static const int path_timer_trigger = 200;
        sf::Vector2i cell;
        std::stack<sf::Vector2f> trajectory;
};

extern int SPAWN_ID;

class Spawner {
public:
    Spawner(const std::string &sprite_name, float pos_x, float pos_y, int hp, bool enhanced);
    virtual ~Spawner();

    void draw(sf::RenderWindow &bliton);

    virtual void update(float target_x, float target_y,
                std::list<Bullet> &bullets,
                boost::ptr_vector<Tank> &AI_group,
                sf::RenderWindow &bliton);

    sf::FloatRect get_rect() const;
    void get_dmg();
    bool is_alive() const;

    int id;
    int hp;
    int hp_max;

protected:
    void _init_trigger();
    int time_counter;
    int time_trigger;
    bool alive;
    bool enhanced;
    sf::Vector2f pos;
    sf::Sprite thesprite_ok;
    sf::Sprite thesprite_1dmg;
    sf::Sprite thesprite_2dmg;
    sf::Sprite destroyedSprite;
};

#endif
