#include "Importation.hpp"

int NB_LEVEL = 31;

int get_voisins(std::array<std::array<int,32>,21> &map, int i, int j, int type) {
    int n = 21;
    int m = 32;
    int voisins = 0;
    /* 1        1       1         1
    Droite | Gauche |  Haut  |   Bas */

    if (i == 0) {
        if (j == 0) {     // si sur le coin en haut à gauche
                voisins += map[i][j + 1]==type ? 1<<3 : 0; //droite
                voisins += map[i + 1][j]==type ? 1 : 0; //bas
        }
        else if (j == m-1) { // si sur le coin en haut à droite
            voisins += map[i][j - 1]==type ? 1<<2 : 0; //gauche
            voisins += map[i - 1][j]==type ? 1 : 0; //bas
        }
        else {          // si en haut
            voisins += map[i][j - 1]==type ? 1<<2 : 0; //gauche
            voisins += map[i][j + 1]==type ? 1<<3 : 0; //droite
            voisins += map[i + 1][j]==type ? 1 : 0; //bas
        }
    } else if (i == n-1) {
        if (j == 0) {     // si sur le coin en bas à gauche
            voisins += map[i][j + 1]==type ? 1<<3 : 0; //droite
            voisins += map[i - 1][j]==type ? 1<<1 : 0; //haut
        }
        else if (j == m-1) {  // si sur le coin en bas à droite
            voisins += map[i][j - 1]==type ? 1<<2 : 0; //gauche
            voisins += map[i - 1][j]==type ? 1<<1 : 0; //haut
        }
        else {          // si en bas
            voisins += map[i][j - 1]==type ? 1<<2 : 0; //gauche
            voisins += map[i][j + 1]==type ? 1<<3 : 0; //droite
            voisins += map[i - 1][j]==type ? 1<<1 : 0; //haut
        }
    } else {
        if (j == 0) { // si à gauche
            voisins += map[i][j + 1]==type ? 1<<3 : 0; //droite
            voisins += map[i - 1][j]==type ? 1<<1 : 0; //haut
            voisins += map[i + 1][j]==type ? 1 : 0; //bas
        }
        else if (j == m-1){ // si à droite
            voisins += map[i][j - 1]==type ? 1<<2 : 0; //gauche
            voisins += map[i - 1][j]==type ? 1<<1 : 0; //haut
            voisins += map[i + 1][j]==type ? 1 : 0; //bas
        }
        else { // au milieu
            voisins += map[i][j - 1]==type ? 1<<2 : 0; //gauche
            voisins += map[i][j + 1]==type ? 1<<3 : 0; //droite
            voisins += map[i - 1][j]==type ? 1<<1 : 0; //haut
            voisins += map[i + 1][j]==type ? 1 : 0; //bas
        }
    }
    return voisins;
}


std::string get_type(const std::string &obs_type, int voisins) {
    // consider all the possible cases.
    switch (voisins) {
        case 0:
            return obs_type+"_square.png";
        case 1:
            return obs_type+"_edge_T.png";
        case 2:
            return obs_type+"_edge_B.png";
        case 3:
            return obs_type+"_vertical.png";
        case 4:
            return obs_type+"_edge_L.png";
        case 5:
            return obs_type+"_cornerBL.png";
        case 6:
            return obs_type+"_cornerTL.png";
        case 7:
            return obs_type+"_T_R.png";
        case 8:
            return obs_type+"_edge_R.png";
        case 9:
            return obs_type+"_cornerBR.png";
        case 10:
            return obs_type+"_cornerTR.png";
        case 11:
            return obs_type+"_T_L.png";
        case 12:
            return obs_type+"_horizontal.png";
        case 13:
            return obs_type+"_T_T.png";
        case 14:
            return obs_type+"_T_B.png";
        case 15:
            return obs_type+"_X.png";
        default:
            return "not found";
    }
}

void init_unlocked(bool a) {
    std::ofstream file;
    file.open("./unlocked.txt");
    file << "1 1 ";
    for (int i = 0 ; i<NB_LEVEL-1; i++)
        file << (a ? "1 " : "0 ");
    file.close();
}

std::vector<bool> get_unlocked() {
    std::ifstream file;
    file.open("./unlocked.txt");
    std::vector<bool> unlocked;
    bool read;
    while (file >> read)
        unlocked.push_back(read);
    file.close();
    return unlocked;
}


void overwrite_unlocked(std::vector<bool> &v) {
    std::ofstream file;
    file.open("./unlocked.txt");
    for (int i = 0 ; i<int(v.size()); i++)
        file << to_string(v[i]) << " ";
    file.close();
}
