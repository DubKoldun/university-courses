#include <iostream>
#include <vector>
#include <set>

using std::vector;
using std::cout;
using std::cin;
using std::pair;

#define Pair pair<int,int>
#define FIRST item.first.first
#define SECOND item.first.second
#define weight item.second

vector <pair <Pair, int>> edges;

const int INF = 10000000;

int main(){
    int amountV, amountE, k, start;
    cin >> amountV >> amountE >> k >> start;
    --start;

    for(int i = 0; i < amountE; ++i){
        int v1, v2, w;
        cin >> v1 >> v2 >> w;
        --v1, --v2;
        edges.emplace_back(Pair(v1,v2),w);
    }

    vector <vector <int>> DP(static_cast<unsigned long>(k + 1), vector<int>(amountV, INF));

    DP[0][start] = 0;

    for(int i = 1; i < k+1; ++i){
        for (auto item: edges){
            if (DP[i-1][FIRST] != INF) DP[i][SECOND] = std::min(DP[i][SECOND], DP[i-1][FIRST] + weight);
        }
    }

    for(int i = 0; i < amountV; ++i){
        if(DP[k][i] == INF){
            cout << "-1\n";
            continue;
        }
        cout << DP[k][i] << "\n";
    }


    return 0;
}