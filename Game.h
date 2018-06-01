/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.h
 * Author: snbl
 *
 * Created on June 1, 2018, 6:21 PM
 */

#ifndef GAME_H
#define GAME_H
#include <string>

class Game {
public:
    Game(const std::string& MapFile);
   ~Game();
private:
    std::string nextLevel;

};

#endif /* GAME_H */

