/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AiController.h
 * Author: snbl
 *
 * Created on April 27, 2018, 5:14 PM
 */

#ifndef AICONTROLLER_H
#define AICONTROLLER_H
#include "Controller.h"
#include "DungeonMap.h"
#include "GameEngine.h"


class AiController : public Controller {
public:
    enum Behaviour{STROLL, HOLD, PATROL, ATTACK};
    
    AiController(Behaviour behaviour);
    ~AiController();
    
    int move();
    
    void updateBehaviour(const DungeonMap& map, Position from, Position to);
    void updateShortestPath();
    
    Behaviour getBehaviour() const;
    void setBehaviour(Behaviour behaviour);
    
private:
    int patrol();
    int stroll();
    int hold();
    int attack();
    
    Behaviour m_behaviour;
    vector<Position> m_attackPath;
    
    AiController(const AiController& orig);
};

#endif /* AICONTROLLER_H */

