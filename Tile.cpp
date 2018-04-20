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


Tile::Tile(TileType tileType) : m_tileType {tileType}, m_character{nullptr}
{
}

Tile::~Tile() {
}

Tile::TileType Tile::getTileType() const
{
    return m_tileType;
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
    if (m_tileType == Floor && m_character == nullptr) return true;
    return false;
}

void Tile::onLeave(Tile* toTile) {
    if (toTile->canEnter()) {
        onEnter(m_character);
        m_character == nullptr;
    }    
}

void Tile::onEnter(Character* c) {
    m_character == c;
}


char Tile::tileToChar() const
{
    switch(m_tileType) {
        case Wall   : return '#';
        case Floor  : return '.';
    }
}



/*
Tile::TileType charToTileType(const char& c)
{
    switch (c){
        case '#' : return Tile::Wall;
        case '.' : return Tile::Floor;
    }
} */