#ifndef DEF_OBSTACLES
#define DEF_OBSTACLES

#include <SFML/Graphics.hpp>
#include <string>
#include "Utilities/Ressource_manager.hpp"

class Obstacle {
    // A wall or a Pit
public:
    Obstacle(const std::string &name, int i, int j, bool through);
    void draw(sf::RenderWindow &bliton);
    bool bullet_goes_through() const ;
    sf::FloatRect get_rect() const ;
private:
    sf::Sprite thesprite;
    sf::Vector2f pos;
    bool bullet_through;
};

class DestructibleObstacle : public Obstacle {
    public:
        void get_shot();
        bool is_destroyed();
    private:
        bool destroyed;
        int dmg = 0;
        int max_shots = 5;

};

#endif
