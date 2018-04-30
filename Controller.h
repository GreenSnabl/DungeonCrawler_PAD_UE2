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

#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


class Controller {
public:
    Controller();
    virtual ~Controller();
     
    virtual int move() = 0;
    
private:

    Controller(const Controller& orig);
};

#endif /* CONTROLLER_H */

