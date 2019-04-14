#include <iostream>
#include <vector>
#include <list>
#include <set>

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
        graph.resize(size_v);
        level.resize(size_v);
    }

    void addEdge(int start, int end, int capacity, int number) {
        Edge *a = new Edge(end, 0, capacity, static_cast<int>(graph[end].size()), number);
        Edge *b = new Edge(start, 0, capacity, static_cast<int>(graph[start].size()), -number);
        graph[start].push_back(*a);
        graph[end].push_back(*b); // reverse edge
        delete a;
        delete b;
    }

    bool bfs(); // residual graph

    int pushFlow(int u, int flow, vector<int> & used_edges);

    int Dinic(int s, int t);

    const vector<vector<Edge>> &returnGraph() const;


private:
    int size_v;
    vector<int> level;
    vector<vector<Edge>> graph;

    void updateLevels() {
        for (int i = 0; i < size_v; ++i) level[i] = -1;
        level[0] = 0;
    }

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

int Graph::pushFlow(int u, int flow, vector<int> & used_edges) {
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
        vector <int> used_edges(t);
        while (int flow = pushFlow(s, INF, used_edges))
            answer += flow;
    }
    return answer;
}

vector<vector<Edge>> const &Graph::returnGraph() const {
    return graph;
}

void dfs(int vertex, vector<bool> & used, Graph const& g) {
    if (used[vertex]) return;

    used[vertex] = true;

    for (auto i: g.returnGraph()[vertex]) {
        if (i.flow != i.capacity) dfs(i.vertex, used, g);
    }
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

    g.Dinic(0, n - 1);

    vector<bool> left_part(n);
    dfs(0, left_part, g);

    int flow = 0;
    std::set<int> edges;

    for (int i = 0; i < n; ++i) {
        for (auto j: g.returnGraph()[i]) {
            if (left_part[i] == left_part[j.vertex]) continue;
            flow += abs(j.flow);
            edges.insert(abs(j.number));
        }
    }

    cout << edges.size() << " " << flow/2 << "\n";
    for (auto const& i: edges) {
        cout << i << " ";
    }

    return 0;
}









