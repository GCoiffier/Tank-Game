#include "Utils_classes.hpp"

Message::Message(float x, float y, int size, const std::string &text, const std::string &fontname, const sf::Color &col){
    thetext.setFont(RM.get_font(fontname));
    thetext.setString(text);
    thetext.setCharacterSize(size);
    thetext.setColor(col);
    thetext.setPosition(sf::Vector2f(x- thetext.getGlobalBounds().width/2,y- thetext.getGlobalBounds().height/2));
}

void Message::update(sf::RenderWindow &bliton){
    bliton.draw(thetext);
}

sf::Text Message::get() {
    return thetext;
}
