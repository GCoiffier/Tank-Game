#include "Ressource_manager.hpp"

RessourceManager::RessourceManager() {
    textures.reserve(100);
    fonts.reserve(2);
}


sf::Texture& RessourceManager::get_texture(const std::string &name) {
     if (textures.find(name) == textures.end() ) {
         // texture not found
         sf::Texture newtexture;
         if(!newtexture.loadFromFile("./static/images/"+name)) {}
         textures.insert({name, newtexture});
     }
     return textures[name];
}

sf::Font& RessourceManager::get_font(const std::string &name) {
     if (fonts.find(name) == fonts.end() ) {
         // font not found
         sf::Font newfont;
         if(!newfont.loadFromFile("./static/fonts/"+name)) {}
         fonts.insert({name, newfont});
     }
     return fonts[name];
}

sf::SoundBuffer& RessourceManager::get_sound(const std::string &name) {
    if (sounds.find(name) == sounds.end() ) {
        // font not found
        sf::SoundBuffer newsound;
        if(!newsound.loadFromFile("./static/music/"+name)) {}
        sounds.insert({name, newsound});
    }
    return sounds[name];
}
//Ressource_manager
RessourceManager RM;


sf::Music menu_music;
sf::Music main_music;
sf::Music dead_music;
