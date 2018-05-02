/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Active.h
 * Author: snbl
 *
 * Created on April 27, 2018, 4:39 PM
 */

#ifndef ACTIVE_H
#define ACTIVE_H

#include "Tile.h"
#include "Passive.h"

class Active : public Tile {
public:
    Active(char sign);
    virtual ~Active() = 0;
    void registerPassive(Passive*);
    void unregisterPassive(Passive*);
    virtual void use();
private:
    std::vector<Passive*> m_passives;
};

#endif /* ACTIVE_H */

