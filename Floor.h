/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Floor.h
 * Author: snbl
 *
 * Created on April 27, 2018, 4:39 PM
 */

#ifndef FLOOR_H
#define FLOOR_H

#include "Tile.h"
#include "Item.h"

class Floor : public Tile {
public:
    Floor();
    ~Floor();
    
    void onEnter(Character* c);
    
    Item* takeItem();
    Item* getItem() const;
    void setItem(Item* item);
    
private:
    Item* m_item;
};

#endif /* FLOOR_H */

