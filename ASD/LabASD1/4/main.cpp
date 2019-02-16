#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

#define cout std::cout
#define cin std::cin
#define vector std::vector

int currentTime = 0, color = 0;

vector <bool> used;
vector <int> tIn;
vector <int> up;
vector <std::pair<vector<int>,int>> graf;
std::stack<int> grafComponents;

void paint(int v){
    int last = -1;
    ++color;
    while(!grafComponents.empty() || last != v){
        last = grafComponents.top();
        graf[last].second = color;
        grafComponents.pop();
    }
}

void dfs(int v, int p){
    grafComponents.push(v);
    used[v] = true;
    ++currentTime;
    up[v] = currentTime;
    tIn[v] = currentTime;
    for (auto i: graf[v].first){
        if (i == p) continue;
        if (used[i])
            up[v] = std::min(up[v],tIn[i]);
        else {
            dfs(i,v);
            up[v] = std::min(up[v],up[i]);
            if (up[i] > tIn[v]) paint(v);
        }
    }
}

int main() {
    unsigned int amountE, amountV;
    cin >> amountV >> amountE;
    used.resize(amountV);
    graf.resize(amountV);
    up.resize(amountV);
    tIn.resize(amountV);

    while(amountE > 0){
        --amountE;
        int v1, v2;
        cin >> v1 >> v2;
        --v1, --v2;
        graf[v1].first.push_back(v2);
        graf[v2].first.push_back(v1);
    }

    for (int i = 0; i < amountV; ++i){
        if(!used[i]){
            dfs(i,-1);
        }
    }

    paint();


    cout << color << "\n";
    for (auto i: graf){
        cout << i.second << " ";
    }


    return 0;
}