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

    m_tile = new Tile**[m_height];

    for (int i = 0; i < m_height; ++i) {
        m_tile[i] = new Tile*[m_width];
    }

    for (int i = 0; i < m_height; ++i) {
        for (int j = 0; j < m_width; ++j) {
            m_tile[i][j] = new Floor;
        }
    }
}

DungeonMap::DungeonMap(int height, int width, const std::string& data) : m_height{height}, m_width{width}
{


    m_tile = new Tile**[m_height];

    for (int i = 0; i < m_height; ++i) {
        m_tile[i] = new Tile*[m_width];
    }

    for (int i = 0; i < m_height; ++i) {
        for (int j = 0; j < m_width; ++j) {
            switch (data[i * m_width + j]) {
                case '.': m_tile[i][j] = new Floor; break;
                case '#': m_tile[i][j] = new Wall; break;     
            }
        }
    }
}
/*
DungeonMap::DungeonMap(const DungeonMap& orig) : m_height{orig.m_height}, m_width{orig.m_width}
{

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
*/
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
}

void DungeonMap::place(Position pos, Character* c) {
    find(pos)->setCharacter(c);
}

Position DungeonMap::find(Tile* t) const {
    for (int i = 0; i < m_height; ++i) {
        for (int j = 0; j < m_width; ++j) {
            if (m_tile[j][i] == t) {
                return {j, i};
            }
        }
    }
}

Position DungeonMap::find(Character* c) const {
    for (int i = 0; i < m_height; ++i) {
        for (int j = 0; j < m_width; ++j) {
            if (m_tile[j][i]->getCharacter() == c) {
                return {i, j};
            }
        }
    }
}

Tile* DungeonMap::find(Position pos) const {
    return m_tile[pos.y][pos.x];
}

void DungeonMap::print() const {
    Screen screen(m_width, m_height);
    
    for (int i = 0; i < m_height; ++i) {
        for (int j = 0; j < m_width; ++j) {
            
            screen.setChar({j, i}, find({j, i})->tileToChar());
            
            if (find({j, i})->hasCharacter()) {
                screen.setChar({j, i}, find({j, i})->getCharacter()->getSign());
            }
        }
    }
    screen.draw();
}