#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Level_editor.hpp"
#include "Utilities/Utils.hpp"
#include "Utilities/Utils_classes.hpp"
#include "Utilities/Ressource_manager.hpp"
#include "Level.hpp"
#include "Loops.hpp"
#include "Importation.hpp"

using namespace sf;
using namespace std;

int main() {

	cout << "Current Working Path : "<< getcwd() << endl;
	// init_unlocked(true);

	// Initializing the Window
	sf::RenderWindow app(VideoMode(1024, 672, 32), "Tank Game ! ", Style::Close | Style::Titlebar );
	app.setTitle("Tank Game");
	app.setPosition(sf::Vector2i(200, 100));
	app.setFramerateLimit(60);
	sf::Image icon;
	if(!icon.loadFromFile("./static/images/tank.png")) {}
	app.setIcon(32, 32, icon.getPixelsPtr());

	// Event handling
	Event event;

	// Cursor
	Cursor mouse;
	sf::Vector2i mousePos;
	app.setMouseCursorVisible(false);

	// Background
	Background bg("background_menu.png");

	//	Sounds
	ASound clicksound("click_sound.wav");
	if (!menu_music.openFromFile("./static/music/MenuTheme.ogg")) {}
	if (!main_music.openFromFile("./static/music/MainTheme.ogg")) {}
	if (!dead_music.openFromFile("./static/music/DeadTheme.ogg")) {}
	
	menu_music.play();

	// Level datas
	Level menu(-1, false);

	// titre
	Message title (512, 100, 40, "Tank Game", "impact.ttf", sf::Color(30,30,30));

	// boutons
	Button start_game (512, 200, 36, "Start Game", "impact.ttf", sf::Color(200,0,0));
	Button level_select (512, 300, 36, "Level Selection", "impact.ttf", sf::Color(200,0,0));
	Button editor (512, 400, 36, "Level Editor", "impact.ttf", sf::Color(200,0,0));
	Button options (512, 500, 36, "Options", "impact.ttf", sf::Color(200,0,0));
	Button exit_game (512, 600, 36, "Exit Game", "impact.ttf", sf::Color(200,0,0));

	// Main loop
     while (app.isOpen()) {

		 mousePos = sf::Mouse::getPosition(app);

         while(app.pollEvent(event)) {
			 // check the type of the event...
			 switch (event.type) {
			 	// window closed
			 	case sf::Event::Closed:
			 		app.close();
					return 0;

			 	// key pressed
			 	case sf::Event::KeyPressed: {
			 		if(sf::Keyboard::Escape)
						app.close();
			 	   	break;
			    }

			 	   case sf::Event::MouseButtonPressed :
				 	   if (event.mouseButton.button == sf::Mouse::Left) {
						   	clicksound.play();
				 		   	if (start_game.is_lit()) {
								menu_music.stop();
								int n = 1;
								bool result = level_loop(n,false,true,false, app);
								while (result and n<31)
									result = level_loop(++n,false,false,false, app);
								menu_music.play();
						   	}
							else if (level_select.is_lit()) {
								selection_menu(app);
							}
							else if (editor.is_lit()) {
								menu_music.stop();
								app.close();
								level_editor();
								break;
							}
							else if (options.is_lit()) {
								options_menu();
							}
							else if (exit_game.is_lit()) {
								app.close();
						 		break;
							}
				 	   }
				 	   break;

			 	// we don't process other types of events
			 	default:
			 		break;
			 }
		 }

		 // Update des objets présents
		 bg.update(app);

		 for (auto& ai : menu.AI_group) {
			 ai.update(mousePos.x, mousePos.y,
	                   menu.walls_group, menu.pits_group,
	                   menu.bullets_group, menu.AI_group,
	                   menu.map, true, app);
		 }

		 title.update(app);
		 start_game.update(mousePos.x, mousePos.y, app);
		 level_select.update(mousePos.x, mousePos.y, app);
		 editor.update(mousePos.x, mousePos.y, app);
		 options.update(mousePos.x, mousePos.y, app);
		 exit_game.update(mousePos.x, mousePos.y, app);

		 // Mouse update in last -> cursor on top
		 mouse.update(mousePos.x, mousePos.y, app);
         // Affichage de la fenêtre à l'écran
         app.display();
     }
     return 0;
}
