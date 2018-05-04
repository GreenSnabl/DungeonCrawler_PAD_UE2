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
    void set_next_move(int);
    
private:
    int m_next_move;
    ConsoleController(const ConsoleController& orig);
};

#endif /* CONSOLECONTROLLER_H */

