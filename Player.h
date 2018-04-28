/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Player.h
 * Author: snbl
 *
 * Created on April 27, 2018, 5:21 PM
 */

#ifndef PLAYER_H
#define PLAYER_H
#include "Character.h"

class Player : public Character{
public:
    Player();
    ~Player();
private:
    Player(const Player& orig);
};

#endif /* PLAYER_H */

