/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Character.h
 * Author: den
 *
 * Created on April 19, 2018, 8:36 PM
 */

#ifndef CHARACTER_H
#define CHARACTER_H
#include "Controller.h"
#include "Item.h"
#include <vector>
#include <string>

class Character {
public:
    Character(char sign, Controller* controller);
    Character(char sign, int stamina, int strength, Controller* controller);
    ~Character();
    
    char getSign() const;
    int move();
    
    void showInfo() const;
    int getMaxHP() const;
    int getCurrentHP() const;
    void setCurrentHP(int);
    
    bool takeDamage(int);
    
    
    void addItem(Item*);
    int getItemSize() const;
    Item* getItem(int) const;
    
    
    int getStrength() const;
    int getStamina() const;
    bool isAlive() const;
    
    Controller* getController() const {return m_controller;}
    
    
    static Character* makeCharacter(const std::string& data);
private:
    
    void updateCurrentHP(double);
    
    int m_strength;
    int m_stamina;
    int m_hitpoints;
    bool m_alive;
    
    char m_sign;
    Controller* m_controller;

    std::vector<Item*> m_items;
    
    Character(const Character& orig);
};

#endif /* CHARACTER_H */

