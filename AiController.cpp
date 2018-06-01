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
#include "Ai.h"
#include <map>

using std::map;

AiController::AiController(Behaviour behaviour) : m_behaviour{behaviour}, next_move{Position({0,0})} {

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
    if (next_move == Position({0,0})) return stroll();
   // if (m_attackPath.size() == 0) return stroll();
    return posToInt(next_move);
}

AiController::Behaviour AiController::getBehaviour() const
{
    return m_behaviour;
}


void AiController::setBehaviour(AiController::Behaviour behaviour) 
{
    m_behaviour = behaviour;
}

void AiController::updateBehaviour(DungeonMap* m_map, Position from, Position to)
{
    if (getBehaviour() == Behaviour::HOLD) return;
    if (m_map->checkLine(from, to)) {
        setBehaviour(AiController::ATTACK);
        
        //map<Position, map<Position, int> > graph;
        map<Position, map<Position, double> > graph;
        
        std::map<Position, Position> previous;
        vector<Position> attackPath;
        
        fillGraph(m_map, graph);
        a_star(from, to, graph, previous);
        //dijkstra(from, graph, previous);
        
        if(getShortestPath(attackPath, from, to, previous))
            updateAttackPath(attackPath);
        
    }
    else {
        setBehaviour(STROLL);    
    }
}


void AiController::updateAttackPath(const vector<Position>& attackPath) 
{
    if (attackPath.size() < 1) {setBehaviour(AiController::STROLL);return;}
    next_move = {attackPath[1].x - attackPath[0].x, attackPath[1].y - attackPath[0].y};
}
