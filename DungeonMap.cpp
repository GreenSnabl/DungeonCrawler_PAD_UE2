/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DungeonMap.cpp
 * Author: den
 * 
 * Created on April 19, 2018, 8:50 PM
 */

#include "DungeonMap.h"

DungeonMap::DungeonMap(int height, int width) : m_height{height}, m_width{width}
{

    m_screen = new Screen(m_width, m_height);
    m_screen->addSubScreen(m_screen, {0,0}, "map");
    
    m_tile = new Tile**[m_height];
       
    for (int i = 0; i < m_height; ++i) {
        m_tile[i] = new Tile*[m_width];
    }

    for (int i = 0; i < m_height; ++i) {
        for (int j = 0; j < m_width; ++j) {
            m_tile[i][j] = new Tile(Tile::Floor);
            m_screen->getSubScreen("map")->setChar({j,i}, m_tile[i][j]->tileToChar());
        }
    }
    
    

    
}

DungeonMap::DungeonMap(int height, int width, const std::string& data) : m_height{height}, m_width{width}
{
    
    m_screen = new Screen(m_width, m_height);
    m_screen->addSubScreen(m_screen, {0,0}, "map");
    
    m_tile = new Tile**[m_height];

    for (int i = 0; i < m_height; ++i) {
        m_tile[i] = new Tile*[m_width];
    }

    for (int i = 0; i < m_height; ++i) {
        for (int j = 0; j < m_width; ++j) {
            if (data[i * m_width + j] == '#'){
            m_tile[i][j] = new Tile(Tile::Wall);
            } else {
            m_tile[i][j] = new Tile(Tile::Floor);  
            }
            m_screen->getSubScreen("map")->setChar({j,i}, m_tile[i][j]->tileToChar());
        }
    }
}

DungeonMap::DungeonMap(const DungeonMap& orig) : m_height{orig.m_height}, m_width{orig.m_width}
{
    m_screen = new Screen(*orig.m_screen);
    
    m_tile = new Tile**[m_height];

    for (int i = 0; i < m_height; ++i) {
        m_tile[i] = new Tile*[m_width];
    }

    for (int i = 0; i < m_height; ++i) {
        for (int j = 0; j < m_width; ++j) {
            m_tile[i][j] = new Tile(orig.m_tile[i][j]->getTileType());      
        }
    }
}

DungeonMap::~DungeonMap() {
    for (int i = 0; i < m_height; ++i) {
        for (int j = 0; j < m_width; ++j) {
            delete m_tile[i][j];
        }
    }

    for (int i = 0; i < m_height; ++i) {
        delete[] m_tile[i];
    }

    delete[] m_tile;
    delete m_screen;
}

void DungeonMap::place(Position pos, Character* c)
{
    find(pos)->setCharacter(c);
    m_screen->getSubScreen("map")->setChar({pos.x, pos.y}, c->getSign());
}

Position DungeonMap::find(Tile* t) const
{
    for (int i = 0; i < m_height; ++i) {
        for (int j = 0; j < m_width; ++j)
        {
            if (m_tile[j][i] == t) {
                return {j,i};
            }
        }
    }
}

Position DungeonMap::find(Character* c) const
{
    for (int i = 0; i < m_height; ++i) {
        for (int j = 0; j < m_width; ++j)
        {
            if (m_tile[j][i]->getCharacter() == c) {
                return {j,i};
            }
        }
    }
}

Tile* DungeonMap::find(Position pos) const
{
    return m_tile[pos.y][pos.x];
}


void DungeonMap::print() const
{
    for (int i = 0; i < m_height; ++i) {
        for (int j = 0; j < m_width; ++j) {
            if (find({j,i})->hasCharacter()) {
            m_screen->getSubScreen("map")->setChar({j,i}, (find({j,i})->getCharacter()->getSign()));
        }
    }
    }
    
    m_screen->draw();
}