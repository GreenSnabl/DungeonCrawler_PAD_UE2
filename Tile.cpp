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
#include "Lever.h"
#include "Trap.h"
#include "Portal.h"


Tile::Tile(char sign, bool transparent) : m_character{nullptr}, m_sign{sign}, m_transparent{transparent}, m_walkable{true}
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
        case 'O' : return new Portal;
        case 'C': case 'N': case 'G': return new Floor;
    }
}

Tile* Tile::makeTile(const std::string& name)
{
    if (name == "Switch") return new Switch;
    else if (name == "Door") return new Door;
    else if (name == "Trap") return new Trap;
    else if (name == "Lever") return new Lever;
    else if (name == "Portal") return new Portal;
    return nullptr;
}


void Tile::setSign(char c)
{
    m_sign = c;
}



const std::vector<std::string> Tile::specialTiles{
    "Door",
    "Switch",
    "Trap",
    "Lever",
    "Portal"
};



bool Tile::isSpecialTile(const std::string& str) {
    for (int i = 0; i < specialTiles.size(); ++i)
        if (specialTiles[i] == str) return true;
    return false;
}



char Tile::getSign() const {return m_sign;}

void Tile::setTransparency(bool transparent)
{
    m_transparent = transparent;
}

bool Tile::isTransparent() const
{
    return m_transparent;
}

void Tile::setWalkable(bool walkable)
{
    m_walkable = walkable;
}

bool Tile::isWalkable() const {return m_walkable;}