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
#include <limits>
#include <algorithm>

const int INF = std::numeric_limits<int>::max();

using std::map;
using std::set;

void fillGraph(const DungeonMap& map, std::map<Position, std::map<Position, int> >& graph) {
    graph.clear();
    for (int i = 0; i < map.getHeight(); ++i) {
        for (int j = 0; j < map.getWidth(); ++j) {
            if (map.find({j, i})->isWalkable()) {

                for (int k = i - 1; k < i + 2; ++k) {
                    for (int l = j - 1; l < j + 2; ++l) {
                        if (k < 0 || k >= map.getHeight() || l < 0 || l >= map.getWidth() || (k == i && l == j)) continue;
                        if (map.find({l, k})->isWalkable()) graph[{j, i}][{l, k}] = 1;
                    }
                }
            }
        }
    }
}

void dijkstra(Position from, std::map<Position, std::map<Position,int> >& graph, std::map<Position, Position>& previous)
{
    
    map<Position, int> min_distance;
    previous.clear();
    
    for (auto it : graph) {
        min_distance[it.first] = INF;
    }
    
    min_distance[from] = 0;
    
    set<std::pair<int, Position> > queue; 
    queue.insert(std::make_pair(min_distance[from], from));
    
    while(!queue.empty()) {
        int dist = queue.begin()->first;
        Position u = queue.begin()->second;
        queue.erase(queue.begin());
        
        for (auto it : graph[u])
        {
            int dist_through_u = dist + it.second;
            Position v = it.first;
            if (dist_through_u < min_distance[v])
            {
                queue.erase(std::make_pair(min_distance[v], v));
                
                previous[v] = u;
                min_distance[v] = dist_through_u;
                queue.insert(std::make_pair(min_distance[v], v));            
            }
            
        }
    }
}


bool getShortestPath(vector<Position>& shortestPath, Position from, Position to, std::map<Position, Position>& previous)
{
   
    if (previous.find(to) == previous.end()) return false;
    
    shortestPath.push_back(to);
    
    while (true) {
        shortestPath.push_back(previous[shortestPath[shortestPath.size() - 1]]);
        if (shortestPath[shortestPath.size() - 1] == from) break;
    } 
    std::reverse(shortestPath.begin(), shortestPath.end());
}