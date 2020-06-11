#include "Utils_classes.hpp"

Cursor::Cursor() {
    thesprite.setTexture(RM.get_texture(std::string("cursor.png")));
}

void Cursor::update(const float mouse_x, const float mouse_y, sf::RenderWindow &bliton){
    thesprite.setPosition(mouse_x,mouse_y);
    bliton.draw(thesprite);
}
