/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Trap.h
 * Author: den
 *
 * Created on May 9, 2018, 8:29 AM
 */

#ifndef TRAP_H
#define TRAP_H

#include "Active.h"

class Trap  : public Active {
public:
    Trap();
    ~Trap();
    void use();
    void setWasUsed(bool wasUsed);
    virtual void onEnter(Character* c);
private:
    Trap(const Trap& orig);
};

#endif /* TRAP_H */

