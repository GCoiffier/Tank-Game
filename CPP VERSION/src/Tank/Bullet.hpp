#ifndef DEF_BULLET
#define DEF_BULLET

extern int BULLET_ID;

#include <SFML/Graphics.hpp>
#include <cmath>

class Bullet {
    public:
         Bullet(float x, float y, float angle);
         void update(sf::RenderWindow &bliton, bool blit) const;
         void draw(sf::RenderWindow &bliton) const ;
         sf::FloatRect get_rect() const;
         float angle; //Radians
         int id;
    private:
        int speed = 2;
        mutable sf::Sprite thesprite;
        sf::Texture thetexture;
        sf::Vector2f offset;
        mutable sf::Vector2f true_pos;
};

bool operator == (const Bullet & obj1, const Bullet & obj2);


#endif
