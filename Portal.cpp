/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Portal.cpp
 * Author: snbl
 * 
 * Created on May 26, 2018, 2:29 PM
 */

#include "Portal.h"
#include "Active.h"

Portal::Portal() : Tile('O', true) {
}


Portal::~Portal() {
}

void Portal::setDestination(Portal* portal)
{
    m_destination = portal;
}

Portal* Portal::getDestination()
{
   return m_destination;
}

bool Portal::canEnter() const
{
    return !m_destination->hasCharacter() && !hasCharacter();    
}

void Portal::onEnter(Character* c)
{
    m_destination->setCharacter(c);
}