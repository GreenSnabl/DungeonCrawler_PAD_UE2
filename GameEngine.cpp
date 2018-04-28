/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GameEngine.cpp
 * Author: den
 * 
 * Created on April 19, 2018, 9:08 PM
 */

#include "GameEngine.h"
#include "Player.h"
#include "Switch.h"
#include "AiController.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;


GameEngine::GameEngine(int height, int width, const std::string& data) : m_map{new DungeonMap(height, width, data)} 
{
    m_charVec.push_back(new Player);
    m_map->place({5,11}, m_charVec[0]);

}

    GameEngine::GameEngine(const std::string& mapFile, const std::string& connectorFile)
    {
        vector<string> vecMap;
        if(!loadMap(mapFile, vecMap)) throw;
        
        m_map = new DungeonMap(vecMap.size(), vecMap[0].size(), vecMap);
        
        loadEntities(vecMap);
        
        vector<Position> vecPos;        
        if (!loadConnectors(connectorFile, vecPos)) throw;
        for (int i = 0; i < vecPos.size() - 1; i = i + 2) {
            dynamic_cast<Active*>(m_map->find(vecPos[i]))->registerPassive(dynamic_cast<Passive*>(m_map->find(vecPos[i+1])));
        }
        
    }
    
    bool GameEngine::loadMap(const string& mapFile, vector<string>& vecMap)
    {
        string str = "";
        std::ifstream ifs;
        
        ifs.open(mapFile);
        while (getline(ifs, str)) {
            vecMap.push_back(str);
        }
        ifs.close();
        
        return vecMap.size() > 0 && vecMap[0].size() > 0 && (vecMap[0].size() == vecMap[vecMap.size() - 1].size());
    }
    
    bool GameEngine::loadConnectors(const std::string& connectorFile, std::vector<Position>& vecPos)
    {
        Position tempPos;
        std::stringstream ss;
        string tempStr;
        std::ifstream ifs;
        ifs.open(connectorFile);
         
        while (getline(ifs, tempStr)) {
            ss.str(tempStr);
            while(ss >> tempPos.y >> tempPos.x){
                vecPos.push_back(tempPos);   
            }
            ss.clear();
        }
        
        ifs.close();
        return vecPos.size() % 2 == 0;
    }

    void GameEngine::loadEntities(const vector<string>& vecMap)
    {
        Character* temp = nullptr;
        for (int i = 0; i < vecMap.size(); ++i) {
            for (int j = 0; j < vecMap[i].size(); ++j) {
                if (temp = Character::makeCharacter(vecMap[i][j]))
                {
                    m_charVec.push_back(temp);
                    m_map->place({j,i}, m_charVec[m_charVec.size()-1]);
                    temp = nullptr;
                }
            }
        }
    }

GameEngine::GameEngine(const GameEngine& orig) {
}

GameEngine::~GameEngine() {
    delete m_map;
    for (int i = 0; i < m_charVec.size(); ++i) {
        delete m_charVec[i];
    }
}

bool GameEngine::turn()
{
    for (int i = 0; i < m_charVec.size(); ++i) {
        Position charPos = m_map->find(m_charVec[i]);
        Position movement = intToPos(m_charVec[i]->move());
        m_map->find(charPos)->onLeave(m_map->find({charPos.x + movement.x, charPos.y + movement.y}));
        m_map->print();
    }
}

bool GameEngine::finished()
{
    return rounds > 20;
}

void GameEngine::run()
{
    m_map->print();
    while (!finished())
    {
        turn();
        ++rounds;
    }
}

int GameEngine::rounds = 0;

Position intToPos(int dir)
{
    switch (dir) {
        case 1 : return {-1, 1};
        case 2 : return { 0, 1};
        case 3 : return { 1, 1};
        case 4 : return {-1, 0};
        case 5 : return { 0, 0};
        case 6 : return { 1, 0};
        case 7 : return {-1, -1};
        case 8 : return { 0, -1};
        case 9 : return { 1, -1};
    }
}