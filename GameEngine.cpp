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
#include "Portal.h"
#include "Lever.h"
#include "Door.h"
#include "Trap.h"
#include "Wall.h"
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
using std::ofstream;
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
    static const sf::Vector2f PORTAL{40, 10};

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
            case 'O': return PORTAL;
        }
    }
};

GameEngine::GameEngine(const GameEngine& orig) {
    
}

GameEngine::~GameEngine() {
    delete m_map;
    for (int i = 0; i < m_charVec.size(); ++i) {
        delete m_charVec[i];
    }
    delete m_window;
}


GameEngine::GameEngine(const std::string& mapFile) : m_tileSize{sf::Vector2f(32, 32)}, m_playerAttacked{false}, m_playerWasAttacked{false}, m_map{nullptr}, newMap{false}, m_redTriangle{sf::CircleShape(10, 3)}, m_actionWasTaken{false}
{

    loadFromFile(mapFile);
    
    m_font.loadFromFile("./font/UbuntuMono-B.ttf");
    m_status.setFont(m_font);
    m_status.setColor(sf::Color(255, 255, 255));
    m_status.setCharacterSize(30);

    m_defendText.setFont(m_font);
    m_defendText.setColor(sf::Color(255,255,255));
    m_defendText.setCharacterSize(15);
    
    m_attackText.setFont(m_font);
    m_attackText.setColor(sf::Color(255,255,255));
    m_attackText.setCharacterSize(15);
    
    m_redTriangle.setFillColor(sf::Color::Red);
    m_redTriangle.rotate(180.f);
    
    
    m_mapTex.loadFromFile("./gfx/ProjectUtumno_full.png");
    m_mapSprite.setTexture(m_mapTex);
    
    bDeath.loadFromFile("./sound/death.ogg");
    sDeath.setBuffer(bDeath);
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
   



    //m_window = new sf::RenderWindow(sf::VideoMode(1024, 640), "Game running!");    
    m_window = new sf::RenderWindow(sf::VideoMode(m_map->getHeight() * m_tileSize.x + 300.f, m_map->getWidth() * m_tileSize.y), "Game running!");
}

bool GameEngine::saveToFile(const std::string& mapFile)
{
    ofstream ofs;
    stringstream ss;
    ss << "./savefiles/" << mapFile << ".txt";
    ofs.open(ss.str());
    ss.str("");
    ss << m_map->getHeight() << " " << m_map->getWidth() << "\n";
    for (int i = 0; i < m_map->getHeight(); ++i) {
        for (int j = 0; j < m_map->getWidth(); ++j) {
            if (dynamic_cast<Wall*>(m_map->find({j, i}))) ss << "#";
            else {ss << ".";}
        }
        ss << "\n";
        ofs << ss.str();
        ss.str("");
    }
    ss.str("");
    for (int i = 0; i < m_map->getHeight(); ++i) {
        for (int j = 0; j < m_map->getWidth(); ++j) {
            if (Switch* tswitch = dynamic_cast<Switch*>(m_map->find({j,i})))
            {
                if (tswitch->getWasUsed())
                {
                    ss << "SwitchUsed";
                } else {
                ss << "Switch";
                }                
                ss << " " << Position({j,i}) << " ";
                for (int i = 0; i < tswitch->getPassiveSize(); ++i)
                {
                    ss << passiveToString(tswitch->getPassive(i)) << " " << m_map->find(tswitch->getPassive(i)) << " ";
                }
                ss << "\n";
                ofs << ss.str();
                ss.str("");           
            }
            else if (Lever* tlever = dynamic_cast<Lever*>(m_map->find({j,i})))
            {
                ss << "Lever " << Position({j,i}) << " ";
                for (int i = 0; i < tlever->getPassiveSize(); ++i)
                {
                    ss << passiveToString(tlever->getPassive(i)) << " " << m_map->find(tlever->getPassive(i)) << " ";
                }
                ss << "\n";
                ofs << ss.str();
                ss.str("");           
            }
            else if (Trap* trap = dynamic_cast<Trap*>(m_map->find({j,i}))) 
            {
                if (trap->getWasUsed()) { ss << "TrapUsed"; }
                else { ss << "Trap";}
                ss << " " << Position({j,i}) << "\n";
                ofs << ss.str();
                ss.str("");
            }
            
            else if (Portal* portal = dynamic_cast<Portal*>(m_map->find({j,i})))
            {
                Position src = m_map->find(portal);
                Position dest = m_map->find(portal->getDestination());
                if (dest < src) continue;
                ss << "Portal " << src << " Portal " << m_map->find(portal->getDestination()) << "\n";
                ofs << ss.str();
                ss.str("");
            }
            
            else if (Floor* tmpFloor = dynamic_cast<Floor*>(m_map->find(Position({j,i}))))
            {
                if (tmpFloor->hasItem()) {
                Item* tmp = tmpFloor->getItem();
                Position pos({j,i});
                ss << Item::itemToString(tmp) << " " << pos << "\n";
                ofs << ss.str();
                ss.str("");
                }
            }
        }
    }
    

    saveEntities(m_charVec, ofs);
    saveEntities(m_players, ofs);
}

void GameEngine::saveEntities(const vector<Character*>& charVec, ofstream& ofs)
{
    stringstream ss;
    for (int i = 0; i < charVec.size(); ++i)
    {
        ss << "Character " << charVec[i]->getSign() << " " << m_map->find(charVec[i]) << " ";
        if (dynamic_cast<ConsoleController*>(charVec[i]->getController())) 
        {
            ss << "ConsoleController ";
        }
        else if (AiController* temp = dynamic_cast<AiController*>(charVec[i]->getController()))
        {
            if (temp->getBehaviour() == AiController::Behaviour::HOLD)
                ss << "StationaryController ";
            else {
                ss << "AiController ";
            }
        }
        ss << charVec[i]->getStrength() << " " << charVec[i]->getStamina() << " " << charVec[i]->getCurrentHP();

        for (int j = 0; j < charVec[i]->getItemSize(); ++j)
        {
            if (Item* tmp = dynamic_cast<Item*>(charVec[i]->getItem(j)))
            {
                ss << " " << Item::itemToString(tmp);
            }
        }
  
        ss << "\n";
        ofs << ss.str();
        ss.str("");
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
        vector<string> items;
        string tempItem;
        int stamina, strength, currentHP;
        ss >> stamina >> strength >> currentHP;
        if (currentHP == 0) 
        {
            ss.clear();
            ss.str("");
            ss << data;
            ss >> name >> sign >> pos >> controller >> stamina >> strength;
        }
        
        while (ss.good())
        {
            ss >> tempItem;
            items.push_back(tempItem);
        }
        if (Character * character = Character::makeCharacter(data)) {
            m_map->place(pos, character);
            for (int i = 0; i < items.size(); ++i)
                {
                 character->addItem(Item::makeItem(items[i]));   
                }
            if (currentHP != 0) character->setCurrentHP(currentHP);
            if (controller == "ConsoleController") {
                ConsoleController* controller = dynamic_cast<ConsoleController*> (character->getController());
                controller->setPlayerNr(++numberOfPlayers);
                m_players.push_back(character);
            }
            else {
                m_charVec.push_back(character);
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
        if (tiles.size() > 1 && tiles[0].first != "Portal") {
            for (int i = 1; i < tiles.size(); ++i)
                dynamic_cast<Active*> (m_map->find(tiles[0].second))->registerPassive(dynamic_cast<Passive*> (m_map->find(tiles[i].second)));
        }
        if (tiles.size() > 1 && tiles[0].first == "Portal")
        {
            dynamic_cast<Portal*>(m_map->find(tiles[0].second))->setDestination(dynamic_cast<Portal*>(m_map->find(tiles[1].second)));
            dynamic_cast<Portal*>(m_map->find(tiles[1].second))->setDestination(dynamic_cast<Portal*>(m_map->find(tiles[0].second)));
        }
    }

    else if (Item::isItem(name)) {
        ss >> pos;
        m_map->find(pos);
        dynamic_cast<Floor*> (m_map->find(pos))->setItem(Item::makeItem(name));
    }
}



bool GameEngine::run() {
    m_map->print(m_map->find(m_players[0]));
    render();
    sf::Event event;
    while (m_window->isOpen() && !newMap) {
        
        processEvents(m_players[currentPlayer]);
        render();  
    }
    return newMap;
}


void GameEngine::turn() {
    
    m_playerAttacked = false;
    m_playerWasAttacked = false;
    
    for (int i = 0; i < m_charVec.size(); ++i)
    {
        if (m_charVec[i]->getCurrentHP() <= 0)
        {
            m_map->find(m_map->find(m_charVec[i]))->setCharacter(nullptr);    
            delete m_charVec[i];
            m_charVec.erase(m_charVec.begin() + i);      
        }
    }
    
    
    for (int i = 0; i < m_players.size(); ++i)
    {
        if (m_players[i]->getCurrentHP() <= 0)
        {
            --numberOfPlayers;
            if (numberOfPlayers < 1){
                enterMenuState(true, m_players[0]);
                return;
            }
            
            m_map->find(m_map->find(m_players[i]))->setCharacter(nullptr);    
            delete m_players[i];
            m_players.erase(m_players.begin() + i);      
        }
    }
    
    
        Position charPos = m_map->find(m_players[currentPlayer]);
        Position movement = intToPos(m_players[currentPlayer]->move());
        
        bool fightHappened = (
                m_map->find({charPos.x + movement.x, charPos.y + movement.y})->hasCharacter() &&
                m_map->find(Position({charPos.x + movement.x, charPos.y + movement.y}))->getCharacter() != m_players[currentPlayer]                         
                        );
                
        m_map->find(charPos)->onLeave(m_map->find({charPos.x + movement.x, charPos.y + movement.y}));
        if(fightHappened)
        {
            Character* attacker = m_map->find(charPos)->getCharacter();
            Character* defender = m_map->find({charPos.x + movement.x, charPos.y + movement.y})->getCharacter();
            // Hier kommt die Kampfphase hin
            fight(attacker, defender);
        }    
        currentPlayer++;
        if (currentPlayer >= m_players.size()) {
        for (int i = 0; i < m_charVec.size(); ++i) {
        Position charPos = m_map->find(m_charVec[i]);
        
        if (AiController* control = dynamic_cast<AiController*>(m_charVec[i]->getController())) {
            Character* temp = m_players[0];
            double minDistance = std::numeric_limits<double>::max();
            for (int j = 0; j < m_players.size(); ++j)
            {
                Position source = m_map->find(m_charVec[i]);
                Position destination = m_map->find(m_players[j]);
                if (m_map->checkLine(source, destination))
                {
                    double tmpDistance = getDistance(source, destination);
                    if (tmpDistance < minDistance) 
                    {
                        minDistance = tmpDistance;
                        temp = m_players[j];
                    }  
                }
            }
            control->updateBehaviour(m_map, charPos, m_map->find(temp));
        }
        
        Position movement = intToPos(m_charVec[i]->move());
        
        bool fightHappened = (
                m_map->find({charPos.x + movement.x, charPos.y + movement.y})->hasCharacter() &&
                m_map->find(Position({charPos.x + movement.x, charPos.y + movement.y}))->getCharacter() != m_charVec[i]
                        );
                
        m_map->find(charPos)->onLeave(m_map->find({charPos.x + movement.x, charPos.y + movement.y}));
        if(fightHappened)
        {
            Character* attacker = m_map->find(charPos)->getCharacter();
            Character* defender = m_map->find({charPos.x + movement.x, charPos.y + movement.y})->getCharacter();
            // Hier kommt die Kampfphase hin
            fight(attacker, defender);
        }
    }
        currentPlayer = 0;
        }
    m_map->print(m_map->find(m_players[0]));
}


std::string GameEngine::getNewMap() const
{
    return newMapName;
}

void GameEngine::fight(Character* attacker, Character* defender)
{
    bool playerIsAttacking = false;
    bool attackerDied = false;
    int attackerDamage = attacker->getStrength();
    int defenderDamage = -1;
    defender->takeDamage(attackerDamage);
    if (dynamic_cast<ConsoleController*>(attacker->getController()))
    {
        playerIsAttacking = true;
        m_playerAttacked = true;
    }
    else {
        m_playerWasAttacked = true;
    }
    if (defender->getCurrentHP() > 0) {
        defenderDamage = defender->getStrength();
        attacker->takeDamage(defenderDamage);
        if (attacker->getCurrentHP() == 0) 
        {
            attackerDied = true;
            sDeath.play();
        }
    } else 
    {
        sDeath.play();
    }
    setFightStatus(playerIsAttacking, attackerDied, attackerDamage, defenderDamage);
    
}

void GameEngine::setFightStatus(bool playerIsAttacking, bool attackerDied, int attackerDamage, int defenderDamage)
{
    std::stringstream ss;
    std::string attacker, defender;
    ss << "Spieler " << currentPlayer + 1;
    
    if (playerIsAttacking) 
    {
        attacker = ss.str(); defender = "Gegner";
    }
    else 
    { 
        attacker = "Gegner"; defender = "Spieler";
    }
    ss.str("");
    ss << attacker << " attackiert " << defender << "\n" << attackerDamage << " Schaden.\n";
    
    if (defenderDamage != -1)
    {
        ss << "\n" << defender << " verteidigt sich \n" << defenderDamage << " Schaden.";
        if (attackerDied) ss << "\n" << attacker << " stirbt.";
    }
    else {
        ss << "\n" << defender << " stirbt.";
    }
    
    if (playerIsAttacking) {m_attackText.setString(ss.str());}
    else {m_defendText.setString(ss.str());}
}

int GameEngine::numberOfPlayers = 0;
int GameEngine::currentPlayer = 0;


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

int posToInt(Position pos) {
    if (pos == Position({-1, 1})) return 1;
    else if (pos == Position({0, 1})) return 2;
    else if (pos == Position({1, 1})) return 3;
    else if (pos == Position({-1, 0})) return 4;
    else if (pos == Position({0, 0})) return 5;
    else if (pos == Position({1, 0})) return 6;
    else if (pos == Position({-1, -1})) return 7;
    else if (pos == Position({0, -1})) return 8;
    else if (pos == Position({1, -1})) return 9;
}

void GameEngine::render() {
    sf::Vector2f tilePos;
    m_window->clear();
    
    bool hasSight = false;
    
    for (int i = 0; i < m_map->getHeight(); ++i) {
        for (int j = 0; j < m_map->getWidth(); ++j) {
            hasSight = false;
            for (int k = 0; k < m_players.size(); ++k) {
            if (m_map->checkLine(m_map->find(m_players[k]), {j,i})) {
                tilePos = spriteIds::charToSpriteId(m_map->find({j, i})->tileToChar());
                renderTile(tilePos,{static_cast<float> (j), static_cast<float> (i)});
                m_window->draw(m_mapSprite);
                hasSight = true;
                break;
            }
            }
            if (hasSight) continue;
            
            renderTile(spriteIds::WALL,{static_cast<float> (j), static_cast<float> (i)});
            m_window->draw(m_mapSprite);
            
        }
    }
    
    for (int i = 0; i < m_charVec.size(); ++i) {
        Position charPos = m_map->find(m_charVec[i]);
        for (int j = 0; j < m_players.size(); ++j) {
        if (m_map->checkLine(m_map->find(m_players[j]), charPos)) {
        tilePos = spriteIds::charToSpriteId(m_charVec[i]->getSign());
        renderChar(tilePos,{static_cast<float> (charPos.x), static_cast<float> (charPos.y)});
        break;
        }
        m_window->draw(m_mapSprite);
        }
    }
    
    for (int i = 0; i < m_players.size(); ++i) {
        Position charPos = m_map->find(m_players[i]);
        tilePos = spriteIds::charToSpriteId(m_players[i]->getSign());
        renderChar(tilePos,{static_cast<float> (charPos.x), static_cast<float> (charPos.y)});
        m_window->draw(m_mapSprite);
        }
    
    Position currentPlayerPos = m_map->find(m_players[currentPlayer]);
    float player_x = static_cast<float>(currentPlayerPos.x) * static_cast<float>(m_tileSize.x)  + static_cast<float>(m_tileSize.x - 5);
    float player_y = static_cast<float>(currentPlayerPos.y * m_tileSize.y);
    
    m_redTriangle.setPosition(player_x, player_y);
    m_window->draw(m_redTriangle);
    
    
    
    renderStatus(m_players[currentPlayer]);
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

void GameEngine::setStatus(Character* player) {
    stringstream ss;
    ss << "Player Stats\n"
            << "Stamina: " << player->getStamina()
            << "\nStrength: " << player->getStrength()
            << "\nMax HP: " << player->getMaxHP()
            << "\nCurrent HP: " << player->getCurrentHP();

    m_status.setString(ss.str());
}

void GameEngine::renderStatus(Character* player) {
    setStatus(player);
    m_status.setPosition(m_map->getWidth() * 32 + 20, m_map->getHeight() * 32 / 6);
    m_window->draw(m_status);
    
    if (m_playerAttacked)
    {
        m_attackText.setPosition(m_map->getWidth() * 32 + 20, (m_map->getHeight() * 32 / 4) * 2);
        m_window->draw(m_attackText);
    }
    if (m_playerWasAttacked)
    {
        m_defendText.setPosition(m_map->getWidth() * 32 + 20, (m_map->getHeight() * 32 / 4) * 3);
        m_window->draw(m_defendText);
    
    }
    
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

void GameEngine::processEvents(Character* player) {
    sf::Event event;
    while (m_window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, player);
                if (m_actionWasTaken) turn();
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

void GameEngine::handlePlayerInput(sf::Keyboard::Key& key, Character* player) {
    ConsoleController* controller = dynamic_cast<ConsoleController*>(player->getController());
    m_actionWasTaken = false;
    if (key == sf::Keyboard::Num1) {
        controller->set_next_move(1);
        m_actionWasTaken = true;
    }
    else if (key == sf::Keyboard::Num2) {
        controller->set_next_move(2);
        m_actionWasTaken = true;
    }
    else if (key == sf::Keyboard::Num3) {
        controller->set_next_move(3);
        m_actionWasTaken = true;
    }
    else if (key == sf::Keyboard::Num4) {
        controller->set_next_move(4);
        m_actionWasTaken = true;
    }
    else if (key == sf::Keyboard::Num5) {
        controller->set_next_move(5);
        m_actionWasTaken = true;
    }
    else if (key == sf::Keyboard::Num6) {
        controller->set_next_move(6);
        m_actionWasTaken = true;
    }
    else if (key == sf::Keyboard::Num7) {
        controller->set_next_move(7);
        m_actionWasTaken = true;
    }
    else if (key == sf::Keyboard::Num8) {
        controller->set_next_move(8);
        m_actionWasTaken = true;
    }
    else if (key == sf::Keyboard::Num9) {
        controller->set_next_move(9);
        m_actionWasTaken = true;
    }
    else if (key == sf::Keyboard::Escape) {
        m_window->close();
    }
    else if (key == sf::Keyboard::Num0){
        enterMenuState(false, player);
    }
}


void GameEngine::enterMenuState(bool gameEnd, Character* player) {
    setStatus(player);

    sf::Text showInfo;
    sf::Text back;
    sf::Text end;
    sf::Text dead;
    sf::Text saveGame;
    sf::Text loadGame;
    sf::Text textInput;
    sf::Text saveOptions;
    sf::Text loadOptions;
    sf::Text items;


    
    if (gameEnd) {
    dead.setFont(m_font);
    dead.setCharacterSize(30);
    dead.setString("Ups, du bist tot");
    dead.setPosition(300, 10);
    }
    end.setFont(m_font);
    end.setCharacterSize(30);
    end.setString("0. Spiel beenden");
    end.setPosition(40, 50);

    back.setFont(m_font);
    back.setCharacterSize(30);
    back.setString("1. Zurueck zum Spiel");
    back.setPosition(40, 100);

    showInfo.setFont(m_font);
    showInfo.setCharacterSize(30);
    showInfo.setPosition(40, 150);
    showInfo.setString("2. Spielerinformationen anzeigen");

    items.setFont(m_font);
    items.setCharacterSize(20);
    items.setPosition(300, 300);
    
    saveGame.setFont(m_font);
    saveGame.setCharacterSize(30);
    saveGame.setPosition(40, 200);
    saveGame.setString("3. Spielstand speichern");
    
    loadGame.setFont(m_font);
    loadGame.setCharacterSize(30);
    loadGame.setPosition(40, 250);
    loadGame.setString("4. Spielstand laden");
    
    textInput.setFont(m_font);
    textInput.setCharacterSize(20);
    textInput.setPosition(40, 400);
    
    saveOptions.setFont(m_font);
    saveOptions.setCharacterSize(20);
    saveOptions.setPosition(40, 370);
    saveOptions.setString("Abbrechen (ESC), Speichern (Enter)");
    
    loadOptions.setFont(m_font);
    loadOptions.setCharacterSize(20);
    loadOptions.setPosition(40, 370);
    loadOptions.setString("Abbrechen (ESC), Laden (Enter)");
    
    
    m_status.setPosition(40, 300);
    
    
    bool showStatus = false;
    bool textInputMode = false;
    bool changedToInputMode = false;
    bool load = false;
    bool save = false;
    std::string str;
    sf::Event event;


    while (m_window->isOpen()) {
        while (m_window->pollEvent(event)) {
            m_window->clear();
            m_window->draw(end);
            m_window->draw(back);
            m_window->draw(showInfo);
            m_window->draw(saveGame);
            m_window->draw(loadGame);
            m_window->draw(textInput);
            if (textInputMode && save) m_window->draw(saveOptions);
            if (textInputMode && load) m_window->draw(loadOptions);
            if (showStatus) {
                m_window->draw(m_status);
                m_window->draw(items);
            }
            if (gameEnd) m_window->draw(dead);
            m_window->display();
            if (event.type == sf::Event::TextEntered && textInputMode)
            {
                if(event.text.unicode == '\b' && str.size() > 0)
                {
                    str.erase(str.size()-1, 1);
                }
                else if (event.text.unicode == 27)
                {
                    str = "";
                    textInputMode = false;
                }
                else if (event.text.unicode == 13)
                {
                    if (load) {
                        stringstream ss;
                        ss << "./savefiles/" << str << ".txt";
                        newMap = true;
                        newMapName = ss.str();
                        return;
                    }
                    if (save) {
                        saveToFile(str);
                    }
                    str = "";
                    textInputMode = false;
                    load = save = false;
                
                }
                else if (changedToInputMode)
                {
                    changedToInputMode = false;
                }
                else if (isAllowedChar(event.text.unicode))
                {
                    str += event.text.unicode;
                }
                textInput.setString(str);
            }
            
            if (event.type == sf::Event::KeyPressed && !textInputMode) {
                if (event.key.code == sf::Keyboard::Num0 || event.key.code == sf::Keyboard::Escape) {
                    m_window->close();
                } 
                else if (event.key.code == sf::Keyboard::Num1 && !textInputMode)
                {
                    m_window->clear();
                    return;                
                }
                else if (event.key.code == sf::Keyboard::Num2 && !textInputMode)
                {
                    showStatus = !showStatus;
                    stringstream ss;
                    ss << "Playeritems:\n";
                    for (int i = 0; i < player->getItemSize(); ++i)
                    {
                        ss << Item::itemToString(player->getItem(i)) << " ";
                        if ((i + 1) % 3 == 0)
                            ss << "\n";
                    }
                    items.setString(ss.str());
                }
                else if (event.key.code == sf::Keyboard::Num3 && !textInputMode)
                {
                   textInputMode = true;
                   changedToInputMode = true;
                   save = true;
                   load = false;
                }
                else if (event.key.code == sf::Keyboard::Num4 && !textInputMode)
                {
                    textInputMode = true;
                    changedToInputMode = true;
                    load = true;
                    save = false;
                
                }
            }
            else if (event.type == sf::Event::Closed)
            {
                m_window->close();
            }

        }
    }
}

bool isAllowedChar(int num)
{
    return num >= 48 && num < 58 || num >= 65 && num < 91 || num >= 97 && num < 128;
}

