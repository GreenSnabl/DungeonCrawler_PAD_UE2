/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Controller.h
 * Author: snbl
 *
 * Created on April 27, 2018, 5:03 PM
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller {
public:
    Controller();
    virtual ~Controller();
    
    static Controller* makeController(char sign);
    
    virtual int move() = 0;
    
private:

    Controller(const Controller& orig);
};

#endif /* CONTROLLER_H */

