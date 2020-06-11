#include "Bullet.hpp"

int BULLET_ID = 0;

Bullet::Bullet(float x, float y, float angle) {
    id = BULLET_ID++;
    if(!thetexture.loadFromFile("./static/images/bullet.png")) {}
    thesprite.setTexture(thetexture);
    true_pos = sf::Vector2f(x + 32*cos(angle), y - 32*sin(angle));
    offset = sf::Vector2f(speed * cos(angle), -speed * sin(angle));
    sf::FloatRect t = thesprite.getGlobalBounds();
    thesprite.setPosition(sf::Vector2f(true_pos.x-t.width/2,true_pos.y-t.height/2));
}

sf::FloatRect Bullet::get_rect() const {
    return thesprite.getGlobalBounds();
}

void Bullet::draw(sf::RenderWindow &bliton) const {
    bliton.draw(thesprite);
}

void Bullet::update(sf::RenderWindow &bliton, bool blit = true) const {
    true_pos.x += offset.x;
    true_pos.y += offset.y;
    thesprite.setPosition(true_pos);
    if (blit) draw(bliton);
}

bool operator == (const Bullet & obj1, const Bullet & obj2) {
    return (obj1.id == obj2.id);
}
