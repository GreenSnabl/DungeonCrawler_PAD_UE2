/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ConsoleController.h
 * Author: snbl
 *
 * Created on April 27, 2018, 5:04 PM
 */

#ifndef CONSOLECONTROLLER_H
#define CONSOLECONTROLLER_H

#include "Controller.h"

class ConsoleController : public Controller {
public:
    ConsoleController();
    ~ConsoleController();
    
    int move();
    bool madeTurn() const;
    void setPlayerNr(int playerNr);
    int getPlayerNr() const;
    void setMadeTurn(bool);
    void set_next_move(int);
    
private:
    int mPlayerNr;
    bool m_madeTurn;;
    int m_nextMove;
    ConsoleController(const ConsoleController& orig);
};

#endif /* CONSOLECONTROLLER_H */

