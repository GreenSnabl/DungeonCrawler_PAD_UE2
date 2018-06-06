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
#include "Passive.h"
#include <fstream>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>




class GameEngine {
public:

    GameEngine(const std::string& mapFile);
    ~GameEngine();

    bool run();
    std::string getNewMap() const;
    
private:
    void turn();
    void processEvents(Character* player);
    
    bool loadFromFile(const std::string& mapFile);
    bool loadEntity(const std::string& data);
    
    bool saveToFile(const std::string& mapFile);
    void saveEntities(const vector<Character*>& charVec, std::ofstream& ofs);
    
    void fight(Character*, Character*);
    bool m_playerWasAttacked;
    bool m_playerAttacked;
    

    
    void render();
    void renderTile(sf::Vector2f tilePos, sf::Vector2f mapPos);
    void renderChar(sf::Vector2f tilePos, sf::Vector2f mapPos);
    
    void setStatus(Character* player);
    void setFightStatus(bool, bool, int, int);
    void renderStatus(Character* player);
    
    void handlePlayerInput(sf::Keyboard::Key&, Character* player);
    
    
    void enterMenuState(bool gameEnd, Character* player);

    
    std::vector<Character*> m_charVec;
    DungeonMap* m_map;
    static int numberOfPlayers;
    static int currentPlayer;
    bool m_actionWasTaken;
    
    const sf::Vector2u m_tileSize;    
    sf::Texture m_mapTex;
    sf::Sprite m_mapSprite;
    sf::RenderWindow *m_window;
    
    
    sf::CircleShape m_redTriangle;
    sf::Text m_status;
    sf::Text m_defendText;
    sf::Text m_attackText;
    
    sf::Font m_font;
    
    sf::SoundBuffer bDeath;
    sf::Sound sDeath;
    
    vector<Character*> m_players;
    
    bool newMap;
    std::string newMapName;

    GameEngine(const GameEngine& orig);
};

Position intToPos(int);
int posToInt(Position);
bool isAllowedChar(int);

#endif /* GAMEENGINE_H */

