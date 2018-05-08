/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Item.h
 * Author: den
 *
 * Created on May 7, 2018, 3:18 PM
 */

#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <vector>

class Item {
public:
    Item();
    virtual ~Item();

    // virtual int modifyStrength() = 0;
    virtual int modifyStrength(int strength) = 0;
    // virtual int modifyStamina() = 0;
    virtual int modifyStamina(int stamina) = 0;
    
    
    static bool isItem(const std::string& str);
    
private:
    Item(const Item& orig);
    
    const static std::vector<std::string> items;
};

class ArmingSword : public Item {
public:
    int modifyStamina(int stamina) override;
    int modifyStrength(int strength) override;
};

class Greatsword : public Item {
public:
    int modifyStamina(int stamina) override;
    int modifyStrength(int strength) override;
};

class Club : public Item {
public:
    int modifyStamina(int stamina) override;
    int modifyStrength(int strength) override;
};

class RapierAndDagger : public Item {
public:
    int modifyStamina(int stamina) override;
    int modifyStrength(int strength) override;
};

class Gambeson : public Item {
public:
    int modifyStamina(int stamina) override;
    int modifyStrength(int strength) override;
};

class MailArmour : public Item {
    int modifyStamina(int stamina) override;
    int modifyStrength(int strength) override;
};

class Shield : public Item {
    int modifyStamina(int stamina) override;
    int modifyStrength(int strength) override;
};

class FullPlateArmour : public Item {
    int modifyStamina(int stamina) override;
    int modifyStrength(int strength) override;
};

#endif /* ITEM_H */

