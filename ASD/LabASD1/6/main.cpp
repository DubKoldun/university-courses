#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

#define vector std::vector
#define cout std::cout
#define cin std::cin

vector<bool> used;
vector<vector<int>> graf, revGraf;
vector<int> ord, component, colors;


void dfsNorm(int v) {
    used[v] = true;
    for (auto i: graf[v]) {
        if (!used[i]) {
            dfsNorm(i);
        }
    }
    ord.push_back(v);
}

void dfsRev(int v) {
    used[v] = true;
    component.push_back(v);
    for (auto i: revGraf[v]) {
        if (!used[i]) {
            dfsRev(i);
        }
    }
}

int main() {
    unsigned amountE, amountV;
    cin >> amountV >> amountE;

    std::set<int> bridges[100000];

    used.resize(amountV);
    graf.resize(amountV);
    revGraf.resize(amountV);
    colors.resize(amountV);

    while (amountE > 0) {
        --amountE;
        int v1, v2;
        cin >> v1 >> v2;
        if (v1 != v2) {
            --v1, --v2;
            graf[v1].push_back(v2);
            revGraf[v2].push_back(v1);
        }
    }

    for (int i = 0; i < used.size(); ++i) {
        if (!used[i]) {
            dfsNorm(i);
        }
    }

    for (auto &&i: used) i = false;
    std::reverse(ord.begin(), ord.end());

    int currentColor = 0;
    for (int i = 0; i < used.size(); ++i) {
        int v = ord[i];
        if (!used[v]) dfsRev(v);


        ++currentColor;
        for (auto item: component)
            colors[item] = currentColor;

        component.clear();
    }




    for (int i = 0; i < graf.size(); ++i) {
        for (auto j: graf[i]) {
            if (colors[i] != colors[j])
                bridges[colors[i]].insert(colors[j]);
        }
    }

    /*for (int i = 0; i < graf.size(); ++i){
        for (int j = 0; j < graf[i].size(); ++j){
            if (colors[i] == colors[graf[i][j]] && (!usedColors[colors[i]][colors[graf[i][j]]])){
                ++amount;
                usedColors[colors[i]][colors[graf[i][j]]] = true;
            }
        }
    }         ????????? set? */


    int amount = 0;
    for (int i = 0; i < currentColor; ++i) {
        amount += bridges[i].size();
    }

    cout << amount;

    return 0;
}