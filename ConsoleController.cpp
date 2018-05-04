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

ConsoleController::ConsoleController() {
}

ConsoleController::ConsoleController(const ConsoleController& orig) {
}

ConsoleController::~ConsoleController() {
}

int ConsoleController::move()
{
    return m_next_move;
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
    m_next_move = next_move;
}