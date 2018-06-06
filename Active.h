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
    Active(char sign, bool transparent, bool wasUsed);
    virtual ~Active() = 0;
    virtual void registerPassive(Passive*);
    virtual void unregisterPassive(Passive*);
    virtual void use();
    virtual int getPassiveSize() const;
    virtual Passive* getPassive(int index) const;
    
    bool getWasUsed() const;
    virtual void setWasUsed(bool wasUsed);
    
private:
    std::vector<Passive*> m_passives;
    bool m_wasUsed;
};

#endif /* ACTIVE_H */

