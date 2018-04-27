/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Controller.cpp
 * Author: snbl
 * 
 * Created on April 27, 2018, 5:03 PM
 */

#include "Controller.h"
#include "ConsoleController.h"
#include "AiController.h"

Controller::Controller() {
}

Controller::Controller(const Controller& orig) {
}

Controller::~Controller() {
}

Controller* Controller::makeController(char sign)
{
    switch(sign){
        case '@' : return new ConsoleController;
        case 'G' : return new AiController(AiController::PATROL);
        case 'O' : return new AiController(AiController::STROLLING);
        case 'z' : return new AiController(AiController::HOLD);
    }
}