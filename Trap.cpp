/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Trap.cpp
 * Author: den
 * 
 * Created on May 9, 2018, 8:29 AM
 */

#include "Trap.h"

Trap::Trap() : Active('.'), m_wasUsed(false) {
}


Trap::~Trap() {
}

void Trap::use() {
    getCharacter()->takeDamage(20);
    Tile::setSign('t');
    m_wasUsed = true;
}
void Trap::onEnter(Character* c) {
    Tile::setCharacter(c);
    if (!m_wasUsed) use();
}
