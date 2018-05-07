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

class Item {
public:
    Item();
    virtual ~Item();
    
   // virtual int modifyStrength() = 0;
    virtual int modifyStrength(int strength)  = 0;
   // virtual int modifyStamina() = 0;
    virtual int modifyStamina(int stamina) = 0;    
private:
    Item(const Item& orig);
};


class ArmingSword : public Item {};
class Greatsword : public Item {};
class Club : public Item {};
class RapierAndDagger : public Item {};
class Gameson : public Item {};
class MailArmour : public Item {};
class Shield : public Item {};
class FullPlateArmour : public Item {};

#endif /* ITEM_H */

