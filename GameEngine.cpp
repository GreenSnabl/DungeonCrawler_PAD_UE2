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

namespace spriteIds {

    static const sf::Vector2f FLOOR{10, 3};
    static const sf::Vector2f WALL{0, 18};
    static const sf::Vector2f SWITCH_UNUSED{0, 1};
    static const sf::Vector2f SWITCH_USED{2, 1};
    static const sf::Vector2f DOOR_CLOSED{11, 11};
    static const sf::Vector2f DOOR_OPEN{13, 11};
    static const sf::Vector2f PLAYER{0, 60};
    static const sf::Vector2f GOBLIN{28, 61};
    static const sf::Vector2f NEUTRAL{1, 59};
    static const sf::Vector2f DRAGON{3, 60};

    sf::Vector2f charToSpriteId(char c) {
        switch (c) {
            case '.': return FLOOR;
            case '#': return WALL;
            case '?': return SWITCH_UNUSED;
            case '!': return SWITCH_USED;
            case 'X': return DOOR_CLOSED;
            case '/': return DOOR_OPEN;
            case '@': return PLAYER;
            case 'G': return GOBLIN;
            case 'N': return NEUTRAL;
            case 'D': return DRAGON;
        }
    }
};


GameEngine::GameEngine(int height, int width, const std::string& data) : m_map{new DungeonMap(height, width, data)}
{
    m_charVec.push_back(new Player);
    m_map->place({5, 11}, m_charVec[0]);

}

GameEngine::GameEngine(const std::string& mapFile, const std::string& connectorFile) : m_tileSize{sf::Vector2f(32, 32)}
{
    vector<string> vecMap;
    if (!loadMap(mapFile, vecMap)) throw;

    m_map = new DungeonMap(vecMap.size(), vecMap[0].size(), vecMap);

    loadEntities(vecMap);

    vector<Position> vecPos;
    if (!loadConnectors(connectorFile, vecPos)) throw;
    for (int i = 0; i < vecPos.size() - 1; i = i + 2) {
        dynamic_cast<Active*> (m_map->find(vecPos[i]))->registerPassive(dynamic_cast<Passive*> (m_map->find(vecPos[i + 1])));
    }

    m_mapTex.loadFromFile("./gfx/ProjectUtumno_full.png");
    m_mapSprite.setTexture(m_mapTex);
}

bool GameEngine::loadMap(const string& mapFile, vector<string>& vecMap) {
    string str = "";
    std::ifstream ifs;

    ifs.open(mapFile);
    while (getline(ifs, str)) {
        vecMap.push_back(str);
    }
    ifs.close();

    return vecMap.size() > 0 && vecMap[0].size() > 0 && (vecMap[0].size() == vecMap[vecMap.size() - 1].size());
}

bool GameEngine::loadConnectors(const std::string& connectorFile, std::vector<Position>& vecPos) {
    Position tempPos;
    std::stringstream ss;
    string tempStr;
    std::ifstream ifs;
    ifs.open(connectorFile);

    while (getline(ifs, tempStr)) {
        ss.str(tempStr);
        while (ss >> tempPos.y >> tempPos.x) {
            vecPos.push_back(tempPos);
        }
        ss.clear();
    }

    ifs.close();
    return vecPos.size() % 2 == 0;
}

void GameEngine::loadEntities(const vector<string>& vecMap) {
    Character* temp = nullptr;
    for (int i = 0; i < vecMap.size(); ++i) {
        for (int j = 0; j < vecMap[i].size(); ++j) {
            if (temp = Character::makeCharacter(vecMap[i][j])) {
                m_charVec.push_back(temp);
                m_map->place({j, i}, m_charVec[m_charVec.size() - 1]);
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

bool GameEngine::turn() {
    for (int i = 0; i < m_charVec.size(); ++i) {
        Position charPos = m_map->find(m_charVec[i]);
        Position movement = intToPos(m_charVec[i]->move());
        m_map->find(charPos)->onLeave(m_map->find({charPos.x + movement.x, charPos.y + movement.y}));

    }
    m_map->print();
}

bool GameEngine::finished() const {
    return m_rounds > 20;
}

void GameEngine::run() {
    sf::RenderWindow window(sf::VideoMode(m_map->getHeight() * m_tileSize.x, m_map->getWidth() * m_tileSize.y), "Game running!");


    m_map->print();
    render(window);
    window.display();
    sf::Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || finished()) {
                window.close();
            }
            window.clear();
            turn();
            render(window);
            window.display();
            ++m_rounds;
        }
    }
}

int GameEngine::m_rounds = 0;

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





void GameEngine::render(sf::RenderWindow& window) {
    sf::Vector2f tilePos;
    for (int i = 0; i < m_map->getHeight(); ++i) {
        for (int j = 0; j < m_map->getWidth(); ++j) {

            tilePos = spriteIds::charToSpriteId(m_map->find({j, i})->getSign());
            renderTile(window, tilePos,{static_cast<float>(j), static_cast<float>(i)});
            window.draw(m_mapSprite);
        }
    }
    for (int i = 0; i < m_charVec.size(); ++i) {
        Position charPos = m_map->find(m_charVec[i]);
        tilePos = spriteIds::charToSpriteId(m_charVec[i]->getSign());
        renderChar(window, tilePos,{static_cast<float>(charPos.x), static_cast<float>(charPos.y)});
        window.draw(m_mapSprite);
    }

}

void GameEngine::renderTile(sf::RenderWindow& window, sf::Vector2f tilePos, sf::Vector2f mapPos) {

    if (tilePos != spriteIds::FLOOR) renderTile(window, spriteIds::FLOOR, mapPos);
    int posX, posY, width, height;
    posX = tilePos.x * m_tileSize.x;
    posY = tilePos.y * m_tileSize.y;
    width = m_tileSize.x;
    height = m_tileSize.y;
    m_mapSprite.setTextureRect({posX, posY, width, height});
    
    
    //m_mapSprite.setTextureRect({tilePos.x * m_tileSize.x, tilePos.y * m_tileSize.y, m_tileSize.x, m_tileSize.y});
    m_mapSprite.setPosition(mapPos.x * m_tileSize.x, mapPos.y * m_tileSize.y);
    window.draw(m_mapSprite);
}

void GameEngine::renderChar(sf::RenderWindow& window, sf::Vector2f tilePos, sf::Vector2f mapPos)
{
    
    int posX, posY, width, height;
    posX = tilePos.x * m_tileSize.x;
    posY = tilePos.y * m_tileSize.y;
    width = m_tileSize.x;
    height = m_tileSize.y;
    m_mapSprite.setTextureRect({posX, posY, width, height});
    
    //m_mapSprite.setTextureRect({static_cast<int>(tilePos.x * m_tileSize.x), static_cast<int>(tilePos.y * m_tileSize.y), m_tileSize.x, m_tileSize.y});
    m_mapSprite.setPosition(mapPos.x * m_tileSize.x, mapPos.y * m_tileSize.y);
    window.draw(m_mapSprite);
}