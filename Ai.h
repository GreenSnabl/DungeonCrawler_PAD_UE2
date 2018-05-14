/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Ai.h
 * Author: den
 *
 * Created on May 14, 2018, 10:19 AM
 */

#ifndef AI_H
#define AI_H
#include <map>
#include "DungeonMap.h"



    void fillGraph(DungeonMap* map, std::map<Position, std::map<Position, int> >& graph);
    bool getShortestPath(vector<Position>& shortestPath, Position from, Position to, std::map<Position, Position>& previous);
    void dijkstra(Position from, std::map<Position, std::map<Position, int> >& graph, std::map<Position, Position>& previous);


#endif /* AI_H */

