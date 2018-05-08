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
#include "Switch.h"
#include "AiController.h"
#include "Floor.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

using std::cout;
using std::endl;
using std::stringstream;
using std::ifstream;
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
    static const sf::Vector2f SWORD{38, 45};
    static const sf::Vector2f ARMOUR{14, 38};

    sf::Vector2f charToSpriteId(char c) {
        switch (c) {
            case '.': return FLOOR;
            case '#': return WALL;
            case '?': return SWITCH_UNUSED;
            case '!': return SWITCH_USED;
            case 'X': return DOOR_CLOSED;
            case '/': return DOOR_OPEN;
            case '@': return PLAYER;
            case '%': return NEUTRAL;
            case 'G': return GOBLIN;
            case 'N': return NEUTRAL;
            case 'D': return DRAGON;
            case '*': return SWORD;
            case 'A': return ARMOUR;
        }
    }
};

int GameEngine::m_rounds = 0;


GameEngine::GameEngine(const std::string& mapFile) : m_tileSize{sf::Vector2f(32, 32)}
{

    loadFromFile(mapFile);
}

bool GameEngine::loadFromFile(const std::string& mapFile) {
    vector<string> mapVec;
    ifstream ifs;
    ifs.open(mapFile);
    string temp;
    while (ifs.good()) {
        std::getline(ifs, temp);
        mapVec.push_back(temp);
    }

    m_map = new DungeonMap(mapVec);

    for (int i = m_map->getHeight() + 1; i < mapVec.size(); ++i) {
        loadEntity(mapVec[i]);
    }

    m_mapTex.loadFromFile("./gfx/ProjectUtumno_full.png");
    m_mapSprite.setTexture(m_mapTex);
    m_window = new sf::RenderWindow(sf::VideoMode(m_map->getHeight() * m_tileSize.x, m_map->getWidth() * m_tileSize.y), "Game running!");

}

bool GameEngine::loadEntity(const std::string& data) {
    std::stringstream ss;
    std::string name, controller;
    Position pos;
    ss << data;
    ss >> name;

    if (name == "Character") {
        char sign;
        ss >> sign >> pos.y >> pos.x >> controller;
        if (Character * character = Character::makeCharacter(data)) {
            m_charVec.push_back(character);
            m_map->place(pos, character);
            if (controller == "ConsoleController")
                m_playerControl = dynamic_cast<ConsoleController*> (character->getController());
       }
    }
    else if (Tile::isSpecialTile(name)) {
        vector<std::pair<string, Position> > tiles;
        ss.str("");
        ss << data;
        while (ss.good()) {
            ss >> name >> pos.y >> pos.x;
            tiles.push_back(std::make_pair(name, pos));
        }
        for (int i = 0; i < tiles.size(); ++i) {
            m_map->replaceTile(tiles[i].first, tiles[i].second);
        }
        if (tiles.size() > 1) {
            for (int i = 1; i < tiles.size(); ++i)
                dynamic_cast<Active*> (m_map->find(tiles[0].second))->registerPassive(dynamic_cast<Passive*> (m_map->find(tiles[i].second)));
        }    
    } 
    
    else if (Item::isItem(name)) {
        ss >> pos.y >> pos.x;
        m_map->find(pos);
        dynamic_cast<Floor*> (m_map->find(pos))->setItem(Item::makeItem(name));
    }
}

GameEngine::GameEngine(const GameEngine& orig) {
}

GameEngine::~GameEngine() {
    delete m_map;
    for (int i = 0; i < m_charVec.size(); ++i) {
        delete m_charVec[i];
    }
    delete m_window;
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
    m_map->print();
    render();
    sf::Event event;
    while (m_window->isOpen()) {
        processEvents();
        render();
    }
}

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

void GameEngine::render() {
    sf::Vector2f tilePos;
    m_window->clear();
    for (int i = 0; i < m_map->getHeight(); ++i) {
        for (int j = 0; j < m_map->getWidth(); ++j) {

            tilePos = spriteIds::charToSpriteId(m_map->find({j, i})->tileToChar());
            renderTile(tilePos,{static_cast<float> (j), static_cast<float> (i)});
            m_window->draw(m_mapSprite);
        }
    }
    for (int i = 0; i < m_charVec.size(); ++i) {
        Position charPos = m_map->find(m_charVec[i]);
        tilePos = spriteIds::charToSpriteId(m_charVec[i]->getSign());
        renderChar(tilePos,{static_cast<float> (charPos.x), static_cast<float> (charPos.y)});
        m_window->draw(m_mapSprite);
    }
    m_window->display();
}

void GameEngine::renderTile(sf::Vector2f tilePos, sf::Vector2f mapPos) {

    if (tilePos != spriteIds::FLOOR) renderTile(spriteIds::FLOOR, mapPos);
    int posX, posY, width, height;
    posX = tilePos.x * m_tileSize.x;
    posY = tilePos.y * m_tileSize.y;
    width = m_tileSize.x;
    height = m_tileSize.y;
    m_mapSprite.setTextureRect({posX, posY, width, height});


    //m_mapSprite.setTextureRect({tilePos.x * m_tileSize.x, tilePos.y * m_tileSize.y, m_tileSize.x, m_tileSize.y});
    m_mapSprite.setPosition(mapPos.x * m_tileSize.x, mapPos.y * m_tileSize.y);
    m_window->draw(m_mapSprite);
}

void GameEngine::renderChar(sf::Vector2f tilePos, sf::Vector2f mapPos) {

    int posX, posY, width, height;
    posX = tilePos.x * m_tileSize.x;
    posY = tilePos.y * m_tileSize.y;
    width = m_tileSize.x;
    height = m_tileSize.y;
    m_mapSprite.setTextureRect({posX, posY, width, height});

    //m_mapSprite.setTextureRect({static_cast<int>(tilePos.x * m_tileSize.x), static_cast<int>(tilePos.y * m_tileSize.y), m_tileSize.x, m_tileSize.y});
    m_mapSprite.setPosition(mapPos.x * m_tileSize.x, mapPos.y * m_tileSize.y);
    m_window->draw(m_mapSprite);
}

void GameEngine::processEvents() {
    sf::Event event;
    while (m_window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code);
                turn();
                m_map->print();
                ++m_rounds;
                break;
            case sf::Event::Closed:
                m_window->close();
                break;
            case sf::Event::Resized:
                m_window->display();
                break;
        }
    }
}

void GameEngine::handlePlayerInput(sf::Keyboard::Key& key) {
    if (key == sf::Keyboard::Num1)
        m_playerControl->set_next_move(1);
    else if (key == sf::Keyboard::Num2)
        m_playerControl->set_next_move(2);
    else if (key == sf::Keyboard::Num3)
        m_playerControl->set_next_move(3);
    else if (key == sf::Keyboard::Num4)
        m_playerControl->set_next_move(4);
    else if (key == sf::Keyboard::Num5)
        m_playerControl->set_next_move(5);
    else if (key == sf::Keyboard::Num6)
        m_playerControl->set_next_move(6);
    else if (key == sf::Keyboard::Num7)
        m_playerControl->set_next_move(7);
    else if (key == sf::Keyboard::Num8)
        m_playerControl->set_next_move(8);
    else if (key == sf::Keyboard::Num9)
        m_playerControl->set_next_move(9);
    else if (key == sf::Keyboard::Escape)
        m_window->close();
}



