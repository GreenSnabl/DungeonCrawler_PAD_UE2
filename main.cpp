/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: den
 *
 * Created on April 19, 2018, 8:32 PM
 */

#include <string>
#include "GameEngine.h"

#include "DungeonGFXMap.h"
//#include "Character.h"

using std::string;


int main(int argc, char** argv) {

    
    GameEngine game2("Maps/Map1.txt", "Maps/Connector1.txt");
    game2.run();
    
    /*
    int imap[] = {
        202, 202, 202, 202, 202, 202, 202, 202, 202, 202,
        202, 202, 202, 202, 202, 202, 202, 202, 202, 202,
        202, 202, 202, 202, 202, 202, 202, 202, 202, 202,
        202, 202, 202, 202, 202, 202, 202, 202, 202, 202,
        202, 202, 202, 202, 202, 2, 202, 202, 202, 202,
        202, 202, 202, 202, 202, 202, 202, 202, 202, 202,
        202, 202, 202, 202, 202, 24, 202, 202, 202, 202,
        202, 202, 202, 202, 202, 202, 202, 202, 202, 202,
        202, 202, 202, 202, 202, 202, 202, 202, 202, 202,
        202, 202, 202, 202, 202, 202, 202, 202, 202, 202        
    };
    
    /*
    while (game2.getMap()->getRenderWindow().isOpen())
	{
		sf::Event event;
		while (game2.getMap()->getRenderWindow().pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				game2.getMap()->getRenderWindow().close();
                }
                
                game2.getMap()->getRenderWindow().display();        
        }
    
    
    DungeonGFX::Map map(imap);
    sf::RenderWindow window(sf::VideoMode(320, 320), "asd");
    map.draw(window);
    
    
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
                }
                map.draw(window);
                window.display();        
        }

   */
     return 0;
}

