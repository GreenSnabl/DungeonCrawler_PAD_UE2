/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <SFML/System/Vector2.hpp>


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
    static const sf::Vector2f LEVER{1, 1};
    static const sf::Vector2f LEVER_USED{6, 1};
    static const sf::Vector2f TRAP_USED{8, 13};

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
            case 'L': return LEVER;
            case 'l': return LEVER_USED;
            case 't': return TRAP_USED;
        }
    }
};


GameEngine::GameEngine(const std::string& mapFile) : m_tileSize{sf::Vector2f(32, 32)}
{

    loadFromFile(mapFile);

    m_font.loadFromFile("./font/UbuntuMono-B.ttf");
    m_status.setFont(m_font);
    m_status.setColor(sf::Color(255, 255, 255));
    m_status.setCharacterSize(30);

    m_mapTex.loadFromFile("./gfx/ProjectUtumno_full.png");
    m_mapSprite.setTexture(m_mapTex);


    //m_window = new sf::RenderWindow(sf::VideoMode(1024, 640), "Game running!");    
    m_window = new sf::RenderWindow(sf::VideoMode(m_map->getHeight() * m_tileSize.x + 300.f, m_map->getWidth() * m_tileSize.y), "Game running!");
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
}

bool GameEngine::loadEntity(const std::string& data) {
    std::stringstream ss;
    std::string name, controller;
    Position pos;
    ss << data;
    ss >> name;

    if (name == "Character") {
        char sign;
        ss >> sign >> pos >> controller;
        if (Character * character = Character::makeCharacter(data)) {
            m_charVec.push_back(character);
            m_map->place(pos, character);
            if (controller == "ConsoleController") {
                m_playerControl = dynamic_cast<ConsoleController*> (character->getController());
                m_player = character;
            }
        }
    } else if (Tile::isSpecialTile(name)) {
        vector<std::pair<string, Position> > tiles;
        ss.str("");
        ss << data;
        while (ss.good()) {
            ss >> name >> pos;
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
        ss >> pos;
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

void GameEngine::turn() {
    
    for (int i = 0; i < m_charVec.size(); ++i)
    {
        if (m_charVec[i]->getCurrentHP() <= 0)
        {
            if (ConsoleController* c = dynamic_cast<ConsoleController*>(m_charVec[i]->getController())) 
            {
                enterMenuState(true);
                return;
            }
            else {
            delete m_charVec[i];
            m_charVec.erase(m_charVec.begin() + i);
            }
        }
    }
     

    for (int i = 0; i < m_charVec.size(); ++i) {
        Position charPos = m_map->find(m_charVec[i]);
        Position movement = intToPos(m_charVec[i]->move());

        // Hier kommt die Kampfphase hin

        m_map->find(charPos)->onLeave(m_map->find({charPos.x + movement.x, charPos.y + movement.y}));
    }
    m_map->print(m_map->find(m_player));
}


void GameEngine::run() {
    m_map->print(m_map->find(m_player));
    render();
    sf::Event event;
    while (m_window->isOpen()) {
        processEvents();
        update();
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
            if (m_map->checkLine(m_map->find(m_player), {j,i})) {
            tilePos = spriteIds::charToSpriteId(m_map->find({j, i})->tileToChar());
            renderTile(tilePos,{static_cast<float> (j), static_cast<float> (i)});
            m_window->draw(m_mapSprite);
            }
            else {
            renderTile(spriteIds::WALL,{static_cast<float> (j), static_cast<float> (i)});
            m_window->draw(m_mapSprite);
            }            }
        }
    
    for (int i = 0; i < m_charVec.size(); ++i) {
        Position charPos = m_map->find(m_charVec[i]);
        if (m_map->checkLine(m_map->find(m_player), charPos)) {
        tilePos = spriteIds::charToSpriteId(m_charVec[i]->getSign());
        renderChar(tilePos,{static_cast<float> (charPos.x), static_cast<float> (charPos.y)});
        m_window->draw(m_mapSprite);
        }
    }
    renderStatus();

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

void GameEngine::setStatus() {
    stringstream ss;
    ss << "Player Stats\n"
            << "Stamina: " << m_player->getStamina()
            << "\nStrength: " << m_player->getStrength()
            << "\nMax HP: " << m_player->getMaxHP()
            << "\nCurrent HP: " << m_player->getCurrentHP();

    m_status.setString(ss.str());
}

void GameEngine::renderStatus() {
    setStatus();
    m_status.setPosition(m_map->getWidth() * 32 + 20, m_map->getHeight() * 32 / 4);
    m_window->draw(m_status);
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
    else if (key == sf::Keyboard::Num0)
        enterMenuState(false);
}

void GameEngine::update() {
    //if (m_player->getCurrentHP() <= 0)
    //    m_window->close();
}



void GameEngine::enterMenuState(bool gameEnd) {
    setStatus();

    sf::Text showInfo;
    sf::Text back;
    sf::Text end;
    sf::Text dead;

    if (gameEnd) {
    dead.setFont(m_font);
    dead.setCharacterSize(30);
    dead.setString("Ups, du bist tot");
    dead.setPosition(300, 50);
    }
    end.setFont(m_font);
    end.setCharacterSize(30);
    end.setString("0. Spiel beenden");
    end.setPosition(40, 100);

    back.setFont(m_font);
    back.setCharacterSize(30);
    back.setString("1. Zurueck zum Spiel");
    back.setPosition(40, 150);

    showInfo.setFont(m_font);
    showInfo.setCharacterSize(30);
    showInfo.setPosition(40, 200);
    showInfo.setString("2. Spielerinformationen anzeigen");

    m_status.setPosition(40, 250);
    
    sf::Event event;
    
    bool showStatus = false;

    while (m_window->isOpen()) {
        while (m_window->pollEvent(event)) {
            m_window->clear();
            m_window->draw(end);
            m_window->draw(back);
            m_window->draw(showInfo);
            if (showStatus) m_window->draw(m_status);
            if (gameEnd) m_window->draw(dead);
            m_window->display();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Num0 || event.key.code == sf::Keyboard::Escape) {
                    m_window->close();
                } 
                else if (event.key.code == sf::Keyboard::Num1)
                {
                    m_window->clear();
                    return;                
                }
                else if (event.key.code == sf::Keyboard::Num2)
                {
                    showStatus = !showStatus;
                }
                
            }
            else if (event.type == sf::Event::Closed)
            {
                m_window->close();
            }
        }
    }
}