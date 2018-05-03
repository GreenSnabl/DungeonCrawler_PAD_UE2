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
#include <vector>




class Tile {
public:
    Tile(char sign);
    virtual ~Tile() = 0;
    Character* getCharacter() const;

    void setCharacter(Character* character);
    bool hasCharacter() const;
    
    virtual bool canEnter() const;
    virtual void onLeave(Tile* toTile);
    virtual void onEnter(Character *c);
    
    virtual char tileToChar() const;
    static Tile* makeTile(char c, Position pos);
    
    virtual void setSign(char c);
    int getSign() const {return m_sign;}
        
    void setSpriteId(int id) { m_spriteId = id;}
    int getSpriteId() const { return m_spriteId;}
    
private:
    Character* m_character;
    char m_sign;

    Tile(const Tile& other);

    int m_spriteId;
};

#endif /* TILE_H */

