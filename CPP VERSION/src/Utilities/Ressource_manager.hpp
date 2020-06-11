#ifndef DEF_RESSOURCE_MANAGER
#define DEF_RESSOURCE_MANAGER

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>

class RessourceManager {
    /* an unordered_map containing every ressources loaded in the game.
        In particular, contains every textures and font used.
        This class prevents similar objects from being loaded several times,
        which is a big gain of memory */
public:
    RessourceManager();
    sf::Texture& get_texture(const std::string &name);
    sf::Font& get_font(const std::string &name);
    sf::SoundBuffer& get_sound(const std::string &name);
    sf::Color& get_color(const std::string &name);
    /* these functions look up the map in search of the objects
     of same name. If the object isnt in the map, it loads it in */

private:
    std::unordered_map<std::string,sf::Texture> textures;
    std::unordered_map<std::string,sf::Font> fonts;
    std::unordered_map<std::string, sf::SoundBuffer> sounds;
    std::unordered_map<std::string, sf::Color> colors;

};

extern RessourceManager RM;


extern sf::Music menu_music;
extern sf::Music main_music;
extern sf::Music dead_music;

#endif
