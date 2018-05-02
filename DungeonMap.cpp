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
            m_tile[i][j] = Tile::makeTile('.', {j,i});
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
            m_tile[i][j] = Tile::makeTile(data[i * m_width + j], {j,i});

        }
    }
}

DungeonMap::DungeonMap(int height, int width, const std::vector<std::string>& data, sf::Texture& tileset) : m_height{height}, m_width{width}
{
    
    m_intMap = new int[m_height * m_width];
    
    m_tile = new Tile**[m_height];

    for (int i = 0; i < m_height; ++i) {
        m_tile[i] = new Tile*[m_width];
    }

    
    
    for (int i = 0; i < m_height; ++i) {
        for (int j = 0; j < m_width; ++j) {
            m_tile[i][j] = Tile::makeTile(data[i][j], {j, i});
            m_intMap[i * m_width + j] = m_tile[i][j]->getSpriteIde();
        }
    }
    gfxMap = new DungeonGFX::Map(&tileset, m_intMap);
    
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
    delete[] m_intMap;
    delete gfxMap;
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

void DungeonMap::print(sf::RenderWindow& window) const {
    
    
    //window.clear();
    
    gfxMap->draw(window);
   
    
}



int DungeonMap::tileToInt(Tile* tile)
{
    switch (tile->getSign())
    {
        case '#' : return DungeonGFX::WALL;
        default : return DungeonGFX::FLOOR;    
    }
}