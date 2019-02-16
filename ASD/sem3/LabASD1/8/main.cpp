#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

#define vector std::vector
#define cout std::cout
#define cin std::cin

std::ifstream fin("avia.in");
std::ofstream fout("avia.out");

vector<bool> used;
vector<vector<long long>> baseGraf;
vector<vector<long long>> graf, revGraf;
vector<long long> ord, component, colors, massT;
long long amountV;


void dfsNorm(long long v) {
    used[v] = true;
    for (auto i: graf[v]) {
        if (!used[i]) {
            dfsNorm(i);
        }
    }
    ord.push_back(v);
}

void dfsRev(long long v) {
    used[v] = true;
    component.push_back(v);
    for (auto i: revGraf[v]) {
        if (!used[i]) {
            dfsRev(i);
        }
    }
}


long long answer(long long t) {
    graf.resize(amountV);
    revGraf.resize(amountV);
    for (long long i = 0; i < baseGraf.size(); ++i) {
        for (long long j = 0; j < baseGraf[i].size(); ++j) {
            if (baseGraf[i][j] <= t && i != j) {
                graf[i].push_back(j);
                revGraf[j].push_back(i);
            }
        }
    }

    for (long long i = 0; i < used.size(); ++i) {
        if (!used[i]) {
            dfsNorm(i);
        }
    }

    for (auto &&i: used) i = false;
    std::reverse(ord.begin(), ord.end());

    long long currentColor = 0;
    for (long long v : ord) {
        ++currentColor;
        if (!used[v]) dfsRev(v);
        for (auto item: component)
            colors[item] = currentColor;
        component.clear();
    }
    for (auto i :colors) if (colors[0] != i) return -1;
    return t;
}


int main() {
    fin >> amountV;

    used.resize(amountV);
    colors.resize(amountV);
    baseGraf.resize(amountV);

    for (long long i = 0; i < amountV; ++i) {
        for (long long j = 0; j < amountV; ++j){
            long long v;
            fin >> v;
            baseGraf[i].push_back(v);
            massT.push_back(v);
        }
    }

    sort(massT.begin(), massT.end());

    long long left = 0;
    long long right = massT.size() - 1;

    while (left < right) {
        long long prevl = left, prevr = right;
        long long middle = (left + right) / 2;

        long long a = answer(massT[middle]);
        if (a == massT[middle]) right = middle;
        else left = middle+1;
        graf.clear();
        revGraf.clear();
        for (auto &&i: used) i = false;
        for (auto &&i: colors) i = 0;
        ord.clear();

        if (prevl == left && prevr == right) left = right;
    }
    fout << massT[right];

    return 0;
}