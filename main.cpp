// �����: � �������
// ����� ����������� ����������: ��������
// ������: 3
#include <iostream>
#include "Graph.h"
using namespace std;

void clear_monitor()
{
    for (int i = 0; i < 3; i++)
    {
        cout << endl;
    }
}


int check()
{
    int number;
    while (!(cin >> number) || (cin.peek() != '\n'))
    {
        cin.clear();
        while (cin.get() != '\n');
        cout << "Incorrect value" << endl;
    }
    return number;
}

int muny()
{
    cout << "To press.." << endl;
    cout << "1 - add vertex" << endl;
    cout << "2 - add edge" << endl;
    cout << "3 - has vertex" << endl;
    cout << "4 - has edge" << endl;
    cout << "5 - delete vertex" << endl;
    cout << "6 - delete edge" << endl;
    cout << "7 - degree of vertex" << endl;
    cout << "8 - order" << endl;
    cout << "9 - walk" << endl;
    cout << "10 - dijkstra" << endl;
    cout << "11 - find emergency room" << endl;
    cout << "12 - print" << endl;
    cout << "13 - go out" << endl;
    cout << "Operation �";
    int n = check();
    while (n > 13 || n <= 0)
    {
        cout << "Incorrect value" << endl << "Operation �";
        n = check();
    }
    clear_monitor();
    return n;
}


void add_vertex(Graph& obj)
{
    cout << "What vertex to add?" << endl;
    int id = check();
    obj.add_vertex(id);
}


void add_edge(Graph& obj)
{
    cout << "What edge to add?" << endl;
    cout << "from: ";
    int from = check();
    cout << "to: ";
    int to = check();
    cout << "weight: ";
    int weight = check();
    obj.add_edge(from, to, weight);
}


void has_vertex(Graph& obj)
{
    cout << "What vertex?" << endl;
    int id = check();
    if (obj.has_vertex(id) != -1)
        cout << "vertex is" << endl;
    else
        cout << "vertex is not";
    getchar();
}


void has_edge(Graph& obj)
{
    cout << "What edge?" << endl;
    cout << "from: ";
    int from = check();
    cout << "to: ";
    int to = check();
    if (obj.has_edge(from, to))
        cout << "edge is" << endl;
    else
        cout << "edge is not";
    getchar();
}


void delete_vertex(Graph& obj)
{
    cout << "What vertex?" << endl;
    int id = check();
    obj.remove_vertex(id);
}


void delete_edge(Graph& obj)
{
    cout << "What edge?" << endl;
    cout << "from: ";
    int from = check();
    cout << "to: ";
    int to = check();
    obj.remove_edge(from, to);
}

void degree(Graph& obj)
{
    cout << "What vertex?" << endl;
    int id = check();
    cout << "Degree of " << id << " is " << obj.degree(id);
    getchar();
}

void order(Graph& obj)
{
    cout << "Order is " << obj.order();
    getchar();
}

void walk(Graph& obj)
{
    cout << "What vertex?" << endl;
    int id = check();
    obj.walk(id);
    getchar();
    obj.clean_color();
}

void print(Graph& obj)
{
    obj.print();
    getchar();
}

void dijkstra(Graph& obj)
{
    cout << "What vertex?" << endl;
    cout << "from: ";
    int from = check();
    cout << "to: ";
    int to = check();
    int weight;
    vector<int> res = obj.shortest_path(from, to, weight);
    if (weight == INT_MAX)
        cout << "has not way";
    else
    {
        cout << "Weight = " << weight << endl;
        cout << "Way:" << endl;
        for (auto i : res)
        {
            cout << i << "->";
        }
        cout << "finish";
    }
    getchar();
}

void emergency(Graph& obj)
{
    cout << "Emergency room is " << obj.emergency();
    getchar();
}

int main()
{
    Graph g;

    void (*operatoin[12])(Graph & obj) = { add_vertex,add_edge,has_vertex,has_edge,delete_vertex,delete_edge,degree,order,walk,dijkstra,emergency,print };
    int n = muny();
    getchar();
    while (n < 13)
    {
        try {
            operatoin[n - 1](g);
        }
        catch (ESetErrors& err) {
            err.print_error();
            getchar();
        }
        getchar();
        clear_monitor();
        cout << "What's next?" << endl;
        n = muny();
    }
    return 0;
}