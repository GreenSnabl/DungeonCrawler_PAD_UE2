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
#include "NPC.h"
#include "Switch.h"
#include "AiController.h"


GameEngine::GameEngine(int height, int width, const std::string& data) : m_map{new DungeonMap(height, width, data)} 
{
    m_charVec.push_back(new Player);
    m_charVec.push_back(new NPC('G', AiController::PATROL));
    m_charVec.push_back(new NPC('O', AiController::STROLLING));
    m_charVec.push_back(new NPC('z', AiController::HOLD));
    
    dynamic_cast<Active*>(m_map->find({5,7}))->registerPassive(dynamic_cast<Passive*>(m_map->find({7,4})));
    
    m_map->place({5,11}, m_charVec[0]);
    m_map->place({5,5}, m_charVec[1]);
    m_map->place({7,3}, m_charVec[2]);
    m_map->place({10,9}, m_charVec[3]);
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