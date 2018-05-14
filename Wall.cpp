/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Wall.cpp
 * Author: snbl
 * 
 * Created on April 27, 2018, 4:39 PM
 */

#include "Wall.h"


Wall::Wall() : Tile('#', false) 
{
    setWalkable(false);
}

bool Wall::canEnter() const {
        return false;
    }