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
#include "Screen.h"

struct Position{
    int x;
    int y;

    friend std::ostream& operator<<(std::ostream& os, const Position& pos);
    friend std::istream& operator>>(std::istream& is, Position& pos);
};

class DungeonMap {
public:
    DungeonMap(const std::vector<std::string>& dataVec);
    ~DungeonMap();
    
    void place(Position pos, Character* c);
    
    bool replaceTile(const std::string& name, Position pos);
    
    Position find(Tile* t) const;
    Position find(Character* c) const;
    
    Tile* find(Position pos) const;
    
    void print() const;
    void print(Position) const;
    
    int getHeight() const {return m_height;}
    int getWidth() const {return m_width;}
    
    bool checkLine(Position from, Position to) const;
    
    
private:
    Tile*** m_tile;
    int m_height;
    int m_width;

    DungeonMap(const DungeonMap& orig);
};

#endif /* DUNGEONMAP_H */

