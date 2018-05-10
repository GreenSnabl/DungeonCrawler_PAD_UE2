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
#include <cmath>

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

void DungeonMap::print(Position pos) const
{
    Screen screen(m_width, m_height);

    for (int i = 0; i < m_height; ++i) {
        for (int j = 0; j < m_width; ++j) {

            if (checkLine(pos, {j, i})) {
            screen.setChar({j, i}, find({j, i})->tileToChar());

            if (find({j, i})->hasCharacter()) {
                screen.setChar({j, i}, find({j, i})->getCharacter()->getSign());
            }
            }
            else 
            {
                screen.setChar({j,i},'#');
            }
        }
    }
    screen.draw();
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
    delete m_tile[pos.y][pos.x];
    m_tile[pos.y][pos.x] = Tile::makeTile(name);
    
/*
    if (Tile* tempTile = find(pos)) {
        if (Tile* newTile = Tile::makeTile(name)) 
        {
        delete tempTile;
        m_tile[pos.y][pos.x] = newTile;
        }
    }
 */
}


bool DungeonMap::checkLine(Position from, Position to) const
{
    double dy = to.y - from.y;
    double dx = to.x - from.x;
    double nx = std::abs(dx); double ny = std::abs(dy);
    int sign_x = dx > 0 ? 1 : -1;
    int sign_y = dy > 0 ? 1 : -1;
    double err = 0.4;
    
    Position p{from.x, from.y};
        
    int ix = 0; int iy = 0;
    
    while (ix < nx || iy < ny)
    {
        if ((err + ix) / nx == (err + iy) / ny) {
            p.x += sign_x;
            p.y += sign_y;
            ix++;
            iy++;
        }
        else if ((err + ix / nx) < (err + iy) / ny) {
            p.x += sign_x;
            ix++;        
        }
        else {
            p.y += sign_y;
            iy++;
        }
        if (!m_tile[p.y][p.x]->isTransparent()) return false;
        if (p.x == to.x && p.y == to.y) return true;
    }
    return true;
}

