#ifndef Graph_h
#define Graph_h
#include <vector>
#include <stdio.h>
#include <iostream>
#include <iterator>
#include "ESetErrors.h"
#include <algorithm>
using namespace std;

struct Edge 
{
    float weight; 
    int id; 
    Edge(int to_id, float new_weight)
    {
        weight = new_weight;
        id = to_id;
    }
};
struct Vertex 
{
    int id;
    int color;
    vector<Edge> edges;
    Vertex(int new_id)
    {
        id = new_id;
        color = 0;
    }
};
class Graph
{
private:
    vector<Vertex> graph;
public:
    ~Graph();

    int find_vertex(int id);
    void add_vertex(int id);
    bool remove_vertex(int id);

    void add_edge(int from, int to, int weight);
    bool remove_edge(int from, int to);
    bool find_edge(int from, int to);
    int find_index_edge(int from, int to);
    void print();

    vector<Edge> edges(int from);
    int order(); 
    int degree(int id); 
    
    void exp(vector<int>& result);
    vector<int> shortest_path(int from, int to, int& weight);
  
    void clean_color();
    void walk(int from);
    vector<int> Dijkstra(int S, vector<Vertex>& matrix, int N, vector<vector<int>>& way);
    vector<Vertex> create_mat();
    int emergency();
};
#endif