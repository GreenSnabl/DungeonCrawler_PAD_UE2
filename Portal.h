/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Portal.h
 * Author: snbl
 *
 * Created on May 26, 2018, 2:29 PM
 */

#ifndef PORTAL_H
#define PORTAL_H
#include "Active.h"
#include "Passive.h"


class Portal : public Tile {
public:
    Portal();
    virtual ~Portal();
    void onEnter(Character* c);
    bool canEnter() const;
    
    Portal* getDestination();
    void setDestination(Portal* portal);
    
private:
    
    Portal* m_destination;    
    Portal(const Portal& orig);

};

#endif /* PORTAL_H */

