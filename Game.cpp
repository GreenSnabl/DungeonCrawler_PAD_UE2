/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.cpp
 * Author: snbl
 * 
 * Created on June 1, 2018, 6:21 PM
 */

#include "Game.h"
#include "GameEngine.h"
#include <string>

Game::Game(const std::string& mapFile) {
    GameEngine* currentLevel = new GameEngine(mapFile);
    while (currentLevel->run())
    {
        std::string newLevel = currentLevel->getNewMap();
        delete currentLevel;
        currentLevel = new GameEngine(newLevel);
    }
    delete currentLevel;
}


Game::~Game() {
}

