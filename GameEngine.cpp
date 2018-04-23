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

GameEngine::GameEngine(int height, int width, const std::string& data) : m_map{new DungeonMap(height, width, data)}
{
    m_charVec.push_back(new Character('@'));
    m_map->place({5, 5}, m_charVec[0]);
}

GameEngine::GameEngine(const GameEngine& orig) {
}

GameEngine::~GameEngine() {
    delete m_map;
    delete m_charVec[0];
}

bool GameEngine::turn() {
    Position charPos = m_map->find(m_charVec[0]);
    Position movement = intToPos(m_charVec[0]->move());
    m_map->find(charPos)->onLeave(m_map->find({charPos.x + movement.x, charPos.y + movement.y}));
    m_map->print();
}

bool GameEngine::finished() {
    return rounds > 10;
}

void GameEngine::run() {
    m_map->print();
    while (!finished()) {
        turn();
        ++rounds;
    }
}

int GameEngine::rounds = 0;

Position intToPos(int dir) {
    switch (dir) {
        case 1: return {-1, 1};
        case 2: return { 0, 1};
        case 3: return { 1, 1};
        case 4: return {-1, 0};
        case 5: return { 0, 0};
        case 6: return { 1, 0};
        case 7: return {-1, -1};
        case 8: return { 0, -1};
        case 9: return { 1, -1};
    }
}