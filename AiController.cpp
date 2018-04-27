/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AiController.cpp
 * Author: snbl
 * 
 * Created on April 27, 2018, 5:14 PM
 */

#include "AiController.h"

AiController::AiController(Behaviour behaviour) : m_behaviour{behaviour} {
}

AiController::~AiController() {
}

int AiController::move()
{
    switch(m_behaviour) { 
        case PATROL : return patrol();
        case HOLD   : return hold();
        case STROLLING : return strolling();
        default : return strolling();
    }
}

int AiController::patrol()
{
    static int patrolIndex = -1;
    vector<int> patrolMovement{4,4,4,8,8,8,8,6,6,6,2,2,2,2,2,2};
    return patrolMovement[++patrolIndex%patrolMovement.size()];
    
}

int AiController::strolling()
{
    return (std::rand() % 9) + 1;
}

int AiController::hold()
{
    return 5;
}