#include "Utils_classes.hpp"
#include "Ressource_manager.hpp"

Button::Button(float pos_x, float pos_y, int size, const std::string &text, const std::string &fontname, const sf::Color &col){
    lit = false;
    sf::Text T;
    T.setFont(RM.get_font(fontname));
    T.setString(text);
    T.setCharacterSize(size);
    thecolor = col;
    thelitcolor = thecolor+sf::Color(30,30,30);
    T.setColor(thecolor);
    therect = T.getGlobalBounds();
    T.setPosition(sf::Vector2f(pos_x-therect.width/2,pos_y-therect.height/2));
    therect = T.getGlobalBounds();
    thetext = T;
}

sf::FloatRect Button::getrect(){
    return therect;
}

bool Button::is_lit() {
    return lit;
}

void Button::update(const float mouse_x, const float mouse_y, sf::RenderWindow &bliton){
    if ((therect.contains(mouse_x,mouse_y))^lit) {
        if (lit) {
            thetext.setColor(thecolor);
        }
        else {
            thetext.setColor(thelitcolor);
        }
        lit = !lit;
    }
    bliton.draw(thetext);
}
