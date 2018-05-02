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


class GameEngine {
public:
    
    GameEngine(int height, int width, const std::string& data);
    GameEngine(int height, int width, const std::vector<string>& data);
    GameEngine(const std::string& mapFile, const std::string& connectorFile);
    ~GameEngine();
    
    void run();
    
    DungeonMap* getMap() const {return m_map;}
    
private:
    bool finished();
    bool turn(sf::RenderWindow& window);

    bool loadMap(const std::string& mapFile, std::vector<std::string>& VecMap);    
    bool loadConnectors(const std::string& connectorFile, std::vector<Position>& vecPos);
    
    void loadEntities(const std::vector<std::string>& vecMap);
    std::vector<Character*> m_charVec;
    
    DungeonMap* m_map;
    static int rounds;
    
    GameEngine(const GameEngine& orig);
    
};

Position intToPos(int);

#endif /* GAMEENGINE_H */

