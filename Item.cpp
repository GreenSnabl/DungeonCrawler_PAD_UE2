/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Item.cpp
 * Author: den
 * 
 * Created on May 7, 2018, 3:18 PM
 */

#include "Item.h"

Item::Item() {
}

Item::Item(const Item& orig) {
}

Item::~Item() {
}

int ArmingSword::modifyStamina(int stamina) {
    return 0;
}

int ArmingSword::modifyStrength(int strength) {
    return 3;
}

int Greatsword::modifyStamina(int stamina) {
    return -1;
}

int Greatsword::modifyStrength(int strength) {
    return 5;
}

int Club::modifyStamina(int stamina) {
    return 0;
}

int Club::modifyStrength(int strength) {
    return strength * 0.5;
}

int RapierAndDagger::modifyStamina(int stamina) {
    return 1;
}

int RapierAndDagger::modifyStrength(int strength) {
    return 2;
}

int Gambeson::modifyStamina(int stamina) {
    return 1;
}

int Gambeson::modifyStrength(int strength) {
    return 0;
}

int MailArmour::modifyStamina(int stamina) {
    return 3;
}

int MailArmour::modifyStrength(int strength) {
    return 0;
}

int Shield::modifyStamina(int stamina) {
    return stamina;
}

int Shield::modifyStrength(int strength) {
    return -1;
}

int FullPlateArmour::modifyStamina(int stamina) {
    return 6;
}

int FullPlateArmour::modifyStrength(int strength) {
    return -2;
}


bool Item::isItem(const std::string& str) {
    for (int i = 0; i < items.size(); ++i)
        if (items[i] == str) return true;
    return false;
}




const std::vector<std::string> Item::items{
    "GreatSword",
    "ArmingSword",
    "Club",
    "RapierAndDagger",
    "Gambeson",
    "MailArmour",
    "Shield",
    "FullPlateArmour"
};