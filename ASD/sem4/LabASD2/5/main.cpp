#include <iostream>

#include <iostream>
#include <vector>
#include <list>
#include <list>
#include <fstream>

using std::cout;
using std::cin;
using std::vector;
using std::list;
using std::min;

std::ifstream in ("mincost.in");
std::ofstream out("mincost.out");

static const long long INF = 1000000000000000000;

class Edge {
public:
    long long vertex, flow, capacity;
    long long index_rev, cost;

    Edge(long long vertex, long long flow, long long capacity, long long index_rev, long long cost) :
            vertex(vertex), flow(flow), capacity(capacity), index_rev(index_rev), cost(cost) {}

};

class Graph {
public:
    explicit Graph(long long size_v) : size_v(size_v) {
        graph.resize(size_v);
    }

    void addEdge(long long start, long long end, long long capacity, long long cost) {
        Edge *a = new Edge(end, 0, capacity, static_cast<long long>(graph[end].size()), cost);
        Edge *b = new Edge(start, 0, 0, static_cast<long long>(graph[start].size()), -cost);
        graph[start].push_back(*a);
        graph[end].push_back(*b); // reverse edge
        delete a;
        delete b;
    }

    const vector<vector<Edge>> &returnGraph();

    long long minCostFlow(long long s, long long t,long long k);

private:
    long long size_v;
    vector<vector<Edge>> graph;


    bool local_path(long long s, long long t, vector<long long> & path, vector<long long> & index) {
        std::list<long long> list;
        list.push_front(s);

        std::vector<long long> local_costs(size_v, INF);
        local_costs[s] = 0;

        std::vector<long long> visited(size_v);

        while (!list.empty()) {

            long long v = list.front();
            list.pop_front();
            visited[v] = -1;

            for (long long i = 0; i < graph[v].size(); ++i) {
                Edge &u = graph[v][i];
                if (u.flow < u.capacity && local_costs[v] + u.cost < local_costs[u.vertex]) {
                    local_costs[u.vertex] = local_costs[v] + u.cost;

                    if (visited[u.vertex] == 0) list.push_back(u.vertex);
                    else if (visited[u.vertex] == -1) list.push_front(u.vertex);

                    path[u.vertex] = v;
                    visited[u.vertex] = 1;
                    index[u.vertex] = i;
                }
            }
        }

        return local_costs[t] == INF;
    }

};


vector<vector<Edge>> const &Graph::returnGraph() {
    return graph;
}

long long Graph::minCostFlow(long long s, long long t, long long k) {
    vector<long long> path(size_v), index(size_v);
    long long flow = 0, cost = 0;

    while (flow < k) {

        if (local_path(s,t, path, index)) return cost;

        long long addFlow = k - flow;

        for (long long v = t; v != s; v = path[v]) {
            long long parent = path[v], index_v = index[v];
            addFlow = min (addFlow, graph[parent][index_v].capacity - graph[parent][index_v].flow);
        }
        for (long long v = t; v != s; v = path[v]) {
            long long parent = path[v], index_v = index[v],  r = graph[parent][index_v].index_rev;
            graph[parent][index_v].flow += addFlow;
            graph[v][r].flow -= addFlow;
            cost += graph[parent][index_v].cost * addFlow;
        }
        flow += addFlow;
    }
    return cost;
}



int main() {
    int n, m;
    cin >> n >> m;

    Graph g(n + n + 2);

    for (int i = 1; i < n + 1; ++i) {
        long long a;
        cin >> a;
        g.addEdge(i, n + n + 1, 1, 0);
        g.addEdge(n + i, i, INF, a);
        g.addEdge(i, n + i, INF, 0);
        g.addEdge(0, n + i, 1, 0);
    }

    for (int i = 0; i < m; ++i) {
        long long a, b, c;
        cin >> a >> b >> c;
        g.addEdge(n + a, b, INF, c);
    }

    cout << g.minCostFlow(0, n + n + 1, INF);

}