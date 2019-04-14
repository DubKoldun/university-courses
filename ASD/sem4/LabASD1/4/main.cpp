#include <iostream>
#include <vector>
#include <list>
#include <limits>

using std::cout;
using std::cin;
using std::vector;
using std::list;
using std::min;


static const int INF = std::numeric_limits<int>::max();

class Edge {
public:
    int vertex, flow, capacity;
    int index_rev;

    Edge(int vertex, int flow, int capacity, int index_rev) :
            vertex(vertex), flow(flow), capacity(capacity), index_rev(index_rev) {}
};

class Graph {
public:
    explicit Graph(int size_v) : size_v(size_v) {
        graph.resize(size_v);
        level.resize(size_v);
    }

    void addEdge(int start, int end, int capacity) {
        Edge *a = new Edge(end, 0, capacity, static_cast<int>(graph[end].size()));
        Edge *b = new Edge(start, 0, 0, static_cast<int>(graph[start].size()));
        graph[start].push_back(*a);
        graph[end].push_back(*b); // reverse edge
        delete a;
        delete b;
    }

    void deleteEdge(int start, int end) {
        for (auto &i: graph[start]) {
            if (i.vertex == end) {
                i.flow = 0;
                return;
            }
        }
    }

    bool bfs(int s, int t); // residual graph

    int pushFlow(int u, int t, int flow, vector<int> &used_edges);

    int Dinic(int s, int t);

    const vector<vector<Edge>> &returnGraph() const;

    int size() const;

private:
    int size_v;
    vector<int> level;
    vector<vector<Edge>> graph;

    void updateLevels(int s) {
        for (int i = 0; i < size_v; ++i) level[i] = -1;
        level[s] = 0;
    }

};

bool Graph::bfs(int s, int t) {

    updateLevels(s);

    list<int> queue;
    queue.push_back(s);

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
    return level[t] >= 0;
}

int Graph::pushFlow(int u, int t, int flow, vector<int> &used_edges) {

    if (!flow) return 0;

    if (u == t)
        return flow;

    while (used_edges[u] < graph[u].size()) {
        Edge &e = graph[u][used_edges[u]];

        if (level[e.vertex] == level[u] + 1 && e.flow < e.capacity) {
            int newFlow = pushFlow(e.vertex, t, min(flow, e.capacity - e.flow), used_edges);
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
    while (bfs(s, t)) {
        vector<int> used_edges(size_v);
        while (int flow = pushFlow(s, t, INF, used_edges))
            answer += flow;
    }
    return answer;
}

vector<vector<Edge>> const &Graph::returnGraph() const {
    return graph;
}

int Graph::size() const {
    return size_v;
}


int main () {
    int n = 0, m = 0;
    cin >> n >> m;

    const int S = 0, T = n + m + 1;

    Graph g(T+1);

    for (int i = 1; i < n + 1; ++i) {
        int a = 0;
        cin >> a;
        while (a != 0) {
            g.addEdge(i, n + a, 1);
            cin >> a;
        }
    }

    for (int i = 1; i < n + 1; ++i) {
        g.addEdge(S, i, 1);
    }

    for (int i = n + 1; i < n + m + 1; ++i) {
        g.addEdge(i, T, 1);
    }

    int a = g.Dinic(S,T);
    if (a < 1) {
        cout << 0;
        return 0;
    }

    cout << a << "\n";

    vector<std::pair<int,int>> answer;

    for (int i = 1; i < n + 1; ++i) {
        for (auto j: g.returnGraph()[i]) {
            if (j.flow == 1 && j.vertex != S) answer.emplace_back(i,j.vertex-n);
        }
    }

    for (auto i: answer) cout << i.first << " " << i.second << "\n";
}
