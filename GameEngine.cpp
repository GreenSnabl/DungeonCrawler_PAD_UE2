/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GameEngine.cpp
 * Author: den
 * 
 * Created on April 19, 2018, 9:08 PM
 */

#include "GameEngine.h"

GameEngine::GameEngine(int height, int width, const std::string& data) {
}

GameEngine::GameEngine(const GameEngine& orig) {
}

GameEngine::~GameEngine() {
}

bool GameEngine::turn()
{
}

bool GameEngine::finished()
{
}

void GameEngine::run()
{
    while (!finished())
    {
        turn();
    }
}
