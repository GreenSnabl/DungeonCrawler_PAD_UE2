/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Switch.cpp
 * Author: snbl
 * 
 * Created on April 27, 2018, 4:39 PM
 */

#include "Switch.h"

Switch::Switch() : Active('?'), m_wasUsed(false) 
{
    setSpriteId(751);
}

Switch::~Switch() {}

void Switch::use() {
    Active::use();
    Tile::setSign('!');
    m_wasUsed = true;
    setSpriteId(360);
}

void Switch::onEnter(Character* c)
{
    Tile::setCharacter(c);
    if (!m_wasUsed) use();
}