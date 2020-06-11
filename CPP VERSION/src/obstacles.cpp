#include "obstacles.hpp"

Obstacle::Obstacle(const std::string &name, int i, int j, bool through) {
    thesprite.setTexture(RM.get_texture(name));
    bullet_through = through;
    pos = sf::Vector2f(float(32*j), float(32*i));
    thesprite.setPosition(pos);
}

sf::FloatRect Obstacle::get_rect() const {
    return thesprite.getGlobalBounds();
}

void Obstacle::draw(sf::RenderWindow &bliton) {
    bliton.draw(thesprite);
}

bool Obstacle::bullet_goes_through() const {
    return bullet_through;
}
