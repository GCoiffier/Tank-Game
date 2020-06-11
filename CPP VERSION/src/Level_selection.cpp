#include "Loops.hpp"
#include <sys/stat.h>
#include <unistd.h>

inline bool exists (const std::string& name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}

void selection_menu(sf::RenderWindow &app) {
    Background bg("background_menu.png");
    Cursor mouse;
    sf::Vector2i mousePos;
    sf::Event event;

    std::vector<Button> buttons;
    std::vector<bool> unlocked = get_unlocked();

    Message title(512, 50, 36, "Select a level", "impact.ttf", sf::Color(200,0,0));
    Button back(512, 590, 36, "Back", "impact.ttf", sf::Color(200,0,0));
    Message help_msg(512, 620, 18 ,"You can only select levels you've unlocked. To unlock a level, beat all the previous ones.", "impact.ttf", sf::Color(69,52,16));
    // load the buttons
    int n,i,j;
    for (n = 1 ; n<=NB_LEVEL ; n++) {
        if (i>500) {
            i=0;
            j+=50;
        }
        buttons.emplace_back(100+j,100+i, 20, "#"+std::to_string(n), "impact.ttf" ,sf::Color(200,0,0));
        i+=30;
    }
    int n_customs = n-1;
    int m = 1; i = 0; j = 0;
    while (exists("./static/custom_levels/custom_level"+std::to_string(m)+".txt")) {
        if (i>500) {
            i = 0;
            j+=50;
        }
        buttons.emplace_back(900+j, 100+i, 20, "#custom"+std::to_string(m), "impact.ttf" ,sf::Color(200,0,0));
        i+=30;
        m++;
    }

    while (app.isOpen()) {

        mousePos = sf::Mouse::getPosition(app);

        while(app.pollEvent(event)) {
            // check the type of the event...
            switch (event.type) {
               // window closed
               case sf::Event::Closed:
                   app.close();
                   return;

               // key pressed
               case sf::Event::KeyPressed: {
                   if(sf::Keyboard::Escape)
                       return;
                   break;
               }

              case sf::Event::MouseButtonPressed :
                  if (event.mouseButton.button == sf::Mouse::Left) {
                       if (back.is_lit())
                           return;
                       else {
                           for (int i = 0 ; i < int(buttons.size()); i++) {
                               if (buttons[i].is_lit()) {
                                   menu_music.stop();
                                   if (i>=n_customs) {
                                       bool x = level_loop(i-n_customs+1, true, true, true, app);
                                   } else if (unlocked[i]) {
                                       if (level_loop(i+1, false, true, true, app))
                                            unlocked = get_unlocked();
                                   }
                                   main_music.stop();
                                   menu_music.play();
                               }
                           }
                       }
                  }
                  break;

               // we don't process other types of events
               default:
                   break;
            }
        }

        bg.update(app);
        title.update(app);
        help_msg.update(app);
        back.update(mousePos.x, mousePos.y, app);
        for (int i = 0 ; i < int(buttons.size()); i++) {
            buttons[i].update(mousePos.x, mousePos.y, app);
        }

        mouse.update(mousePos.x, mousePos.y, app);
        app.display();
    }
}
