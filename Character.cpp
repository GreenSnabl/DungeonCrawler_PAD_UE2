/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Character.cpp
 * Author: den
 * 
 * Created on April 19, 2018, 8:36 PM
 */

#include "Character.h"
#include "ConsoleController.h"
#include "Player.h"
#include "NPC.h"


Character::Character(char sign, Controller* controller, Position pos) : m_sign{sign}, m_controller{controller} {
    
}

Character::Character(const Character& orig) {

}

Character::~Character() {
    delete m_controller;
}

char Character::getSign() const
{
    return m_sign;
}

int Character::move()
{
    m_controller->move();
}

Character* Character::makeCharacter(char sign, Position pos)
{
    switch (sign) {
        case 'C'  : return new Player(pos);
        case 'G'  : return new Enemy(sign, new AiController(AiController::PATROL), pos);
        case 'N'  : return new Neutral(sign, new AiController(AiController::HOLD), pos);
        default   : return nullptr;
               
    
    }
}

void Character::setSprite(sf::Texture& tileset, int tilesize, sf::Vector2u tilesetSize)
{
    m_sprite.setTexture(tileset);
    
    int x,y;
    x = m_spriteId % tilesetSize.x;
    y = m_spriteId / tilesetSize.x;
    
    m_sprite.setTextureRect({x, y, tilesize, tilesize});
}

void Character::render(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}