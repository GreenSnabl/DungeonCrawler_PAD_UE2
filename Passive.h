/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Passive.h
 * Author: snbl
 *
 * Created on April 27, 2018, 4:39 PM
 */

#ifndef PASSIVE_H
#define PASSIVE_H

#include "Tile.h"

class Passive : public Tile {
public:
    Passive(char sign, Position pos);
    virtual ~Passive() = 0;
    virtual void notify() = 0;
};

#endif /* PASSIVE_H */

