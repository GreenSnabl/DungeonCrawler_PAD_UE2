/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Active.cpp
 * Author: snbl
 * 
 * Created on April 27, 2018, 4:39 PM
 */

#include "Active.h"

Active::Active(char sign, bool transparent) : Tile(sign, transparent) {}
Active::~Active() {}

void Active::use() {
    for (auto it : m_passives){
        it->notify();
    }        
}

void Active::registerPassive(Passive* passive)
{
    m_passives.push_back(passive);
}

void Active::unregisterPassive(Passive* passive)
{
    for (int i = 0; i < m_passives.size(); ++i)
    {
        if (m_passives[i] == passive) m_passives.erase(m_passives.begin() + i);
    }
}