/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ConsoleController.cpp
 * Author: snbl
 * 
 * Created on April 27, 2018, 5:04 PM
 */

#include "ConsoleController.h"
#include <iostream>

using std::cin;

ConsoleController::ConsoleController() : m_nextMove{5}, m_madeTurn{false} {
}

ConsoleController::ConsoleController(const ConsoleController& orig) {
}

ConsoleController::~ConsoleController() {
}

bool ConsoleController::madeTurn() const
{
    return m_madeTurn;
}
void ConsoleController::setMadeTurn(bool madeTurn)
{
    m_madeTurn = madeTurn;
}

void ConsoleController::setPlayerNr(int playerNr) 
{
    mPlayerNr = playerNr;
}


int ConsoleController::getPlayerNr() const
{
    return mPlayerNr;
}



int ConsoleController::move()
{
    int temp = m_nextMove;
    m_nextMove = 5;
    return temp;
    /*
    char c = '0';
    while (c < '1' || c > '9') {
        cin >> c;
    }
    return static_cast<int>(c-'0');    
    */
 }

void ConsoleController::set_next_move(int next_move) 
{
    m_nextMove = next_move;
    setMadeTurn(true);
}