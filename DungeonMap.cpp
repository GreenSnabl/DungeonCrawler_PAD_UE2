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
#include <fstream>
#include <sstream>

using std::ifstream;
using std::stringstream;

DungeonMap::DungeonMap(int height, int width) : m_height{height}, m_width{width}
{

    m_tile = new Tile**[m_height];

    for (int i = 0; i < m_height; ++i) {
        m_tile[i] = new Tile*[m_width];
    }

    for (int i = 0; i < m_height; ++i) {
        for (int j = 0; j < m_width; ++j) {
            m_tile[i][j] = Tile::makeTile('.');
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
            m_tile[i][j] = Tile::makeTile(data[i * m_width + j]);

        }
    }
}

DungeonMap::DungeonMap(int height, int width, const std::vector<std::string>& data) : m_height{height}, m_width{width}
{
    m_tile = new Tile**[m_height];

    for (int i = 0; i < m_height; ++i) {
        m_tile[i] = new Tile*[m_width];
    }

    for (int i = 0; i < m_height; ++i) {
        for (int j = 0; j < m_width; ++j) {
            m_tile[i][j] = Tile::makeTile(data[i][j]);
        }
    }
}

DungeonMap::DungeonMap(const std::vector<std::string>& dataVec) {

    stringstream ss;
    ss << dataVec[0];
    ss >> m_height >> m_width;

    m_tile = new Tile**[m_height];
    for (int i = 0; i < m_height; ++i) {
        m_tile[i] = new Tile*[m_width];
    }
    for (int i = 0; i < m_height; ++i) {
        for (int j = 0; j < m_width; ++j) {
            m_tile[i][j] = Tile::makeTile(dataVec[i + 1][j]);
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
            if (m_tile[i][j]->getCharacter() == c) {
                return {j, i};
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

bool DungeonMap::replaceTile(const std::string& name, Position pos) {
    if (Tile* tile = Tile::makeTile(name)) 
    {
        delete find(pos);
        m_tile[pos.y][pos.x] = tile;
    }
}