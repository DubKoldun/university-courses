#include <iostream>
#include <vector>
#include <set>

using std::vector;
using std::cout;
using std::cin;
using std::pair;
using std::set;

typedef pair<int,int> Pair;

vector <bool> used;
vector <int>  distance;
vector <vector<Pair>> graf;

const int INF = 1000000;

set<Pair> dei;


#define weight item.second
#define SECOND item.first


int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int amountV, amountE;
    cin >> amountV >> amountE;
    distance.resize(amountV, INF);
    used.resize(amountV);
    graf.resize(amountV);

    for (int i = 0; i < amountE; ++i){
        int v1, v2, w;
        cin >> v1 >> v2 >> w;
        --v1, --v2;
        graf[v1].push_back(Pair(v2,w));
        graf[v2].push_back(Pair(v1,w));
    }

    dei.insert(Pair(0,0));
    distance[0] = 0;

    for (int i = 0; i < amountV; ++i){
        auto buff = dei.begin();
        while (used[buff->second] && !dei.empty()){
            dei.erase(dei.begin());
            buff = dei.begin();
        }

        int v1 = buff->second;
        used[v1] = true;

        for (const auto &item: graf[v1]){
            if (distance[v1] + weight < distance[SECOND]) {
                distance[SECOND] = distance[v1] + weight;
                dei.insert(Pair(distance[SECOND],SECOND));
            }
        }

    }

    for (auto i: distance){
        cout << i << " ";
    }

    return 0;
}