#ifndef Graph_h
#define Graph_h
#include <vector>
#include <stdio.h>
#include <iostream>
#include <iterator>
#include "ESetErrors.h"
#include <algorithm>
using namespace std;

struct Edge //ребро
{
    float weight; // вес ребра
    int id; // индекс вершины, в которую ведет ребро
//        vector<Edge> next;
    bool flag;
    Edge(int to_id, float new_weight)
    {
        weight = new_weight;
        id = to_id;
        flag = true;
    }
};
struct Vertex //вершина
{
    int id;
    int color;// название вершины
    vector<Edge> edges; // список исходящих ребер
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
    //проверка-добавление-удаление вершин
    int find_vertex(int id);
    void add_vertex(int id);
    bool remove_vertex(int id);
    //проверка-добавление-удаление ребер
    void add_edge(int from, int to, int weight);
    bool remove_edge(int from, int to);
    bool find_edge(int from, int to);
    int find_index_edge(int from, int to);
    void print();
    //получение всех ребер, выходящих из вершины
    vector<Edge> edges(int from);
    int order(); //порядок число вершин
    int degree(int id); //степень входящие
    //поиск кратчайшего пути
    void exp(vector<int>& result);

    vector<int> shortest_path(int from, int to, int& weight);
    //обход
    void clean_color();
    void walk(int from);
    vector<int> Dijkstra(int S, vector<Vertex>& matrix, int N, vector<vector<int>>& way);
    vector<Vertex> create_mat();
    int emergency();
};
#endif