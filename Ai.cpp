/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Ai.cpp
 * Author: den
 * 
 * Created on May 14, 2018, 10:19 AM
 */

#include "Ai.h"
#include <set>

using std::map;
using std::set;

Graph::Graph() {}
Graph::Graph(const DungeonMap& map) {
    fillGraph(map);
}

void Graph::fillGraph(const DungeonMap& map) {
    m_graph.clear();
    for (int i = 0; i < map.getHeight(); ++i) {
        for (int j = 0; j < map.getWidth(); ++j) {
            if (map.find({j, i})->isWalkable()) {

                for (int k = i - 1; k < i + 2; ++k) {
                    for (int l = j - 1; l < j + 2; ++l) {
                        if (k < 0 || k >= 6 || l < 0 || l >= 6 || (k == i && l == j)) continue;
                        if (map.find({l, k})->isWalkable() == true) m_graph[{j, i}][{l, k}] = 1;
                    }
                }
            }
        }
    }
}

void Graph::dijkstra(Position from)
{
    map<Position, int> min_distance;
    
}