/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DungeonMap.h
 * Author: den
 *
 * Created on April 19, 2018, 8:50 PM
 */

#ifndef DUNGEONMAP_H
#define DUNGEONMAP_H
#include "Tile.h"
#include "Character.h"
#include <string>
#include <vector>

struct Position{
    int x;
    int y;
};

class DungeonMap {
public:
    DungeonMap(int height, int width);
    DungeonMap(int height, int width, std::vector<std::string>& data);
    DungeonMap(const DungeonMap& orig);
    
    virtual ~DungeonMap();
    
    void place(Position pos, Character* c);
    
    Position find(Tile* t) const;
    Position find(Character* c) const;
    
    Tile* find(Position pos) const;
    
    void print() const;
    
    
private:
    Tile*** m_tile;
    const int m_height;
    const int m_width;

};

#endif /* DUNGEONMAP_H */

