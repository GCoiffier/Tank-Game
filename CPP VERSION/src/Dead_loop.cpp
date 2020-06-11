#include "Loops.hpp"

bool dead_menu(Background &bg, Level &level, Player &p, sf::RenderWindow &app) {
    Button recommencer(512,220, 36, "Try Again", "impact.ttf", sf::Color(200,0,0));
    Button quitter(512,350, 36, "Return to Menu", "impact.ttf", sf::Color(200,0,0));
    Message you_died(512,150, 50, "You Died !", "impact.ttf", sf::Color(69,52,16));
    sf::Event event;
    Cursor mouse;
    sf::Vector2i mousePos;
    std::list<Bullet>::iterator blist;
    dead_music.play();

    while (true) {
        mousePos = sf::Mouse::getPosition(app);

        while(app.pollEvent(event)) {
            // check the type of the event...
            switch (event.type) {
               // window closed
               case sf::Event::Closed :
                   app.close();
                   break;

              case sf::Event::MouseButtonPressed :
                  if (event.mouseButton.button == sf::Mouse::Left) {
                      if (recommencer.is_lit()) {
                          dead_music.stop();
                          return true;
                      } else if (quitter.is_lit()) {
                          dead_music.stop();
                          return false;
                      }
                  }
                  break;

               // we don't process other types of events
               default:
                   break;
            }
        }

        bg.update(app);

        p.draw(app);

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

        you_died.update(app);
        recommencer.update(mousePos.x, mousePos.y, app);
        quitter.update(mousePos.x, mousePos.y, app);
        mouse.update(mousePos.x, mousePos.y, app);

        app.display();
    }
}
