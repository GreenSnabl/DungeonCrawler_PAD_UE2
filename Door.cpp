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


Door::Door() : Passive('X', false), m_isOpen{false} 
{
}

Door::~Door() {}

void Door::notify() {
    m_isOpen = !m_isOpen;
    if (m_isOpen) {
        setSign('/');
        Tile::setTransparency(true);
    }
    else {
        setSign('X');
        Tile::setTransparency(false);
    }
}

bool Door::canEnter() const {
    if (m_isOpen) return Tile::canEnter();
    else return false;
}
