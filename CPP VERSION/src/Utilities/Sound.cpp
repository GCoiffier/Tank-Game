#include "Utils_classes.hpp"


ASound::ASound(const std::string &name) {
    thesound.setBuffer(RM.get_sound(name));
}


void ASound::play() {
    thesound.play();
}
