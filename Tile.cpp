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


Tile::Tile() : m_character{nullptr}
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


Floor::Floor() {}
Wall::Wall() {}

char Floor::tileToChar() const {return '.';}
char Wall::tileToChar() const {return '#';}


bool Wall::canEnter() const {
        return false;
    }


Active::~Active() {}
Switch::Switch() : m_wasUsed(false), m_sign('?') {}
Switch::~Switch() {}

bool Switch::use() {
    m_sign = '!';
    return m_wasUsed = true;
}

char Switch::tileToChar() const
{
    return m_sign;
}
