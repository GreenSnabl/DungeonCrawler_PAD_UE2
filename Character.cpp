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


Character::Character(char sign) : m_sign{sign} {
    m_controller = new ConsoleController;
}

Character::Character(const Character& orig) {
    delete m_controller;
}

Character::~Character() {
}

char Character::getSign() const
{
    return m_sign;
}

int Character::move()
{
    m_controller->move();
}