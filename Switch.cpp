/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Switch.cpp
 * Author: snbl
 * 
 * Created on April 27, 2018, 4:39 PM
 */

#include "Switch.h"

Switch::Switch() : Active('?'), m_wasUsed(false), m_sign('?') {}

Switch::~Switch() {}

bool Switch::use() {
    m_sign = '!';
    return m_wasUsed = true;
}