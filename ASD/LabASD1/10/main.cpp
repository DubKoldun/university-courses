#include <iostream>
#include <vector>
#include <algorithm>

#define vector std::vector
#define cout std::cout
#define cin std::cin

class edge{
public:
    int v1, v2, weight;
    edge(int v11, int v22, int w);
};

edge::edge(int v11, int v22, int w) {
    v1 = v11;
    v2 = v22;
    weight = w;
}

vector <edge*> dsf;
vector <int> parent, rang;

int get(int v){
    if (parent[v] != v)
        parent[v] = get(parent[v]);
    return parent[v];
}

void uni(int a, int b){
    int x = get(a);
    int y = get(b);
    if (x != y){
        if (rang[x] == rang[y]) ++rang[x];
        if (rang[x] <  rang[y]) parent[x] = y;
        else parent[y] = x;
    }
}

bool compare(edge const *v1, edge const *v2){
    return (v1->weight < v2->weight);
}

int main() {
    unsigned amountV, amountE;
    cin >> amountV >> amountE;

    parent.resize(amountV);
    rang.resize(amountV);

    for (int i = 0; i < parent.size(); ++i){
        parent[i] = i;
    }

    while (amountE > 0){
        --amountE;
        int v1, v2, w;
        cin >> v1 >> v2 >> w;
        if (v1 != v2) {
            --v1, --v2;
            auto a = new edge(std::min(v1, v2), std::max(v1, v2), w);
            dsf.push_back(a);
        }
    }

    std::sort(dsf.begin(),dsf.end(),compare);

    long long answer = 0;

    for (auto &i : dsf) {
        if (get(i->v1) != get(i->v2)){
            uni(i->v1, i->v2);
            answer += i->weight;
        }
    }

    cout << answer;
    return 0;
}