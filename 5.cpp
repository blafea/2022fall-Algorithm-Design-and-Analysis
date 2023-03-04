#include <iostream>
#include <list>
#include <stack>
using namespace std;

long long int pairs = 0, count = 0;

class Graph
{
    int V;
    list<int> *adj;
    void fillOrder(int v, bool visited[], stack<int> &Stack);
    void find_pair(int v, bool visited[]);

public:
    Graph(int V);
    void addEdge(int v, int w);
    void print_ans();
    Graph getTranspose();
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void Graph::find_pair(int v, bool visited[])
{
    visited[v] = true;
    pairs++;

    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            find_pair(*i, visited);
}

Graph Graph::getTranspose()
{
    Graph g(V);
    for (int v = 0; v < V; v++)
    {
        list<int>::iterator i;
        for (i = adj[v].begin(); i != adj[v].end(); ++i)
        {
            g.adj[*i].push_back(v);
        }
    }
    return g;
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
}

void Graph::fillOrder(int v, bool visited[], stack<int> &Stack)
{
    visited[v] = true;

    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            fillOrder(*i, visited, Stack);

    Stack.push(v);
}

void Graph::print_ans()
{
    stack<int> Stack;
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;
    for (int i = 0; i < V; i++)
        if (visited[i] == false)
            fillOrder(i, visited, Stack);

    Graph gr = getTranspose();

    for (int i = 0; i < V; i++)
        visited[i] = false;

    while (Stack.empty() == false)
    {
        int v = Stack.top();
        Stack.pop();

        if (visited[v] == false)
        {
            gr.find_pair(v, visited);
            count += pairs * (pairs - 1) / 2;
            pairs = 0;
        }
    }
    cout << count << endl;
}

int main()
{
    int n, m, u, v;
    cin >> n >> m;
    Graph g(n);
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v;
        g.addEdge(u - 1, v - 1);
    }
    g.print_ans();
}