#include "Utils_classes.hpp"

Background::Background(const std::string &name) {
    thebg.setTexture(RM.get_texture(name));
}

Background::Background(int n, bool custom) {
    if (n==-1 or n>=20 and not custom)
        thebg.setTexture(RM.get_texture("background_menu.png"));
    else
        thebg.setTexture(RM.get_texture("background.png"));
}

void Background::update(sf::RenderWindow &bliton){
    bliton.draw(thebg);
}
