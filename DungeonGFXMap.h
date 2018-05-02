/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DungeonGFXMap.h
 * Author: den
 *
 * Created on April 30, 2018, 8:54 AM
 */

#ifndef DUNGEONGFXMAP_H
#define DUNGEONGFXMAP_H

#include "Tilemap.h"
#include "Tile.h"


namespace DungeonGFX { 
    const int WALL = 135; 
    const int FLOOR = 202;
    const int SWITCH = 402;
    const int DOOR_CLOSED = 502;    
    const int DOOR_OPEN = 503;
    const int ENEMY = 300;


class Map : public Tilemap {
public:
    Map(int* tiles);
    Map(sf::Texture* tileset, int* tiles);
    ~Map();
    
    
private:

};

};

#endif /* DUNGEONGFXMAP_H */

