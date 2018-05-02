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
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

using std::cin;

ConsoleController::ConsoleController() {
}

ConsoleController::ConsoleController(const ConsoleController& orig) {
}

ConsoleController::~ConsoleController() {
}

int ConsoleController::move() {
    sf::Event event;

    while (true) {
        if (sf::Event::KeyReleased == event.type) {
            return 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)) {
            return 2;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3)) {
            return 3;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4)) {
            return 4;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num5)) {
            return 5;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num6)) {
            return 6;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num7)) {
            return 7;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num8)) {
            return 8;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num9)) {
            return 9;
        }

    }
    char c = '0';
    while (c < '1' || c > '9') {
        cin >> c;
    }
    return static_cast<int> (c - '0');

}