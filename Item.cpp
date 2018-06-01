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

Item* Item::makeItem(const std::string& name)
{
    if (name == "ArmingSword") return new ArmingSword;
    if (name == "Greatsword") return new Greatsword;
    if (name == "Club") return new Club;
    if (name == "RapierAndDagger") return new RapierAndDagger;
    if (name == "Gambeson") return new Gambeson;
    if (name == "MailArmour") return new MailArmour;
    if (name == "Shield") return new Shield;
    if (name == "FullPlateArmour") return new FullPlateArmour;
    return nullptr;
}

const std::vector<std::string> Item::items{
    "Greatsword",
    "ArmingSword",
    "Club",
    "RapierAndDagger",
    "Gambeson",
    "MailArmour",
    "Shield",
    "FullPlateArmour"
};

std::string Item::itemToString(Item* item)
{
    if (Greatsword* temp = dynamic_cast<Greatsword*>(item)) return items[0];
    if (ArmingSword* temp = dynamic_cast<ArmingSword*>(item)) return items[1];
    if (Club* temp = dynamic_cast<Club*>(item)) return items[2];
    if (RapierAndDagger* temp = dynamic_cast<RapierAndDagger*>(item)) return items[3];
    if (Gambeson* temp = dynamic_cast<Gambeson*>(item)) return items[4];
    if (MailArmour* temp = dynamic_cast<MailArmour*>(item)) return items[5];
    if (Shield* temp = dynamic_cast<Shield*>(item)) return items[6];
    if (FullPlateArmour* temp = dynamic_cast<FullPlateArmour*>(item)) return items[7];
}