#ifndef DEF_UTIL_CLASS
#define DEF_UTIL_CLASS

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Ressource_manager.hpp"

class Message {
    public:
        Message(float pos_x, float pos_y, int size, const std::string &text, const std::string &fontname, const sf::Color &col);
        sf::Text get();
        void update(sf::RenderWindow &app);
    private:
        sf::Text thetext;
};

class Button {
    public:
        Button(float pos_x, float pos_y, int size, const std::string &text, const std::string &fontname, const sf::Color &col);
        sf::FloatRect getrect();
        void update(float mouse_x, float mouse_y, sf::RenderWindow &app);
        bool is_lit();
    private:
        bool lit;
        sf::Text thetext;
        sf::Color thecolor;
        sf::Color thelitcolor;
        sf::FloatRect therect;
};


class Cursor {
    public:
        Cursor();
        void update(const float mouse_x, const float mouse_y, sf::RenderWindow &bliton);
    private:
        sf::Sprite thesprite;
};

class Background {
    public:
        Background(const std::string &name);
        Background(int n, bool custom);
        void update(sf::RenderWindow &bliton);
    private:
        sf::Sprite thebg;
};

class ASound {
    public:
        ASound(const std::string &name);
        void play();
    private:
        sf::Sound thesound;
};

#endif
