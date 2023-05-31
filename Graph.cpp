#include "Graph.h"

Graph:: ~Graph()
{
    graph.clear();
}


int Graph::find_vertex(int value)
{
    if (graph.size() == 0) return -1;

    for (auto i = graph.begin(); i != graph.end(); i++)
    {
        if (i->id == value)
            return int(i - graph.begin());
    }
    return -1;
}


void Graph::add_vertex(int id)
{
    if (find_vertex(id) != -1) throw EUncorrectIndex();
    Vertex v(id);
    graph.push_back(v);
}


bool Graph::remove_vertex(int id)
{
    int index = find_vertex(id);
    if (index == -1) throw EUnpossibal();

    for (auto i = graph.begin(); i != graph.end(); i++)
    {
        if (find_edge(i->id, id))
            remove_edge(i->id, id);
    }
    graph[index].edges.clear();
    graph.erase(graph.begin() + index);
    return true;
}


bool Graph::find_edge(int from, int to)
{
    if (graph.size() == 0) return false;
    int i_from = find_vertex(from);
    int i_to = find_vertex(to);
    if (i_to == -1 || i_from == -1) throw EUnpossibal();

    for (auto i = graph[i_from].edges.begin(); i != graph[i_from].edges.end(); i++)
    {
        if (i->id == to)
            return true;
    }
    return false;
}

int Graph::find_index_edge(int from, int to)
{
    if (graph.size() == 0) return false;
    int i_from = find_vertex(from);
    int i_to = find_vertex(to);
    if (i_to == -1 || i_from == -1) throw EUnpossibal();

    for (auto i = graph[i_from].edges.begin(); i != graph[i_from].edges.end(); i++)
    {
        if (i->id == to)
            return int(i - graph[i_from].edges.begin());
    }
    return false;
}

void Graph::add_edge(int from, int to, int weight)
{
    int i_from = find_vertex(from);
    int i_to = find_vertex(to);
    if (i_to == -1 || i_from == -1) throw EUnpossibal();
    if (find_edge(from, to)) throw EUncorrectIndex();

    Edge tmp(to, weight);
    graph[i_from].edges.push_back(tmp);
}
bool Graph::remove_edge(int from, int to)
{
    int i_from = find_vertex(from);
    int i_to = find_vertex(to);
    if (i_to == -1 || i_from == -1) throw EUnpossibal();
    if (!find_edge(from, to)) throw EUnpossibal();

    graph[i_from].edges.erase(graph[i_from].edges.begin() + i_to);
    return true;
}


void Graph::print()
{
    for (auto i = graph.begin(); i != graph.end(); i++)
    {
        cout << i->id << ": ";
        for (auto j = i->edges.begin(); j != i->edges.end(); j++)
        {
            cout << j->id << ", ";
        }
        cout << endl;
    }
}

vector<Edge> Graph::edges(int from)
{
    int index = find_vertex(from);
    if (index == -1) throw EUnpossibal();

    return graph[index].edges;
}

int Graph::order()
{
    return int(graph.size());
}//порядок число вершин


int Graph::degree(int id)
{
    int index = find_vertex(id);
    if (index == -1) throw EUnpossibal();

    int count = 0;
    for (auto i = graph.begin(); i != graph.end(); i++)
    {
        if (find_edge(i->id, index))
            count++;
    }
    return count;
}

void Graph::exp(vector<int>& result)
{
    vector<int>::iterator i;

    if (result.size() == 0) return;
    for (i = result.end() - 1; i != result.begin(); i--)
    {
        if (!find_edge(*(i - 1), *i))
            result.erase(i - 1);
    }
    return;
}

vector<Vertex> Graph::create_mat()
{
    vector<Vertex> w;
    for (auto i = graph.begin(); i != graph.end(); i++)
    {
        w.push_back(i->id);
    }
    for (auto i = w.begin(); i != w.end(); i++)
    {
        for (auto j = w.begin(); j != w.end(); j++)
        {
            if (find_edge(i->id, j->id))
            {
                for (auto k = graph[find_vertex(i->id)].edges.begin(); k != graph[find_vertex(i->id)].edges.end(); k++)
                {
                    if (k->id == j->id)
                    {
                        Edge tmp(j->id, k->weight);
                        i->edges.push_back(tmp);
                    }
                }
            }
            else
            {
                Edge tmp(j->id, INT_MAX);
                i->edges.push_back(tmp);
            }
        }
    }
    return w;
}

vector<int> Graph::shortest_path(int from, int to, int& weight)
{
    int i_from = find_vertex(from);
    int i_to = find_vertex(to);
    if (i_from == -1) throw EUnpossibal();
    if (i_to == -1) throw EUnpossibal();
    if (i_to == i_from) throw EUnpossibal();

    vector<Vertex> graph_mat = create_mat();
    vector<vector<int>> way;
    vector<int> result = Dijkstra(i_from, graph_mat, int(graph.size()), way);

    for (auto i : way)
    {
        exp(i);
    }
    weight = result[i_to];
    return way[i_to];
}
//обход

void Graph::clean_color()
{
    for (auto i = graph.begin(); i != graph.end(); i++)
    {
        i->color = 0;
    }
}
void Graph::walk(int from)
{
    int index = find_vertex(from);
    if (index == -1) throw EUncorrectIndex();
    cout << graph[index].id;
    graph[index].color = 1;
    for (auto i = graph[index].edges.begin(); i != graph[index].edges.end(); i++)
    {
        int tmp = find_vertex(i->id);
        if (graph[tmp].color == 0)
        {
            cout << " -> ";
            walk(i->id);
        }
    }
    graph[index].color = 2;
}

vector<int> Graph::Dijkstra(int S, vector<Vertex>& matrix, int N, vector<vector<int>>& way)
{
    //    s индекс начала
    vector<int> path;
    way.resize(N);

    vector<bool> valid;
    valid.resize(N);
    fill(valid.begin(), valid.end(), true);

    vector<int> weight;
    weight.resize(N);
    fill(weight.begin(), weight.end(), INT_MAX);

    weight[S] = 0;
    for (int i = 0; i < N; i++)
    {
        int min_weight = INT_MAX;
        int ID_min_weight = -1;
        for (int j = 0; j < N; j++)
        {
            if (valid[j] && weight[j] < min_weight)
            {
                min_weight = weight[j];
                ID_min_weight = j;
            }
        }
        if (ID_min_weight == -1)
            break;
        path.push_back(matrix[ID_min_weight].id);
        for (int z = 0; z < N; z++)
        {
            if (weight[ID_min_weight] + matrix[ID_min_weight].edges[z].weight < weight[z])
            {
                weight[z] = weight[ID_min_weight] + matrix[ID_min_weight].edges[z].weight;
                int k = matrix[ID_min_weight].edges[z].id;
                way[z] = path;
                way[z].push_back(k);
            }
        }
        valid[ID_min_weight] = false;
    }
    return weight;
}

int Graph::emergency()
{
    if (graph.size() == 0) throw EUnpossibal();

    int max = INT_MIN;
    int max_id = graph[0].id;
    for (auto i = graph.begin(); i != graph.end(); i++)
    {
        int sum = 0;
        for (auto j = i->edges.begin(); j != i->edges.end(); j++)
        {
            sum += j->weight;
        }
        for (auto j = graph.begin(); j != graph.end(); j++)
        {
            if (find_edge(j->id, i->id))
                sum += j->edges[find_index_edge(j->id, i->id)].weight;
        }
        if (max < sum)
        {
            max = sum;
            max_id = i->id;
        }
    }
    return max_id;
}