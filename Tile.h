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
    Tile();
//    Tile(const Tile& other);
    virtual ~Tile() = 0;
    Character* getCharacter() const;

    void setCharacter(Character* character);
    bool hasCharacter() const;
    
    virtual bool canEnter() const;
    virtual void onLeave(Tile* toTile);
    virtual void onEnter(Character *c);
    
    virtual char tileToChar() const = 0;
    
    
private:
    Character* m_character;
};

class Floor : public Tile
{
public:
    Floor();
    char tileToChar() const;
};

class Wall : public Tile {
public:
    Wall();
    bool canEnter() const;
    char tileToChar() const;
    
};

class Passive : public Tile {
public:
    virtual ~Passive() = 0;
    void notify();
};

class Active : public Tile {
public:
    virtual ~Active() = 0;
    void registerPassive(Passive*);
    void unregisterPassive(Passive*);
private:
    std::vector<Passive*> m_passives;
};

class Switch : public Active {
public:
    Switch();
    ~Switch();
    
    char tileToChar() const;
    bool use();
private:
    
    bool m_wasUsed;
    char m_sign;
    Switch(const Switch& orig);
};

#endif /* TILE_H */

