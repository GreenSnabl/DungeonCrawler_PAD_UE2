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

    GameEngine(int height, int width, const std::string& data);
    
    GameEngine(int height, int width, const std::vector<string>& data);
    GameEngine(const std::string& mapFile, const std::string& connectorFile);
    GameEngine(const std::string& mapFile);
    
    ~GameEngine();

    void run();

    
    bool isItem(const std::string& str);




private:
    bool finished() const;
    bool turn();
    void processEvents();
    void render();
    void renderTile(sf::Vector2f tilePos, sf::Vector2f mapPos);
    void renderChar(sf::Vector2f tilePos, sf::Vector2f mapPos);
    void handlePlayerInput(sf::Keyboard::Key&);
    
    bool loadEntity(const std::string& data);
    bool loadFromFile(const std::string& mapFile);

    
    std::vector<Character*> m_charVec;
    DungeonMap* m_map;

    static int m_rounds;
    
    
    
    
        
    //bool loadFromFile(const std::string& mapFile);
    bool loadMap(const std::string& mapFile, std::vector<std::string>& VecMap);
    bool loadConnectors(const std::string& connectorFile, std::vector<Position>& vecPos);
    void loadEntities(const std::vector<std::string>& vecMap);
    

    
    const sf::Vector2u m_tileSize;    
    sf::Texture m_mapTex;
    sf::Sprite m_mapSprite;
    sf::RenderWindow *m_window;
    ConsoleController* m_playerControl;

    const static std::vector<std::string> items;

    
    
    GameEngine(const GameEngine& orig);
};

Position intToPos(int);

#endif /* GAMEENGINE_H */

