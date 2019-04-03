#include <iostream>
#include <vector>
#include <list>

using std::cout;
using std::cin;
using std::vector;
using std::list;
using std::min;


static const int INF = 1000;

class Edge {
public:
    int vertex, flow, capacity;
    int index_rev, number;

    Edge(int vertex, int flow, int capacity, int index_rev, int number) :
            vertex(vertex), flow(flow), capacity(capacity), index_rev(index_rev), number(number) {}
};

class Graph {
public:
    explicit Graph(int size_v) : size_v(size_v) {
        //graph = new vector<Edge>[size_v];
        //level = new int[size_v];
        graph.resize(size_v);
        level.resize(size_v);
    }
/*
    ~Graph() {
        delete[] graph;
        delete[] level;
    }*/

    void addEdge(int used_edges, int end, int capacity, int number) {
        Edge *a = new Edge(end, 0, capacity, static_cast<int>(graph[end].size()), number);
        Edge *b = new Edge(used_edges, 0, capacity, static_cast<int>(graph[used_edges].size()), -number);
        graph[used_edges].push_back(*a);
        graph[end].push_back(*b); // reverse edge
    }

    bool bfs(); // residual graph

    void updateLevels() {
        for (int i = 0; i < size_v; ++i) level[i] = -1;
        level[0] = 0;
    }

    int pushFlow(int u, int flow, int used_edges[]);

    int Dinic(int s, int t);

    const vector<vector<Edge>> &returnGraph();

private:
    int size_v;
    vector<int> level;
    vector<vector<Edge>> graph;

};

bool Graph::bfs() {

    updateLevels();

    list<int> queue;
    queue.push_back(0);

    while (!queue.empty()) {
        int u = queue.front();
        queue.pop_front();
        for (auto i = graph[u].begin(); i != graph[u].end(); ++i) {
            Edge &e = *i;
            if (level[e.vertex] < 0 && e.flow < e.capacity) {
                level[e.vertex] = level[u] + 1;
                queue.push_back(e.vertex);
            }
        }
    }
    return level[size_v - 1] >= 0;
}

int Graph::pushFlow(int u, int flow, int used_edges[]) {
    if (!flow) return 0;

    if (u == size_v - 1)
        return flow;

    while (used_edges[u] < graph[u].size()) {
        Edge &e = graph[u][used_edges[u]];

        if (level[e.vertex] == level[u] + 1 && e.flow < e.capacity) {
            int newFlow = pushFlow(e.vertex, min(flow, e.capacity - e.flow), used_edges);
            if (newFlow > 0) {
                e.flow += newFlow;
                graph[e.vertex][e.index_rev].flow -= newFlow;
                return newFlow;
            }
        }
        used_edges[u]++;
    }

    return 0;
}

int Graph::Dinic(int s, int t) {

    if (s == t)
        return -1;

    int answer = 0;
    while (bfs()) {
        int *used_edges = new int[t];
        while (int flow = pushFlow(s, INF, used_edges))
            answer += flow;
    }
    return answer;
}

vector<vector<Edge>> const &Graph::returnGraph() {
    return graph;
}

int main() {
    int n, m;
    cin >> n >> m;

    Graph g(n);
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        g.addEdge(a - 1, b - 1, c, i + 1);
    }

    cout << g.Dinic(0, n - 1) << "\n";

    vector<int> answer(m, 0);
    for (const auto& i: g.returnGraph()) {
        for(auto j: i) {
            if ((j.number > 0 && j.flow > 0) || (j.number < 0 && j.flow < 0)) answer[abs(j.number) - 1] = abs(j.flow);
            else answer[abs(j.number) - 1] = -abs(j.flow);
        }
    }

    for (auto i: answer) {
        cout << i << "\n";
    }
    return 0;
} 