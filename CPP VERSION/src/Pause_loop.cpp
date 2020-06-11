#include "Loops.hpp"

bool pause_menu(Background &bg, Level &level, Player &p, sf::RenderWindow &app) {
    Button resume(512,250,36,"Resume Game", "impact.ttf", sf::Color(200,0,0));
    Button quitter(512,350,36, "Return to Menu", "impact.ttf", sf::Color(200,0,0));
    Cursor mouse;
    sf::Vector2i mousePos;
    sf::Event event;
    std::list<Bullet>::iterator blist;
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
                      if (resume.is_lit()) {
                          return false;
                      } else if (quitter.is_lit()) {
                          main_music.stop();
                          return true;
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

        resume.update(mousePos.x, mousePos.y, app);
        quitter.update(mousePos.x, mousePos.y, app);
        mouse.update(mousePos.x, mousePos.y, app);

        app.display();


    }
}
