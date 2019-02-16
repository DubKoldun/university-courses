#include <iostream>
#include <vector>
#include <set>
#include <fstream>

using std::vector;
using std::pair;
using std::set;

std::ifstream in("dwarf.in");
std::ofstream out("dwarf.out");

typedef pair<long long,int> Pair;

vector <long long>  distance;
vector <vector<Pair>> graf;


set<Pair> dei;

#define THIRD item.second
#define SECOND item.first


int main() {

    int amountV, amountC;
    in >> amountV >> amountC;
    distance.resize(amountV);
    graf.resize(amountV);

    for (int i = 0; i < amountV; ++i){
        long long w;
        in >> w;
        dei.insert(Pair(w,i));
        distance[i] = w;
    }

    bool flagOne = false;

    for (int i = 0; i < amountC; ++i){
        int v1, v2, v3;
        in >> v1 >> v2 >> v3;
        if(v1 == 1) flagOne = true;
        --v1, --v2, --v3;
        graf[v2].push_back(Pair(v1,v3));
        graf[v3].push_back(Pair(v1,v2));
    }

    if (!flagOne){
        out << distance[0];
        return 0;
    }

    while (!dei.empty()){

        auto buff = *(dei.begin());
        dei.erase(dei.begin());

        int v1 = buff.second;

        if (distance[v1] < buff.first) continue;

        for (const auto &item: graf[v1]){
            if (distance[v1] + distance[THIRD] < distance[SECOND]) {
                distance[SECOND] = distance[v1] + distance[THIRD];
                dei.insert(Pair(distance[SECOND],SECOND));
            }
        }

    }

    out << distance[0];




    return 0;
}