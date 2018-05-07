/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Floor.cpp
 * Author: snbl
 * 
 * Created on April 27, 2018, 4:39 PM
 */

#include "Floor.h"

Floor::Floor() : Tile('.') {}


Item* Floor::getItem() const {
    return m_item;
}
void Floor::setItem(Item* item) {
    m_item = item;
}
