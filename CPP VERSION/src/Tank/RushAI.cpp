#include "AI_Player.hpp"

RushAI::RushAI(const std::string &tank_name,
       const std::string &canon_name,
       float pos_x, float pos_y,
       float target_x, float target_y,
       int id_spawn, int hp, bool is_plus) :
       StillAI(tank_name, canon_name, pos_x, pos_y, target_x, target_y, hp, is_plus) {
       idspawn = idspawn;
       cell = sf::Vector2i(int(pos_x/32), int(pos_y/32));
}

sf::Vector2i RushAI::get_cell() {
    return cell;
}


/* A* algorithm : utility functions */

struct Cell {
    sf::Vector2i coords;
    int dist;
    bool operator () (const Cell &a, const Cell &b) const {
        return a.dist < b.dist;
    }
};



void get_voisins(auto& map, std::vector<sf::Vector2i> &voisins, sf::Vector2i &pos) {
    int x = pos.x;
    int y = pos.y;
    if (y>0 and (map[y-1][x]!=1) and (map[y-1][x]!=2))
        voisins.emplace_back(x,y-1);
    if (x>0 and (map[y][x-1]!=1) and (map[y][x-1]!=2))
        voisins.emplace_back(x-1,y);
    if (y<20 and (map[y+1][x]!=1) and (map[y+1][x]!=2))
        voisins.emplace_back(x,y+1);
    if (x<31 and (map[y][x+1]!=1) and (map[y][x+1]!=2))
        voisins.emplace_back(x+1,y);
}

void RushAI::get_new_path(float target_x, float target_y,
            std::vector<Obstacle> &walls,
            std::vector<Obstacle> &pits,
            std::array<std::array<int,32>,21> &map) {
    // dump old trajectory :
    while (not trajectory.empty()) {
        trajectory.pop();
    }
    sf::Vector2i goal_pos( int(target_x/32) , int(target_y/32));
    sf::Vector2i init_pos = get_cell();

    // declare and init data containers for A*
    std::array<std::array<bool,32>,21> seen;
    std::array<std::array<int,32>,21> distance;
    std::array<std::array<sf::Vector2i,32>,21> passage;

    //std::priority_queue<Cell, std::vector<Cell>, Cell> pq;
    std::queue<Cell> pq;
    for (int i = 0 ; i< 21 ; i++) {
        for (int j = 0 ; j < 32 ; j++) {
            seen[i][j] = false;
            distance[i][j] = 1000*1000*1000;
            passage[i][j] = sf::Vector2i(-1,-1);
        }
    }
    distance[init_pos.y][init_pos.x] = 0;
    pq.push({init_pos,0});

    // reach out for goal position
    while (not seen[goal_pos.y][goal_pos.x]) {
        if (pq.empty()) return;
        Cell c = pq.front(); pq.pop();
        int cx = c.coords.x;
        int cy = c.coords.y;
        if (not seen[cy][cx]) {
            int new_distance;
            std::vector<sf::Vector2i> voisins;
            get_voisins(map, voisins, c.coords);
            for (auto& v : voisins) {
                new_distance = distance[cy][cx] + 1 + (goal_pos.x-v.x)*(goal_pos.x-v.x)+(goal_pos.y-v.y)*(goal_pos.y-v.y);
                if ((not seen[v.y][v.x]) and new_distance < distance[v.y][v.x]) {
                        distance[v.y][v.x] = new_distance;
                        passage[v.y][v.x] = sf::Vector2i(cx,cy);
                    }
                pq.push({v,distance[v.y][v.x]});
                }
            seen[cy][cx] = true;
        }
    }

    // fallback to initial position
    sf::Vector2i pos = goal_pos;
    std::vector<sf::Vector2i> traj;
    while (pos != init_pos) {
        traj.emplace_back(pos.x,pos.y);
        pos = passage[pos.y][pos.x];
    }

    // clean useless points (3 points aligned => middle one can go)
    std::vector<bool> keep(traj.size(), true);
    for (int i = 1 ; i < int(traj.size())-1 ;i++) {
        sf::Vector2i p = traj[i];
        sf::Vector2i prec = traj[i-1];
        sf::Vector2i suiv = traj[i+1];
        if ((p.x == suiv.x and p.x == prec.x) or (p.y == suiv.y and p.y == prec.y)) {
            keep[i]=false;
        }
    }

    // fill the trajectory stack
    for (int i = 0 ; i < int(traj.size()) ;i++) {
        if (keep[i]) {
            trajectory.push(sf::Vector2f(traj[i].x, traj[i].y));
        }
    }

    /*
    std::cout << "seen matrix : \n";
    for (int i = 0 ; i< 21 ; i++) {
        for (int j = 0 ; j < 32 ; j++) {
            std::cout << seen[i][j] << " ";
        }
        std::cout << "\n";
    }
    */

}


void RushAI::basic_move() {
    sf::FloatRect r = get_rect();
    float pos_x = r.left + r.width/2;
    float pos_y = r.top + r.height/2;
    float goal_x = (trajectory.top().x)*32+16;
    float goal_y = (trajectory.top().y)*32+16;
    if (abs(pos_x - goal_x) > speed or abs(pos_y - goal_y) > speed) {
        // we're still not at the goal point
        stopvertical();
        if (pos_x < goal_x - speed) //always move on x first.
            moveright();
        else if (pos_x > goal_x + speed) moveleft();
        else {
            stophorizontal();
            if (pos_y < goal_y - speed)  movedown();
            else if (pos_y > goal_y + speed) moveup();
        }
    } else {
        // we arrived at the point -> go to next point
        stop();
        trajectory.pop();
    }
    cell.x = int(get_rect().left/32);
    cell.y = int(get_rect().top/32);
    path_timer++;
}


void RushAI::update(float target_x, float target_y,
            std::vector<Obstacle> &walls,
            std::vector<Obstacle> &pits,
            std::list<Bullet> &bullets,
            boost::ptr_vector<Tank> &AI_group,
            std::array<std::array<int,32>,21> &map,
            bool in_menu,
            sf::RenderWindow &bliton) {
    if (not in_menu) {
        if (trajectory.empty() or path_timer == path_timer_trigger) {
            path_timer = 0;
            get_new_path(target_x, target_y, walls, pits, map);
        }
        basic_move();
    }
    StillAI::update(target_x, target_y, walls, pits, bullets, AI_group, map, in_menu, bliton);
}
