/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Character.h
 * Author: den
 *
 * Created on April 19, 2018, 8:36 PM
 */

#ifndef CHARACTER_H
#define CHARACTER_H
#include "Controller.h"


class Character {
public:
    Character(char sign);
    virtual ~Character() = 0;
    
    char getSign() const;
    int move();
private:
    
    char m_sign;
    Controller* m_controller;

    
    Character(const Character& orig);
};

#endif /* CHARACTER_H */

