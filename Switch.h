/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Switch.h
 * Author: snbl
 *
 * Created on April 27, 2018, 4:39 PM
 */

#ifndef SWITCH_H
#define SWITCH_H

#include "Active.h"

class Switch : public Active {
public:
    Switch(Position pos);
    ~Switch();
    void use();
    virtual void onEnter(Character* c);
private:
    bool m_wasUsed;
    Switch(const Switch& orig);
};

#endif /* SWITCH_H */

