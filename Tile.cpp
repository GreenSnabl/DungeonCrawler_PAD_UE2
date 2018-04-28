/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tile.cpp
 * Author: den
 * 
 * Created on April 19, 2018, 8:33 PM
 */

#include "Tile.h"
#include "Floor.h"
#include "Wall.h"
#include "Switch.h"
#include "Door.h"


Tile::Tile(char sign) : m_character{nullptr}, m_sign{sign}
{
}


Tile::~Tile() {
}




Character* Tile::getCharacter() const
{
    return m_character;
}

void Tile::setCharacter(Character* character)
{
    m_character = character;
}

bool Tile::hasCharacter() const
{
    return m_character != nullptr;
}

bool Tile::canEnter() const
{
    if (!hasCharacter()) return true;
    return false;
}

void Tile::onLeave(Tile* toTile) {
    if (toTile->canEnter()) {
        toTile->onEnter(m_character);
        m_character = nullptr;
    }    
}

void Tile::onEnter(Character* c) {
    m_character = c;
}

char Tile::tileToChar() const {
    return m_sign;
}


Tile* Tile::makeTile(char c){
    switch(c) {
        case '.' : return new Floor;
        case '#' : return new Wall;
        case 'D' : return new Door;
        case 'S' : return new Switch;
        case 'C': case 'N': case 'G': return new Floor;
    }
}

void Tile::setSign(char c)
{
    m_sign = c;
}





