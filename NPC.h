/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NPC.h
 * Author: snbl
 *
 * Created on April 27, 2018, 5:21 PM
 */

#ifndef NPC_H
#define NPC_H

#include "Character.h"

class NPC : public Character{
public:
    NPC(char sign);
    virtual ~NPC();
private:
    NPC(const NPC& orig);

};

#endif /* NPC_H */

