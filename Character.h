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

class Character {
public:
    Character(char sign);
    Character(const Character& orig);
    virtual ~Character();


    char getSign() const;
    int move();
private:
    char m_sign;

};

#endif /* CHARACTER_H */

