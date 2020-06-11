#ifndef IMPORT
#define IMPORT

#include <SFML/Graphics.hpp>
#include "obstacles.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

extern int NB_LEVEL;

int get_voisins(std::array<std::array<int,32>,21> &level, int i, int j, int type);
/* Renvoie les voisins de l'élément T[i][j] sous la forme d'un entier 4 bits.
    1          1         1        1
    Droite | Gauche |  Haut  |   Bas
    Ceci permet de savoir à quel case adjacente sera connecté notre mur.
    Type sert à différencier les différents types de murs (qui ne se connectent pas entre eux)
*/

std::string get_type(const std::string &obs_type, int voisins);

void init_unlocked(bool a);
// inits unlocked level. If a : all level unlocked, else all level locked

std::vector<bool> get_unlocked();
// returns a vect such that vect[i]==true <=> level i is unlocked

void overwrite_unlocked(std::vector<bool> &v);
// write back the player's progression in the unlocked.txt

#endif
