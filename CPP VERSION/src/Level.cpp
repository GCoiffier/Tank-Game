#include "Level.hpp"

Level::Level(int n, bool custom) {
    using namespace std;
    // ----- #1 Ouverture du fichier txt correspondant -----
    ifstream level_file;
    string level_name;
    if (n == -1) // menu
        level_name = "levels/menu.txt";
    else if (n == -2) // Training mode
        level_name = "levels/training.txt";
    else
        if (custom)
            level_name = "custom_levels/custom_level"+to_string(n)+".txt";
        else
            level_name = "levels/level"+to_string(n)+".txt";
    level_file.open("./static/" + level_name);

    /* ----- #2 on remplit la matrice des murs -----
     on récupère le placement des IA, etc. */
    int n_blues = 0;
    for (int i = 0 ; i<21 ; i++) {
        for (int j = 0 ; j<32 ; j++) {
            int x;
            level_file >> x;
            if (x==6 or x==7 or x==10 or x==11) n_blues++;
            map[i][j]=x;
        }
    }

    /* ---- #3 On obtient la liste des points de déplacement des IA bleues -----
    -> sous forme de liste non-organisée en tuples des coordonnées des
     points à atteindre : x1 y1 x2 y2 x3 y3 etc.
     points_list contiendra l"ensemble des trajectoires des IA du niveau */

    level_file.ignore(0);

    for (int k = 0 ; k < n_blues ; k++) {
        vector<sf::Vector2f> traj;
        int n;
        while (level_file >> n) {
            traj.clear();
            for (int i = 0 ; i<n ; i++) {
                float x,y;
                level_file >> x >> y;
                traj.emplace_back(32*x+16,32*y+16);
            }
        trajectories.push_back(traj);
        }
    }

    /*
    for (unsigned int i = 0 ; i < trajectories.size() ; i++) {
        for (unsigned int j = 0 ; j< trajectories[i].size() ; j++) {
            cout << trajectories[i][j].x << " "  << trajectories[i][j].y << " ";
        }
        cout << "\n";
    }
    */

    level_file.close();

    /* ----- #4 Construction de tous les objets ----- */
    int nb_traj = 0;
    for (int i = 0 ; i < 21 ; i++) {
        for (int j = 0 ; j < 32 ; j++) {
            int pos_x = 32*j;
            int pos_y = 32*i;
            if (map[i][j] == 1) { //wall
                    string name = get_type("wall", get_voisins(map, i, j, 1));
                    walls_group.push_back(Obstacle(name, i, j, false));
            } else if (map[i][j] == 2) { //pit
                    const string name = get_type("pit", get_voisins(map, i, j, 2));
                    pits_group.push_back(Obstacle(name, i, j, true ));
            } else {
                pos_x+=16;
                pos_y+=16; // Pour les IA, on prend en compte le centre et pas le coin topleft
                if (map[i][j]==3)
                    pos_player = sf::Vector2f(float(pos_x),float(pos_y));
                else {
                    switch (map[i][j]) {
                        case 4: //yellow
                            AI_group.push_back(new YellowAI(pos_x, pos_y, 0 , 0));
                            break;
                        case 5: //yellowPlus
                            AI_group.push_back(new YellowPlusAI(pos_x, pos_y, 0 , 0));
                            break;
                        case 6: //blue
                            AI_group.push_back(new BlueAI(pos_x, pos_y, 0 , 0, trajectories[nb_traj++]));
                            break;
                        case 7: //bluePlus
                            AI_group.push_back(new BluePlusAI(pos_x, pos_y, 0 , 0, trajectories[nb_traj++]));
                            break;
                        case 8: //red
                            AI_group.push_back(new RedAI(pos_x, pos_y, 0 , 0));
                            break;
                        case 9: //redPlus
                            AI_group.push_back(new RedPlusAI(pos_x, pos_y, 0 , 0));
                            break;
                        case 10: //purple
                            AI_group.push_back(new PurpleAI(pos_x, pos_y, 0 , 0, trajectories[nb_traj++]));
                            break;
                        case 11: //purplePlus
                            AI_group.push_back(new PurplePlusAI(pos_x, pos_y, 0 , 0, trajectories[nb_traj++]));
                            break;
                        case 12: //spawner
                            all_spawners.push_back(new SpawnerSimple(pos_x, pos_y));
                            break;
                        case 13: //spawnerPlus
                            all_spawners.push_back(new SpawnerPlus(pos_x, pos_y));
                            break;
                        case 14: //Dark
                            AI_group.push_back(new DarkIA(pos_x, pos_y, 0 , 0));
                            break;
                        case 15: //DarkPlus
                            AI_group.push_back(new DarkPlusIA(pos_x, pos_y, 0 , 0));
                            break;
                        default: //shouldn't happen
                            break;
                        } // end switch
                } // end else
            } //end else

        } //end for (j)
    }// end for (i)
} // end fun

void Level::debug() {
    using namespace std;
    cout << "------ Level map : ------ \n";
    for (int j = 0 ; j<21 ; j++) {
        for (int i = 0 ; i<32 ; i++) {
            cout << map[j][i] << " ";
        }
    cout << endl;
    }
}
