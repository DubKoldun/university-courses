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
vector <int> colorEdges;
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

void paint(int v, int color, int p){
    used[v] = true;
    for (auto i: graf[v]) {
        if (i.first == p) continue;
        if (!used[i.first]){
            if ((up[i.first] >= tIn[v])){
                ++maxColor;
                for (auto &j: graf[v]) if (j.first == i.first) colorEdges[j.second] = maxColor;
                paint(i.first,maxColor,v);
            } else {
                for (auto &j: graf[v]) if (j.first == i.first) colorEdges[j.second] = color;
                paint(i.first,color,v);
            }
        } else if (tIn[i.first] < tIn[v]) {
            for (auto &j : graf[v]) if (j.first == i.first) colorEdges[j.second] = color;
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
    colorEdges.resize(amountE);

    int buff = amountE;
    while(amountE > 0){
        --amountE;
        int v1, v2;
        cin >> v1 >> v2;
        --v1, --v2;
        graf[v1].push_back(std::pair<int,int>(v2,buff - amountE - 1));
        graf[v2].push_back(std::pair<int,int>(v1,buff - amountE - 1));
    }

    for (int i = 0; i < amountV; ++i){
        if(!used[i]){
            dfs(i,-1);
        }
    }

    for (auto &&i : used) i = false;

    for (int i = 0; i < amountV; ++i){
        if(!used[i]){
            paint(i,maxColor, -1);
        }
    }

    cout << maxColor << "\n";
    for (auto item: colorEdges){
        cout << item << " ";
    }


    return 0;
}