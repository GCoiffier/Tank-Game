#include "Tank.hpp"
#include "../Utilities/Ressource_manager.hpp"

int TANK_ID = 0;

Tank::Tank(const std::string &tank_name, const std::string &canon_name, float pos_x, float pos_y, int nhp){
    id = TANK_ID++;
    hp = nhp;
    bodySprite.setTexture(RM.get_texture(tank_name));
    canonSprite.setTexture(RM.get_texture(canon_name));
    deadSprite.setTexture(RM.get_texture("tank_destroyed.png"));
    sf::FloatRect r = bodySprite.getGlobalBounds();
    bodySprite.setOrigin(r.width/2, r.height/2);
    bodySprite.setPosition(pos_x, pos_y);
    deadSprite.setOrigin(r.width/2, r.height/2);
    deadSprite.setPosition(pos_x, pos_y);
    r = canonSprite.getGlobalBounds();
    canonSprite.setOrigin(r.width/2, r.height/2);
    canonSprite.setPosition(pos_x, pos_y);
    alive = true;
    pos = sf::Vector2f(pos_x, pos_y);
}

Tank::Tank(const std::string &tank_name,
           const std::string &canon_name,
           float pos_x, float pos_y,
           float target_x, float target_y, int hp){
    id = TANK_ID++;
    hp = hp;
    bodySprite.setTexture(RM.get_texture(tank_name));
    canonSprite.setTexture(RM.get_texture(canon_name));
    deadSprite.setTexture(RM.get_texture("tank_destroyed.png"));
    sf::FloatRect r = bodySprite.getGlobalBounds();
    bodySprite.setOrigin(r.width/2, r.height/2);
    bodySprite.setPosition(pos_x, pos_y);
    deadSprite.setOrigin(r.width/2, r.height/2);
    deadSprite.setPosition(pos_x, pos_y);
    r = canonSprite.getGlobalBounds();
    canonSprite.setOrigin(r.width/2, r.height/2);
    canonSprite.setPosition(pos_x, pos_y);
    alive = true;
    pos = sf::Vector2f(pos_x, pos_y);
    target_pos = sf::Vector2f(target_x, target_y);
    _rotate_canon(target_x, target_y);
}

Tank::~Tank() {}

bool Tank::is_alive() const {
    return alive;
}

bool Tank::set_alive(bool a){
    alive = a;
}

sf::FloatRect Tank::get_rect() const {
    return bodySprite.getGlobalBounds();
}

void Tank::set_goal_angle(float angle) {
    goal_angle = angle;
}


void Tank::moveright()      { movepos[0] = speed; goal_angle = 0;}
void Tank::moveleft()       { movepos[0] = -speed; goal_angle = 180;}
void Tank::moveup()         { movepos[1] = -speed; goal_angle = -90;}
void Tank::movedown()       { movepos[1] = speed; goal_angle = 90;}
void Tank::stophorizontal() { movepos[0] = 0;}
void Tank::stopvertical()   { movepos[1] = 0;}
void Tank::stop()           { movepos[0] = 0; movepos[1] = 0;}

void Tank::move(bool right, bool left, bool up, bool down) {
    // Case 1: right was hit and left was not
    if (right and not left) {
        moveright();
        // deal with up and down keys
        if (up and not down)
            goal_angle = 45;
        else if (down and not up)
            goal_angle = -45;
    }
    // Counter-case 1: left was hit and right was not
    else if (left and not right) {
        moveleft();
        if (up and not down)
            goal_angle = -135;
        else if (down and not up)
            goal_angle = 135;
    }
    // Case 2: up was hit and down was not
    if (up and not down) {
        moveup();
        if (right and not left)
            goal_angle = -45;
        else if (left and not right)
            goal_angle = -135;
    }
    // Counter-case 2: down was hit and up was not
    else if (down and not up) {
        movedown();
        if (right and not left)
            goal_angle = 45;
        else if (left and not right)
            goal_angle = 135;
    }
    // Case 3: stop cases
    if ((not right and not left) or (right and left))
        stophorizontal();
    if ((not up and not down) or (up and down))
        stopvertical();
}


void Tank::_update_body_angle() {
    float delta = (goal_angle-angle);
    if (delta > 180)
        delta -= 360;
    if (delta < -180)
        delta += 360;
    if (delta > 5)
        angle += rotation_step;
    else if (delta < -5)
        angle -= rotation_step;
}


void Tank::collide_with(std::vector<Obstacle> &obs){
    for (const auto& w : obs) {
        sf::FloatRect tankrec = get_rect();
        sf::FloatRect obsrec = w.get_rect();
        if (tankrec.intersects(obsrec)) {
            // On a percuté un mur. On trouve la direction à bloquer;
            float pos_x = tankrec.left + tankrec.width/2;
            float pos_y = tankrec.top + tankrec.height/2;
            float obs_x = obsrec.left + obsrec.width/2;
            float obs_y = obsrec.top + obsrec.height/2;
            if ((pos_x<obs_x and movepos[0] == 1) or (pos_x>obs_x and movepos[0] == -1))
                movepos[0] = 0;
            if ((pos_y<obs_y and movepos[1] == 1) or (pos_y>obs_y and movepos[1] == -1))
                movepos[1] = 0;
        }
    }
}

/* Bullet logic */
float Tank::get_bullet_angle(float target_x, float target_y) {
    sf::FloatRect r = bodySprite.getGlobalBounds();
    float dx = r.left+r.width/2- target_x;
    float dy = r.top+r.height/2- target_y;
    return atan2(dx,dy)+M_PI_2; // Angle en radians
}

void Tank::_rotate_canon(float target_x, float target_y) {
    canonSprite.setRotation(atan2(target_x-pos.x,pos.y-target_y)*180/M_PI + 180);
}

void Tank::draw(sf::RenderWindow &bliton) {
    if (is_alive()) {
        bliton.draw(bodySprite);
        bliton.draw(canonSprite);
    } else {
        bliton.draw(deadSprite);
    }
}


void Tank::get_dmg(){
    hp--;
}

void Tank::update(float target_x, float target_y,
                  std::vector<Obstacle> &walls,
                  std::vector<Obstacle> &pits,
                  std::list<Bullet> &bullets,
                  boost::ptr_vector<Tank> &AI_group,
                  std::array<std::array<int,32>,21> &map,
                  bool in_menu,
                  sf::RenderWindow &bliton) {
    if (is_alive()) {
        //test collisions with other bullets :
        std::list<Bullet>::iterator b;
        for(b = bullets.begin(); b != bullets.end(); b ++) {
            if (get_rect().intersects(b->get_rect())) {
                bullets.erase(b--);
                get_dmg();
                if (hp==0) set_alive(false);
            }
        }
        collide_with(walls);
        collide_with(pits);
        target_pos = sf::Vector2f(target_x, target_y);
        target_pos = sf::Vector2f(target_x, target_y);
        pos += sf::Vector2f(movepos[0]*speed, movepos[1]*speed);
        _update_body_angle();
        _rotate_canon(target_x, target_y);
        bodySprite.setRotation(angle);
        deadSprite.setRotation(angle);
        bodySprite.move(movepos[0],movepos[1]);
        canonSprite.move(movepos[0], movepos[1]);
        deadSprite.move(movepos[0], movepos[1]);
    }
    draw(bliton);
}
