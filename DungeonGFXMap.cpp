/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DungeonGFXMap.cpp
 * Author: den
 * 
 * Created on April 30, 2018, 8:54 AM
 */

#include "DungeonGFXMap.h"

using namespace DungeonGFX;

/*
Map::Map(int* tiles) 
    : Tilemap("./gfx/ProjectUtumno_full.png", 32, tiles, 10, 10) 
{

}
*/

Map::Map(sf::Texture* tileset, int* tiles) 
    : Tilemap(tileset, 32, tiles, 10, 10) 
{

}


Map::~Map() {
}

