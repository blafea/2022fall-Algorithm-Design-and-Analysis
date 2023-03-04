#include <bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f

typedef pair<int, int> iPair;

class Graph
{
public:
    int V;
    list<pair<int, int>> *adj;
    Graph(int V);
    Graph(const Graph &g);
    long long int shortestPath(int s);
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<iPair>[V];
}

long long int Graph::shortestPath(int s)
{
    priority_queue<iPair, vector<iPair>, greater<iPair>> pq;
    vector<long long int> dist(V, INF);

    pq.push(make_pair(0, s));
    dist[s] = 0;

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        list<pair<int, int>>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            int v = (*i).first;
            int weight = (*i).second;

            if (dist[v] > dist[u] + weight)
            {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    long long int ans = 0;
    for (int i = 0; i < V; ++i)
        ans += dist[i];
    return ans;
}

int main()
{
    int N, M, a, b, c;
    cin >> N >> M;
    Graph g(N);
    for (int i = 0; i < M; i++)
    {
        cin >> a >> b >> c;
        g.adj[a - 1].push_back(make_pair(b - 1, c));
    }
    long long int ans = INT64_MAX, temp;
    for (int i = 1; i < N; i++)
    {
        g.adj[0].push_back(make_pair(i, 0));
        temp = g.shortestPath(0);
        if (temp < ans)
            ans = temp;
        g.adj[0].pop_back();
    }
    cout << ans;
    return 0;
}