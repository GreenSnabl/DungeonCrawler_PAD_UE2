/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Lever.h
 * Author: den
 *
 * Created on May 9, 2018, 8:20 AM
 */

#ifndef LEVER_H
#define LEVER_H

#include "Active.h"

class Lever : public Active {
public:
    Lever();
    virtual ~Lever();
    void use();
    virtual void onEnter(Character* c);

private:
    bool m_wasUsed;
    
    Lever(const Lever& orig);
};

#endif /* LEVER_H */

