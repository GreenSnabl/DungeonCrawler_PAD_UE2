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

void makeMap(int height, int width, const string& str) {
    DungeonMap map(height, width, str);
}

/*
 * 
 */
int main(int argc, char** argv) {

    const string map =  "##########"
                        "####.....#"
                        "###......#"
                        "##.......#"
                        "#........#"
                        "#........#"
                        "#........#"
                        "#........#"
                        "#........#"
                        "##########";

    GameEngine game(10, 10, map);

    game.run();

    return 0;
}

