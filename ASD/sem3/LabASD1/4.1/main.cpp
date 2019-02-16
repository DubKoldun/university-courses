#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

#define cout std::cout
#define cin std::cin
#define vector std::vector

int currentTime = 0, maxColor = 0;

vector <bool> used;
vector <int> tIn;
vector <int> up;
vector <int> colors;

vector <vector<std::pair<int,int>>> graf;

void dfs(int v, int p){
    used[v] = true;
    ++currentTime;
    up[v] = currentTime;
    tIn[v] = currentTime;
    for (auto i: graf[v]){
        if (i.first == p) continue;
        if (used[i.first])
            up[v] = std::min(up[v],tIn[i.first]);
        else {
            dfs(i.first,v);
            up[v] = std::min(up[v],up[i.first]);
        }
    }
}

void paint(int v, int color){
    colors[v] = color;
    for (auto i: graf[v]) {
        if(colors[i.first] == 0){
            if ((up[i.first] > tIn[v]) && i.second < 2){
                ++maxColor;
                paint(i.first,maxColor);
            } else paint(i.first,color);
        }
    }
}

void check(int v, int u){
    for (auto &i: graf[v]) {
        if (u == i.first){
            ++i.second;
        }
    }

    for (auto &i: graf[u]){
        if (v == i.first) {
            ++i.second;
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
    colors.resize(amountV);

    while(amountE > 0){
        --amountE;
        int v1, v2;
        cin >> v1 >> v2;
        --v1, --v2;
        graf[v1].push_back(std::pair<int,int>(v2,0));
        graf[v2].push_back(std::pair<int,int>(v1,0));
        check(v1, v2);
    }

    for (int i = 0; i < amountV; ++i){
        if(!used[i]){
            dfs(i,-1);
        }
    }

    for (int i = 0; i < amountV; ++i){
        if(colors[i] == 0){
            ++maxColor;
            paint(i,maxColor);
        }
    }


    cout << maxColor << "\n";
    for (auto i: colors){
        cout << i << " ";
    }


    return 0;
}