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

// Die Dijkstra Funktion ist angelehnt an den Kommentar von Samuel auf
// https://stackoverflow.com/questions/3447566/dijkstras-algorithm-in-c

#ifndef AI_H
#define AI_H
#include <map>
#include "DungeonMap.h"

    template<typename T>
    void fillGraph(DungeonMap* map, std::map<Position, std::map<Position, T> >& graph) {
    for (int i = 0; i < map->getHeight(); ++i) {
        for (int j = 0; j < map->getWidth(); ++j) {
            if (map->find({j, i})->isWalkable()) {

                for (int k = i - 1; k < i + 2; ++k) {
                    for (int l = j - 1; l < j + 2; ++l) {
                        if (k < 0 || k >= map->getHeight() || l < 0 || l >= map->getWidth() || (k == i && l == j)) continue;
                        if (map->find({l, k})->isWalkable()) graph[{j, i}][{l, k}] = 1;
                    }
                }
            }
        }
    }
}

    
    
    bool getShortestPath(vector<Position>& shortestPath, Position from, Position to, std::map<Position, Position>& previous);
    void dijkstra(Position from, std::map<Position, std::map<Position, int> >& graph, std::map<Position, Position>& previous);
    void a_star(Position source, Position destination, std::map<Position, std::map<Position, double> >& graph, std::map<Position, Position>& previous);
    
#endif /* AI_H */

