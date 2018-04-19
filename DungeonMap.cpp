/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DungeonMap.cpp
 * Author: den
 * 
 * Created on April 19, 2018, 8:50 PM
 */

#include "DungeonMap.h"

DungeonMap::DungeonMap(int height, int width) : m_height{height}, m_width{width}{
}

DungeonMap::DungeonMap(int height, int width, std::vector<std::string>& data) : m_height{height}, m_width{width} {
}

DungeonMap::DungeonMap(const DungeonMap& orig) : m_height{orig.m_height}, m_width{orig.m_width}{
}

DungeonMap::~DungeonMap() {
}

