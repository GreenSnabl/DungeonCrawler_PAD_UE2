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
#include "Player.h"
#include "NPC.h"


Character::Character(char sign, Controller* controller) : m_sign{sign}, m_controller{controller} {
}

Character::Character(char sign, Controller* controller, int strength, int stamina) : m_sign{sign}, m_controller{controller}, m_strength{strength}, m_stamina{stamina}, m_hitpoints{getMaxHP()} {
}


Character::Character(const Character& orig) {

}

Character::~Character() {
    delete m_controller;
}

char Character::getSign() const
{
    return m_sign;
}

int Character::move()
{
    m_controller->move();
}

Character* Character::makeCharacter(char sign)
{
    switch (sign) {
        case 'C'  : return new Player;
        case 'G'  : return new Enemy(sign, new AiController(AiController::STROLL));
        case 'N'  : return new Neutral(sign, new AiController(AiController::HOLD));
        default   : return nullptr;
    }
}


    int Character::getMaxHP() const {return 20 + getStamina() * 5;}
    
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