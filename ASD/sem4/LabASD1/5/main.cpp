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
    int index_rev, x, y;

    Edge(int vertex, int flow, int capacity, int index_rev, int x, int y) :
            vertex(vertex), flow(flow), capacity(capacity), index_rev(index_rev), x(x), y(y) {}
};

class Graph {
public:
    explicit Graph(int size_v) : size_v(size_v) {
        graph.resize(size_v);
        level.resize(size_v);
    }

    void addEdge(int start, int end, int capacity, int x, int y) {
        Edge *a = new Edge(end, 0, capacity, static_cast<int>(graph[end].size()), x, y);
        Edge *b = new Edge(start, 0, 0, static_cast<int>(graph[start].size()), x, y);
        graph[start].push_back(*a);
        graph[end].push_back(*b); // reverse edge
        delete a;
        delete b;
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
            Edge &j = *i;
            if (level[j.vertex] < 0 && j.flow < j.capacity) {
                level[j.vertex] = level[u] + 1;
                queue.push_back(j.vertex);
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
        Edge &j = graph[u][used_edges[u]];

        if (level[j.vertex] == level[u] + 1 && j.flow < j.capacity) {
            int newFlow = pushFlow(j.vertex, t, min(flow, j.capacity - j.flow), used_edges);
            if (newFlow > 0) {
                j.flow += newFlow;
                graph[j.vertex][j.index_rev].flow -= newFlow;
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


void dfs(int v, vector<bool> used, Graph &g) {
    if (used[v]) {
        return;
    }

    used[v] = true;

    for (auto e: g.returnGraph()[v]) {
        if (e.capacity != e.flow) {
            dfs(e.vertex, used, g);
        }
    }
}


class Hatch {
public:
    Hatch(bool ld, size_t x, size_t y) : left_down(ld), x(x), y(y) {}

    const bool left_down;
    const size_t x, y;
};

std::vector<Hatch> paint_table(std::vector<std::vector<bool>> const &table, size_t width, size_t length) {
    Graph net((width + length) * 2);
    const int S = 0, T = (width + length) * 2 - 1;

    size_t diagonals = width + length - 1;

    for (size_t i = 0; i < width; ++i) {
        for (size_t j = 0; j < length; ++j) {
            if (table[i][j]) {
                net.addEdge(i - j + length, i + j + length + width, 1, i, j);
            }
        }
    }

    for (size_t i = 0; i < width + length - 1; ++i) {
        net.addEdge(S, i + 1, 1, 0, 0);
        net.addEdge(i + width + length, T, 1, 0, 0);
    }

    net.Dinic(S, T);
    vector<bool> visited(net.size());
    dfs(S, visited, net);

    std::vector<Hatch> result;
    for (size_t i = 1; i < diagonals + 1; ++i) {
        if (visited[i]) {
            continue;
        }
        for (auto e: net.returnGraph()[i]) {
            if (e.flow != 1) {
                continue;
            }
            result.emplace_back(true, e.x, e.y);
        }
    }

    for (size_t i = diagonals + 1; i < T; ++i) {
        if (!visited[i]) {
            continue;
        }
        for (auto e: net.returnGraph()[i]) {
            if (e.flow != -1) {
                continue;
            }
            result.emplace_back(false, e.x, e.y);
        }
    }

    return std::move(result);
}

void reverse_table(std::vector<std::vector<bool>> &table, size_t width, size_t length) {
    for (size_t i = 0; i < width; ++i) {
        for (size_t j = 0; j < length; ++j) {
            table[i][j] = !table[i][j];
        }
    }
}

std::pair<bool, std::vector<Hatch>>
normalize_table(std::vector<std::vector<bool>> &table, size_t width, size_t length) {
    auto first = paint_table(table, width, length);
    reverse_table(table, width, length);
    auto second = paint_table(table, width, length);

    return first.size() < second.size() ? std::make_pair(true, std::move(first)) : std::make_pair(false,
                                                                                                  std::move(second));
}

int main() {
    size_t width, length;
    std::cin >> width >> length;

    std::vector<std::vector<bool>> table(width, std::vector<bool>(length));

    for (size_t i = 0; i < width; ++i) {
        for (size_t j = 0; j < length; ++j) {
            char c;
            std::cin >> c;
            table[i][j] = c == 'B' == !((i + j) & 1);
        }
    }

    auto[white, result] = normalize_table(table, width, length);

    std::cout << result.size() << '\n';
    for (auto i: result) {
        bool colour = ((i.x + i.y) & 1);
        if (white) {
            colour = !colour;
        }
        std::cout << i.left_down + 1 << ' ' << i.x + 1 << ' ' << i.y + 1 << ' ' << (colour ? 'W' : 'B') << '\n';
    }

    return 0;
}