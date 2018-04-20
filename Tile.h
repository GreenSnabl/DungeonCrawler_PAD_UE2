/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tile.h
 * Author: den
 *
 * Created on April 19, 2018, 8:33 PM
 */

#ifndef TILE_H
#define TILE_H
#include "Character.h"




class Tile {
public:
    enum TileType {Floor, Wall};

    Tile(TileType tiletype);
    ~Tile();
    TileType getTileType() const;
    Character* getCharacter() const;


    void setCharacter(Character* character);
    
    bool hasCharacter() const;
    
    bool canEnter() const;
    
    void onLeave(Tile* toTile);
    void onEnter(Character *c);
    
    char tileToChar() const;
    
private:
    TileType m_tileType;
    Character* m_character;
};

#endif /* TILE_H */

