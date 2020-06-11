#include "Loops.hpp"
#include <iostream>

bool level_loop(int n, bool custom, bool start, bool from_selection, sf::RenderWindow &app) {
    Level level(n, custom);
    sf::Event event;

    Cursor mouse;
    sf::Vector2i mousePos;
    std::list<Bullet>::iterator blist;

    std::vector<bool> unlocked = get_unlocked(); //les niveaux disponibles

    //	Sounds
    ASound clicksound("click_sound.wav");
    ASound shotSound("shot_sound.wav");

    Background bg(n,custom);

    //tutorial messages
    Message help_msg1 (800, 600, 18, "Use the mouse to control your cannon", "impact.ttf", sf::Color(69,52,16));
    Message help_msg2 (800, 630, 18, "and press left click to fire a bullet.", "impact.ttf", sf::Color(69,52,16));
    Message help_msg3 (700, 600, 18, "Use Z,Q,S,D or up, down, left and right to move.", "impact.ttf", sf::Color(69,52,16));
    Message help_msg4 (800, 630, 18, "Press ESC to pause at any moment.", "impact.ttf", sf::Color(69,52,16));
    Message begin_msg(level.pos_player.x, level.pos_player.y-50, 18, "CLICK TO BEGIN !", "impact.ttf", sf::Color(200,0,0));

    Player player(level.pos_player);

    bool has_begun = false;

    // On lance la boucle de jeu
    while (app.isOpen()) {

        mousePos = sf::Mouse::getPosition(app);

        bg.update(app);

        if (has_begun) {
            if (player.is_alive()) {

                // #1 Gestion d'évènements divers
                while(app.pollEvent(event)) {
                    // check the type of the event...
                    switch (event.type) {
                       // window closed
                       case sf::Event::Closed :
                           app.close();
                           break;

                      case sf::Event::MouseButtonPressed :
                          if (event.mouseButton.button == sf::Mouse::Left) {
                              // Player fires a bullet
                              if (player.nb_bullets < player.max_bullet+10000000) {
                                  shotSound.play();
                                  player.fire(mousePos.x, mousePos.y, level.bullets_group);
                              }
                          }
                          break;

                      case sf::Event::LostFocus :
                        {
                        bool quit = pause_menu(bg,level, player, app);
                        if (quit) return true;
                        break;
                        }
                       // we don't process other types of events
                       default:
                           break;
                    }
                }

                // #2 On gère les déplacements du player

                bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) or sf::Keyboard::isKeyPressed(sf::Keyboard::D);
                bool left =  sf::Keyboard::isKeyPressed(sf::Keyboard::Left) or sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
                bool up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up) or sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
                bool down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down) or sf::Keyboard::isKeyPressed(sf::Keyboard::S);
                player.move(right , left , up , down);

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    bool quit = pause_menu(bg, level, player, app);
                    if (quit) return false; // back to main menu
                }

                // 3# Update de tous les sprites

                int enemy_alive = 0;

                // update tanks
                for (auto& IA : level.AI_group) {
                    if (IA.is_alive()) enemy_alive++ ;
                    IA.update(player.pos.x, player.pos.y,
                               level.walls_group, level.pits_group,
                               level.bullets_group, level.AI_group,
                               level.map, false, app);
                }

                // update spawners
                for (auto& spawner : level.all_spawners) {
                    if (spawner.is_alive()) enemy_alive++;
                    spawner.update(player.pos.x, player.pos.y,
                                   level.bullets_group, level.AI_group, app);
                }

                for (auto &pit : level.pits_group) {
                    pit.draw(app);
                }

                // bullets that hit walls
                for (auto &wall: level.walls_group) {
                    for(blist = level.bullets_group.begin(); blist!= level.bullets_group.end(); blist ++) {
                        if (blist->get_rect().intersects(wall.get_rect())) {
                            level.bullets_group.erase(blist--);
                        }
                    }
                    wall.draw(app);
                }

                player.update(mousePos.x , mousePos.y, level.walls_group, level.pits_group, level.bullets_group , level.AI_group, level.map, false, app);

                for(blist = level.bullets_group.begin(); blist!= level.bullets_group.end(); blist ++) {
                    blist->update(app,true);
                }

                if (enemy_alive==0) {// toutes les IA ont été détruites, on a gagné
                    if (not unlocked[n] and not custom) {
                        unlocked[n] = true;  // le niveau suivant est débloqué
                        overwrite_unlocked(unlocked); // on actualise le fichier unlocked
                    }
                    if (from_selection) {
                        // pygame.mixer.music.fadeout(200)
                    }
                    return true;
                }


            } else {   // le player est mort, on affiche la boite de dialogue
                main_music.stop();
                bool k = dead_menu(bg, level, player,  app);
                if (k) // on veut recommencer
                    return level_loop(n, custom, true, from_selection, app);
                return false;
            }
        } else { // le niveau n'a pas commencé : on attend que le player clique
            while(app.pollEvent(event)) {
                // check the type of the event...
                switch (event.type) {
                   // window closed
                   case sf::Event::Closed :
                       app.close();
                       break;

                  case sf::Event::MouseButtonPressed :
                      if (event.mouseButton.button == sf::Mouse::Left) {
                          clicksound.play();
                          if(main_music.getStatus() != sf::Music::Status::Playing)
                            main_music.play();
                          has_begun = true;
                      }
                      break;

                   // we don't process other types of events
                   default:
                       break;
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                bool quit = pause_menu(bg, level, player, app);
                if (quit) return false; // back to main menu
            }

            player.update(mousePos.x , mousePos.y, level.walls_group, level.pits_group, level.bullets_group , level.AI_group, level.map, false, app);

            for (auto& IA : level.AI_group)
                IA.draw(app);

            for (auto& spawner : level.all_spawners)
                spawner.draw(app);

            for (auto &pit : level.pits_group)
                pit.draw(app);

            for (auto &wall: level.walls_group)
                wall.draw(app);

            for(blist = level.bullets_group.begin(); blist!= level.bullets_group.end(); blist ++) {
                blist->draw(app);
            }

            begin_msg.update(app);
        }

        //affichage des messages d'aide dans les premiers niveaux
        if ((n == 1 or n == 2) and not custom) {
            if (n==1) {
                help_msg1.update(app);
                help_msg2.update(app);
            } else {
                help_msg3.update(app);
                help_msg4.update(app);
            }
        }

        mouse.update(mousePos.x, mousePos.y, app);

        // #4 on met à jour l'ensemble de l'image
        app.display();
    }
}
