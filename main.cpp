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


#include "GameEngine.h"


int main(int argc, char** argv) {

      GameEngine game2("Maps/level2.txt");
      game2.run();
    
    return 0;
}


/*
#include "DungeonMap.h"
#include "Ai.h"
#include <vector>
#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::vector;
using std::string;

int main() {
    
    vector<Position> pos;
    
    vector<string> mapVec = {
        {"5 5"},
        {"#####"},
        {"#...#"},
        {"#...#"},
        {"#...#"},
        {"#####"}
    };
    DungeonMap map(mapVec);
    
    std::map<Position, std::map<Position, int> > graph;
    std::map<Position, Position> previous;
    fillGraph(map, graph);
    dijkstra({3,3}, graph, previous);
    getShortestPath(pos, {3,3},{1,1}, previous);
    
    for (auto it : pos)
        cout << it << endl;
    
    return 0;
}
*/