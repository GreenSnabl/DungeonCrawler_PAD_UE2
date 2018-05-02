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
#include <SFML/Graphics/Sprite.hpp>

#include "Controller.h"

struct Position{
    int x;
    int y;
};


class Character {
public:
    Character(char sign, Controller* controller, Position pos);
    virtual ~Character() = 0;
    
    char getSign() const;
    int move();

    int getSpriteId() const {return m_spriteId;}
    void setSpriteId(int spriteId) { m_spriteId = spriteId;}
    
    void render(sf::RenderWindow& window);
    void setSprite(sf::Texture& tileset, int tilesize, sf::Vector2u size);
    
    void setSpritePosition(float x, float y) {m_sprite.setPosition({x,y});}
    
    static Character* makeCharacter(char c, Position pos);
private:
    Position pos;
    int m_spriteId;
    char m_sign;
    Controller* m_controller;

    sf::Sprite m_sprite;
    
    Character(const Character& orig);
};

#endif /* CHARACTER_H */

