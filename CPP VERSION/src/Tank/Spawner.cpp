#include "AI_Player.hpp"
#include "../Utilities/Ressource_manager.hpp"

int SPAWN_ID = 0;

Spawner::Spawner(const std::string &sprite_name,
        float pos_x, float pos_y, int k,
        bool enhanced) {
    id = SPAWN_ID++;
    thesprite_ok.setTexture(RM.get_texture(sprite_name));
    thesprite_1dmg.setTexture(RM.get_texture("spawner_1dmg.png"));
    thesprite_2dmg.setTexture(RM.get_texture("spawner_2dmg.png"));
    destroyedSprite.setTexture(RM.get_texture("spawner_destroyed.png"));
    enhanced = enhanced;
    hp = k;
    hp_max = k;
    pos.x = pos_x;
    pos.y = pos_y;
    sf::FloatRect r = thesprite_ok.getGlobalBounds();
    thesprite_ok.setOrigin(r.width/2, r.height/2);
    thesprite_ok.setPosition(pos_x, pos_y);
    thesprite_1dmg.setOrigin(r.width/2, r.height/2);
    thesprite_1dmg.setPosition(pos_x, pos_y);
    thesprite_2dmg.setOrigin(r.width/2, r.height/2);
    thesprite_2dmg.setPosition(pos_x, pos_y);
    destroyedSprite.setOrigin(r.width/2, r.height/2);
    destroyedSprite.setPosition(pos_x, pos_y);
    _init_trigger();
    alive = true;
}

Spawner::~Spawner(){}

void Spawner::_init_trigger() {
        time_trigger = 300+(rand()%200);
}

sf::FloatRect Spawner::get_rect() const {
    return thesprite_ok.getGlobalBounds();
}

bool Spawner::is_alive() const {
    return alive;
}

void Spawner::get_dmg(){
    hp--;
}

void Spawner::draw(sf::RenderWindow &bliton) {
    if (is_alive()) {
        switch (hp_max-hp) {
        case 1 :
            bliton.draw(thesprite_1dmg);
            break;
        case 2 :
            bliton.draw(thesprite_2dmg);
            break;
        default:
            bliton.draw(thesprite_ok);
            break;
        }
    } else {
        bliton.draw(destroyedSprite);
    }
}

void Spawner::update(float target_x, float target_y,
                    std::list<Bullet> &bullets,
                    boost::ptr_vector<Tank> &AI_group,
                    sf::RenderWindow &bliton) {
    if (is_alive()) {
        if (time_counter > time_trigger) {
            time_counter = 0;
            _init_trigger();
            if (enhanced)
                AI_group.push_back(new RushAI("tank_corps_spawned.png", "canon_spawnedPlus.png",
                                         pos.x, pos.y, target_x, target_y, id, 1, true));
            else
                AI_group.push_back(new RushAI("tank_corps_spawned.png", "canon_spawned.png",
                                         pos.x, pos.y, target_x, target_y, id, 1, false));

        }
        time_counter++;
        std::list<Bullet>::iterator b;
        for(b = bullets.begin(); b!= bullets.end(); b ++) {
            if (get_rect().intersects(b->get_rect())) {
                bullets.erase(b--);
                get_dmg();
                if (hp==0)
                    alive = false;
            }
        }
    }
    draw(bliton);
}
