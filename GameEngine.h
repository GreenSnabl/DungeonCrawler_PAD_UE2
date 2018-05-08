/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GameEngine.h
 * Author: den
 *
 * Created on April 19, 2018, 9:08 PM
 */

#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "Character.h"
#include "DungeonMap.h"
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "ConsoleController.h"




class GameEngine {
public:

    GameEngine(const std::string& mapFile);
    ~GameEngine();

    void run();
    
private:
    bool finished() const;
    bool turn();
    void processEvents();
    
    void render();
    void renderTile(sf::Vector2f tilePos, sf::Vector2f mapPos);
    void renderChar(sf::Vector2f tilePos, sf::Vector2f mapPos);
    void renderStatus();
    void handlePlayerInput(sf::Keyboard::Key&);
    
    bool loadFromFile(const std::string& mapFile);
    bool loadEntity(const std::string& data);
    
    std::vector<Character*> m_charVec;
    DungeonMap* m_map;

    static int m_rounds;
    
    const sf::Vector2u m_tileSize;    
    sf::Texture m_mapTex;
    sf::Sprite m_mapSprite;
    sf::RenderWindow *m_window;
    sf::Text m_status;
    sf::Font m_font;
    
    Character* m_player;
    ConsoleController* m_playerControl;

    GameEngine(const GameEngine& orig);
};

Position intToPos(int);

#endif /* GAMEENGINE_H */

