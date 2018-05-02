/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Door.cpp
 * Author: snbl
 * 
 * Created on April 27, 2018, 4:39 PM
 */

#include "Door.h"


Door::Door(Position pos) : Passive('X', pos), m_isOpen{false} 
{
    setSpriteId(400);
}

Door::~Door() {}

void Door::notify() {
    setSign('/');
    m_isOpen = true;
}

bool Door::canEnter() const {
    if (m_isOpen) return Tile::canEnter();
    else return false;
}

