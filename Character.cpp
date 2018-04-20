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
#include <iostream>

using std::cin;

Character::Character(char sign) : m_sign{sign} {
}

Character::Character(const Character& orig) {
}

Character::~Character() {
}

char Character::getSign() const
{
    return m_sign;
}

int Character::move()
{
    char c = '0';
    while (c < '1' || c > '9') {
        cin >> c;
    }
    return static_cast<int>(c-'0');    
}