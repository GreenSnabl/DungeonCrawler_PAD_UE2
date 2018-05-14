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
        case STROLL : return stroll();
        case ATTACK : return attack();
        default : return stroll();
    }
}

int AiController::patrol()
{
    static int patrolIndex = -1;
    vector<int> patrolMovement{4,4,4,8,8,8,8,6,6,6,2,2,2,2,2,2};
    return patrolMovement[++patrolIndex % patrolMovement.size()];
    
}

int AiController::stroll()
{
    return (std::rand() % 9) + 1;
}

int AiController::hold()
{
    return 5;
}

int AiController::attack() 
{
    if (m_attackPath.size() == 0) return stroll();
    return posToInt(m_attackPath[0]);
}

AiController::Behaviour AiController::getBehaviour() const
{
    return m_behaviour;
}
void AiController::setBehaviour(AiController::Behaviour behaviour) 
{
    m_behaviour = behaviour;
}

void AiController::updateBehaviour(const DungeonMap& map, Position from, Position to)
{
    if (map.checkLine(from, to)) {
        setBehaviour(ATTACK);
        updateShortestPath();
    }

}


void AiController::updateShortestPath() 
{

}