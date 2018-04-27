/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NPC.cpp
 * Author: snbl
 * 
 * Created on April 27, 2018, 5:21 PM
 */

#include "NPC.h"
#include "AiController.h"

NPC::NPC(char sign, AiController::Behaviour behaviour) : Character(sign, new AiController(behaviour)) {
}


NPC::~NPC() {
}

