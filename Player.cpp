/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Player.cpp
 * Author: snbl
 * 
 * Created on April 27, 2018, 5:21 PM
 */

#include "Player.h"
#include "ConsoleController.h"


Player::Player(Position pos) : Character('@', new ConsoleController, pos) {
    setSpriteId(500);
}


Player::~Player() {
}

