/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Character.cpp
 * Author: den
 * 
 * Created on April 19, 2018, 8:36 PM
 */

#include "Character.h"
#include "ConsoleController.h"
#include "AiController.h"
#include <sstream>


Character::Character(char sign, Controller* controller) : m_sign{sign}, m_controller{controller}
{
}

Character::Character(char sign, int strength, int stamina, Controller* controller) : m_sign{sign}, m_strength{strength}, m_stamina{stamina}, m_controller{controller}
{
    m_hitpoints = getMaxHP();
    m_alive = isAlive();
}

Character::Character(const Character& orig) {

}

Character::~Character() {
    for (int i = 0; i < m_items.size(); ++i)
        delete m_items[i];
    delete m_controller;
}

char Character::getSign() const {
    return m_sign;
}

int Character::move() {
    m_controller->move();
}

Character* Character::makeCharacter(const std::string& data) {
    std::stringstream ss;
    ss << data;
    std::string name, controllerType;
    Position pos;
    char sign;
    int strength, stamina;
    ss >> name >> sign >> pos>> controllerType >> stamina >> strength;
    // pos.y >> pos.x 
    Character* character = nullptr;
    if (controllerType == "StationaryController") {
        character = new Character(sign, stamina, strength, new AiController(AiController::HOLD));
    } else if (controllerType == "AiController") {
        character = new Character(sign, stamina, strength, new AiController(AiController::STROLL));
    } else if (controllerType == "ConsoleController") {
        character = new Character(sign, stamina, strength, new ConsoleController());
    }
    return character;
}

int Character::getMaxHP() const {
    return 20 + getStamina() * 5;
}

int Character::getCurrentHP() const {
    return m_hitpoints;
}

void Character::setCurrentHP(int currentHP)
{
    m_hitpoints = currentHP;
}

bool Character::isAlive() const {
    return m_hitpoints > 0;
}

bool Character::takeDamage(int damage)
{
    if (m_hitpoints - damage > 0) m_hitpoints -= damage;
    else m_hitpoints = 0;
    
    return !isAlive();
}

int Character::getStamina() const {
    int stamina = m_stamina;
    //for (auto it : m_items)
    //    stamina += *it->modifyStamina(m_stamina);
    for (int i = 0; i < m_items.size(); ++i)
        stamina += m_items[i]->modifyStamina(m_stamina);
    return stamina;
}

int Character::getStrength() const {
    int strength = m_strength;
    //for (auto it : m_items)
    //    stamina += *it->modifyStrength(m_strength);
    for (int i = 0; i < m_items.size(); ++i)
        strength += m_items[i]->modifyStrength(strength);
    return strength;
}

void Character::updateCurrentHP(double percentageOfRemainingHP)
{
    m_hitpoints = static_cast<int>(getMaxHP() * percentageOfRemainingHP);    
}

void Character::addItem(Item* item) {
    int prevMaxHP = getMaxHP();
    double percentage = m_hitpoints / static_cast<double>(prevMaxHP);
    m_items.push_back(item);
    updateCurrentHP(percentage);
}

int Character::getItemSize() const {return m_items.size();}

Item* Character::getItem(int index) const {
    return m_items[index];
}