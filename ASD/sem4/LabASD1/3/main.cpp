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
        for (auto & i: graph[start]) {
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
            int newFlow = pushFlow(e.vertex,t, min(flow, e.capacity - e.flow), used_edges);
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


bool dfs(int vertex, vector<int> &answer, vector<bool> &visited, int t, Graph &g) {
    answer.push_back(vertex);
    visited[vertex] = true;
    if (vertex == t) {
        return true;
    }
    for (auto const &j: g.returnGraph()[vertex]) {
        if (!visited[j.vertex] && j.flow == 1) {
            g.deleteEdge(vertex, j.vertex);
            if (dfs(j.vertex, answer, visited, t, g)) {
                return true;
            }
            else continue;
        }
    }
    return false;
}


int main() {

    int n = 0, m = 0, s = 0, t = 0;
    cin >> n >> m >> s >> t;

    Graph g(n);

    for (int i = 0; i < m; ++i) {
        int a = 0, b = 0;
        cin >> a >> b;
        g.addEdge(a - 1, b - 1, 1);
    }

    vector<bool> visited(g.size(), false);
    vector<int> answer;
    vector<int> answer1;

    if (g.Dinic(s - 1, t - 1) < 2) cout << "NO";
    else {
        cout << "YES\n";
        dfs(s - 1, answer, visited, t - 1, g);
        for (auto && i : visited) i = false;
        dfs(s - 1, answer1, visited, t - 1, g);
    }

    for (auto i: answer) {
        cout << i + 1 << " ";
    }

    cout << "\n";

    for (auto i: answer1) {
        cout << i + 1 << " ";
    }
    return 0;
}