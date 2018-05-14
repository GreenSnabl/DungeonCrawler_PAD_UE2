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



class Graph{
    Graph(const DungeonMap& map);
    void fillGraph(const DungeonMap& map);
    void getShortestPath(vector<Position>& shortestPath, const std::map<Position, Position>& previous);
    void dijkstra(Position from, Position to, std::map<Position, Position>& previous);
private:
    std::map <Position, std::map<Position, int> >m_graph;
};

#endif /* AI_H */

