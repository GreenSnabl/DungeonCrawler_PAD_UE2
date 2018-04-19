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

TileType Tile::getTileType() const
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
    