/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Lever.cpp
 * Author: den
 * 
 * Created on May 9, 2018, 8:20 AM
 */

#include "Lever.h"

Lever::Lever() : Active('L'), m_wasUsed(false) {}

Lever::~Lever() {}

void Lever::use() {
    Active::use();
    m_wasUsed = !m_wasUsed;
    m_wasUsed ? Tile::setSign('l') : Tile::setSign('L');
}

void Lever::onEnter(Character* c)
{
    Tile::setCharacter(c);
    use();
}