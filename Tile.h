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
    Tile(char sign, bool transparent);
//    Tile(const Tile& other);
    virtual ~Tile() = 0;
    Character* getCharacter() const;

    void setCharacter(Character* character);
    bool hasCharacter() const;
    
    virtual bool canEnter() const;
    virtual void onLeave(Tile* toTile);
    virtual void onEnter(Character *c);
    
    virtual char tileToChar() const;
    
    static Tile* makeTile(char c);
    static Tile* makeTile(const std::string& name);
    
    
    virtual void setSign(char c);
    char getSign() const;
    
    static bool isSpecialTile(const std::string& str);
    
    virtual bool isTransparent() const;
    void setTransparency(bool);
    
    virtual bool isWalkable() const;
    void setWalkable(bool);
    
    
private:
    Character* m_character;
    char m_sign;
    
    bool m_transparent;
    bool m_walkable;
    
    const static std::vector<std::string> specialTiles;
};

#endif /* TILE_H */

