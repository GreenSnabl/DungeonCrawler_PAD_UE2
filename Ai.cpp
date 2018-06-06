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
#include <utility>

const int INF = std::numeric_limits<int>::max();

using std::map;
using std::set;
using std::pair;


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

void a_star(Position source, Position destination, map<Position, map<Position, double> >& graph, map<Position, Position>& previous)
{
    map<Position, double> min_distance;
    map<Position, double> heuristic_distance;
    min_distance.clear();
    previous.clear();
    for (auto it : graph) {
        min_distance[it.first] = INF;
        heuristic_distance[it.first] = sqrt(pow(destination.x - it.first.x, 2) + pow(destination.y - it.first.y, 2));
    }    
    min_distance[source] = 0;
    
    set<pair<double, Position> > queue;
    queue.insert(std::make_pair(min_distance[source], source));
    while (!queue.empty())
    {
        Position u = queue.begin()->second;
        int distance = queue.begin()->first;
        queue.erase(queue.begin());
        
        for (auto it : graph[u])
        {
            Position v = it.first;
            int dist_through_u = distance + it.second + heuristic_distance[v];
            
            if (dist_through_u < min_distance[v])
            {
                queue.erase(std::make_pair(min_distance[v], v));
                previous[v] = u;
                min_distance[v] = dist_through_u;
                queue.insert(std::make_pair(min_distance[v], v));
                if (v == destination) return;
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
    return true;
}

double getDistance(Position source, Position destination)
{
    double delta_x = static_cast<double>(destination.x) - static_cast<double>(source.x);
    double delta_y = static_cast<double>(destination.y) - static_cast<double>(source.y);
    return std::sqrt(std::pow(delta_x, 2) + std::pow(delta_y, 2));
}