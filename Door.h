/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Door.h
 * Author: snbl
 *
 * Created on April 27, 2018, 4:39 PM
 */

#ifndef DOOR_H
#define DOOR_H
#include "Active.h"


class Door : public Passive {
public:
    Door(Position pos);
    ~Door();
    bool canEnter() const;
    void notify();

private:
    bool m_isOpen;
};


#endif /* DOOR_H */

