/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: den
 *
 * Created on April 19, 2018, 8:32 PM
 */

#include <string>
#include "GameEngine.h"

//#include "DungeonMap.h"
//#include "Character.h"

using std::string;


void makeMap(const string& str)
{
    DungeonMap map(10,10, str);
}
/*
 * 
 */
int main(int argc, char** argv) {

    const string map =  "##########"
                        "####.....#"
                        "###...x..#"
                        "##.......#"
                        "#........#"
                        "#........#"
                        "#........#"
                        "#........#"
                        "#........#"
                        "##########";
    
    GameEngine game(10, 10, map);
    
    game.run();
    
    
    /*
    DungeonMap dungeonMap(10, 10, map);

    makeMap(map);
    
    DungeonMap copyMap(dungeonMap);
    

    copyMap.print();
    
    Character* c = new Character('@');
    
    copyMap.find({5,5})->setCharacter(c);
    
    copyMap.print();
    
    delete c;
     */
     
    
    
    return 0;
}

