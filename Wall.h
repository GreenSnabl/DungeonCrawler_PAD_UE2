/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Wall.h
 * Author: snbl
 *
 * Created on April 27, 2018, 4:39 PM
 */

#ifndef WALL_H
#define WALL_H

#include "Tile.h"


class Wall : public Tile {
public:
    Wall(Position pos);
    bool canEnter() const;
    
};


#endif /* WALL_H */

