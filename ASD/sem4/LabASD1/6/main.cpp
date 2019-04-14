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



int main() {
    int n;
    std::cin >> n;


    const int S = n, T = n+1;

    Graph g(n + 2);
    vector<vector<char>> table(n,vector<char>(n));
    vector<int> over(n);
    vector<int> possible(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {

            char temp;
            cin >> temp;
            table[i][j] = temp;

            switch (table[i][j]) {
                case '.': if (j > i) {
                        g.addEdge(i, j, 3);
                        possible[i] += 3;
                    } break;
                case 'W': over[i] -= 3; break;
                case 'w': over[i] -= 2; break;
                case 'l': over[i] -= 1; break;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        int temp;
        cin >> temp;
        over[i] += temp;
        g.addEdge(S, i, possible[i]);
        g.addEdge(i, T, over[i]);
    }

    g.Dinic(S,T);

    for (int i = 0; i < g.size() - 2; ++i) {
        for (auto j: g.returnGraph()[i]) {
            if (table[i][j.vertex] == '.' && j.vertex != S && j.vertex!= T) {

                if (j.flow == 0) {
                    table[i][j.vertex] = 'W';
                    table[j.vertex][i] = 'L';
                    continue;
                }

                if (j.flow == 1) {
                    table[i][j.vertex] = 'w';
                    table[j.vertex][i] = 'l';
                    continue;
                }

                if (j.flow == 2) {
                    table[i][j.vertex] = 'l';
                    table[j.vertex][i] = 'w';
                    continue;
                }

                table[i][j.vertex] = 'L';
                table[j.vertex][i] = 'W';
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << table[i][j];
        } cout << "\n";
    }

    return 0;
}