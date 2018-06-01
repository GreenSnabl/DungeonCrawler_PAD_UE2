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

Floor::Floor() : Tile('.', true), m_item{nullptr} {}

Floor::~Floor() {
    if (m_item)
    {
        delete m_item;
    }
}

void Floor::onEnter(Character* c)
{
    if (getItem())
    {
        c->addItem(takeItem());    
    }
    Tile::onEnter(c);
}

bool Floor::hasItem() const
{
    return (m_item != nullptr);
}

Item* Floor::getItem() const
{
    return m_item;
}

Item* Floor::takeItem() {
    Item* temp = m_item;
    m_item = nullptr;
    return temp;
}
void Floor::setItem(Item* item) {
    m_item = item;
}

char Floor::tileToChar() const
{
    if (getItem()) return '*';
    return Tile::getSign();
}